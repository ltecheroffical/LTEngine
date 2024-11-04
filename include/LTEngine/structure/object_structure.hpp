#pragma once

#include <LTEngine/rendering/renderer.hpp>


namespace LTEngine::Object {
    class ObjectStructure {
    public:
        virtual ~ObjectStructure() = 0;

        virtual void update(f32 delta) = 0;
        virtual void render(LTEngine::Rendering::Renderer *renderer) = 0;
        
        virtual std::unique_ptr<ObjectStructure> clone() const = 0;

        virtual void clear() = 0;

        Rendering::Color getClearColor() const;

    protected:
        Rendering::Color m_clearColor;
    };
}
