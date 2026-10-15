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

  printf("Display and PWN init done\n");
  FontxFile fx16G[2];
  uint8_t buffer_fx16G[FontxGlyphBufSize];
  uint8_t fontWidth_fx16G, fontHeight_fx16G;
  InitFontx(fx16G, "/home/student/libpynq-5EWC0-2023-v0.2.6/fonts/ILGH24XB.FNT", "");
  GetFontx(fx16G, 0, buffer_fx16G, &fontWidth_fx16G, &fontHeight_fx16G);
  displaySetFontDirection(&display, TEXT_DIRECTION0);
  printf("Font loaded\n");
  uint8_t duty_text[15] = "Duty cycle: - ";
  displayDrawString(&display, fx16G, 28, fontHeight_fx16G * 4, duty_text, RGB_WHITE);

  while (1) {
    if (get_button_state(0)) break;
    for (int i = 1; i <= 9; i += 2) {
      if (get_button_state(0)) break;
      sleep_msec(500);
      pwm_set_duty_cycle(PWM0, (float)i / 10 * SIGNAL_PERIOD);
      displayDrawString(&display, fx16G, 28, fontHeight_fx16G * 4, duty_text, RGB_PURPLE);
      duty_text[12] = '0' + i;
      duty_text[13] = '0';
      displayDrawString(&display, fx16G, 28, fontHeight_fx16G * 4, duty_text, RGB_WHITE);
    }
    if (get_button_state(0)) break;
    for (int i = 9; i >= 1; i -= 2) {
      if (get_button_state(0)) break;
      sleep_msec(500);
      pwm_set_duty_cycle(PWM0, (float)i / 10 * SIGNAL_PERIOD);
      displayDrawString(&display, fx16G, 28, fontHeight_fx16G * 4, duty_text, RGB_PURPLE);
      duty_text[12] = '0' + i;
      duty_text[13] = '0';
      displayDrawString(&display, fx16G, 28, fontHeight_fx16G * 4, duty_text, RGB_WHITE);
    }
  }
  displayFillScreen(&display, RGB_RED);
  uint8_t done_text[] = "Done";
  displayDrawString(&display, fx16G, 28, fontHeight_fx16G * 4, done_text, RGB_WHITE);
  printf("Exploding...\n");
  pwm_destroy(PWM0);
  buttons_destroy();
  display_destroy(&display);
  pynq_destroy();
  return EXIT_SUCCESS;
}
