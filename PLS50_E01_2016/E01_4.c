//PLS50
//Homework E01 - Question 4
//Author: Iakovos Klimenof
//Description: Bus reservation programme

#include <stdio.h>
#include <stdlib.h>

#define MAX_SEATS 53
#define FILENAME "bus.txt"
#define BUS_OK 1
#define BUS_NOT_OK -1
#define SEAT_NOT_EMPTY 1
#define SEAT_EMPTY 0
#define WINDOWS_RESERVED -1
#define OUTPUTFILE  "layout.txt"

//Function prototypes
int check_bus(int seats);
void print_message();
void check_empty_seats(int occupancy[], int seats);
int check_if_seat_empty(int occupancy[], int seat_number);
void reserve_seat_by_number(int seats, int occupancy[]);
void reserve_seat_by_window(int occupancy[], int seats);
void cancel_reservation_by_number(int occupancy[], int seats);
void search_seat_by_number(int occupancy[], int seats);
void print_reserved_seats_by_number(int occupancy[], int seats);
void print_bus_graph(int occupancy[], int seats, char car_plate[]);
void export_bus_graph_to_file(int occupancy[], int seats, char car_plate[]);
int check_if_all_windows_reserved(int occupancy[], int seats);


int main(void){

    //Variable defintion
    FILE *fp;

    char car_plate[8];
    int seats;
    int occupancy[MAX_SEATS] = {0};
    int loop = 1;
    char choice;

    //Open the file that contains info for the bus
    fp = fopen(FILENAME, "r");

    if(fp == NULL){ //Checks if the file is EMPTY
        printf("Cannot open file \n");
        exit(-1);
    }
    else{ //Else it reads file and stores the values
        fscanf(fp, "%s%d", car_plate, &seats);
        }

    fclose(fp);//Close the file

    //Check if the bus is OK (valid number of seats)
    if(check_bus(seats) == -1){
        printf("Numbers of seats is not valid\n");
        exit(-1);
    }

    printf("Car plate: %s\nNumber of seats: %d\n\n", car_plate, seats);

    while(loop){
        //Print the appropriate messages
        print_message();

        //Take the choice
        scanf(" %c", &choice);
        printf("%c\n\n", choice);

        //Check the choices and compute

        if(choice == '0'){
            printf("Programme will be terminated...\n");
            loop = 0;//Exits the loop
        }

        else if(choice == '1'){
            check_empty_seats(occupancy, seats);
        }

        else if(choice == '2'){
            reserve_seat_by_number(seats, occupancy);
        }

        else if(choice == '3'){
            reserve_seat_by_window(occupancy, seats);
        }

        else if(choice == '4'){
            cancel_reservation_by_number(occupancy, seats);
        }

        else if(choice == '5'){
            search_seat_by_number(occupancy, seats);
        }

        else if(choice == '6'){
            print_reserved_seats_by_number(occupancy, seats);
        }

        else if(choice == '7'){
            print_bus_graph(occupancy, seats, car_plate);
        }

        else if(choice == '8'){
            export_bus_graph_to_file(occupancy, seats, car_plate);
        }

        else{
        printf("Please enter valid choice (0-8)\n\n");
        }

    }
    return 0;
}


//Helper functions

//Function that checks if a bus is valid
int check_bus(int seats){
    int seat_rows;

    seat_rows = (seats - 5) % 4;

    if(seat_rows !=0 || seats > MAX_SEATS ){
        return BUS_NOT_OK;
    }
    else{
        return BUS_OK;
    }
}

//function that print the appropriate messages
void print_message(void){
    printf("Reserve and configuration programme for bus\n");
        printf("Please enter your choice:\n");
        printf("1. Print number of empty seats\n");
        printf("2. Reserve seat by number\n");
        printf("3. Reserve seat by window\n");
        printf("4. Cancel a reservation by seat number\n");
        printf("5. Search seat by number\n");
        printf("6. Print reserved seats by number\n");
        printf("7. Print bus graph\n");
        printf("8. Save bus graph\n");
        printf("0. Exit\n");
}
//Function that counts the empty seats and print the message to the screen
void check_empty_seats(int occupancy[], int seats){

    int count = 0;//count the empty seats
    int i;//classic variable for the loops
    int seat_number;

    printf("Empty seats:\n");
    for(i = 0; i < seats; i++){
        if (occupancy[i] == 0){
            count += 1;
            seat_number = i + 1;
            printf("%d, ",seat_number);
        }
    }
    printf("\b\b ");
    printf("\nTotal number of empty seats: %d\n\n", count);
}


