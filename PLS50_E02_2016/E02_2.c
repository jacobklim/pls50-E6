//PLS 50
//Homework E02 - Question 2
//Author: Iakovos Klimenof
//Description: Bus reservation extended using malloc and linked lists

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Programme specific constants
#define FILENAME "bus.txt"
#define MAX_SEATS 53
#define PLATE_NUM_SIZE 7
#define PASSENGER_NAME 40
#define PASSENGER_TEL_NUM 10

//Menu selections and checks
#define MIN_SELECTION 0
#define MAX_SELECTION 5
#define INVALID_USER_SELECTION -1

//FILE constants needed for check if a file was open properly
#define OPEN_FILE_SUCCESS 1
#define OPEN_FILE_ERROR -1

//Seat check constants
#define SEAT_EMPTY 1
#define SEAT_NOT_EMPTY 0

//Constants needed for searching by name or tel number
#define NAME_OR_NUMBER_OK 1
#define NAME_OR_NUMBER_NOT_OK -1


//Stracture to store passenger info
typedef struct {

    char name[PASSENGER_NAME +1];
    unsigned short tel_number[PASSENGER_TEL_NUM];
    unsigned int seat_number;

} Passenger;
//Stracture used for the linked list
typedef struct nodelist{

    Passenger data;
    struct nodelist *next;

}NodeList;

//Function Prototypes
void printMenu(void);
int getUserSelection(void);
int openFile(FILE **file);
void readBusFile(FILE *file, char *bus_plate, int *seats);
void printBusInfo(char *bus_plate, int seats);
void initializePassengerArray(int seats);
void checkEmptySeats(int seats);
int checkIfSeatIsEmpty(int seat_number);
void reserveSeatByNumber(int seats);
int checkNameOrTelephone( int seats);
void printBusStatus( int seats);
void cancelReservationByNumber(int seats);
void refreshBusFile(FILE **file,char *bus_plate, int seats);
void sortMessageAndChoice(int seats);
void sortByName(int seats);
void sortBySeat(int seats);
NodeList *insert(NodeList **nodePtr, int i);
void createNodeList(int seats);
void refreshBusFileNodeList(FILE **file,char *bus_plate, int seats);
//Initiate the Passenger struct array
Passenger *occupancy; //Global variable
//Initiate tke linked list
NodeList *head = NULL; //Global variable

int main(void){

    FILE *fp; //Pointer for the bus file

    unsigned int user_selection; //Variable to store user selection

    char bus_plate[PLATE_NUM_SIZE + 1]; //Variable to store the bus plate read from the file
    int seats; //Variable to store the total number of seats read from the file

    //Open the file bus,txt, if no file with name bus.txt
    //return OPEN_FILE_ERROR
    if(openFile(&fp) == OPEN_FILE_SUCCESS){
        printf("File OK\n");
        //Read bus.txt and store the variables
        readBusFile(fp, bus_plate, &seats);
    }
    else{
        printf("Cannot open file...\n");
        return OPEN_FILE_ERROR;
    }

    //Close the file
    fclose(fp);

    //Print the bus info
    printBusInfo(bus_plate, seats);

    //Print the appropriate message before loop
    printMenu();

    while(user_selection = getUserSelection()){

        switch(user_selection){
        case 1:
            printf("%d\n",user_selection);
            checkEmptySeats(seats);
            break;
        case 2:
            printf("%d\n",user_selection);
            reserveSeatByNumber(seats);
            break;
        case 3:
            printf("%d\n",user_selection);
            if(checkNameOrTelephone(seats)==NAME_OR_NUMBER_OK){
                printf("There is a reservation with this Name or Phone number!\n");
            }
            break;
        case 4:
            printf("%d\n",user_selection);
            cancelReservationByNumber(seats);
            break;
        case 5:
            printf("%d\n",user_selection);
            sortMessageAndChoice(seats);
            sortBySeat(seats);
            break;
        case INVALID_USER_SELECTION:
            printf("Invalid selection.\n");
        }
        //Print the appropriate after selection
        printMenu();
    }
    //Sort the occupancy again by name
    sortByName(seats);
    //Create the linked list
    createNodeList(seats);
    //Refresh the bus file from the linked list
    refreshBusFileNodeList(&fp, bus_plate,seats);
    return 0;
}


