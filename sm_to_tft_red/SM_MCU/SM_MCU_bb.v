
module SM_MCU (
	clk_in_clk,
	reset_in_reset_n,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	pio_led_export,
	lcd_data_out_export,
	lcd_rs_export,
	lcd_wr_export,
	lcd_cs_export,
	lcd_rd_export,
	lcd_reset_export,
	scl_export,
	sda_export,
	vs_int_in_export,
	sm_2strobe_export,
	sm_1clr_export,
	sm_1ena_export,
	sm_mux_export,
	sm_data_in_export);	

	input		clk_in_clk;
	input		reset_in_reset_n;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output	[1:0]	pio_led_export;
	output	[15:0]	lcd_data_out_export;
	output		lcd_rs_export;
	output		lcd_wr_export;
	output		lcd_cs_export;
	output		lcd_rd_export;
	output		lcd_reset_export;
	output		scl_export;
	inout		sda_export;
	input	[1:0]	vs_int_in_export;
	output		sm_2strobe_export;
	output		sm_1clr_export;
	output		sm_1ena_export;
	output	[1:0]	sm_mux_export;
	input	[31:0]	sm_data_in_export;
endmodule
