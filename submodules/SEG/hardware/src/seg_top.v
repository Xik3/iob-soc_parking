/*`timescale 1ns / 1ps

module seg_top
	(
		input 			clk,       	// from Basys 3
		input 			rst,    	// btnC
		input [3:0] 	data,	
		output 			dp,
		output [3:0] 	anode,   
		output [6:0] 	seg      	// 7 segment display segment pattern
    );
    
	
    // Internal wires for connecting inner modules
    wire w_10Hz;
    wire [3:0] w_1s, w_10s, w_100s, w_1000s;
    
    // Instantiate inner design modules
  	
	 
    
    digits digs
     (
      .clk_10Hz		(clk_10Hz),
      .reset		(rst),
      .ones			(ones), 
      .tens			(tens),
      .hundreds		(hundreds),
      .thousands	(thousands)
      );
      
    seg_core seg_core
     (
      .clk	(clk), 
      .reset		(rst), 
      .ones			(ones), 
      .tens			(tens),
      .hundreds		(hundreds), 
      .thousands	(thousands), 
      .seg			(seg), 
      .digit		(digit)
      );
	
endmodule
*/
