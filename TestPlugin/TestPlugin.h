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

	//返回插件名字，带后缀，如dll等
	virtual std::string GetFileName() const;

	//返回插件的名字，不带后缀
	virtual std::string GetDisplayName() const;

private:
	CMsgOsgViewer* m_pMsg;

};
