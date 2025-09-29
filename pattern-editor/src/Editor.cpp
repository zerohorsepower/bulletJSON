#include "Editor.hpp"
#include "GameManager.hpp"
#include "Global.hpp"
#include "imgui_internal.h"
#include "imnodes.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <cstddef>

PatternEditor::Editor::Editor() {

    // ImGui setup
    rlImGuiSetup(true);
    ImGuiIO& _io = ImGui::GetIO();

    editorFont = _io.Fonts->AddFontFromFileTTF((Global::assetsPath + "/fira-code.ttf").c_str(), fontSize, NULL, _io.Fonts->GetGlyphRangesDefault());

    _io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    setupImGuiStyle();

    // ImNodes setup
    ImNodes::CreateContext();

    // TextEditor
    jsonEditor.SetLanguageDefinition(jsonEditorLang);
	jsonEditor.SetPalette(TextEditor::GetDarkPalette());
    jsonEditor.SetTabSize(2);
    jsonEditor.SetText(jsonExample);

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

void PatternEditor::Editor::update() {};

// Helper to display a little (?) mark which shows a tooltip when hovered.
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
    ImGuiID _mainDockspaceId = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_NoUndocking);
    static bool _initDockspace = true;
    ImGuiID _dockIdLeft, _dockIdGame, _dockIdSettings, _dockIdLeftBottom;
    if (_initDockspace) {
        _initDockspace = false;
        ImGui::DockBuilderRemoveNode(_mainDockspaceId);
        ImGui::DockBuilderAddNode(_mainDockspaceId);
        ImGui::DockBuilderSetNodeSize(_mainDockspaceId, ImGui::GetMainViewport()->Size);

    	ImGui::DockBuilderSplitNode(_mainDockspaceId, ImGuiDir_Left, 0.43f, &_dockIdLeft, &_dockIdGame);
        ImGui::DockBuilderDockWindow("Game", _dockIdGame);

        ImGui::DockBuilderSplitNode(_dockIdLeft, ImGuiDir_Up, 0.27f, &_dockIdLeft, &_dockIdLeftBottom);

        ImGui::DockBuilderDockWindow("Settings", _dockIdLeft);
        ImGui::DockBuilderDockWindow("Node Editor", _dockIdLeftBottom);
        ImGui::DockBuilderDockWindow("JSON Editor", _dockIdLeftBottom);

        ImGui::DockBuilderFinish(_mainDockspaceId);
    }
}

