module MEM_WB ( clk, CAL_in, rd, wn, CAL_out, rd_out, wn_out, RegWrite_in, MemtoReg_in, RegWrite_out, MemtoReg_out ) ;

	input 			clk ;	
	input	[4:0]		wn ;
	input	[31:0]		CAL_in,  rd ;
	input			RegWrite_in, MemtoReg_in ;	
	output	reg [4:0]	wn_out ;
	output	reg [31:0]	CAL_out, rd_out ;	
	output	reg		RegWrite_out, MemtoReg_out ;
	
	always @( posedge clk ) begin
	
		CAL_out <= CAL_in ;
		rd_out <= rd ;
	
		wn_out <= wn ;
		
		RegWrite_out <= RegWrite_in ;
		MemtoReg_out <= MemtoReg_in ;
	
	
	end
	
endmodule