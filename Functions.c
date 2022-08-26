/*
 * Functions.c
 *
 *  Created on: Aug 20, 2022
 *      Author: Omar Anwar
 */
#include <stdio.h>
#include "Functions.h"
// Definition to switch between the cases of vehicles whether the temperature controller exists.
#define WITH_ENGINE_TEMP_CONTROLLER 1


char choice; //Global variable to save the choice each step.

// state initializing
#if WITH_ENGINE_TEMP_CONTROLLER
STATE state = {
		.speed = 35.0,
		.roomTemp = 25.0,
		.engineTemp = 80.0,
		.Engine_State = ON,
		.AC_State = OFF,
		.EngineTemperature_ControllerState = OFF
};
#else
//initialization of the state of a vehicle without temperature controller.
STATE state = {
		.speed = 35.0,
		.roomTemp = 25.0,
		.engineTemp = 80.0,
		.Engine_State = ON,
		.AC_State = OFF,
};
#endif

// the start menu of the application.

void VehicleControlSystem(){

	printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n\n");
	fflush(stdout);
	scanf(" %c", &choice);

	switch (choice){
	case 'a':
		Sensors_SetMenu(); // this action leads to choose the system needed to change of the sensors.
		break;

	case 'b':
		printf("Turn off the vehicle engine\n\n");
		VehicleControlSystem();
		break;

	case 'c':
		// Break the system down.
		printf("Quit the system\n\n");
		break;

	default:
		// if the user chose an undefined choice.
		printf("Undefined choice");
		VehicleControlSystem();
		break;
	}

}

void Sensors_SetMenu(){

	printf("a. Turn off the engine.\nb. Set the traffic light color.\nc. Set the room temperature (Temperature Sensor)\n");

#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d. Set the engine temperature (Engine Temperature Sensor).\n");
#endif

	printf("\n");
	fflush(stdout);
	scanf("\n %c", &choice);

	switch (choice){
	case 'a':
		VehicleControlSystem();
		break;

	case 'b':
		printf("Set the traffic light color\n\n");
		fflush(stdout);
		scanf(" %c", &choice);
		trafficLight_Data(&choice);
		break;

	case 'c':
		printf("Set the room temperature\n\n");
		fflush(stdout);
		scanf(" %f", &state.roomTemp);
		if (state.roomTemp < 10.0 || state.roomTemp > 30.0) {
			state.AC_State = ON;
			state.roomTemp = 20.0;
		}
		else {
			state.AC_State = OFF;
		}
		displayData();
		break;



#if WITH_ENGINE_TEMP_CONTROLLER
	case 'd':
		printf("Set the engine temperature\n\n");
		fflush(stdout);
		scanf(" %f", &state.engineTemp);
		if (state.engineTemp < 100.0 || state.engineTemp > 150.0) {
			state.EngineTemperature_ControllerState = ON;
			state.engineTemp = 125.0;
		}
		else {
			state.EngineTemperature_ControllerState = OFF;
		}
		displayData();
		break;
#endif



	default:
		printf("Undefined choice");
		Sensors_SetMenu();
		break;
	}

}

void trafficLight_Data (char* color){

	switch (*color) {
	case 'g':
	case 'G':
		state.speed = 100;
		displayData();
		break;

	case 'o':
	case 'O':
		state.speed = 30;
		displayData();
		break;

	case 'r':
	case 'R':
		state.speed = 0;
		displayData();
		break;

	default:
		printf("Undefined choice");
		fflush(stdout);
		Sensors_SetMenu();
		break;
	}

}

void CheckSpeed(){
	if (state.speed == 30.0) {
		// For AC and Room temperature.
		state.AC_State = 1;
		state.roomTemp = ((state.roomTemp)*(5.0/4))+1.0;


		// For Engine and Engine temperature.
#if WITH_ENGINE_TEMP_CONTROLLER
		state.EngineTemperature_ControllerState = ON;
		state.engineTemp = (state.engineTemp)*(5.0/4)+1;
#endif


	}

}

void displayData(){
	CheckSpeed(); // To check the speed before displaying the current state.

	// for displaying engine state.
	if (state.Engine_State) {

		printf("Engine is ON\n");
	}
	else {
		printf("Engine is OFF\n");
	}

	// for displaying AC state.
	if (state.AC_State) {
		printf("AC is ON\n");
	}
	else {
		printf("AC is OFF\n");
	}

	printf("VehCile Speed: %f Km/Hr\n", state.speed);
	printf("Room Temperature: %f degree C\n", state.roomTemp);
#if WITH_ENGINE_TEMP_CONTROLLER
	if (state.EngineTemperature_ControllerState) {
		printf("Engine Temperature Controller is ON\n");

	}
	else {
		printf("Engine Temperature Controller is OFF\n");
	}
	printf("Engine Temperature: %f degree C\n", state.engineTemp);
#endif
	printf("\n");
	fflush(stdout);
	Sensors_SetMenu(); //Reasking the user for more feature to test.
}