/**  Function:       printMenu()
    Description:    Helper function for printing the main
                    main menu
*/
void printMenu(void){

    printf("\t-------Menu-------\n");
    printf("\tPlease enter your choice:\n");
    printf("\t1. Print empty seats\n");
    printf("\t2. Reserve seat by number\n");
    printf("\t3. Search reservation by Name or Tel number\n");
    printf("\t4. Cancel reservation by seat number\n");
    printf("\t5. Print bus status\n");
    printf("\t0. Exit\n");
}

/**  Function:       getUserSelection()
    Description:    Returns the user's choice
*/
int getUserSelection(void){

    unsigned int user_selection;

    printf("Please enter selection %d - %d\n",MIN_SELECTION, MAX_SELECTION);

    scanf("%d", &user_selection);

    //Checks if user selection is between 0-5
    if(user_selection < MIN_SELECTION || user_selection > MAX_SELECTION){
        user_selection = INVALID_USER_SELECTION;
    }

    return user_selection;
}

/**  Function:       openFile()
    Description:    Takes as an argument a pointer to FILE
                    and returns OPEN_FILE_SUCCESS or
                    OPEN_FILE_ERROR
*/
int openFile(FILE **file){

    *file = fopen(FILENAME, "r");

    if(*file == NULL){
        return OPEN_FILE_ERROR;
    }
    else{
        //printf("Cannot open file...\n");
        return OPEN_FILE_SUCCESS;
    }
}

/**  Function        readBusFile()
    Description:    Reads the file with fscanf()
*/
void readBusFile(FILE *file, char *bus_plate, int *seats){

    char name[PASSENGER_NAME];
    char surname[PASSENGER_NAME];
    int seat_number;
    //double phone_number;
    int i;
    //Read the first line and store the bus info
    fscanf(file, "%s %d\n", &(*bus_plate), &(*seats));
    //Initialize the array using malloc
    initializePassengerArray(*seats);
    //Read the remaining file and store passenger info
    while( !feof(file) ){

        fscanf(file, "%s %s %d",surname, name, &seat_number);

        for(i=0; i<PASSENGER_TEL_NUM; i++){
            fscanf(file, "%1hu",&occupancy[seat_number-1].tel_number[i]);
        }
        strcpy(occupancy[seat_number - 1].name, surname);
        strcat(occupancy[seat_number - 1].name, " ");
        strcat(occupancy[seat_number - 1].name, name);

        occupancy[seat_number - 1].seat_number = seat_number;
    }
}

/**  Function:      printBusInfo()
    Description:    Takes as arguments the string plate of bus
                    and int seats, total number of seats
                    and prints the appropriate message
*/
void printBusInfo(char *bus_plate, int seats){

    printf("\t------Bus Info--------\n");
    printf("\tBus plate: %s\n\tNumber of seats: %d\n\n", bus_plate, seats);
}

/** Function:       initializePassengerArray
    Description:    Helper function that onitializes the
                    array of Pssenger stuct to zero
*/
void initializePassengerArray(int seats){

    int i;//Loop variable
    //Reserve memory with malloc
    occupancy = malloc(sizeof(Passenger) * seats);
    //Initiate array with empty seats
    for(i=0; i<seats; ++i){
        occupancy[i].name[0] = '\0';
    }

}

/** Function:       checkEmptySeats()
    Description:    Takes as an argument a Passenger struct
                    and checks the empty seats.
*/
void checkEmptySeats( int seats){

    int count = 0;//count the empty seats
    int i;//classic variable for the loops
    int seat_number;

    printf("Empty seats:\n");
    for(i = 0; i < seats; i++){
        if (occupancy[i].name[0]=='\0'){
            count += 1;
            seat_number = i + 1;
            printf("%d, ",seat_number);
        }
    }
    printf("\b\b ");
    printf("\nTotal number of empty seats: %d\n\n", count);
}

/** Function:       checkIfSeatISEmpty()
    Description:    Takes as arguments the array of strucs Passenger
                    and seat number.
                    Returns an int regarding the state of the seat
*/
int checkIfSeatIsEmpty(int seat_number){

    if(occupancy[seat_number-1].name[0] == '\0'){
        return SEAT_EMPTY;
    }
    else{
        return SEAT_NOT_EMPTY;
    }
}

