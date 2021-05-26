//
//  main.c
//  478_Lab_2
//
//  Created by Javier Gonzalez on 9/17/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 250
#define PATTERN_SIZE 8

int main() {
    char buffer[BUFFER_SIZE];
    char pattern[PATTERN_SIZE] = {'0', '1', '1', '1', '1', '1', '1', '0'};
    int checker = 0;
    int start_position = 0, end_position =0; //marks the data between flags
    
    system("/bin/stty raw"); //sets input to raw data
    printf("To stop program enter \'~\'\n");
    for(int i=0;i<BUFFER_SIZE;i++) {
        //add user input to the buffer
        scanf(" %c", &buffer[i]);
        if (buffer[i] == '~') {
            system("stty sane");
            return 0;
        }
        //check the buffer for the pattern
        if (i>=PATTERN_SIZE-1) {
            for (int j=i-PATTERN_SIZE+1, k=0; j<=i; j++,k++) {
                //loop through buffer checking for pattern
                if (buffer[j] == pattern[k]) {
                    checker++;
                }
            }
        }
        
        //checks for flags
        if (checker!=PATTERN_SIZE) { //no flag found
            checker=0;
        } else { //flag found
            if (end_position==0 && start_position!=0) { //second of flags found
                end_position = i-PATTERN_SIZE; //end position set to ending index of information between flags
                //print flag found and the data between
                printf("\nSecond flag found.\n");
                printf("Data:\t");
                for (; start_position<=end_position; start_position++) {
                    printf("%c",buffer[start_position]);
                }
                printf("\n");
                //reset flag checkers and positions
                checker=0;
                start_position=0;
                end_position=0;
                continue;
            }
            if (start_position==0) { //no first flag found yet
                start_position = i+1;   //sets the position for the input between flags
                printf("\nFirst flag found, input data:\n");
                checker=0; //reset for second flag checking
            }
            
        }
        
    }
    return 0;
}
