#include <rotEn.h>

int aLastState = LOW;
int counter = 500;

int RotEn ::ReadLightLevel()
{
    int aState = digitalRead(ROT_EN_A);

    if (aState != aLastState)
    {
        if (digitalRead(ROT_EN_B) != aState)
        {
            counter++;
        }
        else
        {
            counter--;
        }
        aLastState = aState;
    }

    aLastState = aState;
    return counter;
}