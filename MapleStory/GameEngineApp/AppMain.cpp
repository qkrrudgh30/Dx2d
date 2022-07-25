#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

#include <GameEngineContents/ContentsCore.h>
#include <GameEngineBase/GameEngineMath.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	new int();
	/*
	_CrtDumpMemoryLeaks();
_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
_CrtSetBreakAlloc()
_crtBreakAlloc
	
	*/

	GameEngineCore::Start<ContentsCore>();

	// _CrtSetBreakAlloc(287);

	return 0;
}