void PatternEditor::Editor::drawSettingsMenuBar() {

    if (ImGui::BeginMenuBar()) {

        static bool _openAbout = false;
        if (ImGui::BeginMenu("Options")) {

            if (ImGui::MenuItem("Fullscreen", NULL, Global::isFullscreen)) {
                
                Global::isFullscreen = !Global::isFullscreen;
                ToggleBorderlessWindowed();
            }

            if (ImGui::BeginMenu("Texture Filter")) {

                if (ImGui::MenuItem("Nearest", NULL, (Global::textureFilter == TEXTURE_FILTER_POINT))) {

                    PatternEditor::gameManagerPtr->setTextureFilterAll(TEXTURE_FILTER_POINT);
                }

                if (ImGui::MenuItem("Bilinear", NULL, (Global::textureFilter == TEXTURE_FILTER_BILINEAR))) {

                    PatternEditor::gameManagerPtr->setTextureFilterAll(TEXTURE_FILTER_BILINEAR);
                }

                ImGui::EndMenu();
            }


            if (ImGui::BeginMenu("FPS Limit")) {

                if (ImGui::MenuItem("No FPS Limit", NULL, (Global::fpsLimit == 99999))) {

                    Global::fpsLimit = 99999;
                    SetTargetFPS(99999);
                }

                if (ImGui::MenuItem("60", NULL, (Global::fpsLimit == 60))) {

                    Global::fpsLimit = 60;
                    SetTargetFPS(60);
                }

                if (ImGui::MenuItem("120", NULL, (Global::fpsLimit == 120))) {

                    Global::fpsLimit = 120;
                    SetTargetFPS(120);
                }

                if (ImGui::MenuItem("144", NULL, (Global::fpsLimit == 144))) {

                    Global::fpsLimit = 144;
                    SetTargetFPS(144);
                }

                if (ImGui::MenuItem("240", NULL, (Global::fpsLimit == 240))) {

                    Global::fpsLimit = 240;
                    SetTargetFPS(240);
                }

                ImGui::EndMenu();
            }
            

            ImGui::Separator();

            if (ImGui::MenuItem("Show FPS & Bullet Count", NULL, Global::drawFPS)) Global::drawFPS = !Global::drawFPS;

            if (ImGui::MenuItem("Performance Mode", NULL, Global::isPerformanceMode)) Global::isPerformanceMode = !Global::isPerformanceMode;
            ImGui::SameLine();
            ImGuiHelpMarker("The UI causes a lot of FPS loss, to get maximum FPS you can disable the UI by activating this option.");

            ImGui::Separator();

            if (ImGui::MenuItem("About")) _openAbout = true;
            
            ImGui::EndMenu();
        }

        if (_openAbout) ImGui::OpenPopup("About");

        if (ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

            ImGui::Text("This project is a Bullet Hell / Danmaku pattern editor, it uses");
            ImGui::SameLine();
            if(ImGui::TextLinkOpenURL("BulletJSON", "https://github.com/zerohorsepower/bulletJSON/DEFINITION.md")) {
            
                #ifdef IS_OS_BUILD_WEB
                    //OpenURL("https://github.com/zerohorsepower/bulletJSON");
                #endif  
            }
            ImGui::SameLine();
            ImGui::Text("specification.");
            
            ImGui::NewLine();

            ImGui::Text("It also supports");
            ImGui::SameLine();
            if (ImGui::TextLinkOpenURL("BulletML", "https://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html")) {
            
                #ifdef IS_OS_BUILD_WEB
                    //OpenURL("https://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html");
                #endif
            }
            ImGui::SameLine();
            ImGui::Text("XML Files.");

            ImGui::SameLine();

            ImGui::Text("Most pattern examples are from");
            ImGui::SameLine();
            if(ImGui::TextLinkOpenURL("BulletMLExamples", "https://github.com/dmanning23/BulletMLExamples")) {
            
                #ifdef IS_OS_BUILD_WEB
                    //OpenURL("https://github.com/dmanning23/BulletMLExamples");
                #endif
            }

            ImGui::NewLine();

            ImGui::TextColored({ 150, 0, 0, 255 }, "The used sprites are from the game DoDonPachi Daiffukatsu, developed by CAVE.");
            ImGui::TextColored({ 150, 0, 0, 255 }, "All rights reserved ©.");

            ImGui::NewLine();

            ImGui::Text("This project was developed by");
            ImGui::SameLine();
            if(ImGui::TextLinkOpenURL("zerohorsepower", "https://github.com/zerohorsepower")) {
            
                #ifdef IS_OS_BUILD_WEB
                    //OpenURL("https://github.com/zerohorsepower");
                #endif 
            }

            ImGui::Text("For more information about BulletJSON and its specification, access its");
            ImGui::SameLine();
            if(ImGui::TextLinkOpenURL("repository", "https://github.com/zerohorsepower/bulletJSON")) {
            
                #ifdef IS_OS_BUILD_WEB
                    //OpenURL("https://github.com/zerohorsepower/bulletJSON");
                #endif  
            }

            ImGui::NewLine();

            
            ImGui::Separator();
            if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); _openAbout = false; }
            
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }

        static bool _openHTUModal = false;
        if (ImGui::BeginMenu("Help")) {

            if (ImGui::MenuItem("How to Use")) _openHTUModal = true;            
            
            ImGui::EndMenu();
        }

        if (_openHTUModal) ImGui::OpenPopup("How To Use");

        if (ImGui::BeginPopupModal("How To Use", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

            ImGui::Text("TODO: finish this guide");

            ImGui::Text("BulletJSON is a extension of");
            ImGui::SameLine();
            if (ImGui::TextLinkOpenURL("BulletML", "https://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html")) {
            
                #ifdef IS_OS_BUILD_WEB
                    //OpenURL("https://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html");
                #endif
            }

            ImGui::NewLine();

            ImGui::Text("For a more detailed documentation, access the");
            ImGui::SameLine();
            if(ImGui::TextLinkOpenURL("repository", "https://github.com/zerohorsepower/bulletJSON")) {
            
                #ifdef IS_OS_BUILD_WEB
                    //OpenURL("https://github.com/zerohorsepower/bulletJSON");
                #endif  
            }

            ImGui::NewLine();

            
            ImGui::Separator();
            if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); _openHTUModal = false; }
            
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }

        ImGui::EndMenuBar();
    }
}

