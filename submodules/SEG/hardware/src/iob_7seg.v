`timescale 1ns/1ps
`include "iob_lib.vh"
`include "iob_seg_swreg_def.vh"


module iob_seg
  # (
     parameter DATA_W = 32, //PARAM & 32 & 64 & CPU data width
     parameter ADDR_W = `iob_seg_swreg_ADDR_W, //CPU address section width
     parameter SEG_W = 32 //PARAM Number of SEG (can be up to DATA_W)
     )

  (

   //CPU interface
`include "iob_s_if.vh"

    // inputs and outputs have dedicated interface
    //input [SEG_W-1:0] seg_input,
    output [6:0] seg_cat,
    output [3:0] seg_anode,
    // output enable can be used to tristate outputs on external module
    output [SEG_W-1:0] seg_data_enable,
    

`include "iob_gen_if.vh"
   );

//BLOCK Register File & Configuration control and status register file.
`include "iob_seg_swreg_gen.vh"


	// SWRegs    
    `IOB_WIRE(SEG_DATA_ENABLE, DATA_W)
    iob_reg #(.DATA_W(DATA_W))
    seg_data_enable_reg (
        .clk        (clk),
        .arst       (rst),
        .rst        (rst),
        .en         (SEG_DATA_ENABLE_en),
        .data_in    (SEG_DATA_ENABLE_wdata),
        .data_out   (SEG_DATA_ENABLE)
    );
    
    `IOB_WIRE(SEG_DATA_CAT, DATA_W)
    iob_reg #(.DATA_W(DATA_W))
    seg_data_cat    (
        .clk        (clk),
        .arst       (rst),
        .rst        (rst),
        .en         (SEG_DATA_CAT_en),
        .data_in    (SEG_DATA_CAT_wdata),
        .data_out   (SEG_DATA_CAT)
    );
    
    `IOB_WIRE(SEG_DATA_ANO, DATA_W)
    iob_reg #(.DATA_W(DATA_W))
    seg_data_ano    (
        .clk        (clk),
        .arst       (rst),
        .rst        (rst),
        .en         (SEG_DATA_ANO_en),
        .data_in    (SEG_DATA_ANO_wdata),
        .data_out   (SEG_DATA_ANO)
    );
    
    //assign SEG_INPUT_rdata = seg_input;
    assign seg_cat = SEG_DATA_CAT;
    assign seg_anode = SEG_DATA_ANO;
    assign seg_data_enable = SEG_DATA_ENABLE;


   
endmodule
    
