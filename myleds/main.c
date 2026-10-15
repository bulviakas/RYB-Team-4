#include <libpynq.h>
int main(void) {
  pynq_init();
///// begin of new code that you have type in (or copy):
for(int i = 0; i < 5; i++){
  leds_init_onoff();           // start using the LEDs
  green_led_onoff(0,LED_ON);  // switch LED 0 on
  sleep_msec(1000);            // wait for one second
  green_led_onoff(0,LED_OFF); // switch LED 0 off
  green_led_onoff(1,LED_ON);
  sleep_msec(1000);
  green_led_onoff(1,LED_OFF);
  green_led_onoff(2,LED_ON);
  sleep_msec(1000);
  green_led_onoff(2,LED_OFF);
  green_led_onoff(3,LED_ON);
  sleep_msec(1000);
  green_led_onoff(3,LED_OFF);
}
  leds_destroy();              // stop using the LEDs
///// end of new code
  pynq_destroy();
  return EXIT_SUCCESS;
}


