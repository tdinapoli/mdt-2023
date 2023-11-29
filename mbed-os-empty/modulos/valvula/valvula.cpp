#include "DigitalOut.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "valvula.h"

#define _IN_1_ D4
#define _IN_2_ D5
#define _IN_3_ D6
#define _IN_4_ D7

#define _IN_BETWEEN_STEPS_DELAY_ 10 
#define _STEPS_TO_OPEN_ 50 

DigitalOut motor_pin_1(_IN_1_);
DigitalOut motor_pin_2(_IN_2_);
DigitalOut motor_pin_3(_IN_3_);
DigitalOut motor_pin_4(_IN_4_);

valveState_t valveState;

static Serial valveSerial(USBTX, USBRX);

StepperMotor::StepperMotor(valveState_t valveState, bridgeState_t bridgeState) : valveState(valveState), bridgeState(bridgeState) {}

void StepperMotor::oneStepRight(){
    switch (bridgeState) {
        case one: stepOneTwo(); break;
        case two: stepTwoThree(); break;
        case three: stepThreeFour(); break;
        case four: stepFourOne(); break;
        default: valveSerial.printf("Estado del puente H desconocido\n"); break;
    }
}

void StepperMotor::oneStepLeft(){
    switch (bridgeState) {
        case one: stepOneFour(); break;
        case two: stepTwoOne(); break;
        case three: stepThreeTwo(); break;
        case four: stepFourThree(); break;
        default: valveSerial.printf("Estado del puente H desconocido\n"); break;
    }
}

void StepperMotor::open(){
    if (valveState == CLOSED){
    int stepsLeft = _STEPS_TO_OPEN_;
    valveSerial.printf("Abriendo valvula...\n");
    while (stepsLeft > 0){
        oneStepLeft(); // esto se podría poner Right según cómo se conecte el motor
        stepsLeft = stepsLeft - 1;
        }
    valveState = OPEN;
    valveSerial.printf("La valvula se termino de abrir\n");
    }
    else {
        valveSerial.printf("La valvula ya esta abierta\n");
    }
}

void StepperMotor::close(){
    if (valveState == OPEN){
    int stepsLeft = _STEPS_TO_OPEN_;
    valveSerial.printf("Cerrando valvula...\n");
    while (stepsLeft > 0){
        oneStepRight(); // esto se podría poner Right según cómo se conecte el motor
        stepsLeft = stepsLeft - 1;
        }
    valveState = CLOSED;
    valveSerial.printf("La valvula se termino de cerrar\n");
    }
    else {
        valveSerial.printf("La valvula ya esta cerrada\n");
    }
}

void StepperMotor::stepOneTwo(){
    motor_pin_1 = 0;
    motor_pin_2 = 1;
    motor_pin_3 = 1;
    motor_pin_4 = 0;
}

void StepperMotor::stepTwoThree(){
    motor_pin_1 = 0;
    motor_pin_2 = 1;
    motor_pin_3 = 0;
    motor_pin_4 = 1;
}

void StepperMotor::stepThreeFour(){
    motor_pin_1 = 1;
    motor_pin_2 = 0;
    motor_pin_3 = 0;
    motor_pin_4 = 1;
}

void StepperMotor::stepFourOne(){
    motor_pin_1 = 1;
    motor_pin_2 = 0;
    motor_pin_3 = 1;
    motor_pin_4 = 0;
}

void StepperMotor::stepOneFour(){
    motor_pin_1 = 1;
    motor_pin_2 = 0;
    motor_pin_3 = 0;
    motor_pin_4 = 1;
}

void StepperMotor::stepTwoOne(){
    motor_pin_1 = 1;
    motor_pin_2 = 0;
    motor_pin_3 = 1;
    motor_pin_4 = 0;
}

void StepperMotor::stepThreeTwo(){
    motor_pin_1 = 0;
    motor_pin_2 = 1;
    motor_pin_3 = 1;
    motor_pin_4 = 0;
}

void StepperMotor::stepFourThree(){
    motor_pin_1 = 0;
    motor_pin_2 = 1;
    motor_pin_3 = 0;
    motor_pin_4 = 1;
}