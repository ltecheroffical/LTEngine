#ifdef LTENGINE_COMPONENT_C_API
#include <LTEngine/c_api/rendering/renderer.h>

#include <LTEngine/rendering/renderer.hpp>


class CRenderer : public LTEngine::Rendering::Renderer {
public:
    CRenderer(LTEngine_CustomRendererFuncs *funcs) {
        m_rendererFuncs = *funcs;
        m_ctx = funcs->init({{this}});
    }

    ~CRenderer() {
        m_rendererFuncs.deinit({{this}}, m_ctx);
    }

    
    void clear(LTEngine::Rendering::Color color) override {
        auto cColor = LTEngine_Color(color.r, color.g, color.b);
        m_rendererFuncs.clear({{this}}, m_ctx, cColor);
        LTEngine_Color_free(cColor);
    }

    void clear(LTEngine::Rendering::ColorA color) override {
        auto cColor = LTEngine_ColorA(color.r, color.g, color.b, color.a);
        m_rendererFuncs.clearA({{this}}, m_ctx, cColor);
        LTEngine_ColorA_free(cColor);
    }


    void setPixel(LTEngine::Math::Vec2i position, LTEngine::Rendering::Color color) override {
        auto cPosition = LTEngine_Vec2i(position.x, position.y);
        auto cColor = LTEngine_Color(color.r, color.g, color.b);
        m_rendererFuncs.setPixel({{this}}, m_ctx, cPosition, cColor);
        LTEngine_Vec2i_free(cPosition);
        LTEngine_Color_free(cColor);
    }

    void setPixel(LTEngine::Math::Vec2i position, LTEngine::Rendering::ColorA color) override {
        auto cPosition = LTEngine_Vec2i(position.x, position.y);
        auto cColor = LTEngine_ColorA(color.r, color.g, color.b, color.a);
        m_rendererFuncs.setPixelA({{this}}, m_ctx, cPosition, cColor);
        LTEngine_Vec2i_free(cPosition);
        LTEngine_ColorA_free(cColor);
    }

    LTEngine::Rendering::Color getPixel(LTEngine::Math::Vec2i position) override {
        auto cPosition = LTEngine_Vec2i(position.x, position.y);
        auto color = m_rendererFuncs.getPixel({{this}}, m_ctx, cPosition);
        LTEngine_Vec2i_free(cPosition);
        return {
            LTEngine_Color_r(color),
            LTEngine_Color_g(color),
            LTEngine_Color_b(color)
        };
    }


    void drawRect(LTEngine::Shapes::Rect rect, LTEngine::Rendering::ColorA color, RendererFlags flags) override {
        auto cRect = LTEngine_Rect(rect.x, rect.y, rect.w, rect.h);
        auto cColor = LTEngine_ColorA(color.r, color.g, color.b, color.a);
        LTEngine_Shape_setRotation(cRect, rect.rotation);
        m_rendererFuncs.drawRect({{this}}, m_ctx, cRect, cColor, flags);
        LTEngine_Rect_free(cRect);
        LTEngine_ColorA_free(cColor);
    }

    void drawCircle(LTEngine::Shapes::Circle circle, LTEngine::Rendering::ColorA color, RendererFlags flags) override {
        auto cCircle = LTEngine_Circle(circle.x, circle.y, circle.radius);
        auto cColor = LTEngine_ColorA(color.r, color.g, color.b, color.a);
        m_rendererFuncs.drawCircle({{this}}, m_ctx, cCircle, cColor, flags);
        LTEngine_Circle_free(cCircle);
        LTEngine_ColorA_free(cColor);
    }


    void drawLine(LTEngine::Math::Vec2 a, LTEngine::Math::Vec2 b, LTEngine::u16 thickness, LTEngine::Rendering::ColorA color, RendererFlags flags) override {
        auto cA = LTEngine_Vec2(a.x, a.y);
        auto cB = LTEngine_Vec2(b.x, b.y);
        auto cColor = LTEngine_ColorA(color.r, color.g, color.b, color.a);
        m_rendererFuncs.drawLine({{this}}, m_ctx, cA, cB, thickness, cColor, flags);
        LTEngine_Vec2_free(cA);
        LTEngine_Vec2_free(cB);
        LTEngine_ColorA_free(cColor);
    }

