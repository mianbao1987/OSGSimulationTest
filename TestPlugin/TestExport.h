#ifndef SHAPEEXPORT_INCLUDE 
#define SHAPEEXPORT_INCLUDE
#include "TestPlugin.h"
#include "PluginManager.h"

#define EXPORT_API __declspec(dllexport)

class PluginInstance;

extern "C" EXPORT_API PluginInstance *StartPlugin(CSingletonMsgBus* pIns, std::string name);

extern "C" EXPORT_API void StopPlugin();

#endif	