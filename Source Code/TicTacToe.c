// Operating system:> Arch Linux
// Compiler used:> gnu gcc-9.3.0

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Global variables declaration
char x, o;
char arr[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char player1Name[20], player2Name[20];


// Functions prototypes
int isWinner(void);
int decision(void);

void greenClr(void);
void redColor(void);
void blueColr(void);
void setBoard(void);
void gameRule(void);


// Driver function
int main(void) {

    FILE *file;
    file = fopen("Leaderboard.txt", "a+");
    fclose(file);

    char symbol, start;
    int select = 0;
    int player = 1;
    int choice = 0; 
    int score = -1;
    static int i = 0;
    
    system("clear");
    redColor();
    printf("\n\n");
    printf("%*s\n", 70, "---------------------------");
    printf("%*s\n", 70, "|       TIC-TAC-TOE       |");
    printf("%*s\n", 70, "---------------------------");
    printf("\n\n\n");
    printf("--------------------------------\n");
    printf("|             MENU             |\n");
    printf("--------------------------------\n");
    printf("|      1. START CHALLENGE      |\n");
    printf("|      2. LEADERBOARD          |\n");
    printf("|      3. GAME RULES           |\n");
    printf("|      4. QUIT                 |\n");
    printf("--------------------------------\n");
    printf("\nPlayer's choice? (1/2/3/4):> ");
    scanf("%d", &select);


    if(select == 1) {

    inputLabel:
        file = fopen("Leaderboard.txt", "a+");
        printf("\n--------------------------------\n");
        printf("Enter name of player(1):> ");
        scanf("%s", player1Name);
        fprintf(file, "%d. %s\n", ++i, player1Name);
        printf("Enter name of player(2):> ");
        scanf("%s", player2Name);
        printf("--------------------------------\n");
        fprintf(file, "%d. %s\n", ++i, player2Name);
        fclose(file);

        if(!strcmp(player1Name, player2Name)) {
            printf("\nTry Again! Opt different names.\n");
            goto inputLabel;
        }
        else decision();
        
        setBoard();

        do {
            
            player = ((player % 2) ? 1 : 2);

            if(player == 1) 
                printf("\n\n\n\n%s enter any digit from (1-9) as a response:> ", player1Name);
            else 
                printf("\n\n\n\n%s enter any digit from (1-9) as a response:> ", player2Name);

            scanf("%d", &choice);
            symbol = ((player == 1) ? x : o);

            if(choice == 1 && arr[0] == '1')
                arr[0] = symbol;
            else if(choice == 2 && arr[1] == '2') 
                arr[1] = symbol;
            else if(choice == 3 && arr[2] == '3')
                arr[2] = symbol;
            else if(choice == 4 && arr[3] == '4')
                arr[3] = symbol;
            else if(choice == 5 && arr[4] == '5')
                arr[4] = symbol;
            else if(choice == 6 && arr[5] == '6')
                arr[5] = symbol;
            else if(choice == 7 && arr[6] == '7')
                arr[6] = symbol;
            else if(choice == 8 && arr[7] == '8')
                arr[7] = symbol;
            else if(choice == 9 && arr[8] == '9')
                arr[8] = symbol;
            else player--;

            score = isWinner();
            player++;
            setBoard();

        } while(score == -1);

        file = fopen("Leaderboard.txt", "a+");
        if(score == 1) {
            if(player == 2) {
                printf("\n\n\n\nCongrats %s! You Won.", player1Name);
                fprintf(file, "Winner: %s\n\n", player1Name);
                getchar();
            }

            else {
                printf("\n\n\n\nCongrats %s! You Won.", player2Name);
                fprintf(file, "Winner: %s\n\n", player2Name);
                getchar();
            }
            fclose(file);
        }

        else {
            printf("\n\n\n\nHard Luck! Game Drawn.");
            fprintf(file, "Game Drawn!\n\n");
            getchar();
        }

        printf("\n\nGood Game! Well Played.\n\n");
    } 
    
    if(select == 2) {

        system("clear");
        int option;
        printf("%*s\n", 70, "---------------------------");
        printf("%*s\n", 70, "|       LEADERBOARD       |");
        printf("%*s\n", 70, "---------------------------");
        printf("\n\n");
        char ch;

        file = fopen("Leaderboard.txt", "r");
        while((ch = getc(file)) != EOF) {
            printf("%c", ch);
        }
        fclose(file);

        printf("\nPRESS (1) TO START (else) TO END GAME:> ");
        scanf("%d", &option);
        
        if(option == 1) goto inputLabel;
        else goto exitLabel;
    }
         
    if(select == 3) {

        int uResponse;
        gameRule();
        printf("\nPRESS (1) TO START (else) TO END GAME:> ");
        scanf("%d", &uResponse);
        if(uResponse == 1) goto inputLabel;
        else goto exitLabel;
    }

    if(select == 4) {

        exitLabel:
            greenClr();
            printf("\n\nYOU EXITED THE GAME ROOM!!\n\n");
    }
    return 0;
}


void redColor(void) { printf("\033[0;91m"); }
void greenClr(void) { printf("\033[0;92m"); }
void blueColr(void) { printf("\033[0;94m"); }


void setBoard(void) {

    system("clear");
    greenClr();
    printf("%*s\n", 70, "---------------------------");
    printf("%*s\n", 70, "|       TIC-TAC-TOE       |");
    printf("%*s\n", 70, "---------------------------");
    printf("\n\n%s:> (%c)\n", player1Name, x);
    printf("\n%s:> (%c)\n\n", player2Name, o);
    printf("\n\n");

    printf("  %49c  |  %c  |  %c  \n", arr[0], arr[1], arr[2]);
    printf("%*s\n", 65, "     |     |     ");
    printf("%*s\n", 65, "-----|-----|-----");
    printf("%*s\n", 65, "     |     |     ");
    printf("  %49c  |  %c  |  %c  \n", arr[3], arr[4], arr[5]);
    printf("%*s\n", 65, "     |     |     ");
    printf("%*s\n", 65, "-----|-----|-----");
    printf("%*s\n", 65, "     |     |     ");
    printf("  %49c  |  %c  |  %c  \n", arr[6], arr[7], arr[8]);
}


int decision(void) {

    char decision;
    decisionLabel:
        printf("\n%s choose from X or O:> ", player1Name);
        decision = getchar();
        scanf("%c", &decision);

        if(decision == 'X' || decision == 'x') {
            x = 'X';
            o = '0';
        }
        else if(decision == '0') {
            x = '0';
            o = 'X';
        }
        else {
            printf("\nPlease, enter X or O only.\n");
            goto decisionLabel;
        }
}


int isWinner(void) {

    if(arr[0] == arr[1] && arr[1] == arr[2]) return 1;
    else if(arr[3] == arr[4] && arr[4] == arr[5]) return 1;
    else if(arr[6] == arr[7] && arr[7] == arr[8]) return 1;
    else if(arr[0] == arr[3] && arr[3] == arr[6]) return 1;
    else if(arr[1] == arr[4] && arr[4] == arr[7]) return 1;
    else if(arr[2] == arr[5] && arr[5] == arr[8]) return 1;
    else if(arr[0] == arr[4] && arr[4] == arr[8]) return 1;
    else if(arr[2] == arr[4] && arr[4] == arr[6]) return 1;
    else if(arr[0] != '1' && arr[1] != '2' && arr[2] != '3' && arr[3] != '4' && arr[4] != '5' && arr[5] != '6' && arr[6] != '7' && arr[7] != '8' && arr[8] != '9') {
        return 0;
    }
    else return -1;
}


void gameRule(void) {

    system("clear");
    blueColr();
    printf("%*s\n", 75, "------------------------------");
    printf("%*s\n", 75, "|   WELCOME TO TIC-TAC-TOE   |");
    printf("%*s\n", 75, "------------------------------");
    printf("\n\n");

    printf("%92s", "--------------------------------------------------------------------\n");
    printf("%92s", "|         RULES FOR PLAYING TIC-TOC-TOE IN TWO PLAYER MODE         |\n");
    printf("%92s", "--------------------------------------------------------------------\n");
    redColor();
    printf("%92s", "1. This game is played on a grid that is 3 squares by 3 squares.   |\n");
    printf("%92s", "2. You are X, your friend is O (or vice versa).                    |\n");
    printf("%92s", "3. Players take turns putting their marks in empty squares.        |\n");
    printf("%92s", "4. First player to get 3 marks in a row (up, down, diagonally)     |\n");
    printf("%92s", "   is the winner.                                                  |\n");
    printf("%92s", "5. When all the 9 squares will be filled, game will be over.       |\n");
    printf("%92s", "6. In case no players has 3 marks in a row, the game ends on a tie.|\n");
    blueColr();
    printf("%92s", "--------------------------------------------------------------------\n");
    printf("\n\n\n");
}
