/* MODIFIED HEAVILY BY GENBTC October 7,2016 as courtesy for DROX */
/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/*
 * INTRODUCTORY PARAGRAPH
 * ----------------------
 * The following code is used to play the codebreaker game. The user enters a seed which generates a random sequence of four numbers. They are then given 12 attempts
 * to guess the correct solution. After making each guess the user is told how many perfect and imperfect matches they got so that they can use this information to
 * improve upon their prior guess.
 * The 'set seed' function within this code simply checks if the entered seed is valid and proceeds accordingly. The 'start game' function generates the random
 * sequence. Finally, the 'make guess' function allows the user to enter an input of 4 integers. It then checks the validity of this input and, if it is valid,
 * compares this to the actual sequence to provide feedback on the matches.
 */

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution[4];

int set_seed (const char seed_str[]) {
    int seed;
    char post[2];

    if(sscanf(seed_str, "%d%1s", &seed, post) == 1) {
        srand(seed);
        return 1;
    } else {
        printf("set_seed: invalid seed\n");
        return 0;
    }
}

void start_game (int* one, int* two, int* three, int* four) {
    solution[0] = *one = rand()%8;
    solution[1] = *two = rand()%8;
    solution[2] = *three = rand()%8;
    solution[3] = *four = rand()%8;

    guess_number = 1;
}

int make_guess (const char guess_str[], int* one, int* two, int* three, int* four) {
    char post[2];
    int w,x,y,z;
    int guess[4];
    int result = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
    if(result == 4) {
        //for-loop code prep
        guess[0] = w;
        guess[1] = x;
        guess[2] = y;
        guess[3] = z; 
        //validate input    
        if(w < 8 && x < 8 && y < 8 && z < 8) {
            *one = w;
            *two = x;
            *three = y;
            *four = z;

            int paired[4] = {}; //initialized to 0 just in case we want to check paired == 0 directly instead of !=1
            int perfect_matches = 0;
            int misplaced_matches = 0;
           
            //loop 1: finds any perfect matches and marks them as such
            int i;
            for (i=0; i<4; i++) {
                if (guess[i] == solution[i]) {
                    perfect_matches++;
                    paired[i] = 1;
                    //printf("PERFECT MATCH #: %d.\n", i+1);
                }
            }
            //nested loop 2: check any non perfect matches for misplaced order
            int j;
            for (i=0; i<4; i++) {
                for (j=0; j<4; j++) {
                    if (paired[i] != 1 && guess[i] == solution[j]) {
                        misplaced_matches++;
                        paired[i] = 1;
                        //printf("Guess %d == Solution %d.\n", i+1,j+1);
                    }
                }
            }            

            printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_matches, misplaced_matches);
            guess_number++;
        } else {
            printf("make_guess: invalid guess\n");
            return 0;
        }
    } else {
        printf("make_guess: invalid guess\n");
        return 0;
    }
    return 1;
}


