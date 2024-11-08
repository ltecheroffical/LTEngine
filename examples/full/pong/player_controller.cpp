#include "player_controller.hpp"


using namespace Pong;


i32 PlayerController::getDirection() {
    if (m_window->isKeyPressed(LTEngine::WindowKey::KEY_UP)) {
        return -1;
    } else if (m_window->isKeyPressed(LTEngine::WindowKey::KEY_DOWN)) {
        return 1;
    }
    return 0;
}
