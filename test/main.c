#include <libpynq.h>
int main(void) {
  pynq_init();
  leds_init_onoff();
  buttons_init();
  switches_init();

  char c;

  while(c != 'q'){
    wait_until_any_button_pushed();

    //scanf("%c", &c);
    if(get_button_state(0)){
      green_led_onoff(0,LED_ON);
      sleep_msec(1000);
      green_led_onoff(0,LED_OFF);
    }
    if(get_button_state(1)){
      green_led_onoff(1,LED_ON);
      sleep_msec(1000);
      green_led_onoff(1,LED_OFF);
    }
    if(get_button_state(2)){
      green_led_onoff(2,LED_ON);
      sleep_msec(1000);
      green_led_onoff(2,LED_OFF);
    }
    if(get_button_state(3)){
      c = 'q';
    }
    if(get_switch_state(0)){
      green_led_onoff(0,LED_ON);
      sleep_msec(1000);
      green_led_onoff(0,LED_OFF);
    }
    if(get_switch_state(1)){
      green_led_onoff(1,LED_ON);
      sleep_msec(1000);
      green_led_onoff(1,LED_OFF);
    }  
  }

  leds_destroy();
  buttons_destroy();
  switches_destroy();
  pynq_destroy();
  return EXIT_SUCCESS;
}
