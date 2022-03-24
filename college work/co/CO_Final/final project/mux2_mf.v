module mux2_mf( funct, opcode , a, out );

	input 	[5:0] 	funct, opcode ;
	input 	[31:0] 	a ;
	output 	[31:0] 	out ;

    assign out = ( opcode == 6'd0 ) ? ( (funct == 6'd18 || funct == 6'd16 ) ? 32'd0 : a ) : a ;  
endmodule