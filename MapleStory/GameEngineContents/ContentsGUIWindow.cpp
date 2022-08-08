#include "PreCompile.h"
#include "ContentsGUIWindow.h"
#include "Player.h"

ContentsGUIWindow::ContentsGUIWindow() 
{
}

ContentsGUIWindow::~ContentsGUIWindow() 
{
}

void ContentsGUIWindow::Initialize(GameEngineLevel* _Level)
{
}

void ContentsGUIWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == Player::GetPlayer())
	{
		return;
	}

	Player* pPlayer = Player::GetPlayer();
	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Player World Position:    %7.2f, %7.2f, %7.2f, %7.2f",
		pPlayer->GetTransform().GetWorldPosition().x,
		pPlayer->GetTransform().GetWorldPosition().y,
		pPlayer->GetTransform().GetWorldPosition().z,
		pPlayer->GetTransform().GetWorldPosition().w);
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "Player Head Pixel Color:  %4.2f, %4.2f, %4.2f, %4.2f",
		pPlayer->GetHeadPixelData().x,
		pPlayer->GetHeadPixelData().y,
		pPlayer->GetHeadPixelData().z,
		pPlayer->GetHeadPixelData().w);
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "Player Below Pixel Color: %4.2f, %4.2f, %4.2f, %4.2f",
		pPlayer->GetPixelData().x,
		pPlayer->GetPixelData().y,
		pPlayer->GetPixelData().z,
		pPlayer->GetPixelData().w);
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "Player Left Pixel Color:    %4.2f, %4.2f, %4.2f, %4.2f",
		pPlayer->GetPixelDataOnLeftSide().x,
		pPlayer->GetPixelDataOnLeftSide().y,
		pPlayer->GetPixelDataOnLeftSide().z,
		pPlayer->GetPixelDataOnLeftSide().w);
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "Player Right Pixel Color:  %4.2f, %4.2f, %4.2f, %4.2f",
		pPlayer->GetPixelDataOnRightSide().x,
		pPlayer->GetPixelDataOnRightSide().y,
		pPlayer->GetPixelDataOnRightSide().z,
		pPlayer->GetPixelDataOnRightSide().w);
	ImGui::EndChild();
	
}

