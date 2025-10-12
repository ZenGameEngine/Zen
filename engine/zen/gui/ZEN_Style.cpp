#include <zen/gui/ZEN_Style.h>

#include <include/imgui/imgui.h>
namespace Zen {
  void styleSetup() {
    // RAGE2 style from ImThemes
    ImGuiStyle &style = ImGui::GetStyle();

    style.Alpha                    = 1.0f;
    style.DisabledAlpha            = 0.5f;
    style.WindowPadding            = ImVec2(8.0f, 8.0f);
    style.WindowRounding           = 0.0f;
    style.WindowBorderSize         = 0.0f;
    style.WindowMinSize            = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign         = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding            = 0.0f;
    style.ChildBorderSize          = 1.0f;
    style.PopupRounding            = 0.0f;
    style.PopupBorderSize          = 1.0f;
    style.FramePadding             = ImVec2(4.0f, 3.0f);
    style.FrameRounding            = 0.0f;
    style.FrameBorderSize          = 0.0f;
    style.ItemSpacing              = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing         = ImVec2(4.0f, 4.0f);
    style.CellPadding              = ImVec2(4.0f, 2.0f);
    style.IndentSpacing            = 21.0f;
    style.ColumnsMinSpacing        = 6.0f;
    style.ScrollbarSize            = 14.0f;
    style.ScrollbarRounding        = 0.0f;
    style.GrabMinSize              = 10.0f;
    style.GrabRounding             = 0.0f;
    style.TabRounding              = 0.0f;
    style.TabBorderSize            = 0.0f;
    // style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign     = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] =
        ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);

    style.Colors[ImGuiCol_WindowBg] =
        ImVec4(0.02745098061859608f, 0.03529411926865578f, 0.04313725605607033f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] =
        ImVec4(0.05490196123719215f, 0.07058823853731155f, 0.08235294371843338f, 1.0f);
    style.Colors[ImGuiCol_PopupBg] =
        ImVec4(0.02745098061859608f, 0.03529411926865578f, 0.04313725605607033f, 1.0f);
    style.Colors[ImGuiCol_Border] =
        ImVec4(0.003921568859368563f, 0.007843137718737125f, 0.007843137718737125f, 1.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.003921568859368563f,
                                                 0.007843137718737125f,
                                                 0.007843137718737125f,
                                                 0.6980392336845398f);

    style.Colors[ImGuiCol_FrameBg] =
        ImVec4(0.05490196123719215f, 0.07058823853731155f, 0.08235294371843338f, 1.0f);
    style.Colors[ImGuiCol_FrameBgHovered] =
        ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 1.0f);
    style.Colors[ImGuiCol_FrameBgActive] =
        ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2313725501298904f, 0.4980392158031464f);

    style.Colors[ImGuiCol_TitleBg] =
        ImVec4(0.05490196123719215f, 0.07058823853731155f, 0.08235294371843338f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] =
        ImVec4(0.01568627543747425f, 0.01960784383118153f, 0.0235294122248888f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] =
        ImVec4(0.05490196123719215f, 0.05490196123719215f, 0.05490196123719215f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] =
        ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 0.3450980484485626f);

    style.Colors[ImGuiCol_DockingPreview] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f,
                                                0.01960784383118153f,
                                                0.01960784383118153f,
                                                0.529411792755127f);
    style.Colors[ImGuiCol_ScrollbarGrab] =
        ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] =
        ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] =
        ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);

    style.Colors[ImGuiCol_CheckMark] =
        ImVec4(0.9058823585510254f, 0.1568627506494522f, 0.2196078449487686f, 1.0f);

    style.Colors[ImGuiCol_SliderGrab]       = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    style.Colors[ImGuiCol_Button] =
        ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] =
        ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2313725501298904f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] =
        ImVec4(0.05098039284348488f, 0.062745101749897f, 0.07450980693101883f, 1.0f);

    style.Colors[ImGuiCol_Header] =
        ImVec4(0.05098039284348488f, 0.062745101749897f, 0.07450980693101883f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] =
        ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2313725501298904f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] =
        ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 1.0f);
    style.Colors[ImGuiCol_Separator] =
        ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.501960813999176f);
    style.Colors[ImGuiCol_SeparatorHovered] =
        ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.6695278882980347f);
    style.Colors[ImGuiCol_SeparatorActive] =
        ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9570815563201904f);
    style.Colors[ImGuiCol_ResizeGrip] =
        ImVec4(0.1019607856869698f, 0.1137254908680916f, 0.1294117718935013f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ResizeGripHovered] =
        ImVec4(0.2039215713739395f, 0.2078431397676468f, 0.2156862765550613f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ResizeGripActive] =
        ImVec4(0.3019607961177826f, 0.3019607961177826f, 0.3019607961177826f, 0.2000000029802322f);

    style.Colors[ImGuiCol_Tab] =
        ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 1.0f);
    style.Colors[ImGuiCol_TabHovered] =
        ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2313725501298904f, 1.0f);
    style.Colors[ImGuiCol_TabSelected] =
        ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);
    style.Colors[ImGuiCol_TabSelectedOverline] =
        ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);
    style.Colors[ImGuiCol_TabDimmed] =
        ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 0.501960813999176f);
    style.Colors[ImGuiCol_TabDimmedSelected] =
        ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 0.501960813999176f);
    style.Colors[ImGuiCol_TabDimmedSelectedOverline] =
        ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 0.501960813999176f);

    style.Colors[ImGuiCol_PlotLines] =
        ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] =
        ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] =
        ImVec4(0.9647058844566345f, 0.2000000029802322f, 0.2235294133424759f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] =
        ImVec4(0.772549033164978f, 0.1607843190431595f, 0.1843137294054031f, 1.0f);

    style.Colors[ImGuiCol_TableHeaderBg] =
        ImVec4(0.1490196138620377f, 0.1647058874368668f, 0.1725490242242813f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] =
        ImVec4(0.1882352977991104f, 0.196078434586525f, 0.2039215713739395f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] =
        ImVec4(0.2431372553110123f, 0.2549019753932953f, 0.2666666805744171f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.09803921729326248f,
                                               0.01960784383118153f,
                                               0.0235294122248888f,
                                               0.05882352963089943f);
    style.Colors[ImGuiCol_TableRowBgAlt] =
        ImVec4(0.9960784316062927f, 0.9215686321258545f, 0.9215686321258545f, 0.05882352963089943f);
    style.Colors[ImGuiCol_TextSelectedBg] =
        ImVec4(0.9058823585510254f, 0.1568627506494522f, 0.2196078449487686f, 1.0f);

    style.Colors[ImGuiCol_DragDropTarget] =
        ImVec4(0.9686274528503418f, 0.2784313857555389f, 0.3098039329051971f, 1.0f);
    style.Colors[ImGuiCol_NavHighlight] =
        ImVec4(0.1803921610116959f, 0.2274509817361832f, 0.2784313857555389f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.0f, 0.0f, 0.0f, 0.5450980663299561f);
    style.Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.0f, 0.0f, 0.0f, 0.3529411852359772f);
  }
} // namespace Zen