module EX_MEM ( clk, pc_incr, branch_addr_in, CAL_in, rd2, jump_addr_in, wn_in, Zero_in, 
				pc_next, branch_addr_out, CAL_out, rd2_out, jump_addr_out, wn_out, opcode_in,
				Zero_out,MemRead_in, MemWrite_in, Branch_in, RegWrite_in, MemtoReg_in, Jump_in, 
				MemRead_out, MemWrite_out, Branch_out, RegWrite_out, MemtoReg_out, Jump_out, opcode_out ) ;
				
	input				Zero_in, clk ;
	input	[4:0]		wn_in ;
	input	[5:0]		opcode_in ;
	input	[31:0]		pc_incr, branch_addr_in,  CAL_in,  rd2, 	jump_addr_in ;
	input				MemRead_in,  MemWrite_in,  Branch_in,  RegWrite_in,  MemtoReg_in,  Jump_in	;		
	output	reg			Zero_out ;
	output  reg	[4:0]	wn_out ;
	output 	reg [5:0] 	opcode_out ;
	output  reg	[31:0]	pc_next, branch_addr_out, CAL_out, rd2_out, jump_addr_out ;
	output	reg			MemRead_out, MemWrite_out, Branch_out, RegWrite_out, MemtoReg_out, Jump_out ;
	
	always @( posedge clk ) begin
	
		pc_next 	    <= pc_incr ;
		branch_addr_out	<= branch_addr_in ;
		CAL_out 	  	<= CAL_in ;
		rd2_out 	 	<= rd2 ;
		jump_addr_out 	<= jump_addr_in ;
	
		wn_out 		  	<= wn_in ;
		opcode_out		<= opcode_in ;
	
		Zero_out 	  	<= Zero_in ;
		MemRead_out   	<= MemRead_in ;
		MemWrite_out  	<= MemWrite_in ;
		Branch_out 	  	<= Branch_in ;
		RegWrite_out  	<= RegWrite_in ;
		MemtoReg_out  	<= MemtoReg_in ;
		Jump_out 	  	<= Jump_in ;

	end	
endmodule