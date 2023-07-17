#ifndef _VALVULA_STEPPER_H_
#define _VALVULA_STEPPER_H_

typedef enum{
    ABIERTA=0,
    CERRADA
    } estadoValvulaStepper_t;

void fourStepsRight();
void fourStepsLeft();
void valvulaStepperInit();
void valvulaStepperAbrir();
void valvulaStepperCerrar();
estadoValvulaStepper_t estadoValvulaStepperRead();


#endif //_VALVULA_STEPPER_H_
