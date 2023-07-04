#ifndef _VALVULA_H_
#define _VALVULA_H_

typedef enum{
    ABIERTA=0,
    CERRADA
    } estadoValvula_t;
    
void valvulaInit();
void valvulaAbrir();
void valvulaCerrar();
estadoValvula_t estadoValvulaRead();

#endif //_VALVULA_H_
