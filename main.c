#include "ev3.h"

int main()
{
	// Initialize EV3 lib
	InitEV3();

	//Reset the arm and wait 500ms to make sure its reset
	reset_arm();

	//Drive forward till arm can reach crane right operator
	//Move arm up
	//Move arm down
	//Drive backwards 
	//Turn
	//Drive forwards
	//turn
	//Drive forwards
	//Operator other arm
	//Do a dance
	
	int degrees = convert_cm(5);
	FreeEV3();
	return 0;
}

void reset_arm() {
	OnRevReg(OUT_A, 25);
	Wait(MS_500);
	Off(OUT_A);
}

int convert_cm(int cm) {
	

}
