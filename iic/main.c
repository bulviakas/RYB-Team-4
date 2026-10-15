#include <libpynq.h>
int main(void)
{
  // this is the address by which this slave is reached by the master
  // different slaves must have different addresses
  const uint32_t my_slave_address = 0x70;
  // this array contains 32 registers that can be written & read by the master
  // the slave can of course modify the values of the registers
  uint32_t my_register_map[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
  const uint32_t my_register_map_length = sizeof(my_register_map)/sizeof(uint32_t);
 
  pynq_init();
  iic_init(IIC0);
  iic_set_slave_mode(IIC0, my_slave_address, &(my_register_map[0]), my_register_map_length);

  while (1) {
    // the slave mode handler must be run regularly to react to the master
    iic_slave_mode_handler(IIC0);
    uint8_t* byte[] = "Hello\n";
    int i = 0;
    while (byte[i] != '\0') {
      iic_write_register(IIC0, my_slave_address, 0, byte[i], 3);
      printf("sent byte %d\n", byte[i]);
      i++;
    }

    printf("message sent");
    sleep_msec(10);
  }
  //shit
  iic_reset(IIC0);
  iic_destroy(IIC0);
  pynq_destroy();
  return EXIT_SUCCESS;
}