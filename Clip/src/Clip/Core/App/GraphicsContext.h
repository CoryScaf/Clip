#ifndef CP_GRAPHICSAPI_H_
#define CP_GRAPHICSAPI_H_

#include "Clip/Core/Core.h"
#include <string.h>
#ifdef CP_PLATFORM_WINDOWS
#include <Windows.h>
#elif defined( CP_PLATFORM_LINUX )

#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CP_API_VULKAN

#include <vulkan/vulkan.h>

typedef struct tagCPgraphicsContextVK
{
	VkInstance instance;
	VkPhysicalDevice physDevices[16];
	VkSurfaceKHR surface;
} CPgraphicsContext, CPgraphicsContextVK;

CP_API CPgraphicsContextVK* cpCreateGraphicsContextVK( const char* app_name, unsigned int app_version );
CP_API void cpFreeGraphicsContextVK( CPgraphicsContextVK* context );
#ifdef CP_PLATFORM_WINDOWS
CP_API void cpLinkGraphicsContextVK( HWND hWnd );
#elif defined( CP_PLATFORM_LINUX )

#endif

#elif defined( CP_API_OPENGL )

typedef struct tagCPgraphicsContextGL
{
	
} CPgraphicsContext, CPgraphicsContextGL;

#elif defined( CP_API_DIRECTX )

typedef struct tagCPgraphicsContextDX
{

} CPgraphicsContext, CPgraphicsContextDX;

#endif

CP_API CPgraphicsContext* cpCreateGraphicsContext();
CP_API void cpFreeGraphicsContext( CPgraphicsContext* context );

#ifdef __cplusplus
}
#endif

#endif