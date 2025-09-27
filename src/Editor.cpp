#include "Editor.hpp"
#include "GameManager.hpp"
#include "Global.hpp"
#include "imgui_internal.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <cstddef>

PatternEditor::Editor::Editor() {

    // ImGui setup
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

        static bool _openAbout = false;
        if (ImGui::BeginMenu("Options")) {

            if (ImGui::MenuItem("Fullscreen", NULL, Global::isFullscreen)) {
                
                Global::isFullscreen = !Global::isFullscreen;
                ToggleFullscreen();
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

            ImGui::Text("This project is a Bullet Hell / Danmaku Pattern Editor,\nyou can create and edit patterns for any kind of bullet hell game here.");
            
            ImGui::NewLine();

            ImGui::Text("It also supports");
            ImGui::SameLine();
            if (ImGui::TextLinkOpenURL("BulletML", "https://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html")) {
            
                #ifdef IS_OS_BUILD_WEB
                    OpenURL("https://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html");
                #endif
            }
            ImGui::SameLine();
            ImGui::Text("XML Files.");

            ImGui::NewLine();

            ImGui::Text("Most pattern examples are from");
            ImGui::SameLine();
            if(ImGui::TextLinkOpenURL("BulletMLExamples", "https://github.com/dmanning23/BulletMLExamples")) {
            
                #ifdef IS_OS_BUILD_WEB
                    OpenURL("https://github.com/dmanning23/BulletMLExamples");
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
                    OpenURL("https://github.com/zerohorsepower");
                #endif 
            }

            ImGui::Text("For more information about the project, access the");
            ImGui::SameLine();
            if(ImGui::TextLinkOpenURL("source code", "https://github.com/zerohorsepower/bullet-hell-pattern-editor")) {
            
                #ifdef IS_OS_BUILD_WEB
                    OpenURL("https://github.com/zerohorsepower/bullet-hell-pattern-editor");
                #endif  
            }

            
            ImGui::Separator();
            if (ImGui::Button("Close", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); _openAbout = false; }
            
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }

        if (ImGui::BeginMenu("Help")) {

            if (ImGui::MenuItem("##github_link")) {
                OpenURL("https://github.com/zerohorsepower/bullet-hell-pattern-editor");
            };
            ImGui::SameLine();
            ImGui::TextLinkOpenURL("https://github.com/zerohorsepower/bullet-hell-pattern-editor", "https://github.com/zerohorsepower/bullet-hell-pattern-editor");
            
            
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

void PatternEditor::Editor::drawEditor() {

    static ImVec2 _fullButtonSize = ImVec2(-FLT_MIN, 0.0f);

    // TODO
    static int _currentPattern = 0;
    ImGui::NewLine();
    ImGui::Text("PATTERN: ");
    ImGui::SameLine();
    ImGui::Combo("##current_pattern", &_currentPattern, "[DDP DaiOuJou] - Hibachi\0[Ketsui] - Boss 2\0\0");
    ImGui::SameLine();
    ImGui::Button(" [+] ");
    ImGui::NewLine();

    if (ImGui::BeginTabBar("Editor", ImGuiTabBarFlags_DrawSelectedOverline)) {

        if (ImGui::BeginTabItem(" Editor ")) {
            
            ImGui::NewLine();
            ImGui::Text("Pattern editor options will be here...");

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(" Json ")) {
            
            static char _jsonExample[1024 * 2] = "{\n  \"@type\": \"horizontal\",\n  \"action\": [\n    {\n      \"@label\": \"oogi\",\n      \"fire\": {\n        \"direction\": {\n          \"@type\": \"absolute\",\n          \"#text\": \"270-(4+$rank*6)*15/2\"\n        },\n        \"bulletRef\": {\n          \"@label\": \"seed\"\n        }\n      },\n      \"repeat\": {\n        \"times\": \"4+$rank*6\",\n        \"action\": {\n          \"fire\": {\n            \"direction\": {\n              \"@type\": \"sequence\",\n              \"#text\": \"15\"\n            },\n            \"bulletRef\": {\n              \"@label\": \"seed\"\n            }\n          }\n        }\n      }\n    },\n    {\n      \"@label\": \"top\",\n      \"repeat\": [\n        {\n          \"times\": \"4\",\n          \"action\": {\n            \"actionRef\": {\n              \"@label\": \"oogi\"\n            },\n            \"wait\": \"40\"\n          }\n        },\n        {\n          \"times\": \"8\",\n          \"action\": {\n            \"actionRef\": {\n              \"@label\": \"oogi\"\n            },\n            \"wait\": \"20\"\n          }\n        }\n      ],\n      \"wait\": [\n        \"40\",\n        \"30\"\n      ]\n    }\n  ],\n  \"bullet\": {\n    \"@label\": \"seed\",\n    \"speed\": \"1.5\",\n    \"action\": {\n      \"changeSpeed\": {\n        \"speed\": \"0\",\n        \"term\": \"60\"\n      },\n      \"wait\": \"60\",\n      \"fire\": {\n        \"speed\": \"0.75\",\n        \"bullet\": null\n      },\n      \"repeat\": {\n        \"times\": \"4+$rank*4\",\n        \"action\": {\n          \"fire\": {\n            \"speed\": {\n              \"@type\": \"sequence\",\n              \"#text\": \"0.3\"\n            },\n            \"bullet\": null\n          }\n        }\n      },\n      \"vanish\": null\n    }\n  }\n}";
            if (ImGui::Button("Copy to Clipboard", _fullButtonSize)) ImGui::SetClipboardText(_jsonExample);
            ImGui::InputTextMultiline(
                "##json",
                _jsonExample,
                IM_ARRAYSIZE(_jsonExample),
                ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 40),
                ImGuiInputTextFlags_ReadOnly
            );

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(" BulletML (XML) ")) {

            static char _xmlExample[1024 * 2] = "<?xml version=\"1.0\" ?>\n<!DOCTYPE bulletml SYSTEM \"bulletml.dtd\">\n\n<bulletml type=\"horizontal\"\n          xmlns=\"http://www.asahi-net.or.jp/~cs8k-cyu/bulletml\">\n\n<action label=\"oogi\">\n<fire>\n <direction type=\"absolute\">270-(4+$rank*6)*15/2</direction>\n <bulletRef label=\"seed\"/>\n</fire>\n<repeat><times>4+$rank*6</times>\n<action>\n <fire>\n  <direction type=\"sequence\">15</direction>\n  <bulletRef label=\"seed\"/>\n </fire>\n</action>\n</repeat>\n</action>\n\n<action label=\"top\">\n <repeat> <times>4</times>\n <action>\n  <actionRef label=\"oogi\"/>\n  <wait>40</wait>\n </action>\n </repeat>\n <wait>40</wait>\n <repeat> <times>8</times>\n <action>\n  <actionRef label=\"oogi\"/>\n  <wait>20</wait>\n </action>\n </repeat> \n<wait>30</wait>\n</action>\n\n<bullet label=\"seed\">\n<speed>1.5</speed>\n<action>\n<changeSpeed>\n <speed>0</speed>\n <term>60</term>\n</changeSpeed>\n<wait>60</wait>\n<fire>\n <speed>0.75</speed>\n <bullet/>\n</fire>\n<repeat><times>4+$rank*4</times>\n<action>\n <fire>\n  <speed type=\"sequence\">0.3</speed>\n  <bullet/>\n </fire>\n</action>\n</repeat>\n<vanish/>\n</action>\n</bullet>\n\n</bulletml>";
            if (ImGui::Button("Copy to Clipboard", _fullButtonSize)) ImGui::SetClipboardText(_xmlExample);
            ImGui::InputTextMultiline(
                "##bulletml",
                _xmlExample,
                IM_ARRAYSIZE(_xmlExample),
                ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 40),
                ImGuiInputTextFlags_ReadOnly
            );

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}

void PatternEditor::Editor::update() {};

void PatternEditor::Editor::draw() {

    rlImGuiBegin();
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