#include <libpynq.h>
#define SIGNAL_PERIOD 100000 // Frequency 1kHz

int main(void) {
  pynq_init();
  buttons_init();
  display_t display;
  display_init(&display);
  displayFillScreen(&display, RGB_PURPLE);
  switchbox_set_pin(IO_AR0, SWB_PWM0);
  pwm_init(PWM0,SIGNAL_PERIOD);
  pwm_set_duty_cycle(PWM0, 0.1 * SIGNAL_PERIOD);

  FontxFile fx16G[2];
  uint8_t buffer_fx16G[FontxGlyphBufSize];
  uint8_t fontWidth_fx16G, fontHeight_fx16G;
  InitFontx(fx16G, "../../../fonts/ILMH16XB.FNT", "");
  GetFontx(fx16G, 0, buffer_fx16G, &fontWidth_fx16G, &fontHeight_fx16G);
  displaySetFontDirection(&display, TEXT_DIRECTION0);
  uint8_t text[] = "Idle";
  displayDrawString(&display, fx16G, 20, fontHeight_fx16G * 7, text, RGB_WHITE);

  while (1) {
    if (get_button_state(0)) break;
    for (float i = 0.1; i <= 0.9; i += 0.2) {
      printf("Bomboclat: %.0f\n", i * 100);
      sleep_msec(100);
      pwm_set_duty_cycle(PWM0, i * SIGNAL_PERIOD);
    }
    for (float i = 0.9; i >= 0.1; i -= 0.2) {
      sleep_msec(100);
      pwm_set_duty_cycle(PWM0, i * SIGNAL_PERIOD);
      printf("Micheal: %.0f\n", i * 100);
    }
  }
  printf("Exploding...\n");
  pwm_destroy(PWM0);
  buttons_destroy();
  display_destroy(&display);
  pynq_destroy();
  return EXIT_SUCCESS;
}
