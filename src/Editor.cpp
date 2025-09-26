#include "Editor.hpp"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

PatternEditor::Editor::Editor() {

    rlImGuiSetup(true);
    ImGuiIO& _io = ImGui::GetIO();
    _io.FontGlobalScale = 2.0f;
};

void PatternEditor::Editor::update() {};

void PatternEditor::Editor::draw() {

    BeginDrawing();

        ClearBackground(RAYWHITE);

        rlImGuiBegin();

        static ImVec2 _fullButtonSize = ImVec2(-FLT_MIN, 0.0f);
        ImGui::ShowDemoWindow();

        rlImGuiEnd();

    EndDrawing(); 
};

void PatternEditor::Editor::clean() {};