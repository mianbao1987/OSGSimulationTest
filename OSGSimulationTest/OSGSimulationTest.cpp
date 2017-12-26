// OSGSimulationTest.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <windows.h>
#include <tchar.h>

/*
#include "App.h"

CApp* g_App = nullptr;*/
#include <iostream>

#include "PluginInstance.h"
#include "PluginManager.h"

using namespace std;


bool InstanceSingleton()
{
	::CreateMutex(NULL, TRUE, _T("SimulationWnd"));

	return ERROR_ALREADY_EXISTS == GetLastError();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	if (InstanceSingleton())
	{
		return 0;
	}

	if (AllocConsole())
	{
		freopen("conout$", "w+t", stdout);
	}


	PluginManager &pluManager = PluginManager::GetInstance();
	int errCode;

	PluginInstance *pInstance = pluManager.Load("OsgViewerPlugin", errCode);
	PluginInstance *pInstance111 = pluManager.Load("TestPlugin", errCode);
	if (pInstance)
	{
		printf("%s,%d\n", pInstance->GetFileName().c_str(), errCode);
	}
	if (pInstance111)
	{
		printf("%s,%d\n", pInstance111->GetFileName().c_str(), errCode);
	}

	pluManager.UnLoad("OsgViewerPlugin");
	pluManager.UnLoad("TestPlugin");
	printf("%d\n", pluManager.GetAllPlugins().size());


	return 0;
}
