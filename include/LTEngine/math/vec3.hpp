#ifndef _LTENGINE_VEC3_HPP_
#define _LTENGINE_VEC3_HPP_

#include <cmath>

#include <LTEngine/common/compiler_utils.h>

namespace LTEngine::Math {
	LTENGINE_PACK_START() struct Vec3 {
		f32 x, y, z;

		static const Vec3 ZERO;
		static const Vec3 ONE;
		static const Vec3 UP;
		static const Vec3 DOWN;
		static const Vec3 LEFT;
		static const Vec3 RIGHT;
		static const Vec3 FORWARD;
		static const Vec3 BACKWARD;

		Vec3() : x(0), y(0), z(0) {}
		Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

		Vec3 normalize() {
			f32 mag = std::sqrt(x * x + y * y + z * z);
			if (mag == 0.f) return ZERO;
			return Vec3(x / mag, y / mag, z / mag);
		}

		f32 distance(Vec3 other) {
			f32 dx = other.x - x;
			f32 dy = other.y - y;
			f32 dz = other.z - z;
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}

		Vec3 operator+(Vec3 b) const { return Vec3(x + b.x, y + b.y, z + b.z); }
		Vec3 operator+(u32 b) const { return Vec3(x + b, y + b, z + b); }

		Vec3 operator-(Vec3 b) const { return Vec3(x - b.x, y - b.y, z - b.z); }
		Vec3 operator-(u32 b) const { return Vec3(x - b, y - b, z - b); }

		Vec3 operator*(Vec3 b) const { return Vec3(x * b.x, y * b.y, z * b.z); }
		Vec3 operator*(u32 b) const { return Vec3(x * b, y * b, z * b); }

		Vec3 operator/(Vec3 b) const { return Vec3(x / b.x, y / b.y, z / b.z); }
		Vec3 operator/(u32 b) const { return Vec3(x / b, y / b, z / b); }

		bool operator==(const Vec3 &other) const { return LTEngine_f32_eq(x, other.x) && LTEngine_f32_eq(y, other.y) && LTEngine_f32_eq(z, other.z); }
		bool operator!=(const Vec3 &other) const { return !(*this == other); }

		void operator+=(Vec3 b) { x += b.x; y += b.y; z += b.z; }
		void operator+=(u32 b) { x += b; y += b; z += b; }

		void operator-=(Vec3 b) { x -= b.x; y -= b.y; z -= b.z; }
		void operator-=(u32 b) { x -= b; y -= b; z -= b; }

		void operator*=(Vec3 b) { x *= b.x; y *= b.y; z *= b.z; }
		void operator*=(u32 b) { x *= b; y *= b; z *= b; }

		void operator/=(Vec3 b) { x /= b.x; y /= b.y; z /= b.z; }
		void operator/=(u32 b) { x /= b; y /= b; z /= b; }

	} LTENGINE_PACK_END();

	typedef Vec3 Vec3f;

	LTENGINE_PACK_START() struct Vec3i {
		i32 x, y, z;

		static const Vec3i ZERO;
		static const Vec3i ONE;
		static const Vec3i UP;
		static const Vec3i DOWN;
		static const Vec3i LEFT;
		static const Vec3i RIGHT;
		static const Vec3i FORWARD;
		static const Vec3i BACKWARD;

		Vec3i() : x(0), y(0), z(0) {}
		Vec3i(i32 x, i32 y, i32 z) : x(x), y(y), z(z) {}

		Vec3i normalize() {
			f32 mag = std::sqrt(x * x + y * y + z * z);
			if (mag == 0.f) return ZERO;
			return Vec3i(x / mag, y / mag, z / mag);
		}

		f32 distance(Vec3i other) {
			f32 dx = other.x - x;
			f32 dy = other.y - y;
			f32 dz = other.z - z;
			return std::sqrt(dx * dx + dy * dy + dz * dz);
		}

		Vec3i operator+(Vec3i b) { return Vec3i(x + b.x, y + b.y, z + b.z); }
		Vec3i operator+(u32 b) { return Vec3i(x + b, y + b, z + b); }

		Vec3i operator-(Vec3i b) { return Vec3i(x - b.x, y - b.y, z - b.z); }
		Vec3i operator-(u32 b) { return Vec3i(x - b, y - b, z - b); }

		Vec3i operator*(Vec3i b) { return Vec3i(x * b.x, y * b.y, z * b.z); }
		Vec3i operator*(u32 b) { return Vec3i(x * b, y * b, z * b); }

		Vec3i operator/(Vec3i b) { return Vec3i(x / b.x, y / b.y, z / b.z); }
		Vec3i operator/(u32 b) { return Vec3i(x / b, y / b, z / b); }

		bool operator==(const Vec3i &other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const Vec3i &other) const { return !(*this == other); }

		void operator+=(Vec3i b) { x += b.x; y += b.y; z += b.z; }
		void operator+=(u32 b) { x += b; y += b; z += b; }

		void operator-=(Vec3i b) { x -= b.x; y -= b.y; z -= b.z; }
		void operator-=(u32 b) { x -= b; y -= b; z -= b; }

		void operator*=(Vec3i b) { x *= b.x; y *= b.y; z *= b.z; }
		void operator*=(u32 b) { x *= b; y *= b; z *= b; }

		void operator/=(Vec3i b) { x /= b.x; y /= b.y; z /= b.z; }
		void operator/=(u32 b) { x /= b; y /= b; z /= b; }

	} LTENGINE_PACK_END();

