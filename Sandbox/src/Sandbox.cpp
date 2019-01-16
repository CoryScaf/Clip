#include "Clip.hpp"
#include <iostream>

int main()
{
	_CLwindow* window = clCreateWindow( L"Test Window", 1280, 720 );

	while( clGetLastEvent().type != CL_EVENT_WINDOW_CLOSE )
	{
		std::cout << clGetLastEvent().type << std::endl;
		clPollEvents();
	}
	return 0;
}