#pragma once
#include "MsgBus.h"
#include "MsgBase.h"


class CSingletonMsgBus
{
public:
	static CSingletonMsgBus* getInstance()
	{
		static CSingletonMsgBus instance;
		return &instance;
	}
	void RegisterMsg(string& strMsgName, CMsgBase* pMsg);
	void RemoveMsg(string& strMsgName);
	bool SendMsg(string & dstName, CMsgBase * pMsg);
protected:
	struct Object_Creator
	{
		Object_Creator()
		{
			CSingletonMsgBus::getInstance();
		}
	};
	static Object_Creator _object_creator;

	CSingletonMsgBus() {}
	~CSingletonMsgBus() {}

	//int m_nId;
private:
	MessageBus<> m_bus;
	std::multimap<string, CMsgBase*> m_map;

};