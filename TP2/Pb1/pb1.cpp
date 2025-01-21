// Travail : TP2
// Section # : 4
// Équipe # : EQUIPE_NO
// Correcteur : CORRECTEUR

/*
Description du programme : 
*/

// TODO : faire la table des etats

// TODO: inclure le tableau des etats

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

// TODO : ajouter MS pour deux seconce continuite
const uint16_t DEUX_SECONDES = 2000;
const uint8_t DELAY_DEBOUNCE_MS = 10;

enum class State{
    INIT,
    CLICKED1,
    RELEASED1,
    CLICKED2,
    RELEASED2,
    CLICKED3,
    RELEASED3,
};

void setState(State &state){
    switch(state)
    {
    case State::INIT:
        if (buttonDebounce()) {
            state = State::CLICKED1;
        }
        break;
    case State::CLICKED1:
        if (!isButtonPressed()) {
            state = State::RELEASED1;
        }
        break;
    case State::RELEASED1:
        if (buttonDebounce()) {
            state = State::CLICKED2;
        }
        break;
    case State::CLICKED2:
        if (!isButtonPressed()) {
            state = State::RELEASED2;
        }
        break;
    case State::RELEASED2:
        if (buttonDebounce()) {
            state = State::CLICKED3;
        }
        break;
    case State::CLICKED3:
        if (!isButtonPressed()) {
            state = State::RELEASED3;
        }
        break;
    case State::RELEASED3:
        lightGreen();
        _delay_ms(DEUX_SECONDES);
        state = State::INIT;
        break;
    // TODO: enlever le default car inutile??
    default:
        break;
    }
}

void lightOff(){
    PORTA &= ~ ((1 << PA0) | (1 << PA1));
}

void lightGreen()
{
    PORTA &= ~(1 << PA0); 
    PORTA |= (1 << PA1);
}

void lightRed()
{
    PORTA &= ~ (1 << PA1);
    PORTA |= (1 << PA0);
}

bool isButtonPressed(){
    return PIND & 0x04;
}

// TODO : demander a la correctrice : PIND & PD1 au lieu de la fonction limiter le code
bool buttonDebounce(){
    if (isButtonPressed()){
        _delay_ms(10);
        if (isButtonPressed()) {
            return true;
        }
        else {   
            return false;
        }
    }
    else {    
        return false;
    }
}

void initRobotPorts(){
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
    }
}