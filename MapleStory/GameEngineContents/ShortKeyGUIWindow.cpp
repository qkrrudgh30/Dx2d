#include "PreCompile.h"
#include "ShortKeyGUIWindow.h"

#include <GameEngineCore/GameEngineLevel.h>

ShortKeyGUIWindow::ShortKeyGUIWindow() 
{
}

ShortKeyGUIWindow::~ShortKeyGUIWindow() 
{
}

void ShortKeyGUIWindow::Initialize(GameEngineLevel* _Level)
{
}

void ShortKeyGUIWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Attack: F G");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Jump: Space bar");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Below jump: Space bar + Down");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Inventory: I");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Move Inventory: Drag title bar and Drop");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Follow player with main camera On/Off: F2");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Show pixel collision map On/Off: F3");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Camera's moving limit On/Off: F7");
	ImGui::EndChild();

}