    void drawPoints(LTEngine::Shapes::Polygon polygon, LTEngine::Rendering::ColorA color, RendererFlags flags) override {
        auto cPolygon = LTEngine_Polygon();
        auto cPoints = LTEngine_DynamicArray_Vec2_createWithCapacity(polygon.points.size());
        auto cColor = LTEngine_ColorA(color.r, color.g, color.b, color.a);

        LTEngine_Shape_setRotation(cPolygon, polygon.rotation);

        for (auto point : polygon.points) {
            LTEngine_DynamicArray_Vec2_add(&cPoints, LTEngine_Vec2(point.x, point.y));
        }

        LTEngine_Polygon_setPoints(cPolygon, cPoints);

        for (size_t i = 0; i < LTEngine_DynamicArray_Vec2_size(&cPoints); i++) {
            LTEngine_Vec2_free(LTEngine_DynamicArray_Vec2_get(&cPoints, i));
        }

        LTEngine_DynamicArray_Vec2_free(&cPoints);

        m_rendererFuncs.drawPoints({{this}}, m_ctx, cPolygon, cColor, flags);

        LTEngine_ColorA_free(cColor);
        LTEngine_Polygon_free(cPolygon);
    }


    void drawImage(const LTEngine::Rendering::Image *image, LTEngine::Math::Vec2i position, LTEngine::f32 rotation, LTEngine::Shapes::Recti region, LTEngine::Rendering::ColorA color, RendererFlags flags) override {
        auto cPosition = LTEngine_Vec2(position.x, position.y);
        auto cRegion = LTEngine_Recti(region.x, region.y, region.w, region.h);
        auto cColor = LTEngine_ColorA(color.r, color.g, color.b, color.a);
        auto cImage = LTEngine_HImage{{const_cast<LTEngine::Rendering::Image*>(image)}};

        m_rendererFuncs.drawImage({{this}}, m_ctx, cImage, cPosition, rotation, cRegion, cColor, flags);

        LTEngine_Vec2_free(cPosition);
        LTEngine_Recti_free(cRegion);
        LTEngine_ColorA_free(cColor);
    }

protected:
    void cameraCreated(LTEngine::u32 id) override {
        m_rendererFuncs.cameraCreated({{this}}, m_ctx, id);
    }

    void cameraDestroyed(LTEngine::u32 id) override {
        m_rendererFuncs.cameraDestroyed({{this}}, m_ctx, id);
    }

    void cameraSelected(LTEngine::u32 id) override {
        m_rendererFuncs.cameraSelected({{this}}, m_ctx, id);
    }

    void cameraDeselected() override {
        m_rendererFuncs.cameraDeselected({{this}}, m_ctx);
    }

private:
    LTEngine_CustomRendererFuncs m_rendererFuncs;
    void *m_ctx;
};


LTEngine_HRenderer LTEngine_CustomRenderer(LTEngine_CustomRendererFuncs funcs) {
    return {{ new CRenderer(&funcs) }};
}

void LTEngine_CustomRenderer_free(LTEngine_HRenderer handle) {
    delete (CRenderer *)handle.handle.ptr;
}


void LTEngine_Renderer_setScale(LTEngine_HRenderer handle, const LTEngine_HVec2 scale) {
    ((CRenderer *)handle.handle.ptr)->setScale({LTEngine_Vec2_x(scale), LTEngine_Vec2_y(scale)});
}


void LTEngine_Renderer_setRotationOffset(LTEngine_HRenderer handle, LTEngine_f32 offset) {
    ((CRenderer *)handle.handle.ptr)->setRotationOffset(offset);
}

void LTEngine_Renderer_setScaleFactor(LTEngine_HRenderer handle, const LTEngine_HVec2 scale) {
    ((CRenderer *)handle.handle.ptr)->setScaleFactor({LTEngine_Vec2_x(scale), LTEngine_Vec2_y(scale)});
}

void LTEngine_Renderer_setPositionOffset(LTEngine_HRenderer handle, const LTEngine_HVec2 offset) {
    ((CRenderer *)handle.handle.ptr)->setPositionOffset({LTEngine_Vec2_x(offset), LTEngine_Vec2_y(offset)});
}


void LTEngine_Renderer_resetTransform(LTEngine_HRenderer handle) {
    ((CRenderer *)handle.handle.ptr)->resetTransform();
}


LTEngine_u32 LTENGINE_API LTEngine_Renderer_createCamera(LTEngine_HRenderer handle, const LTEngine_HVec2 position, const LTEngine_HVec2 zoom) {
    return ((CRenderer *)handle.handle.ptr)->createCamera({LTEngine_Vec2_x(position), LTEngine_Vec2_y(position)}, {LTEngine_Vec2_x(zoom), LTEngine_Vec2_y(zoom)});
}

