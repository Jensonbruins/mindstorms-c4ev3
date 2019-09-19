#include "ev3.h"

int main()
{
	// Initialize EV3 lib
	InitEV3();

	// Reset arm to zero for program
	reset_arm();
	
	// Rotatemotor (62cm) from base to crane
	
	// Start driving to first lever
	RotateMotor(OUT_BC, 25, convert_cm(30));
	turn_right();
	RotateMotor(OUT_BC, 15, convert_cm(10));
	turn_left();
	RotateMotor(OUT_BC, 25, convert_cm(32));
	// End driving to first lever
	
	// Start lever up
	RotateMotor(OUT_A, -10, 72);
	Wait(MS_100);
	reset_arm();
	// End lever up
	
	// Start driving to second lever
	RotateMotor(OUT_BC, -25, convert_cm(15));
	turn_left();
	RotateMotor(OUT_BC, 15, convert_cm(10));
	turn_right();
	RotateMotor(OUT_BC, 25, convert_cm(15));
	// End driving to second lever
		
	// Start lever up
	RotateMotor(OUT_A, -25, 80);
	Wait(MS_100);
	reset_arm();
	// End lever up
	
	RotateMotor(OUT_BC, -25, convert_cm(15));
	Off(OUT_ALL);

	dance();

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

void turn_left() {
	OnFwdReg(OUT_C, 25);
	OnRevReg(OUT_B, 25);
	Wait(MS_700);
	Wait(MS_50);
	Off(OUT_BC);
}

void turn_right() {
	OnFwdReg(OUT_B, 25);
	OnRevReg(OUT_C, 25);
	Wait(MS_700);
	Wait(MS_50);
	Off(OUT_BC);
}

void dance() {
	OnFwdReg(OUT_B, 25);
	OnRevReg(OUT_C, 25);
	Wait(MS_200);
	Off(OUT_BC);
	
	SetLedPattern(LED_GREEN);

	RotateMotor(OUT_A, -25, 80);
	reset_arm();

	SetLedPattern(LED_RED);
	
	PlaySound(SOUND_LOW_BEEP);

	RotateMotor(OUT_A, -25, 80);
	reset_arm();

	SetLedPattern(LED_GREEN_PULSE);
	Wait(MS_50);
	SetLedPattern(LED_RED_PULSE);
	
	OnFwdReg(OUT_C, 25);
	OnRevReg(OUT_B, 25);
	Wait(MS_200);
	Off(OUT_BC);

	SetLedPattern(LED_ORANGE);

	RotateMotor(OUT_A, -25, 80);
	reset_arm();

	PlaySound(SOUND_DOWN);
	PlaySound(SOUND_UP);
	PlaySound(SOUND_DOUBLE_BEEP);
	PlaySound(FAST_UP);
	
	RotateMotor(OUT_A, -25, 80);
	reset_arm();
	
}
