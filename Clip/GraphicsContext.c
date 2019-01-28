#include "Clip/Core/App/GraphicsContext.h"
#include "Clip/Core/Logging/Console.h"

#ifdef CP_API_VULKAN

CP_API CPgraphicsContextVK* cpCreateGraphicsContextVK( const char* app_name, unsigned int app_version )
{
	CPgraphicsContextVK* context = malloc( sizeof( CPgraphicsContextVK ) );
	memset( context, 0, sizeof( CPgraphicsContextVK ) );

	VkApplicationInfo appInfo ={ 0 };
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = app_name;
	appInfo.applicationVersion = app_version;
	appInfo.pEngineName = "Clip Engine";
	appInfo.engineVersion = VK_MAKE_VERSION( 0, 1, 0 );
	appInfo.apiVersion = VK_API_VERSION_1_1;

	VkInstanceCreateInfo ici ={ 0 };
	ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ici.pApplicationInfo = &appInfo;

#ifdef CP_DEBUG
	const char* debugLayers[] =
	{
		"VK_LAYER_LUNARG_standard_validation"
	};

	ici.ppEnabledLayerNames = debugLayers;
	ici.enabledLayerCount = sizeof( debugLayers ) / sizeof( debugLayers[0] );
#endif

	const char* extensions[] =
	{
		"VK_KHR_SURFACE_EXTENSION_NAME"
	};
	ici.ppEnabledExtensionNames = extensions;
	ici.enabledExtensionCount = sizeof( extensions ) / sizeof( extensions[0] );

	int code = vkCreateInstance( &ici, 0, &context->instance );
	if( code != VK_SUCCESS )
		CP_CORE_LOG_FATAL( "Failed Vulkan Instance Creation: %i", code );

	uint32_t physicalDeviceCount = sizeof( context->physDevices ) / sizeof( context->physDevices[0] );

	code = vkEnumeratePhysicalDevices( context->instance, physicalDeviceCount, context->physDevices );
	if( code != VK_SUCCESS )
		CP_CORE_LOG_FATAL( "Failed Vulkan Instance Creation: %i", code );
}

#elif defined( CP_API_OPENGL )

#elif defined( CP_API_DIRECTX )

#endif