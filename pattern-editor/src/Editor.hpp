#pragma once

#include "TextEditor.h"
#include "imgui.h"

namespace PatternEditor {

    class Editor {
        private:
            ImFont * editorFont;
            float fontSize = 30.0f;

            TextEditor jsonEditor;
	        TextEditor::LanguageDefinition jsonEditorLang = TextEditor::LanguageDefinition::CPlusPlus();

            char jsonExample[1024 * 32] = "{\n  \"@type\": \"horizontal\",\n  \"action\": [\n    {\n      \"@label\": \"oogi\",\n      \"fire\": {\n        \"direction\": {\n          \"@type\": \"absolute\",\n          \"#text\": \"270-(4+$rank*6)*15/2\"\n        },\n        \"bulletRef\": {\n          \"@label\": \"seed\"\n        }\n      },\n      \"repeat\": {\n        \"times\": \"4+$rank*6\",\n        \"action\": {\n          \"fire\": {\n            \"direction\": {\n              \"@type\": \"sequence\",\n              \"#text\": \"15\"\n            },\n            \"bulletRef\": {\n              \"@label\": \"seed\"\n            }\n          }\n        }\n      }\n    },\n    {\n      \"@label\": \"top\",\n      \"repeat\": [\n        {\n          \"times\": \"4\",\n          \"action\": {\n            \"actionRef\": {\n              \"@label\": \"oogi\"\n            },\n            \"wait\": \"40\"\n          }\n        },\n        {\n          \"times\": \"8\",\n          \"action\": {\n            \"actionRef\": {\n              \"@label\": \"oogi\"\n            },\n            \"wait\": \"20\"\n          }\n        }\n      ],\n      \"wait\": [\n        \"40\",\n        \"30\"\n      ]\n    }\n  ],\n  \"bullet\": {\n    \"@label\": \"seed\",\n    \"speed\": \"1.5\",\n    \"action\": {\n      \"changeSpeed\": {\n        \"speed\": \"0\",\n        \"term\": \"60\"\n      },\n      \"wait\": \"60\",\n      \"fire\": {\n        \"speed\": \"0.75\",\n        \"bullet\": null\n      },\n      \"repeat\": {\n        \"times\": \"4+$rank*4\",\n        \"action\": {\n          \"fire\": {\n            \"speed\": {\n              \"@type\": \"sequence\",\n              \"#text\": \"0.3\"\n            },\n            \"bullet\": null\n          }\n        }\n      },\n      \"vanish\": null\n    }\n  }\n}";

            // ImGui
            void ImGuiHelpMarker(const char* desc);
            void setupImGuiStyle();

            // Widgets
            void dockspaceSetup();
            void drawSettingsMenuBar();
            void drawEditorSettings();
            void drawEditorJSON();
            void drawEditorVisual();
            

        public:
            Editor();
            void update();
            void draw();
            void clean();
    };

}