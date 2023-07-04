#include "mbed.h"

#include "pc_serial_com.h"
#include "valvula.h"
#include "motor_bomba.h"
#include "alarmas.h"
#include "celda_carga.h"
#include "control_sensores.h"
#include "sistema.h"
#include "arm_book_lib.h"

static Serial usbPort_sistema(USBTX, USBRX);

void sistemaInit(){
    usbPort_sistema.printf("El programa está corriendo!\n");
    valvulaInit();
    motorBombaInit();
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
