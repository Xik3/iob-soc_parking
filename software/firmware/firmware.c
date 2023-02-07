#include "system.h"
#include "periphs.h"
#include "iob-uart.h"
#include "printf.h"
#include "stdio.h"
#include "iob-gpio.h"
#include "iob-seg.h"
#include "iob-timer.h"

#define DISPLAY_RATE 1
#define SENSOR_RATE 11
#define SNAKE_RATE 100


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


int count_transitions(int prev, int current) {
  int count = 0;
  
  if (prev == 1 && current == 0) {
    prev = 0;
    count = 1;
  }
  if (prev == 2 && current == 0){
    prev = 0;
    count = 2;
  }

  //timer_reset();
  //while(timer_time_ms()<=SENSOR_RATE);
  return count;
}

void snake_i(uint8_t cars, uint8_t sseg_ca_value)
  {
    int i = 0;
    int max = 0;
    int ano = 0;
    uint8_t snake[14] = {119, 123, 125, 63, 137, 107, 109, 47, 79, 75, 77, 15, 11 ,13};
    
    switch(cars)
      {
      case 1:
	i = 0;
	max = 4;
	ano= 14;
	break;
      case 2:
	i = 5;
	max = 8;
	ano= 14;
	break;
      case 3:
	i = 9;
	max = 11;
	ano= 14;
      break;
      case 4:
	i = 12;
	max = 13;
	ano= 14;
      break;
      case 7:
	i = 0;
	max = 4;
	ano= 13;
	break;
      case 8:
	i = 5;
	max = 8;
	ano= 13;
	break;
      case 9:
	i = 9;
	max = 11;
	ano= 13;
      break;
      case 10:
	i = 12;
	max = 13;
	ano= 13;
      break;
      default:
      }
    
    for(i; i<=max; i++){

      sseg_ca_value = snake[i];
      seg_data_cat(sseg_ca_value);
      seg_data_ano(ano);
      timer_reset();
      while(timer_time_ms()<=SNAKE_RATE);
    }

  }

void display(uint8_t cars, uint8_t sseg_ca_value)
{
	uint8_t floor[4] = {48,79,18,56};
	uint8_t parking[7] = {127, 111, 79, 15, 13, 9, 1};
	if(cars == 0)
	  {
	    sseg_ca_value = parking[cars];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(14);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);

	    sseg_ca_value = floor[0];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(7);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);
	
	    sseg_ca_value = parking[cars];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(13);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);
	
	  }
	else if(cars <= 6 && cars > 0)
	  {

	    sseg_ca_value = parking[cars];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(14);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);

	    sseg_ca_value = floor[1];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(7);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);
	
	    sseg_ca_value = parking[0];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(13);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);
	  }

	else if (cars > 6 && cars < 12)
	  {
	    sseg_ca_value = parking[6];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(14);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);
	
	    sseg_ca_value = floor[2];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(7);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);
	
	    sseg_ca_value = parking[cars - 6];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(13);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);
	  }
	
	else if(cars == 12)
	  {
   
	    sseg_ca_value = parking[6];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(14);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);

	    sseg_ca_value = floor[3];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(7);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);
	
	    sseg_ca_value = parking[6];
	    seg_data_cat(sseg_ca_value);
	    seg_data_ano(13);
	    timer_reset();
	    while(timer_time_ms()<=DISPLAY_RATE);

	  }
    
}

void snake_o(uint8_t cars, uint8_t sseg_ca_value)
  {
    int i = 0;
    int max = 0;
    int ano = 0;
    uint8_t snake_o[10] = {47, 109, 107, 77, 73, 11, 95, 63, 125, 123};

    switch(cars)
      {
      case 0:
	i = 6;
	max = 9;
	ano= 14;
	break;
      case 1:
	i = 0;
	max = 2;
	ano= 14;
	break;
      case 2:
	i = 3;
	max = 4;
	ano= 14;
	break;
      case 3:
	i = 5;
	max = 5;
	ano= 14;
      break;
      case 6:
	i = 6;
	max = 9;
	ano= 13;
	break;
      case 7:
	i = 0;
	max = 2;
	ano= 13;
	break;
      case 8:
	i = 3;
	max = 4;
	ano= 13;
	break;
      case 9:
	i = 5;
	max = 5;
	ano= 13;
      default:
      }
    
    for(i; i<=max; i++){

      sseg_ca_value = snake_o[i];
      seg_data_cat(sseg_ca_value);
      seg_data_ano(ano);
      timer_reset();
      while(timer_time_ms()<=SNAKE_RATE);
    }
    

    }

int main()
{
  int sw =0;
  int i = 0;
  
  //init uart
  uart_init(UART_BASE,FREQ/BAUD);

  //init GPIO
  gpio_init(GPIO_BASE);

  //init SEG
  seg_init(SEG_BASE);

  gpio_set_output_enable(0x3);

  timer_init(TIMER_BASE);

  uint8_t sseg_ca_value;
  uint8_t flag = 0;
  uint8_t cars = 0;
  int prev, prev_o, prev_i,current,count;
  while(1)
    {
      if(gpio_get())
	{
	  printf("Value = %d\n\n",gpio_sensor_get());

	  while(gpio_sensor_i_get())
	    {
	      flag = 1;
	      display(cars, sseg_ca_value);
	    }

	  while(gpio_sensor_o_get())
	    {
	      flag = 2;
	      display(cars, sseg_ca_value);
	    }

	  switch(flag)
	    {
	    case 1:
	      if(cars < 12)
		{
		  cars += 1;
		  flag = 0;
		  snake_i(cars, sseg_ca_value);
		}
	      break;
	    case 2:
	      if(cars > 0)
		{
		  cars -= 1;
		  flag = 0;
		  snake_o(cars, sseg_ca_value);
		}
	      break;
	    default:
	    }

	  display(cars, sseg_ca_value);
	}



      
      //printf("Value of cars = %d\n\n",cars); 
      /*
      if(gpio_sensor_get())
	{
	  prev = gpio_sensor_get();
	  timer_reset();
	  while(timer_time_ms()<=SENSOR_RATE);
	  current = gpio_sensor_get();
	  count = count_transitions(prev, current);
       
	  switch(count)
	    {
	    case 1:
	      if(cars < 12)
		{
		  cars += 1;
		  snake_i(cars, sseg_ca_value);
		}
	      break;
	    case 2:
	      if(cars > 0)
		{
		  cars -= 1;
		  //snake_o(cars, sseg_ca_value);
		}
	      break;
	    default:
	    }

	  printf("Value of cars = %d\n\n",cars);
	
	}

	display(cars, sseg_ca_value);*/
	
    }  
    
  uart_finish();
}
