#ifndef _MOTOR_BOMBA_H_
#define _MOTOR_BOMBA_H_

void motorBombaInit();
void setBombaDutyCycle(float dutyCycle);
float readBombaDutyCycle();
void subirMuchoBombaDutyCycle();
void bajarMuchoBombaDutyCycle();
void subirPocoBombaDutyCycle();
void bajarPocoBombaDutyCycle();

#endif //_MOTOR_BOMBA_H_
