#include "diff_viewer.hpp"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "main.hpp"

#include <memory>

using namespace DiffViewer;

void Window::draw() {
    constexpr static auto WINDOW_FLAGS = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    constexpr static auto WINDOW_SIZE = ImVec2(WINDOW_W, WINDOW_H);
    constexpr static auto WINDOW_POS = ImVec2(0.0F, 0.0F);

    ImGui::SetNextWindowSize(WINDOW_SIZE);
    ImGui::SetNextWindowPos(WINDOW_POS);

    ImGui::Begin("Diff Viewer", nullptr, WINDOW_FLAGS);
    draw_selection();
    draw_diff_view();
    draw_stats();
    ImGui::End();
}

void Window::draw_selection() {

    file_diff_1_ = std::make_unique<Window::FileDiff>();
    file_diff_2_ = std::make_unique<Window::FileDiff>();

    ImGui::InputText("Left", &file_diff_1_->path_);
    ImGui::SameLine();
    if (ImGui::Button("Save###left")) {
        save_file_content(file_diff_1_);
    }

    ImGui::SameLine();

    ImGui::InputText("Rigth", &file_diff_2_->path_);
    ImGui::SameLine();
    if (ImGui::Button("Save###rigth")) {
        save_file_content(file_diff_2_);
    }

    if (ImGui::Button("Compare")) {
        file_diff_1_ = load_file_content(file_diff_1_);
        file_diff_2_ = load_file_content(file_diff_2_);
    }
}

void Window::draw_diff_view() {}

void Window::draw_stats() {}

void Window::create_diff() {}

Window::FileDiffPtr Window::load_file_content(const Window::FileDiffPtr& file_diff) {}

Window::FileDiffPtr Window::save_file_content(const Window::FileDiffPtr& file_diff) {}
