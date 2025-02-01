
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

enum Color {
    OFF,
    RED,
    GREEN,
};

void waitSecond(int nSeconds)
{
    for (int i = 0; i < nSeconds; i++)
    {
        _delay_ms(1000);
    }
}

void setColor(Color color){
    switch (color)
    {
    case OFF: // mettre les deux pin a 0
        PORTA &= ~ (1 << PA0);
        PORTA &= ~ (1 << PA1);
        break;
    case GREEN:
        PORTA &= ~(1 << PA0); // pin 1 a 0
        PORTA |= (1 << PA1); // pin 2 a 1
        break;

    case RED:
        PORTA &= ~ (1 << PA1); // pin 2 a 0
        PORTA |= (1 << PA0);  // pin 1 a 1 
        break;
    default:
        break;
    }
}

void lightOff(){
    setColor(OFF);
}

void lightGreen()
{
    setColor(GREEN);
    waitSecond(1);
}

void lightRed()
{
    setColor(RED);
    waitSecond(1);
}

void lightAmber()
{
    for (int i = 0; i < 50; i++)
    {
        setColor(RED);
        _delay_ms(10);
        setColor(GREEN);
        _delay_ms(10);
    }
}

bool isButtonPressed(){
    return PIND & 0x04;
}

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

void colorLoop(){
    lightGreen();
    lightRed();
}

int main()
{
    DDRA |= (1 << PA0 | 1 << PA1); 
    DDRD &= ~(1 << PD2);

    while (true)
    {
        if (buttonDebounce())
        {
            lightAmber();
            lightGreen();
            lightRed();
        }
        lightOff();
        
    }

    return 0;
}
