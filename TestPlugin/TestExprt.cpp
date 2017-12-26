#include "TestExport.h"


static PluginInstance *pPlugin = NULL;

 PluginInstance* StartPlugin(CSingletonMsgBus* pIns, std::string name)
 {

	 if (pIns)
	 {
		 pPlugin = new ShapePlugin(pIns, name);
		 PluginManager::GetInstance().LoadPlugin(pPlugin);

		 return pPlugin;
	 }
	 return NULL;
 }

void StopPlugin()
{
	PluginManager::GetInstance().UnLoadPlugin(pPlugin);

	delete pPlugin;
}