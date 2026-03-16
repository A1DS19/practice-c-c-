
#include "imgui.h"

#include <cstdint>
#include <tuple>
#include <vector>
namespace Paint {
class Window {

public:
    using PointData = std::tuple<ImVec2, ImColor, float>;
    Window()
        : points_({}), canvas_pos_({}), current_draw_color_(ImColor(255, 255, 255)),
          point_draw_size_(2.0F), file_name_buffer_("test.bin") {}
    void draw();

private:
    std::uint32_t num_rows_ = 800;
    std::uint32_t num_cols_ = 600;
    std::uint32_t num_channels_ = 3;
    ImVec2 canvas_size_ = ImVec2(static_cast<float>(num_rows_), static_cast<float>(num_cols_));
    std::vector<PointData> points_;
    ImVec2 canvas_pos_;
    ImColor current_draw_color_;
    float point_draw_size_;
    char file_name_buffer_[256];

    void draw_menu();
    void draw_canvas();
    void save_to_image_file();
    void load_from_image_file();
    void clear_canvas();
    void draw_color_buttons();
};
} // namespace Paint
