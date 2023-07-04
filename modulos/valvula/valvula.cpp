#include "mbed.h"
#include "arm_book_lib.h"
#include "valvula.h"
#include "pc_serial_com.h"
#include "sistema.h"


#define _TIEMPO_DE_CIERRE_ 4000 //tiempo tanto para apertura como para cierre de la valvula

DigitalInOut motorM1Pin(PF_2);
DigitalInOut motorM2Pin(PE_3);

estadoValvula_t estadoValvula;

static Serial usbPort_valvula(USBTX, USBRX);


void valvulaInit(){
    //setea pines como openDrain
    motorM1Pin.mode(OpenDrain);
    motorM2Pin.mode(OpenDrain);
    
    //setea pines como input -> motor frenado
    motorM1Pin.input();
    motorM2Pin.input();
    
    //Declara el estado inicial de la válvula
    estadoValvula = CERRADA;
    }

//abre la valvula
void valvulaAbrir(){
    //se fija si está cerrada
    if ( estadoValvula == CERRADA ){
        motorM1Pin.input();
        motorM2Pin.output();
        motorM2Pin = LOW;
        usbPort_valvula.printf("La valvula se esta abriendo...\n");
        delay(_TIEMPO_DE_CIERRE_);
        //setea pines como input -> motor frenado
        motorM1Pin.input();
        motorM2Pin.input();
        estadoValvula = ABIERTA;
        usbPort_valvula.printf("La valvula esta abierta.\n");
        }
    else{
        usbPort_valvula.printf("La valvula ya esta abierta\n");
        }
    }

void valvulaCerrar(){
    if ( estadoValvula == ABIERTA ){
        //cierra la valvula//
        motorM2Pin.input();
        motorM1Pin.output();
        motorM1Pin = LOW;
        usbPort_valvula.printf("La valvula se esta cerrando...\n");
        delay(_TIEMPO_DE_CIERRE_);
        //setea pines como input -> motor frenado
        motorM1Pin.input();
        motorM2Pin.input();
        estadoValvula = CERRADA;
        usbPort_valvula.printf("La valvula esta cerrada\n");
        }
    else{
        usbPort_valvula.printf("La valvula ya esta cerrada\n");
        }
    }

estadoValvula_t estadoValvulaRead(){
    return estadoValvula;
    }

    
