#include "text_editor.hpp"

#include "imgui.h"
#include "main.hpp"
#include "shortcut_manager.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

using namespace TextEditor;
using namespace Utils;
namespace fs = std::filesystem;

void Window::draw() {
    constexpr static auto WINDOW_FLAGS = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |

                                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    constexpr static auto WINDOW_SIZE = ImVec2(WINDOW_W, WINDOW_H);
    constexpr static auto WINDOW_POS = ImVec2(0.0F, 0.0F);

    ImGui::SetNextWindowSize(WINDOW_SIZE);
    ImGui::SetNextWindowPos(WINDOW_POS);

    ImGui::Begin("Text Editor", nullptr, WINDOW_FLAGS);
    draw_menu();
    draw_content();
    draw_info();

    ImGui::End();
}

void Window::draw_menu() {

    if (ImGui::Button("Save") ||
        (get_shortcut(Shortcut::CNTRL_PRESSED) && get_shortcut(Shortcut::S_PRESSED))) {
        ImGui::OpenPopup("Save File");
    }

    ImGui::SameLine();

    if (ImGui::Button("Load") ||
        (get_shortcut(Shortcut::CNTRL_PRESSED) && get_shortcut(Shortcut::L_PRESSED))) {
        ImGui::OpenPopup("Load file");
    }

    ImGui::SameLine();

    if (ImGui::Button("Clear")) {
        clear_text_buffer();
    }

    draw_load_popup();
    draw_save_popup();
}

void Window::draw_save_popup() {
    static char save_filename_buffer[256] = "text.txt";

    ImGui::SetNextWindowSize(POPUP_SIZE);
    ImGui::SetNextWindowPos(POPUP_POSITION);

    if (ImGui::BeginPopupModal("Save File", nullptr, POPUP_FLAGS)) {
        ImGui::InputText("Filename", save_filename_buffer, sizeof(save_filename_buffer));
        if (ImGui::Button("Save", POPUP_BUTTON_SIZE)) {
            save_to_file(save_filename_buffer);
            current_filename_ = save_filename_buffer;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", POPUP_BUTTON_SIZE) || get_shortcut(Shortcut::ESC_PRESSED)) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Window::draw_load_popup() {
    static char load_filename_buffer[256] = "text.txt";
    ImGui::SetNextWindowSize(POPUP_SIZE);
    ImGui::SetNextWindowPos(POPUP_POSITION);

    if (ImGui::BeginPopupModal("Load file", nullptr, POPUP_FLAGS)) {
        ImGui::InputText("Filename", load_filename_buffer, sizeof(load_filename_buffer));
        if (ImGui::Button("Load", POPUP_BUTTON_SIZE)) {
            load_from_file(load_filename_buffer);
            current_filename_ = load_filename_buffer;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", POPUP_BUTTON_SIZE) || get_shortcut(Shortcut::ESC_PRESSED)) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Window::draw_content() {
    static constexpr auto INPUT_TEXT_SIZE = ImVec2(WINDOW_W, WINDOW_H);
    static constexpr auto LINE_NUMBER_SIZE = ImVec2(30.0F, INPUT_TEXT_SIZE.y);
    static constexpr auto INPUT_TEXT_FLAGS =
        ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_NoHorizontalScroll;

    ImGui::BeginChild("line-numbers", LINE_NUMBER_SIZE);
    const auto LINE_COUNT = std::count(text_buffer_.begin(), text_buffer_.end(), '\n') + 1;

    for (auto i = 1; i <= LINE_COUNT; ++i) {
        ImGui::Text("%d", i);
    }

    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::InputTextMultiline("###input-text", text_buffer_.data(), BUFFER_SIZE, INPUT_TEXT_SIZE,
                              INPUT_TEXT_FLAGS);
}

void Window::draw_info() {
    if (current_filename_.size() == 0) {
        ImGui::Text("No file open");
        return;
    }

    const auto FILE_EXTENSION = get_file_extension(current_filename_);
    ImGui::Text("Opened file %s | file extension %s", current_filename_.data(),
                FILE_EXTENSION.data());
}

void Window::save_to_file(std::string_view filename) {
    auto out = std::ofstream{filename.data()};
    if (out.is_open()) {
        out << text_buffer_.data();
        out.close();
    }
}

void Window::load_from_file(std::string_view filename) {
    auto in = std::ifstream{filename.data()};
    if (in.is_open()) {
        auto buffer = std::stringstream();
        buffer << in.rdbuf();
        const auto str = buffer.str();
        const auto copy_size = std::min(str.size(), BUFFER_SIZE - 1);
        std::copy_n(str.data(), copy_size, text_buffer_.data());
        text_buffer_[copy_size] = '\0';
        in.close();
    }
}

std::string Window::get_file_extension(std::string_view filename) {
    const auto FILE_PATH = fs::path(filename);
    return FILE_PATH.extension().string();
}
