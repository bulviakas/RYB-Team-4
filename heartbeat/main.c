#include <libpynq.h>

int main(void) {
  pynq_init();
  buttons_init();
  display_t display;
  display_init(&display);

  int pulse[240];
  int length = sizeof(pulse)/sizeof(pulse[0]);
  int p;
  int erase;

  while(get_button_state(3) == 0) {
      pulse[0] = get_button_state(0) * 60;
      for(int i = 0; i < length; i++) {
        if (i >= 9) {
          p = 120;
        }
        else{
          p = pulse[i] + 120;
        }
        if(p == 180){
          erase = 120;
        }else{
          erase = 180;
        }
        printf("i: %d\npulse: %d\np: %d\nerase %d\n", i, pulse[i], p, erase);

        displayDrawPixel(&display, i, p, RGB_YELLOW); 
        displayDrawPixel(&display, i, erase, RGB_BLACK);      
        sleep_msec(10); 
      }
      for(int i = 239; i > 0; i--){
        pulse[i] = pulse[i-1];
      }
      sleep_msec(10);  
  }
    displayFillScreen(&display, RGB_BLACK);

  pynq_destroy();
  return EXIT_SUCCESS;
}
