#include "MsgBase.h"
#include "MsgBusBase.h"


CMsgBase::CMsgBase(CSingletonMsgBus* pIns)
{
	if (pIns)
	{
		m_pSingletonMsgBus = pIns;
	}
}

CMsgBase::~CMsgBase()
{
	Remove();
}

void CMsgBase::SetMsgName(string name)
{
	if (name != m_strMsgName && !name.empty())
	{
		m_strMsgName = name;
		Register();

	}
}


bool CMsgBase::SendMsg(string& dstMsgName)
{
	if (!dstMsgName.empty())
	{
		return m_pSingletonMsgBus->SendMsg(dstMsgName, this);
	}

	return false;
}


void CMsgBase::Parse(CMsgBase* pMsg, CMsgBase* dstMsg)
{
	if (pMsg && dstMsg)
	{
		dstMsg->ParseMsg(pMsg);
	}

}

void CMsgBase::Register()
{
	m_pSingletonMsgBus->RegisterMsg(m_strMsgName, this);
}

void CMsgBase::Remove()
{
	m_pSingletonMsgBus->RemoveMsg(m_strMsgName);
}
