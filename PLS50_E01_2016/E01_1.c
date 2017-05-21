//PLS50
//Homework E01 - Question 1
//Author: Iakovos Klimenof
//Description: A simple calculator

#include <stdio.h>

int main(void) {

    //Variables that will be used
    char operation;
    float first_number, second_number, result;

    printf("Dwse arithmo praksi arithmo\n");

    scanf("%f %c %f", &first_number, &operation, &second_number);

    //Check if the operator entered correct operation
    if(operation != '+' && operation != '-' && operation != '*' && operation != '/' ){
        printf("Parakalw eisagete swsti praksi");
        return 0;
    }
    else{
        switch(operation){
            case '+':
            result = first_number + second_number;
            break;

            case '-':
            result = first_number - second_number;
            break;

            case '*':
            result = first_number * second_number;
            break;

            case '/':
            if(second_number == 0){
                printf("Parakalw eisagete diaireti megalytero toy 0");
                return 0;
            }
            else{
            result = first_number / second_number;
            break;
            }
        }
    }
    printf("apotelesma = %.2f", result);
    return 0;
}



