
module SHIFT_extend( shamt, ext_shamt) ;
	input [4:0] shamt ;
	output [31:0] ext_shamt ;
	assign ext_shamt = { 27'b0, shamt } ;
endmodule