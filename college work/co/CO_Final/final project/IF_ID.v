module IF_ID ( clk, pc_incr, rd, pc_next, instr ) ;

	input 				clk ;
	input	[31:0] 		pc_incr, rd ;
	output reg [31:0] 	pc_next, instr ;


	always @( posedge clk ) begin
		pc_next  <= pc_incr ;
		instr	 <= rd ;
	end
	
endmodule