#include "DigitalOut.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "valvula_stepper.h"

#define _IN_1_ D4
#define _IN_2_ D5
#define _IN_3_ D6
#define _IN_4_ D7

#define _IN_BETWEEN_STEPS_DELAY_ 10
#define _STEPS_TO_OPEN_ 200 

DigitalOut motor_pin_1(_IN_1_);
DigitalOut motor_pin_2(_IN_2_);
DigitalOut motor_pin_3(_IN_3_);
DigitalOut motor_pin_4(_IN_4_);

estadoValvulaStepper_t estadoValvula;

static Serial valvula_stepper_serial(USBTX, USBRX);
static void fourStepsRight(void);
static void fourStepsLeft(void);

void valvulaStepperInit(){
    estadoValvula = CERRADA;
}

void valvulaStepperAbrir(){
    if (estadoValvula == CERRADA){
        valvula_stepper_serial.printf("Abriendo válvula...\n");
        int steps_left = _STEPS_TO_OPEN_/4;
        while (steps_left>0){
            fourStepsRight(); // se podría cambiar a left según cómo se conecte
            steps_left = steps_left - 1;
        }
        estadoValvula = ABIERTA;
        valvula_stepper_serial.printf("Válvula abierta.\n");
    }
    else {
        valvula_stepper_serial.printf("La válvula ya está abierta");
    }
}

void valvulaStepperCerrar(){
    if (estadoValvula == ABIERTA){
    valvula_stepper_serial.printf("Cerrando válvula...\n");
    int steps_left = _STEPS_TO_OPEN_/4;
    while (steps_left>0){
        fourStepsLeft(); // se podría cambiar a RIGHT según cómo se conecte
        steps_left = steps_left - 1;
    }
    estadoValvula = CERRADA;
    valvula_stepper_serial.printf("Válvula cerrada.\n");
    }
    else {
        valvula_stepper_serial.printf("La válvula ya está cerrada");
    }

}

estadoValvulaStepper_t estadoValvulaStepperRead(){
    return estadoValvula;
}

// esta funcion hace 4 pasos del stepper
// esta definida así para no tener que manejar el orden de los pasos
// que es más complejo. 
static void fourStepsRight(){
    motor_pin_1 = 1;
    motor_pin_2 = 0;
    motor_pin_3 = 1;
    motor_pin_4 = 0;
    delay(_IN_BETWEEN_STEPS_DELAY_);
    motor_pin_1 = 0;
    motor_pin_2 = 1;
    motor_pin_3 = 1;
    motor_pin_4 = 0;
    delay(_IN_BETWEEN_STEPS_DELAY_);
    motor_pin_1 = 0;
    motor_pin_2 = 1;
    motor_pin_3 = 0;
    motor_pin_4 = 1;
    delay(_IN_BETWEEN_STEPS_DELAY_);
    motor_pin_1 = 1;
    motor_pin_2 = 0;
    motor_pin_3 = 0;
    motor_pin_4 = 1;
    delay(_IN_BETWEEN_STEPS_DELAY_);
}

static void fourStepsLeft(){
    motor_pin_1 = 1;
    motor_pin_2 = 0;
    motor_pin_3 = 0;
    motor_pin_4 = 1;
    delay(_IN_BETWEEN_STEPS_DELAY_);
    motor_pin_1 = 0;
    motor_pin_2 = 1;
    motor_pin_3 = 0;
    motor_pin_4 = 1;
    delay(_IN_BETWEEN_STEPS_DELAY_);
    motor_pin_1 = 0;
    motor_pin_2 = 1;
    motor_pin_3 = 1;
    motor_pin_4 = 0;
    delay(_IN_BETWEEN_STEPS_DELAY_);
    motor_pin_1 = 1;
    motor_pin_2 = 0;
    motor_pin_3 = 1;
    motor_pin_4 = 0;
    delay(_IN_BETWEEN_STEPS_DELAY_);
}
