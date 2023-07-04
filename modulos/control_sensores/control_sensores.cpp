#include "arm_book_lib.h"
#include "mbed.h"
#include "presion_antes.h"
#include "presion_despues.h"
#include "motor_bomba.h"
#include "control_sensores.h"
#include "alarmas.h"
#include "celda_carga.h"

#define _PRESION_ANTES_PELIGRO_     0.7 //cambio para ver alarma
#define _PRESION_DESPUES_PELIGRO_   0.7 //cambio para ver alarma
#define _CELDA_CARGA_PELIGRO_ -2000 // cambio para ver alarma

//definiciones de las funciones y variables que voy a usar
static float controlPresionAntes();
static float controlPresionDespues();
static float controlCeldaCarga();
static float control_presion_antes_valor;
static float control_presion_despues_valor;
static float control_celda_carga_valor;
static void alarmaPresionAntes(float control_presion_antes_valor);
static void alarmaPresionDespues(float control_presion_despues_valor);
static void alarmaCeldaCarga(float control_celda_carga_valor);

void controlSensoresInit(){
    }


void controlSensoresUpdate(){
    //guarda los valores de los sensores de presion
    control_presion_antes_valor = controlPresionAntes(); 
    control_presion_despues_valor = controlPresionDespues();
    control_celda_carga_valor = controlCeldaCarga();
    
    //Chequea si los valores de los sensores son muy altos
    alarmaPresionAntes(control_presion_antes_valor);
    alarmaPresionDespues(control_presion_despues_valor);
    alarmaCeldaCarga(control_celda_carga_valor);
    }

static void alarmaPresionAntes(float control_presion_antes_valor){
    //chequea si el valor de presion es muy alto, y si lo es apaga la bomba
    if ( control_presion_antes_valor > _PRESION_ANTES_PELIGRO_ ){
        setBombaDutyCycle(0.0);
        if ( !alarmasEstadoRojo() ){
            alarmasCambiarRojo();
            }
        }
    else {
        if ( alarmasEstadoRojo() ){
            alarmasCambiarRojo();
            }
        }
    }
    
static void alarmaPresionDespues(float control_presion_despues_valor){
    //chequea si el valor de presion es muy alto, y si lo es apaga la bomba
    if ( control_presion_despues_valor > _PRESION_DESPUES_PELIGRO_ ){
        setBombaDutyCycle(0.0);
        if ( !alarmasEstadoVerde() ){
            alarmasCambiarVerde();
            }
        }
    else {
        if ( alarmasEstadoVerde() ){
            alarmasCambiarVerde();
            }
        }
    }
    
static void alarmaCeldaCarga(float control_celda_carga_valor){
    //chequea si el valor de carga es muy bajo, y si lo es apaga la bomba
    if ( control_celda_carga_valor < _CELDA_CARGA_PELIGRO_){
        setBombaDutyCycle(0.0);
        if ( !alarmasEstadoAzul() ){
            alarmasCambiarAzul();
            }
        }
    else {
        if ( alarmasEstadoAzul() ){
            alarmasCambiarAzul();
            }
        }
    }

//funciones que leen los sensores
static float controlPresionAntes(){
    return sensorPresionAntesRead();
    }
    
static float controlPresionDespues(){
    return sensorPresionDespuesRead();
    }
    
static float controlCeldaCarga(){
    return celdaCargaRead();
    }
