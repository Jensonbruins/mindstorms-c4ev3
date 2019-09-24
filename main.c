#include "ev3.h"

/*
 * function: main()
 * Runs when program is init
 */
int main()
{
	// Initialize EV3 lib
	InitEV3();

	// Reset arm to zero for program
	reset_arm();

	crane_mission();

    	FreeEV3();
	return 0;
}

/*
 * function: crane_mission()
 * Runs the crane mission from base
 */
void crane_mission() {
	
	// Start driving to first lever
	RotateMotor(OUT_BC, 20, convert_cm(30));
	turn_right();
	RotateMotor(OUT_BC, 15, convert_cm(10));
	turn_left();
	RotateMotor(OUT_BC, 20, convert_cm(32));
	
	// Start lever up
	RotateMotor(OUT_A, -10, 72);
	Wait(MS_500);
	reset_arm();
	
	// Start driving to second lever
	RotateMotor(OUT_BC, -20, convert_cm(15));
	turn_left();
	RotateMotor(OUT_BC, 15, convert_cm(10));
	turn_right();
	RotateMotor(OUT_BC, 20, convert_cm(15));
		
	// Start lever up
	RotateMotor(OUT_A, -20, 80);
	Wait(MS_500);
	reset_arm();

	// Move away from obstacles
	RotateMotor(OUT_BC, -20, convert_cm(15));
	
	// Shutdown motors
	Off(OUT_ALL);
}

/*
 * function: reset_arm()
 * Resets the arm to its downright position
 */
void reset_arm() {
	OnRevReg(OUT_A, 25);
	Wait(MS_500);
	Off(OUT_A);
}


/*
 * Function: convert_cm(<amount of cm>)
 * Converts a given amount of cm to wheel degrees
 */
int convert_cm(int amount) {
	const int degrees = 20;
	int retval;

	retval = amount * degrees;

	return retval;
}

/*
 * function: turn_left()
 * Will turn the bot 90deg left
 */
void turn_left() {
	OnFwdReg(OUT_C, 25);
	OnRevReg(OUT_B, 25);
	Wait(MS_700);
	Wait(MS_50);
	Off(OUT_BC);
}

/*
 * function: turn_right()
 * Will turn the bot 90deg right
 */
void turn_right() {
	OnFwdReg(OUT_B, 25);
	OnRevReg(OUT_C, 25);
	Wait(MS_700);
	Wait(MS_50);
	Off(OUT_BC);
}

/*
 * function: dance()
 * will make the bot party 
 */
void dance() {
	
	// Turning
	turn_left();
	turn_right();
	turn_right();
	turn_left();
	
	// Arm
	RotateMotor(OUT_A, -100, 70);
	RotateMotor(OUT_A, -100, 35);
	RotateMotor(OUT_A, 100, 35);
	RotateMotor(OUT_A, -100, 35);
	reset_arm();

	// Sound
	PlaySound(SOUND_UP);
	PlaySound(SOUND_CLICK);
	PlaySound(SOUND_DOUBLE_BEEP);
	PlaySound(SOUND_FAST_UP);
	StopSound();
}

