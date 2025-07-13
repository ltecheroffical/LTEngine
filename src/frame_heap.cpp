#include <LTEngine/frame_heap.hpp>


using namespace LTEngine;


void FrameHeap::end_frame() {
	_next_heap_index = 0;
}


void *FrameHeap::alloc(size_t size) {
	if (_next_heap_index + size > _heap.size()) { _heap.resize(_next_heap_index + size); }
	void *ptr = &(*_heap.end());
	_next_heap_index += size;
	return ptr;
}
