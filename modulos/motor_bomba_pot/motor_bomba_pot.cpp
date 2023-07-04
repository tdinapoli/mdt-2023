#include "mbed.h"

// define los pines a utilizar para el potenciometro
// por ahora pongo cualquiera que diga SPI_XXXX en
// https://os.mbed.com/platforms/ST-Nucleo-F429ZI/
// después hay que cambiarlos por alguno q convenga más
#define _CS_ SPI1_CS // PA_15
#define _MOSI_ SPI1_MOSI // PB_5
#define _MISO_ SPI1_MISO // PB_4
#define _SCLK_ SPI1_SCK // PA_4
#define _INCREMENTO_CHICO_ 1
#define _INCREMENTO_GRANDE_ 10

SPI spi(_MOSI_, _MISO_, _SCLK_);
DigitalOut cs(_CS_);

Serial motor_bomba_pot_pc_serial(USBTX, USBRX);

int pwm_level = 0; // max 255

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
    motor_bomba_pot_pc_serial.printf("WHOAMI register = 0x%X\n", whoami);
 
    // Deselect the device
    cs = 1;
}

void potBombaSubirPocoDutyCycle(){
    cs = 0;
    spi.write(0x11); // mado command byte 00 01 00 11
                     // pagina 18 datasheet
    int nuevo_pwm = pwm_level + _INCREMENTO_CHICO_
    if (chequearRestricciones(nuevo_pwm)){
        spi.write(nuevo_pwm);
        pwm_level = nuevo_pwm;
    }
    else {
        motor_bomba_pot_pc_serial.printf("El potenciómetro ya está al máximo");
    }
    cs = 1;
}

void potBombaBajarPocoDutyCycle(){
    cs = 0;
    spi.write(0x11); // mado command byte 00 01 00 11
                     // pagina 18 datasheet
    int nuevo_pwm = pwm_level - _INCREMENTO_CHICO_
    if (chequearRestricciones(nuevo_pwm)){
        spi.write(nuevo_pwm);
        pwm_level = nuevo_pwm;
    }
    else {
        motor_bomba_pot_pc_serial.printf("El potenciómetro ya está al mínimo");
    }
    cs = 1;
}

void potBombaSubirMuchoDutyCycle(){
    cs = 0;
    spi.write(0x11); // mado command byte 00 01 00 11
                     // pagina 18 datasheet
    int nuevo_pwm = pwm_level + _INCREMENTO_GRANDE_;
    if (chequearRestricciones(nuevo_pwm)){
        spi.write(nuevo_pwm);
        pwm_level = nuevo_pwm;
    }
    else {
        motor_bomba_pot_pc_serial.printf("El potenciómetro ya está al máximo");
    }
    cs = 1;
}

void potBombaBajarMuchoDutyCycle(){
    cs = 0;
    spi.write(0x11); // mado command byte 00 01 00 11
                     // pagina 18 datasheet
    int nuevo_pwm = pwm_level - _INCREMENTO_GRANDE_;
    if (chequearRestricciones(nuevo_pwm)){
        spi.write(pwm_level - _INCREMENTO_GRANDE_);
        pwm_level = pwm_level - _INCREMENTO_GRANDE_;
    }
    else {
        motor_bomba_pot_pc_serial.printf("El potenciómetro ya está al mínimo");
    }
    cs = 1;
}

static bool chequearRestricciones(int level){
    return (level < 255 && level > 0)
}
