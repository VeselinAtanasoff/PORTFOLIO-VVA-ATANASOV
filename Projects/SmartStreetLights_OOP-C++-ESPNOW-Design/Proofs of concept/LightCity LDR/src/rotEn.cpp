#include "rotEn.h"

int iRotEn :: rotEn(){
    int aState = digitalRead(ROT_EN_A);

    if (aState != aLastState){     
        if (digitalRead(ROT_EN_B) != aState) { 
            counter ++;
        }
        else {
            counter --;
        }
        if(counter > 100){
            counter = 100;
        }
        else if(counter < 0){
            counter = 0;
        }
        aLastState = aState;
        return counter;
    } 
    
    aLastState = aState;
    return -1;
}