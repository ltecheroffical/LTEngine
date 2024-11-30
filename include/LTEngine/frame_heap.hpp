#ifndef _LTENGINE_FRAME_ALLOCATOR_HPP_
#define _LTENGINE_FRAME_ALLOCATOR_HPP_

#include <cstddef>
#include <vector>

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine {
	/**
	 * @brief A temporary heap that allocates memory for the current frame.
	 *
	 * @details
	 * The heap is cleared at the end of the frame once `endFrame()` is called. The memory is not zeroed however.
	 *
	 */
	class FrameHeap {
	public:
		FrameHeap() = default;
		~FrameHeap() = default;

		/**
		 * @brief Marks the end of a frame and clears the frame heap
		 *
		 * @details
		 * This function should be called at the end of frame processing to erase anything leftover.
		 * This serves as a garbage collector.
		 */
		void endFrame();

		/**
		 * @brief Allocates memory on the frame heap.
		 *
		 * @param size The size of the memory to allocate
		 * @return A pointer to the allocated memory
		 *
		 * @details
		 * This function allocates memory on the frame heap and returns a pointer to the allocated memory.
		 * The memory allocated is not cleared. Any memory allocated here is garbage collected at the end of the frame and will make
		 * the address invalid or pointing to other memory. Accessing this after it's been freed will result in behavior depending
		 * on the program state, or undefined behavior.
		 */
		void *alloc(size_t size);

	private:
		size_t m_nextHeapIndex = 0;
		std::vector<u8> m_heap;
	};
} // namespace LTEngine

#endif
