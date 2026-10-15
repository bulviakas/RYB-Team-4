#include <libpynq.h>
int main (void)
{
 // initialise all I/O
 pynq_init();
 switchbox_set_pin(IO_, SWB_UART0_RX);
 switchbox_set_pin(IO_RBPI07, SWB_UART0_TX);
 // initialize UART 0
 uart_init(UART0);
 // flush FIFOs of UART 0
 uart_reset_fifos(UART0);
 
 uint8_t byte[] = "good day\n";
 int i = 0;
 while (byte[i] != '\0') {
  uart_send (UART0, byte[i]);
  printf("sent byte %d\n", byte[i]);
  sleep_msec(10);
  i++;
 }
 
  // clean up after use
  pynq_destroy();
  return EXIT_SUCCESS;
}
