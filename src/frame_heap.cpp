#include <LTEngine/frame_heap.hpp>


using namespace LTEngine;


void FrameHeap::endFrame() {
	m_nextHeapIndex = 0;
}


void *FrameHeap::alloc(size_t size) {
	if (m_nextHeapIndex + size > m_heap.size()) { m_heap.resize(m_nextHeapIndex + size); }
	void *ptr = &(*m_heap.end());
	m_nextHeapIndex += size;
	return ptr;
}
