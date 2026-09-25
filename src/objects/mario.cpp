#include "mario.hpp"

#include "map_movable.hpp"
#include "moving_platform.hpp"

using lae::Mario;

Mario::Mario(const Coord& top_left, const int width, const int height) 
	: Movable(top_left, width, height, 0, 0) {}

lae::Rect Mario::get_rect() const noexcept {
	return {top_left, width, height};
}

lae::Speed Mario::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void Mario::move_map_left() noexcept {
	move_horizontal_offset(lae::MapMovable::MAP_STEP);
}

void Mario::move_map_right() noexcept {
	move_horizontal_offset(-lae::MapMovable::MAP_STEP);
}

void Mario::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void Mario::process_mario_collision(Collisionable* mario) noexcept {}

void Mario::process_vertical_static_collision(Rect* obj) noexcept {
	if (vspeed > 0) {
		// Марио упал на корабль.
		top_left.y -= vspeed;
	} else if (vspeed < 0) {
		// Марио ударился головой о полку и после этого должен падать вниз.
		top_left.y -= vspeed;
	}
	vspeed = 0;
}

void Mario::process_vertical_platform_collision(MovingPlatform* obj) noexcept {
    if (vspeed > 0) {
        // Марио упал сверху
        top_left.y -= vspeed;
        vspeed = 0;

        bool is_moving_platform = (dynamic_cast<MovingPlatform*>(obj) != nullptr);

        if (is_moving_platform) {
            float y_speed_of_platform = obj->get_speed().v;
            float x_speed_of_platform = obj->get_speed().h;

            top_left.y += y_speed_of_platform;
            top_left.x += x_speed_of_platform;
        }
    }
}
