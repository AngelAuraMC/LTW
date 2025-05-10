/**
 * Created by: artDev
 * Copyright (c) 2025 artDev, SerpentSpirale, PojavLauncherTeam, Digital Genesis LLC.
 * For use under LGPL-3.0
 */

#include <stdbool.h>
#include "glformats.h"
#include "libraryinternal.h"
#include "GL/gl.h"
#include <stdio.h>

static GLint pick_depth_internalformat(GLenum* type, bool* convert) {
    switch (*type) {
        case GL_UNSIGNED_SHORT:
        case GL_UNSIGNED_INT:
            return GL_DEPTH_COMPONENT16;
        case GL_FLOAT:
            return GL_DEPTH_COMPONENT32F;
        default:
            *convert = true;
            *type = GL_UNSIGNED_SHORT;
            return GL_DEPTH_COMPONENT16;
    }
}

static GLint pick_depth_stencil_internalformat(GLenum* type, bool* convert) {
    switch (*type) {
        case GL_UNSIGNED_INT_24_8:
            return GL_DEPTH24_STENCIL8;
        case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:
            return GL_DEPTH32F_STENCIL8;
        default:
            *convert = true;
            *type = GL_UNSIGNED_INT_24_8;
            return GL_DEPTH24_STENCIL8;
    }
}

static GLint pick_red_internalformat(GLenum* type, bool* convert) {
    switch(*type) {
        case GL_BYTE:
            return GL_R8_SNORM;
        case GL_UNSIGNED_BYTE:
            return GL_R8;
        case GL_HALF_FLOAT:
            return GL_R16F;
        case GL_FLOAT:
            return GL_R32F;
        default:
            *convert = true;
            *type = GL_UNSIGNED_BYTE;
            return GL_R8;
    }
}

static GLint pick_rg_internalformat(GLenum* type, bool* convert) {
    switch(*type) {
        case GL_BYTE:
            return GL_RG8_SNORM;
        case GL_UNSIGNED_BYTE:
            return GL_RG8;
        case GL_HALF_FLOAT:
            return GL_RG16F;
        case GL_FLOAT:
            return GL_RG32F;
        default:
            *convert = true;
            *type = GL_UNSIGNED_BYTE;
            return GL_RG8;
    }
}

void pick_color_renderable_format(GLint* internalformat, GLenum* type, GLenum* format) {

}

