#include <glad/glad.h>
// After glad/glad.h
#include <GLFW/glfw3.h>
#include <virtual_machine/graphics_mode.h>
#include <vm/assembler/assembler.h>
#include <vm/assembler/disassembler.h>
#include <vm/emulator/cpu.h>
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

  vm::Memory memory(1024);
  vm::Bus bus;
  bus.add_range(0x0000, 0x0000, memory.size(), vm::Memory::load, vm::Memory::store, &memory);
  bus.add_range(0xA000, 0x0000, U32(g_screen_width * g_screen_height),
                GraphicsMode::graphics_mode_fetch_func, GraphicsMode::graphics_mode_store_func,
                &graphics_mode);
  vm::CPU cpu(&bus);

  vm::Assembler a(memory.data(), memory.size());

  auto count = 0;
  count += a.emit_mov_reg_from_lit(vm::Register::DS, 0xA000);
  count += a.emit_mov_reg_from_lit(vm::Register::DI, 0x0000);
  count += a.emit_mov_reg_from_lit(vm::Register::CX, 1);
  // count += a.emit_multiply(vm::Register::CX, 0x10);
  auto label_loop = a.label();
  count += a.emit_mov_reg_addr_from_lit(vm::Register::DI, 255);
  count += a.emit_add(vm::Register::DI, 1);
  count += a.emit_subtract(vm::Register::CX, 1);
  count += a.emit_compare_reg_to_lit(vm::Register::CX, 0);
  count += a.emit_jump_if_not_equal(label_loop);
  count += a.emit_halt();

  printf("Wrote %d bytes of instructions\n", count);

  vm::Disassembler d(memory.data(), memory.size());
  d.disassemble([](const char* line) { printf("%s\n", line); });

  glfwShowWindow(window);

  bool running = true;

  std::thread t([&cpu, &running]() {
    while (running && cpu.step() != vm::StepResult::Halt) {
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
