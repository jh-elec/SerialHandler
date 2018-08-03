#include <windows.h>
#include <stdio.h>
#include <stdint.h>
 
char *serialInit( HANDLE hSerial , char *portName , char *baud )
{
	// Declare variables and structures
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};	
	
	char pName[15] = "\\\\.\\COM";
	strcat( pName , portName );
          
    hSerial = CreateFile( pName , GENERIC_READ | GENERIC_WRITE , 0 , NULL , OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );
    
	if ( hSerial == INVALID_HANDLE_VALUE )
    {
        return NULL;
    }
    
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (GetCommState(hSerial, &dcbSerialParams) == 0)
    {
    	CloseHandle(hSerial);
        return NULL;
    }
     
    uint32_t baudrate = atoi( baud );
    if ( baudrate < 110 || baudrate > 256000 )
    {
    	baudrate = 9600;
    	return NULL;
	}
     
    dcbSerialParams.BaudRate = CBR_38400;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if(SetCommState(hSerial, &dcbSerialParams) == 0)
    {
        CloseHandle(hSerial);
        return NULL;
    }
 
    // Set COM port timeout settings
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    
	if(SetCommTimeouts(hSerial, &timeouts) == 0)
    {
    	CloseHandle(hSerial);
        return NULL;
    }
}

char *serialWrite( HANDLE hSerial , char *stream )
{
    DWORD bytes_written, total_bytes_written = 0;
    fprintf(stderr, "Sending bytes...\r\n");
    
    if( !WriteFile(hSerial, stream , strlen( stream ) , &bytes_written , NULL ) )
    {
        CloseHandle(hSerial);
        return "Konnte den Port nicht oeffnen\r\n";
    }   
    fprintf(stderr, "%d bytes written\r\n", bytes_written);
}
 
char *serialClose( HANDLE hSerial ) 
{	
    if (CloseHandle(hSerial) == 0)
    {
        return "Serieller Port konnte nicht geschlossen werden!\r\n";
    }
    else
    {
    	return "Serieller Port geschlossen!\r\n";
	}
	
    return NULL;	
}

const char *header[] =
{
	"\r\n",
	"/*******************************************************\r\n",
	"* Serial Port Handling by J.H - Elec\r\n",
	"* arg[0] = Portnummer\r\n",
	"* arg[1] = Baudrate\r\n",
	"* arg[2] = Daten die Gesendet werden sollen (ASCII)\r\n",	
	"/*******************************************************\r\n",
};
const headerSize = sizeof( header) / sizeof( *header );

void showHeader( void )
{
	uint8_t x;
	for ( x = 0 ; x < headerSize ; x++ )
	{
		printf( header[x] );
	}
}

/*
*	arg:		Anzahl der Argumente
*	argv[0]: 	Portnummer
*	argv[1]:	Baudrate
*	argv[2]:	Stream der gesendet werden soo
*/
int main( int arg , char *argv[] )
{

    HANDLE hSerial;	
	
	showHeader();
	
	printf( "\r\n" );
	printf( "SerialPort : COM%s\r\n" , argv[1] );
	printf( "SerialPort : %s Baud\r\n" , argv[2] );

	char *handlePtr = serialInit( hSerial , argv[1] , argv[2] );

	if ( handlePtr == NULL )
	{
		printf( "SerialPort : Konnte nicht initalisiert werden..\r\n\n" );
		printf( "***Serial Port Handling by Hm***\r\n");
		exit(0);
	}

	printf("\r\n");
	printf( "/*********************************\r\n" );
	printf( "SerialPort    : " );
	serialWrite( hSerial , argv[3] );
	printf( "Gesendet      : %s\r\n" , argv[3] );
	printf( "SerialPort    : %s\r\n" , serialClose( hSerial ) );
	printf( "/*********************************\r\n" );
	
	printf("\r\n");	
	
	system( "pause" );

    return 0;
}
