#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//functions needed for this program:
//Time pause function (header)
//random number generator (header)
//testinput function (written), for checking the validity of a user's
//command. Modifies a pointer input char and returns 0 if successful
//returns -1 if unsuccessful
//
//insult function, spits out a string (written)

int validateinput(*userinput);
char throwinsult();
void endgame();

int main() {
    int usec = 200000; //0.2 seconds or 200K microseconds
    int *userin;

    //Game intro
    printf("Welcome to SciPaperStone!\n");
    usleep(usec); //from unistd function
    printf("Choose the number of games to play: ");


    return 0;
}



int validateinput(*userinput){
    int input, status, temp;
    printf("Please enter a number: ");
	status = scanf("%d", &input);
	while(status!=1){
		while((temp=getchar()) != EOF && temp != '\n');
		printf("Invalid input... please enter a number: ");
		status = scanf("%d", &input);

    return input;
	}
//takes userinput
//only return value if it is a positive integer
//else, it will keep looping until proper input is received
}

char throwinsult() {

}
void endgame() {

}