void pick_format(GLint internalformat, GLenum* type, GLenum* format) {
    switch (internalformat) {
        // Unsized formats. In this case we always prefer the "byte" versions of them (meaning 32bit/24bit color)
        case GL_RGB: *format=GL_RGB; *type = GL_UNSIGNED_BYTE; break;
        case GL_RGBA: *format=GL_RGBA; *type = GL_UNSIGNED_BYTE; break;
        case GL_LUMINANCE_ALPHA: *format=GL_LUMINANCE_ALPHA; *type = GL_UNSIGNED_BYTE; break;
        case GL_LUMINANCE: *format=GL_LUMINANCE; *type = GL_UNSIGNED_BYTE; break;
        case GL_ALPHA: *format=GL_ALPHA; *type = GL_UNSIGNED_BYTE; break;
        // Sized Formats
        case GL_R8: *format=GL_RED; *type=GL_UNSIGNED_BYTE; break;
        case GL_R8_SNORM: *format=GL_RED; *type=GL_BYTE; break;
        case GL_R16F: *format=GL_RED; *type=GL_HALF_FLOAT; break;
        case GL_R32F: *format=GL_RED; *type=GL_FLOAT; break;
        case GL_R8UI: *format=GL_RED_INTEGER; *type=GL_UNSIGNED_BYTE; break;
        case GL_R8I: *format=GL_RED_INTEGER; *type=GL_BYTE; break;
        case GL_R16UI: *format=GL_RED_INTEGER; *type=GL_UNSIGNED_SHORT; break;
        case GL_R16I: *format=GL_RED_INTEGER; *type=GL_SHORT; break;
        case GL_R32UI: *format=GL_RED_INTEGER; *type=GL_UNSIGNED_INT; break;
        case GL_R32I: *format=GL_RED_INTEGER; *type=GL_INT; break;
        case GL_RG8: *format=GL_RG; *type=GL_UNSIGNED_BYTE; break;
        case GL_RG8_SNORM: *format=GL_RG; *type=GL_BYTE; break;
        case GL_RG16F: *format=GL_RG; *type=GL_HALF_FLOAT; break;
        case GL_RG32F: *format=GL_RG; *type=GL_FLOAT; break;
        case GL_RG8UI: *format=GL_RG_INTEGER; *type=GL_UNSIGNED_BYTE; break;
        case GL_RG8I: *format=GL_RG_INTEGER; *type=GL_BYTE; break;
        case GL_RG16UI: *format=GL_RG_INTEGER; *type=GL_UNSIGNED_SHORT; break;
        case GL_RG16I: *format=GL_RG_INTEGER; *type=GL_SHORT; break;
        case GL_RG32UI: *format=GL_RG_INTEGER; *type=GL_UNSIGNED_INT; break;
        case GL_RG32I: *format=GL_RG_INTEGER; *type=GL_INT; break;
        case GL_RGB8: *format=GL_RGB; *type=GL_UNSIGNED_BYTE; break;
        case GL_SRGB8: *format=GL_RGB; *type=GL_UNSIGNED_BYTE; break;
        case GL_RGB565: *format=GL_RGB; *type=GL_UNSIGNED_BYTE; break;
        case GL_RGB8_SNORM: *format=GL_RGB; *type=GL_BYTE; break;
        case GL_R11F_G11F_B10F: *format=GL_RGB; *type=GL_FLOAT; break;
        case GL_RGB9_E5: *format=GL_RGB; *type=GL_UNSIGNED_INT_5_9_9_9_REV; break;
        case GL_RGB16F: *format=GL_RGB; *type=GL_HALF_FLOAT; break;
        case GL_RGB32F: *format=GL_RGB; *type=GL_FLOAT; break;
        case GL_RGB8UI: *format=GL_RGB_INTEGER; *type=GL_UNSIGNED_BYTE; break;
        case GL_RGB8I: *format=GL_RGB_INTEGER; *type=GL_BYTE; break;
        case GL_RGB16UI: *format=GL_RGB_INTEGER; *type=GL_UNSIGNED_SHORT; break;
        case GL_RGB16I: *format=GL_RGB_INTEGER; *type=GL_SHORT; break;
        case GL_RGB32UI: *format=GL_RGB_INTEGER; *type=GL_UNSIGNED_INT; break;
        case GL_RGB32I: *format=GL_RGB_INTEGER; *type=GL_INT; break;
        case GL_RGBA8: *format=GL_RGBA; *type=GL_UNSIGNED_BYTE; break;
        case GL_SRGB8_ALPHA8: *format=GL_RGBA; *type=GL_UNSIGNED_BYTE; break;
        case GL_RGBA8_SNORM: *format=GL_RGBA; *type=GL_BYTE; break;
        case GL_RGB5_A1: *format=GL_RGBA; *type=GL_UNSIGNED_BYTE; break;
        case GL_RGBA4: *format=GL_RGBA; *type=GL_UNSIGNED_BYTE; break;
        case GL_RGB10_A2: *format=GL_RGBA; *type=GL_UNSIGNED_INT_2_10_10_10_REV; break;
        case GL_RGBA16F: *format=GL_RGBA; *type=GL_HALF_FLOAT; break;
        case GL_RGBA32F: *format=GL_RGBA; *type=GL_FLOAT; break;
        case GL_RGBA8UI: *format=GL_RGBA_INTEGER; *type=GL_UNSIGNED_BYTE; break;
        case GL_RGBA8I: *format=GL_RGBA_INTEGER; *type=GL_BYTE; break;
        case GL_RGB10_A2UI: *format=GL_RGBA_INTEGER; *type=GL_UNSIGNED_INT_2_10_10_10_REV; break;
        case GL_RGBA16UI: *format=GL_RGBA_INTEGER; *type=GL_UNSIGNED_SHORT; break;
        case GL_RGBA16I: *format=GL_RGBA_INTEGER; *type=GL_SHORT; break;
        case GL_RGBA32I: *format=GL_RGBA_INTEGER; *type=GL_INT; break;
        case GL_RGBA32UI: *format=GL_RGBA_INTEGER; *type=GL_UNSIGNED_INT; break;
        // Sized depth formats. Unsized formats handled before this function
        case GL_DEPTH_COMPONENT16: *format = GL_DEPTH_COMPONENT; *type = GL_UNSIGNED_SHORT; break;
        case GL_DEPTH_COMPONENT24: *format = GL_DEPTH_COMPONENT; *type = GL_UNSIGNED_INT; break;
        case GL_DEPTH_COMPONENT32F: *format = GL_DEPTH_COMPONENT; *type = GL_FLOAT; break;
        case GL_DEPTH24_STENCIL8: *format = GL_DEPTH_STENCIL; *type = GL_UNSIGNED_INT_24_8; break;
        case GL_DEPTH32F_STENCIL8: *format = GL_DEPTH_STENCIL; *type = GL_FLOAT_32_UNSIGNED_INT_24_8_REV; break;
        case GL_STENCIL_INDEX8: *format = GL_STENCIL_INDEX; *type = GL_UNSIGNED_BYTE; break;
    }
}


