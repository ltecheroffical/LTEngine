#pragma once

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::Math {
	struct Vec2 {
		f32 x, y;

		static const Vec2 ZERO;
		static const Vec2 ONE;
		static const Vec2 UP;
		static const Vec2 DOWN;
		static const Vec2 LEFT;
		static const Vec2 RIGHT;

		Vec2() : x(0), y(0) {}
		Vec2(f32 x, f32 y) : x(x), y(y) {}

		Vec2 operator+(Vec2 b) const { return Vec2(x + b.x, y + b.y); }

		Vec2 operator+(u32 b) const { return Vec2(x + b, y + b); }

		Vec2 operator-(Vec2 b) const { return Vec2(x - b.x, y - b.y); }

		Vec2 operator-(u32 b) const { return Vec2(x - b, y - b); }

		Vec2 operator*(Vec2 b) const { return Vec2(x * b.x, y * b.y); }

		Vec2 operator*(u32 b) const { return Vec2(x * b, y * b); }

		Vec2 operator/(Vec2 b) const { return Vec2(x / b.x, y / b.y); }

		Vec2 operator/(u32 b) const { return Vec2(x / b, y / b); }

		bool operator<(const Vec2 &other) const { return x < other.x || (x == other.x && y < other.y); }


		void operator+=(Vec2 b) {
			x += b.x;
			y += b.y;
		}

		void operator+=(u32 b) {
			x += b;
			y += b;
		}

		void operator-=(Vec2 b) {
			x -= b.x;
			y -= b.y;
		}

		void operator-=(u32 b) {
			x -= b;
			y -= b;
		}

		void operator*=(Vec2 b) {
			x *= b.x;
			y *= b.y;
		}

		void operator*=(u32 b) {
			x *= b;
			y *= b;
		}

		void operator/=(Vec2 b) {
			x /= b.x;
			y /= b.y;
		}

		void operator/=(u32 b) {
			x /= b;
			y /= b;
		}
	};

	struct Vec2i {
		i32 x, y;

		static const Vec2i ZERO;
		static const Vec2i ONE;
		static const Vec2i UP;
		static const Vec2i DOWN;
		static const Vec2i LEFT;
		static const Vec2i RIGHT;

		Vec2i() : x(0), y(0) {}
		Vec2i(i32 x, i32 y) : x(x), y(y) {}

		Vec2i operator+(Vec2i b) { return Vec2i(x + b.x, y + b.y); }

		Vec2i operator+(u32 b) { return Vec2i(x + b, y + b); }

		Vec2i operator-(Vec2i b) { return Vec2i(x - b.x, y - b.y); }

		Vec2i operator-(u32 b) { return Vec2i(x - b, y - b); }

		Vec2i operator*(Vec2i b) { return Vec2i(x * b.x, y * b.y); }

		Vec2i operator*(u32 b) { return Vec2i(x * b, y * b); }

		Vec2i operator/(Vec2i b) { return Vec2i(x / b.x, y / b.y); }

		Vec2i operator/(u32 b) { return Vec2i(x / b, y / b); }

		bool operator<(const Vec2i &other) const { return x < other.x || (x == other.x && y < other.y); }


		void operator+=(Vec2i b) {
			x += b.x;
			y += b.y;
		}

		void operator+=(u32 b) {
			x += b;
			y += b;
		}

		void operator-=(Vec2i b) {
			x -= b.x;
			y -= b.y;
		}

		void operator-=(u32 b) {
			x -= b;
			y -= b;
		}

		void operator*=(Vec2i b) {
			x *= b.x;
			y *= b.y;
		}

		void operator*=(u32 b) {
			x *= b;
			y *= b;
		}

		void operator/=(Vec2i b) {
			x /= b.x;
			y /= b.y;
		}

		void operator/=(u32 b) {
			x /= b;
			y /= b;
		}
	};

	struct Vec2u {
		u32 x, y;

		static const Vec2u ZERO;
		static const Vec2u ONE;

		Vec2u() : x(0), y(0) {}
		Vec2u(u32 x, u32 y) : x(x), y(y) {}

		Vec2u operator+(Vec2u b) { return Vec2u(x + b.x, y + b.y); }

		Vec2u operator+(u32 b) { return Vec2u(x + b, y + b); }

		Vec2u operator-(Vec2u b) { return Vec2u(x - b.x, y - b.y); }

		Vec2u operator-(u32 b) { return Vec2u(x - b, y - b); }

		Vec2u operator*(Vec2u b) { return Vec2u(x * b.x, y * b.y); }

		Vec2u operator*(u32 b) { return Vec2u(x * b, y * b); }

		Vec2u operator/(Vec2u b) { return Vec2u(x / b.x, y / b.y); }

		Vec2u operator/(u32 b) { return Vec2u(x / b, y / b); }


		void operator+=(Vec2u b) {
			x += b.x;
			y += b.y;
		}

		void operator+=(u32 b) {
			x += b;
			y += b;
		}

		void operator-=(Vec2u b) {
			x -= b.x;
			y -= b.y;
		}

		void operator-=(u32 b) {
			x -= b;
			y -= b;
		}

		void operator*=(Vec2u b) {
			x *= b.x;
			y *= b.y;
		}

		void operator*=(u32 b) {
			x *= b;
			y *= b;
		}

		void operator/=(Vec2u b) {
			x /= b.x;
			y /= b.y;
		}

		void operator/=(u32 b) {
			x /= b;
			y /= b;
		}
	};

	inline const Vec2 Vec2::ZERO = Vec2(0, 0);
	inline const Vec2 Vec2::ONE = Vec2(1, 1);
	inline const Vec2 Vec2::UP = Vec2(0, 1);
	inline const Vec2 Vec2::DOWN = Vec2(0, -1);
	inline const Vec2 Vec2::LEFT = Vec2(-1, 0);
	inline const Vec2 Vec2::RIGHT = Vec2(1, 0);

	inline const Vec2i Vec2i::ZERO = Vec2i(0, 0);
	inline const Vec2i Vec2i::ONE = Vec2i(1, 1);
	inline const Vec2i Vec2i::UP = Vec2i(0, 1);
	inline const Vec2i Vec2i::DOWN = Vec2i(0, -1);
	inline const Vec2i Vec2i::LEFT = Vec2i(-1, 0);
	inline const Vec2i Vec2i::RIGHT = Vec2i(1, 0);

	inline const Vec2u Vec2u::ZERO = Vec2u(0, 0);
	inline const Vec2u Vec2u::ONE = Vec2u(1, 1);
} // namespace LTEngine::Math
