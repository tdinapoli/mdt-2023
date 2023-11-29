#include "mbed.h"
#include "HX711.h"
#include <type_traits>

#define _OFFSET_ -1.20
#define _ANALOG_VOLTAGE_ 5
#define _CLOCK_PIN_ D8
#define _DOUT_PINT_ D9
#define _GAIN_ 128

HX711 celda(_ANALOG_VOLTAGE_, _CLOCK_PIN_, _DOUT_PINT_, _GAIN_);

static Serial usbPort_pc_celda(USBTX, USBRX);


void celdaCargaInit(){

    celda.setDrift(_OFFSET_);

    if (celda.isReady()){
        usbPort_pc_celda.printf("La celda está lista con ganancia %d\n", _GAIN_);
    }
    else {
        usbPort_pc_celda.printf("La celda NO está lista con ganancia %d\n", _GAIN_);
    }
    
    }
    
float celdaCargaRead(){
    return celda.read();
    }
