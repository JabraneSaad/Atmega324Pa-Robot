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

const uint32_t ONE_SECOND_US = 1'000'000;

void initRobotPorts()
{
    DDRB |= (1 << PB0 | 1 << PB2);
    // DDRD &= ~(1 << PD1);
}

void useDelayUs(uint32_t nUs)
{
    _delay_us(nUs);
    // for (uint32_t i = 0; i < nUs; i++){
    //     _delay_us(1);
    // }
}
void turnOff(uint32_t nUs)
{
    PORTB &= ~((1 << PB0) | (1 << PB2));
    useDelayUs(nUs);
}

void turnOn(uint32_t nUs)
{
    // PORTB &= ~(1 << PB2);
    PORTB |= (1 << PB0);
    useDelayUs(nUs);
}

void turnWheel(uint8_t PercentageAB, uint16_t frequency, uint16_t durationSeconds)
{
    uint16_t totalTime = ONE_SECOND_US / frequency;
    uint16_t timeOn = PercentageAB * totalTime / 100;
    uint16_t timeOff = totalTime - timeOn;
    uint16_t nCycles = durationSeconds * frequency;

    for (uint16_t i = 0; i < nCycles; i++)
    {
        turnOn(timeOn);
        turnOff(timeOff);
    }
}

int main()
{
    initRobotPorts();
    while (true)
    {
        turnWheel(25, 60, 10);
    }
}