module write_tft(
		input iCLK,
		input iRST,
		//camera input 
		input iDAVL,//DATA VALID
		input [7:0] i0v7660_data_8bit,
		input [10:0] oX_Cont,
		input [10:0] oY_Cont,
		//tft interferce
		output lcd2_cs,
		output lcd2_wr,
		output lcd2_rs,
		output lcd2_reset,
		output lcd2_rd,
		output [7:0] lcd2_data16H,
		output [7:0] lcd2_data16L
		);

assign lcd2_wr = reg_lcd2_wr;    
assign lcd2_rs = 1'b1; 
assign lcd2_rd = 1'b1;
assign lcd2_cs = 1'b0;
assign lcd2_reset = 1'b1;
assign {lcd2_data16H[7:0],lcd2_data16L[7:0]} = ov7660_data_16bit;
///////////////////////////////////////////////////////
//ov7660 data 8 bit to 16 bit
//功    能：将输入的8位数据转换成16位，同时进行位转换。
//由OV7660 RGB565 的输出格式 RRRRRGGGGGGBBBBB 改为 BBBBBGGGGGGRRRRR 格式
//转换后的数据符合TFT 数据输入格式
reg data_state;
reg [7:0] pre_i0v7660_data_8bit;
reg [15:0] ov7660_data_16bit;
wire iDVAL;
always@(posedge iCLK or negedge iRST)
	if(!iRST)
		begin
			data_state <= 1'b0;
		end
	else
	begin
	if(iDVAL)
		case(data_state)
		0 : begin
			pre_i0v7660_data_8bit <= i0v7660_data_8bit;
			data_state <= 1'b1;
			end
		1 : begin
			ov7660_data_16bit <= {pre_i0v7660_data_8bit,i0v7660_data_8bit};
//{i0v7660_data_8bit[4:0],pre_i0v7660_data_8bit[2:0],i0v7660_data_8bit[7:5],pre_i0v7660_data_8bit[7:3]};//{pre_i0v7660_data_8bit,i0v7660_data_8bit};
			data_state <= 1'b0;
			end
		endcase
	end

//功能：时钟转换：pclk_div2 = OV7660的PCLK 输入时钟/2 ;
//16位数据转换后，有效时间为一个PCLK周期，期间PCLK的下降沿时，pclk_div2为上升沿。
reg temp1;
reg temp2;
always@(posedge iCLK or negedge iRST)
	if(!iRST)
		begin
			temp1 <= 1'b0;
			temp2 <= 1'b0;
		end
	else
		begin
			temp1 <= iDVAL;
			temp2 <= temp1;
		end
reg reg_lcd2_wr;
always@(negedge iCLK or negedge iRST)
	if(!iRST)
		begin
			reg_lcd2_wr <= 1'b1;
		end
	else
		if(temp2)
			reg_lcd2_wr <= ~reg_lcd2_wr;
		else
			reg_lcd2_wr <= 1'b1;
endmodule


		