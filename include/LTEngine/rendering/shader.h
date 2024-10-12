#include "texture.hpp"

#pragma once

typedef struct shader_params_t {
    ltvec2_t obj_coord;
    ltvec2_t frag_coord;
    /* 
     * If it doesn't exist, it's nullptr
     *
     * Also for the double const,
     * it's a const ptr to a const texture
     */
    lttexture_t *const texture; 
    ltcolora_t color;
    u64 time;
    ltvec2u_t resolution;
} ltshader_params_t;


/*
 * Unlike nearly every other rendering api, the shader
 * is written in C++, now this has some pros and cons
 *
 * Pros:
 *   Better ofcuscation of the code
 *   Faster use of the shader
 *   Allowed to use all C/C++ features
 *   Very portable between different platforms
 *   Has the ability for endless argments and argment types
 *   Not limited to the shader language feature set
 *
 * Cons:
 *    Not editable after compilation
 *    Not portable to other languages
 *    Not portable to different renderers
 *
 *
 */
class ltshader_t {
public: 
    virtual ~ltshader_t() = default;

    virtual ltcolora_t fragment(const ltshader_params_t params) = 0;
};
