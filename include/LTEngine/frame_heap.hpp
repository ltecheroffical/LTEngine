#ifndef _LTENGINE_FRAME_ALLOCATOR_HPP_
#define _LTENGINE_FRAME_ALLOCATOR_HPP_

#include <cstddef>
#include <vector>

#include <LTEngine/common/types/inttypes.h>


namespace LTEngine {
	class FrameHeap {
	public:
		FrameHeap() = default;
		~FrameHeap() = default;

		void endFrame();

		void *alloc(size_t size);

	private:
		std::vector<u8> m_heap;
	};
} // namespace LTEngine

#endif