	LTENGINE_PACK_START() struct Vec3u {
		u32 x, y, z;

		static const Vec3u ZERO;
		static const Vec3u ONE;

		Vec3u() : x(0), y(0), z(0) {}
		Vec3u(u32 x, u32 y, u32 z) : x(x), y(y), z(z) {}

		Vec3u operator+(Vec3u b) { return Vec3u(x + b.x, y + b.y, z + b.z); }
		Vec3u operator+(u32 b) { return Vec3u(x + b, y + b, z + b); }

		Vec3u operator-(Vec3u b) { return Vec3u(x - b.x, y - b.y, z - b.z); }
		Vec3u operator-(u32 b) { return Vec3u(x - b, y - b, z - b); }

		Vec3u operator*(Vec3u b) { return Vec3u(x * b.x, y * b.y, z * b.z); }
		Vec3u operator*(u32 b) { return Vec3u(x * b, y * b, z * b); }

		Vec3u operator/(Vec3u b) { return Vec3u(x / b.x, y / b.y, z / b.z); }
		Vec3u operator/(u32 b) { return Vec3u(x / b, y / b, z / b); }

		bool operator==(const Vec3u &other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const Vec3u &other) const { return !(*this == other); }

		void operator+=(Vec3u b) { x += b.x; y += b.y; z += b.z; }
		void operator+=(u32 b) { x += b; y += b; z += b; }

		void operator-=(Vec3u b) { x -= b.x; y -= b.y; z -= b.z; }
		void operator-=(u32 b) { x -= b; y -= b; z -= b; }

		void operator*=(Vec3u b) { x *= b.x; y *= b.y; z *= b.z; }
		void operator*=(u32 b) { x *= b; y *= b; z *= b; }

		void operator/=(Vec3u b) { x /= b.x; y /= b.y; z /= b.z; }
		void operator/=(u32 b) { x /= b; y /= b; z /= b; }

	} LTENGINE_PACK_END();

	inline const Vec3 Vec3::ZERO = Vec3(0, 0, 0);
	inline const Vec3 Vec3::ONE = Vec3(1, 1, 1);
	inline const Vec3 Vec3::UP = Vec3(0, 1, 0);
	inline const Vec3 Vec3::DOWN = Vec3(0, -1, 0);
	inline const Vec3 Vec3::LEFT = Vec3(-1, 0, 0);
	inline const Vec3 Vec3::RIGHT = Vec3(1, 0, 0);
	inline const Vec3 Vec3::FORWARD = Vec3(0, 0, 1);
	inline const Vec3 Vec3::BACKWARD = Vec3(0, 0, -1);

	inline const Vec3i Vec3i::ZERO = Vec3i(0, 0, 0);
	inline const Vec3i Vec3i::ONE = Vec3i(1, 1, 1);
	inline const Vec3i Vec3i::UP = Vec3i(0, 1, 0);
	inline const Vec3i Vec3i::DOWN = Vec3i(0, -1, 0);
	inline const Vec3i Vec3i::LEFT = Vec3i(-1, 0, 0);
	inline const Vec3i Vec3i::RIGHT = Vec3i(1, 0, 0);
	inline const Vec3i Vec3i::FORWARD = Vec3i(0, 0, 1);
	inline const Vec3i Vec3i::BACKWARD = Vec3i(0, 0, -1);

	inline const Vec3u Vec3u::ZERO = Vec3u(0, 0, 0);
	inline const Vec3u Vec3u::ONE = Vec3u(1, 1, 1);
} // namespace LTEngine::Math

#endif // _LTENGINE_VEC3_HPP_