/** Function:       reserveSeatByNumber()
    Description:    Takes as arguments the array of strucs Passenger
                    and total number of seats.
                    If the seat is not taken it will be reserved.
*/
void reserveSeatByNumber(int seats){

        int seat_number;
        char name[PASSENGER_NAME];
        char lastname[PASSENGER_NAME];
        int i;

        printf("Enter seat number: \n");
        scanf("%d", &seat_number);

        if(seat_number <= seats && seat_number > 0){
            if(checkIfSeatIsEmpty(seat_number)){
                printf("Enter LastName Name:\n");
                scanf("%s %s", lastname, name );
                printf("Enter 10-digit phone number:\n");
                for(i=0; i<PASSENGER_TEL_NUM; i++){
                    scanf("%1hu", &occupancy[seat_number-1].tel_number[i]);
                }

                strcpy(occupancy[seat_number - 1].name, lastname);
                strcat(occupancy[seat_number - 1].name, " ");
                strcat(occupancy[seat_number - 1].name, name);
                occupancy[seat_number - 1].seat_number = seat_number;
                printf("Seat %d reserved!!\n\n", seat_number);
            }
            else{
                printf("Seat already reserved!!\n\n");
            }
        }
        else{
            printf("Invalid seat number!!\n\n");
        }

}
/** Function:       checkNameOrTelephone()
    Description:    Takes as arguments the array of strucs Passenger
                    and total number of seats.
                    Asks for name or telephone number to search in array
                    of Passenger struct.
                    Returns int NAME_OR_NUMBER_OK or NAME_OR_NUMBER_NOT_OK.
*/
int checkNameOrTelephone(int seats){

    int choice, count;
    int i;
    int j;
    char lastname[PASSENGER_NAME];
    char name[PASSENGER_NAME];
    unsigned short phone_number[PASSENGER_TEL_NUM];
    unsigned short num_digit;

    printf("Search by:\n");
    printf("1. LastName Name\n");
    printf("2. Telephone number\n");

    scanf("%d", &choice);

    switch(choice){
        case 1:
            printf("Enter LastName Name:\n");
            fflush(stdin);
            scanf("%s%s", lastname, name );
            strcat(lastname, " ");
            strcat(lastname, name);

            for(i=0; i<seats; i++){
                if(strcmp(occupancy[i].name, lastname) == 0){
                    return NAME_OR_NUMBER_OK;
                }
            }
            printf("No reservation with this Name or Tel Number!!\n\n");
            return NAME_OR_NUMBER_NOT_OK;
            break;

        case 2:
            printf("Enter 10-digit phone number:\n");
            fflush(stdin);
            for(i=0; i<PASSENGER_TEL_NUM; i++){
                scanf("%1hu", &num_digit);
                phone_number[i] = num_digit;
            }
            for(i=0; i<seats; i++){
                for(j=0; j<PASSENGER_TEL_NUM; j++){
                    if(occupancy[i].tel_number[j] == phone_number[j])
                    count +=1;
                }
                if(count == PASSENGER_TEL_NUM){
                    return NAME_OR_NUMBER_OK;
                }
                count = 0;
            }
            printf("No reservation with this Name or Tel Number!!\n\n");
            return NAME_OR_NUMBER_NOT_OK;
            break;

        default:
            printf("Invalid selection\n");
            return NAME_OR_NUMBER_NOT_OK;
            break;
    }
}
/** Function:       printBusStatus()
    Description:    Prints the status of the bus.
                    Prints passenger Name, phone number
                    and seat number.
*/
void printBusStatus(int seats){

    int i;
    int j;
    printf("****************************************************\n");
    printf("NAME\t\t\tTEL NUMBER\tSEAT NUM\n");
    for(i=0; i<seats; i++){
        if(occupancy[i].name[0] != '\0' ){
            printf("%s\t", occupancy[i].name);
            for(j=0; j<PASSENGER_TEL_NUM; j++){
                printf("%hu", occupancy[i].tel_number[j]);
            }
            printf("\t");
            printf("%d\n", occupancy[i].seat_number);
        }
    }
    printf("****************************************************\n");
}