INTERNAL void pick_internalformat(GLint *internalformat, GLenum* type, GLenum* format, GLvoid const** data) {
    // Compared to OpenGL ES, desktop OpenGL implicitly supports way more depth/RGB formats without explicit sizing.
    // This function converts appropriate unsized formats to sized ones according to the type.
    bool convert_data;
    switch (*internalformat) {
        case GL_DEPTH_COMPONENT32:
            // 1.21.5 workaround: fix internalformat (not handled in ES drivers cause it's from GL 1.4)
            // Work around by selecting the equivalent type (for float) or 24-bit (for int)
            if(*type == GL_FLOAT) {
                *internalformat = GL_DEPTH_COMPONENT32F;
            } else {
                *internalformat = GL_DEPTH_COMPONENT24;
                if(*type != GL_UNSIGNED_INT) convert_data = true;
                *type = GL_UNSIGNED_INT;
            }
            break;
        case GL_DEPTH_COMPONENT:
            *internalformat =  pick_depth_internalformat(type, &convert_data);
            break;
        case GL_DEPTH_STENCIL:
            *internalformat = pick_depth_stencil_internalformat(type, &convert_data);
            break;
        case GL_RED:
            *internalformat = pick_red_internalformat(type, &convert_data);
            break;
        case GL_RG:
            *internalformat = pick_rg_internalformat(type, &convert_data);
            break;
        // Desktop OpenGL specifies integer color formats with a regular format and
        // a sized internal format.
        // GLES is quirky, though, and requires you to explicitly specify that the format is an integer one.
        case GL_R8I:
        case GL_R8UI:
        case GL_R16I:
        case GL_R16UI:
        case GL_R32I:
        case GL_R32UI:
            *format = GL_RED_INTEGER;
            break;
        case GL_RG8I:
        case GL_RG8UI:
        case GL_RG16I:
        case GL_RG16UI:
        case GL_RG32I:
        case GL_RG32UI:
            *format = GL_RG_INTEGER;
            break;
        case GL_RGB8I:
        case GL_RGB8UI:
        case GL_RGB16I:
        case GL_RGB16UI:
        case GL_RGB32I:
        case GL_RGB32UI:
            *format = GL_RGB_INTEGER;
            break;
        case GL_RGBA8I:
        case GL_RGBA8UI:
        case GL_RGBA16I:
        case GL_RGBA16UI:
        case GL_RGBA32I:
        case GL_RGBA32UI:
            *format = GL_RGBA_INTEGER;
            break;
        default:
            if(*data != NULL) break;
            bool _signed = false;
            // Pray that EXT_color_buffer_float exists on target if the float versions of the textures are used on framebuffers
            switch(*format) {
                case GL_RGB:
                    switch (*type) {
                        case GL_FLOAT:
                        case GL_HALF_FLOAT:
                            *internalformat = GL_R11F_G11F_B10F;
                            return;
                        case GL_UNSIGNED_SHORT:
                        case GL_UNSIGNED_BYTE:
                        case GL_UNSIGNED_INT:
                        case GL_SHORT:
                        case GL_BYTE:
                        case GL_INT:
                            if(*internalformat == GL_RGB16 || *internalformat == GL_RGB12 || *internalformat == GL_RGB10) {
                                // Color renderable 16 bit RGB integer formats don't exist on GLES
                                *internalformat = GL_R11F_G11F_B10F;
                                *type = GL_FLOAT;
                                return;
                            }

                    }

                    break;
                case GL_RGBA:
                    switch(*type) {
                        case GL_FLOAT:
                            *internalformat = GL_RGBA32F;
                            return;
                        case GL_HALF_FLOAT:
                            *internalformat = GL_RGBA16F;
                            return;
                        case GL_SHORT:
                        case GL_BYTE:
                        case GL_INT:
                            _signed = true;
                        case GL_UNSIGNED_SHORT:
                        case GL_UNSIGNED_BYTE:
                        case GL_UNSIGNED_INT:
                            if(*internalformat == GL_RGBA16 || *internalformat == GL_RGBA12) {
                                *format = GL_RGBA_INTEGER;
                                if(_signed) {
                                    *internalformat = GL_RGBA16I;
                                    *type = GL_SHORT;
                                }else {
                                    *internalformat = GL_RGBA16UI;
                                    *type = GL_UNSIGNED_SHORT;
                                }
                                return;
                            }
                    }
            }
            break;
    }
    // GL applications do not have to supply valid data to "type" and "format" fields if they are not uploading any data
    // So automatically pick the best options from ones available.
    if(*data == NULL) {
        pick_format(*internalformat, type, format);
        return;
    }
    if(*data != NULL && convert_data) {
        printf("LTW: we don't support format conversion at the moment. Sorry!\n");
    }
}