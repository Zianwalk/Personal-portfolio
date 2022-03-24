module mux2_cal( funct, alu_out, shift_out, dataOut ) ;
	input	[5:0]  funct ;
	input	[31:0] alu_out, shift_out ;
	output	[31:0] dataOut ;
	assign dataOut = ( funct == 6'd0 ) ? shift_out : alu_out ;
endmodule