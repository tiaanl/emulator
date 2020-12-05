#include <glad/glad.h>
// After glad/glad.h
#include <GLFW/glfw3.h>
#include <virtual_machine/graphics_mode.h>
#include <vm/assembler/assembler.h>
#include <vm/assembler/disassembler.h>
#include <vm/emulator/cpu.h>
#include <vm/emulator/emulator.h>
#include <vm/emulator/memory.h>

#include <cstdio>
#include <thread>

const I32 g_screen_width = 320;
const I32 g_screen_height = 200;
const I32 g_screen_zoom = 3;

int main() {
  if (glfwInit() != GLFW_TRUE) {
    return 1;
  }

  glfwSetErrorCallback(
      [](int code, const char* message) { fprintf(stderr, "ERROR (%d): %s", code, message); });

  glfwWindowHint(GLFW_RESIZABLE, 0);
  glfwWindowHint(GLFW_VISIBLE, 0);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  auto window = glfwCreateWindow(g_screen_width * g_screen_zoom, g_screen_height * g_screen_zoom,
                                 "Emulator Virtual Machine", nullptr, nullptr);
  if (!window) {
    return 1;
  }

  // Make the context current before initializing glad!
  glfwMakeContextCurrent(window);

  if (!gladLoadGL()) {
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  GraphicsMode graphics_mode;
  graphics_mode.init(g_screen_width, g_screen_height);

  vm::Emulator emulator;

  vm::Assembler a;
  a.emit_halt();

  emulator.upload_code(a.code(), a.size());

  //  vm::Disassembler d(memory.data(), memory.size());
  //  d.disassemble([](const char* line) { printf("%s\n", line); });

  glfwShowWindow(window);

  bool running = true;

  std::thread t([&emulator, &running]() {
    while (running && emulator.cpu().step() != vm::StepResult::Halt) {
    }
    printf("Program exit.\n");
  });

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // graphics_mode.clear_screen(127);
    graphics_mode.render();
    glfwSwapBuffers(window);
  }

  running = false;
  t.join();

  graphics_mode.destroy();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
