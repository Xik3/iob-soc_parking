#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "printf.h"
#include "stdio.h"
#include "iob-gpio.h"

char *send_string = "Sending this string as a file to console.\n"
                    "The file is then requested back from console.\n"
                    "The sent file is compared to the received file to confirm " 
                    "correct file transfer via UART using console.\n"
                    "Generating the file in the firmware creates an uniform "
                    "file transfer between pc-emul, simulation and fpga without"
                    " adding extra targets for file generation.\n";

// copy src to dst
// return number of copied chars (excluding '\0')
int string_copy(char *dst, char *src) {
    if (dst == NULL || src == NULL) {
        return -1;
    }
    int cnt = 0;
    while(src[cnt] != 0){
        dst[cnt] = src[cnt];
        cnt++;
    }
    dst[cnt] = '\0';
    return cnt;
}

// 0: same string
// otherwise: different
int compare_str(char *str1, char *str2, int str_size) {
    int c = 0;
    while(c < str_size) {
        if (str1[c] != str2[c]){
            return str1[c] - str2[c];
        }
        c++;
    }
    return 0;
}

int main()
{
  int sw =0;
  int i = 0;
  
  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  //init GPIO
  gpio_init(GPIO_BASE);
  //Enable LED[1] & LED[2]
  gpio_set_output_enable(0x3);
  
  while(1)
  {
	  //Check if SWITCH[0] or SWITCH[1] is on
	  sw = gpio_get();
	  if(sw == 1 || sw == 2)
	  {
		//Set LED[1] & LED[2] on
		gpio_set(0x3);
	  }
	  else
	  {	//Set LED[1] & LED[2] off
		gpio_set(0x0);
	  }
	  i = gpio_get();
	  printf("Value of switch = %d\n\n", i);
  }
  /*
  //test puts
  uart_puts("\n\n\nHello world!\n\n\n");

  //test printf with floats 
  printf("Value of Pi = %f\n\n", 3.1415);

  //test file send
  char *sendfile = malloc(1000);
  int send_file_size = 0;
  send_file_size = string_copy(sendfile, send_string);
  uart_sendfile("Sendfile.txt", send_file_size, sendfile);

  //test file receive
  char *recvfile = malloc(10000);
  int file_size = 0;
  file_size = uart_recvfile("Sendfile.txt", recvfile);

  //compare files
  if (compare_str(sendfile, recvfile, send_file_size)) {
      printf("FAILURE: Send and received file differ!\n");
  } else {
      printf("SUCCESS: Send and received file match!\n");
  }

  free(sendfile);
  free(recvfile);
  
  // initialize first and second terms
  int a = 0;
  int b = 1;

  // initialize the next term (3rd term)
  int next = a + b;

  // print the first two terms t1 and t2
  printf("Fibonacci Series: %d, %d, ", a, b);

  // print 3rd to nth terms
  for (i = 3; i <= 50; ++i) {
    printf("%d\n", next);
    a = b;
    b = next;
    next = a + b;
  
    }*/

  uart_finish();
}
