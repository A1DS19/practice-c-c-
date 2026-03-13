#include "imgui.h"

#include <cstdint>

namespace Utils {

enum class Shortcut : std::uint8_t { CNTRL_PRESSED, ESC_PRESSED, S_PRESSED, L_PRESSED };

inline bool get_shortcut(const Shortcut& shortcut) {
    switch (shortcut) {
        case Shortcut::CNTRL_PRESSED: {
            return ImGui::GetIO().KeyCtrl;
        }
        case Shortcut::ESC_PRESSED:
            return ImGui::IsKeyPressed(ImGuiKey_Escape);
        case Shortcut::S_PRESSED: {
            return ImGui::IsKeyPressed(ImGuiKey_S);
        }
        case Shortcut::L_PRESSED: {
            return ImGui::IsKeyPressed(ImGuiKey_L);
        }
        default: {
            return false;
        }
    }
}

} // namespace Utils
