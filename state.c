#include <stdlib.h>

//module to track the program's state. There are two states, either 1 or 0

int state;

void initialiseState(){
	state = 1;
}

int getState(){
	return state;
}

void changeState(){
	state = !state;
}
