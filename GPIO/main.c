#include <libpynq.h>

int main(void) {
  pynq_init();
  gpio_init();
  
  gpio_reset();
  
  int c;
  int n[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, //0
    {0, 1, 1, 0, 0, 0, 0}, //1
    {1, 1, 0, 1, 1, 0, 1}, //2
    {1, 1, 1, 1, 0, 0, 1}, //3
    {0, 1, 1, 0, 0, 1, 1}, //4
    {1, 0, 1, 1, 0, 1, 1}, //5
    {1, 0, 1, 1, 1, 1, 1}, //6
    {1, 1, 1, 0, 0, 0, 0}, //7
    {1, 1, 1, 1, 1, 1 ,1}, //8
    {1 ,1 ,1 ,0 ,0 ,1 ,1} //9
  };
    
  scanf("%d", &c);
  while(c != 0){ 
    for(int i = 0; i < 12; i++){
      gpio_set_direction(i, GPIO_DIR_OUTPUT);
    }

    for(int i = 9; i < 12; i++){
      gpio_set_direction(i, GPIO_DIR_OUTPUT);
      gpio_set_level(i, 1);  
    }

    for(int i = 0; i < 7; i++){
       printf("GPIO %d: %d\n", i, n[(int) c][i]);
       printf("%d\n", (int) c);
       gpio_set_level(i, n[(int) c][i]);     
    }
    scanf("%d", &c);
    gpio_reset();  
  }


  gpio_destroy();
  pynq_destroy();
  return EXIT_SUCCESS;
}
