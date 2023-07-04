#include "motor_bomba.h"
#include "mbed.h"

#define _PERIODO_PWM_ 0.01
#define _MUCHO_PWM_ 0.1 //necesario para cambios rápidos
#define _POCO_PWM_ 0.01 //necesario para ajustes

static Serial usbPort_motor_bomba(USBTX, USBRX);
static bool chequearRestriccionesBombaDutyCycle(float dutyCycle_nuevo);

PwmOut motorBombaPWM( PC_8 );


void motorBombaInit(){
    motorBombaPWM.period(_PERIODO_PWM_); //setea el periodo del PWM
    motorBombaPWM.write(0.0f); //setea el duty cycle del PWM   
    }

void setBombaDutyCycle(float dutyCycle){ //Setea el duty Cycle al pin al que esta conectada la bomba
    motorBombaPWM.write(dutyCycle); 
    }

float readBombaDutyCycle(){ //leer el patron de uso del pin al que está conectado la bomba (duty cycle del PWM)
    return motorBombaPWM.read();
    }
    
void subirPocoBombaDutyCycle(){
    float dutyCycle_nuevo = readBombaDutyCycle() + _POCO_PWM_;
    if (chequearRestriccionesBombaDutyCycle(dutyCycle_nuevo)){
        motorBombaPWM.write(dutyCycle_nuevo);
        usbPort_motor_bomba.printf("Duty Cycle: %.2f \n", readBombaDutyCycle());
        }
    else {
        usbPort_motor_bomba.printf("El Duty Cycle excede los valores permitidos \n");
        }
    }

void bajarPocoBombaDutyCycle(){
    float dutyCycle_nuevo = readBombaDutyCycle() - _POCO_PWM_;
    if (chequearRestriccionesBombaDutyCycle(dutyCycle_nuevo)){
        motorBombaPWM.write(dutyCycle_nuevo);
        usbPort_motor_bomba.printf("Duty Cycle: %.2f \n", readBombaDutyCycle());
        }
    else {
        usbPort_motor_bomba.printf("El Duty Cycle excede los valores permitidos \n");
        }
    }
    
void subirMuchoBombaDutyCycle(){
    float dutyCycle_nuevo = readBombaDutyCycle() + _MUCHO_PWM_;
    if (chequearRestriccionesBombaDutyCycle(dutyCycle_nuevo)){
        motorBombaPWM.write(dutyCycle_nuevo);
        usbPort_motor_bomba.printf("Duty Cycle: %.2f \n", readBombaDutyCycle());
        }
    else {
        usbPort_motor_bomba.printf("El Duty Cycle excede los valores permitidos \n");
        }
    }

void bajarMuchoBombaDutyCycle(){
        float dutyCycle_nuevo = readBombaDutyCycle() - _MUCHO_PWM_;
    if (chequearRestriccionesBombaDutyCycle(dutyCycle_nuevo)){
        motorBombaPWM.write(dutyCycle_nuevo);
        usbPort_motor_bomba.printf("Duty Cycle: %.2f \n", readBombaDutyCycle());
        }
    else {
        usbPort_motor_bomba.printf("El Duty Cycle excede los valores permitidos \n");
        }
    }
    

static bool chequearRestriccionesBombaDutyCycle(float dutyCycle_nuevo){
    if (dutyCycle_nuevo > 1.0 || dutyCycle_nuevo < 0.0){
        return false;
        }
    else {
        return true;
        }
    }
