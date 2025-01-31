/*
Travail : TP2 PB1
Section # : 4
Équipe # : EQUIPE_103
Correcteur : Meriam Ben Rabia

Identification du materiel : la cathode de la LED est connecté à la broche A0 et l'anode à la broche A2.

Description du programe : On allume une LED en vert a chaque 3 cliques d'un boutton

Tableau d'etats :
+---------------+--------+------------+-------+
| CURRENT STATE | BUTTON | NEXT STATE | LED   |
+---------------+--------+------------+-------+
|     INIT      |   0    |    INIT    |  OFF  |
+---------------+--------+------------+-------+
|     INIT      |   1    |  PRESSED1  |  OFF  |
+---------------+--------+------------+-------+
|   PRESSED1    |   0    | RELEASED1  |  OFF  |
+---------------+--------+------------+-------+
|   PRESSED1    |   1    |  PRESSED1  |  OFF  |
+---------------+--------+------------+-------+
|   RELEASED1   |   0    | RELEASED1  |  OFF  |
+---------------+--------+------------+-------+
|   RELEASED1   |   1    |  PRESSED2  |  OFF  |
+---------------+--------+------------+-------+
|   PRESSED2    |   0    | RELEASED2  |  OFF  |
+---------------+--------+------------+-------+
|   PRESSED2    |   1    |  PRESSED2  |  OFF  |
+---------------+--------+------------+-------+
|   RELEASED2   |   0    | RELEASED2  |  OFF  |
+---------------+--------+------------+-------+
|   RELEASED2   |   1    |  PRESSED3  |  OFF  |
+---------------+--------+------------+-------+
|   PRESSED3    |   0    | RELEASED3  |  OFF  |
+---------------+--------+------------+-------+
|   PRESSED3    |   1    |  PRESSED3  |  OFF  |
+---------------+--------+------------+-------+
|   RELEASED3   |   X    |    INIT    | GREEN |
+---------------+--------+------------+-------+
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint16_t TWO_SECONDS_MS = 2000;
const uint8_t DEBOUNCE_DELAY_MS = 10;

enum class State
{
    INIT,
    PRESSED1,
    RELEASED1,
    PRESSED2,
    RELEASED2,
    PRESSED3,
    RELEASED3,
};

void lightOff()
{
    PORTA &= ~((1 << PA0) | (1 << PA1));
}

void lightGreen()
{
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
}

void lightRed()
{
    PORTA &= ~(1 << PA1);
    PORTA |= (1 << PA0);
}

bool isButtonPressed()
{
    if (PIND & (1 << PD2))
    {
        _delay_ms(DEBOUNCE_DELAY_MS);
        return (PIND & (1 << PD2));
    }
    return false;
}

void setState(State &state)
{
    switch (state)
    {
    case State::INIT:
        lightOff();
        if (isButtonPressed())
        {
            state = State::PRESSED1;
        }
        break;
    case State::PRESSED1:
        if (!isButtonPressed())
        {
            state = State::RELEASED1;
        }
        break;
    case State::RELEASED1:
        if (isButtonPressed())
        {
            state = State::PRESSED2;
        }
        break;
    case State::PRESSED2:
        if (!isButtonPressed())
        {
            state = State::RELEASED2;
        }
        break;
    case State::RELEASED2:
        if (isButtonPressed())
        {
            state = State::PRESSED3;
        }
        break;
    case State::PRESSED3:
        if (!isButtonPressed())
        {
            state = State::RELEASED3;
        }
        break;
    case State::RELEASED3:
        lightGreen();
        _delay_ms(TWO_SECONDS_MS);
        state = State::INIT;
        break;
    }
}

void setLED(State currentState)
{
    switch (currentState)
    {
    case State::RELEASED3:
        lightGreen();
        _delay_ms(TWO_SECONDS_MS);
        break;

    default:
        lightOff();
        break;
    }
}

void initRobotPorts()
{
    DDRA |= (1 << PA0 | 1 << PA1);
    DDRD &= ~(1 << PD1);
}

int main()
{
    State state = State::INIT;
    initRobotPorts();
    while (true)
    {
        setState(state);
        setLED(state);
    }
}