module lcd_switch(
		output lcd2_cs,
		output lcd2_wr,
		output lcd2_rs,
		output lcd2_reset,
		output lcd2_rd,
		output reg  [15:0] lcd2_data16,
		
		input lcd2_cs_cpu,
		input lcd2_wr_cpu,
		input lcd2_rs_cpu,
		input lcd2_reset_cpu,
		input lcd2_rd_cpu,
		input [15:0] lcd2_data16_cpu,
		
		input lcd2_cs_hw,
		input lcd2_wr_hw,
		input lcd2_rs_hw,
		input lcd2_reset_hw,
		input lcd2_rd_hw,
		input [15:0] lcd2_data16_hw,

		
		input [1:0] enable
		);
		
assign lcd2_cs = (enable[1:0]==2'b10) ?   lcd2_cs_hw : lcd2_cs_cpu;
assign lcd2_wr = (enable[1:0]==2'b10) ?   lcd2_wr_hw : lcd2_wr_cpu ;
assign lcd2_rs = (enable[1:0]==2'b10) ?   lcd2_rs_hw : lcd2_rs_cpu;
assign lcd2_reset = (enable[1:0]==2'b10) ?   lcd2_reset_hw : lcd2_reset_cpu;
assign lcd2_rd = (enable[1:0]==2'b10) ?   lcd2_rd_hw : lcd2_rd_cpu;


always@(enable[1] or enable[0])
	case(enable[1:0])
		2'b01	:	lcd2_data16[15:0]	<=	lcd2_data16_cpu[15:0];
		2'b10	:	lcd2_data16[15:0]	<=	lcd2_data16_hw[15:0];
		default	:	lcd2_data16[15:0]	<=	16'hzzzz;
	endcase

endmodule



