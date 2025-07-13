#ifndef _LTENGINE_COLOR_HPP_
#define _LTENGINE_COLOR_HPP_


#include <LTEngine/common/compiler_utils.h>


namespace LTEngine::Graphics {
	LTENGINE_PACK_START() struct Color {
		u8 r, g, b;

		static const Color BLACK;
		static const Color WHITE;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color YELLOW;
		static const Color CYAN;

		Color() : r(0), g(0), b(0) {
		}
		Color(u8 r, u8 g, u8 b) : r(r), g(g), b(b) {
		}

		Color operator+(Color other) const {
			return Color(this->r + other.r, this->g + other.g, this->b + other.b);
		}
		Color operator+(u8 other) const {
			return Color(this->r + other, this->g + other, this->b + other);
		}
		Color operator-(Color other) const {
			return Color(this->r - other.r, this->g - other.g, this->b - other.b);
		}
		Color operator-(u8 other) const {
			return Color(this->r - other, this->g - other, this->b - other);
		}
		Color operator*(Color other) const {
			return Color(this->r * other.r, this->g * other.g, this->b * other.b);
		}
		Color operator*(u8 other) const {
			return Color(this->r * other, this->g * other, this->b * other);
		}
		Color operator/(Color other) const {
			return Color(this->r / other.r, this->g / other.g, this->b / other.b);
		}


		bool operator<(const Color &other) const {
			if (r != other.r)
				return r < other.r;
			if (g != other.g)
				return g < other.g;
			return b < other.b;
		}

		bool operator>(const Color &other) const {
			if (r != other.r)
				return r > other.r;
			if (g != other.g)
				return g > other.g;
			return b < other.b;
		}

		bool operator==(const Color &other) const {
			return r == other.r && g == other.g && b == other.b;
		}
		bool operator!=(const Color &other) const {
			return r != other.r && g != other.g && b != other.b;
		}


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
	} LTENGINE_PACK_END();

	LTENGINE_PACK_START() struct ColorA {
		u8 r, g, b, a;

		static const ColorA BLACK;
		static const ColorA WHITE;
		static const ColorA RED;
		static const ColorA GREEN;
		static const ColorA BLUE;
		static const ColorA YELLOW;
		static const ColorA CYAN;
		static const ColorA CLEAR;

		ColorA() : r(0), g(0), b(0), a(0) {
		}
		ColorA(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {
		}

		operator Color() const {
			return Color(this->r, this->g, this->b);
		}

		ColorA operator+(ColorA other) const {
			return ColorA(this->r + other.r, this->g + other.g, this->b + other.b, this->a + other.a);
		}

		ColorA operator+(u8 other) const {
			return ColorA(this->r + other, this->g + other, this->b + other, this->a);
		}

		ColorA operator-(ColorA other) const {
			return ColorA(this->r - other.r, this->g - other.g, this->b - other.b, this->a - other.a);
		}

		ColorA operator-(u8 other) const {
			return ColorA(this->r - other, this->g - other, this->b - other, this->a);
		}

		ColorA operator*(ColorA other) const {
			return ColorA(this->r * other.r, this->g * other.g, this->b * other.b, this->a * other.a);
		}

		ColorA operator*(u8 other) const {
			return ColorA(this->r * other, this->g * other, this->b * other, this->a);
		}

		ColorA operator/(ColorA other) const {
			return ColorA(this->r / other.r, this->g / other.g, this->b / other.b, this->a / other.a);
		}


		bool operator<(const ColorA &other) const {
			if (r != other.r)
				return r < other.r;
			if (g != other.g)
				return g < other.g;
			if (b != other.b)
				return b < other.b;
			return a < other.a;
		}

		bool operator>(const ColorA &other) const {
			if (r != other.r)
				return r > other.r;
			if (g != other.g)
				return g > other.g;
			if (b != other.b)
				return b > other.b;
			return a > other.a;
		}

		bool operator==(const ColorA &other) const {
			return r == other.r && g == other.g && b == other.b && a == other.a;
		}
		bool operator!=(const ColorA &other) const {
			return r != other.r && g != other.g && b != other.b && a == other.a;
		}


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
	} LTENGINE_PACK_END();
	
} // namespace LTEngine::Rendering

#endif
