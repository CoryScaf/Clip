#include "Clip.hpp"
#include <iostream>
#include <limits>
int main()
{
	CPpconsole console = cpCreateConsole( "Water Sheep", "%z" );
	CPpstring str = cpCreateString( "HALLOW" );
	cpConsoleLogTrace( console, "TRACE TEST" );
    cpConsoleLogInfo( console, "INFO TEST" );
    cpConsoleLogWarning( console, "WARNING TEST" );
	cpConsoleLogError( console, "ERROR TEST" );
    cpConsoleLogFatal( console, "FATAL TEST" );
	cpDeleteConsole( console );
	return 0;
}