void LTENGINE_API LTEngine_Renderer_deleteCamera(LTEngine_HRenderer handle, LTEngine_u32 id) {
    ((CRenderer *)handle.handle.ptr)->deleteCamera(id);
}

void LTENGINE_API LTEngine_Renderer_setCameraPosition(LTEngine_HRenderer handle, LTEngine_u32 id, const LTEngine_HVec2 position) {
    ((CRenderer *)handle.handle.ptr)->setCameraPosition(id, {LTEngine_Vec2_x(position), LTEngine_Vec2_y(position)});
}

void LTENGINE_API LTEngine_Renderer_setCameraRotation(LTEngine_HRenderer handle, LTEngine_u32 id, LTEngine_f32 rotation) {
    ((CRenderer *)handle.handle.ptr)->setCameraRotation(id, rotation);
}

void LTENGINE_API LTEngine_Renderer_setCameraZoom(LTEngine_HRenderer handle, LTEngine_u32 id, const LTEngine_HVec2 zoom) {
    ((CRenderer *)handle.handle.ptr)->setCameraZoom(id, {LTEngine_Vec2_x(zoom), LTEngine_Vec2_y(zoom)});
}

void LTENGINE_API LTEngine_Renderer_setCameraInclude(LTEngine_HRenderer handle, LTEngine_u32 id) {
    ((CRenderer *)handle.handle.ptr)->setCameraInclude(id);
}

void LTENGINE_API LTEngine_Renderer_setCameraExclude(LTEngine_HRenderer handle, LTEngine_u32 id) {
    ((CRenderer *)handle.handle.ptr)->setCameraExclude(id);
}

void LTENGINE_API LTEngine_Renderer_setCurrentCamera(LTEngine_HRenderer handle, LTEngine_u32 id) {
    ((CRenderer *)handle.handle.ptr)->setCurrentCamera(id);
}

void LTENGINE_API LTEngine_Renderer_clearCameraCamera(LTEngine_HRenderer handle) {
    ((CRenderer *)handle.handle.ptr)->clearCurrentCamera();
}

LTEngine_HVec2 LTENGINE_API LTEngine_Renderer_getCameraPosition(const LTEngine_HRenderer handle, LTEngine_u32 id) {
    auto position = ((CRenderer *)handle.handle.ptr)->getCameraPosition(id);
    return LTEngine_Vec2(position.x, position.y);
}

LTEngine_HVec2 LTENGINE_API LTEngine_Renderer_getCameraZoom(const LTEngine_HRenderer handle, LTEngine_u32 id) {
    auto zoom = ((CRenderer *)handle.handle.ptr)->getCameraZoom(id);
    return LTEngine_Vec2(zoom.x, zoom.y);
}

LTEngine_f32 LTENGINE_API LTEngine_Renderer_getCameraRotation(const LTEngine_HRenderer handle, LTEngine_u32 id) {
    return ((CRenderer *)handle.handle.ptr)->getCameraRotation(id);
}

bool LTENGINE_API LTEngine_Renderer_isCameraIncluded(const LTEngine_HRenderer handle, LTEngine_u32 id) {
    return ((CRenderer *)handle.handle.ptr)->isCameraIncluded(id);
}


void LTENGINE_API LTEngine_Renderer_clear(LTEngine_HRenderer handle, const LTEngine_HColor color) {
    ((CRenderer *)handle.handle.ptr)->clear({LTEngine_Color_r(color), LTEngine_Color_g(color), LTEngine_Color_b(color)});
}
void LTENGINE_API LTEngine_Renderer_clearA(LTEngine_HRenderer handle, const LTEngine_HColorA color) {
    ((CRenderer *)handle.handle.ptr)->clear({LTEngine_ColorA_r(color), LTEngine_ColorA_g(color), LTEngine_ColorA_b(color), LTEngine_ColorA_a(color)});
}


void LTENGINE_API LTEngine_Renderer_setPixel(LTEngine_HRenderer handle, const LTEngine_HVec2i position, const LTEngine_HColor color) {
    ((CRenderer *)handle.handle.ptr)->setPixel({LTEngine_Vec2i_x(position), LTEngine_Vec2i_y(position)}, {LTEngine_Color_r(color), LTEngine_Color_g(color), LTEngine_Color_b(color)});
}

void LTENGINE_API LTEngine_Renderer_setPixelA(LTEngine_HRenderer handle, const LTEngine_HVec2i position, const LTEngine_HColorA color) {
    ((CRenderer *)handle.handle.ptr)->setPixel({LTEngine_Vec2i_x(position), LTEngine_Vec2i_y(position)}, {LTEngine_ColorA_r(color), LTEngine_ColorA_g(color), LTEngine_ColorA_b(color), LTEngine_ColorA_a(color)});
}

