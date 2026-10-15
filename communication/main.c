#include <libpynq.h>
#include <stdio.h>

/*
abreviations
- heartbeat = HB
- noise = NO
- decision making = DM
- motor control = MC
*/

int main (void)
{
 // initialise all I/O
 pynq_init();
 switches_init();
 buttons_init();
 leds_init_onoff();
 display_t display;
 display_init(&display);
 displayFillScreen(&display, RGB_BLACK);
 uart_init(UART0);
 uart_init(UART1);
 uart_reset_fifos(UART0);
 uart_reset_fifos(UART1);

// debug mode true/false
// prints extra info in terminal when enabled
bool debug = true;

// initialize variables
int mode; //current mode of the program

// IO pin assignments for each module
int IO_HB = IO_AR1;
int IO_NO = IO_AR2;
int IO_DM = IO_AR3;

//setting up buttons
gpio_set_direction(IO_BTN0, GPIO_DIR_INPUT);

// setup display
uint8_t buffer_fx16G[FontxGlyphBufSize];
uint8_t fontWidth_fx16G, fontHeight_fx16G;
FontxFile fx16G[2];
InitFontx(fx16G, "/boot/ILGH16XB.FNT", "");
GetFontx(fx16G, 0, buffer_fx16G, &fontWidth_fx16G, &fontHeight_fx16G);
displaySetFontDirection(&display, TEXT_DIRECTION180);

size_t i = 0;
ssize_t x;

//function for displaying text on the display
int displayText(uint8_t *text, uint16_t color){
    x = 0;
    int y = (fontHeight_fx16G * (i + 1));
    displayDrawString(&display, fx16G, x, y, text, color);
    i++;
    return i;
}

//function for sending bytes - channel: 0/1, byte: uint8_t byte[] = "str"
void send(int channel, uint8_t byte[]){
    int i = 0;
    while (byte[i] != '\0') {
        green_led_off(mode);
        uart_send (channel, byte[i]);
        printf("sent byte %c\n", byte[i]);
        sleep_msec(10);
        green_led_on(mode);
        i++;
    }
    green_led_on(mode);
}

//function for receiving bytes writing them to the display - channel: 0/1, color: color
int recv(int channel, uint16_t color){
    x = 0;
    uint8_t msg = 0;
    printf("listening\n");
    do {
        msg = uart_recv(channel);
        printf("%c", msg);
        int y = (fontHeight_fx16G * (i + 1));
        displayDrawChar(&display, fx16G, x, y, msg, color);
        x = x + 7;
    } while (msg != 10);
    i++;
    printf("\n");
    return i;
}

//the state of the switches on the pynq-board determines which mode/module
if(get_switch_state(0) == 1 && get_switch_state(1) == 1){
    //heartbeat
    mode = 0;
} else if(get_switch_state(0) == 0 && get_switch_state(1) == 1){
    //noise
    mode = 1;
} else if(get_switch_state(0) == 1 && get_switch_state(1) == 0){
    //decision making
    mode = 2;
} else if(get_switch_state(0) == 0 && get_switch_state(1) == 0){
    //motor control
    mode = 3;
}

if(debug){
    printf("mode: %d\n", mode);
}

green_led_on(mode);

switch(mode){
    case 0:
        //heartbeat module

        //set pin(s) for sending/receiving
        switchbox_set_pin(IO_HB, SWB_UART0_TX);
        
        do{

            //write module name on display
            char *str = "heartbeat submodule";
            displayText((uint8_t *)str, RGB_RED);

            //connect to DM            
            char *msg ="message sent";
            displayText((uint8_t *)msg, RGB_RED);
            uint8_t byte[] = "heartbeat connected\n";
            send(0, byte);
        } while(0);

        while(1){
            //put the code for the module here
            wait_until_button_pushed(BUTTON0);
            char *msg ="message sent";
            displayText((uint8_t *)msg, RGB_RED);
            uint8_t byte[] = "1\n";
            send(0, byte);
            wait_until_button_released (BUTTON0);
        }
        break;
    case 1:
        //noise module
        do{
            //set pin(s) for sending/receiving
            switchbox_set_pin(IO_NO, SWB_UART1_TX);
            //write module name on display
            char *str = "noise submodule";
            displayText((uint8_t *)str, RGB_BLUE);

            //connect to DM
            char *msg ="message sent";
            displayText((uint8_t *)msg, RGB_BLUE);
            uint8_t byte[] = "noise connected\n";
            send(1, byte);
        } while(0);

        while(1){
            //put the code for the module here
            wait_until_button_pushed(BUTTON0);
            char *msg ="message sent";
            displayText((uint8_t *)msg, RGB_BLUE);
            uint8_t byte[] = "1\n";
            send(1, byte);
            wait_until_button_released (BUTTON0);
        }
        break;
    case 2:
        do{
            //set pin(s) for sending/receiving
            switchbox_set_pin(IO_HB, SWB_UART0_RX);
            switchbox_set_pin(IO_NO, SWB_UART1_RX);
            switchbox_set_pin(IO_DM, SWB_UART0_TX);

            //write module name on display
            char *str = "decision making submodule";
            displayText((uint8_t *)str, RGB_GREEN);

            //connect to MC
            char *msg ="message sent";
            displayText((uint8_t *)msg, RGB_GREEN);
            uint8_t byte[] = "decision making connected\n";
            send(0, byte);            
            
        } while(0);

        while(1){
              //connect to HB module
              if(uart_has_data(0)){
                recv(0, RGB_RED);
              }
              //connect to NO module
              if(uart_has_data(1)){
                recv(1, RGB_BLUE);
              }
              //send data to MC module
              if(get_button_state(BUTTON0) == 1){
                char *msg ="message sent";
                displayText((uint8_t *)msg, RGB_GREEN);
                uint8_t byte[] = "1\n";
                send(0, byte);
                wait_until_button_released (BUTTON0);
              }
            //put the code for the module here
            break;
        }
        break;
        
    case 3:
        //motor control module
        do{
            //set pin(s) for sending/receiving
            switchbox_set_pin(IO_DM, SWB_UART0_RX); 

            //write module name on display
            char *str = "motor control submodule";
            displayText((uint8_t *)str, RGB_WHITE);

            //connect to DM
            recv(0, RGB_GREEN);
        } while(0);

        while(1){
            //put the code for the module here
            recv(0, RGB_GREEN);
        }
        break;
}
//clean up
pynq_destroy();
}