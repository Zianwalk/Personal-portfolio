`timescale 1ns/1ns
module HiLo( clk, DivAns, HiOut, LoOut, reset );
input clk ;
input reset ;
input [63:0] DivAns ;
output [31:0] HiOut ;
output [31:0] LoOut ;

reg [63:0] HiLo ;
reg count ;

always@( posedge clk or reset )
begin
	if (reset) count = 0 ;
	if (clk) count = count + 1 ;
		assign HiLo = (count > 0) ? DivAns : 64'b0 ;
end

assign HiOut = HiLo[63:32] ;
assign LoOut = HiLo[31:0] ;

endmodule