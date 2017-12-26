#include "MsgBusBase.h"


void CSingletonMsgBus::RegisterMsg(string& strMsgName,  CMsgBase* pMsg)
{
	m_map.insert(std::make_pair(strMsgName , pMsg));
	m_bus.Attach<CMsgBase*, CMsgBase*>(strMsgName, &CMsgBase::Parse, pMsg);
}

void CSingletonMsgBus::RemoveMsg(string & strMsgName)
{
	if (m_map.find(strMsgName) == m_map.end())
	{
		return;
	}
	m_map.erase(strMsgName);
	m_bus.Remove<CMsgBase*, CMsgBase*>(strMsgName);
}


bool CSingletonMsgBus::SendMsg(string & dstName, CMsgBase * pMsg)
{
	if (dstName.empty() || pMsg == NULL)
	{
		return false;
	}
	std::multimap<string, CMsgBase*>::iterator iter = m_map.find(dstName);
	if (iter != m_map.end())
	{
		CMsgBase* dst = iter->second;
		m_bus.SendReq(dstName, pMsg, dst);
		return true;
	}
	return false;
}
