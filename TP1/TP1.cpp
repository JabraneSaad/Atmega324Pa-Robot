
/*
 * Description: 
 L'exercice consiste encore à allumer la DEL. 
 Toutefois, les changements seront commandés par l'utilisation du bouton-poussoir Interrupt du circuit. 
 Ainsi, chaque fois que l'utilisateur appuie sur le bouton (avec la souris...), la DEL tourne à la couleur 
 de votre choix et demeure dans cette couleur tant que le bouton n'est pas relâché. 
 Lorsque le bouton est finalement relâché, la DEL s'éteint.
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint8_t RED = PA1;
const uint8_t GREEN = PA2;
const uint8_t OFF = PA0;


void waitSecond(int nSeconds)
{
    int wait = 5 * nSeconds;
    for (int i = 0; i < wait; i++)
    {
        _delay_ms(200);
    }
}

void ledOff(){
    PORTA = OFF;
}

void ledGreen()
{
    PORTA = GREEN;
    waitSecond(1);
}

void ledRed()
{
    PORTA = RED;
    waitSecond(10);
}

void ledAmbre()
{
    for (int i = 0; i < 50; i++)
    {
        PORTA = RED;
        _delay_ms(10);
        PORTA = GREEN;
        _delay_ms(10);
    }
}

bool checkButtonState(){
    return PIND & 0x04;
}

bool validateButtonPress(){
    if (checkButtonState()){
        _delay_ms(10);
        if (checkButtonState())
        {
            return true;
        }
        else {
            return false;
        }
    }
    else{
        return false;
    }
}


void colorLoop(){
    ledGreen();
    ledRed();
    ledAmbre();
}

int main()
{
    DDRA = 0xFF;
    DDRD = 0x00;
    while (true)
    {
        while (validateButtonPress())
        {
            ledRed();
            ledGreen();
            ledAmbre();

        }
        PORTA = OFF;
    }

    return 0;
}
