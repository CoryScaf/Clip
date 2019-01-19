#include "Clip.hpp"
#include <iostream>

int main()
{
	CPwindow* window = cpCreateWindow( L"Test Window", 1280, 720 );

	while( cpGetLastEvent().type != CP_EVENT_WINDOW_CLOSE )
	{
		std::cout << cpGetLastEvent().type << std::endl;
		cpPollEvents();
	}
	return 0;
}