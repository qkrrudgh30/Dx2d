#pragma once
#include <GameEngineCore/CoreMinimal.h>

// ���� :
class GameEngineTextureRenderer;
class Portal : public GameEngineActor
{
	friend class ContentsLevel;

private :
	GameEngineTextureRenderer* mpRenderer;
	float                      mfWidth;
	float                      mfHeight;

public:
	// constrcuter destructer
	Portal();
	~Portal();

	// delete Function
	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;

	GameEngineTextureRenderer* GetRenderer() { return mpRenderer; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

