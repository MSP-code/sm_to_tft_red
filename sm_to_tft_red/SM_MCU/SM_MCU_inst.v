	SM_MCU u0 (
		.clk_in_clk          (<connected-to-clk_in_clk>),          //       clk_in.clk
		.reset_in_reset_n    (<connected-to-reset_in_reset_n>),    //     reset_in.reset_n
		.sdram_wire_addr     (<connected-to-sdram_wire_addr>),     //   sdram_wire.addr
		.sdram_wire_ba       (<connected-to-sdram_wire_ba>),       //             .ba
		.sdram_wire_cas_n    (<connected-to-sdram_wire_cas_n>),    //             .cas_n
		.sdram_wire_cke      (<connected-to-sdram_wire_cke>),      //             .cke
		.sdram_wire_cs_n     (<connected-to-sdram_wire_cs_n>),     //             .cs_n
		.sdram_wire_dq       (<connected-to-sdram_wire_dq>),       //             .dq
		.sdram_wire_dqm      (<connected-to-sdram_wire_dqm>),      //             .dqm
		.sdram_wire_ras_n    (<connected-to-sdram_wire_ras_n>),    //             .ras_n
		.sdram_wire_we_n     (<connected-to-sdram_wire_we_n>),     //             .we_n
		.pio_led_export      (<connected-to-pio_led_export>),      //      pio_led.export
		.lcd_data_out_export (<connected-to-lcd_data_out_export>), // lcd_data_out.export
		.lcd_rs_export       (<connected-to-lcd_rs_export>),       //       lcd_rs.export
		.lcd_wr_export       (<connected-to-lcd_wr_export>),       //       lcd_wr.export
		.lcd_cs_export       (<connected-to-lcd_cs_export>),       //       lcd_cs.export
		.lcd_rd_export       (<connected-to-lcd_rd_export>),       //       lcd_rd.export
		.lcd_reset_export    (<connected-to-lcd_reset_export>),    //    lcd_reset.export
		.scl_export          (<connected-to-scl_export>),          //          scl.export
		.sda_export          (<connected-to-sda_export>),          //          sda.export
		.vs_int_in_export    (<connected-to-vs_int_in_export>),    //    vs_int_in.export
		.sm_2strobe_export   (<connected-to-sm_2strobe_export>),   //   sm_2strobe.export
		.sm_1clr_export      (<connected-to-sm_1clr_export>),      //      sm_1clr.export
		.sm_1ena_export      (<connected-to-sm_1ena_export>),      //      sm_1ena.export
		.sm_mux_export       (<connected-to-sm_mux_export>),       //       sm_mux.export
		.sm_data_in_export   (<connected-to-sm_data_in_export>)    //   sm_data_in.export
	);

