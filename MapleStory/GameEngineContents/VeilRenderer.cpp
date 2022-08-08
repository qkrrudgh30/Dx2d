#include "PreCompile.h"
#include "VeilRenderer.h"

VeilRenderer::VeilRenderer() 
{
	
}

VeilRenderer::~VeilRenderer() 
{	
}

void VeilRenderer::Start()
{
	GameEngineRenderer::Start();
	PushRendererToMainCamera();

	
}

