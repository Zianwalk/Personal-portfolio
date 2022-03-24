`timescale 1ns/1ns

module one_bit_ALU( dataA, dataB, carryIn, Signal, dataOut, carryOut, reset, less ) ;
input reset ;   // �Yreset��1�A�h�k�s
input dataA ;   // A��J�Ybit
input dataB ; 	// B��J�Ybit
input carryIn ; // �W��ALU�Ƕi�Ӫ�carryin
input [5:0] Signal ; // �P�_�n���ƻ�B��
output dataOut ;  	 // ��X
output carryOut ;	 // carryOut
input less ;

// Signal 6-bits
// and : 36
// or  : 37
// add : 32
// sub : 34
// slt : 42

wire w1,w2,w3 ;  
wire tempB ;
wire temp ;
assign temp = 1'b1 ;
wire andOut, orOut ;
wire sum, carry ;
wire s1,s2,s3 ;
wire diff, dcarry ;
wire less ;

parameter AND = 6'b100100 ; //[5],[2]
parameter OR  = 6'b100101 ;//[5],[2],[0]
parameter ADD = 6'b100000 ;//[5]
parameter SUB = 6'b100010 ;//[5],[1]
parameter SLT = 6'b101010 ;//[5],[3],[1]

/*�w�q�U�ذT��*/

//assign dataOut = (reset) ? 1'b0 : dataOut ;

/*�Y�Oreset�T���N�k�s*/

// AND and OR gate below
and ( andOut, dataA, dataB ) ;
or ( orOut, dataA, dataB ) ;

// adder
xor ( w1, dataA, dataB ) ;
xor ( sum, w1, carryIn ) ;
// adder carry //
and ( w2, orOut, carryIn ) ;
or ( carry, w2, andOut ) ;

// subber
xor ( tempB, 1'b1, dataB ) ; // tempB = b xor 1
xor ( s1, dataA, tempB ) ;	 // s1 = a xor ( b xor 1 )
xor ( diff, s1, carryIn ) ;  // sum = ( a xor ( b xor 1 )) xor cin
and ( s2, s1, carryIn ) ;	 // s2 = ( a xor ( b xor 1 )) and cin
and ( s3, dataA, tempB ) ;   // s3 = a and ( b xor 1 )
or ( dcarry, s2, s3 ) ;		 // cout = s2 

// less


assign carryOut = Signal[1] ? ((Signal == SUB) ? dcarry : 1'b0) : ((Signal == ADD ) ? carry : 1'b0 ) ;
assign dataOut = Signal[2] ? (Signal[0] ? orOut : andOut) : (Signal[1] ? (Signal[3] ? less : diff ) : sum ) ;

endmodule

/*case�Ω�T���B�z�A�ھڶǶi�Ӫ�Signal�Ӱ����P���B��A�A��i�Ȧs��*/
