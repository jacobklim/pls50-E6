//PLS50
//Homework E01 - Question 2
//Author: Iakovos Klimenof
//Description: Geometric Calculations - Find the perimeter


#include <stdio.h>
#include <math.h>

#define PI 3.14

//Function prototypes
float square(float plevra);
float rectangular(float mikos, float platos);
float triangle(float mikos1, float mikos2);
float circle(float aktina);


int main(void){

    //Variable definition
    char choice;
    char loop = 1;
    float plevra_tetragwnou, mikos, platos, mikos1, mikos2, aktina;

    while(loop){
        //Print the initial message for the operator
        printf("Ypologismos perimetrou gewmetrikvn sximatwn\n");
        printf("Parakalw eisagete tin epilogi sas\n");
        printf("0. Eksodos\n");
        printf("1. Tetragwno\n");
        printf("2. Parallilogrammo\n");
        printf("3. Orthogwnio trigwno\n");
        printf("4. Kyklos\n");

        //Scan the operator's choice
        scanf(" %c", &choice);

        //Determine the right function and result
        if(choice == '0'){
            loop = 0;//Exits the loop
        }
        else if(choice == '1'){
            printf("Eisagete to mikos tis plevras\n");
            scanf("%f", &plevra_tetragwnou);
            printf("H perimetros tou tetragwnou einai: %.2f\n\n", square(plevra_tetragwnou));
        }
        else if(choice == '2'){
            printf("Eisagete mikos kai platos\n");
            scanf("%f %f", &mikos, &platos);
            printf("H perimetros toy parallilogramou einai: %.2f\n\n", rectangular(mikos, platos));
        }
        else if(choice == '3'){
            printf("Eisagete mikos twn kathetwn plevrwn\n");
            scanf("%f %f", &mikos1, &mikos2);
            printf("H perimetros tou trigwnou einai: %.2f\n\n", triangle(mikos1, mikos2));
        }
        else if(choice == '4'){
            printf("Eisagete tin aktina toy kyklou\n");
            scanf("%f", &aktina);
            printf("H perimetros tou kyklou einai: %.2f\n\n", circle(aktina));
        }
        else{
            printf("Parakalw eisagete swsti epilogi (0-4)\n");
        }
    }
    return 0;
}

/*Helper functions for calculating the perimeters*/

//Function that calculates the perimeter of square
float square(float plevra){
    float result;
    result = plevra * 4;
    return result;
}
//Function that calculates the perimeter of rectangular
float rectangular(float mikos, float platos){
    float result;
    result = 2*mikos + 2*platos;
    return result;
}
//Function that calculates the perimeter of triangle
float triangle(float mikos1, float mikos2){
    float result, ypoteinousa;
    ypoteinousa = sqrt(pow(mikos1, 2) + pow(mikos2, 2));
    result = mikos1 + mikos2 + ypoteinousa;
    return result;
}
//Function that calculates the perimeter of circle
float circle(float aktina){
    float result;
    result = 2 * PI * aktina;
    return result;
}
