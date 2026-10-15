#include <libpynq.h>

int main(void) {
  pynq_init();

  display_t display;
  display_init(&display);
  display_set_flip(&display, true, true);
  displayFillScreen(&display, RGB_WHITE);

  sleep_msec(1000);

  displayFillScreen(&display, RGB_BLACK);
  display_destroy(&display);
  pynq_destroy();
  return EXIT_SUCCESS;
}
