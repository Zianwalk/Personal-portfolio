
module Three2_bit_ALU( dataA, dataB, Signal, dataOut, zero ) ;

input  zero ;
input[31:0] dataA ;
input[31:0] dataB ;
input[2:0]  Signal ;
output[31:0] dataOut ;


parameter AND = 3'b0 ;
parameter OR  = 3'b001 ;
parameter ADD = 3'b010 ;
parameter SUB = 3'b110 ;
parameter SLT = 3'b111 ;

wire set ;
wire slt_set ;
wire[31:0] carry ;

assign slt_set = ( dataA < dataB ) ? 1 : 0 ;
assign set = ( Signal == SUB ) ? 1 : 0 ;
assign zero = ( dataOut == 32'b0 ) ? 1 : 0 ;

one_bit_ALU		ALU_0( .dataA(dataA[0]), .dataB(dataB[0]), .carryIn(set), .Signal(Signal), .dataOut(dataOut[0]), .carryOut(carry[0]), .less(slt_set) ) ;
one_bit_ALU  	ALU_1( .dataA(dataA[1]), .dataB(dataB[1]), .carryIn(carry[0]), .Signal(Signal), .dataOut(dataOut[1]), .carryOut(carry[1]), .less(1'b0) ) ;
one_bit_ALU		ALU_2( .dataA(dataA[2]), .dataB(dataB[2]), .carryIn(carry[1]), .Signal(Signal), .dataOut(dataOut[2]), .carryOut(carry[2]), .less(1'b0) );
one_bit_ALU 	ALU_3( .dataA(dataA[3]), .dataB(dataB[3]), .carryIn(carry[2]), .Signal(Signal), .dataOut(dataOut[3]), .carryOut(carry[3]), .less(1'b0) ) ;
one_bit_ALU 	ALU_4( .dataA(dataA[4]), .dataB(dataB[4]), .carryIn(carry[3]), .Signal(Signal), .dataOut(dataOut[4]), .carryOut(carry[4]), .less(1'b0) ) ;
one_bit_ALU 	ALU_5( .dataA(dataA[5]), .dataB(dataB[5]), .carryIn(carry[4]), .Signal(Signal), .dataOut(dataOut[5]), .carryOut(carry[5]), .less(1'b0) ) ;
one_bit_ALU		ALU_6( .dataA(dataA[6]), .dataB(dataB[6]), .carryIn(carry[5]), .Signal(Signal), .dataOut(dataOut[6]), .carryOut(carry[6]), .less(1'b0) ) ;
one_bit_ALU		ALU_7( .dataA(dataA[7]), .dataB(dataB[7]), .carryIn(carry[6]), .Signal(Signal), .dataOut(dataOut[7]), .carryOut(carry[7]), .less(1'b0) ) ;
one_bit_ALU		ALU_8( .dataA(dataA[8]), .dataB(dataB[8]), .carryIn(carry[7]), .Signal(Signal), .dataOut(dataOut[8]), .carryOut(carry[8]), .less(1'b0) ) ;
one_bit_ALU		ALU_9( .dataA(dataA[9]), .dataB(dataB[9]), .carryIn(carry[8]), .Signal(Signal), .dataOut(dataOut[9]), .carryOut(carry[9]), .less(1'b0) ) ;
one_bit_ALU		ALU_10( .dataA(dataA[10]), .dataB(dataB[10]), .carryIn(carry[9]), .Signal(Signal), .dataOut(dataOut[10]), .carryOut(carry[10]), .less(1'b0) ) ;
one_bit_ALU		ALU_11( .dataA(dataA[11]), .dataB(dataB[11]), .carryIn(carry[10]), .Signal(Signal), .dataOut(dataOut[11]), .carryOut(carry[11]), .less(1'b0) ) ;
one_bit_ALU		ALU_12( .dataA(dataA[12]), .dataB(dataB[12]), .carryIn(carry[11]), .Signal(Signal), .dataOut(dataOut[12]), .carryOut(carry[12]), .less(1'b0) ) ;
one_bit_ALU		ALU_13( .dataA(dataA[13]), .dataB(dataB[13]), .carryIn(carry[12]), .Signal(Signal), .dataOut(dataOut[13]), .carryOut(carry[13]), .less(1'b0) ) ;
one_bit_ALU		ALU_14( .dataA(dataA[14]), .dataB(dataB[14]), .carryIn(carry[13]), .Signal(Signal), .dataOut(dataOut[14]), .carryOut(carry[14]), .less(1'b0) ) ;
one_bit_ALU		ALU_15( .dataA(dataA[15]), .dataB(dataB[15]), .carryIn(carry[14]), .Signal(Signal), .dataOut(dataOut[15]), .carryOut(carry[15]), .less(1'b0) ) ;
one_bit_ALU		ALU_16( .dataA(dataA[16]), .dataB(dataB[16]), .carryIn(carry[15]), .Signal(Signal), .dataOut(dataOut[16]), .carryOut(carry[16]), .less(1'b0) ) ;
one_bit_ALU		ALU_17( .dataA(dataA[17]), .dataB(dataB[17]), .carryIn(carry[16]), .Signal(Signal), .dataOut(dataOut[17]), .carryOut(carry[17]), .less(1'b0) ) ;
one_bit_ALU		ALU_18( .dataA(dataA[18]), .dataB(dataB[18]), .carryIn(carry[17]), .Signal(Signal), .dataOut(dataOut[18]), .carryOut(carry[18]), .less(1'b0) ) ;
one_bit_ALU		ALU_19( .dataA(dataA[19]), .dataB(dataB[19]), .carryIn(carry[18]), .Signal(Signal), .dataOut(dataOut[19]), .carryOut(carry[19]), .less(1'b0) ) ;
one_bit_ALU		ALU_20( .dataA(dataA[20]), .dataB(dataB[20]), .carryIn(carry[19]), .Signal(Signal), .dataOut(dataOut[20]), .carryOut(carry[20]), .less(1'b0) ) ;
one_bit_ALU		ALU_21( .dataA(dataA[21]), .dataB(dataB[21]), .carryIn(carry[20]), .Signal(Signal), .dataOut(dataOut[21]), .carryOut(carry[21]), .less(1'b0) ) ;
one_bit_ALU		ALU_22( .dataA(dataA[22]), .dataB(dataB[22]), .carryIn(carry[21]), .Signal(Signal), .dataOut(dataOut[22]), .carryOut(carry[22]), .less(1'b0) ) ;
one_bit_ALU		ALU_23( .dataA(dataA[23]), .dataB(dataB[23]), .carryIn(carry[22]), .Signal(Signal), .dataOut(dataOut[23]), .carryOut(carry[23]), .less(1'b0) ) ;
one_bit_ALU		ALU_24( .dataA(dataA[24]), .dataB(dataB[24]), .carryIn(carry[23]), .Signal(Signal), .dataOut(dataOut[24]), .carryOut(carry[24]), .less(1'b0) ) ;
one_bit_ALU		ALU_25( .dataA(dataA[25]), .dataB(dataB[25]), .carryIn(carry[24]), .Signal(Signal), .dataOut(dataOut[25]), .carryOut(carry[25]), .less(1'b0) ) ;
one_bit_ALU		ALU_26( .dataA(dataA[26]), .dataB(dataB[26]), .carryIn(carry[25]), .Signal(Signal), .dataOut(dataOut[26]), .carryOut(carry[26]), .less(1'b0) ) ;
one_bit_ALU		ALU_27( .dataA(dataA[27]), .dataB(dataB[27]), .carryIn(carry[26]), .Signal(Signal), .dataOut(dataOut[27]), .carryOut(carry[27]), .less(1'b0) ) ;
one_bit_ALU		ALU_28( .dataA(dataA[28]), .dataB(dataB[28]), .carryIn(carry[27]), .Signal(Signal), .dataOut(dataOut[28]), .carryOut(carry[28]), .less(1'b0) ) ;
one_bit_ALU		ALU_29( .dataA(dataA[29]), .dataB(dataB[29]), .carryIn(carry[28]), .Signal(Signal), .dataOut(dataOut[29]), .carryOut(carry[29]), .less(1'b0) ) ;
one_bit_ALU		ALU_30( .dataA(dataA[30]), .dataB(dataB[30]), .carryIn(carry[29]), .Signal(Signal), .dataOut(dataOut[30]), .carryOut(carry[30]), .less(1'b0) ) ;
one_bit_ALU		ALU_31( .dataA(dataA[31]), .dataB(dataB[31]), .carryIn(carry[30]), .Signal(Signal), .dataOut(dataOut[31]), .carryOut(carry[31]), .less(1'b0) ) ;

endmodule