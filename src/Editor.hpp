#pragma once

#include "imgui.h"

namespace PatternEditor {

    class Editor {
        private:
            ImFont * editorFont;
            float fontSize = 30.0f;

            // ImGui
            void ImGuiHelpMarker(const char* desc);
            void setupImGuiStyle();

            // Widgets
            void dockspaceSetup();
            void drawMenuBar();
            void drawEditor();
            void drawMainEditorSettings();

        public:
            Editor();
            void update();
            void draw();
            void clean();
    };

}