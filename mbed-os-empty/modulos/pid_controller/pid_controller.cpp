#include "PID.h"
#include "presion_antes.h"
#include "presion_despues.h"
#include "motor_bomba_pot.h"

#define PID_RATE 100
#define KC 1
#define TI 1
#define TD 1

#define MIN_TMP 1
#define MAX_TMP 100
#define MIN_DC 0
#define MAX_DC 100
#define OPTIMAL_TMP 10
#define BIAS 0

PID pidController(KC, TI, TD, PID_RATE);

static float presionAntes;
static float presionDespues;
static float TMP;
static float controllerOutput;

void pidControllerInit(){
    pidController.setInputLimits(MIN_TMP, MAX_TMP);
    pidController.setOutputLimits(MIN_DC, MAX_DC);
    pidController.setSetPoint(OPTIMAL_TMP);
    pidController.setMode(1); //esto setea el pid en modo automatico. Todavía no se bien q significa
}

void pidControllerUpdate(){
    presionAntes = sensorPresionAntesRead();
    presionDespues = sensorPresionDespuesRead();
    TMP = (presionDespues + presionAntes)/2;
    pidController.setProcessValue(TMP);
    controllerOutput = pidController.compute();
    setPWM(controllerOutput);
}


