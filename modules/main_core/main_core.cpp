//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "main_core.h"
#include "temperature_sensor.h"
#include "amper_sensor.h"
#include "relay.h"
#include "user_interface.h"
#include "pc_serial_com.h"

Timer timer;
float tempAnterior;
float deltaTemp;
bool flagOnDuty;

void systemInit()
{
    userInterfaceInit();
    temperatureSensorInit();
    amperSensorInit();
    relayInit();
    pcSerialComInit();
    
    timer.start();
    tempAnterior=temperatureSensorReadCelsius();
    flagOnDuty=false;
}

void systemUpdate()
{
    userInterfaceUpdate();
    temperatureSensorUpdate();
    amperSensorUpdate();
    pcSerialComUpdate();
    relayUpdate();
    
    if (timer.read()>=20.0)
    {
        if (!flagOnDuty)
        {
            deltaTemp = tempAnterior - temperatureSensorReadCelsius();
            if ( deltaTemp <= 2.0 )
            {
                setEstadoEsterilizador( 3 );
                turnOffRelay();
            }
            if ( tempBetweenSetting() ){
                timer.stop();
                flagOnDuty=true;
            }
        }
    }
    
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
