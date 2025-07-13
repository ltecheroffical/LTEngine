#ifndef _LTENGINE_SHAPE_HPP_
#define _LTENGINE_SHAPE_HPP_

#include <LTEngine/math/vec2.hpp>


namespace LTEngine::Shapes {
	struct Shape {
		f32 x = 0.0f, y = 0.0f;
		f32 rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;

		Shape() = default;
		Shape(f32 x, f32 y) : x(x), y(y) {
		}
		Shape(f32 x, f32 y, f32 rot_x, f32 rot_y, f32 rot_z) : x(x), y(y), rot_x(rot_x), rot_y(rot_y), rot_z(rot_z) {
		}
	};

	struct Shape3Di {
		i32 x = 0, y = 0, z = 0;
		i16 rot_x = 0, rot_y = 0, rot_z = 0;

		Shape3Di() = default;
		Shape3Di(i32 x, i32 y) : x(x), y(y) {
		}
		Shape3Di(i32 x, i32 y, i16 rot_x, i16 rot_y, i16 rot_z) : x(x), y(y), rot_x(rot_x), rot_y(rot_y), rot_z(rot_z) {
		}
	};
} // namespace LTEngine::Shapes

#endif
