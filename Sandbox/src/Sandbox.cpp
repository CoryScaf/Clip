#include "CPCore.h"
#include "CPCore/App/Window.h"
#include <iostream>
#include <limits>
int main()
{
	CPpconsole console = cpCreateConsole( "TEST_CONSOLE", "%z" );
    if( CP_PLATFORM & CP_PLATFORM_LINUX ) cpConsoleLogInfo( console, "LINUX" );
    if( CP_PLATFORM & CP_API_OPENGL ) cpConsoleLogWarning( console, "OPENGL" );
    if( CP_PLATFORM & CP_PROTOCOL_WAYLAND ) cpConsoleLogError( console, "WAYLAND" );
    else cpConsoleLogFatal( console, "VALUES: %us", CP_PLATFORM );
	CPpstring str = cpCreateString( "HALLOW" );
	cpConsoleLogTrace( console, "TRACE TEST" );
    cpConsoleLogInfo( console, "INFO TEST" );
    cpConsoleLogWarning( console, "WARNING TEST" );
	cpConsoleLogError( console, "ERROR TEST" );
    cpConsoleLogFatal( console, "FATAL TEST" );
	cpDeleteConsole( console );
    //CPwindow* window = cpCreateWindow( L"tittle", 300, 400 );
	return 0;
}
