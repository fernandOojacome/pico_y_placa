/*
This program predicts whether or not a car with a given licence plate
and at a given time can be out on the road from Monday to Friday
according to Pico y Placa restriction in Quito, Ecuador
*/

#include <stdio.h>

int checkPlate(int plateNum);
int checkDate(char *d);
int checkTime(int hour, int minute);
void checkRestriction(int dayNum, int plateNum);
void allowedOut(void);
void notAllowedOut(void);

int main (void){
	int i = 0;
	int plateNumber = 0;
	int plateDigit = 0;
	int time_h = 0;
	int time_m = 0;
	int time = 0;
	char day[10];
	int dayNumber = 0;

	//Input plate number is stored as integer in variable plateNumber

	printf("\nEnter 4 digits of plate number:\nOnly enter the digits not the letters.\n\n");
	scanf("%d",&plateNumber);

	//Check if input plate number is not negative, zero or greater than 9999
	//Only last digit is kept from plate number in plateDigit
	//If plate number is not valid it is assigned a value of 10 which will terminate the program

	plateDigit = checkPlate(plateNumber);
	if (plateDigit == 10) {
		printf("Invalid plate number!\n");
		return 0;
	}

	//Input day is stored as a String in variable day

	printf("\nEnter, from Monday to Friday, the day in which the car will go out:\n\n");
	scanf("%s",day);

	//Assign a number to the day entered from 1 to 5, 0 is used to assign Saturday and Sunday
	//If day name is not valid it is assigned a value of 10 which will terminate the program

	dayNumber = checkDate(day);
	if (dayNumber == 10) {
		printf("Invalid day!\n");
		return 0;
	}

	//Input hour and minutes are stored in variables time_h and time_m respectively

	printf("\nEnter the time for the car to go out in 24 hour format:\nEnter first the hour, then enter the minutes.\n\n");
	scanf("%d%d",&time_h,&time_m);

	//Check if hours and minutes are valid
	//If time is not valid it is assigned a value of 5000 which will terminate the program

	time = checkTime(time_h,time_m);
	if (time == 5000) {return 0;}

	printf("\nOn a %s, at %02d:%02d, a car with plate number ending in %d is:\n\n", day, time_h, time_m, plateDigit);

	//Check if the time input is within restriction hours (7:00 - 9:30 and 16:00 - 19:30)

	if ((time >= 700 && time <= 950) || (time >= 1600 && time <= 1950)){

	//Switch case to check whether number plate can go out depending on the day previously assigned to dayNumber

		checkRestriction(dayNumber,plateDigit);

	} else {

		allowedOut();	//If time is outside restriction hours every car is allowed to go out

	}
	
	return 0;	//program ends
}

int checkPlate(int plateNum){

	if ((plateNum <= 0) || (plateNum >= 10000)) {
		return 10;
	}

	return plateNum % 10;	//returns only last digit
}

int checkDate(char *d){

	int dayNumber = 0;

	if (d[0] == 's' || d[0] == 'S'){			//Saturday or Sunday
		dayNumber = 0;
	} else if (d[0] == 'm' || d[0] == 'M'){		//Monday
		dayNumber = 1;
	} else if (d[1] == 'u' || d[1] == 'U'){		//Tuesday
		dayNumber = 2;
	} else if (d[0] == 'w' || d[0] == 'W'){		//Wednesday
		dayNumber = 3;
	} else if (d[1] == 'h' || d[1] == 'H'){		//Thursday
		dayNumber = 4;
	} else if (d[0] == 'f' || d[0] == 'F'){		//Friday
		dayNumber = 5;
	} else {									//Anything else is invalid
		return 10;
	}

	return dayNumber;
}

int checkTime(int hour, int minute){

	if (hour > 23 || hour < 0){
		printf("Invalid hour!\n");
		return 5000;
	}

	if (minute > 59 || minute < 0){
		printf("Invilid minutes!\n");
		return 5000;
	}

	return 100 * hour + (100 * minute / 60);
}

void checkRestriction(int dayNum, int plateNum){

	//Switch case to check whether number plate can go out depending on the day previously assigned to dayNumber

	switch (dayNum){

			case 0: allowedOut();								//No restriction on weekends
					break;

			case 1: if (plateNum == 1 || plateNum == 2){		//Restriction to 1 and 2 on Monday
						notAllowedOut();
					} else {
						allowedOut();
					}
					break;

			case 2: if (plateNum == 3 || plateNum == 4){		//Restriction to 3 and 4 on Tuesday
						notAllowedOut();
					} else {
						allowedOut();
					}
					break;

			case 3: if (plateNum == 5 || plateNum == 6){		//Restriction to 5 and 6 on Wednesday
						notAllowedOut();
					} else {
						allowedOut();
					}
					break;

			case 4: if (plateNum == 7 || plateNum == 8){		//Restriction to 7 and 8 on Thursday
						notAllowedOut();
					} else {
						allowedOut();
					}
					break;

			case 5: if (plateNum == 9 || plateNum == 0){		//Restriction to 9 and 0 on Friday
						notAllowedOut();
					} else {
						allowedOut();
					}
					break;
		}
}

void allowedOut(void){
	printf("ALLOWED TO GO OUT\n\n");
}

void notAllowedOut(void){
	printf("NOT ALLOWED TO GO OUT\n\n");
}