
#include "ev3.h"

// Mission declaration
void crane_mission();
void traffic_jam();
void swing();
void start_mission();
// conversions
int convert_cm(int amount);
// Movements for the bot
void reset_arm();
void forward(int amount);
void backward(int amount);
void turn_left();
void turn_right();
void turn_drive(int motor_a, int motor_b,int change_speed);

int main() {
	
	InitEV3();

	setAllSensorMode(GYRO_ANG, TOUCH_PRESS, NO_SEN, NO_SEN);

	reset_arm();

	crane_mission();
    start_mission();
    traffic_jam();
    start_mission();
    swing();

	// Disable everything before shutdown
	Off(OUT_BC);
	FreeEV3();
	

    return 0;
}

/*
 * crane_mission()
 * Runs the crane mission from base
 */
void crane_mission() {
	// Drive towards right arm
	forward(28);
	turn_left();
	forward(41);
	
	// Start right arm
	RotateMotor(OUT_A, -10, 88);
	forward(8);
	RotateMotor(OUT_A, 10, 19);
	Wait(MS_500);
	backward(10);
	
	// Reset arm for next mission
	reset_arm();

	//Drive towards left arm
	turn_left();
	forward(10);
	turn_right();
	forward(8);

	// Start left arm
	RotateMotor(OUT_A, -10, 60);
    Wait(MS_600);
	reset_arm();

	// Drive away from left arm
	backward(60);
}

/*
 * traffic_jam()
 * This will start the traffic mission
 */
void traffic_jam() {
	forward(74);
	turn_right();
	forward(1);
	RotateMotor(OUT_A, -100, 70);
	Wait(MS_500);
    forward(11);
    Wait(MS_500);
    turn_right();
    forward(75);
    reset_arm();
}

void swing(){
    forward(20);
    turn_right();
    forward(150);
    turn_right();
    RotateMotor(OUT_A, -100, 70);
    forward(15);
    turn_left();
    backward(155);
    reset_arm();
}
/*
 * reset_arm()
 * Resets the arm to its downright position
 */
void reset_arm() {
	OnRevReg(OUT_A, 25);
	Wait(MS_500);
	Off(OUT_A);
}

void start_mission() {
    do {
        if (readSensor(IN_2) == 1) {
            Wait(MS_800);
        }
     } while (readSensor(IN_2) == 0);
}

/*
i * convert_cm(<amount of cm>)
 * Converts a given amount of cm to wheel degrees
 */
int convert_cm(int amount) {
	const int degrees = 20;
	int retval;

	retval = amount * degrees;

	return retval;
}

void forward(int amount) {
	amount = convert_cm(amount);
	RotateMotor(OUT_BC, 24, amount);
}

void backward(int amount) {
	amount = convert_cm(amount);
	RotateMotor(OUT_BC, -15, amount);
}

void turn_right() {
	// Declaration for all the variables used
	int gyro_value, gyro_offset, gyro_check_start_one, gyro_check_start_two, gyro_check_start_three, gyro_check_stop_one, gyro_check_stop_two, gyro_check_stop_three, gyro_check_final;
	
	// Create an offset value
	gyro_offset = readSensor(IN_1);

	// Filling stops with values
	gyro_check_start_one = 10;
	gyro_check_start_two = 20;
	gyro_check_start_three = 30;
	gyro_check_stop_one = 60;
	gyro_check_stop_two = 70;
	gyro_check_stop_three = 78;
	gyro_check_final = 87; // 87 is decent
	
	// The loop that does stuff
	while(1)
	{
		// Reading out the gyro value with offset
		gyro_value = readSensor(IN_1) - gyro_offset;
		
		// Based on gyro value do some turn stuff
		if (gyro_value == 0) {
			turn_drive(OUT_B,OUT_C,7);
		} else if (gyro_value >= gyro_check_start_one && gyro_value < gyro_check_start_two) {
			turn_drive(OUT_B, OUT_C, 9);
		} else if (gyro_value >= gyro_check_start_two && gyro_value < gyro_check_start_three) {
			turn_drive(OUT_B, OUT_C, 10);
		} else if (gyro_value >= gyro_check_start_three && gyro_value < gyro_check_stop_one) {
			turn_drive(OUT_B, OUT_C, 12);
		} else if (gyro_value >= gyro_check_stop_one && gyro_value < gyro_check_stop_two) {
			turn_drive(OUT_B,OUT_C,7);
		} else if (gyro_value >= gyro_check_stop_two && gyro_value < gyro_check_stop_three) {
			turn_drive(OUT_B,OUT_C, 5);	
		} else if (gyro_value >= gyro_check_final) {
			Off(OUT_ALL);
			break;
		}

		// This is to prevent the stupid ev3 brick from crashing
		Wait(10);
	}
	// Calm the bot down after turning because it needs it
	Wait(SEC_1);
}


void turn_left() {
	// Declaration for all the variables used
	int gyro_value, gyro_offset, gyro_check_start_one, gyro_check_start_two, gyro_check_start_three, gyro_check_stop_one, gyro_check_stop_two, gyro_check_stop_three, gyro_check_final;
	
	// Create an offset value
	gyro_offset = readSensor(IN_1);

	// Filling stops with values
	gyro_check_start_one = -10;
	gyro_check_start_two = -20;
	gyro_check_start_three = -30;
	gyro_check_stop_one = -60;
	gyro_check_stop_two = -70;
	gyro_check_stop_three = -80;
	gyro_check_final = -86; //ben zeer tevreden wanneer -86
	
	// The loop that does stuff
	while(1)
	{
		// Reading out the gyro value with offset
		gyro_value = readSensor(IN_1) - gyro_offset;
		
		// Based on gyro value do some turn stuff
		if (gyro_value == 0) {
			turn_drive(OUT_C,OUT_B,7);
		} else if (gyro_value <= gyro_check_start_one && gyro_value > gyro_check_start_two) {
			turn_drive(OUT_C, OUT_B, 9);
		} else if (gyro_value <= gyro_check_start_two && gyro_value > gyro_check_start_three) {
			turn_drive(OUT_C, OUT_B, 10);
		} else if (gyro_value <= gyro_check_start_three && gyro_value > gyro_check_stop_one) {
			turn_drive(OUT_C, OUT_B, 12);
		} else if (gyro_value <= gyro_check_stop_one && gyro_value > gyro_check_stop_two) {
			turn_drive(OUT_C,OUT_B,7);
		} else if (gyro_value <= gyro_check_stop_two && gyro_value > gyro_check_stop_three) {
			turn_drive(OUT_C,OUT_B, 5);	
		} else if (gyro_value <= gyro_check_final) {
			Off(OUT_ALL);
			break;
		}

		// This is to prevent the stupid ev3 brick from crashing
		Wait(10);
	}
	// Calm the bot down after turning because it needs it
	Wait(SEC_1);
}


void turn_drive(int motor_a, int motor_b ,int change_speed) {
	OnFwdReg(motor_a, change_speed);
	OnRevReg(motor_b, change_speed);
}
