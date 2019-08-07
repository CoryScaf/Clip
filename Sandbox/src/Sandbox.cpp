#define NOMINMAX
#include "Clip.hpp"
#include <iostream>
#include <limits>
int main()
{
	CPpconsole console = cpCreateConsole( "Water Sheep", "%z", CP_CONSOLE_PARSE_PRINTF_STYLE );
	CPpstring str = cpCreateString( "HALLOW" );
	cpConsoleLogTrace( console, "INT, CHAR* TEST: %+d, %s", -23, str );
	cpConsoleLogError( console, "One Two Three" );
	cpDeleteConsole( console );
	return 0;
}
