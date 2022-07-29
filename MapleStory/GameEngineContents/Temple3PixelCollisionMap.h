#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple3PixelCollisionMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple3PixelCollisionMap();
	~Temple3PixelCollisionMap();

	// delete Function
	Temple3PixelCollisionMap(const Temple3PixelCollisionMap& _Other) = delete;
	Temple3PixelCollisionMap(Temple3PixelCollisionMap&& _Other) noexcept = delete;
	Temple3PixelCollisionMap& operator=(const Temple3PixelCollisionMap& _Other) = delete;
	Temple3PixelCollisionMap& operator=(Temple3PixelCollisionMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* mpRenderer;

};

