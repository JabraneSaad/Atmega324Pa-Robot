/*
Travail : TP3
Section # : 4
Équipe # : EQUIPE_103
Correcteur : Travail non corrige

Identification du materiel : la cathode de la LED est connecté à la broche A0 et l'anode à la broche A2.

Description du programme :
*/

#define F_CPU 8000000UL

// le delay_ms a une incertitude qui s accumule avec les appels
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <util/delay.h>

const uint16_t nCycles = 3000;

void initRobotPorts()
{
    DDRA |= (1 << PA0 | 1 << PA1);
    DDRD &= ~(1 << PD1);
}

void useDelayUs(uint32_t nUs)
{
    _delay_us(nUs);

    // for (uint32_t i = 0; i < nUs; i++){
    //     _delay_us(1);
    // }
}
void lightOff(uint32_t nUs)
{
    PORTA &= ~((1 << PA0) | (1 << PA1));
    useDelayUs(nUs);
}

void lightGreen(uint32_t nUs)
{
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
    useDelayUs(nUs);
}

void lightRed(uint32_t nUs)
{
    PORTA &= ~(1 << PA1);
    PORTA |= (1 << PA0);
    useDelayUs(nUs);
}

void toneDownLight()
{

    uint16_t timeOff = 0;
    uint16_t timeOn = 1000;

    for (uint16_t i = 0; i < nCycles; i++)
    {

        lightRed(timeOn);
        lightOff(timeOff);

        if (i % 3 == 0)
        {
            timeOn--;
            timeOff++;
        }
    }
}

int main()
{
    initRobotPorts();
    while (true)
    {
        toneDownLight();
    }
}