#include "constants.h"

int x_0;
int y_0;
int z_0;

unsigned int BOARD_SIZE = 100;
unsigned int ACCEL_POLL_TIME_INT = DEFAULT_SYSTEM_CLOCK / 100;
double TIME_INT_S = 0.01;
unsigned int TOTAL_WAYPOINTS = 1;
float DIV_CONST = 1000;
float FUEL_LOSS = 0.0001;
float TIME_UNIT = 0.01;

unsigned int GREEN_LED_DELAY = DEFAULT_SYSTEM_CLOCK * 3;
unsigned int BLUE_LED_DELAY = DEFAULT_SYSTEM_CLOCK / 2;
unsigned int BLUE_LED_DELAY_BASE = DEFAULT_SYSTEM_CLOCK / 10;
unsigned int RED_LED_DELAY = 0;


int toggled = 0;

int calc_flash_delay(int percentage) {
	int new_time = BLUE_LED_DELAY * percentage;
	return new_time > BLUE_LED_DELAY_BASE ? new_time : BLUE_LED_DELAY_BASE;
}