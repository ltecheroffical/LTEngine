#include <LTEngine/frame_heap.hpp>


using namespace LTEngine;


void FrameHeap::endFrame() {
    m_heap.clear();
}


void *FrameHeap::alloc(size_t size) {
    void *ptr = &(*m_heap.end());
    m_heap.resize(m_heap.size() + size);
    return ptr;
}
