#ifdef LTENGINE_COMPONENT_OPENGL

#include <LTEngine/hash.hpp>

#include <LTEngine/backends/opengl/graphics/opengl11_renderer.hpp>

using namespace LTEngine;
using namespace LTEngine::Graphics;

OpenGL11Renderer3D::OpenGL11Renderer3D(OpenGL *context) {
    _cache.resize(4);
}

void OpenGL11Renderer3D::clear(ColorA color) {
    _add_draw_cmd([color]() {
        glClear(GL_DEPTH_BUFFER_BIT);
    }, -1);
}

void OpenGL11Renderer3D::set_pixel(ColorA pixel, Math::Vec2 position) {
    _add_draw_cmd([pixel, position, this]() {
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);

        glColor4f(pixel.r / 255.f, pixel.g / 255.f, pixel.b / 255.f, pixel.a / 255.f);
        glVertex2f(position.x, position.y);
    }, GL_POINT);
}

void OpenGL11Renderer3D::draw(Shapes::Cube cube, Math::Vec3 scale, Renderer::Material &material) {
    _add_draw_cmd([&cube, &scale, material, this]() {
        _apply_material(material);

        glTranslatef(cube.x, cube.y, cube.z);
        glRotatef(cube.rot_x, 1, 0, 0);
        glRotatef(cube.rot_y, 0, 1, 0);
        glRotatef(cube.rot_z, 0, 0, 1);
        glScalef(scale.x, scale.y, scale.z);

        float hx = cube.w / 2.0f;
        float hy = cube.h / 2.0f;
        float hz = cube.l / 2.0f;

        auto vertex = [&](float x, float y, float z, float u=0, float v=0) {
            if (material.diffuse_texture) glTexCoord2f(u, v);
            glVertex3f(x, y, z);
        };

        // Front
        vertex(-hx, -hy, hz, 0,0); vertex(hx, -hy, hz, 1,0); vertex(hx, hy, hz, 1,1);
        vertex(-hx, -hy, hz, 0,0); vertex(hx, hy, hz, 1,1); vertex(-hx, hy, hz, 0,1);

        // Back
        vertex(-hx, -hy, -hz, 0,0); vertex(-hx, hy, -hz, 0,1); vertex(hx, hy, -hz, 1,1);
        vertex(-hx, -hy, -hz, 0,0); vertex(hx, hy, -hz, 1,1); vertex(hx, -hy, -hz, 1,0);

        // Left
        vertex(-hx, -hy, -hz, 0,0); vertex(-hx, -hy, hz, 1,0); vertex(-hx, hy, hz, 1,1);
        vertex(-hx, -hy, -hz, 0,0); vertex(-hx, hy, hz, 1,1); vertex(-hx, hy, -hz, 0,1);

        // Right
        vertex(hx, -hy, -hz, 0,0); vertex(hx, hy, -hz, 0,1); vertex(hx, hy, hz, 1,1);
        vertex(hx, -hy, -hz, 0,0); vertex(hx, hy, hz, 1,1); vertex(hx, -hy, hz, 1,0);

        // Top
        vertex(-hx, hy, -hz, 0,0); vertex(-hx, hy, hz, 0,1); vertex(hx, hy, hz, 1,1);
        vertex(-hx, hy, -hz, 0,0); vertex(hx, hy, hz, 1,1); vertex(hx, hy, -hz, 1,0);

        // Bottom
        vertex(-hx, -hy, -hz, 0,0); vertex(hx, -hy, -hz, 1,0); vertex(hx, -hy, hz, 1,1);
        vertex(-hx, -hy, -hz, 0,0); vertex(hx, -hy, hz, 1,1); vertex(-hx, -hy, hz, 0,1);
    }, GL_TRIANGLES);
}


