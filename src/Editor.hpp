#pragma once

namespace PatternEditor {

    class Editor {

        public:
            Editor();
            void update();
            void draw();
            void clean();

            // ImGui
            void ImGuiHelpMarker(const char* desc);
            void setupImGuiStyle();
    };

}