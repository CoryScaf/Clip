#define NOMINMAX
#include "Clip.hpp"
#include <iostream>
#include <limits>
int main()
{
	cpInitConsoleApps();
	//CPwindow* window = cpCreateWindow( L"Test Window", 1280, 720 );
	CPconsole* testConsole = cpCreateConsole( "APP-ENGINE-TEST", "%z", CP_CONSOLE_PARSE_PRINTF_STYLE );

	//while( cpGetLastEvent().type != CP_EVENT_WINDOW_CLOSE )
	//{
	//	cpPollEvents();
	//}
	CPsize size = 123;
	CPpstring str = cpCreateString( "HALLOW" );
	double val = 12.455666777888;
	cpConsoleLogError( testConsole, "DOUBLE TEST: %.12lf", val ); // This here produces wrong input
	cpConsoleLogError( testConsole, "FLOAT TEST: %f", 12.11f );	// This is a good time to fix the extra 0's after the two decimals
	cpConsoleLogWarning( testConsole, "INT, CHAR* TEST: %+d, %s", -23, str );
	cpConsoleLogInfo( testConsole, "INDENT TEST %-3ull.", size );

	cpUninitConsoleApps();
	return 0;
}