void OpenGL11Renderer3D::draw(Shapes::Sphere sphere, Math::Vec3 scale, Renderer::Material &material) {
    _add_draw_cmd([sphere, scale, &material, this]() {
        _apply_material(material);

        glTranslatef(sphere.x, sphere.y, 0.0f);
        glRotatef(sphere.rot_x, 1, 0, 0);
        glRotatef(sphere.rot_y, 0, 1, 0);
        glRotatef(sphere.rot_z, 0, 0, 1);
        glScalef(scale.x, scale.y, scale.z);

        const int slices = 16;
        const int stacks = 16;
        float radius = sphere.radius; // assume Shapes::Sphere has radius

        for (int i = 0; i < stacks; ++i) {
            float phi1 = (i / (float)stacks) * M_PI;
            float phi2 = ((i + 1) / (float)stacks) * M_PI;

            for (int j = 0; j < slices; ++j) {
                float theta1 = (j / (float)slices) * 2 * M_PI;
                float theta2 = ((j + 1) / (float)slices) * 2 * M_PI;

                auto vertex = [&](float r, float phi, float theta) {
                    float x = r * sinf(phi) * cosf(theta);
                    float y = r * cosf(phi);
                    float z = r * sinf(phi) * sinf(theta);
                    if (material.diffuse_texture) glTexCoord2f(theta / (2*M_PI), phi / M_PI);
                    glVertex3f(x, y, z);
                };

                // 2 triangles per quad on the sphere
                vertex(radius, phi1, theta1);
                vertex(radius, phi2, theta1);
                vertex(radius, phi2, theta2);

                vertex(radius, phi1, theta1);
                vertex(radius, phi2, theta2);
                vertex(radius, phi1, theta2);
            }
        }

    }, GL_TRIANGLES);
}


void OpenGL11Renderer3D::draw(Shapes::Cylinder cylinder, Math::Vec3 scale, Renderer::Material &material) {
    _add_draw_cmd([cylinder, scale, &material, this]() {
        _apply_material(material);

        glTranslatef(cylinder.x, cylinder.y, 0.0f);
        glRotatef(cylinder.rot_x, 1, 0, 0);
        glRotatef(cylinder.rot_y, 0, 1, 0);
        glRotatef(cylinder.rot_z, 0, 0, 1);
        glScalef(scale.x, scale.y, scale.z);

        const int slices = 16;
        float radius = cylinder.radius; // assume Shapes::Cylinder has radius
        float height = cylinder.height; // assume Shapes::Cylinder has height

        auto vertex = [&](float x, float y, float z, float u=0, float v=0) {
            if (material.diffuse_texture) glTexCoord2f(u, v);
            glVertex3f(x, y, z);
        };

        // Side faces
        for (int i = 0; i < slices; ++i) {
            float theta1 = (i / (float)slices) * 2 * M_PI;
            float theta2 = ((i + 1) / (float)slices) * 2 * M_PI;

            float x1 = radius * cosf(theta1);
            float z1 = radius * sinf(theta1);
            float x2 = radius * cosf(theta2);
            float z2 = radius * sinf(theta2);

            vertex(x1, 0, z1, i/(float)slices, 0);
            vertex(x1, height, z1, i/(float)slices, 1);
            vertex(x2, height, z2, (i+1)/(float)slices, 1);

            vertex(x1, 0, z1, i/(float)slices, 0);
            vertex(x2, height, z2, (i+1)/(float)slices, 1);
            vertex(x2, 0, z2, (i+1)/(float)slices, 0);
        }

        // Top and bottom caps
        for (int i = 0; i < slices; ++i) {
            float theta1 = (i / (float)slices) * 2 * M_PI;
            float theta2 = ((i + 1) / (float)slices) * 2 * M_PI;

            float x1 = radius * cosf(theta1);
            float z1 = radius * sinf(theta1);
            float x2 = radius * cosf(theta2);
            float z2 = radius * sinf(theta2);

            // Bottom
            vertex(0, 0, 0, 0.5f, 0.5f);
            vertex(x2, 0, z2, 0.5f + cosf(theta2)/2, 0.5f + sinf(theta2)/2);
            vertex(x1, 0, z1, 0.5f + cosf(theta1)/2, 0.5f + sinf(theta1)/2);

            // Top
            vertex(0, height, 0, 0.5f, 0.5f);
            vertex(x1, height, z1, 0.5f + cosf(theta1)/2, 0.5f + sinf(theta1)/2);
            vertex(x2, height, z2, 0.5f + cosf(theta2)/2, 0.5f + sinf(theta2)/2);
        }

    }, GL_TRIANGLES);
}


