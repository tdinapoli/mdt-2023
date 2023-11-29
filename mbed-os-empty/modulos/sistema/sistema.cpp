#include "mbed.h"

#include "pc_serial_com.h"
//#include "valvula_stepper.h"
#include "motor_bomba_pot.h"
#include "alarmas.h"
#include "celda_carga.h"
#include "control_sensores.h"
#include "sistema.h"
#include "arm_book_lib.h"
#include "valvula.h"

static Serial usbPort_sistema(USBTX, USBRX);

StepperMotor valveMotor(CLOSED); // se le podría poner open. o poner una opción en el menú para setearlo al inicio

void sistemaInit(){
    usbPort_sistema.printf("El programa está corriendo!\n");
//    valvulaStepperInit();
    motorBombaPotInit();
    pcSerialComInit();
    celdaCargaInit();
    controlSensoresInit();
    alarmasInit();
//    userInterfaceInit();
    }

void sistemaUpdate(){
    pcSerialComUpdate();
    controlSensoresUpdate();
//    userInterfaceUpdate();
    delay(TIEMPO_DE_INCREMENTO_MS);
    }
