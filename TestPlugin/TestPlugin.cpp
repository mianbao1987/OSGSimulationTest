#include "TestPlugin.h"
#include <iostream>

ShapePlugin::ShapePlugin(CSingletonMsgBus* pIns, const std::string &strName)
	:PluginInstance(pIns,strName)
{
	if (pIns)
	{
		this->m_pMsg = new CMsgOsgViewer(pIns, strName);

	}
	
}

ShapePlugin::~ShapePlugin(void)
{
	if (this->m_pMsg)
	{
		delete m_pMsg;
	}
}

bool ShapePlugin::Load()
{
	return 1;
}

bool ShapePlugin::UnLoad()
{
	return 1;
}

std::string ShapePlugin::GetFileName() const
{
	if (this->m_pMsg != NULL)
	{
		string in = "OsgViewerPlugin";
		this->m_pMsg->SendMsg(in);
	}
	return this->m_strPluginName;
}

std::string ShapePlugin::GetDisplayName() const
{
	return this->m_strPluginName;
}

bool CMsgOsgViewer::ParseMsg(CMsgBase * pSrcMsg)
{
	string tmp1 = this->GetMsgName();
	string tmp2 = pSrcMsg->GetMsgName();
	std::cout << "dst:" << tmp1 << "---" << "src:" << tmp2 << std::endl;
	return false;
}
