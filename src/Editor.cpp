#include "Editor.hpp"
#include "GameManager.hpp"
#include "Global.hpp"
#include "imgui_internal.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <cstddef>

PatternEditor::Editor::Editor() {

    rlImGuiSetup(true);
    ImGuiIO& _io = ImGui::GetIO();
    _io.FontGlobalScale = 2.0f;
    _io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    setupImGuiStyle();
};

void PatternEditor::Editor::setupImGuiStyle() {

    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_Header]                = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_Separator]             = style.Colors[ImGuiCol_Border];
    style.Colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_Tab]                   = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
    style.Colors[ImGuiCol_TabHovered]            = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
    style.Colors[ImGuiCol_TabActive]             = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocused]          = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_DockingPreview]        = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
    style.Colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[ImGuiCol_DragDropTarget]        = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
void PatternEditor::Editor::ImGuiHelpMarker(const char* desc) {

    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip()) {

        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void PatternEditor::Editor::dockspaceSetup() {

    // DockSpace setup
    ImGuiID _dockspaceId = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_NoUndocking);
    static bool _initDockspace = true;
    ImGuiID _dockIdLeft, _dockIdRight;
    if (_initDockspace) {
        _initDockspace = false;
        ImGui::DockBuilderRemoveNode(_dockspaceId);
        ImGui::DockBuilderAddNode(_dockspaceId);
        ImGui::DockBuilderSetNodeSize(_dockspaceId, ImGui::GetMainViewport()->Size);

    	ImGui::DockBuilderSplitNode(_dockspaceId, ImGuiDir_Left, 0.4f, &_dockIdLeft, &_dockIdRight);
        ImGui::DockBuilderDockWindow("Pattern Editor", _dockIdLeft);
        ImGui::DockBuilderDockWindow("Game", _dockIdRight);

        ImGui::DockBuilderFinish(_dockspaceId);
    }
}

void PatternEditor::Editor::drawMenuBar() {

    if (ImGui::BeginMenuBar()) {

        if (ImGui::BeginMenu("Options")) {
            if (ImGui::MenuItem("Fullscreen", NULL, Global::isFullscreen)) {
                
                Global::isFullscreen = !Global::isFullscreen;
                ToggleFullscreen();
            }
            ImGui::MenuItem("FPS Limit: TODO (60, 120, 144, 240, Unlimited)");
            ImGui::MenuItem("Texture Filter: TODO (Nearest, Bilinear)");

            ImGui::Separator();

            if (ImGui::MenuItem("Show FPS & Bullet Count", NULL, Global::drawFPS)) Global::drawFPS = !Global::drawFPS;

            if (ImGui::MenuItem("Performance Mode", NULL, Global::isPerformanceMode)) Global::isPerformanceMode = !Global::isPerformanceMode;
            ImGui::SameLine();
            ImGuiHelpMarker("The UI causes a lot of FPS loss, to get maximum FPS you can disable the UI by activating this option.");

            ImGui::Separator();

            if (ImGui::MenuItem("About")) {};
            
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help")) {

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

void PatternEditor::Editor::drawEditor() {

    // TODO
    static int _currentPattern = 0;
    ImGui::NewLine();
    ImGui::Text("PATTERN: ");
    ImGui::SameLine();
    ImGui::Combo("##current_pattern", &_currentPattern, "[DDP DaiOuJou] - Hibachi\0[Ketsui] - Boss 2\0\0");
    ImGui::NewLine();

    if (ImGui::BeginTabBar("Editor", ImGuiTabBarFlags_DrawSelectedOverline)) {

        if (ImGui::BeginTabItem(" Editor ")) {
            
            ImGui::NewLine();
            ImGui::Text("Pattern editor options will be here...");

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(" Json ")) {
            

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(" BulletML (XML) ")) {

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}

void PatternEditor::Editor::update() {};

void PatternEditor::Editor::draw() {

    rlImGuiBegin();

    static ImVec2 _fullButtonSize = ImVec2(-FLT_MIN, 0.0f);

    dockspaceSetup();

    //ImGui::ShowDemoWindow();

    ImGui::Begin("Pattern Editor", NULL, ImGuiWindowFlags_MenuBar);

        drawMenuBar();
        drawEditor();

    ImGui::End();

    ImGui::Begin("Game");
        
        if (IsRenderTextureValid(PatternEditor::gameManagerPtr->gameRenderTextureYInverted)) rlImGuiImageFit(&PatternEditor::gameManagerPtr->gameRenderTextureYInverted.texture, true);
    
    ImGui::End();
    rlImGuiEnd();
};

void PatternEditor::Editor::clean() {

    rlImGuiShutdown();
};