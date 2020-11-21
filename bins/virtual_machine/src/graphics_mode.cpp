#include "virtual_machine/graphics_mode.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace {

const char* g_vertex_shader_source = R"(
#version 330

layout(location = 0) in vec2 vs_in_position;
layout(location = 1) in vec2 vs_in_tex_coord;

out vec2 vs_out_tex_coord;

void main() {
  gl_Position = vec4(vs_in_position, 0.0f, 1.0f);
  vs_out_tex_coord = vs_in_tex_coord;
}
)";

const char* g_fragment_shader_source = R"(
#version 330 core

in vec2 vs_out_tex_coord;

out vec4 fs_out_frag_color;

uniform sampler2D u_texture;

void main() {
  float c = texture(u_texture, vs_out_tex_coord).r;
  fs_out_frag_color = vec4(c, c, c, 1.0f);
}
)";

GLuint create_shader(GLenum shader_type, const char* source) {
  auto shader = glCreateShader(shader_type);
  GLint length = strlen(source);
  glShaderSource(shader, 1, &source, &length);
  glCompileShader(shader);

  return shader;
}

}  // namespace

bool GraphicsMode::init(I16 screen_width, I16 screen_height) {
  screen_width_ = screen_width;
  screen_height_ = screen_height;

  int buffer_size = screen_width * screen_height;
  printf("buffer size: %d\n", buffer_size);
  color_buffer_ = (U8*)malloc(buffer_size);
  memset(color_buffer_, 0, buffer_size);

  program_ = glCreateProgram();

  auto vertex_shader = create_shader(GL_VERTEX_SHADER, g_vertex_shader_source);
  auto fragment_shader = create_shader(GL_FRAGMENT_SHADER, g_fragment_shader_source);

  glAttachShader(program_, vertex_shader);
  glAttachShader(program_, fragment_shader);

  glLinkProgram(program_);
  GLint success;
  glGetProgramiv(program_, GL_LINK_STATUS, &success);

  if (success != GL_TRUE) {
    char buffer[1024];
    GLint length;
    glGetProgramInfoLog(program_, sizeof(buffer), &length, buffer);
    buffer[length] = '\0';
    fprintf(stderr, "Error: %s\n", buffer);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  glUseProgram(0);

  glGenVertexArrays(1, &vertex_array_object_);
  glBindVertexArray(vertex_array_object_);

  static const F32 vertices[] = {
      -1.0f, -1.0f, 0.0f, 1.0f,  //
      +1.0f, -1.0f, 1.0f, 1.0f,  //
      +1.0f, +1.0f, 1.0f, 0.0f,  //
      +1.0f, +1.0f, 1.0f, 0.0f,  //
      -1.0f, +1.0f, 0.0f, 0.0f,  //
      -1.0f, -1.0f, 0.0f, 1.0f,  //
  };

  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexArrayAttrib(vertex_array_object_, 0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(F32), (void*)0);
  glEnableVertexArrayAttrib(vertex_array_object_, 1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(F32), (void*)(sizeof(F32) * 2));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, screen_width, screen_height, 0, GL_RED, GL_UNSIGNED_BYTE,
               color_buffer_);
  glTextureParameteri(texture_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTextureParameteri(texture_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);

  return true;
}

void GraphicsMode::render() {
  assert(color_buffer_);

  glUseProgram(program_);
  glBindVertexArray(vertex_array_object_);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, screen_width_, screen_height_, 0, GL_RED, GL_UNSIGNED_BYTE,
               color_buffer_);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  glUseProgram(0);
}

void GraphicsMode::destroy() {
  free(color_buffer_);
  color_buffer_ = nullptr;
  screen_width_ = 0;
  if (vertex_array_object_) {
    glDeleteVertexArrays(1, &vertex_array_object_);
    vertex_array_object_ = 0;
  }
  if (program_) {
    glDeleteProgram(program_);
    program_ = 0;
  }
}

void GraphicsMode::clear_screen(U8 color) {
  memset(color_buffer_, color, screen_width_ * screen_height_);
}

void GraphicsMode::set_pixel(I16 x, I16 y, U8 color) {
  assert(color_buffer_);

  I16 index = y * (screen_width_) + x;
  color_buffer_[index] = color;
}
