//PLS50
//Homework E01 - Question 3
//Author: Iakovos Klimenof
//Description:Binary representation of decimal number

#include <stdio.h>


int main(void){

    //Variable definition
    int number;
    char bit;
    const int STABLE = 2;

    printf("Eisagete thetiko arithmo\n");

    scanf("%d", &number);

    //Checks if the number is negative, if it is, repeatedly asks for a positive number
    while(number <= 0){
        printf("Parakalw eisagete thetiko arithmo\n");
        scanf("%d", &number);
    }

    //If the number is positive, repeatedly divide the number by 2 and print the
    //result which is the bit from the binary number representation
    while(number > 0){
        bit = ((number % STABLE) == 1) ? '1':'0';
        putchar(bit);
        number /= STABLE;
    }
    return 0;

}
