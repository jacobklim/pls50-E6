//PLS 50
//Homework E02 - Question 3
//Author: Iakovos Klimenof
//Description: SET card game

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Game constants
#define DECK 81
#define VALUE 3
#define FEATURES 4
#define PLAY 12
#define NUMBER_OF_PLAYERS 3
//Boolean constants
#define TRUE 1
#define FALSE 0
//Double array constants
#define ROWS 3
#define COLUMNS 4
//Check constants
#define INVALID_ID -1
#define VALID_ID 1
//Constant for the number of cards a player will choose
#define PLAYER_CHOICE 3
//Constant for checking if three cards are SET
#define VALID_SET 1
#define INVALID_SET 0
//Constants for the score
#define WIN 2
#define LOSS -1
#define MIN_SCORE 0
#define MAX_SCORE 10
#define MAX_CHAR_VALUE 255
#define STOP_FOR_SCORE 0
#define CONTINUE 1

//Struct for the players
typedef struct {
    char name[17];
    unsigned char score;
    char id;
} Player;
//Struct for the cards
typedef struct {
    char colour;
    char symbol;
    char number;
    char shading;
    int played;
} Card;

//Function Prototypes
void createDeck(Card deck[], char colours[], char symbols[], char numbers[], char shadings[]);
void printDeck(Card deck[]);
void getNextCard(Card deck[], Card play[ROWS][COLUMNS]);
void printPlay(Card play[ROWS][COLUMNS]);
void printPlayerStatus(Player playerlist[]);
void initializePlayerList(Player playerlist[]);
int checkPlayerID(Player playlist[], char *player_id);
int takePlayerCards(Player playlist[], Card play[ROWS][COLUMNS], char player_id);
Player findPlayer(Player playlist[], char player_id);
int checkIfSet(Card player_cards[]);
void changeScore(Player player_list[], char player_id, int score);
int checkScore(Player player_list[]);

int main(void){

    //3-player game
    Player playerlist[NUMBER_OF_PLAYERS];
    //Initailize the default settings
    initializePlayerList(playerlist);
    //Array of structs Card for the cards
    Card deck[DECK];
    //Array of structs Card for the play deck
    Card play[ROWS][COLUMNS];
    //The values of the cards
    char colours[VALUE] = {'r', 'g', 'b'};
    char symbols[VALUE] = {'c', 't', 'r'};
    char numbers[VALUE] = {'1', '2', '3'};
    char shadings[VALUE] = {'b', 'h', 'e'};
    //Variable to store player id
    char player_id;
    //Variable needed for the switch
    int choice;
    //Initiate rand
    srand(time(NULL));
    //Create the 81-card-deck
    createDeck(deck, colours, symbols, numbers,shadings);
    //Create the 12-card SET game
    getNextCard(deck, play);
    //Print initial player status
    printPlayerStatus(playerlist);
    //Print the 12-card SET game
    printPlay(play);
    //Take the ID of the player and loop
    while(choice = checkPlayerID(playerlist, &player_id)){
        switch(choice){
            case VALID_ID:
                //Take player's card and check if SET
                if(takePlayerCards(playerlist, play, player_id) == VALID_SET){
                    createDeck(deck, colours, symbols, numbers,shadings);
                    getNextCard(deck, play);
                }
                break;
            case INVALID_ID:
                //In case of INVALID_ID create new deck and play deck
                createDeck(deck, colours, symbols, numbers,shadings);
                getNextCard(deck, play);
                break;
        }
        //Print player status
        printPlayerStatus(playerlist);
        //Check the player's score
        if(checkScore(playerlist) == STOP_FOR_SCORE){
            break;
        }
        //Print the 12-card SET game
        printPlay(play);
    }

    return 0;
}



