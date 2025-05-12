#include <chrono>
#include <iostream>

#include <LTCore/logger.hpp>
#include <LTCore/random/platform_random.hpp>
#include <LTCore/thread_pool.hpp>

int main() {
	const LTCore::u8 sumArray[] = {
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


	LTCore::Logger logger;
	logger.setLogOutput(LTCore::Logger::LogOutput::Stdout);

	LTCore::u16 sumResults = 0;
	LTCore::u32 timeToWrapU32InNs = 0;

	// The context will destroy the thread pool asking it to wait
	{
		LTCore::ThreadPool threadPool(4);
		threadPool.enqueue([&sumResults, &logger, sumArray]() {
			logger.info("Started array summing");
			for (LTCore::u16 i = 0; i < sizeof(sumArray) / sizeof(sumArray[0]); i++) {
				sumResults += sumArray[i];
			}
			logger.info("Finished summing up the array");
		});

		threadPool.enqueue([&timeToWrapU32InNs, &logger]() {
			logger.info("Started wrapping u32");

			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

			LTCore::u32 num = 1;
			LTCore::u8 lastPercent = 0;

			while (num != 0) {
				LTCore::f32 percent = (LTCore::f32)num / (LTCore::f32)std::numeric_limits<LTCore::u32>::max();
				if ((LTCore::u32)(percent * 100.f) > lastPercent && (LTCore::u32)(percent * 100.f) % 5 == 0) {
					std::cout << "Wrapping u32: " << percent * 100.f << "%" << std::endl;
					lastPercent = percent * 100.f;
				}
				num++;
			}

			std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;

			timeToWrapU32InNs = elapsed.count() * 1e9;

			logger.info("Finished wrapping u32");
		});


		for (LTCore::u8 i = 0; i < 4; i++) {
			threadPool.enqueue([i, &logger]() {
				LTCore::Random::PlatformRandom random({});
				LTCore::u8 sleepTime = random.next_u8() % (15 - 1) + 1;

				logger.info("[Sleeper #%u] Started for %us", (LTCore::u16)i, (LTCore::u16)sleepTime);

				std::this_thread::sleep_for(std::chrono::seconds(sleepTime));

				logger.info("[Sleeper #%u] Finished", (LTCore::u16)i);
			});
		}
	}

	std::cout << "Sum: " << sumResults << std::endl;
	std::cout << "Time to wrap u32: " << timeToWrapU32InNs << "ns" << std::endl;
	return 0;
}
