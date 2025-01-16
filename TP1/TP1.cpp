
/*
 * Jabrane Saad
 * Karimi Taha
 * Description: Ce programme fait passer le LED de la couleur verte (1s) à la couleur rouge (1s) à la couleur ambre (1s)
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

// TODO : utilsier des uint
// TODO : utiliser des constantes
// TODO : enlever les chiffres magiques
// TODO : enlever le bitshift

const uint8_t RED = 0b00000001;
const uint8_t GREEN = RED << 1;

void waitSecond(int nSeconds)
{
    int wait = 5 * nSeconds;
    for (int i = 0; i < wait; i++)
    {
        _delay_ms(200);
    }
}

void green()
{
    PORTA = GREEN;
    waitSecond(1);
}

void red()
{
    PORTA = RED;
    waitSecond(1);
}

void ambre()
{
    for (int i = 0; i < 50; i++)
    {
        // TODO : modifier la fonction green() pour pouvoir l'utiliser ici (parametres)
        PORTA = GREEN;
        _delay_ms(5);
        PORTA = RED;
        _delay_ms(15);
    }
}

int main()
{
    DDRA = 0xFF;
    while (true)
    {
        green();
        red();
        ambre();
    }

    return 0;
}
