#pragma once

#include <array>
#include <cstdint>
#include <set>
#include <string_view>
namespace FunctionPlotter {
class Window {
public:
    enum class Function : uint8_t { NONE, SIN, COS };
    std::set<Function> selected_functions_;
    Window() : selected_functions_({}) {}
    void draw();

private:
    static constexpr auto FUNCTION_NAMES =
        std::array<std::string_view, 3>{"unk", "sin(x)", "cos(x)"};
    Function function_name_mapping(std::string_view function_name);
    double evaluate_function(const Function& function, const double param);
    void draw_selection();
    void draw_plot();
};
} // namespace FunctionPlotter
