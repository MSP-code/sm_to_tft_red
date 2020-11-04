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
//��    �ܣ��������8λ����ת����16λ��ͬʱ����λת����
//��OV7660 RGB565 �������ʽ RRRRRGGGGGGBBBBB ��Ϊ BBBBBGGGGGGRRRRR ��ʽ
//ת��������ݷ���TFT ���������ʽ
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

//���ܣ�ʱ��ת����pclk_div2 = OV7660��PCLK ����ʱ��/2 ;
//16λ����ת������Чʱ��Ϊһ��PCLK���ڣ��ڼ�PCLK���½���ʱ��pclk_div2Ϊ�����ء�
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


		