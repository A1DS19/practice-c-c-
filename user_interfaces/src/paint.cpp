#include "paint.hpp"

#include "imgui.h"
#include "main.hpp"

using namespace Paint;

void Window::draw() {
    constexpr static auto WINDOW_FLAGS = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    constexpr static auto WINDOW_SIZE = ImVec2(WINDOW_W, WINDOW_H);
    constexpr static auto WINDOW_POS = ImVec2(0.0F, 0.0F);

    ImGui::SetNextWindowSize(WINDOW_SIZE);
    ImGui::SetNextWindowPos(WINDOW_POS);

    ImGui::Begin("Paint 2.0", nullptr, WINDOW_FLAGS);

    draw_menu();
    draw_canvas();

    ImGui::End();
}

void Window::draw_menu() {}

void Window::draw_canvas() {}
void Window::save_to_image_file() {}
void Window::load_from_image_file() {}
void Window::clear_canvas() {}
void Window::draw_color_buttons() {}
