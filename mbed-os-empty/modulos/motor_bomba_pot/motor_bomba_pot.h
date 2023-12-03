#ifndef _MOTOR_BOMBA_POT_H_
#define _MOTOR_BOMBA_POT_H_

void motorBombaPotInit();
void potBombaSubirPocoDutyCycle();
void potBombaBajarPocoDutyCycle();
void potBombaSubirMuchoDutyCycle();
void potBombaBajarMuchoDutyCycle();
float readPotBombaDutyCycle();
int pctToDuty(float pct);
void setPWM(float pwm);
void setPotResistance(int level);

#endif //_MOTOR_BOMBA_POT_H_
