#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer; 
class Temple1PixelCollisionMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Temple1PixelCollisionMap();
	~Temple1PixelCollisionMap();

	// delete Function
	Temple1PixelCollisionMap(const Temple1PixelCollisionMap& _Other) = delete;
	Temple1PixelCollisionMap(Temple1PixelCollisionMap&& _Other) noexcept = delete;
	Temple1PixelCollisionMap& operator=(const Temple1PixelCollisionMap& _Other) = delete;
	Temple1PixelCollisionMap& operator=(Temple1PixelCollisionMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* mpRenderer;

};

