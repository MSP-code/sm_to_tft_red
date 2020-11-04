module max_find(
		//output
		Wmax_out,
		//input		
		Wmax_in,
		aclr,
		clock,
		w_ena
		
		);
		output [7:0] Wmax_out;
				
		input[7:0] Wmax_in;
		input	aclr;
		input clock;
		input w_ena;
		assign Wmax_out[7:0]= Wmax[7:0];
		reg [7:0]Wmax;
	
	always@(posedge clock or posedge aclr )
	begin
	if(aclr)
	Wmax[7:0]<=0;
	else
	begin
	if (w_ena)
	begin
	if(Wmax[7:0]<Wmax_in[7:0])
	Wmax[7:0]<=Wmax_in[7:0];
	end
	end
	end
endmodule