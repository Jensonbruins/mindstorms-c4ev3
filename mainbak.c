#include "ev3.h"

void left();
void turn_drive(int motor_a, int motor_b,int change_speed);
void right();

int main() {
	
	InitEV3();

	setAllSensorMode(GYRO_ANG, NO_SEN, NO_SEN, NO_SEN);
	
	left();
//	right();
	Off(OUT_BC);
	
	FreeEV3();
	
	return 0;
}

void right() {
	int gyro_value, gyro_offset, gyro_check_one, gyro_check_two, gyro_check_three, gyro_check_four;

	gyro_offset = readSensor(IN_1);
	gyro_check_one = 30;
	gyro_check_two = 60;
	gyro_check_three = 80;
	gyro_check_four = 89;

	while(1)
	{
		gyro_value = readSensor(IN_1) - gyro_offset;

		if (gyro_value == 0) {
			turn_drive(OUT_B,OUT_C,15);
		} else if (gyro_value >= gyro_check_one && gyro_value < gyro_check_two) {
			turn_drive(OUT_B,OUT_C,10);
		} else if (gyro_value >= gyro_check_two && gyro_value < gyro_check_three) {
			turn_drive(OUT_B,OUT_C,5);	
		} else if (gyro_value >= gyro_check_four) {
			turn_drive(OUT_B, OUT_C, 0);
			break;
		}
		Wait(MS_100);
	}
	Wait(SEC_1);
}


void left() {
	int gyro_value, gyro_offset, gyro_check_one, gyro_check_two, gyro_check_three, gyro_check_four;

	gyro_offset = readSensor(IN_1);
	gyro_check_one = -30;
	gyro_check_two = -60;
	gyro_check_three = -80;
	gyro_check_four = -89;

	while(1)
	{
		gyro_value = readSensor(IN_1) - gyro_offset;

		//  0 == 0
		if (gyro_value == 0) {
			turn_drive(OUT_C,OUT_B,15);
		} else if (gyro_value <= gyro_check_one && gyro_value > gyro_check_two) {
			turn_drive(OUT_C,OUT_B,12);
		} else if (gyro_value <= gyro_check_two && gyro_value > gyro_check_three) {
			turn_drive(OUT_C,OUT_B,3);	
		} else if (gyro_value <= gyro_check_four) {
			turn_drive(OUT_B, OUT_C, 0);
			break;
		}
		Wait(MS_100);
	}
	Wait(SEC_1);
}

void turn_drive(int motor_a, int motor_b ,int change_speed) {
	OnFwdReg(motor_a, change_speed);
	OnRevReg(motor_b, change_speed);
}
