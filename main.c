#include "ev3.h"

int main()
{
	// Initialize EV3 lib
	InitEV3();
	reset_arm();

	RotateMotor(OUT_BC, 25, convert_cm(62));
    // enough power to let the arm release
     RotateMotor(OUT_A, -25, 80);
    //RotateMotor(OUT_A, -25, 75);
    
    reset_arm();

	FreeEV3();
	return 0;
}

void reset_arm() {
	OnRevReg(OUT_A, 25);
	Wait(MS_500);
	Off(OUT_A);
}

int convert_cm(int amount) {
	const int degrees = 20;
	int retval;

	retval = amount * degrees;

	return retval;
}
