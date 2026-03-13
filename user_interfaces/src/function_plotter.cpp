#include "function_plotter.hpp"

#include "imgui.h"
#include "implot.h"
#include "main.hpp"

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <format>
#include <string_view>

using namespace FunctionPlotter;

void Window::draw() {
    constexpr static auto WINDOW_FLAGS = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    constexpr static auto WINDOW_SIZE = ImVec2(WINDOW_W, WINDOW_H);
    constexpr static auto WINDOW_POS = ImVec2(0.0F, 0.0F);

    ImGui::SetNextWindowSize(WINDOW_SIZE);
    ImGui::SetNextWindowPos(WINDOW_POS);

    ImGui::Begin("Function Plotter", nullptr, WINDOW_FLAGS);
    draw_selection();
    draw_plot();
    ImGui::End();
}

Window::Function Window::function_name_mapping(std::string_view function_name) {
    if (std::string_view{"sin(x)"} == function_name) {
        return Window::Function::SIN;
    }

    if (std::string_view{"cos(x)"} == function_name) {
        return Window::Function::COS;
    }

    return Window::Function::NONE;
}

double Window::evaluate_function(const Window::Function& function, const double param) {
    switch (function) {
        case Window::Function::COS: {
            return std::sin(param);
        }
        case Window::Function::SIN: {
            return std::cos(param);
        }
        case Window::Function::NONE:
        default: {
            return 0;
        }
    }
}

void Window::draw_plot() {
    static constexpr auto NUM_POINTS = 10'000;
    static constexpr auto X_MIN = -100.0;
    static constexpr auto X_MAX = 100.0;
    static const auto X_STEP = (std::abs(X_MAX) + std::abs(X_MIN)) / NUM_POINTS;
    static auto xs = std::array<double, NUM_POINTS>{};
    static auto ys = std::array<double, NUM_POINTS>{};

    if (selected_functions_.size() == 0 ||
        (selected_functions_.size() == 1 && *selected_functions_.begin() == Function::NONE)) {
        ImPlot::BeginPlot("###plot", ImVec2(-1.0F, -1.0F), ImPlotFlags_NoTitle);
        ImPlot::EndPlot();
        return;
    }

    ImPlot::BeginPlot("###plot", ImVec2(-1.0F, -1.0F), ImPlotFlags_NoTitle);
    for (const auto& function : selected_functions_) {
        auto x = X_MIN;
        for (std::size_t i = 0; i < NUM_POINTS; ++i) {
            xs[i] = x;
            ys[i] = evaluate_function(function, x);
            x += X_STEP;
        }

        const auto PLOT_LABEL = std::format("##function{}", static_cast<int>(function));
        ImPlot::PlotLine(PLOT_LABEL.data(), xs.data(), ys.data(), NUM_POINTS);
    }
    ImPlot::EndPlot();
}

void Window::draw_selection() {
    for (const auto FUNC_NAME : Window::FUNCTION_NAMES) {
        const auto CURR_FUNCTION = function_name_mapping(FUNC_NAME);
        auto selected = selected_functions_.contains(CURR_FUNCTION);

        if (ImGui::Checkbox(FUNC_NAME.data(), &selected)) {
            if (selected) {
                selected_functions_.insert(CURR_FUNCTION);
            } else {
                selected_functions_.erase(CURR_FUNCTION);
            }
        }
    }
}
