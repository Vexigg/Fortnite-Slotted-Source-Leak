#include "custom.h"

#include <string>

using namespace ImGui;

bool Custom::tab(const char* icon, bool selected, bool separator) {
    ImGuiWindow* window = GetCurrentWindow();

    ImGuiContext& g = *GImGui;

    ImGuiID id = window->GetID(icon);

    ImVec2 p = window->DC.CursorPos;

    ImVec2 labelSize(23, 23);

    ImRect totalBb(p, { p.x + labelSize.x, p.y + labelSize.y });

    ItemSize(totalBb);
    ItemAdd(totalBb, id);

    bool hovered, held;
    bool pressed = ButtonBehavior(totalBb, id, &hovered, &held);

    if (separator)
        window->DrawList->AddLine({ totalBb.Min.x, totalBb.Max.y + 12.5f }, { totalBb.Max.x, totalBb.Max.y + 12.5f }, ImColor(24, 24, 24));

    float textAlpha = ImTricks::Animations::FastFloatLerp(std::string(icon).append("textAlpha"), selected, 0.2f, 1.f, GetIO().DeltaTime * 5);


    PushStyleColor(ImGuiCol_Text, GetColorU32(ImGuiCol_Text, textAlpha));
    RenderText(totalBb.Min, icon);
    PopStyleColor();

    PopFont();

    return pressed;
}

bool Custom::subtab(const char* label, bool selected) {
    ImGuiWindow* window = GetCurrentWindow();

    ImGuiContext& g = *GImGui;

    ImGuiID id = window->GetID(label);

    ImVec2 p = window->DC.CursorPos;

    ImVec2 labelSize = CalcTextSize(label);
    ImVec2 size(labelSize.x + 52, 25);
    ImRect totalBb(p, { p.x + size.x, p.y + size.y });

    ItemSize(totalBb);
    ItemAdd(totalBb, id);

    bool hovered, held;
    bool pressed = ButtonBehavior(totalBb, id, &hovered, &held);

    float textAlpha = ImTricks::Animations::FastFloatLerp(std::string(label).append("textAlpha"), selected, 0.6f, 1.f, GetIO().DeltaTime * 5);
    float alpha = ImTricks::Animations::FastFloatLerp(std::string(label).append("alpha"), selected, 0.f, 1.f, GetIO().DeltaTime * 5);

    Drawlist::renderFrame(totalBb.Min, totalBb.Max, GetColorU32(ImGuiCol_FrameBg), GetColorU32(ImGuiCol_Border), 360);
    Drawlist::renderFrame(totalBb.Min, totalBb.Max, ImColor(18 / 255.f, 131 / 255.f, 59 / 255.f, alpha), ImColor(29 / 255.f, 184 / 255.f, 84 / 255.f, alpha), 360);

    Drawlist::renderRectShadow(window->DrawList, totalBb.Min, totalBb.Max, ImColor(29 / 255.f, 184 / 255.f, 100 / 255.f, alpha / 5), 360);

    PushStyleColor(ImGuiCol_Text, GetColorU32(ImGuiCol_Text, textAlpha));
    RenderText({ totalBb.Min.x + size.x / 2 - labelSize.x / 2, totalBb.Min.y + size.y / 2 - labelSize.y / 2 }, label);
    PopStyleColor();

    return pressed;
}

void Custom::beginChild(const char* name, ImVec2 size) {
    ImGuiWindow* window = GetCurrentWindow();
    ImGuiContext& g = *GImGui;

    float pad = 5.f;

    ImVec2 p = window->DC.CursorPos;

    BeginChild(std::string(name).append("main").c_str(), size);

    ImDrawList* draw = GetWindowDrawList();

    draw->AddLine({ p.x, p.y + 27 }, { p.x + size.x, p.y + 27 }, GetColorU32(ImGuiCol_Border));
    draw->AddRect(p, { p.x + size.x, p.y + size.y }, GetColorU32(ImGuiCol_Border), g.Style.ChildRounding);

    RenderText({ p.x + 20, p.y + 28 / 2 - CalcTextSize(name).y / 2 }, name);

    SetCursorPos({ g.Style.WindowPadding.x - pad, g.Style.WindowPadding.y });

    BeginChild(name, { size.x - g.Style.WindowPadding.x * 2 + pad * 2, size.y - g.Style.WindowPadding.y }, false, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar);

    SetCursorPosX(pad);

    BeginGroup();
}

void Custom::endChild() {
    EndGroup();
    EndChild();
    EndChild();
}

void Custom::Drawlist::renderFrame(ImVec2 start, ImVec2 end, ImColor frameColor, ImColor borderColor, float rounding) {
    PushStyleColor(ImGuiCol_Border, ImU32(borderColor));
    RenderFrame(start, end, frameColor, true, rounding);
    PopStyleColor();
}

void Custom::Drawlist::renderCircleShadow(ImDrawList* drawlist, ImVec2 center, float radius, ImColor color) {
    while (true) {
        if (color.Value.w <= 0.019f)
            break;

        color.Value.w -= color.Value.w / 4;
        radius++;

        drawlist->AddCircle(center, radius, color, 360);
    }
}

void Custom::Drawlist::renderRectShadow(ImDrawList* drawlist, ImVec2 start, ImVec2 end, ImColor color, float rounding) {
    while (true) {
        if (color.Value.w <= 0.019f)
            break;

        color.Value.w -= color.Value.w / 4;
        start = ImVec2(start.x - 1, start.y - 1);
        end = ImVec2(end.x + 1, end.y + 1);

        drawlist->AddRect(start, end, color, rounding);
    }
}