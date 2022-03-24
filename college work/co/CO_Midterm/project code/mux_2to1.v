`timescale 1ns/1ns

module mux_2to1( dataA, dataB, Ctrl, dataOut );
// dataA = 尚未移動的資料, dataB = 移動後的資料 //

input dataA ;
input dataB ;
input Ctrl ;
output dataOut;

assign dataOut = (Ctrl) ? dataB : dataA ;

endmodule