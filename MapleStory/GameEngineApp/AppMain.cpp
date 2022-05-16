// AppMain.cpp

#include <Windows.h>

#pragma comment(lib, "GameEngineBase.lib")

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineSound.h>
#include <vector>

using namespace std;

int main()
{
    GameEngineDirectory Dir;

    /*
    1. 현재 working dir에 Resources 디렉터리가 있는지 체크
      1-1. 없으면 뒤로가기
      1-2. 있으면 현재 path 저장
    */
    if (false == Dir.MoveParentToExitsChildDirectory("Resources"))
    {
        MsgBoxAssert("경로를 찾지 못했습니다.");
        return 0;
    }

    Dir.Move("Resources"); // 이후 코드부터는 Dir을 가지고 사운드와 리소스를 꺼내서 쓸 수 있음. 
    Dir.Move("Sound");

    // for (size_t i = 0; i < Dir.GetAllFile().size(); ++i) {} 올바르지 않은 코드. for문 회차마다 GetAllFile() 함수내 코드까지 실행됨.

    vector<GameEngineFile> Files = Dir.GetAllFile();
    for (auto& File : Files)
    {
        GameEngineSound::LoadRessource(File);
    }

    GameEngineSound::SoundPlayOneShot("TestBGM.mp3");

    while (true)
    {
        GameEngineSound::Update();
    }

    return 0;
}