void OpenGL11Renderer3D::draw(Shapes::Capsule capsule, Math::Vec3 scale, Renderer::Material &material) {
    _add_draw_cmd([capsule, scale, &material, this]() {
        _apply_material(material);

        glTranslatef(capsule.x, capsule.y, 0.0f);
        glRotatef(capsule.rot_x, 1, 0, 0);
        glRotatef(capsule.rot_y, 0, 1, 0);
        glRotatef(capsule.rot_z, 0, 0, 1);
        glScalef(scale.x, scale.y, scale.z);

        const int slices = 16;
        const int stacks = 8;
        float radius = capsule.radius;
        float height = capsule.height; // cylinder portion only

        auto vertex = [&](float x, float y, float z, float u=0, float v=0) {
            if (material.diffuse_texture) glTexCoord2f(u, v);
            glVertex3f(x, y, z);
        };

        // Cylinder part
        for (int i = 0; i < slices; ++i) {
            float theta1 = (i / (float)slices) * 2 * M_PI;
            float theta2 = ((i + 1) / (float)slices) * 2 * M_PI;

            float x1 = radius * cosf(theta1);
            float z1 = radius * sinf(theta1);
            float x2 = radius * cosf(theta2);
            float z2 = radius * sinf(theta2);

            vertex(x1, 0, z1, i/(float)slices, 0);
            vertex(x1, height, z1, i/(float)slices, 1);
            vertex(x2, height, z2, (i+1)/(float)slices, 1);

            vertex(x1, 0, z1, i/(float)slices, 0);
            vertex(x2, height, z2, (i+1)/(float)slices, 1);
            vertex(x2, 0, z2, (i+1)/(float)slices, 0);
        }

        // Hemispheres top and bottom (approx)
        for (int i = 0; i < stacks; ++i) {
            float phi1 = (i / (float)stacks) * (M_PI/2);
            float phi2 = ((i+1) / (float)stacks) * (M_PI/2);

            for (int j = 0; j < slices; ++j) {
                float theta1 = (j / (float)slices) * 2 * M_PI;
                float theta2 = ((j+1) / (float)slices) * 2 * M_PI;

                auto vertex_sphere = [&](float r, float phi, float theta, float y_offset) {
                    float x = r * sinf(phi) * cosf(theta);
                    float y = r * cosf(phi) + y_offset;
                    float z = r * sinf(phi) * sinf(theta);
                    if (material.diffuse_texture) glTexCoord2f(theta / (2*M_PI), phi / M_PI);
                    glVertex3f(x, y, z);
                };

                // Top hemisphere
                vertex_sphere(radius, phi1, theta1, height);
                vertex_sphere(radius, phi2, theta1, height);
                vertex_sphere(radius, phi2, theta2, height);

                vertex_sphere(radius, phi1, theta1, height);
                vertex_sphere(radius, phi2, theta2, height);
                vertex_sphere(radius, phi1, theta2, height);

                // Bottom hemisphere
                vertex_sphere(radius, phi1, theta1, 0);
                vertex_sphere(radius, phi2, theta2, 0);
                vertex_sphere(radius, phi2, theta1, 0);

                vertex_sphere(radius, phi1, theta1, 0);
                vertex_sphere(radius, phi1, theta2, 0);
                vertex_sphere(radius, phi2, theta2, 0);
            }
        }

    }, GL_TRIANGLES);
}


