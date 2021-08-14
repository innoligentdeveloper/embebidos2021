//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "main_core.h"
#include "temperature_sensor.h"
#include "amper_sensor.h"

#include "display.h"
#include "GLCD_clear_screen.h"

//=====[Declaration of private defines]======================================

#define DISPLAY_REFRESH_TIME_REPORT_MS 1000
#define DISPLAY_REFRESH_TIME_ALARM_MS 300

//=====[Declaration of private data types]=====================================

typedef enum {
    DISPLAY_ALARM_STATE,
    DISPLAY_REPORT_STATE
} displayState_t;

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============
int estadoEsterilizador;
const char* status;
static displayState_t displayState = DISPLAY_REPORT_STATE;
static int displayRefreshTimeMs = DISPLAY_REFRESH_TIME_REPORT_MS;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();
static void userInterfaceDisplayReportStateInit();
static void userInterfaceDisplayReportStateUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    userInterfaceDisplayUpdate();
}

void setEstadoEsterilizador( int estadoActual )
{
    estadoEsterilizador=estadoActual;
}

int getEstadoEsterilizador()
{
    return estadoEsterilizador;
}
const char* getEstadoEsterilizadorStr()
{
    int estadoInt=getEstadoEsterilizador();
    if (estadoInt==0){
        status="HEATING";    
    }else{
        if (estadoInt==1){
            status="ON DUTY";    
        }else{
            if (estadoInt==2){
                status="COOLING";    
            }else{
                if (estadoInt==3){
                    status="BROKEN!!";    
                }
            }
        }
    }
    return status;
}

static void userInterfaceDisplayReportStateInit()
{
    displayState = DISPLAY_REPORT_STATE;
    displayRefreshTimeMs = DISPLAY_REFRESH_TIME_REPORT_MS;

    displayModeWrite( DISPLAY_MODE_CHAR );

    displayClear();

    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "ESTERILIZADOR" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Temp. Agua: " );

    displayCharPositionWrite ( 0,2 );
    displayStringWrite( "Amperaje:" );
    
    displayCharPositionWrite ( 0,3 );
    displayStringWrite( "Estado:" );
}

static void userInterfaceDisplayReportStateUpdate()
{
    char temperatureString[2];
    char ampersString[4];
    sprintf(ampersString, "%.1f", amperSensorRead());
    sprintf(temperatureString, "%.0f", temperatureSensorReadCelsius());
    displayCharPositionWrite ( 12,1 );
    displayStringWrite( temperatureString );
    displayCharPositionWrite ( 14,1 );
    displayStringWrite( "'C" );
    displayCharPositionWrite ( 10,2 );
    displayStringWrite( ampersString );
    displayCharPositionWrite ( 14,2 );
    displayStringWrite( " A" );
    displayCharPositionWrite ( 8,3 );
    displayStringWrite( getEstadoEsterilizadorStr() );
}

static void userInterfaceDisplayInit()
{
    displayInit( DISPLAY_TYPE_GLCD_ST7920, DISPLAY_CONNECTION_SPI );
    userInterfaceDisplayReportStateInit();
}
static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;

    if( accumulatedDisplayTime >=
        displayRefreshTimeMs ) {

        accumulatedDisplayTime = 0;

        userInterfaceDisplayReportStateUpdate();
//        switch ( displayState ) {
//        case DISPLAY_REPORT_STATE:
  //          userInterfaceDisplayReportStateUpdate();

    //        if ( alarmStateRead() ) {
//                userInterfaceDisplayAlarmStateInit();
//            }
//            break;

  //      case DISPLAY_ALARM_STATE:
//            userInterfaceDisplayAlarmStateUpdate();

//            if ( !alarmStateRead() ) {
////                userInterfaceDisplayReportStateInit();
//            }
//            break;

//        default:
  //          userInterfaceDisplayReportStateInit();
//            break;
  //      }

    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;
    }
}
