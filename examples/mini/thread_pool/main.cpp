#include <chrono>
#include <iostream>

#include <LTEngine/random/platform_random.hpp>
#include <LTEngine/rendering/software_renderer.hpp>
#include <LTEngine/thread_pool.hpp>


using namespace LTEngine;


class RandomRectangleShader : public Rendering::CPUShader {
public:
	RandomRectangleShader() : m_random({}) {};
	~RandomRectangleShader() override = default;

	void fragment(Rendering::CPUShaderIO *io) override {
		io->color.r = m_random.next_u8();
		io->color.g = m_random.next_u8();
		io->color.b = m_random.next_u8();
	}

private:
	Random::PlatformRandom m_random;
};


int main() {
	const u8 sumArray[] = {
	    42,  123, 80,  47,  126, 32,  86,  68,  19,  77,  93,  111, 25, 36,  91,  71,  56,  116, 30,  52,  8,   33,  115, 4,   53,
	    85,  103, 79,  72,  109, 49,  112, 128, 1,   50,  20,  121, 54, 118, 100, 88,  101, 107, 110, 114, 58,  16,  92,  29,  27,
	    9,   14,  38,  113, 62,  35,  67,  70,  59,  26,  106, 44,  64, 46,  74,  7,   94,  122, 99,  102, 24,  15,  90,  13,  55,
	    57,  12,  22,  40,  28,  95,  61,  51,  87,  60,  119, 39,  34, 73,  75,  96,  63,  127, 124, 41,  83,  81,  3,   108, 125,
	    17,  69,  6,   117, 97,  76,  104, 65,  43,  5,   48,  82,  10, 37,  11,  84,  120, 89,  23,  98,  21,  45,  66,  31,  18,
	    105, 78,  2,   27,  6,   48,  77,  114, 87,  23,  127, 8,   98, 94,  1,   88,  75,  63,  84,  15,  43,  7,   113, 108, 38,
	    20,  111, 41,  53,  112, 104, 34,  50,  16,  80,  76,  33,  3,  62,  55,  82,  2,   56,  64,  106, 109, 26,  57,  19,  118,
	    35,  70,  96,  11,  99,  29,  68,  128, 22,  73,  103, 44,  30, 24,  97,  105, 9,   36,  119, 79,  101, 121, 74,  126, 12,
	    123, 92,  69,  81,  72,  54,  66,  90,  49,  95,  85,  13,  67, 124, 37,  91,  102, 60,  32,  107, 71,  28,  4,   39,  40,
	    93,  116, 86,  47,  89,  31,  21,  110, 58,  17,  5,   115, 61, 45,  10,  14,  83,  117, 59,  52,  65,  120, 100, 51,  25,
	    122, 42,  46,  18,  125, 78,  40,  81,  41,  73,  79,  120, 83, 2,   112, 68,  82,  89,  93,  15,  49,  71,  23,  27,  128,
	    38,  88,  8,   30,  101, 26,  76,  77,  43,  22,  46,  24,  44, 48,  91,  123, 47,  11,  72,  100, 95,  53,  67,  85,  42,
	    13,  116, 94,  97,  109, 118, 64,  28,  96,  32,  61,  21,  16, 29,  69,  107, 12,  65,  6,   9,   39,  33,  115, 54,  10,
	    5,   127, 124, 114, 25,  63,  92,  108, 99,  62,  35,  80,  36, 51,  121, 75,  59,  74,  55,  98,  19,  111, 57,  122, 7,
	    14,  102, 3,   78,  4,   18,  52,  31,  103, 119, 34,  56,  70, 60,  113, 58,  17,  37,  106, 45,  90,  126, 20,  86,  105,
	    66,  125, 110, 1,   50,  84,  104, 87,  117, 11,  82,  113, 40, 20,  102, 15,  88,  126, 4,   6,   11,  45,  63,  58,  97,
	    101, 59,  25,  70,  16,  112, 44,  2,   77,  92,  33,  60,  75, 100, 24,  54,  116, 127, 62,  50,  39,  31,  83,  106, 3,
	    108, 103, 66,  23,  38,  104, 47,  29,  37,  13,  72,  43,  68, 122, 124, 80,  119, 64,  5,   61,  41,  128, 10,  49,  35,
	    84,  74,  48,  17,  87,  85,  91,  53,  90,  78,  32,  19,  95, 69,  22,  42,  89,  115, 28,  96,  71,  121, 56,  67,  99,
	    123, 34,  21,  114, 27,  86,  8,   73,  117, 98,  46,  125, 52, 107, 57,  120, 55,  81,  7,   76,  118, 12,  36,  79,  94,
	    105, 1,   51,  65,  110, 93,  14,  30,  26,  109, 9,   18};


	u16 sumResults = 0;
	u32 timeToWrapU32InNs = 0;
	Rendering::SoftwareRenderer renderer(1920, 1080);
	RandomRectangleShader shader; // We have to load the shader now since otherwise it would get destroyed and UAFed

	// The context will destroy the thread pool asking it to wait
	{
		LTEngine::ThreadPool threadPool(4);
		threadPool.enqueue([&sumResults, sumArray]() {
			std::cout << "Started summing up the array" << std::endl;
			for (u16 i = 0; i < sizeof(sumArray) / sizeof(sumArray[0]); i++) {
				sumResults += sumArray[i];
			}
			std::cout << "Finished summing up the array" << std::endl;
		});

		threadPool.enqueue([&timeToWrapU32InNs]() {
			std::cout << "Started wrapping u64" << std::endl;

			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

			u32 num = 1;
			u8 lastPercent = 0;

			while (num != 0) {
				f32 percent = (f32)num / (f32)std::numeric_limits<u32>::max();
				if ((u32)(percent * 100.f) > lastPercent && (u32)(percent * 100.f) % 5 == 0) {
					std::cout << "Wrapping u32: " << percent * 100.f << "%" << std::endl;
					lastPercent = percent * 100.f;
				}
				num++;
			}

			std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;

			timeToWrapU32InNs = elapsed.count() * 1e9;

			std::cout << "Finished wrapping u32" << std::endl;
		});


		for (u8 i = 0; i < 4; i++) {
			threadPool.enqueue([i]() {
				Random::PlatformRandom random({});
				u8 sleepTime = random.next_u8() % (15 - 1) + 1;

				std::cout << "[Sleeper #" << (u16)i + 1 << "] Started for " << (u16)sleepTime << "s" << std::endl;

				std::this_thread::sleep_for(std::chrono::seconds(sleepTime));

				std::cout << "[Sleeper #" << (u16)i + 1 << "] Finished" << std::endl;
			});
		}

		// Build a simple scene using the CPU
		renderer.setScreenOnly();
		renderer.clear(Rendering::Color::Cyan);

		renderer.drawRect(Shapes::Rect(100, 100, 500, 500), Rendering::ColorA::Red);
		renderer.drawCircle(Shapes::Circle{{465 + 250, 318 + 250}, 250}, Rendering::ColorA::Blue, Rendering::Renderer::FLAG_FILL);

		renderer.setShader(&shader);
		renderer.drawRect(Shapes::Rect(1224, 147, 585, 375), Rendering::ColorA::Green);
		renderer.clearShader();

		threadPool.enqueue([&renderer]() {
			renderer.processAll();
		});
	}

	std::cout << "Sum: " << sumResults << std::endl;
	std::cout << "Time to wrap u32: " << timeToWrapU32InNs << "ns" << std::endl;

	std::cout << "Save the rendered CPU scene? (y/n) ";
	std::string save = "";
	std::getline(std::cin, save);
	if (save == "y") {
		std::string path = "";
		std::cout << "Please enter a PNG path: ";
		std::getline(std::cin, path);

		std::vector<Rendering::Color> screen(renderer.getScreenData(nullptr));
		renderer.getScreenData(screen.data());

		Rendering::Image image(screen.data(), 1920, 1080);
		image.savePNG(path.c_str());
	}
	return 0;
}
