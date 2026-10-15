#include <libpynq.h>

int main(void) {
  pynq_init();
  leds_init_onoff();
  buttons_init();
  switches_init();

  while(get_button_state(3) == 0){
    if(get_switch_state(0) == 1){
      if(get_button_state(0) == 1){
        color_led_green_onoff(LED_ON);
      }
      if(get_button_state(2) == 1){
        color_led_red_onoff(LED_ON);
      }
      if(get_button_state(1) == 1){
        color_led_blue_onoff(LED_ON);
      }
    }else{
      color_led_off();
    }
  }

  leds_destroy();
  buttons_destroy();
  switches_destroy();
  pynq_destroy();

  return EXIT_SUCCESS;
}
