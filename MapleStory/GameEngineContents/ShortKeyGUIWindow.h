#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// Ό³Έν :
class ShortKeyGUIWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	ShortKeyGUIWindow();
	~ShortKeyGUIWindow();

	// delete Function
	ShortKeyGUIWindow(const ShortKeyGUIWindow& _Other) = delete;
	ShortKeyGUIWindow(ShortKeyGUIWindow&& _Other) noexcept = delete;
	ShortKeyGUIWindow& operator=(const ShortKeyGUIWindow& _Other) = delete;
	ShortKeyGUIWindow& operator=(ShortKeyGUIWindow&& _Other) noexcept = delete;

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

};

