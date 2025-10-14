#include <zen/gui/ZEN_Style.h>

#include <include/imgui/imgui.h>
namespace Zen {
  void styleSetup() {
    // Zen Style
    ImGuiStyle &style = ImGui::GetStyle();

    style.Alpha                    = 1.0f;
    style.DisabledAlpha            = 1.0f;
    style.WindowPadding            = ImVec2(20.0f, 20.0f);
    style.WindowRounding           = 8.0f;
    style.WindowBorderSize         = 1.0f;
    style.WindowMinSize            = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign         = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildRounding            = 10.0f;
    style.ChildBorderSize          = 1.0f;
    style.PopupRounding            = 16.0f;
    style.PopupBorderSize          = 1.0f;
    style.FramePadding             = ImVec2(20.0f, 4.0f);
    style.FrameRounding            = 12.0f;
    style.FrameBorderSize          = 1.0f;
    style.ItemSpacing              = ImVec2(8.0f, 12.0f);
    style.ItemInnerSpacing         = ImVec2(8.0f, 2.0f);
    style.CellPadding              = ImVec2(12.0f, 8.0f);
    style.IndentSpacing            = 0.0f;

    style.ScrollbarSize     = 12.0f;
    style.ScrollbarRounding = 20.0f;
    style.GrabMinSize       = 12.0f;
    style.GrabRounding      = 20.0f;
    style.TabRounding       = 12.0f;
    style.TabBorderSize     = 1.0f;

    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign     = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] =
        ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);

    style.Colors[ImGuiCol_WindowBg] =
        ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] =
        ImVec4(0.09411764889955521f, 0.1019607856869698f, 0.1176470592617989f, 1.0f);
    style.Colors[ImGuiCol_PopupBg] =
        ImVec4(0.01960784383118153f, 0.09803921729326248f, 0.1372549086809158f, 1.0f);

    style.Colors[ImGuiCol_Border] =
        ImVec4(0.1777524054050446f, 0.2026628106832504f, 0.2145922780036926f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.01960784383118153f,
                                                 0.09803921729326248f,
                                                 0.1372549086809158f,
                                                 0.09442061185836792f);

    style.Colors[ImGuiCol_FrameBg] =
        ImVec4(0.1137254908680916f, 0.125490203499794f, 0.1529411822557449f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] =
        ImVec4(0.0f, 0.1882352977991104f, 0.2784313857555389f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] =
        ImVec4(0.0f, 0.1882352977991104f, 0.2784313857555389f, 1.0f);

    style.Colors[ImGuiCol_TitleBg] =
        ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] =
        ImVec4(0.0117647061124444f, 0.05098039284348488f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] =
        ImVec4(0.01960784383118153f, 0.09803921729326248f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] =
        ImVec4(0.0f, 0.08627451211214066f, 0.1372549086809158f, 1.0f);

    style.Colors[ImGuiCol_ScrollbarBg] =
        ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrab] =
        ImVec4(0.3843137323856354f, 0.5254902243614197f, 0.5960784554481506f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] =
        ImVec4(0.0f, 0.6509804129600525f, 0.9843137264251709f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] =
        ImVec4(0.3843137323856354f, 0.5254902243614197f, 0.5960784554481506f, 1.0f);

    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.6509804129600525f, 0.9843137264251709f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] =
        ImVec4(0.3843137323856354f, 0.5254902243614197f, 0.5960784554481506f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] =
        ImVec4(0.3843137323856354f, 0.5254902243614197f, 0.5960784554481506f, 1.0f);

    style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.1176470592617989f, 0.1843137294054031f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] =
        ImVec4(0.0f, 0.1882352977991104f, 0.2784313857555389f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] =
        ImVec4(0.1529411822557449f, 0.1529411822557449f, 0.1529411822557449f, 1.0f);

    style.Colors[ImGuiCol_Header] =
        ImVec4(0.1411764770746231f, 0.1647058874368668f, 0.2078431397676468f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] =
        ImVec4(0.0f, 0.1882352977991104f, 0.2784313857555389f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] =
        ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);

    style.Colors[ImGuiCol_Separator] =
        ImVec4(0.1294117718935013f, 0.1490196138620377f, 0.1921568661928177f, 1.0f);
    style.Colors[ImGuiCol_SeparatorHovered] =
        ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    style.Colors[ImGuiCol_SeparatorActive] =
        ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);

    style.Colors[ImGuiCol_ResizeGrip] =
        ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1450980454683304f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripHovered] =
        ImVec4(0.0f, 0.6509804129600525f, 0.9843137264251709f, 1.0f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    const ImVec4 col_Tab =
        ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    const ImVec4 col_TabHovered = ImVec4(0.0f, 0.1176470592617989f, 0.1843137294054031f, 1.0f);
    const ImVec4 col_TabActive  = ImVec4(0.0f, 0.1176470592617989f, 0.1843137294054031f, 1.0f);
    const ImVec4 col_TabUnfocused =
        ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
    const ImVec4 col_TabUnfocusedActive =
        ImVec4(0.125490203499794f, 0.2745098173618317f, 0.572549045085907f, 1.0f);

    style.Colors[ImGuiCol_Tab]                       = col_Tab;
    style.Colors[ImGuiCol_TabHovered]                = col_TabHovered;
    style.Colors[ImGuiCol_TabSelected]               = col_TabActive;
    style.Colors[ImGuiCol_TabSelectedOverline]       = col_TabActive;
    style.Colors[ImGuiCol_TabDimmed]                 = col_TabUnfocused;
    style.Colors[ImGuiCol_TabDimmedSelected]         = col_TabUnfocusedActive;
    style.Colors[ImGuiCol_TabDimmedSelectedOverline] = col_TabUnfocusedActive;

    style.Colors[ImGuiCol_PlotLines] =
        ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] =
        ImVec4(0.0f, 0.6509804129600525f, 0.9843137264251709f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] =
        ImVec4(0.0f, 0.6509804129600525f, 0.9843137264251709f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] =
        ImVec4(0.0f, 0.9803921580314636f, 0.9725490212440491f, 1.0f);

    style.Colors[ImGuiCol_TableHeaderBg] =
        ImVec4(0.0117647061124444f, 0.05098039284348488f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] =
        ImVec4(0.0117647061124444f, 0.05098039284348488f, 0.07058823853731155f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] =
        ImVec4(0.0f, 0.1176470592617989f, 0.1843137294054031f, 1.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] =
        ImVec4(0.01960784383118153f, 0.09803921729326248f, 0.1372549086809158f, 1.0f);

    style.Colors[ImGuiCol_TextSelectedBg] =
        ImVec4(0.3490196168422699f, 0.5372549295425415f, 0.6313725709915161f, 0.5665236115455627f);
    style.Colors[ImGuiCol_DragDropTarget] =
        ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);

    style.Colors[ImGuiCol_NavCursor] = ImVec4(0.2666666805744171f, 0.2901960909366608f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] =
        ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.01960784383118153f,
                                                      0.09803921729326248f,
                                                      0.1372549086809158f,
                                                      0.3764705955982208f);
    style.Colors[ImGuiCol_ModalWindowDimBg]  = ImVec4(0.01960784383118153f,
                                                     0.09803921729326248f,
                                                     0.1372549086809158f,
                                                     0.3776823878288269f);

    style.Colors[ImGuiCol_DockingPreview] =
        ImVec4(0.0f, 0.6509804129600525f, 0.9843137264251709f, 1.0f);
    style.Colors[ImGuiCol_DockingEmptyBg] = style.Colors[ImGuiCol_WindowBg];
  }
} // namespace Zen