/** Function:       cancelReservationByNumber()
    Description:    Cancel a reservation by seat number.
                    Takes as arguments an array of
                    Passenger struct and the total number
                    seats of the bus.
*/
void cancelReservationByNumber(int seats){

    int seat_number;

    printf("Enter seat number: \n");
    scanf("%d", &seat_number);

        if(seat_number <= seats && seat_number > 0){
            if(checkIfSeatIsEmpty(seat_number)){
                printf("Seat is not reserved!!\n");
            }
            else{
                occupancy[seat_number-1].name[0] = '\0';
                printf("Reservation cancelled: %d\n", seat_number);
            }
        }
        else{
            printf("Invalid seat number!!\n");
        }
}
/** Function:       refreshBusFile()
    Description:    Updates the FILENAME.
*/
void refreshBusFile(FILE **file,char *bus_plate, int seats){

    int i;
    int j;

    *file = fopen(FILENAME, "w");

    if(*file == NULL){
        printf("Cannot open file!!\n");
    }
    else{
        printf("File opend\n");
        fprintf(*file, "%s %d\n",bus_plate, seats);
        for(i=0; i<seats; i++){
            if(strlen(occupancy[i].name) > 0){
            fprintf(*file, "%s %d ", occupancy[i].name, occupancy[i].seat_number);
            for(j=0; j<PASSENGER_TEL_NUM; j++){
                fprintf(*file, "%1hu", occupancy[i].tel_number[j]);
            }
            fprintf(*file, "\n");
            }
        }
    }
    fclose(*file);
}
/** Function:       sortMessageAndChoice()
    Description:    Used to print the appropriate messages
                    and call the functions regarding the user;s
                    sorting choice.
*/
void sortMessageAndChoice(int seats){

    unsigned int selection;
    unsigned int bus_seats = seats;

    printf("Print Bus Status sorted by:\n");
    printf("1. Lastname Name\n");
    printf("2. Seat number\n");
    scanf(" %d", &selection);

    switch(selection){

        case 1:
            sortByName(bus_seats);
            printBusStatus(seats);
            break;
        case 2:
            printBusStatus(bus_seats);
            break;
        default:
            printf("Invalid selection!\n");
            break;
    }
}
/** Function:       sortNyName()
    Description:    Sorts the occupancy array by NAME using
                    bubble sort.
*/
void sortByName(int seats){

    int i, j;
    Passenger temp;

    for(i=0; i<seats-1; i++){
        for(j=0; j<seats-1; j++){
            if(strcmp(occupancy[j].name, occupancy[j+1].name) > 0){
                temp = occupancy[j+1];
                occupancy[j+1] = occupancy[j];
                occupancy[j] = temp;
            }
        }
    }
}
/** Function:       sortBySeat()
    Description:    Sorts the occupancy array back by
                    seat number using bubble sort.
*/
void sortBySeat(int seats){

    int i, j;
    Passenger temp;
    for(i=0; i<seats-1; i++){
        for(j=0; j<seats-1; j++){
            if(occupancy[j].seat_number > occupancy[j+1].seat_number){
                temp = occupancy[j+1];
                occupancy[j+1] = occupancy[j];
                occupancy[j] = temp;
            }
        }
    }
}

/** Function:       *insert()
    Description:    Recursive function that adds a node
                    to a linked list.
*/
NodeList *insert(NodeList **nodePtr, int i){

    if(*nodePtr==NULL){
        *nodePtr = (NodeList*)malloc(sizeof(NodeList));
        if(*nodePtr == NULL){
            printf("Error!!\n");
            exit(0);
        }
        (*nodePtr)->data = occupancy[i];
        (*nodePtr)->next = NULL;
        return *nodePtr;
    }
    else{
        (*nodePtr)->next = insert(&(*nodePtr)->next, i);
        return *nodePtr;
    }
}
/** Function:       createNodeList()
    Description:    Function that creates the linked list
                    for the reserved seats
*/
void createNodeList(int seats){
    int i;
    for(i=0; i<seats; i++){
        if(strlen(occupancy[i].name) > 0){
            //Call to the recursive function
            insert(&head, i);
        }
    }
}
/** Function:       refreshBusFileNodelist()
    Description:    Refreshes the bus.txt file
                    from the linked list head
*/
void refreshBusFileNodeList(FILE **file,char *bus_plate, int seats){

    int i;

    *file = fopen(FILENAME, "w");

    if(*file == NULL){
        printf("Cannot open file!!\n");
    }
    else{
        printf("File opend\n");
        fprintf(*file, "%s %d\n",bus_plate, seats);
        while(head != NULL){
            fprintf(*file, "%s %d ", head->data.name, head->data.seat_number);
            for(i=0; i<PASSENGER_TEL_NUM; i++){
                fprintf(*file, "%1hu", head->data.tel_number[i]);
            }
            fprintf(*file, "\n");
            head = head->next;
        }
    }
    fclose(*file);
}
