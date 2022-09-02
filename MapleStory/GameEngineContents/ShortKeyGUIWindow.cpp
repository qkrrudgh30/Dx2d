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
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Attack: ");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "F G");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Jump: ");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "Space bar");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Below Jump: ");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "Space bar + Down");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Inventory: ");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "I");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Move Inventory: ");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "Drag title bar and Drop");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Camera's following player On/Off: ");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "F2");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Pixel Collision Map On/Off: ");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "F3");
	ImGui::EndChild();

	ImGui::BeginChild("Scrolling");
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Camera's moving limit On/Off: ");
	ImGui::TextColored(ImVec4(0, 1, 0, 1), "F7");
	ImGui::EndChild();

}

