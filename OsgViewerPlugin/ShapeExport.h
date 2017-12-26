#ifndef SHAPEEXPORT_INCLUDE 
#define SHAPEEXPORT_INCLUDE
#include "ShapePlugin.h"
#include "PluginManager.h"

#define EXPORT_API __declspec(dllexport)

class PluginInstance;

extern "C" EXPORT_API PluginInstance *StartPlugin(CSingletonMsgBus* pIns,std::string name);

extern "C" EXPORT_API void StopPlugin();

#endif	