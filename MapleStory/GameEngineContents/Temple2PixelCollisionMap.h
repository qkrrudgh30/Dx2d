#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class Temple2PixelCollisionMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple2PixelCollisionMap();
	~Temple2PixelCollisionMap();

	// delete Function
	Temple2PixelCollisionMap(const Temple2PixelCollisionMap& _Other) = delete;
	Temple2PixelCollisionMap(Temple2PixelCollisionMap&& _Other) noexcept = delete;
	Temple2PixelCollisionMap& operator=(const Temple2PixelCollisionMap& _Other) = delete;
	Temple2PixelCollisionMap& operator=(Temple2PixelCollisionMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* mpRenderer;

};

