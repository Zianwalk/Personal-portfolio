

module one_bit_ALU( dataA, dataB, carryIn, Signal, dataOut, carryOut, less ) ;
input dataA ;   // A輸入某bit
input dataB ; 	// B輸入某bit
input carryIn ; // 上個ALU傳進來的carryin
input [2:0] Signal ; // 判斷要做甚麼運算
output dataOut ;  	 // 輸出
output carryOut ;	 // carryOut
input less ;

wire w1,w2,w3 ;  
wire tempB ;
wire temp ;
assign temp = 1'b1 ;
wire andOut, orOut ;
wire sum, carry ;
wire s1,s2,s3 ;
wire diff, dcarry ;


parameter AND = 3'b000 ;
parameter OR  = 3'b001 ;
parameter ADD = 3'b010 ;
parameter SUB = 3'b110 ;
parameter SLT = 3'b111 ;

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

assign carryOut = Signal[2] ? ((Signal == SUB) ? dcarry : 1'b0) : ((Signal == ADD ) ? carry : 1'b0 ) ;
assign dataOut = Signal[1] ? (Signal[2] ? (Signal[0] ? less : diff ) : sum ) : (Signal[0] ? orOut : andOut) ;

endmodule


