#include <glad/glad.h>
// After glad/glad.h
#include <GLFW/glfw3.h>
#include <assembler/assembler.h>
#include <emulator/cpu.h>
#include <emulator/memory.h>
#include <virtual_machine/graphics_mode.h>

#include <cstdio>

const I32 g_screen_width = 320;
const I32 g_screen_height = 200;
const I32 g_screen_zoom = 3;

int main() {
  if (glfwInit() != GLFW_TRUE) {
    return 1;
  }

  glfwWindowHint(GLFW_RESIZABLE, 0);
  glfwWindowHint(GLFW_VISIBLE, 0);

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

  glfwShowWindow(window);

  auto memory = emulator::Memory::create(1024);
  auto bus = emulator::Bus::create();
  bus.add_range(0, memory.size, emulator::memory_fetch_func, emulator::memory_store_func, &memory);
  bus.add_range(0xB800, U16(g_screen_width * g_screen_height),
                GraphicsMode::graphics_mode_fetch_func, GraphicsMode::graphics_mode_store_func,
                &graphics_mode);
  auto cpu = emulator::CPU::create(&bus);

  U8* ip = memory.data;

  ip += assembler::emit_mov_reg_from_lit(ip, emulator::Register::AX, 0xB800);
  ip += assembler::emit_mov_reg_from_lit(ip, emulator::Register::BX, g_screen_width);
  ip += assembler::emit_multiply(ip, emulator::Register::BX, g_screen_height / 2);
  auto label_loop = U16(ip - memory.data);
  ip += assembler::emit_mov_reg_addr_from_lit(ip, emulator::Register::AX, 255);
  ip += assembler::emit_add(ip, emulator::Register::AX, 1);
  ip += assembler::emit_subtract(ip, emulator::Register::BX, 1);
  ip += assembler::emit_compare_reg_to_lit(ip, emulator::Register::BX, 0);
  ip += assembler::emit_jump_if_not_equal(ip, label_loop);
  ip += assembler::emit_jump_addr(ip, 0);
  assembler::emit_halt(ip);

  printf("Wrote %zu bytes of instructions\n", ip - memory.data);

  U64 ticks = 0;

  bool running = true;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    if (running && cpu.step() == emulator::StepResult::Halt) {
      running = false;
    }

    printf("%d\n", cpu.get_register(emulator::Register::BX));
    ++ticks;
    if (ticks > 2000) {
      ticks %= 2000;
      graphics_mode.render();
      glfwSwapBuffers(window);
      // graphics_mode.clear_screen(127);
    }
  }

  graphics_mode.destroy();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
