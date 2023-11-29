#ifndef _VALVULA_H_
#define _VALVULA_H_

typedef enum{
    OPEN=0,
    CLOSED
} valveState_t;

typedef enum{
    one=0,
    two,
    three,
    four
} bridgeState_t;

//    one
//    motor_pin_1 = 1;
//    motor_pin_2 = 0;
//    motor_pin_3 = 1;
//    motor_pin_4 = 0;

//    two
//    motor_pin_1 = 0;
//    motor_pin_2 = 1;
//    motor_pin_3 = 1;
//    motor_pin_4 = 0;

//    three
//    motor_pin_1 = 0;
//    motor_pin_2 = 1;
//    motor_pin_3 = 0;
//    motor_pin_4 = 1;

//    four
//    motor_pin_1 = 1;
//    motor_pin_2 = 0;
//    motor_pin_3 = 0;
//    motor_pin_4 = 1;
//    

class StepperMotor {
public:
    StepperMotor(valveState_t valveState, bridgeState_t bridgeState = one);

    void open();
    void close();
    void oneStepRight();
    void oneStepLeft();

    valveState_t valveState;

private:
    bridgeState_t bridgeState;
    void stepOneTwo();
    void stepTwoThree();
    void stepThreeFour();
    void stepFourOne();
    void stepOneFour();
    void stepTwoOne();
    void stepThreeTwo();
    void stepFourThree();
};

#endif //_VALVULA_H_