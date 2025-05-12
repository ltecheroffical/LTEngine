#ifndef _LTCORE_VEC3_HPP_
#define _LTCORE_VEC3_HPP_

#include <cmath>
#include <LTCore/common/compiler_utils.h>

namespace LTCore::Math {
	LTCORE_PACK_START() struct Vec3 {
		f32 x, y, z;

		static const Vec3 Zero;
		static const Vec3 One;
		static const Vec3 Up;
		static const Vec3 Down;
		static const Vec3 Left;
		static const Vec3 Right;
		static const Vec3 Forward;
		static const Vec3 Backward;

		Vec3() : x(0), y(0), z(0) {}
		Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

		Vec3 normalize() {
			f32 mag = std::sqrt(x * x + y * y + z * z);
			if (mag == 0.f) return Zero;
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

		bool operator==(const Vec3 &other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const Vec3 &other) const { return !(*this == other); }

		void operator+=(Vec3 b) { x += b.x; y += b.y; z += b.z; }
		void operator+=(u32 b) { x += b; y += b; z += b; }

		void operator-=(Vec3 b) { x -= b.x; y -= b.y; z -= b.z; }
		void operator-=(u32 b) { x -= b; y -= b; z -= b; }

		void operator*=(Vec3 b) { x *= b.x; y *= b.y; z *= b.z; }
		void operator*=(u32 b) { x *= b; y *= b; z *= b; }

		void operator/=(Vec3 b) { x /= b.x; y /= b.y; z /= b.z; }
		void operator/=(u32 b) { x /= b; y /= b; z /= b; }

	} LTCORE_PACK_END();

	typedef Vec3 Vec3f;

	LTCORE_PACK_START() struct Vec3i {
		i32 x, y, z;

		static const Vec3i Zero;
		static const Vec3i One;
		static const Vec3i Up;
		static const Vec3i Down;
		static const Vec3i Left;
		static const Vec3i Right;
		static const Vec3i Forward;
		static const Vec3i Backward;

		Vec3i() : x(0), y(0), z(0) {}
		Vec3i(i32 x, i32 y, i32 z) : x(x), y(y), z(z) {}

		Vec3i normalize() {
			f32 mag = std::sqrt(x * x + y * y + z * z);
			if (mag == 0.f) return Zero;
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

	} LTCORE_PACK_END();

	LTCORE_PACK_START() struct Vec3u {
		u32 x, y, z;

		static const Vec3u Zero;
		static const Vec3u One;

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

	} LTCORE_PACK_END();

	inline const Vec3 Vec3::Zero = Vec3(0, 0, 0);
	inline const Vec3 Vec3::One = Vec3(1, 1, 1);
	inline const Vec3 Vec3::Up = Vec3(0, 1, 0);
	inline const Vec3 Vec3::Down = Vec3(0, -1, 0);
	inline const Vec3 Vec3::Left = Vec3(-1, 0, 0);
	inline const Vec3 Vec3::Right = Vec3(1, 0, 0);
	inline const Vec3 Vec3::Forward = Vec3(0, 0, 1);
	inline const Vec3 Vec3::Backward = Vec3(0, 0, -1);

	inline const Vec3i Vec3i::Zero = Vec3i(0, 0, 0);
	inline const Vec3i Vec3i::One = Vec3i(1, 1, 1);
	inline const Vec3i Vec3i::Up = Vec3i(0, 1, 0);
	inline const Vec3i Vec3i::Down = Vec3i(0, -1, 0);
	inline const Vec3i Vec3i::Left = Vec3i(-1, 0, 0);
	inline const Vec3i Vec3i::Right = Vec3i(1, 0, 0);
	inline const Vec3i Vec3i::Forward = Vec3i(0, 0, 1);
	inline const Vec3i Vec3i::Backward = Vec3i(0, 0, -1);

	inline const Vec3u Vec3u::Zero = Vec3u(0, 0, 0);
	inline const Vec3u Vec3u::One = Vec3u(1, 1, 1);
} // namespace LTCore::Math

#endif // _LTCORE_VEC3_HPP_