LTEngine_HColor LTEngine_Renderer_getPixel(const LTEngine_HRenderer handle, const LTEngine_HVec2i position) {
    auto color = ((CRenderer *)handle.handle.ptr)->getPixel({LTEngine_Vec2i_x(position), LTEngine_Vec2i_y(position)});
    return LTEngine_Color(color.r, color.g, color.b);
}


void LTENGINE_API LTEngine_Renderer_drawRect(LTEngine_HRenderer handle, const LTEngine_HRect rect, const LTEngine_HColorA color, LTEngine_RendererFlags flags) {
    ((CRenderer *)handle.handle.ptr)->drawRect({LTEngine_Shape_x(rect), LTEngine_Shape_y(rect), LTEngine_Rect_w(rect), LTEngine_Rect_h(rect)}, {LTEngine_ColorA_r(color), LTEngine_ColorA_g(color), LTEngine_ColorA_b(color), LTEngine_ColorA_a(color)}, flags);
}

void LTENGINE_API LTEngine_Renderer_drawCircle(LTEngine_HRenderer handle, const LTEngine_HCircle circle, const LTEngine_HColorA color, LTEngine_RendererFlags flags) {
    ((CRenderer *)handle.handle.ptr)->drawCircle({{LTEngine_Shape_x(circle), LTEngine_Shape_y(circle)}, LTEngine_Circle_radius(circle)}, {LTEngine_ColorA_r(color), LTEngine_ColorA_g(color), LTEngine_ColorA_b(color), LTEngine_ColorA_a(color)}, flags);
}

void LTENGINE_API LTEngine_Renderer_drawLine(LTEngine_HRenderer handle, const LTEngine_HVec2 a, const LTEngine_HVec2 b, LTEngine_u16 thickness, const LTEngine_HColorA color, LTEngine_RendererFlags flags) {
    ((CRenderer *)handle.handle.ptr)->drawLine({LTEngine_Vec2_x(a), LTEngine_Vec2_y(a)}, {LTEngine_Vec2_x(b), LTEngine_Vec2_y(b)}, thickness, {LTEngine_ColorA_r(color), LTEngine_ColorA_g(color), LTEngine_ColorA_b(color), LTEngine_ColorA_a(color)}, flags);
}
void LTENGINE_API LTEngine_Renderer_drawPoints(LTEngine_HRenderer handle, const LTEngine_HPolygon polygon, const LTEngine_HColorA color, LTEngine_RendererFlags flags) {
    std::vector<LTEngine::Math::Vec2> points;
    auto cPoints = LTEngine_Polygon_getPoints((polygon));

    for (size_t i = 0; i < LTEngine_DynamicArray_Vec2_size(&cPoints); i++) {
        points.push_back({LTEngine_Vec2_x(LTEngine_DynamicArray_Vec2_get(&cPoints, i)), LTEngine_Vec2_y(LTEngine_DynamicArray_Vec2_get(&cPoints, i))});
        LTEngine_Vec2_free(LTEngine_DynamicArray_Vec2_get(&cPoints, i));
    }

    LTEngine_DynamicArray_Vec2_free(&cPoints);
    ((CRenderer *)handle.handle.ptr)->drawPoints({{LTEngine_Shape_x(polygon), LTEngine_Shape_y(polygon)}, points}, {LTEngine_ColorA_r(color), LTEngine_ColorA_g(color), LTEngine_ColorA_b(color), LTEngine_ColorA_a(color)}, flags);
}

void LTENGINE_API LTEngine_Renderer_drawImage(LTEngine_HRenderer handle, const LTEngine_HImage image, const LTEngine_HVec2 position, LTEngine_f32 rotation, const LTEngine_HRecti region, const LTEngine_HColorA color, LTEngine_RendererFlags flags) {
    ((CRenderer *)handle.handle.ptr)->drawImage(
        (const LTEngine::Rendering::Image *)image.handle.ptr,
        {(LTEngine::i32)LTEngine_Vec2_x(position), (LTEngine::i32)LTEngine_Vec2_y(position)},
        rotation,
        {LTEngine_Shapei_x(region), LTEngine_Shapei_y(region),
        LTEngine_Recti_w(region), LTEngine_Recti_h(region)},
        {LTEngine_ColorA_r(color), LTEngine_ColorA_g(color), LTEngine_ColorA_b(color), LTEngine_ColorA_a(color)},
        flags);
}

#endif