void OpenGL11Renderer3D::draw(Shapes::Torus torus, Math::Vec3 scale, Renderer::Material &material) {
    _add_draw_cmd([torus, scale, &material, this]() {
        _apply_material(material);

        glTranslatef(torus.x, torus.y, 0.0f);
        glRotatef(torus.rot_x, 1, 0, 0);
        glRotatef(torus.rot_y, 0, 1, 0);
        glRotatef(torus.rot_z, 0, 0, 1);
        glScalef(scale.x, scale.y, scale.z);

        const int slices = 24;
        const int stacks = 16;
        float r = torus.inner_radius; // assume Shapes::Torus
        float R = torus.tube_radius;

        auto vertex = [&](float x, float y, float z, float u=0, float v=0) {
            if (material.diffuse_texture) glTexCoord2f(u, v);
            glVertex3f(x, y, z);
        };

        for (int i = 0; i < slices; ++i) {
            float phi1 = (i / (float)slices) * 2 * M_PI;
            float phi2 = ((i+1) / (float)slices) * 2 * M_PI;

            for (int j = 0; j < stacks; ++j) {
                float theta1 = (j / (float)stacks) * 2 * M_PI;
                float theta2 = ((j+1) / (float)stacks) * 2 * M_PI;

                auto torus_vertex = [&](float phi, float theta) {
                    float x = (R + r*cosf(theta)) * cosf(phi);
                    float y = r * sinf(theta);
                    float z = (R + r*cosf(theta)) * sinf(phi);
                    if (material.diffuse_texture) glTexCoord2f(phi/(2*M_PI), theta/(2*M_PI));
                    glVertex3f(x, y, z);
                };

                torus_vertex(phi1, theta1);
                torus_vertex(phi1, theta2);
                torus_vertex(phi2, theta2);

                torus_vertex(phi1, theta1);
                torus_vertex(phi2, theta2);
                torus_vertex(phi2, theta1);
            }
        }

    }, GL_TRIANGLES);
}


void OpenGL11Renderer3D::draw(Shapes::Polyhedron polyhedron, Math::Vec3 scale, Renderer::Material &material) {
    _add_draw_cmd([polyhedron, scale, &material, this]() {
        _apply_material(material);

        glTranslatef(polyhedron.x, polyhedron.y, 0.0f);
        glRotatef(polyhedron.rot_x, 1, 0, 0);
        glRotatef(polyhedron.rot_y, 0, 1, 0);
        glRotatef(polyhedron.rot_z, 0, 0, 1);
        glScalef(scale.x, scale.y, scale.z);

        const auto points = polyhedron.get_points();

        // Draw points connected in order
        for (size_t i = 1; i < points.size(); ++i) {
            if (material.diffuse_texture) glTexCoord2f(0, 0); // optional
            glVertex3f(points[i-1].x, points[i-1].y, points[i-1].z);
            glVertex3f(points[i].x, points[i].y, points[i].z);
        }

    }, GL_LINES);
}


void OpenGL11Renderer3D::flush() {
    auto run_queue = [this](std::queue<DrawCmd> &cmds, bool hud_mode = false) {
        GLint last_type = _draw_cmds.front().type;
        std::vector<DrawCmd> batch;

        auto run_batch = [&batch, last_type, hud_mode, this]() {
            for (DrawCmd &cmd : batch) {
                if (hud_mode) {
                    glDisable(GL_DEPTH_TEST);
                } else {
                    glEnable(GL_DEPTH_TEST);
                }

                glEnable(GL_LIGHTING);
                glEnable(GL_COLOR_MATERIAL);
                glEnable(GL_NORMALIZE);

                int gl_light_index = 0;
                for (const auto& light : get_lights()) {
                    if (gl_light_index >= 8) break; // OpenGL 1.1 supports max 8 lights
                    GLenum gl_light = GL_LIGHT0 + gl_light_index;

                    glEnable(gl_light);

                    
                    GLfloat ambient[4]  = { (light.ambient.r / 255.0f) * light.intensity,
                                             (light.ambient.g / 255.0f) * light.intensity,
                                             (light.ambient.b / 255.0f) * light.intensity,
                                             light.ambient.a / 255.0f };

                    GLfloat diffuse[4]  = { (light.color.r / 255.0f) * light.intensity,
                                             (light.color.g / 255.0f) * light.intensity,
                                             (light.color.b / 255.0f) * light.intensity,
                                             light.color.a / 255.0f };

                    GLfloat specular[4] = { (light.specular.r / 255.0f) * light.intensity,
                                             (light.specular.g / 255.0f) * light.intensity,
                                             (light.specular.b / 255.0f) * light.intensity,
                                             light.specular.a / 255.0f };

                    glLightfv(gl_light, GL_AMBIENT, ambient);
                    glLightfv(gl_light, GL_DIFFUSE, diffuse);
                    glLightfv(gl_light, GL_SPECULAR, specular);

                    GLfloat pos[4] = { light.position.x, light.position.y, light.position.z, light.type == Light::Type::Directional ? 0.0f : 1.0f };
                    glLightfv(gl_light, GL_POSITION, pos);

                    if (light.type == Light::Type::Spot) {
                        GLfloat dir[3] = { light.direction.x, light.direction.y, light.direction.z };
                        glLightfv(gl_light, GL_SPOT_DIRECTION, dir);
                        glLightf(gl_light, GL_SPOT_CUTOFF, light.cutoff_angle);
                    }
                }

                ++gl_light_index;

                // Disable unused lights
                for (; gl_light_index < 8; ++gl_light_index) {
                    glDisable(GL_LIGHT0 + gl_light_index);
                }

                glBegin(last_type);
                    glPushMatrix();
                        cmd.cmd();
                    glPopMatrix();
                glEnd();
            }
            batch.clear();
        };

        while (!_draw_cmds.empty()) {
            DrawCmd cmd = _draw_cmds.front();
            _draw_cmds.pop();

            if (last_type != cmd.type) {
                run_batch();
                last_type = cmd.type;
                continue;
            }

            batch.push_back(cmd);
        }
        run_batch();
    };

    run_queue(_draw_cmds);
    for (i8 i = std::numeric_limits<i8>().min(); i < std::numeric_limits<i8>().max(); i++) {
        if (_hud_draw_cmds.contains(i)) {
            run_queue(_hud_draw_cmds[i]);
        }
    }
    _hud_draw_cmds.clear();

    
    if (_flush_cycle_thrahes > 0.5 * _cache.size()) {
        _cache.resize(_cache.size() * 2);
        _flush_cycle_thrahes = 0;
    }
    _flush_cycle_thrahes = 0;
}