//Function that checks if a seat is empty
int check_if_seat_empty(int occupancy[], int seat_number){

    if(occupancy[seat_number-1] == 1){
        return SEAT_NOT_EMPTY;
    }
    else{
        return SEAT_EMPTY;
    }
}

//Function that checks and reserve a seat by number
void reserve_seat_by_number(int seats, int occupancy[]){

    int seat_number;

    printf("Enter seat number\n\n");
    scanf("%d", &seat_number);

    if(seat_number <= seats){
        if(check_if_seat_empty(occupancy, seat_number) == 1){
            printf("Seat already reserved!!\n\n");
        }
        else{
            occupancy[seat_number - 1] = 1;
            printf("Seat with number %d reserved!!\n\n", seat_number);
        }
    }
    else{
        printf("Please enter valid seat number: 1-%d\n\n", seats);
    }
}

//Function that reserves the first seat by window
void reserve_seat_by_window(int occupancy[],int seats){

    int i;//classic variable for the loop
    int last_four = seats -5;//variable that stores the seats except the last 5

    //First let's check if all seats by windows are reserved
    if(check_if_all_windows_reserved(occupancy, seats) == -1){
            printf("All seats by window reserved\n\n");
            }
    else{//if theres is an empty seat by window...
    //First, lest's reserve a seat by window at the normal rows
    for(i = 1; i <= last_four; i++){
        if(i % 4 == 0 || i % 4 == 1){
            if(occupancy[i-1] != 1){
                occupancy[i-1] = 1;
                break;
            }
        }
    }
    //then let's check and reserve the first seat by window after the normal rows
    if(i == last_four + 1 && occupancy[i-1] == 0){
        occupancy[i-1] = 1;
    }//if not, we reserve the last seat by window which is the last seat
    else if(i == last_four + 1 && occupancy[seats-1] == 0 && occupancy[i-1] == 1){
        occupancy[seats-1] = 1;
        i = seats;
    }
    printf("Seat by window reserved! Seat number:%d\n\n", i);
    }

}

//Function that checks if there are free windows
int check_if_all_windows_reserved(int occupancy[], int seats){

    int windows_reserved = 0;//counter the reserved seats by window
    int i;//classic variable for a loop
    int last_four = seats -5;
    int half_windows = (seats - 5) / 4;//variable for storing the half seats by window
    int total_windows = half_windows * 2 + 2;//variable that stores the
                                            //number of total seats by window
    //First, lest's check a seat by window at the normal rows
    for(i = 1; i <= last_four; i++){
        if(i % 4 == 0 || i % 4 == 1){
            if(occupancy[i-1] == 1){
                windows_reserved += 1;
            }
        }
    }
    //Then, lets' check the window after the normal rows
    if(i == last_four + 1 && occupancy[i-1] == 1 ){
        windows_reserved += 1;
    }
    //Last, lets check the last seat, which is the last window
    if(occupancy[seats-1] == 1){
        windows_reserved += 1;
    }
    //if all seats by window are reserved then we return WINDOWS_RESERVED
    if(windows_reserved == total_windows){
        return WINDOWS_RESERVED;
    }
    return 0;
}

