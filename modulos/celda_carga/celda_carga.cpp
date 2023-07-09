#include "mbed.h"
#include "HX711.h"

#define _FACTOR_CALIBRACION_ 1
#define _ANALOG_VOLTAGE_ 12
#define _CLOCK_PIN_ D8
#define _DOUT_PINT_ D9
#define _GAIN_ 1

HX711 celda(_ANALOG_VOLTAGE_, _CLOCK_PIN_, _DOUT_PINT_, _GAIN_);

static Serial usbPort_pc_celda(USBTX, USBRX);


void celdaCargaInit(){
    if (celda.isReady()){
        usbPort_pc_celda.printf("La celda está lista\n");
    }
    else {
        usbPort_pc_celda.printf("La celda NO está lista\n");
    }
    
    }
    
float celdaCargaRead(){
    return celda.read();
    }
