#pragma once

#include "imgui.h"
#include "main.hpp"

#include <array>
#include <cstddef>
#include <cstring>
#include <string>
#include <string_view>
namespace TextEditor {
class Window {
public:
    static constexpr auto BUFFER_SIZE = std::size_t{1024};
    Window() : current_filename_({}) { clear_text_buffer(); }
    void draw();

private:
    std::array<char, BUFFER_SIZE> text_buffer_ = std::array<char, BUFFER_SIZE>{};
    void clear_text_buffer() { text_buffer_.fill(0); }
    std::string current_filename_;
    void save_to_file(std::string_view filename);
    void load_from_file(std::string_view filename);
    std::string get_file_extension(std::string_view filename);
    static constexpr auto POPUP_FLAGS = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;
    static constexpr auto POPUP_SIZE = ImVec2(300.0F, 200.0F);
    static constexpr auto POPUP_BUTTON_SIZE = ImVec2(50.0F, 30.0F);
    static constexpr auto POPUP_POSITION = ImVec2((WINDOW_W / 2.0F) - (POPUP_SIZE.x / 2.0F),
                                                  (WINDOW_H / 2.0F) - (POPUP_SIZE.y / 2.0F));

    void draw_menu();
    void draw_content();
    void draw_info();

    void draw_save_popup();
    void draw_load_popup();
};
} // namespace TextEditor
