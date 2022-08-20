/*
 * FunctiONs.h
 *
 *  Created ON: Aug 20, 2022
 *      Author: Anwar
 */


typedef struct {
	enum States{
		OFF = 0, ON
	}Engine_State, AC_State, EngineTemperature_ControllerState;

	float speed;

	float roomTemp;

	float  engineTemp;
}STATE;

void VehicleControlSystem(); //Project cONstructor.

void Sensors_SetMenu(); //FOR Choice 'a' turn ON the engine. --> to open sensors menu.

void trafficLight_Data (char*); // FOR Choice 'b' in sensors menu --> traffic data.

void CheckSpeed(); // To check the speed whenever wanted.

void displayData(); //To display the state
