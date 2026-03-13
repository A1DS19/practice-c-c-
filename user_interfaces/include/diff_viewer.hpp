#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace DiffViewer {
class Window {
public:
    struct FileDiff {
        std::string path_;
        std::vector<std::string> content_;
        std::vector<std::string> diff_result_;
    };
    using FileDiffPtr = std::unique_ptr<FileDiff>;

    void draw();
    void draw_selection();
    void draw_diff_view();
    void draw_stats();
    void create_diff();
    FileDiffPtr load_file_content(const FileDiffPtr& file_diff);
    FileDiffPtr save_file_content(const FileDiffPtr& file_diff);

private:
    FileDiffPtr file_diff_1_;
    FileDiffPtr file_diff_2_;
};
} // namespace DiffViewer
