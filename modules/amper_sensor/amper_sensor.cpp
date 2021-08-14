//=====[Libraries]=============================================================

#include "mbed.h"

#include "main_core.h"

#include "SCT_013_000.h"

//=====[Declaration of private defines]======================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============
float Irms = 0.0;
SCT013000 sen_amp(A0);

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void amperSensorInit()
{
//	SCT013000 sen_amp(A0);
}

void amperSensorUpdate()
{
    Irms= sen_amp.current();
}

float amperSensorRead(){
	return Irms;
}