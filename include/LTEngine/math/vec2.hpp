#pragma once

#include <LTEngine/common/types/floattypes.h>
#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::Math {
	struct Vec2 {
		f32 x, y;

		static const Vec2 Zero;
		static const Vec2 One;
		static const Vec2 Up;
		static const Vec2 Down;
		static const Vec2 Left;
		static const Vec2 Right;

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
		bool operator>(const Vec2 &other) const { return x > other.x || (x == other.x && y > other.y); }
		bool operator<=(const Vec2 &other) const { return x <= other.x || (x == other.x && y <= other.y); }
		bool operator>=(const Vec2 &other) const { return x >= other.x || (x == other.x && y >= other.y); }
		bool operator==(const Vec2 &other) const { return x == other.x && y == other.y; }
		bool operator!=(const Vec2 &other) const { return x != other.x && y != other.y; }


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

	typedef Vec2 Vec2f;

	struct Vec2i {
		i32 x, y;

		static const Vec2i Zero;
		static const Vec2i One;
		static const Vec2i Up;
		static const Vec2i Down;
		static const Vec2i Left;
		static const Vec2i Right;

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
		bool operator>(const Vec2i &other) const { return x > other.x || (x == other.x && y > other.y); }
		bool operator<=(const Vec2i &other) const { return x <= other.x || (x == other.x && y <= other.y); }
		bool operator>=(const Vec2i &other) const { return x >= other.x || (x == other.x && y >= other.y); }
		bool operator==(const Vec2i &other) const { return x == other.x && y == other.y; }
		bool operator!=(const Vec2 &other) const { return x != other.x && y != other.y; }

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

		static const Vec2u Zero;
		static const Vec2u One;

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

		bool operator<(const Vec2u &other) const { return x < other.x || (x == other.x && y < other.y); }
		bool operator>(const Vec2u &other) const { return x > other.x || (x == other.x && y > other.y); }
		bool operator<=(const Vec2u &other) const { return x <= other.x || (x == other.x && y <= other.y); }
		bool operator>=(const Vec2u &other) const { return x >= other.x || (x == other.x && y >= other.y); }
		bool operator==(const Vec2u &other) const { return x == other.x && y == other.y; }
		bool operator!=(const Vec2 &other) const { return x != other.x && y != other.y; }

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

	inline const Vec2 Vec2::Zero = Vec2(0, 0);
	inline const Vec2 Vec2::One = Vec2(1, 1);
	inline const Vec2 Vec2::Up = Vec2(0, 1);
	inline const Vec2 Vec2::Down = Vec2(0, -1);
	inline const Vec2 Vec2::Left = Vec2(-1, 0);
	inline const Vec2 Vec2::Right = Vec2(1, 0);

	inline const Vec2i Vec2i::Zero = Vec2i(0, 0);
	inline const Vec2i Vec2i::One = Vec2i(1, 1);
	inline const Vec2i Vec2i::Up = Vec2i(0, 1);
	inline const Vec2i Vec2i::Down = Vec2i(0, -1);
	inline const Vec2i Vec2i::Left = Vec2i(-1, 0);
	inline const Vec2i Vec2i::Right = Vec2i(1, 0);

	inline const Vec2u Vec2u::Zero = Vec2u(0, 0);
	inline const Vec2u Vec2u::One = Vec2u(1, 1);
} // namespace LTEngine::Math
