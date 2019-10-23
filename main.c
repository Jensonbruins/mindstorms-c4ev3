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

/*
 * Since: 1.0.0
 * main()
 * Everything will be executed from here
 */
int main() {
	// Initializing
	InitEV3();
	setAllSensorMode(GYRO_ANG, TOUCH_PRESS, NO_SEN, NO_SEN);
	reset_arm();

	// Missions
	crane_mission();
    	start_mission();
    	traffic_jam();
    	start_mission();
    	swing();

	// Terminating
	Off(OUT_BC);
	FreeEV3();
    	return 0;
}

/*
 * since: 1.0.0
 * crane_mission()
 * This will execute the crane mission from base when its called
 */
void crane_mission() {
	// Driving towards the first arm of the crane
	forward(28);
	turn_left();
	forward(41);
	
	// Moving the right arm of the crane
	RotateMotor(OUT_A, -10, 88);
	forward(8);
	RotateMotor(OUT_A, 10, 19);
	Wait(MS_500);
	backward(10);
	
	// Resetting the robotarm
	reset_arm();

	// Driving towards the seconds arm of the crane
	turn_left();
	forward(10);
	turn_right();
	forward(8);

	// Moving the right arm of the crane
	RotateMotor(OUT_A, -10, 60);
    	Wait(MS_600);
	reset_arm();

	// Driving back to the base
	backward(60);
}

/*
 * since: 1.1.0
 * traffic_jam()
 * This will execute the crane mission from base when its called
 */
void traffic_jam() {
	// Driving towards the mission
	forward(74);
	turn_right();
	
	// Starting the lifting
	forward(1);
	RotateMotor(OUT_A, -100, 70);
	Wait(MS_500);
    	forward(11);
    	Wait(MS_500);
    	turn_right();
	
	// Driving back to the base
	forward(75);
	reset_arm();
}

/*
 * since: 1.2.0
 * swing()
 * This will execute the swing mission from base when its called
 */
void swing(){
	// Driving towards the mission
	forward(20);
	turn_right();
	forward(150);
	turn_right();

	// Moving the swings arm
	RotateMotor(OUT_A, -100, 70);
	forward(15);
	turn_left();

	// Driving back to the base
	backward(155);
	reset_arm();
}

/*
 * since: 1.0.1
 * reset_arm()
 * Resets the arm to its downright position
 */
void reset_arm() {
	OnRevReg(OUT_A, 25);
	Wait(MS_500);
	Off(OUT_A);
}

/*
 * since: 1.2.1
 * start_mission()
 * Waits for the users input to execute the next mission
 */
void start_mission() {
	// Temporary fix should have a stop button implemented
	// The if statement is useless?
	do {
		if (readSensor(IN_2) == 1) {
			Wait(MS_800);
		}
	} while (readSensor(IN_2) == 0);
}


/*
 * since: 1.0.2
 * convert_cm(<amount in cm>)
 * Converts a given amount of cm to wheel degrees
 */
int convert_cm(int amount) {
	// This value is retrieved from the official legoleague site
	const int degrees = 20;
	int retval;
	
	retval = amount * degrees;

	return retval;
}

/*
 * since: 1.0.1
 * forward(<amount in cm>)
 * This will make the bot drive forwards with a consistent speed when called based on cm
 */
void forward(int amount) {
	amount = convert_cm(amount);
	RotateMotor(OUT_BC, 24, amount);
}

/*
 * since: 1.0.1
 * backward(<amount in cm>)
 * This will make the bot drive backwards with a consistent speed when called based on cm
 */
void backward(int amount) {
	amount = convert_cm(amount);
	RotateMotor(OUT_BC, -15, amount);
}

/*
 * <NOTE>
 * Find a way to combine these two functions together
 * </NOTE>
 */

/*
 * since: 1.0.2
 * turn_right()
 * Will turn the robot right 90 degrees using the gyro sensor
 */
void turn_right() {
	// Declaring alot of values
	int gyro_value, gyro_offset, gyro_check_start_one, gyro_check_start_two, gyro_check_start_three, gyro_check_stop_one, gyro_check_stop_two, gyro_check_stop_three, gyro_check_final;
	
	// Offset value to fix the gyro sensor from doing weird stuff
	gyro_offset = readSensor(IN_1);

	// Creating stop checks (This should be done differently)
	// This is based pure on testing on the board
	gyro_check_start_one = 10;
	gyro_check_start_two = 20;
	gyro_check_start_three = 30;
	gyro_check_stop_one = 60;
	gyro_check_stop_two = 70;
	gyro_check_stop_three = 78;
	gyro_check_final = 87;

	while(1)
	{
		// Creating the gyro_value with offset subtracted
		gyro_value = readSensor(IN_1) - gyro_offset;
		
		// Speeding up and down to make sure the bot doesn't overturn
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

		// The ev3 brick cannot handle too much input so we timer it to make sure it doesn't crash
		Wait(10);
	}
	// Calming the bot down after turning because otherwise driving instantly will offset the bot
	Wait(SEC_1);
}

/*
 * since: 1.0.2
 * turn_left()
 * Will turn left 90 degrees using the gyro sensor
 */
void turn_left() {
	// Declaring alot of values
	int gyro_value, gyro_offset, gyro_check_start_one, gyro_check_start_two, gyro_check_start_three, gyro_check_stop_one, gyro_check_stop_two, gyro_check_stop_three, gyro_check_final;
	
	// Offset the gyro to prevent it from doing weird stuff
	gyro_offset = readSensor(IN_1);

	// Creating stop checks()
	// This is based purely on testing from the FLL board
	gyro_check_start_one = -10;
	gyro_check_start_two = -20;
	gyro_check_start_three = -30;
	gyro_check_stop_one = -60;
	gyro_check_stop_two = -70;
	gyro_check_stop_three = -80;
	gyro_check_final = -86;

	while(1)
	{
		// Creation of gyro value with offset subtracted
		gyro_value = readSensor(IN_1) - gyro_offset;
		
		// Speed up and down to make the perfect turn
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

		// The ev3 brick cannot handle too much data so we timer it to prevent it from crashing
		Wait(10);
	}
	// Calming the bot down after turning because otherwise driving instantly will offset the bot
	Wait(SEC_1);
}

/* 
 * since: 1.0.3
 * turn_drive(<motor forward>, <motor backward>, <speed of motors>)
 * This function is made for the turn functions to prevent copypasta
 */
void turn_drive(int motor_a, int motor_b ,int change_speed) {
	OnFwdReg(motor_a, change_speed);
	OnRevReg(motor_b, change_speed);
}
