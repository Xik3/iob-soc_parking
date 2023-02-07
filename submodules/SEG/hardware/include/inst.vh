   //
   // SEG
   //

   iob_seg seg0
     (
      .clk     (clk),
      .rst     (rst),

      // Registers interface
      //.seg_input (seg_input),
      .seg_anode (seg_anode), 
      .seg_cat (seg_cat),
      .seg_data_enable (seg_data_enable),   
      
      // CPU interface
      .valid   (slaves_req[`valid(`SEG)]),
      .address (slaves_req[`address(`SEG,`iob_seg_swreg_ADDR_W+2)-2]),
      .wdata   (slaves_req[`wdata(`SEG)]),
      .wstrb   (slaves_req[`wstrb(`SEG)]),
      .rdata   (slaves_resp[`rdata(`SEG)]),
      .ready   (slaves_resp[`ready(`SEG)])
      );
