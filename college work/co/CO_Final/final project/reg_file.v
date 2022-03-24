/*
	Title: Register File (32 32-bit registers)
	Editor: Selene (Computer System and Architecture Lab, ICE, CYCU)
	
	Input Port
		1. clk
		2. RegWrite: 控制暫存器是否可寫入
		3. RN1: rs欲讀取的暫存器編號
		4. RN2: rt欲讀取的暫存器編號
		5. WN: 欲寫入的暫存器編號
		6. WD: 寫入暫存器的資料
	Output Port
		1. RD1: rs暫存器所讀取的資料
		2. RD2: rt暫存器所讀取的資料
*/
module reg_file( clk, RegWrite, RN1, RN2, WN, WD, RD1, RD2, opcode, funct );
	input clk;
	input RegWrite;
	input[4:0] RN1, RN2, WN;
	input[5:0] opcode, funct ;
	input[31:0] WD;
	output[31:0] RD1, RD2;

	reg[31:0] RD1, RD2;
	reg[31:0] file_array[31:1];
	reg[31:0] hilo[1:0] ;
	
	always @( RN1 or file_array[RN1] or opcode or funct or hilo[0] or hilo[1] ) begin   
		
		if ( opcode == 6'd0 && funct == 6'd16 )	
			RD1 = hilo[0] ; // hi-number //
		else if ( opcode == 6'd0 && funct == 6'd18 )
			RD1 = hilo[1] ; // lo-number //
		else if ( RN1 == 0 )
			RD1 = 32'd0;
		else
			RD1 = file_array[RN1];
		$display( "%d, reg_file[%d] => %d (Port 1)", $time/10, RN1, RD1);
	end

	always @( RN2 or file_array[RN2] ) begin
		if ( RN2 == 0 )
			RD2 = 32'd0;
		else
			RD2 = file_array[RN2];
		$display( "%d, reg_file[%d] => %d (Port 2)", $time/10, RN2, RD2);
	end

	always @( posedge clk ) begin
		if ( RegWrite && (WN != 0) ) begin
			file_array[WN] <= WD;
			$display( "%d, reg_file[%d] <= %d (Write)", $time/10, WN, WD);
		end
	end
endmodule