/** Function:       createDeck()
    Description:    Creates the 81-card deck
*/
void createDeck(Card deck[], char colours[], char symbols[], char numbers[], char shadings[]){

    int i,j,x,z;//Variable for loop
    int count = 0;

    for(i=0; i<VALUE; i++){
        for(j=0; j<VALUE; j++){
            for(x=0; x<VALUE; x++){
                for(z=0; z<VALUE; z++){
                deck[count].colour = colours[i];
                deck[count].symbol = symbols[j];
                deck[count].number =numbers[x];
                deck[count].shading = shadings[z];
                deck[count].played = FALSE;
                count +=1;
                }
            }
        }
    }
}


/** Function:       printDeck()
    Description:    Helper function thats print the
                    81-card Deck just to check the createDeck
                    function
*/
void printDeck(Card deck[]){

    int i;//Variable for loop
    int count =0;

    for(i=0; i<DECK; i++){
        printf("%d:[%c, %c, %c, %c, %d]\n", i,deck[i].colour, deck[i].symbol, \
        deck[i].number, deck[i].shading, deck[i].played);
        count += 1;
    }
    printf("Number of cards: %d\n\n", count);
}

/** Function:       getNextCard()
    Description:    Randomly creates the play deck
*/
void getNextCard(Card deck[], Card play[ROWS][COLUMNS]){
    int i,j;
    int card;

    for(i=0; i<ROWS; i++){
        for(j=0; j<COLUMNS; j++){

        card = rand() % 81;

        while(deck[card].played == TRUE){
                card = rand() % 81;
        }
        deck[card].played = TRUE;
        play[i][j] = deck[card];
        }
    }
}

void printPlay(Card play[ROWS][COLUMNS]){

    int i,j;//Variable for loop
    int count =0;
    printf("\t\t\t**********SET GAME***********\n\n");
    for(i=0; i<ROWS; i++){
        printf("\t");
        for(j=0; j<COLUMNS; j++){
            printf("[%c, %c, %c, %c] ", play[i][j].colour, play[i][j].symbol, \
            play[i][j].number, play[i][j].shading);
            count += 1;
        }
        printf("\n\n");
    }
    printf("******************************************************************************\n");
    printf("Number of cards: %d\n", count);
}

/** Function:       printPlayerStatus()
    Description:    Function that prints the
                    player status
*/
void printPlayerStatus(Player playerlist[]){
    int i;//Loop variable

    printf("Players on-line:\n");
    printf("%20s\t%2s\t%5s\n", "NAME", "ID","SCORE");
    for(i=0; i<NUMBER_OF_PLAYERS; i++){
        printf("%20s\t%2c\t%5d\n", playerlist[i].name, playerlist[i].id, playerlist[i].score);
    }
    printf("******************************************************************************\n");
}

/** Function:       initializePlayerList()
    Description:    Function that initializes
                    player list to the default
                    settings
*/
void initializePlayerList(Player playerlist[]){
    strcpy(playerlist[0].name,"Marina Andreou");
    playerlist[0].score = 0;
    playerlist[0].id = 'a';

    strcpy(playerlist[1].name,"Kostas Grammenos");
    playerlist[1].score = 0;
    playerlist[1].id = 'g';

    strcpy(playerlist[2].name,"Maria Perdika");
    playerlist[2].score = 0;
    playerlist[2].id = 'p';

}

