module mux2_branch( opcode, pcrsrc, zero, branch );

    input zero ;
    input  [5:0] opcode ;
    input branch ; 
	output pcrsrc ;
	
	wire temp_eq ;
	wire temp_ne ;
	
	and( temp_eq, zero,	branch ) ;
	
	xor( temp_ne, zero, branch ) ;
	
	assign pcrsrc = ( opcode == 6'd4 ) ? temp_eq :( ( opcode == 6'd5 ) ? temp_ne : 1'dx ) ;
	
endmodule
