//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "relay.h"
#include "main_core.h"
#include "temperature_sensor.h"
#include "user_interface.h"

DigitalOut relayPin(D7);

void relayInit()
{
    relayPin = OFF;
}

void relayUpdate()
{
    if( tempBelowSetting() )
    {
	    relayPin= ON;
	    setEstadoEsterilizador(0);
    } 
    if( tempAboveSetting() ) 
    {
    	relayPin=OFF;
    	setEstadoEsterilizador(2);
    }    
    if( tempBetweenSetting() ) 
    {
    	setEstadoEsterilizador(1);
    }
}

void turnOffRelay()
{
	relayPin=OFF;
}
