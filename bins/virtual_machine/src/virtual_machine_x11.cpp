#include <X11/Xlib.h>

int main(int argc, char** argv) {
  auto display = XOpenDisplay(nullptr);
  auto screen = DefaultScreen(display);
  auto visual = DefaultVisual(display, screen);
  auto depth = DefaultDepth(display, screen);

  XSetWindowAttributes attributes;
  attributes.background_pixel = XWhitePixel(display, screen);

  auto window = XCreateWindow(display, XRootWindow(display, screen), 200, 200, 350, 200, 5, depth,
                              InputOutput, visual, CWBackPixel, &attributes);
  XSelectInput(display, window, ExposureMask | KeyPressMask);
  auto font_info = XLoadQueryFont(display, "6x10");

  auto wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", True);
  XSetWMProtocols(display, window, &wm_delete, 1);

  XColor color, dummy;
  XAllocNamedColor(display, DefaultColormap(display, screen), "red", &color, &dummy);

  XGCValues gr_values;
  GC gr_context;

  gr_values.font = font_info->fid;
  gr_values.foreground = color.pixel;
  gr_context = XCreateGC(display, window, GCFont + GCForeground, &gr_values);
  XFlush(display);
  XMapWindow(display, window);
  XFlush(display);

  bool running = true;
  XEvent event;
  while (running) {
    XNextEvent(display, &event);

    switch (event.type) {
      case Expose: {
        XDrawLine(display, window, gr_context, 0, 0, 100, 100);
        XDrawString(display, window, gr_context, 100, 100, "hello", 5);
        break;
      }

      case ClientMessage: {
        running = false;
        break;
      }
    }
  }

  return 0;
}
