#pragma once

namespace PatternEditor {

    class Editor {
        private:
            // ImGui
            void ImGuiHelpMarker(const char* desc);
            void setupImGuiStyle();

            // Widgets
            void dockspaceSetup();
            void drawMenuBar();
            void drawEditor();

        public:
            Editor();
            void update();
            void draw();
            void clean();
    };

}