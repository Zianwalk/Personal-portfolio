
module Multiplier( clk, dataA, dataB, Signal, dataOut, reset ) ;

parameter MULTU = 6'b011001 ;

input       clk ;
input[31:0] dataA ;
input[31:0] dataB ;
input      reset ;
reg [63:0] tempa ;
reg [31:0] tempb ;
input[5:0] Signal ;
output[63:0] dataOut ; // always block 輸出 須為 reg // 
reg [63:0] total ;
reg [5:0] count ;
always@(reset) begin
	tempa = (reset) ? 64'b0 : tempa ;
	tempb = (reset) ? 32'b0 : tempb ;
	total = (reset) ? 64'b0 : total ;
	count = (reset) ? 6'b0 : count ;
	
end
always@(Signal) begin
	tempa = (Signal == MULTU) ? {32'b0, dataA} : tempa ;
	tempb = (Signal == MULTU) ? dataB : tempb ;
end 

always@(posedge clk) begin // clock 訊號 //
    
	if (Signal == MULTU) begin
		if ( tempb[0] ) begin
			total = total + tempa ;
		end
		
		if ( count == 6'd32 ) begin
			count = 6'b0 ;
			total = 64'b0 ;
		end
		count = count + 1 ;
		tempa = tempa << 1 ;
		tempb = tempb >> 1 ;
	end
end

assign dataOut = total ;
endmodule