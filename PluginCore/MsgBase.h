#pragma once
#include <string>
#include "Export.h"
using namespace std;

class CSingletonMsgBus;
class PLUGINCORE_API CMsgBase
{
	//friend class CSingletonMsgBus;
public:

	CMsgBase(CSingletonMsgBus* pIns);
	virtual ~CMsgBase();
	void SetMsgName(string name);
	bool SendMsg(string& dstMsgName);

	string GetMsgName() { return m_strMsgName; };
	void Parse(CMsgBase* pSrcMsg, CMsgBase* dstMsg);
public:
	virtual bool ParseMsg(CMsgBase* pSrcMsg) = 0;		//子类自行解析协议

private:


	void Register();
	void Remove();
	string m_strMsgName;
	CSingletonMsgBus* m_pSingletonMsgBus;

};
