#include "PluginInstance.h"

PluginInstance::PluginInstance(CSingletonMsgBus* pIns, const std::string &strName)
{
	if (pIns)
	{
		m_pIns = pIns;
	}
	m_strPluginName = strName;
	
}

PluginInstance::~PluginInstance(void)
{
}

//bool PluginInstance::Load()
//{
//	return false;
//}
//
//bool PluginInstance::UnLoad()
//{
//	return false;
//}
//
//std::string PluginInstance::GetFileName() const
//{
//	return "";
//}
//
//std::string PluginInstance::GetDisplayName() const
//{
//	return "";
//}
