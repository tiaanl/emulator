#if defined(WIN32)
#include "virtual_machine_win32.cpp"
#elif defined(__linux__)
#include "virtual_machine_x11.cpp"
#endif  // defined(WIN32)
