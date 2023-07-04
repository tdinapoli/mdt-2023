#include "mbed.h"
#include "arm_book_lib.h"
#include "alarmas.h"

DigitalOut rojo(D1);
DigitalOut verde(D2);
DigitalOut azul(D3);

void alarmasInit(){  
    rojo = OFF;
    verde = OFF;
    azul = OFF;
    }

void alarmasCambiarRojo(){
    rojo = !rojo;
    }

void alarmasCambiarVerde(){
    verde = !verde;
    }

void alarmasCambiarAzul(){
    azul = !azul;
    }

bool alarmasEstadoRojo(){
    if (rojo == OFF){
        return false;
        }
    else {
        return true;
        }
    }

bool alarmasEstadoVerde(){
    if (verde == OFF) {
        return false;
        }
    else {
        return true;
        }
    }

bool alarmasEstadoAzul(){
    if (azul == OFF) {
        return false;
        }
    else {
        return true;
        }
    }
    