void PatternEditor::Editor::drawEditorSettings() {

    float _defaultItemWidth = ImGui::CalcItemWidth();
    static int _currentPattern = 0;
    
    ImGui::NewLine();
    ImGui::Text("PATTERN: ");
    ImGui::SameLine();
    ImGui::Combo("##current_pattern", &_currentPattern, "[DDP DaiOuJou] - Hibachi\0[Ketsui] - Boss 2\0\0");
    ImGui::SameLine();
    ImGui::Button(" [+] ");

    ImGui::Text("GAME SPEED: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(_defaultItemWidth + 44);
    ImGui::SliderFloat("##game_speed", &Global::deltaTimeScale, 0.5f, 2.0f);
    

    ImGui::Text("RANK: ");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(_defaultItemWidth + 126);
    ImGui::SliderFloat("##rank", &Global::rank, 0.0f, 1.0f);

    ImGui::Text("SLOWDOWN: ");
    ImGui::SameLine();
    ImGuiHelpMarker("Case enabled, the game will run at the target speed when the number of bullets on screen is reached. (BULLETS x SLOWDOWN TARGET SPEED)");
    ImGui::SameLine();
    ImGui::Checkbox("##slowdown_check", &Global::enableSlowdown);
    ImGuiSliderFlags _sliderFlags = ImGuiSliderFlags_None;
    
    if (!Global::enableSlowdown) {

        _sliderFlags = ImGuiSliderFlags_ReadOnly;
        ImGui::BeginDisabled();
    }

    ImGui::SameLine();
    ImGui::SetNextItemWidth(_defaultItemWidth/2 - 15);
    ImGui::DragInt("##bullets_to_slowdown", &Global::bulletsToSlowdown, 1, 0, 99999, NULL, _sliderFlags);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(_defaultItemWidth/2 - 15);
    ImGui::SliderFloat("##target_slowdown", &Global::targetSlowdown, 0.5f, 1.0f, NULL, _sliderFlags);

    if (!Global::enableSlowdown) ImGui::EndDisabled();

}

void PatternEditor::Editor::drawEditorNode() {

    static ImVec2 _fullButtonSize = ImVec2(-FLT_MIN, 0.0f);
    ImGui::Button("Save", _fullButtonSize);

    ImNodes::BeginNodeEditor();

        // temp
        static const int _hardcodedNodeId = 1;
        ImNodes::BeginNode(_hardcodedNodeId);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Node 1");
        ImNodes::EndNodeTitleBar();
        
        static const int _outputAttrId = 11;
        ImNodes::BeginOutputAttribute(_outputAttrId);
        // in between Begin|EndAttribute calls, you can call ImGui
        // UI functions
        ImGui::Text("attr with output");
        ImNodes::EndOutputAttribute();

        ImNodes::EndNode();

        static const int _hardcodedNodeId2 = 2;
        ImNodes::BeginNode(_hardcodedNodeId2);

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Node 2");
        ImNodes::EndNodeTitleBar();
        
        static const int _inputAttrId = 22;
        ImNodes::BeginInputAttribute(_inputAttrId);
        // in between Begin|EndAttribute calls, you can call ImGui
        // UI functions
        ImGui::Text("attr with input");
        ImNodes::EndInputAttribute();

        ImNodes::EndNode();

        static bool _nodePositionInit = true;
        if (_nodePositionInit) {
            
            _nodePositionInit = false;
            ImNodes::SetNodeEditorSpacePos(1, { 100, 300 });
            ImNodes::SetNodeEditorSpacePos(2, { 600, 400 });
        }
        ImNodes::Link(33, 11, 22);

        // end temp

        ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);
    ImNodes::EndNodeEditor();
}

