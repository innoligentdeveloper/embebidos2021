//=====[#include guards - begin]===============================================

#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

//=====[Libraries]=============================================================

//=====[Declaration of public defines]=======================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void userInterfaceInit();
void userInterfaceUpdate();
void setEstadoEsterilizador( int estadoActual );
int getEstadoEsterilizador();
const char* getEstadoEsterilizadorStr();

//=====[#include guards - end]=================================================

#endif // _USER_INTERFACE_H_