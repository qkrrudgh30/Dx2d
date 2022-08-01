#pragma once

#include <GameEngineCore/GameEngineDefaultRenderer.h>

// Ό³Έν :
class VeilRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	VeilRenderer();
	~VeilRenderer();

	// delete Function
	VeilRenderer(const VeilRenderer& _Other) = delete;
	VeilRenderer(VeilRenderer&& _Other) noexcept = delete;
	VeilRenderer& operator=(const VeilRenderer& _Other) = delete;
	VeilRenderer& operator=(VeilRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

