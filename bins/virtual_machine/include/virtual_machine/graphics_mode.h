#pragma once

#include <glad/glad.h>

#include <cassert>
#include <cstdio>

class GraphicsMode {
public:
  GraphicsMode() = default;
  ~GraphicsMode() = default;

  bool init(I16 screen_width, I16 screen_height);
  void render();
  void destroy();

  void clear_screen(U8 color);
  void set_pixel(I16 x, I16 y, U8 color);

  static U8 graphics_mode_fetch_func(void* data, U16 addr) {
    return 0;
  }

  static void graphics_mode_store_func(void* data, U16 addr, U8 value) {
    auto* graphics_mode = (GraphicsMode*)data;
    assert(addr < graphics_mode->screen_width_ * graphics_mode->screen_height_);
    printf("addr: %d\n", addr);
    graphics_mode->color_buffer_[addr] = value;
  }

private:
  I16 screen_width_ = 0;
  I16 screen_height_ = 0;
  U32 program_ = 0;
  U32 vertex_array_object_ = 0;
  U32 texture_ = 0;
  U8* color_buffer_ = nullptr;
};
