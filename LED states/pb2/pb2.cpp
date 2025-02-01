/*
Travail : TP2 PB2
Section # : 4
Équipe # : EQUIPE_103
Correcteur : Meriam Ben Rabia

Identification du materiel : la cathode de la LED est connecté à la broche A0 et l'anode à la broche A2.

Description du programme :
Quand le bouton est pressé, la DEL affiche la couleur ambre.
Lorsque le bouton est relâché, la DEL devient verte.
Quand le bouton est pressé de nouveau, la DEL redevient rouge.
Quand le bouton est relâché, la DEL s’éteint.
Quand le bouton est encore pressé, la DEL devient verte.
Lorsque le bouton est relâché, la DEL retourne au rouge, prête à recommencer le cycle.

+---------------+--------+------------+-----------+
| CURRENT STATE | BUTTON | NEXT STATE |   LED     |
+---------------+--------+------------+-----------+
|     INIT      |   0    |    INIT    |    RED    |
+---------------+--------+------------+-----------+
|     INIT      |   1    |  PRESSED1  |    RED    |
+---------------+--------+------------+-----------+
|   PRESSED1    |   0    | RELEASED1  |   AMBER   |
+---------------+--------+------------+-----------+
|   PRESSED1    |   1    |  PRESSED1  |   AMBER   |
+---------------+--------+------------+-----------+
|   RELEASED1   |   0    | RELEASED1  |   GREEN   |
+---------------+--------+------------+-----------+
|   RELEASED1   |   1    |  PRESSED2  |   GREEN   |
+---------------+--------+------------+-----------+
|   PRESSED2    |   0    | RELEASED2  |    RED    |
+---------------+--------+------------+-----------+
|   PRESSED2    |   1    |  PRESSED2  |    RED    |
+---------------+--------+------------+-----------+
|   RELEASED2   |   0    | RELEASED2  |    OFF    |
+---------------+--------+------------+-----------+
|   RELEASED2   |   1    |  PRESSED3  |    OFF    |
+---------------+--------+------------+-----------+
|   PRESSED3    |   0    | RELEASED3  |   GREEN   |
+---------------+--------+------------+-----------+
|   PRESSED3    |   1    |  PRESSED3  |   GREEN   |
+---------------+--------+------------+-----------+
|   RELEASED3   |   X    |    INIT    |    RED    |
+---------------+--------+------------+-----------+

*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint16_t TWO_SECONDS_MS = 2000;
const uint8_t DEBOUNCE_DELAY_MS = 10;
const uint8_t AMBER_DELAY_MS = 10;

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

void lightAmber()
{
    lightGreen();
    _delay_ms(AMBER_DELAY_MS);
    lightRed();
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
        state = State::INIT;
        break;
    }
}

void setLED(State currentState)
{
    switch (currentState)
    {
    case State::INIT:
        lightRed();
        break;

    case State::PRESSED1:
        lightAmber();
        break;

    case State::RELEASED1:
        lightGreen();
        break;

    case State::PRESSED2:
        lightRed();
        break;

    case State::RELEASED2:
        lightOff();
        break;

    case State::PRESSED3:
        lightGreen();
        break;

    case State::RELEASED3:
        lightRed();
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