/** Function:       checkPlayerId()
    Description:    Function that checks if
                    player id is valid
*/
int checkPlayerID(Player playerlist[], char *player_id){
    int i; //Loop variable
    char input;

    printf("Please enter player id:\n");
    scanf(" %c", &input);

    if(input == '0'){
        return 0;
    }

    for(i=0; i<NUMBER_OF_PLAYERS; i++){
        if(input == playerlist[i].id){
            *player_id = input;
            return VALID_ID;
        }
    }
    return INVALID_ID;
}
/** Function:       findPlayer()
    Description:    Helper function that
                    returns a Player struct based on
                    given id.
*/
Player findPlayer(Player playlist[], char player_id){
    int i;

    for(i=0; i<NUMBER_OF_PLAYERS; i++){
        if(playlist[i].id == player_id){
            return playlist[i];
        }
    }
}
/** Function:       takePlayerCards()
    Description:    The main function of the game.
                    Reads the player's card, calls
                    the helper function checkIfSet()
                    and regarding the result increment or
                    decrement player's score.

*/
int takePlayerCards(Player playlist[], Card play[ROWS][COLUMNS], char player_id){

    int i=0;//Variable for loop
    int j;//Variable for loop
    int choice_number;
    int row, column;
    Card player_choices[PLAYER_CHOICE];//Array for storing player's cards
    Player player;//Variable to store current player
    int count;//Variable needed for counting if cards are a SET

    //Find current player
    player = findPlayer(playlist, player_id);
    //Print appropriate messages
    printf("%s playing...\n",player.name);
    printf("Please provide 3 cards (ROW COLUMN):\n");
    //Take three cards of player's choice
    while(i<PLAYER_CHOICE){
        printf("Card number %d: ", i+1);
        scanf("%d", &choice_number);
        row = choice_number /10;
        column = choice_number %10;
        if(row>=0 && row<ROWS && column>=0 && column<COLUMNS){
            player_choices[i] = play[row][column];
            i++;
        }
        else{
            printf("Invalid card\n");
        }
    }
    //Print the cards
    printf("Player's cards:\n");
    for(i=0; i<PLAYER_CHOICE; i++){
        printf("%d:[%c, %c, %c, %c] ", i+1,player_choices[i].colour, player_choices[i].symbol, \
        player_choices[i].number, player_choices[i].shading);
    }
    printf("\n\n");
    //Check if SET
    if(checkIfSet(player_choices) == VALID_SET){
        printf("SET!!!!\n");
        printf("******************************************************************************\n");
        changeScore(playlist, player_id, WIN);
        return VALID_SET;
    }
    else{
        printf("NOT SET!!!\n");
        printf("******************************************************************************\n");
        changeScore(playlist, player_id, LOSS);
        return INVALID_SET;
    }

    printf("\n\n");
}
/** Function:       checkIfSet()
    Description:    Helper function to determine if
                    player's cards are SET
*/
int checkIfSet(Card player_cards[]){

    int i;//Variable for loop
    int colour=0;
    int symbol=0;
    int number=0;
    int shading=0;
    int set=0;

    for(i=0; i<PLAYER_CHOICE-1; i++){
        if(player_cards[i].colour == player_cards[i+1].colour){
            colour +=1;
        }
        if(player_cards[i].symbol == player_cards[i+1].symbol){
            symbol +=1;
        }
        if(player_cards[i].number == player_cards[i+1].number){
            number +=1;
        }
        if(player_cards[i].shading == player_cards[i+1].shading){
            shading +=1;
        }
    }
    if(colour == 2 || colour == 0){
        set += 1;
    }
    if(symbol == 2 || symbol == 0){
        set += 1;
    }
    if(number == 2 || number == 0){
        set += 1;
    }
    if(shading == 2 || shading == 0){
        set += 1;
    }
    if(set == 4){
        return VALID_SET;
    }
    else{
        return INVALID_SET;
    }
}

/** Function:       changescore()
    Description:    Apply changes to array of
                    players regarding the score.
*/
void changeScore(Player player_list[], char player_id, int score){
    int i;//Variable for loop

    for(i=0; i<NUMBER_OF_PLAYERS; i++){
        if(player_list[i].id == player_id){
            player_list[i].score += score;
            if(player_list[i].score == MAX_CHAR_VALUE){
                player_list[i].score = 0;
            }
        }
    }
}
/** Function:       checkScore()
    Description:    Keep track of the player's score
*/
int checkScore(Player player_list[]){
    int i;
    for(i=0; i<NUMBER_OF_PLAYERS; i++){
        if(player_list[i].score >= MAX_SCORE){
            printf("Winner is: %s\n", player_list[i].name);
            return STOP_FOR_SCORE;
        }
    }
    return CONTINUE;
}
