module ID_EX (  clk, pc_incr, rd1, rd2, ext_in, Jump_Dst_in, shamt_in, rt, rd , opcode_in,
				funct_in, funct_out, pc_next, rd1_out, rd2_out, ext_out, Jump_Dst_out, shamt_out,
				rt_out, rd_out, ALUOp_in, RegDst_in, ALUSrc_in, MemRead_in, MemWrite_in, opcode_out,
				Branch_in, RegWrite_in, MemtoReg_in, Jump_in, RegDst_out, ALUSrc_out, MemRead_out, 
				MemWrite_out, Branch_out, RegWrite_out, MemtoReg_out, Jump_out, ALUOp_out ) ;


	input 				clk  ;
	
	input	[1:0]		ALUOp_in ;
	input	[4:0]		rt,     rd ;
	input	[5:0]  	 	funct_in, opcode_in ;
	input 	[31:0]		pc_incr, rd1, 	  rd2,	   ext_in, 	Jump_Dst_in,  shamt_in ;
	input			RegDst_in,  ALUSrc_in,  MemRead_in,  MemWrite_in,  Branch_in,  RegWrite_in,  MemtoReg_in,  Jump_in	;		
	output	reg	[1:0]	ALUOp_out ;
	output	reg [4:0]	rt_out, rd_out ;
	output	reg	[5:0] 	funct_out, opcode_out ;
	output	reg	[31:0]	pc_next, rd1_out, rd2_out, ext_out, Jump_Dst_out, shamt_out ;
	output	reg		RegDst_out, ALUSrc_out, MemRead_out, MemWrite_out, Branch_out, RegWrite_out, MemtoReg_out, Jump_out ;
	

	
	always @( posedge clk ) begin
	
		
 		funct_out 	 <= funct_in ;
		pc_next 	 <= pc_incr ;
		rd1_out		 <= rd1 ;
		rd2_out 	 <= rd2 ;
		ext_out 	 <= ext_in ;
		Jump_Dst_out <= Jump_Dst_in ;
		shamt_out 	 <= shamt_in ;
		rt_out 		 <= rt ;
		rd_out  	 <= rd ;
		opcode_out	 <= opcode_in ;
		ALUOp_out 	 <= ALUOp_in ;
		RegDst_out 	 <= RegDst_in ;
		ALUSrc_out 	 <= ALUSrc_in ;
		MemRead_out  <= MemRead_in ;
		MemWrite_out <= MemWrite_in ;
		Branch_out 	 <= Branch_in ;
		MemtoReg_out <= MemtoReg_in ;
		Jump_out 	 <= Jump_in ;
		RegWrite_out <= RegWrite_in ;

	end
	
endmodule