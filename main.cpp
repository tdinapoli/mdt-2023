
#include "sistema.h"
#include "sistema/sistema.h"

// main() runs in its own thread in the OS


int main()
{
    sistemaInit();
    while (true) {
        sistemaUpdate();
    }
}

