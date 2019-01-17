#include "Clip.hpp"
#include <iostream>

int main()
{
	CLPwindow* window = clpCreateWindow( L"Test Window", 1280, 720 );

	while( clpGetLastEvent().type != CLP_EVENT_WINDOW_CLOSE )
	{
		std::cout << clpGetLastEvent().type << std::endl;
		clpPollEvents();
	}
	return 0;
}