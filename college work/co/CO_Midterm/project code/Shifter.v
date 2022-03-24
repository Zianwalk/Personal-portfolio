`timescale 1ns/1ns
module Shifter( dataA, dataB, Signal, dataOut, reset );
input reset ;
input [31:0] dataA ;
input [31:0] dataB ;
input [5:0] Signal ;
output [31:0] dataOut ;


wire [31:0] temp ;
wire [31:0] temp1 ;
wire [31:0] temp2 ;
wire [31:0] temp3 ;
wire [31:0] temp4 ;
parameter SLL = 6'b000000;
	
/*
reset訊號 如果是reset就做歸0
*/
	

			//temp = dataA >> dataB ;
			mux_2to1 bit_0_1( dataA[0], 1'b0, dataB[0], temp[0] ) ; 
			//mux_2to1 bit_0_1( .dataA(dataA[0]), .dataB(1'b0), .Ctrl(dataB[0]), .dataOut(temp[0]) ) ; 
			mux_2to1 bit_1_1( .dataA(dataA[1]), .dataB(dataA[0]), .Ctrl(dataB[0]), .dataOut(temp[1]) ) ; 
			mux_2to1 bit_2_1( .dataA(dataA[2]), .dataB(dataA[1]), .Ctrl(dataB[0]), .dataOut(temp[2]) ) ; 
			mux_2to1 bit_3_1( .dataA(dataA[3]), .dataB(dataA[2]), .Ctrl(dataB[0]), .dataOut(temp[3]) ) ; 
			mux_2to1 bit_4_1( .dataA(dataA[4]), .dataB(dataA[3]), .Ctrl(dataB[0]), .dataOut(temp[4]) ) ; 
			mux_2to1 bit_5_1( .dataA(dataA[5]), .dataB(dataA[4]), .Ctrl(dataB[0]), .dataOut(temp[5]) ) ; 
			mux_2to1 bit_6_1( .dataA(dataA[6]), .dataB(dataA[5]), .Ctrl(dataB[0]), .dataOut(temp[6]) ) ; 
			mux_2to1 bit_7_1( .dataA(dataA[7]), .dataB(dataA[6]), .Ctrl(dataB[0]), .dataOut(temp[7]) ) ; 
			mux_2to1 bit_8_1( .dataA(dataA[8]), .dataB(dataA[7]), .Ctrl(dataB[0]), .dataOut(temp[8]) ) ; 
			mux_2to1 bit_9_1( .dataA(dataA[9]), .dataB(dataA[8]), .Ctrl(dataB[0]), .dataOut(temp[9]) ) ; 
			mux_2to1 bit_10_1( .dataA(dataA[10]), .dataB(dataA[9]), .Ctrl(dataB[0]), .dataOut(temp[10]) ) ; 
			mux_2to1 bit_11_1( .dataA(dataA[11]), .dataB(dataA[10]), .Ctrl(dataB[0]), .dataOut(temp[11]) ) ; 
			mux_2to1 bit_12_1( .dataA(dataA[12]), .dataB(dataA[11]), .Ctrl(dataB[0]), .dataOut(temp[12]) ) ; 
			mux_2to1 bit_13_1( .dataA(dataA[13]), .dataB(dataA[12]), .Ctrl(dataB[0]), .dataOut(temp[13]) ) ; 
			mux_2to1 bit_14_1( .dataA(dataA[14]), .dataB(dataA[13]), .Ctrl(dataB[0]), .dataOut(temp[14]) ) ; 
			mux_2to1 bit_15_1( .dataA(dataA[15]), .dataB(dataA[14]), .Ctrl(dataB[0]), .dataOut(temp[15]) ) ; 
			mux_2to1 bit_16_1( .dataA(dataA[16]), .dataB(dataA[15]), .Ctrl(dataB[0]), .dataOut(temp[16]) ) ; 
			mux_2to1 bit_17_1( .dataA(dataA[17]), .dataB(dataA[16]), .Ctrl(dataB[0]), .dataOut(temp[17]) ) ; 
			mux_2to1 bit_18_1( .dataA(dataA[18]), .dataB(dataA[17]), .Ctrl(dataB[0]), .dataOut(temp[18]) ) ; 
			mux_2to1 bit_19_1( .dataA(dataA[19]), .dataB(dataA[18]), .Ctrl(dataB[0]), .dataOut(temp[19]) ) ; 
			mux_2to1 bit_20_1( .dataA(dataA[20]), .dataB(dataA[19]), .Ctrl(dataB[0]), .dataOut(temp[20]) ) ; 
			mux_2to1 bit_21_1( .dataA(dataA[21]), .dataB(dataA[20]), .Ctrl(dataB[0]), .dataOut(temp[21]) ) ; 
			mux_2to1 bit_22_1( .dataA(dataA[22]), .dataB(dataA[21]), .Ctrl(dataB[0]), .dataOut(temp[22]) ) ; 
			mux_2to1 bit_23_1( .dataA(dataA[23]), .dataB(dataA[22]), .Ctrl(dataB[0]), .dataOut(temp[23]) ) ; 
			mux_2to1 bit_24_1( .dataA(dataA[24]), .dataB(dataA[23]), .Ctrl(dataB[0]), .dataOut(temp[24]) ) ; 
			mux_2to1 bit_25_1( .dataA(dataA[25]), .dataB(dataA[24]), .Ctrl(dataB[0]), .dataOut(temp[25]) ) ; 
			mux_2to1 bit_26_1( .dataA(dataA[26]), .dataB(dataA[25]), .Ctrl(dataB[0]), .dataOut(temp[26]) ) ; 
			mux_2to1 bit_27_1( .dataA(dataA[27]), .dataB(dataA[26]), .Ctrl(dataB[0]), .dataOut(temp[27]) ) ; 
			mux_2to1 bit_28_1( .dataA(dataA[28]), .dataB(dataA[27]), .Ctrl(dataB[0]), .dataOut(temp[28]) ) ; 
			mux_2to1 bit_29_1( .dataA(dataA[29]), .dataB(dataA[28]), .Ctrl(dataB[0]), .dataOut(temp[29]) ) ; 
			mux_2to1 bit_30_1( .dataA(dataA[30]), .dataB(dataA[29]), .Ctrl(dataB[0]), .dataOut(temp[30]) ) ; 
			mux_2to1 bit_31_1( .dataA(dataA[31]), .dataB(dataA[30]), .Ctrl(dataB[0]), .dataOut(temp[31]) ) ; 
			
			mux_2to1 bit_0_2( .dataA(temp[0]), .dataB(1'b0), .Ctrl(dataB[1]), .dataOut(temp1[0]) ) ; 
			mux_2to1 bit_1_2( .dataA(temp[1]), .dataB(1'b0), .Ctrl(dataB[1]), .dataOut(temp1[1]) ) ; 
			mux_2to1 bit_2_2( .dataA(temp[2]), .dataB(temp[0]), .Ctrl(dataB[1]), .dataOut(temp1[2]) ) ; 
			mux_2to1 bit_3_2( .dataA(temp[3]), .dataB(temp[1]), .Ctrl(dataB[1]), .dataOut(temp1[3]) ) ; 
			mux_2to1 bit_4_2( .dataA(temp[4]), .dataB(temp[2]), .Ctrl(dataB[1]), .dataOut(temp1[4]) ) ; 
			mux_2to1 bit_5_2( .dataA(temp[5]), .dataB(temp[3]), .Ctrl(dataB[1]), .dataOut(temp1[5]) ) ; 
			mux_2to1 bit_6_2( .dataA(temp[6]), .dataB(temp[4]), .Ctrl(dataB[1]), .dataOut(temp1[6]) ) ; 
			mux_2to1 bit_7_2( .dataA(temp[7]), .dataB(temp[5]), .Ctrl(dataB[1]), .dataOut(temp1[7]) ) ; 
			mux_2to1 bit_8_2( .dataA(temp[8]), .dataB(temp[6]), .Ctrl(dataB[1]), .dataOut(temp1[8]) ) ; 
			mux_2to1 bit_9_2( .dataA(temp[9]), .dataB(temp[7]), .Ctrl(dataB[1]), .dataOut(temp1[9]) ) ; 
			mux_2to1 bit_10_2( .dataA(temp[10]), .dataB(temp[8]), .Ctrl(dataB[1]), .dataOut(temp1[10]) ) ; 
			mux_2to1 bit_11_2( .dataA(temp[11]), .dataB(temp[9]), .Ctrl(dataB[1]), .dataOut(temp1[11]) ) ; 
			mux_2to1 bit_12_2( .dataA(temp[12]), .dataB(temp[10]), .Ctrl(dataB[1]), .dataOut(temp1[12]) ) ; 
			mux_2to1 bit_13_2( .dataA(temp[13]), .dataB(temp[11]), .Ctrl(dataB[1]), .dataOut(temp1[13]) ) ; 
			mux_2to1 bit_14_2( .dataA(temp[14]), .dataB(temp[12]), .Ctrl(dataB[1]), .dataOut(temp1[14]) ) ; 
			mux_2to1 bit_15_2( .dataA(temp[15]), .dataB(temp[13]), .Ctrl(dataB[1]), .dataOut(temp1[15]) ) ; 
			mux_2to1 bit_16_2( .dataA(temp[16]), .dataB(temp[14]), .Ctrl(dataB[1]), .dataOut(temp1[16]) ) ; 
			mux_2to1 bit_17_2( .dataA(temp[17]), .dataB(temp[15]), .Ctrl(dataB[1]), .dataOut(temp1[17]) ) ; 
			mux_2to1 bit_18_2( .dataA(temp[18]), .dataB(temp[16]), .Ctrl(dataB[1]), .dataOut(temp1[18]) ) ; 
			mux_2to1 bit_19_2( .dataA(temp[19]), .dataB(temp[17]), .Ctrl(dataB[1]), .dataOut(temp1[19]) ) ; 
			mux_2to1 bit_20_2( .dataA(temp[20]), .dataB(temp[18]), .Ctrl(dataB[1]), .dataOut(temp1[20]) ) ; 
			mux_2to1 bit_21_2( .dataA(temp[21]), .dataB(temp[19]), .Ctrl(dataB[1]), .dataOut(temp1[21]) ) ; 
			mux_2to1 bit_22_2( .dataA(temp[22]), .dataB(temp[20]), .Ctrl(dataB[1]), .dataOut(temp1[22]) ) ; 
			mux_2to1 bit_23_2( .dataA(temp[23]), .dataB(temp[21]), .Ctrl(dataB[1]), .dataOut(temp1[23]) ) ; 
			mux_2to1 bit_24_2( .dataA(temp[24]), .dataB(temp[22]), .Ctrl(dataB[1]), .dataOut(temp1[24]) ) ; 
			mux_2to1 bit_25_2( .dataA(temp[25]), .dataB(temp[23]), .Ctrl(dataB[1]), .dataOut(temp1[25]) ) ; 
			mux_2to1 bit_26_2( .dataA(temp[26]), .dataB(temp[24]), .Ctrl(dataB[1]), .dataOut(temp1[26]) ) ; 
			mux_2to1 bit_27_2( .dataA(temp[27]), .dataB(temp[25]), .Ctrl(dataB[1]), .dataOut(temp1[27]) ) ; 
			mux_2to1 bit_28_2( .dataA(temp[28]), .dataB(temp[26]), .Ctrl(dataB[1]), .dataOut(temp1[28]) ) ; 
			mux_2to1 bit_29_2( .dataA(temp[29]), .dataB(temp[27]), .Ctrl(dataB[1]), .dataOut(temp1[29]) ) ; 
			mux_2to1 bit_30_2( .dataA(temp[30]), .dataB(temp[28]), .Ctrl(dataB[1]), .dataOut(temp1[30]) ) ; 
			mux_2to1 bit_31_2( .dataA(temp[31]), .dataB(temp[29]), .Ctrl(dataB[1]), .dataOut(temp1[31]) ) ; 
			
			mux_2to1 bit_0_3( .dataA(temp1[0]), .dataB(1'b0), .Ctrl(dataB[2]), .dataOut(temp2[0]) ) ; 
			mux_2to1 bit_1_3( .dataA(temp1[1]), .dataB(1'b0), .Ctrl(dataB[2]), .dataOut(temp2[1]) ) ; 
			mux_2to1 bit_2_3( .dataA(temp1[2]), .dataB(1'b0), .Ctrl(dataB[2]), .dataOut(temp2[2]) ) ; 
			mux_2to1 bit_3_3( .dataA(temp1[3]), .dataB(1'b0), .Ctrl(dataB[2]), .dataOut(temp2[3]) ) ; 
			mux_2to1 bit_4_3( .dataA(temp1[4]), .dataB(temp1[0]), .Ctrl(dataB[2]), .dataOut(temp2[4]) ) ; 
			mux_2to1 bit_5_3( .dataA(temp1[5]), .dataB(temp1[1]), .Ctrl(dataB[2]), .dataOut(temp2[5]) ) ; 
			mux_2to1 bit_6_3( .dataA(temp1[6]), .dataB(temp1[2]), .Ctrl(dataB[2]), .dataOut(temp2[6]) ) ; 
			mux_2to1 bit_7_3( .dataA(temp1[7]), .dataB(temp1[3]), .Ctrl(dataB[2]), .dataOut(temp2[7]) ) ; 
			mux_2to1 bit_8_3( .dataA(temp1[8]), .dataB(temp1[4]), .Ctrl(dataB[2]), .dataOut(temp2[8]) ) ; 
			mux_2to1 bit_9_3( .dataA(temp1[9]), .dataB(temp1[5]), .Ctrl(dataB[2]), .dataOut(temp2[9]) ) ; 
			mux_2to1 bit_10_3( .dataA(temp1[10]), .dataB(temp1[6]), .Ctrl(dataB[2]), .dataOut(temp2[10]) ) ; 
			mux_2to1 bit_11_3( .dataA(temp1[11]), .dataB(temp1[7]), .Ctrl(dataB[2]), .dataOut(temp2[11]) ) ; 
			mux_2to1 bit_12_3( .dataA(temp1[12]), .dataB(temp1[8]), .Ctrl(dataB[2]), .dataOut(temp2[12]) ) ; 
			mux_2to1 bit_13_3( .dataA(temp1[13]), .dataB(temp1[9]), .Ctrl(dataB[2]), .dataOut(temp2[13]) ) ; 
			mux_2to1 bit_14_3( .dataA(temp1[14]), .dataB(temp1[10]), .Ctrl(dataB[2]), .dataOut(temp2[14]) ) ; 
			mux_2to1 bit_15_3( .dataA(temp1[15]), .dataB(temp1[11]), .Ctrl(dataB[2]), .dataOut(temp2[15]) ) ; 
			mux_2to1 bit_16_3( .dataA(temp1[16]), .dataB(temp1[12]), .Ctrl(dataB[2]), .dataOut(temp2[16]) ) ; 
			mux_2to1 bit_17_3( .dataA(temp1[17]), .dataB(temp1[13]), .Ctrl(dataB[2]), .dataOut(temp2[17]) ) ; 
			mux_2to1 bit_18_3( .dataA(temp1[18]), .dataB(temp1[14]), .Ctrl(dataB[2]), .dataOut(temp2[18]) ) ; 
			mux_2to1 bit_19_3( .dataA(temp1[19]), .dataB(temp1[15]), .Ctrl(dataB[2]), .dataOut(temp2[19]) ) ; 
			mux_2to1 bit_20_3( .dataA(temp1[20]), .dataB(temp1[16]), .Ctrl(dataB[2]), .dataOut(temp2[20]) ) ; 
			mux_2to1 bit_21_3( .dataA(temp1[21]), .dataB(temp1[17]), .Ctrl(dataB[2]), .dataOut(temp2[21]) ) ; 
			mux_2to1 bit_22_3( .dataA(temp1[22]), .dataB(temp1[18]), .Ctrl(dataB[2]), .dataOut(temp2[22]) ) ; 
			mux_2to1 bit_23_3( .dataA(temp1[23]), .dataB(temp1[19]), .Ctrl(dataB[2]), .dataOut(temp2[23]) ) ; 
			mux_2to1 bit_24_3( .dataA(temp1[24]), .dataB(temp1[20]), .Ctrl(dataB[2]), .dataOut(temp2[24]) ) ; 
			mux_2to1 bit_25_3( .dataA(temp1[25]), .dataB(temp1[21]), .Ctrl(dataB[2]), .dataOut(temp2[25]) ) ; 
			mux_2to1 bit_26_3( .dataA(temp1[26]), .dataB(temp1[22]), .Ctrl(dataB[2]), .dataOut(temp2[26]) ) ; 
			mux_2to1 bit_27_3( .dataA(temp1[27]), .dataB(temp1[23]), .Ctrl(dataB[2]), .dataOut(temp2[27]) ) ; 
			mux_2to1 bit_28_3( .dataA(temp1[28]), .dataB(temp1[24]), .Ctrl(dataB[2]), .dataOut(temp2[28]) ) ; 
			mux_2to1 bit_29_3( .dataA(temp1[29]), .dataB(temp1[25]), .Ctrl(dataB[2]), .dataOut(temp2[29]) ) ; 
			mux_2to1 bit_30_3( .dataA(temp1[30]), .dataB(temp1[26]), .Ctrl(dataB[2]), .dataOut(temp2[30]) ) ; 
			mux_2to1 bit_31_3( .dataA(temp1[31]), .dataB(temp1[27]), .Ctrl(dataB[2]), .dataOut(temp2[31]) ) ; 
			
			mux_2to1 bit_0_4( .dataA(temp2[0]), .dataB(1'b0), .Ctrl(dataB[3]), .dataOut(temp3[0]) ) ;  
			mux_2to1 bit_1_4( .dataA(temp2[1]), .dataB(1'b0), .Ctrl(dataB[3]), .dataOut(temp3[1]) ) ; 
			mux_2to1 bit_2_4( .dataA(temp2[2]), .dataB(1'b0), .Ctrl(dataB[3]), .dataOut(temp3[2]) ) ; 
			mux_2to1 bit_3_4( .dataA(temp2[3]), .dataB(1'b0), .Ctrl(dataB[3]), .dataOut(temp3[3]) ) ; 
			mux_2to1 bit_4_4( .dataA(temp2[4]), .dataB(1'b0), .Ctrl(dataB[3]), .dataOut(temp3[4]) ) ; 
			mux_2to1 bit_5_4( .dataA(temp2[5]), .dataB(1'b0), .Ctrl(dataB[3]), .dataOut(temp3[5]) ) ; 
			mux_2to1 bit_6_4( .dataA(temp2[6]), .dataB(1'b0), .Ctrl(dataB[3]), .dataOut(temp3[6]) ) ; 
			mux_2to1 bit_7_4( .dataA(temp2[7]), .dataB(1'b0), .Ctrl(dataB[3]), .dataOut(temp3[7]) ) ; 
			mux_2to1 bit_8_4( .dataA(temp2[8]), .dataB(temp2[0]), .Ctrl(dataB[3]), .dataOut(temp3[8]) ) ; 
			mux_2to1 bit_9_4( .dataA(temp2[9]), .dataB(temp2[1]), .Ctrl(dataB[3]), .dataOut(temp3[9]) ) ; 
			mux_2to1 bit_10_4( .dataA(temp2[10]), .dataB(temp2[2]), .Ctrl(dataB[3]), .dataOut(temp3[10]) ) ; 
			mux_2to1 bit_11_4( .dataA(temp2[11]), .dataB(temp2[3]), .Ctrl(dataB[3]), .dataOut(temp3[11]) ) ; 
			mux_2to1 bit_12_4( .dataA(temp2[12]), .dataB(temp2[4]), .Ctrl(dataB[3]), .dataOut(temp3[12]) ) ; 
			mux_2to1 bit_13_4( .dataA(temp2[13]), .dataB(temp2[5]), .Ctrl(dataB[3]), .dataOut(temp3[13]) ) ; 
			mux_2to1 bit_14_4( .dataA(temp2[14]), .dataB(temp2[6]), .Ctrl(dataB[3]), .dataOut(temp3[14]) ) ; 
			mux_2to1 bit_15_4( .dataA(temp2[15]), .dataB(temp2[7]), .Ctrl(dataB[3]), .dataOut(temp3[15]) ) ; 
			mux_2to1 bit_16_4( .dataA(temp2[16]), .dataB(temp2[8]), .Ctrl(dataB[3]), .dataOut(temp3[16]) ) ; 
			mux_2to1 bit_17_4( .dataA(temp2[17]), .dataB(temp2[9]), .Ctrl(dataB[3]), .dataOut(temp3[17]) ) ;  
			mux_2to1 bit_18_4( .dataA(temp2[18]), .dataB(temp2[10]), .Ctrl(dataB[3]), .dataOut(temp3[18]) ) ;  
			mux_2to1 bit_19_4( .dataA(temp2[19]), .dataB(temp2[11]), .Ctrl(dataB[3]), .dataOut(temp3[19]) ) ; 
			mux_2to1 bit_20_4( .dataA(temp2[20]), .dataB(temp2[12]), .Ctrl(dataB[3]), .dataOut(temp3[20]) ) ;  
			mux_2to1 bit_21_4( .dataA(temp2[21]), .dataB(temp2[13]), .Ctrl(dataB[3]), .dataOut(temp3[21]) ) ;  
			mux_2to1 bit_22_4( .dataA(temp2[22]), .dataB(temp2[14]), .Ctrl(dataB[3]), .dataOut(temp3[22]) ) ;  
			mux_2to1 bit_23_4( .dataA(temp2[23]), .dataB(temp2[15]), .Ctrl(dataB[3]), .dataOut(temp3[23]) ) ;  
			mux_2to1 bit_24_4( .dataA(temp2[24]), .dataB(temp2[16]), .Ctrl(dataB[3]), .dataOut(temp3[24]) ) ;  
			mux_2to1 bit_25_4( .dataA(temp2[25]), .dataB(temp2[17]), .Ctrl(dataB[3]), .dataOut(temp3[25]) ) ;  
			mux_2to1 bit_26_4( .dataA(temp2[26]), .dataB(temp2[18]), .Ctrl(dataB[3]), .dataOut(temp3[26]) ) ;  
			mux_2to1 bit_27_4( .dataA(temp2[27]), .dataB(temp2[19]), .Ctrl(dataB[3]), .dataOut(temp3[27]) ) ;  
			mux_2to1 bit_28_4( .dataA(temp2[28]), .dataB(temp2[20]), .Ctrl(dataB[3]), .dataOut(temp3[28]) ) ;  
			mux_2to1 bit_29_4( .dataA(temp2[29]), .dataB(temp2[21]), .Ctrl(dataB[3]), .dataOut(temp3[29]) ) ;  
			mux_2to1 bit_30_4( .dataA(temp2[30]), .dataB(temp2[22]), .Ctrl(dataB[3]), .dataOut(temp3[30]) ) ;  
			mux_2to1 bit_31_4( .dataA(temp2[31]), .dataB(temp2[23]), .Ctrl(dataB[3]), .dataOut(temp3[31]) ) ;  
			
			mux_2to1 bit_0_5( .dataA(temp3[0]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[0]) ) ;  
			mux_2to1 bit_1_5( .dataA(temp3[1]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[1]) ) ; 
			mux_2to1 bit_2_5( .dataA(temp3[2]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[2]) ) ;  
			mux_2to1 bit_3_5( .dataA(temp3[3]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[3]) ) ;  
			mux_2to1 bit_4_5( .dataA(temp3[4]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[4]) ) ;  
			mux_2to1 bit_5_5( .dataA(temp3[5]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[5]) ) ;  
			mux_2to1 bit_6_5( .dataA(temp3[6]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[6]) ) ;  
			mux_2to1 bit_7_5( .dataA(temp3[7]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[7]) ) ;  
			mux_2to1 bit_8_5( .dataA(temp3[8]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[8]) ) ;  
			mux_2to1 bit_9_5( .dataA(temp3[9]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[9]) ) ;  
			mux_2to1 bit_10_5( .dataA(temp3[10]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[10]) ) ;  
			mux_2to1 bit_11_5( .dataA(temp3[11]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[11]) ) ;  
			mux_2to1 bit_12_5( .dataA(temp3[12]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[12]) ) ; 
			mux_2to1 bit_13_5( .dataA(temp3[13]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[13]) ) ;  
			mux_2to1 bit_14_5( .dataA(temp3[14]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[14]) ) ;  
			mux_2to1 bit_15_5( .dataA(temp3[15]), .dataB(1'b0), .Ctrl(dataB[4]), .dataOut(temp4[15]) ) ;  
			mux_2to1 bit_16_5( .dataA(temp3[16]), .dataB(temp3[0]), .Ctrl(dataB[4]), .dataOut(temp4[16]) ) ;  
			mux_2to1 bit_17_5( .dataA(temp3[17]), .dataB(temp3[1]), .Ctrl(dataB[4]), .dataOut(temp4[17]) ) ;  
			mux_2to1 bit_18_5( .dataA(temp3[18]), .dataB(temp3[2]), .Ctrl(dataB[4]), .dataOut(temp4[18]) ) ;  
			mux_2to1 bit_19_5( .dataA(temp3[19]), .dataB(temp3[3]), .Ctrl(dataB[4]), .dataOut(temp4[19]) ) ;  
			mux_2to1 bit_20_5( .dataA(temp3[20]), .dataB(temp3[4]), .Ctrl(dataB[4]), .dataOut(temp4[20]) ) ;  
			mux_2to1 bit_21_5( .dataA(temp3[21]), .dataB(temp3[5]), .Ctrl(dataB[4]), .dataOut(temp4[21]) ) ;  
			mux_2to1 bit_22_5( .dataA(temp3[22]), .dataB(temp3[6]), .Ctrl(dataB[4]), .dataOut(temp4[22]) ) ;  
			mux_2to1 bit_23_5( .dataA(temp3[23]), .dataB(temp3[7]), .Ctrl(dataB[4]), .dataOut(temp4[23]) ) ;  
			mux_2to1 bit_24_5( .dataA(temp3[24]), .dataB(temp3[8]), .Ctrl(dataB[4]), .dataOut(temp4[24]) ) ;  
			mux_2to1 bit_25_5( .dataA(temp3[25]), .dataB(temp3[9]), .Ctrl(dataB[4]), .dataOut(temp4[25]) ) ;  
			mux_2to1 bit_26_5( .dataA(temp3[26]), .dataB(temp3[10]), .Ctrl(dataB[4]), .dataOut(temp4[26]) ) ;  
			mux_2to1 bit_27_5( .dataA(temp3[27]), .dataB(temp3[11]), .Ctrl(dataB[4]), .dataOut(temp4[27]) ) ;  
			mux_2to1 bit_28_5( .dataA(temp3[28]), .dataB(temp3[12]), .Ctrl(dataB[4]), .dataOut(temp4[28]) ) ;  
			mux_2to1 bit_29_5( .dataA(temp3[29]), .dataB(temp3[13]), .Ctrl(dataB[4]), .dataOut(temp4[29]) ) ;  
			mux_2to1 bit_30_5( .dataA(temp3[30]), .dataB(temp3[14]), .Ctrl(dataB[4]), .dataOut(temp4[30]) ) ;  
			mux_2to1 bit_31_5( .dataA(temp3[31]), .dataB(temp3[15]), .Ctrl(dataB[4]), .dataOut(temp4[31]) ) ;  
			
			assign dataOut = (Signal == SLL) ? ( (dataB[4:0] = 5'd32) ?  32'b0 : temp4 ) : 32'b0 ;
	
/*
移位器運算
*/


endmodule