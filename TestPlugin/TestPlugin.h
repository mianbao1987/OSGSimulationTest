#pragma once

#include <string>
#include "PluginInstance.h"

class CMsgOsgViewer : public CMsgBase
{
public:
	CMsgOsgViewer(CSingletonMsgBus* pIns,string name) :CMsgBase(pIns)
	{
		this->SetMsgName(name);
	};
	~CMsgOsgViewer() {};
	bool ParseMsg(CMsgBase* pSrcMsg);
private:

};


class ShapePlugin : public PluginInstance
{
public:
	explicit ShapePlugin(CSingletonMsgBus* pIns, const std::string &strName);
	~ShapePlugin(void);

	virtual bool Load();

	virtual bool UnLoad();

	//���ز�����֣�����׺����dll��
	virtual std::string GetFileName() const;

	//���ز�������֣�������׺
	virtual std::string GetDisplayName() const;

private:
	CMsgOsgViewer* m_pMsg;

};