//Function that cancels a reservation by seat number
void cancel_reservation_by_number(int occupancy[], int seats){

    int seat_number_to_cancel;

    printf("Enter the number of seat you want to cancel\n");
    scanf("%d", &seat_number_to_cancel);

    //Check if seat number provided is valid
    if(seat_number_to_cancel <= seats){
        //If it is, lets check if seat is reserved or not
        if(check_if_seat_empty(occupancy, seat_number_to_cancel) == 1){
            occupancy[seat_number_to_cancel - 1] = 0;
            printf("Reservation canceled: %d\n\n", seat_number_to_cancel);
        }
        else{
            printf("Seat %d is not reserved!\n\n", seat_number_to_cancel);
        }
    }
    else{
        printf("Please provide valid seat number: 1-%d\n\n", seats);
    }
}

//Function that search a seat by its number and print the status of the seat
void search_seat_by_number(int occupancy[], int seats){

    int seat_to_look_for;

    printf("Enter number of seat...\n");

    scanf("%d", &seat_to_look_for);

    //Check if seat number provided is valid
    if(seat_to_look_for <= seats){
        //If it is, lets check the status
        if(check_if_seat_empty(occupancy, seat_to_look_for) == 1){
            printf("Seat with number %d is reserved!\n\n", seat_to_look_for);
        }
        else{
            printf("Seat with number %d is free!\n\n", seat_to_look_for);
        }
    }
    else{
        printf("Please provide valid seat number: 1-%d\n\n", seats);
    }
}

//Function that prints the reserved seats asceding by number
void print_reserved_seats_by_number(int occupancy[], int seats){

    int i;//looping variable

    printf("Reserved seats:\n");

    for(i = 0; i < seats; i++){
        if(occupancy[i] == 1){
            printf("%d ", i+1);
        }
    }
    printf("\n\n");
}

//function that prnts the bus graph
void print_bus_graph(int occupancy[], int seats, char car_plate[]){

    int count_s = 0;//variable that counts the spaces
    int count_n = 0;//variable that counts the new line
    int i;//looping variable
    char seat_digit;//variable that stores the sign for printing purposes

    printf("%s\n", car_plate);

    //First, lets print the normal rows: seats-5
    for(i = 0; i < seats-5; i++){
        count_s += 1;//Increment the space counter
        count_n += 1;//Increment the new line counter
        if(occupancy[i] == 1){
            seat_digit = '*';
        }
        else{
            seat_digit = '_';
        }
        printf("%c", seat_digit);
        if(count_s == 2){//When space counter reaches two we must print
            printf(" "); //empty space
            count_s = 0; //we set again the counter to zero
        }
        if(count_n == 4){//When new line counter reaches 4 we must print
            printf("\n");//new line character
            count_n = 0; //we set again the counter to zero
        }
    }
    //Then we check the last row which has 5 seats
    for(i=seats-5; i <seats; i++){
        if(occupancy[i] == 1){
            seat_digit = '*';
        }
        else{
            seat_digit = '_';
        }
        printf("%c", seat_digit);
    }
    printf("\n\n");
}

//Function that exports the bus graph to a file
//The same algorithm as the previous function, print_bus_graph
void export_bus_graph_to_file(int occupancy[], int seats, char car_plate[]){

    FILE *fp2;
    int i;
    int count_s;
    int count_n;
    char seat_digit;

    fp2 = fopen(OUTPUTFILE, "w");

    if(fp2 == NULL){ //Checks if the file is EMPTY
        printf("Cannot open file \n");
        exit(-1);
    }
    else{ //Else it reads file and stores the values
        fprintf(fp2, "%s\n", car_plate);
        count_s = 0;
        count_n = 0;
        for(i = 0; i < seats-5; i++){
            count_s += 1;
            count_n += 1;
            if(occupancy[i] == 1){
                seat_digit = '*';
            }
            else{
                seat_digit = '_';
            }
            fprintf(fp2, "%c", seat_digit);
            if(count_s == 2){
                fprintf(fp2, " ");
                count_s = 0;
            }
            if(count_n == 4){
                fprintf(fp2, "\n");
                count_n = 0;
            }
        }

        for(i=seats-5; i <seats; i++){
            if(occupancy[i] == 1){
                seat_digit = '*';
            }
            else{
                seat_digit = '_';
            }
            fprintf(fp2, "%c", seat_digit);
            }
    }

    fclose(fp2);//Close the file
}
