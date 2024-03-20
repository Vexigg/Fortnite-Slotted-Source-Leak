#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "imgui_tricks.h"

extern ImFont* icons;
extern ImFont* font_main;
namespace Custom {
    bool tab(const char* icon, bool selected, bool separator = true);
    bool subtab(const char* label, bool selected);
    void beginChild(const char* name, ImVec2 size);
    void endChild();

    namespace Drawlist {
        void renderFrame(ImVec2 start, ImVec2 end, ImColor frameColor, ImColor borderColor, float rounding);
        void renderCircleShadow(ImDrawList* drawlist, ImVec2 center, float radius, ImColor color);
        void renderRectShadow(ImDrawList* drawlist, ImVec2 start, ImVec2 end, ImColor color, float rounding);
    }
}