#include "mbed.h"
#include "motor_bomba_pot.h"

// define los pines a utilizar para el potenciometro
// por ahora pongo cualquiera que diga SPI_XXXX en
// https://os.mbed.com/platforms/ST-Nucleo-F429ZI/
// después hay que cambiarlos por alguno q convenga más
#define _CS_ PA_4 // PA_4 SPI1_CS
#define _MOSI_ PB_5 // PB_5 SPI1_MOSI
#define _MISO_ PB_4 // PB_4 SPI1_MISO
#define _SCLK_ PB_3 // PB_3 SPI1_SCK
#define _INCREMENTO_CHICO_ 1
#define _INCREMENTO_GRANDE_ 10

SPI spi(_MOSI_, _MISO_, _SCLK_);
DigitalOut cs(_CS_);

Serial motor_bomba_pot_pc_serial(USBTX, USBRX);

int pwm_level = 255; // max 255
static bool chequearRestricciones(int);

void motorBombaPotInit(){
    // Chip must be deselected
    cs = 1;

    // Setup the spi for 8 bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
    spi.format(8,3);
    spi.frequency(1000000); // obs: en el manual dice max 10MHz
 
    // Select the device by seting chip select low
    cs = 0;
 
    // Send 0x8f, the command to read the WHOAMI register
    spi.write(0x8F);
 
    // Send a dummy byte to receive the contents of the WHOAMI register
    int whoami = spi.write(0x00);
    // motor_bomba_pot_pc_serial.printf("WHOAMI register = 0x%X\n", whoami);

    // inicializa el potenciómetro en el maximo 
    setPotResistance(pwm_level);
 
    // Deselect the device
    cs = 1;
}

int pctToDuty(float pct){
    int dutyCycle;
    if (0.0 <= pct && pct <= 100.0){
        dutyCycle = (int) (pct*255/100);
        return dutyCycle;
    } else{ 
        motor_bomba_pot_pc_serial.printf("El porcentaje de duty cycle debe esar entre 0 y 100.\n");
        return -1;
    }
}

void setPWM(float pwm){
    cs = 0;
    spi.write(0x11);
    int newDutyCycle = pctToDuty(pwm);
    if (chequearRestricciones(newDutyCycle)){
        spi.write(newDutyCycle);
        pwm_level = newDutyCycle;
        motor_bomba_pot_pc_serial.printf("Duty Cycle: %.2f \n", readPotBombaDutyCycle());
    } else {
        motor_bomba_pot_pc_serial.printf("Valor del potenciometro para la bomba fuera de rango.\n");
    }
}

void potBombaBajarPocoDutyCycle(){
    cs = 0;
    spi.write(0x11); // mado command byte 00 01 00 11
                     // pagina 18 datasheet
    int nuevo_pwm = pwm_level + _INCREMENTO_CHICO_;
    if (chequearRestricciones(nuevo_pwm)){
        spi.write(nuevo_pwm);
        pwm_level = nuevo_pwm;
        motor_bomba_pot_pc_serial.printf("Duty Cycle: %.2f \n", readPotBombaDutyCycle());
    }
    else {
        motor_bomba_pot_pc_serial.printf("El potenciómetro ya está al mínimo\n");
    }
    cs = 1;
}


void potBombaSubirPocoDutyCycle(){
    cs = 0;
    spi.write(0x11); // mado command byte 00 01 00 11
                     // pagina 18 datasheet
    int nuevo_pwm = pwm_level - _INCREMENTO_CHICO_;
    if (chequearRestricciones(nuevo_pwm)){
        spi.write(nuevo_pwm);
        pwm_level = nuevo_pwm;
        motor_bomba_pot_pc_serial.printf("Duty Cycle: %.2f \n", readPotBombaDutyCycle());
    }
    else {
        motor_bomba_pot_pc_serial.printf("El potenciómetro ya está al máximo\n");
    }
    cs = 1;
}

void potBombaBajarMuchoDutyCycle(){
    cs = 0;
    spi.write(0x11); // mado command byte 00 01 00 11
                     // pagina 18 datasheet
    int nuevo_pwm = pwm_level + _INCREMENTO_GRANDE_;
    if (chequearRestricciones(nuevo_pwm)){
        spi.write(nuevo_pwm);
        pwm_level = nuevo_pwm;
        motor_bomba_pot_pc_serial.printf("Duty Cycle: %.2f \n", readPotBombaDutyCycle());
    }
    else {
        motor_bomba_pot_pc_serial.printf("El potenciómetro ya está al mínimo\n");
    }
    cs = 1;
}

void potBombaSubirMuchoDutyCycle(){
    cs = 0;
    spi.write(0x11); // mado command byte 00 01 00 11
                     // pagina 18 datasheet
    int nuevo_pwm = pwm_level - _INCREMENTO_GRANDE_;
    if (chequearRestricciones(nuevo_pwm)){
        spi.write(nuevo_pwm);
        pwm_level = nuevo_pwm;
        motor_bomba_pot_pc_serial.printf("Duty Cycle: %.2f \n", readPotBombaDutyCycle());
    }
    else {
        motor_bomba_pot_pc_serial.printf("El potenciómetro ya está al máximo\n");
    }
    cs = 1;
}



void setPotResistance(int level){
    cs = 0;
    spi.write(0x11);
    spi.write(level);
    cs = 1;
}

float readPotBombaDutyCycle(){
    float percent = 1 - (float)pwm_level/255; // supongo que mientras más alto el valor del pote menor el duty cycle
    return percent;
}



static bool chequearRestricciones(int level){
    return (level < 255 && level > 0);
}

