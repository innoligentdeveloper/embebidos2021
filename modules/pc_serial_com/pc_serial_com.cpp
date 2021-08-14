//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "pc_serial_com.h"
#include "temperature_sensor.h"
#include "amper_sensor.h"
#include "user_interface.h"
#include "date_and_time.h"

//=====[Declaration of private defines]======================================

//=====[Declaration of private data types]=====================================

typedef enum{
    PC_SERIAL_COMMANDS,
    PC_SERIAL_GET_CODE,
    PC_SERIAL_SAVE_NEW_CODE,
} pcSerialComMode_t;

//=====[Declaration and initialization of public global objects]===============

Serial uartUsb(USBTX, USBRX);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of private global variables]============

static pcSerialComMode_t pcSerialComMode = PC_SERIAL_COMMANDS;

//=====[Declarations (prototypes) of private functions]========================
static void pcSerialComCommandUpdate( char receivedChar );
static void availableCommands();
static void commandShowCurrentTemperatureInCelsius();
static void commandShowCurrentIRMS();
static void commandShowStatus();
static void commandSetDateAndTime();
static void commandShowDateAndTime();


void pcSerialComInit()
{
    availableCommands();
}

char pcSerialComCharRead()
{
    char receivedChar = '\0';
    if( uartUsb.readable() ) {
        receivedChar = uartUsb.getc();
    }
    return receivedChar;
}

void pcSerialComStringWrite( const char* str )
{
    uartUsb.printf( "%s", str );
}

void pcSerialComUpdate()
{
    char receivedChar = pcSerialComCharRead();
    if( receivedChar != '\0' ) {
        switch ( pcSerialComMode ) {
            case PC_SERIAL_COMMANDS:
                pcSerialComCommandUpdate( receivedChar );
                break;
            default:
                pcSerialComMode = PC_SERIAL_COMMANDS;
                break;
        }
    }    
}

static void pcSerialComCommandUpdate( char receivedChar )
{
    switch (receivedChar) {
        case 'c': case 'C': commandShowCurrentTemperatureInCelsius(); break;
        case 'a': case 'A': commandShowCurrentIRMS(); break;
        case 'e': case 'E': commandShowStatus(); break;
        case 's': case 'S': commandSetDateAndTime(); break;
        case 't': case 'T': commandShowDateAndTime(); break;
        default: availableCommands(); break;
    } 
}

static void availableCommands()
{
    uartUsb.printf( "Comandos disponibles para el Esterilizador:\r\n" );
    uartUsb.printf( "Presione 'c' para ver la Temperatura del Agua\r\n" );
    uartUsb.printf( "Presione 'a' para ver el Amperaje de la Resistencia\r\n" );
    uartUsb.printf( "Presione 'e' para ver el Estado del Dispositivo\r\n" );  
    uartUsb.printf( "Presione 's' para configurar la Fecha y Hora\r\n" );        
    uartUsb.printf( "Presione 't' para ver la Fecha y Hora\r\n" );  
    uartUsb.printf( "\r\n" );
}

static void commandShowCurrentTemperatureInCelsius()
{
    uartUsb.printf( "Temperatura del agua del Esterilizador: %.2f °C\r\n",
                    temperatureSensorReadCelsius() );    
}
static void commandShowCurrentIRMS()
{
    uartUsb.printf( "Amperaje de la resistencia: %.2f A\r\n",
                    amperSensorRead() );    
}
static void commandShowStatus()
{    
    uartUsb.printf( "Estado del Dispositivo: %s \r\n",
                    getEstadoEsterilizadorStr() );    
}
static void commandSetDateAndTime()
{
    int year   = 0;
    int month  = 0;
    int day    = 0;
    int hour   = 0;
    int minute = 0;
    int second = 0;
    
    uartUsb.printf("\r\nIngrese el año (YYYY) y presione enter: ");
    uartUsb.scanf("%d", &year);
    uartUsb.printf("%d\r\n", year);

    uartUsb.printf("Ingrese el mes (1-12) y presione enter: ");
    uartUsb.scanf("%d", &month);
    uartUsb.printf("%d\r\n", month);

    uartUsb.printf("Ingrese el día (1-31) y presione enter: ");
    uartUsb.scanf("%d", &day);
    uartUsb.printf("%d\r\n", day);

    uartUsb.printf("Ingrese la hora (0-23) y presione enter: ");
    uartUsb.scanf("%d", &hour);
    uartUsb.printf("%d\r\n",hour);

    uartUsb.printf("Ingrese los minutos (0-59) y presione enter: ");
    uartUsb.scanf("%d", &minute);
    uartUsb.printf("%d\r\n", minute);

    uartUsb.printf("Ingrese los segundos (0-59) y presione enter: ");
    uartUsb.scanf("%d", &second);
    uartUsb.printf("%d\r\n", second);
    
    uartUsb.printf("La Fecha y la Hora han sido configuradas correctamente.\r\n");

    while ( uartUsb.readable() ) {
        uartUsb.getc();
    }

    dateAndTimeWrite( year, month, day, hour, minute, second );
}

static void commandShowDateAndTime()
{
    uartUsb.printf("Fecha y Hora = %s \r\n", dateAndTimeRead());
}