void OpenGL11Renderer3D::_add_draw_cmd(DrawCmdFunction function, GLint type) {
    DrawCmd cmd = {
        .cmd = function,
        .type = type
    };
    
    if (!is_hud_mode()) {
        _draw_cmds.push(cmd);
    } else {
        _hud_draw_cmds[get_hud_z_order()].push(cmd);
    }
}

GLuint OpenGL11Renderer3D::_gpu_texture(Image image) {
    u32 image_crc32 = Hash::crc32((u8*)image.get_mem_buffer(), image.get_size().x * image.get_size().y * sizeof(ColorA));
    size_t slot = 0;


    for (size_t i = 0; i < _cache.size(); i++) {
        if (_cache[i].valid) {
            if (image_crc32 == _cache[i].image_crc32) {
                return _cache[i].texture;
            }
        } else {
            slot = i;
        }
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);



    if (_cache[slot].valid) {
        size_t best_replacement = 0;
        for (size_t i = 0; i < _cache.size(); i++) {
            if (_cache[i].flushes_since_last_used > _cache[best_replacement].flushes_since_last_used) {
                slot = i;
            }
        }
        _flush_cycle_thrahes++;
    }

    _cache[slot].flushes_since_last_used = 0;
    _cache[slot].texture = texture;
    _cache[slot].image_crc32 = image_crc32;
    _cache[slot].valid = true;
    return texture;
}


void OpenGL11Renderer3D::_apply_material(const Material &material) {
    GLfloat diffuse[4]  = { material.base_color.r / 255.f, material.base_color.g / 255.f, material.base_color.b / 255.f, material.base_color.a / 255.f };
    GLfloat specular[4] = { material.smoothness, material.smoothness, material.smoothness, 1.0f };
    GLfloat emissive[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // default
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material.smoothness * 128.0f); // crude mapping
    
    glMaterialfv(GL_FRONT, GL_EMISSION, emissive);

    // Handle texture tiling & offset
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(material.texture_offset.x, material.texture_offset.y, 0.0f);
    glScalef(material.texture_tiling.x, material.texture_tiling.y, 1.0f);

    // Bind texture if present
    if (material.diffuse_texture) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _gpu_texture(material.diffuse_texture.value()));
    } else {
        glDisable(GL_TEXTURE_2D);
    }

    glMatrixMode(GL_MODELVIEW); // back to normal
}
#endif // LTENGINE_COMPONENT_OPENGL
