#include "RenderTexture.h"

REGISTER_FRAME_COMPONENT(RenderTexture);

RenderTexture* RenderTexture::set(texture_ptr new_texture) {
    texture = new_texture;
    return this;
}
