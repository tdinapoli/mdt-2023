#include "mbed.h"
#include "pc_serial_com.h"
//#include "valvula_stepper.h"
#include "arm_book_lib.h"
#include "motor_bomba_pot.h"
#include "presion_antes.h"
#include "presion_despues.h"
#include "alarmas.h"
#include "celda_carga.h"
#include "sistema.h"
#include "valvula.h"

extern StepperMotor valveMotor;

static void comComandosDisponibles();

static Serial usbPort_pc_serial_com(USBTX, USBRX);
static void comSetBombaDutyCycle();
static void comEstadoComponentes();

void pcSerialComInit(){
    comComandosDisponibles(); //muestra comandos disponibles
    }

char pcSerialComCharRead(){
    char caracterRecibido = '\0';
    if( usbPort_pc_serial_com.readable() ){
        caracterRecibido = usbPort_pc_serial_com.getc();
        }
    return caracterRecibido;
    }

void pcSerialComUpdate(){
    char caracterRecibido = pcSerialComCharRead();
    
    //se fija si le mandaste algo a la consola
    if( caracterRecibido != '\0' ) {
        //se fija que es lo que le mandaste y actua en consecuencia
        switch( caracterRecibido ){
            case 'c': comComandosDisponibles(); break; //muestra comandos disponibles
            case 'e': comEstadoComponentes(); break; //muestra el estado de los componentes
            case 'v': valveMotor.close(); break; //cierra la valvula
            case 'V': valveMotor.open(); break; //abre la valvula
            case 'b': comSetBombaDutyCycle(); break; //te permite setear el duty cycle de la bomba
            case 'r': valveMotor.oneStepRight(); break;
            case 'l': valveMotor.oneStepLeft(); break;
            default: usbPort_pc_serial_com.printf("comando no reconocido\n"); break; //si se escribe algo distinto a los comandos anteriores, contesta q no entiende
            }
        }
    }

static void comSetBombaDutyCycle(){
    char caracterRecibido = pcSerialComCharRead();
    usbPort_pc_serial_com.printf("Para subir 0.01 apreta u, para subir 0.1 apreta U\n");
    usbPort_pc_serial_com.printf("Para bajar 0.01 apreta d, para subir 0.1 apreta D\n");
    usbPort_pc_serial_com.printf("Cuando termines settear el Duty Cycle apreta q\n");
    
    while(caracterRecibido != '\n' ){
        caracterRecibido = pcSerialComCharRead();
        delay(50);
        
        if (caracterRecibido == 'u'){
            potBombaSubirPocoDutyCycle();
            }
        else if (caracterRecibido == 'U'){
            potBombaSubirMuchoDutyCycle();
            }
        else if (caracterRecibido == 'd') {
            potBombaBajarPocoDutyCycle();
            }
        else if (caracterRecibido == 'D') {
            potBombaBajarMuchoDutyCycle();
            }
        else if (caracterRecibido == 'q') {
            usbPort_pc_serial_com.printf("Volviendo al menu principal... \n");
            break;
            }
        else if (caracterRecibido == '\0' || caracterRecibido == '\n'){
            }
        else {
            usbPort_pc_serial_com.printf("comando no reconocido\n");
            }
        }
    }

static void comComandosDisponibles(){
    usbPort_pc_serial_com.printf("Comandos disponibles:\n");
    usbPort_pc_serial_com.printf("c: lista de comandos disponibles\n");
    usbPort_pc_serial_com.printf("e: mostrar estado de los componentes\n");
    usbPort_pc_serial_com.printf("v: cerrar valvula\n");
    usbPort_pc_serial_com.printf("V: abrir valvula\n");
    usbPort_pc_serial_com.printf("b: settear la velocidad de la bomba\n");
    usbPort_pc_serial_com.printf("r: mover el motor de la valvula un paso a la derecha");
    usbPort_pc_serial_com.printf("l: mover el motor de la valvula un paso a la izquierda");
    }

static void comEstadoComponentes(){
    float duty_cycle_v = readPotBombaDutyCycle(); //velocidad con la que funciona la bomba
    float presion_antes_v = sensorPresionAntesRead(); //Lee el input analógico del sensor de presion
    float presion_despues_v = sensorPresionDespuesRead(); //Lee el input analógico del sensor de presion
    //estadoValvulaStepper_t estado_v = estadoValvulaStepperRead(); //Lee si la valvula esta abierta o cerrada
    valveState_t state_v = valveMotor.valveState;
    bool alarma_roja_v = alarmasEstadoRojo();
    bool alarma_verde_v = alarmasEstadoVerde();
    bool alarma_azul_v = alarmasEstadoAzul();
    float peso_celda_v = celdaCargaRead();
    usbPort_pc_serial_com.printf("nomenclatura: 0=APAGADO/ABIERTA, 1=PRENDIDO/CERRADA\n");
    usbPort_pc_serial_com.printf("El motor de la bomba esta al %f \n", duty_cycle_v);
    usbPort_pc_serial_com.printf("La presion antes de la bomba es de %f \n", presion_antes_v);
    usbPort_pc_serial_com.printf("La presion despues de la bomba es de %f \n", presion_despues_v);
    usbPort_pc_serial_com.printf("Estado de la valvula %d \n", (int)state_v);
    usbPort_pc_serial_com.printf("Alarma roja %d \n", alarma_roja_v);
    usbPort_pc_serial_com.printf("Alarma verde %d \n", alarma_verde_v);
    usbPort_pc_serial_com.printf("Alarma azul %d \n", alarma_azul_v);
    usbPort_pc_serial_com.printf("El peso que mide la celda es %f \n", peso_celda_v);
    }


