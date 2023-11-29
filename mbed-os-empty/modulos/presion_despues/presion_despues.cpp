
#include "mbed.h"
#include "presion_despues.h"

AnalogIn presionDespues(A1);


void sensorPresionDespuesInit(){
    }

void sensorPresionDespuesUpdate(){
    }
    
float sensorPresionDespuesRead(){
    return presionDespues.read();
    }