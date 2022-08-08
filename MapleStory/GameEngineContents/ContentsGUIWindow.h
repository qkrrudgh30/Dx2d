#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class ContentsGUIWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	ContentsGUIWindow();
	~ContentsGUIWindow();

	// delete Function
	ContentsGUIWindow(const ContentsGUIWindow& _Other) = delete;
	ContentsGUIWindow(ContentsGUIWindow&& _Other) noexcept = delete;
	ContentsGUIWindow& operator=(const ContentsGUIWindow& _Other) = delete;
	ContentsGUIWindow& operator=(ContentsGUIWindow&& _Other) noexcept = delete;

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

};
