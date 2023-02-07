`timescale 1ns / 1ps
`include "system.vh"

module top_system(
	          input        clk,
	          input        reset,

	          //uart
	          output       uart_txd,
	          input        uart_rxd,
	          
	          output [1:0] gpio_output,
	          input [1:0]  gpio_input,

		  input [1:0]  SENSOR_IN,
		  output       GPIO_SENSOR_OUTPUT_I,
		  output       GPIO_SENSOR_OUTPUT_O,

		  output [6:0] seg_cat,
		  output [3:0] seg_anode
		  );

   //
   // RESET MANAGEMENT
   //

   //system reset

   wire                         sys_rst;

   reg [15:0] 			        rst_cnt;
   reg                          sys_rst_int;

   always @(posedge clk, posedge reset)
     if(reset) begin
        sys_rst_int <= 1'b0;
        rst_cnt <= 16'hFFFF;
     end else begin
        if(rst_cnt != 16'h0)
          rst_cnt <= rst_cnt - 1'b1;
        sys_rst_int <= (rst_cnt != 16'h0);
     end

   assign sys_rst = sys_rst_int;

   //
   // SYSTEM
   //
   system system
     (
      .clk           (clk),
      .rst           (sys_rst),
      .trap          (trap),

      //UART
      .uart_txd      (uart_txd),
      .uart_rxd      (uart_rxd),
      .uart_rts      (),
      .uart_cts      (1'b1),
      
      //GPIO
      .gpio_input	 (gpio_input),
      .gpio_output	 (gpio_output),

      .SENSOR_IN         (SENSOR_IN),
      .GPIO_SENSOR_OUTPUT_I	  (GPIO_SENSOR_OUTPUT_I),
      .GPIO_SENSOR_OUTPUT_O       (GPIO_SENSOR_OUTPUT_O),

      //SEG
      .seg_cat (seg_cat),
      .seg_anode (seg_anode)
      );

endmodule