void PatternEditor::Editor::drawEditorJSON() {

    // Menu Bar
    if (ImGui::BeginMenuBar()) {

        if (ImGui::BeginMenu("Edit")) {
            bool _readOnly = jsonEditor.IsReadOnly();

            if (ImGui::MenuItem("Undo", "Ctrl-Z", nullptr, !_readOnly && jsonEditor.CanUndo()))                 jsonEditor.Undo();
            if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !_readOnly && jsonEditor.CanRedo()))
                jsonEditor.Redo();

            ImGui::Separator();

            if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, jsonEditor.HasSelection()))
                jsonEditor.Copy();
            if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !_readOnly && jsonEditor.HasSelection()))
                jsonEditor.Cut();
            if (ImGui::MenuItem("Delete", "Del", nullptr, !_readOnly && jsonEditor.HasSelection()))
                jsonEditor.Delete();
            if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !_readOnly && ImGui::GetClipboardText() != nullptr))
                jsonEditor.Paste();

            ImGui::Separator();

            if (ImGui::MenuItem("Select all", "Ctrl-A"))
                jsonEditor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(jsonEditor.GetTotalLines(), 0));

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Clipboard")) {

            if (ImGui::MenuItem("Copy to Clipboard"))
                ImGui::SetClipboardText(jsonExample);
            if (ImGui::MenuItem("Copy as STRING to Clipboard"))
                ImGui::SetClipboardText(jsonExample);
            
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {

            if (ImGui::MenuItem("Dark palette"))
                jsonEditor.SetPalette(TextEditor::GetDarkPalette());
            if (ImGui::MenuItem("Light palette"))
                jsonEditor.SetPalette(TextEditor::GetLightPalette());
            if (ImGui::MenuItem("Retro blue palette"))
                jsonEditor.SetPalette(TextEditor::GetRetroBluePalette());
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    static ImVec2 _fullButtonSize = ImVec2(-FLT_MIN, 0.0f);
    static std::string _jsonEditSaveButtonLabel = "Edit";
    ImGui::Button("Save", _fullButtonSize);

    jsonEditor.Render("JSON Editor", {}, true);
}

void PatternEditor::Editor::draw() {

    // ---- Setup
    rlImGuiBegin();
    ImGui::PushFont(editorFont);
    dockspaceSetup();

    //ImGui::ShowDemoWindow();

    // ---- Settings
    if (ImGui::Begin("Settings", NULL, ImGuiWindowFlags_MenuBar)) {

        drawSettingsMenuBar();
        drawEditorSettings();

    }
    ImGui::End();

    // ---- Node Editor
    if (ImGui::Begin("Node Editor")) {

        drawEditorNode();
    
    }
    ImGui::End();

    // ---- JSON Editor
    if (ImGui::Begin("JSON Editor", NULL, ImGuiWindowFlags_MenuBar)) {

        drawEditorJSON();
    }
    ImGui::End();

    // ---- Game
    if (ImGui::Begin("Game")) {
        
        //ImGui::Image((ImTextureID) PatternEditor::gameManagerPtr->gameRenderTextureYInverted.texture.id, {200, 200});

        if (IsRenderTextureValid(PatternEditor::gameManagerPtr->gameRenderTextureYInverted)) rlImGuiImageFit(&PatternEditor::gameManagerPtr->gameRenderTextureYInverted.texture, true);

        if (ImGui::IsWindowFocused()) Global::isGameFocused = true;
        else Global::isGameFocused = false;

    }
    ImGui::End();

    ImGui::PopFont();
    rlImGuiEnd();
};

void PatternEditor::Editor::clean() {

    ImNodes::DestroyContext();
    rlImGuiShutdown();
};