#pragma once

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine::Rendering {
	struct Color {
		u8 r, g, b;

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Cyan;

		Color() : r(0), g(0), b(0) {}
		Color(u8 r, u8 g, u8 b) : r(r), g(g), b(b) {}

		Color operator+(Color other) const { return Color(this->r + other.r, this->g + other.g, this->b + other.b); }
		Color operator+(u8 other) const { return Color(this->r + other, this->g + other, this->b + other); }
		Color operator-(Color other) const { return Color(this->r - other.r, this->g - other.g, this->b - other.b); }
		Color operator-(u8 other) const { return Color(this->r - other, this->g - other, this->b - other); }
		Color operator*(Color other) const { return Color(this->r * other.r, this->g * other.g, this->b * other.b); }
		Color operator*(u8 other) const { return Color(this->r * other, this->g * other, this->b * other); }
		Color operator/(Color other) const { return Color(this->r / other.r, this->g / other.g, this->b / other.b); }


		bool operator<(const Color &other) const {
			if (r != other.r) return r < other.r;
			if (g != other.g) return g < other.g;
			return b < other.b;
		}

		bool operator>(const Color &other) const {
			if (r != other.r) return r > other.r;
			if (g != other.g) return g > other.g;
			return b < other.b;
		}

		bool operator==(const Color &other) const { return r == other.r && g == other.g && b == other.b; }
		bool operator!=(const Color &other) const { return r != other.r && g != other.g && b != other.b; }


		void operator+=(Color other) {
			this->r += other.r;
			this->g += other.g;
			this->b += other.b;
		}

		void operator+=(u8 other) {
			this->r += other;
			this->g += other;
			this->b += other;
		}

		void operator-=(Color other) {
			this->r -= other.r;
			this->g -= other.g;
			this->b -= other.b;
		}

		void operator-=(u8 other) {
			this->r -= other;
			this->g -= other;
			this->b -= other;
		}

		void operator*=(Color other) {
			this->r *= other.r;
			this->g *= other.g;
			this->b *= other.b;
		}

		void operator*=(u8 other) {
			this->r *= other;
			this->g *= other;
			this->b *= other;
		}

		void operator/=(Color other) {
			this->r /= other.r;
			this->g /= other.g;
			this->b /= other.b;
		}

		void operator/=(u8 other) {
			this->r /= other;
			this->g /= other;
			this->b /= other;
		}
	};

	struct ColorA {
		u8 r, g, b, a;

		static const ColorA Black;
		static const ColorA White;
		static const ColorA Red;
		static const ColorA Green;
		static const ColorA Blue;
		static const ColorA Yellow;
		static const ColorA Cyan;
		static const ColorA Clear;

		ColorA() : r(0), g(0), b(0), a(0) {}
		ColorA(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}

		operator Color() const { return Color(this->r, this->g, this->b); }

		ColorA operator+(ColorA other) const {
			return ColorA(this->r + other.r, this->g + other.g, this->b + other.b, this->a + other.a);
		}

		ColorA operator+(u8 other) const { return ColorA(this->r + other, this->g + other, this->b + other, this->a); }

		ColorA operator-(ColorA other) const {
			return ColorA(this->r - other.r, this->g - other.g, this->b - other.b, this->a - other.a);
		}

		ColorA operator-(u8 other) const { return ColorA(this->r - other, this->g - other, this->b - other, this->a); }

		ColorA operator*(ColorA other) const {
			return ColorA(this->r * other.r, this->g * other.g, this->b * other.b, this->a * other.a);
		}

		ColorA operator*(u8 other) const { return ColorA(this->r * other, this->g * other, this->b * other, this->a); }

		ColorA operator/(ColorA other) const {
			return ColorA(this->r / other.r, this->g / other.g, this->b / other.b, this->a / other.a);
		}


		bool operator<(const ColorA &other) const {
			if (r != other.r) return r < other.r;
			if (g != other.g) return g < other.g;
			if (b != other.b) return b < other.b;
			return a < other.a;
		}

		bool operator>(const ColorA &other) const {
			if (r != other.r) return r > other.r;
			if (g != other.g) return g > other.g;
			if (b != other.b) return b > other.b;
			return a > other.a;
		}

		bool operator==(const ColorA &other) const { return r == other.r && g == other.g && b == other.b && a == other.a; }
		bool operator!=(const ColorA &other) const { return r != other.r && g != other.g && b != other.b && a == other.a; }


		void operator+=(ColorA other) {
			this->r += other.r;
			this->g += other.g;
			this->b += other.b;
			this->a += other.a;
		}

		void operator+=(u8 other) {
			this->r += other;
			this->g += other;
			this->b += other;
			this->a += other;
		}

		void operator-=(ColorA other) {
			this->r -= other.r;
			this->g -= other.g;
			this->b -= other.b;
			this->a -= other.a;
		}

		void operator-=(u8 other) {
			this->r -= other;
			this->g -= other;
			this->b -= other;
			this->a -= other;
		}

		void operator*=(ColorA other) {
			this->r *= other.r;
			this->g *= other.g;
			this->b *= other.b;
			this->a *= other.a;
		}

		void operator*=(u8 other) {
			this->r *= other;
			this->g *= other;
			this->b *= other;
			this->a *= other;
		}

		void operator/=(ColorA other) {
			this->r /= other.r;
			this->g /= other.g;
			this->b /= other.b;
			this->a /= other.a;
		}

		void operator/=(u8 other) {
			this->r /= other;
			this->g /= other;
			this->b /= other;
			this->a /= other;
		}
	};

	inline const Color Color::Black = Color(0, 0, 0);
	inline const Color Color::White = Color(255, 255, 255);
	inline const Color Color::Red = Color(255, 0, 0);
	inline const Color Color::Green = Color(0, 255, 0);
	inline const Color Color::Blue = Color(0, 0, 255);
	inline const Color Color::Yellow = Color(255, 255, 0);
	inline const Color Color::Cyan = Color(0, 255, 255);

	inline const ColorA ColorA::Black = ColorA(0, 0, 0, 255);
	inline const ColorA ColorA::White = ColorA(255, 255, 255, 255);
	inline const ColorA ColorA::Red = ColorA(255, 0, 0, 255);
	inline const ColorA ColorA::Green = ColorA(0, 255, 0, 255);
	inline const ColorA ColorA::Blue = ColorA(0, 0, 255, 255);
	inline const ColorA ColorA::Yellow = ColorA(255, 255, 0, 255);
	inline const ColorA ColorA::Cyan = ColorA(0, 255, 255, 255);
	inline const ColorA ColorA::Clear = ColorA(0, 0, 0, 0);
} // namespace LTEngine::Rendering
