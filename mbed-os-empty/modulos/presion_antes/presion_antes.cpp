
#include "presion_antes.h"
#include "mbed.h"


AnalogIn presionAntes(A0);


void sensorPresionAntesInit(){
    }

void sensorPresionAntesUpdate(){
    }
    
float sensorPresionAntesRead(){
    return presionAntes.read();
    }
