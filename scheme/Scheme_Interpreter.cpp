# include <iostream>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <iomanip>
# include <sstream>

using namespace std ;

struct Token {

  string token ;
  string type ;
  int line ;
  int column ;

}; // Token

struct Node {
  
  string type ;
  string token ;
  Node * left ;
  Node * right ;
  
}; // Node

struct SQ_Token {
  vector<Token> stack ;
}; // SQ_Token

struct Vari {
  string symbol ;
  vector<Token> stack ;
}; // Vari

struct Table {
  vector<string> symbol ;
}; // Table

int gline = 0 ;
int gcolumn = 0 ;

typedef Node * NodePtr ;

class Scanner {

  public :

  void Set_Type( char * str, int start, int end, string &type ) { // string-type undefine //
    
    int count = 0 ;
    bool dot = false ;
    bool num = false ;
    bool symbol = false ;
    bool letter = false ;

    for ( int i = start ; i <= end ; i++ ) {

      if ( !dot && str[i] == '.' ) dot = true ;
      else if ( str[i] == '+' || str[i] == '-' ) count = count + 1;
      else if ( '0' <= str[i] && str[i] <= '9' ) num = true ;
      else if ( 'A' <= str[i] && str[i] <= 'Z' ) letter = true ;
      else if ( 'a' <= str[i] && str[i] <= 'z' ) letter = true ;
      else symbol = true ;

    } // for ()

    if ( symbol || letter ) type = "SYMBOL" ;
    else if ( !dot && !letter && !symbol && num ) type = "INT" ;
    else if ( !letter && !symbol && num && dot ) type = "FLOAT" ;
    else type = "SYMBOL" ;
    
    if ( type == "INT" || type == "FLOAT" )
      if ( count > 1 ) type = "SYMBOL" ;

  } // Set_Type()

  void Cut_String_Type( char * str, int start, int &end, string &type ) {

    int mark = 0 ;

    for ( int i = start + 1 ; i < strlen( str ) ; i++ ) {
      if ( str[i] == '\"' && str[i - 1] != '\\' ) {
        mark = i ;
        i = strlen( str ) ;
      } // if ()
    } // for()

    if ( mark != 0 ) {
      end = mark ;
      type = "STRING" ;
    } // if ()
        
    else {
      end = strlen( str ) ;
      type = "NO-CLOSING-QUOTE" ;
    } // else
    /*
    cout << "start = " << start << " mark = " << mark << " String = " ;
    for ( int i = start ; i <= mark ; i++ ) cout << str[i] ;
    cout << endl ;
    */
  } // Cut_String_Type()

  void Cut_String_To_Token( char * str, int start, int &end, string &type ) {

    if ( strlen( str ) >= 2 && str[start] == '(' && str[start+1] == ')' ) {
      type = "NIL" ;
      end = start + 1 ;
      return ;
    } // if()

    if ( str[start] == '(' ) {
      end = start ;
      type = "LEFT-PAREN" ;
      return ;
    } // if()

    if ( str[start] == ')' ) {
      end = start ;
      type = "RIGHT-PAREN" ;
      return ;
    } // if()

    if ( str[start] == '\'' ) {
      end = start ;
      type = "QUOTE" ;
      return ;
    } // if()

    if ( str[start] == ';' ) {
      end = start ;
      type = "COMMENT-START" ;
      return ;
    } // if()

    if ( str[start] == '\0' ) {
      end = start + 1 ;
      type = "SPACE" ;
      return ;
    } // if()

    if ( str[start] == '\r' ) {
      end = start + 1 ;
      type = "SPACE" ;
      return ;
    } // if()

    if ( str[start] == '\t' ) {
      end = start + 1 ;
      type = "SPACE" ;
      return ;
    } // if()

    if ( str[start] == '\n' ) {
      end = start + 1 ;
      type = "SPACE" ;
      return ;
    } // if()


    for ( int i = start ; i < strlen( str ) ; i++ ) {

      if ( str[i] == ';' ) {
        if ( i > start ) end = i - 1 ;
        i = strlen( str ) ;
      } // if()

      else if ( str[i] == '\"' || str[i] == '\'' ) {
        if ( i > start ) end = i - 1 ;
        i = strlen( str ) ;
      } // else if ()

      else if ( str[i] == '(' || str[i] == ')' ) {
        if ( i > start ) end = i - 1 ;
        i = strlen( str ) ;
      } // else if ()

      else if ( str[i] == '\t' || str[i] == '\n' || str[i] == ' ' ) {
        if ( i > start ) end = i - 1 ;
        i = strlen( str ) ;
      } // else if ()

      else end = i ;
    
    } // for()

    Set_Type( str, start, end, type ) ;

    if ( str[start] == '"' )
      Cut_String_Type( str, start, end, type ) ;


  } // Cut_String_To_Token()


  void Add_To_TempStack( string token, string type, vector<Token> &mTempStack, int line, int start ) {

    Token temp ;
    temp.token = token ;
    temp.type = type ;
    temp.line = line ;
    temp.column = start ;
    mTempStack.push_back( temp ) ;

  } // Add_To_TempStack()


  void String_To_Token( char * str, vector<Token> &mTempStack, int line_count ) {


    int start = 0 ;
    int end = 0 ;

    string token, type ;
    bool first_token = true ;
    bool command = true ;
    bool comment = false ;
    int size = strlen( str ) ;

    while ( start < size && !comment && command ) {

      for ( int i = start ; i < size ; i++ ) {
        if ( str[i] == ' ' ) start = start + 1 ;
        else i = size ; // equal to break //
      } // for()

      Cut_String_To_Token( str, start, end, type ) ;

      token = "" ;
      for ( int i = start ; i <= end ; i++ ) {
        token.push_back( str[i] ) ;
      } // for()

      if ( token == "." ) type = "DOT" ;
      else if ( token == "t" ) type = "T" ;
      else if ( token == "#t" ) type = "T" ;
      else if ( token == "#f" ) type = "NIL" ;
      else if ( token == "nil" ) type = "NIL" ;
      else ;

      
      if ( token == ";" ) command = false ;

      if ( command && type != "COMMENT-START" && type != "SPACE" )
        Add_To_TempStack( token, type, mTempStack, line_count, start ) ;
      if ( type == "COMMENT-START" ) {
        Add_To_TempStack( token, type, mTempStack, line_count, start ) ;
        comment = true ;
      } // if()
      /*
      cout << "Token = " << token << endl ;
      cout << "line = " << line_count << " start = " << start << " end = " << end ;
      cout << " type = " << type  << endl << endl ;
      */
      start = end + 1 ;
      first_token = false ;

    } // while()


  } // String_To_Token()


}; // Scanner








class Parser {

  public :
  int mCount ;
  int mdot_at ;
  bool mCons_Symbol ;
  bool Is_Sexp() ;
  bool meof, mdot, mtop ;
  string merror_type ;
  
  vector<Table> mTable ;
  vector<Vari> mDifine ;
  vector<Vari> mDifine_string ;
  vector<Token> mNextLine ;
  vector<Token> mTempStack ;
  vector<Token> mTokenStack ;
  
  void Peek_mTempStack( int i, string &type ) {

    if ( i < mTempStack.size() ) type = mTempStack.at( i ).type ;
    else type = "null" ;

  } // Peek_mTempStack()
  
  bool Is_Space( char * str ) {

    if ( strcmp( str, "" ) == 0 ) return true ;
    else {
      bool ans = true ;
      for ( int i = 0 ; i < strlen( str ) ; i++ )
        if ( str[i] != ' ' && str[i] != '\t' ) ans = false ;
      return ans ;
    } // else

  } // Is_Space()
  
  void Match_What( int count ) {
    
    for ( int i = 0 ; i < mTempStack.size() ; i++ ) {
      
      if ( i == count ) {
        cout << " >" ;
        cout << mTempStack.at( i ).token ;
        cout << "<  " ;
      } // if()
          
      else cout << mTempStack.at( i ).token << " " ;
    } // for()
        
    cout << endl ;
  } // Match_What()

  void Fill_TempStack_To_Continue_Match_Syntax() {

    Scanner scan ;

    int before, after ;
    bool check = true ;
    char * str = new char[1024] ;
    
    before = mTempStack.size() ;
    /*
    cout << endl << "************* Fill_TempStack_To_Continue_Match_Syntax *************" << endl ;
    cout << "Current Token String : " ;
    for ( int i = 0 ; i < mTempStack.size() ; i++ )
      cout << mTempStack.at( i ).token << " " ;
    cout << endl ;

    cout << endl << "************************** Get New Token **************************" << endl ;
    */
    while ( check && !meof ) {
      cin.getline( str, 1000 ) ;
      mCount = mCount + 1 ;
      check = Is_Space( str ) ;
      if ( cin.eof() ) meof = true ;
      if ( check && meof ) mCount = mCount - 1 ;
      // cout << check << "str = '" << str << "'" << endl ;
    } // while ()
    
    if ( !check ) scan.String_To_Token( str, mTempStack, mCount ) ;
    /*
    cout << "New Token String : " ;
    for ( int i = 0 ; i < mTempStack.size() ; i++ )
      cout << mTempStack.at( i ).token << " " ;
    cout << endl ;
    cout << endl << "********************** End Of Get New Token ***********************" << endl ;
    */
    after = mTempStack.size() ;
    
    
    if ( mTempStack.at( after - 1 ).token == ";" )
      mTempStack.erase( mTempStack.end() ) ;
  
    after = mTempStack.size() ;
    if ( !meof && after == before ) Fill_TempStack_To_Continue_Match_Syntax() ;
    

  } // Fill_TempStack_To_Continue_Match_Syntax()
  
  
  bool Is_ATOM( vector<Token> temp ) {

    string type ;
    int count = 0 ;
    type = temp.at( count ).type ;

    if ( temp.size() > 2 ) return false ;
    
    
    else if ( type == "SYMBOL" || type == "INT" || type == "FLOAT"
              || type == "STRING" || type == "NIL" || type == "T" ) {
      return true ;
    } // else if()

    else if ( type == "LEFT-PAREN" && temp.size() == 2 ) {

      count = count + 1 ;
      type = mTempStack.at( count ).type ;
      if ( type == "RIGHT-PAREN" ) return true ;
      else return false ;

    } // else if ()

    else return false ;

  } // Is_ATOM()
  
  
  bool Is_ATOM( int &count ) {

    string type ;
    type = mTempStack.at( count ).type ;

    if ( type == "SYMBOL" || type == "INT" || type == "FLOAT"
         || type == "STRING" || type == "NIL" || type == "T" ) {
      return true ;
    } // if()

    else if ( type == "LEFT-PAREN" ) {
      
      count = count + 1 ;
      if ( count >= mTempStack.size() ) Fill_TempStack_To_Continue_Match_Syntax() ;
      if ( meof && count >= mTempStack.size() ) return true ;
      
      type = mTempStack.at( count ).type ;
      if ( type == "RIGHT-PAREN" ) return true ;
      else {
        count = count - 1 ;
        return false ;
      } // else
    } // else if ()

    else return false ;

  } // Is_ATOM()

  bool Is_Sexp( int &count ) {

    string type ;
    bool match ;
    Token token = mTempStack.at( count ) ;
    // cout << endl << "Enter Function : Is_Sexp." << endl << endl ;


    if ( Is_ATOM( count ) ) {
      // cout << "Enter Function : Is_Sexp and Match <S-exp> ::= <ATOM>." << endl ;
      // Match_What( count ) ;
      return true ;
    } // if() // <ATOM>  ::= SYMBOL | INT | FLOAT | STRING | NIL | T | LEFT-PAREN RIGHT-PAREN //
    
    else if ( token.type == "QUOTE" ) {

      // cout << "Enter Function : Is_Sexp and Match <S-exp> ::= QUOTE <S-exp> ." << endl ;

      count = count + 1 ;
      if ( count >= mTempStack.size() ) Fill_TempStack_To_Continue_Match_Syntax() ;
      if ( meof && count >= mTempStack.size() ) return false ;
      // Match_What( count ) ;

      if ( Is_Sexp( count ) ) return true ;
      else return false ;

    } // else if () // <S-exp> ::= QUOTE <S-exp> //
    
    else if ( token.type == "LEFT-PAREN" ) {

      // cout << "Enter Function : Is_Sexp and Match <S-exp> ::= LEFT-PAREN." << endl ;

      count = count + 1 ;
      if ( count >= mTempStack.size() ) Fill_TempStack_To_Continue_Match_Syntax() ;
      if ( meof && count >= mTempStack.size() ) return false ;
      // cout << "Enter Function : Is_Sexp and Match <S-exp> ::= LEFT-PAREN <S-exp>." << endl ;
      // Match_What( count ) ;
      // cout << "************   ************   " << endl ;
      match = Is_Sexp( count ) ; // <S-exp> ::= LEFT-PAREN <S-exp> //
      // cout << "************   ************   ************   ************   " << endl ;

      if ( match ) {
        count = count + 1 ;
        if ( count >= mTempStack.size() ) Fill_TempStack_To_Continue_Match_Syntax() ;
        if ( meof && count >= mTempStack.size() ) return false ;

        if ( mTempStack.at( count ).type == "RIGHT-PAREN" ) {
          // cout << "Match <S-exp> ::= LEFT-PAREN <S-exp> RIGHT-PAREN." << endl ;
          return true ;
        } // else if ()

        // cout << "Match <S-exp> ::= LEFT-PAREN <S-exp> { <S-exp> }." << endl ;


        while ( match ) {
          match = Is_Sexp( count ) ;
          if ( match )  count = count + 1 ;
          if ( count >= mTempStack.size() ) Fill_TempStack_To_Continue_Match_Syntax() ;
          if ( meof && count >= mTempStack.size() ) return false ;
        } // while() // <S-exp> ::= LEFT-PAREN <S-exp> { <S-exp> } //


        // cout << "Match <S-exp> ::= LEFT-PAREN <S-exp> { <S-exp> } [ DOT ." << endl ;

        if ( mTempStack.at( count ).type == "DOT" ) {
            
          string front, back ;
          front = mTempStack.at( count - 1 ).token ;

          if ( front == "(" ) return false ;

          if ( mdot && front == ")" ) {
            int left = 0, right = 0 ;
            for ( int i = mdot_at ; i < count ; i++ ) {
              if ( mTempStack.at( i ).token == "(" ) left = left + 1 ;
              if ( mTempStack.at( i ).token == ")" ) right = right + 1 ;
            } // for ()
              
            if ( left == right ) {
              merror_type = "RIGHT" ;
              return false ;
            } // if ()
          } // if ()

          count = count + 1 ;
          if ( count >= mTempStack.size() ) Fill_TempStack_To_Continue_Match_Syntax() ;
          if ( meof && count >= mTempStack.size() ) return false ;
          back = mTempStack.at( count ).token ;

          if ( !mdot && front == ")" && back == "(" ) {
            mdot = true ;
            mdot_at = count - 1 ;
          } // if ()

          match = true ;
          
        } // if ()


        else if ( mTempStack.at( count ).type == "RIGHT-PAREN" ) {
          // cout << "Match <S-exp> ::= LEFT-PAREN <S-exp> { <S-exp> } RIGHT-PAREN." << endl ;
          return true ;
        } // else if ()
        else match = false ;

        // cout << "Match <S-exp> ::= LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN." << endl ;

        if ( mTempStack.at( count ).type == "RIGHT-PAREN" ) return false ;
        else if ( Is_Sexp( count ) ) {
          count = count + 1 ;
          if ( count >= mTempStack.size() ) Fill_TempStack_To_Continue_Match_Syntax() ;
          if ( meof && count >= mTempStack.size() ) return false ;
          if ( mTempStack.at( count ).type == "RIGHT-PAREN" ) return true ;
          else return false ;
        } // else if()
        else return false ;

      } // if ()

      else return false ;

    } // else if () // <S-exp> ::= LEFT-PAREN <S-exp> { <S-exp> } [ DOT <S-exp> ] RIGHT-PAREN //
        
    else return false ;
  
  
  } // Is_Sexp()

  bool Match_Syntax( int &num ) {

    // cout << "Enter Function : Match_Syntax." << endl ;
    // cout << endl ;

    bool match = true ;
    int size = mTempStack.size() ;
    // cout << "token string size = " << size << endl ;
    // cout << "Enter Function : Match_Syntax before do_while." << endl ;
    
    if ( Is_ATOM( num ) ) return true ;
    mdot_at = 0 ;
    mdot = false ;
    match = Is_Sexp( num ) ;
    return match ;
    
  } // Match_Syntax()

  void Print_String( string str ) {
      
    for ( int i = 0 ; i < str.size() ; i++ ) {
      if ( str[i] != '\\' ) cout << str[i] ;
      
      else if ( str.size() - i >= 2 ) {
        if ( str[i+1] == 'n' ) cout << endl ;
        else if ( str[i+1] == 't' ) cout << '\t' ;
        else if ( str[i+1] == '\\' ) cout << '\\' ;
        else if ( str[i+1] == '\"' ) cout << '"' ;
        else {
          i = i - 1 ;
          cout << '\\' ;
        } // else

        i = i + 1 ;
      } // else if()
          
    } // for()
        
  } // Print_String()
  
  void Token_Print( string token, string type ) {
    if ( type == "INT" )
      cout << atoi( token.c_str() ) ;
    else if ( type == "FLOAT" )
      cout << fixed << setprecision( 3 ) << atof( token.c_str() ) ;
    else if ( type == "STRING" ) Print_String( token ) ;
    else if ( token == "t" || token == "#t" ) cout << "#t" ;
    else if ( token == "()" || token == "#f" ) cout << "nil" ;
    else cout << token ;
  } // Token_Print()

  bool Is_Tree_Item( string token ) {
    
    bool ans = true ;

    if ( token == "" ) ans = false ;
    else if ( token == "." ) ans = false ;
    else if ( token == "(" ) ans = false ;
    else if ( token == ")" ) ans = false ;
    else if ( token == "()" ) ans = false ;
    else if ( token == "#f" ) ans = false ;
    else if ( token == "nil" ) ans = false ;
    else ;

    return ans ;

  } // Is_Tree_Item()


  void Pretty_Print( vector<Token> temp ) {
    
    string token, type ;
    string front, back ;
    int num = 0, left = 0, right = 0 ;
    
    vector<int> count ;
    int quote_num = 0, sum = 0 ;
    
    bool check = false ;
    
    // cout << "> " ;
    num = -2 ;


    if ( mTempStack.size() == 1 ) {
      Token_Print( mTempStack.at( 0 ).token, mTempStack.at( 0 ).type ) ;
      cout << endl << endl ;
      return ;
    } // if()
    
    for ( int i = 0 ; i < temp.size() ; i++ ) {
        
      type = temp.at( i ).type ;
      token = temp.at( i ).token ;
      if ( token == "'" ) quote_num = quote_num + 1 ;
      
      if ( token == "(" ) {
        left = left + 1 ;

        count.push_back( quote_num ) ;
        quote_num = 0 ;

        if ( i == 0 ) cout << "( " ;
        else if ( temp.at( i - 1 ).token == "(" ) cout << "( " ;
        else {
          if ( temp.at( i - 1 ).token != "(" )
            for ( int k = 0 ; k < num + 2 ; k++ )
              cout << " " ;
          cout << "( " ;
        } // else

        num = num + 2 ;
      } // if ()

      else if ( token == ")" ) {

        if ( num > 0 ) {
          right = right + 1 ;
          for ( int k = 0 ; k < num ; k++ )
            cout << " " ;
          Token_Print( token, type ) ;
          cout << endl ;
          num = num - 2 ;
        } // if ()

        while ( quote_num > 0 ) {
          for ( int k = 0 ; k < num ; k++ )
            cout << " " ;
          cout << ")" << endl ;
          num = num - 2 ;
          quote_num = quote_num - 1 ;
        } // while ()
            
        if ( right > 0 ) {
          int total = 0, bound ;
          bound = count.size() - right ;
          for ( int k = count.size() - 1 ; k >= bound ; k-- ) {
            total = total + count.at( k ) ;
            count.at( k ) = 0 ;
          } // for ()
              
          while ( total > 0 ) {
            for ( int k = 0 ; k < num ; k++ )
              cout << " " ;
            cout << ")" << endl ;
            num = num - 2 ;
            total = total - 1 ;
          } // while()
          
        } // if ()

      } // else if ()

      else if ( token == "." ) {
        
        back = temp.at( i + 1 ).token ;
        front = temp.at( i - 1 ).token ;
        if ( Is_Tree_Item( back ) ) {
          for ( int k = 0 ; k < num + 2 ; k++ )
            cout << " " ;
          Token_Print( token, type ) ;
          cout << endl ;
        } // if ()
            
        else if ( back == "(" ) { // // //////////////////////////////////////////
          i = i + 1 ;
          for ( int k = 0 ; k < num + 2 ; k++ )
            cout << " " ;
        
          int exce ; // //
          exce = i + 2 ;
          if ( exce < temp.size() && temp.at( exce ).token == ")" ) {
            
            type = temp.at( exce - 1 ).type ;
            token = temp.at( exce - 1 ).token ;
            
            if ( Is_Tree_Item( token ) ) {
              i = exce ;
              Token_Print( token, type ) ;
              cout << endl ;
            } // if ()
          } // if()
        
        } // else if ()
      } // else if () // // //////////////////////////////////////////////////////
          
      else if ( token == "nil" || token == "()" || token == "#f" ) {
        // back = temp.at( i + 1 ).token ;
        front = temp.at( i - 1 ).token ;
        if ( front == "." ) i = i ;
        else {
          if ( temp.at( i - 1 ).token != "(" )
            for ( int k = 0 ; k < num + 2 ; k++ )
              cout << " " ;
          Token_Print( token, type ) ;
          cout << endl ;
        } // else
      } // else if ()

      else if ( type == "QUOTE" ) {
        token = "( quote" ;
        if ( i != 0 && temp.at( i - 1 ).token != "(" )
          for ( int k = 0 ; k < num + 2 ; k++ )
            cout << " " ;
        Token_Print( token, type ) ;
        cout << endl ;
        num = num + 2 ;
      } // else if ()

      else {
        if ( i != 0 && temp.at( i - 1 ).token != "(" )
          for ( int k = 0 ; k < num + 2 ; k++ )
            cout << " " ;
        Token_Print( token, type ) ;
        cout << endl ;
        
        if ( i != 0 && temp.at( i - 1 ).token == "'" ) {
          for ( int k = 0 ; k < num ; k++ )
            cout << " " ;
          cout << ")" << endl ;
          num = num - 2 ;
          quote_num = quote_num - 1 ;
        } // if ()
      } // else 
    } // for ()
        
    
    
    for ( int i = 0 ; i < count.size() ; i++ )
      sum = sum + count.at( i ) ;
  
    while ( sum > 0 ) {
      for ( int k = 0 ; k < num ; k++ )
        cout << " " ;
      cout << ")" << endl ;
      num = num - 2 ;
      sum = sum - 1 ;
    } // while ()

    if ( quote_num != 0 ) cout << ")" << endl ;
    if ( left == right ) cout << endl ;
    if ( left > right ) cout << ")" << endl << endl ;


  } // Pretty_Print()
  
  
  // //////////////////////////////////////////////////////////////////////////////////////////////
  
  bool Is_Func( vector<Token> temp ) {
    
    string func ;

    if ( temp.size() == 1 ) func = temp.at( 0 ).token ;
    else if ( temp.at( 0 ).token == "'" && temp.size() >= 2 ) return true ;
    else if ( temp.at( 0 ).token == "quote" && temp.size() > 2 ) func = temp.at( 2 ).token ;
    else func = temp.at( 1 ).token ;

    if ( func == "cons" ) return true ;
    else if ( func == "list" ) return true ;

    else if ( func == "'" ) return true ;
    else if ( func == "quote" ) return true ;

    else if ( func == "define" ) return true ;

    else if ( func == "car" ) return true ;
    else if ( func == "cdr" ) return true ;

    else if ( func == "atom?" ) return true ;
    else if ( func == "pair?" ) return true ;
    else if ( func == "list?" ) return true ;
    else if ( func == "null?" ) return true ;
    else if ( func == "integer?" ) return true ;
    else if ( func == "real?" ) return true ;
    else if ( func == "number?" ) return true ;
    else if ( func == "string?" ) return true ;
    else if ( func == "boolean?" ) return true ;
    else if ( func == "symbol?" ) return true ;
    

    else if ( func == "+" ) return true ;
    else if ( func == "-" ) return true ;
    else if ( func == "*" ) return true ;
    else if ( func == "/" ) return true ;

    else if ( func == "not" ) return true ;
    else if ( func == "and" ) return true ;
    else if ( func == "or" ) return true ;

    else if ( func == ">" ) return true ;
    else if ( func == ">=" ) return true ;
    else if ( func == "<" ) return true ;
    else if ( func == "<=" ) return true ;
    else if ( func == "=" ) return true ;
    else if ( func == "string-append" ) return true ;
    else if ( func == "string>?" ) return true ;
    else if ( func == "string<?" ) return true ;
    else if ( func == "string=?" ) return true ;

    else if ( func == "eqv?" ) return true ;
    else if ( func == "equal?" ) return true ;

    else if ( func == "begin" ) return true ;

    else if ( func == "if" ) return true ;
    else if ( func == "cond" ) return true ;
    
    else if ( func == "exit" ) return true ;

    else if ( func == "clean-environment" ) return true ;
    else return false ;
      
  } // Is_Func()
  
  bool Is_Symbol_Func( Token temp ) {
    
    string func ;
    func = temp.token ;
    
    if ( func == "cons" ) return true ;
    else if ( func == "list" ) return true ;

    // else if ( func == "'" ) return true ;
    else if ( func == "quote" ) return true ;

    else if ( func == "define" ) return true ;

    else if ( func == "car" ) return true ;
    else if ( func == "cdr" ) return true ;

    else if ( func == "atom?" ) return true ;
    else if ( func == "pair?" ) return true ;
    else if ( func == "list?" ) return true ;
    else if ( func == "null?" ) return true ;
    else if ( func == "integer?" ) return true ;
    else if ( func == "real?" ) return true ;
    else if ( func == "number?" ) return true ;
    else if ( func == "string?" ) return true ;
    else if ( func == "boolean?" ) return true ;
    else if ( func == "symbol?" ) return true ;
    

    else if ( func == "+" ) return true ;
    else if ( func == "-" ) return true ;
    else if ( func == "*" ) return true ;
    else if ( func == "/" ) return true ;

    else if ( func == "not" ) return true ;
    else if ( func == "and" ) return true ;
    else if ( func == "or" ) return true ;

    else if ( func == ">" ) return true ;
    else if ( func == ">=" ) return true ;
    else if ( func == "<" ) return true ;
    else if ( func == "<=" ) return true ;
    else if ( func == "=" ) return true ;
    else if ( func == "string-append" ) return true ;
    else if ( func == "string>?" ) return true ;
    else if ( func == "string<?" ) return true ;
    else if ( func == "string=?" ) return true ;

    else if ( func == "eqv?" ) return true ;
    else if ( func == "equal?" ) return true ;

    else if ( func == "begin" ) return true ;

    else if ( func == "if" ) return true ;
    else if ( func == "cond" ) return true ;

    else if ( func == "clean-environment" ) return true ;
    else return false ;
      
  } // Is_Symbol_Func()
  
  
  bool Is_Stack_Func( vector<Token> temp ) {
    
    string func ;
    if ( temp.at( 0 ).token == "'" ) return true ;
    else if ( temp.at( 0 ).token != "(" ) return false ;
    else func = temp.at( 1 ).token ;
    
    if ( func == "(" ) return true ;
    else if ( func == "cons" ) return true ;
    else if ( func == "list" ) return true ;

    else if ( func == "'" ) return true ;
    else if ( func == "quote" ) return true ;

    else if ( func == "define" ) return true ;

    else if ( func == "car" ) return true ;
    else if ( func == "cdr" ) return true ;

    else if ( func == "atom?" ) return true ;
    else if ( func == "pair?" ) return true ;
    else if ( func == "list?" ) return true ;
    else if ( func == "null?" ) return true ;
    else if ( func == "integer?" ) return true ;
    else if ( func == "real?" ) return true ;
    else if ( func == "number?" ) return true ;
    else if ( func == "string?" ) return true ;
    else if ( func == "boolean?" ) return true ;
    else if ( func == "symbol?" ) return true ;
    

    else if ( func == "+" ) return true ;
    else if ( func == "-" ) return true ;
    else if ( func == "*" ) return true ;
    else if ( func == "/" ) return true ;

    else if ( func == "not" ) return true ;
    else if ( func == "and" ) return true ;
    else if ( func == "or" ) return true ;

    else if ( func == ">" ) return true ;
    else if ( func == ">=" ) return true ;
    else if ( func == "<" ) return true ;
    else if ( func == "<=" ) return true ;
    else if ( func == "=" ) return true ;
    else if ( func == "string-append" ) return true ;
    else if ( func == "string>?" ) return true ;
    else if ( func == "string<?" ) return true ;
    else if ( func == "string=?" ) return true ;

    else if ( func == "eqv?" ) return true ;
    else if ( func == "equal?" ) return true ;

    else if ( func == "begin" ) return true ;

    else if ( func == "if" ) return true ;
    else if ( func == "cond" ) return true ;

    else if ( func == "clean-environment" ) return true ;
    else return false ;
      
  } // Is_Stack_Func()
  
  
  void Arg_Func_Change( vector<SQ_Token> &Data, vector<Token> &Output, bool &result, string &error ) {

    bool check ;
    int count = 0 ;

    /*
    cout << "This is Arg_Func_Change Input :" << endl ;
    for ( int i = 0 ; i < Data.size() ; i++ ) {
      cout << "Argnum " << i << " : " ;
      count = count + Data.at( i ).stack.size() ;
      for ( int j = 0 ; j < Data.at( i ).stack.size() ; j++ ) 
        cout << Data.at( i ).stack.at( j ).token << " " ;
      cout << endl ;
    } // for ()
    */

    while ( count < Data.size() && result ) {
      // check = Is_Stack_Func( Data.at( count ).stack ) ;
      // if ( Data.at( count ).stack.at( 0 ).token == "(" ) check = true ;
      // if ( check )
      EvalSexp( Data.at( count ).stack, Data.at( count ).stack, result, error ) ;
      if ( !result ) Output.assign( Data.at( count ).stack.begin(), Data.at( count ).stack.end() ) ;
      count = count + 1 ;
    } // while ()
    

    

    /*
    cout << endl ;
    cout << "This is Arg_Func_Change result :" << endl ;
    for ( int i = 0 ; i < Data.size() ; i++ ) {
      cout << "Argnum " << i << " : " ;
      count = count + Data.at( i ).stack.size() ;
      for ( int j = 0 ; j < Data.at( i ).stack.size() ; j++ ) 
        cout << Data.at( i ).stack.at( j ).token << " " ;
      cout << endl ;
    } // for ()
    */

  } // Arg_Func_Change()
  
  
  void Symbol_Change_Recheck( int at, int &newat ) {
    
    string str ;
    
    if ( mDifine.at( at ).stack.size() > 1 || mDifine.at( at ).stack.at( 0 ).type != "SYMBOL" ) {
      newat = at ;
      return ;
    } // if ()
        
    newat = at ;
    str = mDifine.at( at ).stack.at( 0 ).token ;
    
    for ( int i = 0 ; i < mDifine.size() ; i++ )
      if ( str == mDifine.at( i ).symbol )
        newat = i ;
    
    
  } // Symbol_Change_Recheck()
  
  
  void Difine_Symbol_Change( vector<Token> Input, vector<Token> &Output ) {
    
    bool result, quote ;
    vector<Token> temp ;
    int left = 0, right = 0 ;
    
    /*
    for ( int i = 0 ; i < Input.size() ; i++ ) {
      result = false ;
      for ( int j = 0 ; j < mDifine.size() ; j++ ) {
        if ( Input.at( i ).token == mDifine.at( j ).symbol ) {
          for ( int k = 0 ; k < mDifine.at( j ).stack.size() ; k++ )
            temp.push_back( mDifine.at( j ).stack.at( k ) ) ;
          result = true ;
        } // if ()
      } // for ()

      if ( !result ) temp.push_back( Input.at( i ) ) ;
      Output.clear() ;
      Output.assign( temp.begin(), temp.end() ) ;
    } // for ()
    */
    
    
    
    for ( int i = 0 ; i < Input.size() ; i++ ) {
      quote = false ;
      result = false ;
      left = 0, right = 0 ;
      if ( Input.at( i ).token == "'" ) {
        quote = true ;
        temp.push_back( Input.at( i ) ) ;
        i = i + 1 ;
        if ( Input.at( i ).token != "(" ) {
          temp.push_back( Input.at( i ) ) ;
          i = i + 1 ;
          quote = false ;
        } // if ()
      } // if ()
      
      while ( quote && i < Input.size() ) {
        // cout << Input.at( i ).token << " " ;
        if ( Input.at( i ).token == "(" ) left = left + 1 ;
        if ( Input.at( i ).token == ")" ) right = right + 1 ;
        if ( left == right && left != 0 ) quote = false ;
        temp.push_back( Input.at( i ) ) ;
        i = i + 1 ;
      } // while
     
      if ( i < Input.size() ) {
          
        string matchstr ;
        matchstr = Input.at( i ).token ;
          
          
        for ( int j = 0 ; j < mDifine.size() ; j++ ) {
            
            
          if ( matchstr == mDifine.at( j ).symbol ) {
            bool recheck ; 
            recheck = false ;
            
            while ( !recheck && mDifine.at( j ).stack.size() == 1 ) {
              
              Symbol_Change_Recheck( j, j ) ;
              if ( mDifine.at( j ).stack.size() == 1 && mDifine.at( j ).stack.at( 0 ).type == "SYMBOL" ) {
                Symbol_Change_Recheck( j, j ) ;
                recheck = true ;
              } // if ()
                  
              else recheck = true ;
              
            } // while ()
              
              
            if ( mDifine.at( j ).stack.size() > 2 ) {
              Token quoteadd ;
              quoteadd.token = "'" ;
              quoteadd.type = "QUOTE" ;
              temp.push_back( quoteadd ) ;
            } // if ()
                
            for ( int k = 0 ; k < mDifine.at( j ).stack.size() ; k++ )
              temp.push_back( mDifine.at( j ).stack.at( k ) ) ;
            result = true ;
            j = mDifine.size() ;
          } // if ()
              
          
          
        } // for ()

        if ( !result ) temp.push_back( Input.at( i ) ) ;
      } // if ()

      Output.clear() ;
      Output.assign( temp.begin(), temp.end() ) ;
    } // for ()
    

  } // Difine_Symbol_Change()
  
  
  void Check_Argnum( int &argnum, vector<Token> Input, vector<SQ_Token> &Output, bool &result ) {

    mtop = false ;
    bool valid, dot ;
    int start = 0, match_at = 0, count = 0 ;

    vector<Token> origin ;
    origin.assign( mTempStack.begin(), mTempStack.end() ) ;
    mTempStack.assign( Input.begin(), Input.end() ) ;

    if ( Input.size() == 0 ) return ;

    /*
    cout << "This is Check_Argnum Input : " << endl ;
    for ( int i = 0 ; i < Input.size() ; i++ )
      cout << Input.at( i ).token << " " ;
    cout << endl << endl ;
    */

    while ( match_at < Input.size() ) {
      valid = Match_Syntax( match_at ) ; 

      if ( valid ) {
        SQ_Token temp ;
        argnum = argnum + 1 ;

        for ( int i = start ; i <= match_at ; i++ ) 
          temp.stack.push_back( Input.at( i ) ) ;
        Output.push_back( temp ) ;

      } // if ()

      else {
        SQ_Token temp ;
        argnum = argnum + 1 ;

        for ( int i = start ; i <= match_at ; i++ ) 
          temp.stack.push_back( Input.at( i ) ) ;
        Output.push_back( temp ) ;
      } // else 

      start = match_at + 1 ;
      match_at = match_at + 1 ;

    } // while()

    for ( int i = 0 ; i < Output.size() ; i++ ) {
      dot = false ;
      if ( Output.at( i ).stack.size() == 1 && Output.at( i ).stack.at( 0 ).token == "." )
        dot = true ;
      if ( dot ) {
        int after_dot = 0 ;
        after_dot = Output.size() - i - 1 ;
        if ( after_dot > 1 ) result = false ;
      } // if ()
          
    } // for ()
    /*
    cout << "This is Check_Argnum result : " << endl ;
    for ( int i = 0 ; i < Output.size() ; i++ ) {
      cout << "Argnum " << i << " : " ;
      count = count + Output.at( i ).stack.size() ;
      for ( int j = 0 ; j < Output.at( i ).stack.size() ; j++ ) 
        cout << Output.at( i ).stack.at( j ).token << " " ;
      cout << " ----- Match At : " << count << endl ;
    } // for ()
    cout << endl ;
    */

    mTempStack.assign( origin.begin(), origin.end() ) ;

    if ( Output.size() >= 2 && result ) {
      int last = Output.size() - 1 ;
      int sec = Output.size() - 2 ;
      
      if ( Output.at( sec ).stack.size() == 1 && Output.at( last ).stack.size() == 1 
           && Output.at( sec ).stack.at( 0 ).token == "." 
           && Output.at( last ).stack.at( 0 ).type == "NIL" ) {
        argnum = argnum - 2 ;
        result = true ;
        vector<SQ_Token> refresh ;
        refresh.assign( Output.begin(), Output.end() - 2 ) ;
        Output.assign( refresh.begin(), refresh.end() ) ;
      } // if ()
      
    } // if ()
        
    for ( int i = 0 ; i < Output.size() ; i++ ) 
      if ( Output.at( i ).stack.size() == 1 && Output.at( i ).stack.at( 0 ).token == "." ) 
        result = false ;
 

  } // Check_Argnum()
  
  
  void Seperate_Element( vector<Token> Input, vector<Token> &front, vector<Token> &back ) {
    /*
    cout << "This is Seperate_Element : " << endl ;
    for ( int i = 0 ; i < Input.size() ; i++ ) 
      cout << Input.at( i ).token << " " ;
    cout << endl ;
    */
    if ( Input.size() == 2 ) {
      front.clear() ;
      front.assign( Input.begin(), Input.begin() ) ;
      back.clear() ;
      back.assign( Input.end(), Input.end() ) ;
    } // if ()
        
    else {
      bool dot ;
      dot = false ;

      if ( Input.at( 1 ).token != "(" ) {

        front.clear() ;
        front.push_back( Input.at( 1 ) ) ;
        back.clear() ;

        for ( int i = 0 ; i < Input.size() ; i++ ) {
          if ( i == 1 ) i = i + 1 ;
          if ( i == 2 && Input.at( i ).token == "." ) {
            i = i + 1 ;
            dot = true ;
          } // if ()

          back.push_back( Input.at( i ) ) ;
        } // for ()
            
        if ( back.size() == 3 && dot ) {
          Token temp ; 
          temp = back.at( 1 ) ;
          back.clear() ;
          back.push_back( temp ) ;
        } // if()

      } // if ()
      
      else {
        int bound ;
        int left = 0, right = 0 ;

        for ( int i = 1 ; i < Input.size() - 1 ; i++ ) {
          if ( Input.at( i ).token == "(" ) left = left + 1 ;
          if ( Input.at( i ).token == ")" ) right = right + 1 ;
          if ( left == right && left != 0 ) {
            bound = i ;
            i = Input.size() ;
          } // if ()
        } // for()

        front.clear() ;

        for ( int i = 1 ; i <= bound ; i++ ) 
          front.push_back( Input.at( i ) ) ;

        back.clear() ;
        back.push_back( Input.at( 0 ) ) ;

        for ( int i = bound + 1 ; i < Input.size() ; i++ ) {
          if ( i == bound + 1 && Input.at( i ).token == "." ) {
            i = i + 1 ;
            dot = true ;
          } // if ()

          back.push_back( Input.at( i ) ) ;
        } // for ()
            
        if ( back.size() == 3 && dot ) {
          Token temp ; 
          temp = back.at( 1 ) ;
          back.clear() ;
          back.push_back( temp ) ;
        } // if()

      } // else 

    } // else 
    /*
    if ( back.size() >= 4 && back.at( 1 ).token == "(" ) {
      bool check ;
      int second_for_last ;
      int num, left = 0, right = 0 ;
      
      num = 1 ;
      check = false ;
      
      while ( num < back.size() && !check ) {
        if ( back.at( num ).token == "(" ) left = left + 1 ;
        if ( back.at( num ).token == ")" ) right = right + 1 ;
        if ( left == right && left != 0 ) check = true ;
        if ( !check ) num = num + 1 ;
      } // while ()
          
      second_for_last = back.size() - 2 ;
      if ( num == second_for_last )
        back.assign( back.begin() + 1, back.end() - 1 ) ;

    } // if ()
    
    cout << "This is Input : " ;
    for ( int i = 0 ; i < Input.size() ; i++ )
      cout << Input.at( i ).token << " " ;
    cout << endl ;
    
    cout << "This is front : " ;
    for ( int i = 0 ; i < front.size() ; i++ )
      cout << front.at( i ).token << " " ;
    cout << endl ;
    
    cout << "This is back : " ;
    for ( int i = 0 ; i < back.size() ; i++ )
      cout << back.at( i ).token << " " ;
    cout << endl ;
    */
    

    
  } // Seperate_Element()
  
  void Returning_Origin_Command( string func, vector<Token> Input, vector<Token> &Output ) {
    
    vector<SQ_Token> vec_arg ;
    vector<Token> origin, temp ;
    origin.assign( mTokenStack.begin(), mTokenStack.end() ) ;
    
    
    int count = 0, left, right ;
    
    while ( count < origin.size() ) {
      
      if ( origin.at( count ).token == func && origin.at( count - 1 ).token == "(" ) {
        
        left = 1 ;
        right = 0 ;
        vector<Token> add ;
        add.push_back( origin.at( count - 1 ) ) ;
        
        for ( int i = count ; i < origin.size() && left != right ; i++ ) {
          if ( origin.at( i ).token == "(" ) left = left + 1 ;
          if ( origin.at( i ).token == ")" ) right = right + 1 ;
          add.push_back( origin.at( i ) ) ;
        } // for ()
        
        SQ_Token tempadd ;
        tempadd.stack.assign( add.begin(), add.end() ) ;
        vec_arg.push_back( tempadd ) ;
        
      } // if ()
      
      
      count = count + 1 ;
      
    } // while()

    if ( vec_arg.size() == 1 ) Output.assign( vec_arg.at( 0 ).stack.begin(), vec_arg.at( 0 ).stack.end() ) ;
    else {
      int num = 0 ;
      bool check ;
      Token addtoken ;
      vector<Token> inputfill ;
      
      addtoken.token = "(" ;
      addtoken.type = "LEFT-PAREN" ;
      inputfill.push_back( addtoken ) ;
      
      addtoken.token = func ;
      addtoken.type = "SYMBOL" ;
      inputfill.push_back( addtoken ) ;
      
      for ( int i = 0 ; i < Input.size() ; i++ ) 
        inputfill.push_back( Input.at( i ) ) ;
        
      addtoken.token = ")" ;
      addtoken.type = "RIGHT-PAREN" ;
      inputfill.push_back( addtoken ) ;
      
      check = false ;
      
      while ( !check && num < vec_arg.size() ) {
        
        Difine_Symbol_Change( vec_arg.at( num ).stack, temp ) ;
        if ( !check && temp.size() == inputfill.size() ) {
          bool same = true ;
          for ( int i = 0 ; i < temp.size() ; i++ )
            if ( temp.at( i ).token != inputfill.at( i ).token ) same = false ;
          if ( same ) {
            check = true ;
            Output.assign( vec_arg.at( num ).stack.begin(), vec_arg.at( num ).stack.end() ) ;
          } // if ()
        } // if ()
            
        num = num + 1 ;
        
      } // while()
      
      
    } // else 

    
  } // Returning_Origin_Command()
  

  void Func_Cons( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    bool dot ;
    bool check = true, check1 = true, check2 = true ;
    Token temp, temp1, temp2 ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;
    

    
    dot = false ;
    if ( Input.size() == 2 && Input.at( 1 ).type != "SYMBOL" ) dot = true ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;

    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "cons", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "cons" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()

    temp1 = vec_arg.at( 0 ).stack.at( 0 ) ;
    temp2 = vec_arg.at( 1 ).stack.at( 0 ) ;
    
    if ( result && argnum == 2 && temp1.type == "SYMBOL" && !Is_Symbol_Func( temp1 ) ) {
      check = false ;
      check1 = false ;
    } // if () ;
    
    if ( result && argnum == 2 && temp2.type == "SYMBOL" && !Is_Symbol_Func( temp2 ) ) {
      check = false ;
      check2 = false ;
    } // if () ;
    /*
    for ( int i = 0 ; i < vec_arg.size() ; i++ )
      if ( vec_arg.at( i ).stack.at( 0 ).token != "'" && !mCons_Symbol ) 
        Difine_Symbol_Change( vec_arg.at( i ).stack, vec_arg.at( i ).stack ) ;
    */
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */


    if ( argnum == 2 && result ) {

      
      if ( Is_ATOM( vec_arg.at( 1 ).stack ) ) dot = true ;


      if ( vec_arg.at( 1 ).stack.at( 0 ).token == "(" ) 
        vec_arg.at( 1 ).stack.assign( vec_arg.at( 1 ).stack.begin() + 1, vec_arg.at( 1 ).stack.end() - 1 ) ;
    
      if ( !check1 ) 
        if ( temp1.token != vec_arg.at( 0 ).stack.at( 0 ).token ) check1 = true ;

      if ( !check2 ) 
        if ( temp2.token != vec_arg.at( 1 ).stack.at( 0 ).token ) check2 = true ;
    
      if ( check1 && check2 ) check = true ;
    
      if ( check ) {

        temp.token = "(" ;
        temp.type = "LEFT-PAREN" ;
        Output.clear() ;
        Output.push_back( temp ) ;


        for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            Output.push_back( vec_arg.at( i ).stack.at( j ) ) ;
          if ( dot ) {
            temp.token = "." ;
            temp.type = "DOT" ;
            Output.push_back( temp ) ;
            dot = false ;
          } // if ()

        } // for ()

        temp.token = ")" ;
        temp.type = "RIGHT-PAREN" ;
        Output.push_back( temp ) ;

      } // if ()
          
      else {
        result = false ;
        error = "ERROR (unbound symbol) : " ;
        Output.clear() ;
        if ( !check1 ) temp = temp1 ;
        else temp = temp2 ;
        Output.push_back( temp ) ;
      } // else 

    } // if ()

    else {
      dot = false ;

      for ( int i = 0 ; i < vec_arg.size() ; i++ ) 
        for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
          if ( vec_arg.at( i ).stack.at( j ).token == "." ) dot = true ;

      if ( dot ) {
        error = "ERROR (non-list) : " ;
        Output.clear() ;
        result = false ;
        Returning_Origin_Command( "cons", Input, Output ) ;
      } // if ()
        
      else {
        result = false ;
        error = "ERROR (incorrect number of arguments) : " ;
        temp.type = "STRING" ;
        temp.token = "cons" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // else 
  
  } // Func_Cons()
  
  
  void Func_List( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "list", Input, Output ) ;
      return ;
    } // if ()
    /*
    for ( int i = 0 ; i < vec_arg.size() ; i++ )
      Difine_Symbol_Change( vec_arg.at( i ).stack, vec_arg.at( i ).stack ) ;
    */
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    


    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    temp.token = "(" ;
    temp.type = "LEFT-PAREN" ;
    Output.clear() ;
    Output.push_back( temp ) ;

    for ( int i = 0 ; i < vec_arg.size() ; i++ ) 
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
        Output.push_back( vec_arg.at( i ).stack.at( j ) ) ;

    temp.token = ")" ;
    temp.type = "RIGHT-PAREN" ;
    Output.push_back( temp ) ;

  } // Func_List()
  
  void Func_Quote( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

  
    vector<Token> temp ;
    Returning_Origin_Command( "quote", Input, Input ) ;
    
    
    int size ;
    size = Input.size() - 1 ;
    
    for ( int i = 2 ; i < size ; i++ )
      temp.push_back( Input.at( i ) ) ;

  
    if ( temp.size() == 0 ) {
      Token add ;
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      add.type = "STRING" ;
      add.token = "quote" ;
      Output.clear() ;
      Output.push_back( add ) ;
    } // if () 
        
    else if ( temp.size() == 1 ) Output.assign( temp.begin(), temp.end() ) ;

    else {
      int argnum ;
      bool check ;
      vector<SQ_Token> vec_arg ;
      
      Check_Argnum( argnum, temp, vec_arg, result ) ;

      if ( !result ) {
        error = "ERROR (non-list) : " ;
        Output.clear() ;
        Output.assign( Input.begin(), Input.end() ) ;
        return ;
      } // if ()
          
      else if ( argnum > 1 ) {
        Token add ;
        result = false ;
        error = "ERROR (incorrect number of arguments) : " ;
        add.type = "STRING" ;
        add.token = "quote" ;
        Output.clear() ;
        Output.push_back( add ) ;
      } // else if ()
          
      else Output.assign( temp.begin(), temp.end() ) ;

    } // else 

  } // Func_Quote()
  
  
  void Func_Define( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;

    vector<SQ_Token> vec_arg, origin ;
    
    if ( !mtop ) {
      result = false ;
      Output.clear() ;
      error = "ERROR (level of DEFINE)" ;
      return ;
    } // if ()


    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    
    if ( !result && argnum == 4 ) {
      if ( vec_arg.at( 2 ).stack.at( 0 ).token == "." && vec_arg.at( 3 ).stack.at( 0 ).type == "NIL" ) {
        result = true ;
        argnum = 2 ;
        vec_arg.at( 2 ).stack.clear() ;
        vec_arg.at( 3 ).stack.clear() ;
      } // if()
    } // if()

    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
      return ;
    } // if ()
        
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;

    /*
    if ( result && argnum != 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "define" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    */

    
    


    
    if ( argnum == 2 && !Is_Func( vec_arg.at( 0 ).stack ) 
         && vec_arg.at( 0 ).stack.at( 0 ).type == "SYMBOL" ) {

      bool exist ;
      bool realsymbol ;
      exist = false ;
      realsymbol = false ;
      
      Vari vari ;
      vari.symbol = vec_arg.at( 0 ).stack.at( 0 ).token ;
      

      if ( vec_arg.at( 1 ).stack.size() == 1 && vec_arg.at( 1 ).stack.at( 0 ).type == "SYMBOL" ) 
        realsymbol = true ;

      if ( vec_arg.at( 1 ).stack.at( 0 ).token == "(" || vec_arg.at( 1 ).stack.at( 0 ).token == "'" )
        EvalSexp( vec_arg.at( 1 ).stack, vec_arg.at( 1 ).stack, result, error ) ;
    
      if ( !result ) {
        Output.assign( vec_arg.at( 1 ).stack.begin(), vec_arg.at( 1 ).stack.end() ) ;
        return ;
      } // if ()

      if ( Output.size() == 1 && Output.at( 0 ).type == "SYMBOL" && !realsymbol )
        Output.at( 0 ).type = "STRING" ;
    
      if ( !result ) return ;
      vari.stack.assign( vec_arg.at( 1 ).stack.begin(), vec_arg.at( 1 ).stack.end() ) ;
      
      for ( int i = 0 ; i < mDifine.size() ; i++ ) {
        if ( mDifine.at( i ).symbol == vari.symbol ) {
          mDifine.at( i ).stack.assign( vari.stack.begin(), vari.stack.end() ) ;
          exist = true ;
        } // if ()
      } // for ()

      if ( !exist ) mDifine.push_back( vari ) ;
      /*
      if ( vec_arg.at( 0 ).stack.size() == 1 && vec_arg.at( 1 ).stack.size() == 1 ) {
        if ( vec_arg.at( 0 ).stack.at( 0 ).token == vec_arg.at( 1 ).stack.at( 0 ).token ) {
          result = false ;
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.assign( vec_arg.at( 1 ).stack.begin(), vec_arg.at( 1 ).stack.end() ) ;
          return ;
        } // if ()
      } // if ()
      */

      Output.clear() ;
      cout << vec_arg.at( 0 ).stack.at( 0 ).token << " defined" << endl ;
      
      Vari define ;
      bool hassymbol ;
      
      define.symbol = origin.at( 0 ).stack.at( 0 ).token ;
      define.stack.assign( origin.at( 1 ).stack.begin(), origin.at( 1 ).stack.end() ) ;
      
      hassymbol = false ;
      for ( int i = 0 ; i < mDifine_string.size() ; i++ ) {
        if ( define.symbol == mDifine_string.at( i ).symbol ) {
          hassymbol = true ;
          mDifine_string.at( i ).stack.assign( define.stack.begin(), define.stack.end() ) ;
        } // if ()
      } // for ()
      
      if ( !hassymbol ) mDifine_string.push_back( define ) ;
      
      string definesymbol, symbolbliding ;
      definesymbol = vec_arg.at( 0 ).stack.at( 0 ).token ;

      if ( vec_arg.at( 1 ).stack.at( 0 ).type == "SYMBOL" ) 
        symbolbliding = vec_arg.at( 1 ).stack.at( 0 ).token ;
      else 
        symbolbliding = "" ;

      
      for ( int i = 0 ; i < mTable.size() ; i++ )
        for ( int j = 0 ; j < mTable.at( i ).symbol.size() ; j++ )
          if ( mTable.at( i ).symbol.at( j ) == definesymbol )
            mTable.at( i ).symbol.at( j ) = "" ;
        
      if ( symbolbliding.length() == 0 ) {
        Table addtable ;
        addtable.symbol.push_back( definesymbol ) ;
        mTable.push_back( addtable ) ;
      } // if ()
          
      else {
        int symat ;
        bool symbolexist ;
        Table addtable ;
        
        symbolexist = false ;

        for ( int i = 0 ; i < mTable.size() ; i++ ) {
          for ( int j = 0 ; j < mTable.at( i ).symbol.size() ; j++ ) {
            if ( mTable.at( i ).symbol.at( j ) == symbolbliding ) {
              symbolexist = true ;
              mTable.at( i ).symbol.push_back( definesymbol ) ;
            } // if ()
          } // for ()
        } // for ()


        if ( !symbolexist ) {
          addtable.symbol.push_back( symbolbliding ) ;
          addtable.symbol.push_back( definesymbol ) ;
          mTable.push_back( addtable ) ;
        } // if ()


      } // else 


    } // if ()
        
    else if ( !result ) {
      error = "ERROR (non-list) : " ;
      // Returning_Origin_Command( "define", Input, Output ) ;
      Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
    } // else if ()
        
    else {
      result = false ;
      error = "ERROR (DEFINE format) : " ;
      // Returning_Origin_Command( "define", Input, Output ) ;
      Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
    } // else 

  } // Func_Define()
  
  void Func_Car( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    mCons_Symbol = true ;
    Token temp ;
    bool symbol = true ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;
    
    // if ( Input.at( 0 ).token == "'" ) Input.assign( Input.begin() + 1, Input.end() ) ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "car", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "car" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    if ( vec_arg.at( 0 ).stack.at( 0 ).type != "SYMBOL" ) symbol = false ;

    /*
    cout << endl ;
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      cout << "This is Argnum " << i << " : "  ;
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
        cout << vec_arg.at( i ).stack.at( j ).token << " " ;
      cout << endl ;
    } // for ()
    cout << endl ;
    */
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    
    /*
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      cout << "This is Argnum " << i << " : "  ;
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
        cout << vec_arg.at( i ).stack.at( j ).token << " " ;
      cout << endl ;
    } // for ()
    cout << endl ;
    */
    
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      vector<Token> front, back ;

      if ( vec_arg.at( 0 ).stack.at( 0 ).token == "(" ) {
        Seperate_Element( vec_arg.at( 0 ).stack, front, back ) ;
        Output.assign( front.begin(), front.end() ) ;
      } // if ()

      else {
        result = false ;
        
        if ( vec_arg.at( 0 ).stack.at( 0 ).type == "SYMBOL" && symbol ) {
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.push_back( vec_arg.at( 0 ).stack.at( 0 ) ) ;
        } // if ()
            
        else {
          error = "ERROR (car with incorrect argument type) : " ;
          Output.clear() ;
          Output.push_back( vec_arg.at( 0 ).stack.at( 0 ) ) ;
        } // else 

      } // else 


    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "car" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 
        
    mCons_Symbol = false ;

  } // Func_Car()
  
  void Func_Cdr( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    mCons_Symbol = true ;
    Token temp ;
    bool symbol = true ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;
    
    // if ( Input.at( 0 ).token == "'" ) Input.assign( Input.begin() + 1, Input.end() ) ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "cdr", Input, Output ) ;
      return ;
    } // if ()

    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "cdr" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
        
    if ( vec_arg.at( 0 ).stack.at( 0 ).type != "SYMBOL" ) symbol = false ;
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;

        
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      vector<Token> front, back ;

      if ( vec_arg.at( 0 ).stack.at( 0 ).token == "(" ) {
        Seperate_Element( vec_arg.at( 0 ).stack, front, back ) ;
        Output.assign( back.begin(), back.end() ) ;
      } // if ()

      else {
        result = false ;
        
        if ( vec_arg.at( 0 ).stack.at( 0 ).type == "SYMBOL" && symbol ) {
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.push_back( vec_arg.at( 0 ).stack.at( 0 ) ) ;
        } // if ()
            
        else {
          error = "ERROR (cdr with incorrect argument type) : " ;
          Output.clear() ;
          Output.push_back( vec_arg.at( 0 ).stack.at( 0 ) ) ;
        } // else 
      } // else 
    
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "cdr" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 
        
    mCons_Symbol = false ;
  
  } // Func_Cdr()
  
  
  void Func_Is_Atom( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "atom?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "atom?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      if ( Is_ATOM( vec_arg.at( 0 ).stack ) ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()

      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "atom?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Atom()

  void Func_Is_Pair( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool change ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;
    
    if ( Input.size() > 0 && Input.at( 0 ).token == "SYMBOL" ) change = true ;
    

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "pair?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "pair?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    if ( Is_Stack_Func( vec_arg.at( 0 ).stack ) ) change = true ;
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */



    if ( argnum == 1 && result ) {

      if ( vec_arg.at( 0 ).stack.at( 0 ).token == "'" && vec_arg.at( 0 ).stack.size() >= 4 ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()
      
      else if ( change && vec_arg.at( 0 ).stack.at( 0 ).token == "(" && vec_arg.at( 0 ).stack.size() >= 3 ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else if ()
  
      else if ( vec_arg.at( 0 ).stack.at( 0 ).type == "SYMBOL" ) {
        result = false ;
        error = "ERROR (unbound symbol) : " ;
        temp.type = "SYMBOL" ;
        temp.token = vec_arg.at( 0 ).stack.at( 0 ).token ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else if ()
  
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "pair?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Pair()
  
  void Func_Is_List( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {


    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "list?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "list?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    if ( result && vec_arg.at( 0 ).stack.at( 0 ).token != "'" ) 
      Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    check = true ;
    for ( int i = 0 ; i < vec_arg.at( 0 ).stack.size() ; i++ )
      if ( vec_arg.at( 0 ).stack.at( i ).token == "." )
        check = false ;

    if ( argnum == 1 && result ) {
      if ( check && vec_arg.at( 0 ).stack.at( 0 ).token == "'" && vec_arg.at( 0 ).stack.size() == 2
           && vec_arg.at( 0 ).stack.at( 1 ).token == "()" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()
      
      else if ( vec_arg.at( 0 ).stack.at( 0 ).token == "'" && check && vec_arg.at( 0 ).stack.size() > 2 ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else if ()
  
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "list?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_List()
  
  void Func_Is_Null( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "null?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "null?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "NIL" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()
  
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "null?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Null()
  
  void Func_Is_Integer( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "integer?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "integer?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "INT" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()
  
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "integer?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 


  } // Func_Is_Integer()
  
  void Func_Is_Real( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "real?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "real?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    
    if ( argnum == 1 && result ) {
      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "INT" || vec_arg.at( 0 ).stack.at( 0 ).type == "FLOAT" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()
      
      else if ( vec_arg.at( 0 ).stack.at( 0 ).type == "SYMBOL" ) {
        result = false ;
        error = "ERROR (unbound symbol) : " ;
        temp.type = "SYMBOL" ;
        temp.token = vec_arg.at( 0 ).stack.at( 0 ).token ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else if ()
  
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "real?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Real()
  
  
  void Func_Is_Number( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {
    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "number?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "number?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "INT" || vec_arg.at( 0 ).stack.at( 0 ).type == "FLOAT" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()
      
      else if ( vec_arg.at( 0 ).stack.at( 0 ).type == "SYMBOL" ) {
        result = false ;
        error = "ERROR (unbound symbol) : " ;
        temp.type = "SYMBOL" ;
        temp.token = vec_arg.at( 0 ).stack.at( 0 ).token ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else if ()
  
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "number?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Number()
  
  void Func_Is_String( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "string?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "STRING" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()
  
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 
    

  } // Func_Is_String()
  
  void Func_Is_Boolean( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "boolean?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "boolean?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    
    if ( argnum == 1 && result ) {
      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "T" || vec_arg.at( 0 ).stack.at( 0 ).type == "NIL" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()
  
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "boolean?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Boolean()
  
  void Func_Is_Symbol( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    
    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "symbol?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "symbol?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "SYMBOL" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()

      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "symbol?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Symbol()
  
  void Num_To_String( int num, string &str ) {

    stringstream ss ;
    ss << num ;
    ss >> str ;

  } // Num_To_String()
  
  
  void Num_To_String( float num, string &str ) {

    stringstream ss ;
    ss << num ;
    ss >> str ;

  } // Num_To_String()
  
  void Func_Plus( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    bool afloat ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "+", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "+" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    int size ;
    check = true ;
    afloat = false ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      size = vec_arg.at( i ).stack.size() ;
      for ( int j = 0 ; j < size ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" )
            issymbol = true ;
          else 
            issymbol = false ;
          i = vec_arg.size() ;
          j = size ;
        } // if ()

        if ( i < vec_arg.size() && vec_arg.at( i ).stack.at( j ).type == "FLOAT" ) afloat = true ;
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check && !afloat ) {
        int sum = 0 ;
        Token ptr ;
        for ( int i = 0 ; i < vec_arg.size() ; i++ ) 
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            sum = sum + atoi( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
        ptr.type = "INT" ;
        Num_To_String( sum, ptr.token ) ;
        Output.clear() ;
        Output.push_back( ptr );
      } // if ()

      else if ( check && afloat ) {
        float sum = 0 ;
        Token ptr ;
        for ( int i = 0 ; i < vec_arg.size() ; i++ ) 
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            sum = sum + atof( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
        ptr.type = "FLOAT" ;
        Num_To_String( sum, ptr.token ) ;
        Output.clear() ;
        Output.push_back( ptr );
      } // else if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) ) 
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (+ with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "+" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Plus()
  
  
  void Func_Minus( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    bool afloat ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "-", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "-" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    
    int size ;
    check = true ;
    afloat = false ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      size = vec_arg.at( i ).stack.size() ;
      for ( int j = 0 ; j < size ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" )
            issymbol = true ;
          else 
            issymbol = false ;
          i = vec_arg.size() ;
          j = size ;
        } // if ()

        if ( i < vec_arg.size() && vec_arg.at( i ).stack.at( j ).type == "FLOAT" ) afloat = true ;
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check && !afloat ) {
        int sum = 0 ;
        Token ptr ;
        sum = 2 * atoi( vec_arg.at( 0 ).stack.at( 0 ).token.c_str() ) ;
        for ( int i = 0 ; i < vec_arg.size() ; i++ ) 
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            sum = sum - atoi( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
        ptr.type = "INT" ;
        Num_To_String( sum, ptr.token ) ;
        Output.clear() ;
        Output.push_back( ptr );
      } // if ()

      else if ( check && afloat ) {
        float sum = 0 ;
        Token ptr ;
        sum = 2 * atof( vec_arg.at( 0 ).stack.at( 0 ).token.c_str() ) ;
        for ( int i = 0 ; i < vec_arg.size() ; i++ ) 
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            sum = sum - atof( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
        ptr.type = "FLOAT" ;
        Num_To_String( sum, ptr.token ) ;
        Output.clear() ;
        Output.push_back( ptr );
      } // else if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) ) 
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (- with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "-" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Minus()
  
  
  
  void Func_Multiply( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    bool afloat ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "*", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "*" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    int size ;
    check = true ;
    afloat = false ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      size = vec_arg.at( i ).stack.size() ;
      for ( int j = 0 ; j < size ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" )
            issymbol = true ;
          else 
            issymbol = false ;
          i = vec_arg.size() ;
          j = size ;
        } // if ()

        if ( i < vec_arg.size() && vec_arg.at( i ).stack.at( j ).type == "FLOAT" ) afloat = true ;
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check && !afloat ) {
        int sum = 0 ;
        Token ptr ;
        sum = 1 ;
        for ( int i = 0 ; i < vec_arg.size() ; i++ ) 
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            sum = sum * atoi( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
        ptr.type = "INT" ;
        Num_To_String( sum, ptr.token ) ;
        Output.clear() ;
        Output.push_back( ptr );
      } // if ()

      else if ( check && afloat ) {
        float sum = 0 ;
        Token ptr ;
        sum = 1 ;
        for ( int i = 0 ; i < vec_arg.size() ; i++ ) 
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            sum = sum * atof( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
        ptr.type = "FLOAT" ;
        Num_To_String( sum, ptr.token ) ;
        Output.clear() ;
        Output.push_back( ptr );
      } // else if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) ) 
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (* with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "*" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Multiply()
  
  
  void Func_Divide( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    bool afloat ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "/", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "/" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    int size ;
    check = true ;
    afloat = false ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      size = vec_arg.at( i ).stack.size() ;
      for ( int j = 0 ; j < size ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" )
            issymbol = true ;
          else 
            issymbol = false ;
          i = vec_arg.size() ;
          j = size ;
        } // if ()

        if ( i < vec_arg.size() && vec_arg.at( i ).stack.at( j ).type == "FLOAT" ) afloat = true ;
      } // for()
    } // for ()
        
    if ( check ) {
      bool devizero ;
      int zeroi = 0, comparei ;
      float zerof = 0, comparef ;
      
      devizero = false ;
        
      for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
        for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ ) {
            
          if ( vec_arg.at( i ).stack.at( j ).type == "INT" ) {
            comparei = atoi( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
            if ( zeroi == comparei ) devizero = true ;
          } // if ()
              
          if ( vec_arg.at( i ).stack.at( j ).type == "FLOAT" ) {
            comparef = atof( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
            if ( zerof == comparef ) devizero = true ;
          } // if ()
              
          
        } // for ()
      } // for ()
          
      if ( devizero ) {
        result = false ;
        error = "ERROR (division by zero) : " ;
        temp.type = "STRING" ;
        temp.token = "/" ;
        Output.clear() ;
        Output.push_back( temp ) ;
        return ;
      } // if ()
        
    } // if ()
    

    if ( argnum >= 2 && result ) {

      if ( check && !afloat ) {
        int sum = 0 ;
        Token ptr ;
        sum = atoi( vec_arg.at( 0 ).stack.at( 0 ).token.c_str() ) ;
        for ( int i = 1 ; i < vec_arg.size() ; i++ ) 
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            sum = sum / atoi( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
        ptr.type = "INT" ;
        Num_To_String( sum, ptr.token ) ;
        Output.clear() ;
        Output.push_back( ptr );
      } // if ()

      else if ( check && afloat ) {
        float sum = 0 ;
        Token ptr ;
        sum = atof( vec_arg.at( 0 ).stack.at( 0 ).token.c_str() ) ;
        for ( int i = 1 ; i < vec_arg.size() ; i++ ) 
          for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
            sum = sum / atof( vec_arg.at( i ).stack.at( j ).token.c_str() ) ;
        ptr.type = "FLOAT" ;
        Num_To_String( sum, ptr.token ) ;
        Output.clear() ;
        Output.push_back( ptr );
      } // else if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) ) 
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (/ with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "/" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Divide()
  
  
  void Func_Not( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {
    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "not", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "not" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 1 && result ) {
      vector<Token> stack ;
      stack = vec_arg.at( 0 ).stack ;
      if ( origin.at( 0 ).stack.at( 0 ).token == stack.at( 0 ).token && !Is_Func( stack ) ) {
        if ( origin.size() == 1 && vec_arg.size() == 1 && origin.at( 0 ).stack.at( 0 ).type == "SYMBOL" ) {
          result = false ;
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.assign( stack.begin(), stack.end() ) ;
          return ;
        } // if ()
      } // if ()

      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "T" ) {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()

      else if ( vec_arg.at( 0 ).stack.at( 0 ).type == "NIL" ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else if ()

      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 

    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "not" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Not()
  
  
  void Func_And( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "and", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "and" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    
    int nilat, errorat ;
    nilat = -1, errorat = -1 ;

    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      if ( vec_arg.at( i ).stack.size() == 1 && vec_arg.at( i ).stack.at( 0 ).type == "NIL" )
        nilat = i ;
      if ( Output.size() == vec_arg.at( i ).stack.size() ) {
        bool thesame ;
        thesame = true ;
        for ( int j = 0 ; j < Output.size() ; j++ )
          if ( Output.at( j ).token != vec_arg.at( i ).stack.at( j ).token )
            thesame = false ;
        if ( thesame ) errorat = i ;
      } // if ()
          
      if ( nilat != -1 || errorat != -1 ) i = vec_arg.size() ;
      
    } // for ()
    
    if ( !result && errorat == -1 ) result = true ;
    
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */


    if ( argnum >= 2 && result ) {
      bool check = true ;
      for ( int i = 0 ; i < vec_arg.size() ; i++ )
        if ( vec_arg.at( i ).stack.at( 0 ).type == "NIL" )
          check = false ;
      
      if ( check ) {
        int last ;
        last = vec_arg.size() - 1 ;
        Output.clear() ;
        Output.assign( vec_arg.at( last ).stack.begin(), vec_arg.at( last ).stack.end() ) ;
      } // if ()
          
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 

    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "and" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_And()
  
  
  void Func_Or( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {
    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "or", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "or" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum >= 2 && result ) {
      int at ;
      bool check = false ;
      for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
        if ( vec_arg.at( i ).stack.at( 0 ).type != "NIL" ) {
          check = true ;
          at = i ;
          i = vec_arg.size() ;
        } // if ()
      } // for ()
      
      if ( check ) {
        Output.clear() ;
        Output.assign( vec_arg.at( at ).stack.begin(), vec_arg.at( at ).stack.end() ) ;
      } // if ()
          
      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 

    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "or" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Or()
  
  
  void Func_Larger( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( ">", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = ">" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" ) 
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        float num1, num2 ;
        temp.type = "T" ;
        temp.token = "#t" ;
        
        for ( int i = 0, j = 1 ; j < vec_arg.size() ; i++, j++ ) {
          num1 = atof( vec_arg.at( i ).stack.at( 0 ).token.c_str() ) ;
          num2 = atof( vec_arg.at( j ).stack.at( 0 ).token.c_str() ) ;
          if ( num1 <= num2 ) {
            temp.type = "NIL" ;
            temp.token = "nil" ;
          } // if ()

        } // for()
            
        Output.clear() ;
        Output.push_back( temp ) ;
        
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (> with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = ">" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Larger()
  
  
  void Func_Larger_Or_Equal( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( ">=", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = ">=" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" ) 
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        float num1, num2 ;
        temp.type = "T" ;
        temp.token = "#t" ;
        
        for ( int i = 0, j = 1 ; j < vec_arg.size() ; i++, j++ ) {
          num1 = atof( vec_arg.at( i ).stack.at( 0 ).token.c_str() ) ;
          num2 = atof( vec_arg.at( j ).stack.at( 0 ).token.c_str() ) ;
          if ( num1 < num2 ) {
            temp.type = "NIL" ;
            temp.token = "nil" ;
          } // if ()

        } // for()
            
        Output.clear() ;
        Output.push_back( temp ) ;
        
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (>= with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = ">=" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Larger_Or_Equal()
  
  
  void Func_Less( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {
    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "<", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "<" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" ) 
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        float num1, num2 ;
        temp.type = "T" ;
        temp.token = "#t" ;
        
        for ( int i = 0, j = 1 ; j < vec_arg.size() ; i++, j++ ) {
          num1 = atof( vec_arg.at( i ).stack.at( 0 ).token.c_str() ) ;
          num2 = atof( vec_arg.at( j ).stack.at( 0 ).token.c_str() ) ;
          if ( num1 >= num2 ) {
            temp.type = "NIL" ;
            temp.token = "nil" ;
          } // if ()

        } // for()
            
        Output.clear() ;
        Output.push_back( temp ) ;
        
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (< with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "<" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Less()
  
  
  void Func_Less_Or_Equal( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "<=", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "<=" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" ) 
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        float num1, num2 ;
        temp.type = "T" ;
        temp.token = "#t" ;
        
        for ( int i = 0, j = 1 ; j < vec_arg.size() ; i++, j++ ) {
          num1 = atof( vec_arg.at( i ).stack.at( 0 ).token.c_str() ) ;
          num2 = atof( vec_arg.at( j ).stack.at( 0 ).token.c_str() ) ;
          if ( num1 > num2 ) {
            temp.type = "NIL" ;
            temp.token = "nil" ;
          } // if ()

        } // for()
            
        Output.clear() ;
        Output.push_back( temp ) ;
        
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (<= with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "<=" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Less_Or_Equal()
  
  
  void Func_Equal( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "=", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "=" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "INT" && vec_arg.at( i ).stack.at( j ).type != "FLOAT" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" ) 
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        float num1, num2 ;
        temp.type = "T" ;
        temp.token = "#t" ;
        
        for ( int i = 0, j = 1 ; j < vec_arg.size() ; i++, j++ ) {
          num1 = atof( vec_arg.at( i ).stack.at( 0 ).token.c_str() ) ;
          num2 = atof( vec_arg.at( j ).stack.at( 0 ).token.c_str() ) ;
          if ( num1 != num2 ) {
            temp.type = "NIL" ;
            temp.token = "nil" ;
          } // if ()

        } // for()
            
        Output.clear() ;
        Output.push_back( temp ) ;
        
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (= with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "=" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Equal()
  
  
  void Func_String_Append( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
 
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "string-append", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string-append" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() && check ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() && check ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "STRING" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" )
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        string str, addstr ;
        addstr = vec_arg.at( 0 ).stack.at( 0 ).token ;
        addstr.assign( addstr, 0, addstr.length() - 1 ) ;
        str.append( addstr ) ;

        for ( int i = 1 ; i < vec_arg.size() - 1 ; i++ ) {
          addstr = vec_arg.at( i ).stack.at( 0 ).token ;
          addstr.assign( addstr, 1, addstr.length() - 2 ) ;
          str.append( addstr ) ;
        } // for ()
            
        addstr = vec_arg.at( vec_arg.size() - 1 ).stack.at( 0 ).token ;
        addstr.assign( addstr, 1, addstr.length() - 1 ) ;
        str.append( addstr ) ;
            
        temp.token = str ;
        temp.type = "STRING" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (string-append with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string-append" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_String_Append()
  
  
  void Func_String_Larger( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "string>?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string>?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() && check ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() && check ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "STRING" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" )
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        string str1, str2 ;
        temp.type = "T" ;
        temp.token = "#t" ;
        
        for ( int i = 0, j = 1 ; j < vec_arg.size() ; i++, j++ ) {
          str1 = vec_arg.at( i ).stack.at( 0 ).token.c_str() ;
          str2 = vec_arg.at( j ).stack.at( 0 ).token.c_str() ;
          if ( strcmp( str1.c_str(), str2.c_str() ) <= 0 ) {
            temp.type = "NIL" ;
            temp.token = "nil" ;
          } // if ()

        } // for()
            
        Output.clear() ;
        Output.push_back( temp ) ;
        
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (string>? with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string>?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_String_Larger()
  
  
  void Func_String_Less( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "string<?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string<?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() && check ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() && check ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "STRING" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" )
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        string str1, str2 ;
        temp.type = "T" ;
        temp.token = "#t" ;
        
        for ( int i = 0, j = 1 ; j < vec_arg.size() ; i++, j++ ) {
          str1 = vec_arg.at( i ).stack.at( 0 ).token.c_str() ;
          str2 = vec_arg.at( j ).stack.at( 0 ).token.c_str() ;
          if ( strcmp( str1.c_str(), str2.c_str() ) >= 0 ) {
            temp.type = "NIL" ;
            temp.token = "nil" ;
          } // if ()

        } // for()
            
        Output.clear() ;
        Output.push_back( temp ) ;
        
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (string<? with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string<?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_String_Less()
  
  
  void Func_String_Equal( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "string=?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string=?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    check = true ;
    bool issymbol ;
    vector<Token> stack ;
    issymbol = false ;
    
    for ( int i = 0 ; i < vec_arg.size() && check ; i++ ) {
      for ( int j = 0 ; j < vec_arg.at( i ).stack.size() && check ; j++ ) {
        if ( vec_arg.at( i ).stack.at( j ).type != "STRING" ) {
          check = false ;
          stack = vec_arg.at( i ).stack ;
          if ( origin.at( i ).stack.size() == 1 && origin.at( i ).stack.at( 0 ).type == "SYMBOL" )
            issymbol = true ;
        } // if ()
      } // for()
    } // for ()
    

    if ( argnum >= 2 && result ) {

      if ( check ) {
        string str1, str2 ;
        temp.type = "T" ;
        temp.token = "#t" ;
        
        for ( int i = 0, j = 1 ; j < vec_arg.size() ; i++, j++ ) {
          str1 = vec_arg.at( i ).stack.at( 0 ).token.c_str() ;
          str2 = vec_arg.at( j ).stack.at( 0 ).token.c_str() ;
          if ( strcmp( str1.c_str(), str2.c_str() ) != 0 ) {
            temp.type = "NIL" ;
            temp.token = "nil" ;
          } // if ()

        } // for()
            
        Output.clear() ;
        Output.push_back( temp ) ;
        
      } // if ()

      else {
        result = false ;
        if ( stack.size() == 1 && stack.at( 0 ).type == "SYMBOL" && issymbol && !Is_Func( stack ) )
          error = "ERROR (unbound symbol) : " ;
        else error = "ERROR (string=? with incorrect argument type) : " ;
        Output.clear() ;
        Output.assign( stack.begin(), stack.end() ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "string=?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_String_Equal()
  
  
  void Symbol_To_Symbol( vector<Token> Input, vector<Token> &Output ) {
    int at, left = 0, right = 0 ;
    bool exist ;
    vector<Token> temp ;
    
    /*
      quote = false ;
      result = false ;
      left = 0, right = 0 ;
      if ( Input.at( i ).token == "'" ) {
        quote = true ;
        temp.push_back( Input.at( i ) ) ;
        i = i + 1 ;
        if ( Input.at( i ).token != "(" ) {
          temp.push_back( Input.at( i ) ) ;
          i = i + 1 ;
          quote = false ;
        } // if ()
      } // if ()
      
      while ( quote && i < Input.size() ) {
        // cout << Input.at( i ).token << " " ;
        if ( Input.at( i ).token == "(" ) left = left + 1 ;
        if ( Input.at( i ).token == ")" ) right = right + 1 ;
        if ( left == right && left != 0 ) quote = false ;
        temp.push_back( Input.at( i ) ) ;
        i = i + 1 ;
      } // while
    */
    
    for ( int i = 0 ; i < Input.size() ; i++ ) {
      at = 0 ;
      exist = false ;
      
      if ( Input.at( i ).token == "'" ) {
        bool qwork ;
        qwork = false ;
        left = 0, right = 0 ;
        
        temp.push_back( Input.at( i ) ) ;
        i = i + 1 ;

        if ( Input.at( i ).token != "(" ) {
          temp.push_back( Input.at( i ) ) ;
          i = i + 1 ;
          qwork = true ;
        } // if ()
        
        while ( !qwork && i < Input.size() ) {
        // cout << Input.at( i ).token << " " ;
          if ( Input.at( i ).token == "(" ) left = left + 1 ;
          if ( Input.at( i ).token == ")" ) right = right + 1 ;
          if ( left == right && left != 0 ) qwork = true ;
          temp.push_back( Input.at( i ) ) ;
          i = i + 1 ;
        } // while
        
        
      } // if ()
      
      if ( i < Input.size() && Input.at( i ).type == "SYMBOL" ) {
        Token add ;
        for ( int x = 0 ; x < mTable.size() ; x++ ) {
          for ( int y = 0 ; y < mTable.at( x ).symbol.size() ; y++ ) {
            if ( Input.at( i ).token == mTable.at( x ).symbol.at( y ) ) {
              exist = true ;
              at = x ;
            } // if ()
          } // for ()
        } // for ()
        
        if ( !exist ) temp.push_back( Input.at( i ) ) ;
        else {
          add.token = mTable.at( at ).symbol.at( 0 ) ;
          add.type = "SYMBOL" ;
          temp.push_back( add ) ;
        } // else 
        
      } // if ()

      else if ( i < Input.size() ) temp.push_back( Input.at( i ) ) ;
      else ;
      
    } // for ()
    
    Output.assign( temp.begin(), temp.end() ) ;
    
    
  } // Symbol_To_Symbol()
  
  void Func_Is_Eqv( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg, origin ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    origin.assign( vec_arg.begin(), vec_arg.end() ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "eqv?", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "eqv?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()

    /*
    if ( result ) {
      for ( int i = 0 ; i < vec_arg.size() ; i++ )
        if ( vec_arg.at( i ).stack.size() == 1 && vec_arg.at( i ).stack.at( 0 ).type == "SYMBOL" )
          Difine_Symbol_Change( vec_arg.at( i ).stack, vec_arg.at( i ).stack ) ;
    } // if ()
    */

    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
      if ( vec_arg.at( i ).stack.size() > 1 && vec_arg.at( i ).stack.at( 0 ).token == "(" )
        EvalSexp( vec_arg.at( i ).stack, vec_arg.at( i ).stack, result, error ) ;
      if ( !result ) {
        Output.assign( vec_arg.at( i ).stack.begin(), vec_arg.at( i ).stack.end() ) ;
        return ;
      } // if ()
          
    } // for ()

    
    
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */
    
    
    if ( Is_ATOM( vec_arg.at( 0 ).stack ) && Is_ATOM( vec_arg.at( 1 ).stack ) ) {
      Token arg1, arg2 ;
      arg1 = vec_arg.at( 0 ).stack.at( 0 ) ;
      arg2 = vec_arg.at( 1 ).stack.at( 0 ) ;
      
      if ( arg1.token == arg2.token && arg1.type != "STRING" && arg1.type != "SYMBOL" ) {
        check = true ;
      } // if ()
          
      else if ( arg1.type == "SYMBOL" && arg2.type == "SYMBOL" ) {
        bool test ;
        vector<Token> varg1, varg2 ;
        
        varg1.push_back( arg1 ) ;
        varg2.push_back( arg2 ) ;
        
        Difine_Symbol_Change( varg1, varg1 ) ;
        Difine_Symbol_Change( varg2, varg2 ) ;
        
        if ( arg1.token == varg1.at( 0 ).token && !Is_Symbol_Func( arg1 ) ) {
          result = false ;
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.push_back( arg1 ) ;
          return ;
        } // if ()
        
        if ( arg2.token == varg2.at( 0 ).token && !Is_Symbol_Func( arg2 ) ) {
          result = false ;
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.push_back( arg2 ) ;
          return ;
        } // if ()
         
        varg1.clear() ;
        varg2.clear() ;
        varg1.push_back( arg1 ) ;
        varg2.push_back( arg2 ) ;
        
        
        test = true ;
        while ( test ) {
          test = false ;
          for ( int i = 0 ; i < mDifine.size() && !test ; i++ ) {
            if ( arg1.token == mDifine.at( i ).symbol && mDifine.at( i ).stack.at( 0 ).type == "SYMBOL" ) {
              test = true ;
              arg1 = mDifine.at( i ).stack.at( 0 ) ;
              varg1.push_back( mDifine.at( i ).stack.at( 0 ) ) ;
            } // if ()
          } // for()
        } // while()
        
        test = true ;
        while ( test ) {
          test = false ;
          for ( int i = 0 ; i < mDifine.size() && !test ; i++ ) {
            if ( arg2.token == mDifine.at( i ).symbol && mDifine.at( i ).stack.at( 0 ).type == "SYMBOL" ) {
              test = true ;
              arg2 = mDifine.at( i ).stack.at( 0 ) ;
              varg2.push_back( mDifine.at( i ).stack.at( 0 ) ) ;
            } // if ()
          } // for()
        } // while()
        
        /*
        cout << "This is arg1 Token String : " ;
        for ( int i = 0 ; i < varg1.size() ; i++ ) 
          cout << varg1.at( i ).token << " " ;
        cout << endl << endl ;
        
        cout << "This is arg2 Token String : " ;
        for ( int i = 0 ; i < varg2.size() ; i++ ) 
          cout << varg2.at( i ).token << " " ;
        cout << endl << endl ;
        */
        
        check = false ;
        for ( int i = 0 ; i < varg1.size() ; i++ ) 
          for ( int j = 0 ; j < varg2.size() ; j++ )
            if ( varg1.at( i ).token == varg2.at( j ).token )
              check = true ;
          
          
      } // else if ()
          
      else if ( arg1.type == "SYMBOL" && arg2.type != "SYMBOL" ) {

        vector<Token> varg1, varg2 ;
        varg1.push_back( arg1 ) ;
        Difine_Symbol_Change( varg1, varg1 ) ;

        if ( arg1.token == varg1.at( 0 ).token && !Is_Symbol_Func( arg1 ) ) {
          result = false ;
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.push_back( arg1 ) ;
          return ;
        } // if ()
        

        if ( varg1.size() == 1 && varg1.at( 0 ).token == arg2.token )
          check = true ;
        else 
          check = false ;
        
      } // else if ()
          
      else if ( arg1.type != "SYMBOL" && arg2.type == "SYMBOL" ) {

        vector<Token> varg1, varg2 ;
        varg2.push_back( arg2 ) ;
        Difine_Symbol_Change( varg2, varg2 ) ;

        if ( arg2.token == varg2.at( 0 ).token && !Is_Symbol_Func( arg2 ) ) {
          result = false ;
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.push_back( arg2 ) ;
          return ;
        } // if ()
         
        if ( varg2.size() == 1 && varg2.at( 0 ).token == arg1.token )
          check = true ;
        else 
          check = false ;
        
      } // else if ()

      else check = false ;
      


    } // if ()
        
    else {
        
      if ( origin.at( 0 ).stack.at( 0 ).type == "SYMBOL" && origin.at( 1 ).stack.at( 0 ).token == "'" )
        check = false ;
      else if ( origin.at( 1 ).stack.at( 0 ).type == "SYMBOL" && origin.at( 0 ).stack.at( 0 ).token == "'" )
        check = false ;
      else if ( origin.at( 0 ).stack.at( 0 ).token == "'" && origin.at( 1 ).stack.at( 0 ).token == "'" )
        check = false ;
      
      else if ( origin.at( 0 ).stack.at( 0 ).type == "SYMBOL" 
                && origin.at( 1 ).stack.at( 0 ).type != "SYMBOL" ) {

        vector<Token> varg1, varg2 ;
        varg2.assign( origin.at( 1 ).stack.begin(), origin.at( 1 ).stack.end() ) ;

        for ( int i = 0 ; i < mDifine_string.size() ; i++ )
          if ( origin.at( 0 ).stack.at( 0 ).token == mDifine_string.at( i ).symbol )
            varg1.assign( mDifine_string.at( i ).stack.begin(), mDifine_string.at( i ).stack.end() ) ;
        
        bool same ;
        same = true ;
        
        Symbol_To_Symbol( varg1, varg1 ) ;
        if ( origin.at( 1 ).stack.at( 0 ).token == "'" ) Symbol_To_Symbol( varg2, varg2 ) ;
        /*
        cout << "This is varg1 : " << endl ;
        for ( int i = 0 ; i < varg1.size() ; i++ )
          cout << varg1.at( i ).token << " " ;
        cout << endl << endl ;
        
        cout << "This is varg2 : " << endl ;
        for ( int i = 0 ; i < varg2.size() ; i++ )
          cout << varg2.at( i ).token << " " ;
        cout << endl << endl ;
        */

        if ( varg1.size() != varg2.size() )
          same = false ;
        else {
          for ( int i = 0 ; i < varg1.size() ; i++ )
            if ( varg1.at( i ).token != varg2.at( i ).token )
              same = false ;
        } // else
        
        if ( origin.at( 1 ).stack.at( 0 ).token == "'" ) same = false ;
        if ( same ) check = true ;

      } // else if ()
          
      
      else if ( origin.at( 0 ).stack.at( 0 ).type != "SYMBOL" 
                && origin.at( 1 ).stack.at( 0 ).type == "SYMBOL" ) {
          
        vector<Token> varg1, varg2 ;
        varg1.assign( origin.at( 0 ).stack.begin(), origin.at( 0 ).stack.end() ) ;
        
        for ( int i = 0 ; i < mDifine_string.size() ; i++ )
          if ( origin.at( 1 ).stack.at( 0 ).token == mDifine_string.at( i ).symbol )
            varg2.assign( mDifine_string.at( i ).stack.begin(), mDifine_string.at( i ).stack.end() ) ;
        
        bool same ;
        same = true ;
        
        if ( origin.at( 0 ).stack.at( 0 ).token == "'" ) Symbol_To_Symbol( varg1, varg1 ) ;
        Symbol_To_Symbol( varg2, varg2 ) ;
        
        if ( varg1.size() != varg2.size() )
          same = false ;
        else {
          for ( int i = 0 ; i < varg1.size() ; i++ )
            if ( varg1.at( i ).token != varg2.at( i ).token )
              same = false ;
        } // else
            
        if ( origin.at( 0 ).stack.at( 0 ).token == "'" ) same = false ;
        if ( same ) check = true ;

      } // else if ()
          
      else if ( origin.at( 0 ).stack.size() > 1 && origin.at( 1 ).stack.size() > 1 ) {
          
        vector<Token> varg1, varg2 ;
        varg1.assign( origin.at( 0 ).stack.begin(), origin.at( 0 ).stack.end() ) ;
        varg2.assign( origin.at( 1 ).stack.begin(), origin.at( 1 ).stack.end() ) ;
        
        bool same ;
        same = true ;
        
        if ( origin.at( 0 ).stack.at( 0 ).token != "'" ) Symbol_To_Symbol( varg1, varg1 ) ;
        if ( origin.at( 1 ).stack.at( 0 ).token != "'" ) Symbol_To_Symbol( varg2, varg2 ) ;
        
        if ( varg1.size() != varg2.size() )
          same = false ;
        else {
          for ( int i = 0 ; i < varg1.size() ; i++ )
            if ( varg1.at( i ).token != varg2.at( i ).token )
              same = false ;
        } // else
            
        if ( same ) check = true ;
        // check = true ;
        
      } // else if ()
          
      else check = false ;
      
    } // else 

    if ( argnum == 2 && result ) {
      if ( check ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()

      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "eqv?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Eqv()
  
  
  void Func_Is_Equal( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    bool check ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "equal?", Input, Output ) ;
      return ;
    } // if ()
    /*
    for ( int i = 0 ; i < vec_arg.size() ; i++ )
      if ( vec_arg.at( i ).stack.size() == 1 && vec_arg.at( i ).stack.at( 0 ).type == "SYMBOL" )
        Difine_Symbol_Change( vec_arg.at( i ).stack, vec_arg.at( i ).stack ) ;
    */
    if ( result && argnum != 2 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "equal?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    /*
    for ( int i = 0 ; i < vec_arg.size() ; i++ )
      if ( vec_arg.at( i ).stack.size() == 1 && vec_arg.at( i ).stack.at( 0 ).type == "SYMBOL" )
        Difine_Symbol_Change( vec_arg.at( i ).stack, vec_arg.at( i ).stack ) ;
    */
    
    
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    check = true ;
    if ( vec_arg.at( 0 ).stack.size() == vec_arg.at( 1 ).stack.size() ) {
      for ( int i = 0 ; i < vec_arg.at( 0 ).stack.size() ; i++ )
        if ( vec_arg.at( 0 ).stack.at( i ).token != vec_arg.at( 1 ).stack.at( i ).token )
          check = false ;
    } // if ()
        
    else check = false ;

    if ( argnum == 2 && result ) {
      if ( check ) {
        temp.type = "T" ;
        temp.token = "#t" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // if ()

      else {
        temp.type = "NIL" ;
        temp.token = "nil" ;
        Output.clear() ;
        Output.push_back( temp ) ;
      } // else 
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "equal?" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Is_Equal()
  
  
  void Func_Begin( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "begin", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum < 1 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "begin" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    /*
    for ( int i = 0 ; i < vec_arg.size() ; i++ ) {
        
      if ( vec_arg.at( i ).stack.size() == 1 && vec_arg.at( i ).stack.at( 0 ).type == "SYMBOL" ) {
        temp = vec_arg.at( i ).stack.at( 0 ) ;
        // Difine_Symbol_Change( vec_arg.at( i ).stack, vec_arg.at( i ).stack ) ;
        if ( temp.token == vec_arg.at( i ).stack.at( 0 ).token ) {
          result = false ;
          error = "ERROR (unbound symbol) : " ;
          Output.clear() ;
          Output.push_back( temp ) ;
          return ;
        } // if ()
      } // if ()
    } // for ()
    */

    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( error == "ERROR (no return value) : " ) Returning_Origin_Command( "begin", Input, Output ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */


    if ( argnum >= 1 && result ) {
      Output.clear() ;
      argnum = argnum - 1 ;
      /*
      if ( vec_arg.at( argnum ).stack.size() == 1 && vec_arg.at( argnum ).stack.at( 0 ).type == "SYMBOL" ) 
        Difine_Symbol_Change( vec_arg.at( argnum ).stack, vec_arg.at( argnum ).stack ) ;
      */
      for ( int i = 0 ; i < vec_arg.at( argnum ).stack.size() ; i++ )
        Output.push_back( vec_arg.at( argnum ).stack.at( i ) ) ;
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "begin" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Begin()
  
  
  void Func_IF( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<Token> origin ;
    vector<SQ_Token> vec_arg ;


    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "if", Input, Output ) ;
      return ;
    } // if ()
    
    
    if ( argnum < 2 || argnum > 3 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "if" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    // Arg_Func_Change( vec_arg, Output, result, error ) ;
    
    EvalSexp( vec_arg.at( 0 ).stack, vec_arg.at( 0 ).stack, result, error ) ;
    if ( !result ) Output.assign( vec_arg.at( 0 ).stack.begin(), vec_arg.at( 0 ).stack.end() ) ;
    if ( !result ) return ;
    
    
    if ( vec_arg.at( 0 ).stack.at( 0 ).type == "T" || vec_arg.at( 0 ).stack.at( 0 ).type != "NIL" ) {
      EvalSexp( vec_arg.at( 1 ).stack, vec_arg.at( 1 ).stack, result, error ) ;
      if ( !result ) Output.assign( vec_arg.at( 1 ).stack.begin(), vec_arg.at( 1 ).stack.end() ) ;
    } // if ()
    else if ( argnum == 3 && vec_arg.at( 0 ).stack.at( 0 ).type == "NIL" ) {
      EvalSexp( vec_arg.at( 2 ).stack, vec_arg.at( 2 ).stack, result, error ) ;
      if ( !result ) Output.assign( vec_arg.at( 2 ).stack.begin(), vec_arg.at( 2 ).stack.end() ) ;
    } // else if 
    else {
      result = false ;
      error = "ERROR (no return value) : " ;
      Returning_Origin_Command( "if", Input, Output ) ;
    } // else
    
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */


    if ( argnum >= 2 && argnum <= 3 && result ) {

      if ( vec_arg.at( 0 ).stack.at( 0 ).type == "T" || vec_arg.at( 0 ).stack.at( 0 ).type != "NIL" ) {
        Output.clear() ;
        for ( int i = 0 ; i < vec_arg.at( 1 ).stack.size() ; i++ )
          Output.push_back( vec_arg.at( 1 ).stack.at( i ) ) ;
      } // if ()
          
      else {
        if ( argnum == 3 ) {
          Output.clear() ;
          for ( int i = 0 ; i < vec_arg.at( 2 ).stack.size() ; i++ )
            Output.push_back( vec_arg.at( 2 ).stack.at( i ) ) ;
        } // if ()
            
        else {
          result = false ;
          error = "ERROR (no return value) : " ;
          Returning_Origin_Command( "if", Input, Output ) ;
          // Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
        } // else 
      } // else 
    
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "if" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_IF()
      
  void Cond_Seperate( vector<Token> Input, vector<Token> &Condition, vector<SQ_Token> &Value, bool &check ) {

    Value.clear() ;
    Condition.clear() ;
    Input.assign( Input.begin() + 1, Input.end() - 1 ) ;

    if ( Input.size() == 2 ) {
      Condition.push_back( Input.at( 0 ) ) ;

      SQ_Token temp ;
      temp.stack.push_back( Input.at( 1 ) ) ;
      Value.push_back( temp ) ;
      // cout << "Argnum 1 : " << Input.at( 0 ).token << endl ;
      // cout << "Argnum 2 : " << Input.at( 1 ).token << endl ;
    } // if ()
        
    else {

      bool valid, quit ;
      int match_at = 0, argnum = 0, start = 0 ;
      
      vector<Token> store ;
      vector<SQ_Token> output ;
      store.assign( mTempStack.begin(), mTempStack.end() ) ;
      mTempStack.assign( Input.begin(), Input.end() ) ;

      quit = false ;

      while ( match_at < mTempStack.size() && !quit ) {

        valid = Match_Syntax( match_at ) ; 
        
        if ( valid ) {
          SQ_Token temp ;
          argnum = argnum + 1 ;
          // cout << "Argnum " << argnum << " : " ;

          for ( int i = start ; i <= match_at ; i++ ) {
            temp.stack.push_back( Input.at( i ) ) ;
            // cout << Input.at( i ).token << " " ;
          } // for ()

          // cout << "Match_at = " << match_at << endl ;
          start = match_at + 1 ;
          output.push_back( temp ) ;
        } // if ()
            
        else check = false ;
        
        if ( !check ) return ;

        match_at = match_at + 1 ;

      } // while()

      int last = output.size() - 1 ;
      Condition.assign( output.at( 0 ).stack.begin(), output.at( 0 ).stack.end() ) ;
      if ( output.size() > 1 ) Value.assign( output.begin() + 1, output.end() ) ;

      mTempStack.clear() ;
      mTempStack.assign( store.begin(), store.end() ) ;

    } // else 

  } // Cond_Seperate()
  
  
  void Func_Cond( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    /*
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "cond", Input, Output ) ;
      return ;
    } // if ()
    */
    if ( result && argnum < 1 ) {
      result = false ;
      error = "ERROR (COND format) : " ;
      Output.clear() ;
      Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
      return ;
    } // if ()
    
    bool argcheck ;
    argcheck = true ;
    

    for ( int i = 0 ; i < vec_arg.size() ; i++ )
      if ( vec_arg.at( i ).stack.at( 0 ).token != "(" || vec_arg.at( i ).stack.size() < 4 )
        argcheck = false ;
      
    
    if ( !argcheck ) {
      result = false ;
      error = "ERROR (COND format) : " ;
      Output.clear() ;
      Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
      return ;
    } // if ()

    // Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum >= 1 && result ) {
      
      bool check ;
      check = false ;
      int num = 0, arg_size ;
      vector<Token> condition ;
      vector<SQ_Token> value ;
      
      Output.clear() ;
      
      while ( !check && num < vec_arg.size() ) {

        Cond_Seperate( vec_arg.at( num ).stack, condition, value, result ) ;
        if ( !result ) return ;

        
        if ( num != vec_arg.size() - 1 || Is_Stack_Func( condition ) )
          EvalSexp( condition, condition, result, error ) ;
        if ( !result ) {
          Output.assign( condition.begin(), condition.end() ) ;
          return ;
        } // if ()

        if ( condition.at( 0 ).type != "NIL" )
          check = true ;
        else 
          num = num + 1 ;

      } // while()

      if ( !check ) {
        result = false ;
        error = "ERROR (no return value) : " ;
        // Returning_Origin_Command( "cond", Input, Output ) ;
        Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
      } // if ()
          
      else {
          
        if ( value.size() == 0 ) {
          result = false ;
          error = "ERROR (no return value) : " ;
          Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
          return ;
        } // if ()
        /*
        for ( int i = 0 ; i < value.size() ; i++ )
          if ( value.at( i ).stack.size() == 1 && value.at( i ).stack.at( 0 ).type == "SYMBOL" )
            Difine_Symbol_Change( value.at( i ).stack, value.at( i ).stack ) ;
        */
        Arg_Func_Change( value, Output, result, error ) ;
        if ( !result ) return ;

        num = value.size() - 1 ;
        Output.assign( value.at( num ).stack.begin(), value.at( num ).stack.end() ) ;

      } // else 

    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "cond" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Cond()
  
  
  void Func_Env_Cln( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;
    
    if ( !mtop ) {
      result = false ;
      Output.clear() ;
      error = "ERROR (level of CLEAN-ENVIRONMENT)" ;
      return ;
    } // if ()

    // Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;
    
    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Returning_Origin_Command( "clean-environment", Input, Output ) ;
      return ;
    } // if ()
    
    if ( result && argnum != 0 ) {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "clean-environment" ;
      Output.clear() ;
      Output.push_back( temp ) ;
      return ;
    } // if ()
    
    Arg_Func_Change( vec_arg, Output, result, error ) ;
    if ( !result ) return ;
    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    if ( argnum == 0 && result ) {
      result = true ;
      temp.type = "STRING" ;
      temp.token = "environment cleaned" ;
      mDifine.clear() ;
      Output.clear() ;
      mTable.clear() ;
      mDifine.clear() ;
      mDifine_string.clear() ;
      Output.push_back( temp ) ;
    } // if ()

    else {
      result = false ;
      error = "ERROR (incorrect number of arguments) : " ;
      temp.type = "STRING" ;
      temp.token = "clean-environment" ;
      Output.clear() ;
      Output.push_back( temp ) ;
    } // else 

  } // Func_Env_Cln()
  
  
  
  
  
  
  
  
  void Start_Func( vector<Token> Input, string &func, vector<Token> &Output, bool &result, string &error ) {

    Token temp ;
    int argnum = 0 ;
    vector<SQ_Token> vec_arg ;

    Difine_Symbol_Change( Input, Input ) ;
    Check_Argnum( argnum, Input, vec_arg, result ) ;

    if ( !result ) {
      error = "ERROR (non-list) : " ;
      Output.assign( mTokenStack.begin(), mTokenStack.end() ) ;
    } // if ()

    /*
    cout << "Argnum = " << argnum << " Result = " ;
    if ( result ) cout << "TRUE" << endl ;
    else cout << "FALSE" << endl ;
    */

    EvalSexp( vec_arg.at( 0 ).stack, vec_arg.at( 0 ).stack, result, error ) ;
    
    if ( func == "'" ) {
      result = false ;
      error = "ERROR (attempt to apply non-function) : " ;
      Output.assign( vec_arg.at( 0 ).stack.begin(), vec_arg.at( 0 ).stack.end() ) ;
      return ;
    } // if ()
    
    if ( !result ) {
      Output.assign( vec_arg.at( 0 ).stack.begin(), vec_arg.at( 0 ).stack.end() ) ;
      return ;
    } // if ()

    Output.clear() ;
    func = vec_arg.at( 0 ).stack.at( 0 ).token ;

    if ( func != "(" ) {
      for ( int i = 1 ; i < vec_arg.size() ; i++ )
        for ( int j = 0 ; j < vec_arg.at( i ).stack.size() ; j++ )
          Output.push_back( vec_arg.at( i ).stack.at( j ) ) ;
    } // if ()
        
    else {
      result = false ;
      error = "ERROR (attempt to apply non-function) : " ;
      Output.assign( vec_arg.at( 0 ).stack.begin(), vec_arg.at( 0 ).stack.end() ) ;
    } // else 

  } // Start_Func()
  
  
  void Symbol_Check( string &func, string &type, vector<Token> &Data ) {
    
    vector<Token> temp, copy ;
    bool done ;
    bool change ;
    
    done = false ;
    copy.assign( Data.begin() + 2, Data.end() - 1 ) ;
    
    while ( type == "SYMBOL" && !done ) {

      change = false ;
      for ( int i = 0 ; i < mDifine.size() ; i++ ) {
        
        if ( func == mDifine.at( i ).symbol ) {
          temp.assign( mDifine.at( i ).stack.begin(), mDifine.at( i ).stack.end() ) ;
          if ( temp.size() == 1 && temp.at( 0 ).type == "SYMBOL" ) {
            change = true ;
            type = temp.at( 0 ).type ;
            func = temp.at( 0 ).token ;
          } // if ()
              
          else {
            Data.clear() ;
            
            if ( temp.size() != 0 ) {
              type = temp.at( 0 ).type ;
              func = temp.at( 0 ).token ;
              Data.assign( temp.begin(), temp.end() ) ;
            } // if ()
                
            for ( int i = 0 ; i < copy.size() ; i++ ) 
              Data.push_back( copy.at( i ) ) ;
          } // else 
          
        } // if ()

      } // for ()
      
      if ( !change ) done = true ;
      
    } // while()

  } // Symbol_Check()
  
  
  void EvalSexp( vector<Token> Input, vector<Token> &Output, bool &result, string &error ) {

    if ( !result ) return ;
    vector<Token> evalStack ;

    /*
    cout << "This is EvalSexp Input : " ;
    for ( int i = 0 ; i < Input.size() ; i++ ) 
      cout << Input.at( i ).token << " " ;
    cout << endl << endl ; 
    */


    if ( Is_ATOM( Input ) ) {

      if ( Input.at( 0 ).type != "SYMBOL" ) {
        Output.clear() ;
        Output.assign( Input.begin(), Input.end() ) ;
      } // if ()

      else {

        Token temp ;
        bool bound ;
        bound = false ;
        temp = Input.at( 0 ) ;
        
        bool change ;
        change = false ;
        bound = false ;
        
        while ( !change ) {
          for ( int i = 0 ; i < mDifine.size() ; i++ ) {
            if ( temp.token == mDifine.at( i ).symbol ) {
              Output.assign( mDifine.at( i ).stack.begin(), mDifine.at( i ).stack.end() ) ;
              bound = true ;
            } // if ()
          } // for ()
          
          change = true ;
          if ( Output.size() == 1 && Output.at( 0 ).type == "SYMBOL" 
               && temp.token != Output.at( 0 ).token ) {
            temp = Output.at( 0 ) ;
            change = false ;
          } // if ()
              
        } // while ()
            
        if ( !bound && !Is_Func( Input ) ) {
          error = "ERROR (unbound symbol) : " ;
          result = false ;
        } // if ()

      } // else 

    } // if ()


    else if ( Input.at( 0 ).token == "'" ) {
        
      result = true ;

      if ( Input.size() == 2 && Input.at( 1 ).type == "NIL" )
        Output.assign( Input.begin() + 1, Input.end() ) ;

      else if ( Input.size() == 3 && Input.at( 1 ).token == "(" && Input.at( 2 ).token == ")" )
        Output.assign( Input.begin() + 1, Input.end() ) ;

      else Output.assign( Input.begin() + 1, Input.end() ) ;
      /*
      if ( Output.at( 0 ).token == "(" && Output.at( 1 ).token == "("
           && Output.at( Output.size() - 2 ).token == ")" && Output.at( Output.size() - 1 ).token == ")" )
        Output.assign( Output.begin() + 1, Output.end() - 1 ) ;
      */
    } // else if ()


    else {
      /*
      for ( int i = 0 ; i < Input.size() ; i++ ) {
        result = false ;
        for ( int j = 0 ; j < mDifine.size() ; j++ ) {
          if ( Input.at( i ).token == mDifine.at( j ).symbol ) {
            for ( int k = 0 ; k < mDifine.at( j ).stack.size() ; k++ )
              evalStack.push_back( mDifine.at( j ).stack.at( k ) ) ;
            result = true ;
          } // if ()
        } // for ()
        if ( !result ) evalStack.push_back( Input.at( i ) ) ;
      } // for ()
      */
      
      string func, type ;
      
      type = Input.at( 1 ).type ;
      func = Input.at( 1 ).token ;
      
      if ( type == "SYMBOL" ) {
        // cout << endl ;
        // cout << "before func = " << func << endl ;
        Symbol_Check( func, type, Input ) ;
        // cout << "after func = " << func << endl ;
      } // if ()
      
      if ( Input.size() >= 3 && Input.at( 1 ).token != "(" ) 
        evalStack.assign( Input.begin() + 2, Input.end() - 1 ) ;
      if ( Input.size() >= 3 && Input.at( 1 ).token == "(" ) 
        evalStack.assign( Input.begin() + 1, Input.end() - 1 ) ;
      
      /*
      cout << "Going to Function : " << func << endl ;
      cout << "This is evalStack Input : " ;
      for ( int i = 0 ; i < evalStack.size() ; i++ ) 
        cout << evalStack.at( i ).token << " " ;
      cout << endl << endl ; 
      */
      if ( func == "(" || func == "'" ) {
        Start_Func( evalStack, func, evalStack, result, error ) ;
        if ( !result && error != "ERROR (non-list) : " ) {
          Output.assign( evalStack.begin(), evalStack.end() ) ;
          return ;
        } // if ()
      } // if ()

      /*
      cout << "Going to Function : " << func << endl ;
      cout << "This is evalStack Input : " ;
      for ( int i = 0 ; i < evalStack.size() ; i++ ) 
        cout << evalStack.at( i ).token << " " ;
      cout << endl << endl ; 
      //     funclist    //
      */
      
      if ( func == "cons" ) Func_Cons( evalStack, Output, result, error ) ;
      else if ( func == "list" ) Func_List( evalStack, Output, result, error ) ;

      else if ( func == "quote" ) Func_Quote( evalStack, Output, result, error ) ;

      else if ( func == "define" ) Func_Define( evalStack, Output, result, error ) ;

      else if ( func == "car" ) Func_Car( evalStack, Output, result, error ) ;
      else if ( func == "cdr" ) Func_Cdr( evalStack, Output, result, error ) ;

      else if ( func == "atom?" ) Func_Is_Atom( evalStack, Output, result, error ) ;
      else if ( func == "pair?" ) Func_Is_Pair( evalStack, Output, result, error ) ;
      else if ( func == "list?" ) Func_Is_List( evalStack, Output, result, error ) ;
      else if ( func == "null?" ) Func_Is_Null( evalStack, Output, result, error ) ;
      else if ( func == "integer?" ) Func_Is_Integer( evalStack, Output, result, error ) ;
      else if ( func == "real?" ) Func_Is_Real( evalStack, Output, result, error ) ;
      else if ( func == "number?" ) Func_Is_Number( evalStack, Output, result, error ) ;
      else if ( func == "string?" ) Func_Is_String( evalStack, Output, result, error ) ;
      else if ( func == "boolean?" ) Func_Is_Boolean( evalStack, Output, result, error ) ;
      else if ( func == "symbol?" ) Func_Is_Symbol( evalStack, Output, result, error ) ;


      else if ( func == "+" ) Func_Plus( evalStack, Output, result, error ) ;
      else if ( func == "-" ) Func_Minus( evalStack, Output, result, error ) ;
      else if ( func == "*" ) Func_Multiply( evalStack, Output, result, error ) ;
      else if ( func == "/" ) Func_Divide( evalStack, Output, result, error ) ;

      else if ( func == "not" ) Func_Not( evalStack, Output, result, error ) ;
      else if ( func == "and" ) Func_And( evalStack, Output, result, error ) ;
      else if ( func == "or" ) Func_Or( evalStack, Output, result, error ) ;

      else if ( func == ">" ) Func_Larger( evalStack, Output, result, error ) ;
      else if ( func == ">=" ) Func_Larger_Or_Equal( evalStack, Output, result, error ) ;
      else if ( func == "<" ) Func_Less( evalStack, Output, result, error ) ;
      else if ( func == "<=" ) Func_Less_Or_Equal( evalStack, Output, result, error ) ;
      else if ( func == "=" ) Func_Equal( evalStack, Output, result, error ) ;
      else if ( func == "string-append" ) Func_String_Append( evalStack, Output, result, error ) ;
      else if ( func == "string>?" ) Func_String_Larger( evalStack, Output, result, error ) ;
      else if ( func == "string<?" ) Func_String_Less( evalStack, Output, result, error ) ;
      else if ( func == "string=?" ) Func_String_Equal( evalStack, Output, result, error ) ;

      else if ( func == "eqv?" ) Func_Is_Eqv( evalStack, Output, result, error ) ;
      else if ( func == "equal?" ) Func_Is_Equal( evalStack, Output, result, error ) ;

      else if ( func == "begin" ) Func_Begin( evalStack, Output, result, error ) ;

      else if ( func == "if" ) Func_IF( evalStack, Output, result, error ) ;
      else if ( func == "cond" ) Func_Cond( evalStack, Output, result, error ) ;

      else if ( func == "clean-environment" ) Func_Env_Cln( evalStack, Output, result, error ) ;
      
      
      
      else if ( func == "exit" ) {

        if ( !mtop ) {
          result = false ;
          Output.clear() ;
          error = "ERROR (level of EXIT)" ;
          return ;
        } // if ()

        if ( evalStack.size() != 0 ) {
          result = false ;
          error = "ERROR (incorrect number of arguments) : " ;
          Token temp ;
          temp.type = type ;
          temp.token = func ;
          Output.clear() ;
          Output.push_back( temp ) ;
        } // if ()

      } // else if ()
      
      else {
        bool dot ;
        result = false ;
        
        dot = false ;
            
        if ( type == "SYMBOL" ) error = "ERROR (unbound symbol) : " ;
        else {

          for ( int i = 0 ; i < evalStack.size() ; i++ )
            if ( evalStack.at( i ).token == "." ) dot = true ;

          if ( dot ) error = "ERROR (non-list) : " ;
          else error = "ERROR (attempt to apply non-function) : " ;

        } // else 

        Token temp ;
        temp.type = type ;
        temp.token = func ;
        Output.clear() ;

        if ( dot ) Output.assign( Input.begin(), Input.end() ) ;
        else Output.push_back( temp ) ;

      } // else 
      
      /*
      if ( !result && mTempStack.size() == 0 ) {
        mTempStack.clear() ;
        mTempStack.assign( Input.begin(), Input.end() ) ;
      } // if ()
      */
    } // else 
        
    

  } // EvalSexp()
  
  
  // //////////////////////////////////////////////////////////////////////////////////////////////
  
  
  void Read_And_Run_Until_End( int uTestNum, bool &endtype ) {

    
    Scanner sc ;
    bool check = false ;
    int num, left, right ;
    int line_count = 0, size = 0, match_at ;
    bool eof = false, quit = false, valid = false ;

    string front, back ;
    vector<Token> c_format ;
    NodePtr head = new Node() ;
    char * str = new char[1024] ;

    
    meof = false ;
    endtype = true ;
    cin.getline( str, 90 ) ;

    while ( !quit && !eof ) {

      if ( mNextLine.empty() ) {
        line_count = line_count + 1 ;
        if ( cin.getline( str, 1000 ).eof() ) eof = true ;

        while ( Is_Space( str ) && !eof ) {
          cin.getline( str, 1000 ) ;
          if ( !cin.eof() ) line_count = line_count + 1 ;
          else eof = true ;
        } // while

        if ( eof && Is_Space( str ) ) {
          endtype = false ;
          return ;
        } // if()

        if ( !Is_Space( str ) ) sc.String_To_Token( str, mTempStack, line_count ) ;
      } // if()

      else {
        if ( check ) eof = true ;
        mTempStack.assign( mNextLine.begin(), mNextLine.end() ) ;
        mNextLine.clear() ;
      } // else

      /*
      cout << "eof = " ;
      if ( eof ) cout << "true" << endl ;
      else cout << "false" << endl ;
      cout << endl << "THIS IS TOKEN STRING before( if ( mTempStack.at( 0 ).token != ; ) )" << endl ;
      for ( int i = 0 ; i < mTempStack.size() ; i++ )
        cout << mTempStack.at( i ).token << "--(" << mTempStack.at( i ).type << ")    " ;
      cout << endl << "THIS IS TOKEN STRING" << endl << endl ;
      */
          
      if ( mTempStack.at( 0 ).token != ";" ) {
        
        match_at = 0 ;
        mCons_Symbol = false ;
        mCount = line_count ;
        
        if ( mTempStack.at( mTempStack.size() - 1 ).token == ";" )
          mTempStack.erase( mTempStack.end() ) ;
        /*
        cout << endl << "THIS IS TOKEN STRING" << endl ;
        for ( int i = 0 ; i < mTempStack.size() ; i++ )
          cout << mTempStack.at( i ).token << "--(" << mTempStack.at( i ).type << ")    " ;
        cout << endl << "THIS IS TOKEN STRING" << endl << endl ;
        */
        mCount = line_count ;
        valid = Match_Syntax( match_at ) ;
        
        // cout << "This is match_at = " << match_at << endl ;
        
        if ( mTempStack.at( 0 ).token == "(" && mTempStack.at( 1 ).token == ")" ) {
          match_at = 1 ;
          valid = true ;
        } // if ()
            
        if ( valid && mTempStack.size() >= 3 ) {
          string str1, str2, str3 ;
          str1 = mTempStack.at( 0 ).token ;
          str2 = mTempStack.at( 1 ).token ;
          str3 = mTempStack.at( 2 ).token ;
          if ( str1 == "(" && str2 == "exit" && str3 == ")" ) {
            endtype = true ;
            return ;
          } // if ()
        } // if ()
            
        if ( valid && mTempStack.size() >= 5 ) {
          string str1, str2, str3 ;
          string str4, str5 ;
          str1 = mTempStack.at( 0 ).token ;
          str2 = mTempStack.at( 1 ).token ;
          str3 = mTempStack.at( 2 ).token ;
          str4 = mTempStack.at( 3 ).type ;
          str5 = mTempStack.at( 4 ).token ;
          if ( str1 == "(" && str2 == "exit" && str5 == ")" ) {
            if ( str3 == "." && str4 == "NIL" ) {
              endtype = true ;
              return ;
            } // if()
          } // if ()
        } // if ()

        if ( valid && mTempStack.size() >= 6 ) {
          string str1, str2, str3 ;
          string str4, str5, str6 ;
          str1 = mTempStack.at( 0 ).token ;
          str2 = mTempStack.at( 1 ).token ;
          str3 = mTempStack.at( 2 ).token ;
          str4 = mTempStack.at( 3 ).token ;
          str5 = mTempStack.at( 4 ).token ;
          str5 = mTempStack.at( 5 ).token ;
          if ( str1 == "(" && str2 == "exit" && str6 == ")" ) {
            if ( str3 == "." && str4 == "(" && str5 == ")" ) {
              endtype = true ;
              return ;
            } // if()
          } // if ()
        } // if ()
            

        int last_token = mTempStack.size() - 1 ;
        /*
        if ( true ) {
          cout << "This is match_at = " << match_at << endl ;
          cout << "This is mTempStack.size() = " << mTempStack.size() << endl ;
          cout << endl << "THIS IS TOKEN STRING" << endl ;
        
          for ( int i = 0 ; i < mTempStack.size() ; i++ )
            cout << mTempStack.at( i ).token << "--(" << mTempStack.at( i ).type << ")    " ;
          cout << endl << "THIS IS TOKEN STRING" << endl << endl ;
        } // if ()
        */
    
        if ( valid && last_token >= 1 ) {
          int i, j ;
          vector<Token> refresh ;
          for ( i = 0, j = 1 ; j < mTempStack.size() ; i++, j++ ) {
            if ( mTempStack.at( i ).token == "(" && mTempStack.at( j ).token == ")" ) {
              i = i + 1 ;
              j = j + 1 ;
              mTempStack.at( i ).type = "NIL" ;
              mTempStack.at( i ).token = "()" ;
              refresh.push_back( mTempStack.at( i ) ) ;
            } // if ()
            else refresh.push_back( mTempStack.at( i ) ) ;
          } // for ()

          if ( i < mTempStack.size() )
            refresh.push_back( mTempStack.at( mTempStack.size() - 1 ) ) ;
          mTempStack.clear() ;
          mTempStack.assign( refresh.begin(), refresh.end() ) ;
        } // if ()
    
        /*
        if ( true ) {
          cout << "This is match_at = " << match_at << endl ;
          cout << "This is mTempStack.size() = " << mTempStack.size() << endl ;
          cout << endl << "THIS IS TOKEN STRING" << endl ;
        
          for ( int i = 0 ; i < mTempStack.size() ; i++ )
            cout << mTempStack.at( i ).token << "--(" << mTempStack.at( i ).type << ")    " ;
          cout << endl << "THIS IS TOKEN STRING" << endl << endl ;
        } // if ()
        */

        if ( valid && match_at == last_token ) {
          Token temp ;
          bool result ;
          bool symbol ;
          string error ;
          result = true ;
          symbol = false ;
          if ( mTempStack.size() == 1 && mTempStack.at( 0 ).type == "SYMBOL" ) symbol = true ;
          // cout << endl << mTempStack.at( 0 ).token << "--(" << mTempStack.at( 0 ).type << ")" << endl ;
          cout << "> " ;
          mTokenStack.assign( mTempStack.begin(), mTempStack.end() ) ;
          mtop = true ;
          EvalSexp( mTempStack, mTempStack, result, error ) ;

          if ( !result ) {
            cout << error ;
            if ( mTempStack.size() == 0 ) cout << endl ;
            // if ( mTempStack.size() == 0 ) mTempStack.assign( mTokenStack.begin(), mTokenStack.end() ) ;
          } // if()
              
          if ( result && mTokenStack.size() == 1 && Is_Func( mTempStack ) ) {
            temp = mTempStack.at( 0 ) ;
            temp.type = "STRING" ;
            temp.token = "#<procedure " + mTempStack.at( 0 ).token + ">" ;
            mTempStack.at( 0 ) = temp ;
          } // if ()
          
          else if ( result && mTokenStack.at( 0 ).token != "'" ) {
            vector<Token> ptr ;
              
            for ( int i = 0 ; i < mTempStack.size() ; i++ ) {
              temp = mTempStack.at( i ) ;
              ptr.clear() ;
              ptr.push_back( temp ) ;
              
              if ( Is_Func( ptr ) && temp.token != "." && temp.token != "and" && temp.token != "or"
                   && temp.token != "not" && temp.token != "quote" ) {
                temp.type = "STRING" ;
                temp.token = "#<procedure " + mTempStack.at( i ).token + ">" ;
                mTempStack.at( i ) = temp ;
              } // if ()
                  
            } // for ()

          } // else if ()
              
          else if ( error == "ERROR (attempt to apply non-function) : " ) {
            vector<Token> ptr ;
              
            for ( int i = 0 ; i < mTempStack.size() ; i++ ) {
              temp = mTempStack.at( i ) ;
              ptr.clear() ;
              ptr.push_back( temp ) ;
              
              if ( Is_Func( ptr ) && temp.token != "." && temp.token != "and" && temp.token != "or"
                   && temp.token != "not" ) {
                temp.type = "STRING" ;
                temp.token = "#<procedure " + mTempStack.at( i ).token + ">" ;
                mTempStack.at( i ) = temp ;
              } // if ()
                  
            } // for ()
          } // else if ()
          
          else ;
              
          if ( result && mTempStack.size() == 2 
               && mTempStack.at( 0 ).token == "(" && mTempStack.at( 1 ).token == ")" ) {
            temp.token = "nil" ;
            temp.type = "NIL" ;
            mTempStack.clear() ;
            mTempStack.push_back( temp ) ;
          } // if ()
              
          Pretty_Print( mTempStack ) ;
          mTempStack.clear() ;
          line_count = 0 ;
        } // if ( valid && match_at == last_token )

        else if ( valid && match_at < last_token ) {
          Token temp ;
          bool result ;
          bool symbol ;
          string error ;
          result = true ;
          symbol = false ;
          if ( mTempStack.size() == 1 && mTempStack.at( 0 ).type == "SYMBOL" ) symbol = true ;
          int column = mTempStack.at( match_at ).column + strlen( mTempStack.at( match_at ).token.c_str() ) ;
          for ( int i = match_at + 1 ; i < mTempStack.size() ; i++ ) {
            mTempStack.at( i ).line = 1 ;
            mTempStack.at( i ).column = mTempStack.at( i ).column - column ;
            temp = mTempStack.at( i ) ;
            mNextLine.push_back( temp ) ;
          } // for ()
              
          mTempStack.assign( mTempStack.begin(), mTempStack.begin() + match_at + 1 ) ;
          cout << "> " ;
          mTokenStack.assign( mTempStack.begin(), mTempStack.end() ) ;
          mtop = true ;
          EvalSexp( mTempStack, mTempStack, result, error ) ;
          
          if ( !result ) {
            cout << error ;
            if ( mTempStack.size() == 0 ) cout << endl ;
            // if ( mTempStack.size() == 0 ) mTempStack.assign( mTokenStack.begin(), mTokenStack.end() ) ;
          } // if()
              
          if ( result && mTokenStack.size() == 1 && Is_Func( mTempStack ) ) {
            temp = mTempStack.at( 0 ) ;
            temp.type = "STRING" ;
            temp.token = "#<procedure " + mTempStack.at( 0 ).token + ">" ;
            mTempStack.at( 0 ) = temp ;
          } // if ()
          
          else if ( result && mTokenStack.at( 0 ).token != "'" ) {
            vector<Token> ptr ;
              
            for ( int i = 0 ; i < mTempStack.size() ; i++ ) {
              temp = mTempStack.at( i ) ;
              ptr.clear() ;
              ptr.push_back( temp ) ;
              
              if ( Is_Func( ptr ) && temp.token != "." && temp.token != "and" && temp.token != "or"
                   && temp.token != "not" && temp.token != "quote" ) {
                temp.type = "STRING" ;
                temp.token = "#<procedure " + mTempStack.at( i ).token + ">" ;
                mTempStack.at( i ) = temp ;
              } // if ()
                  
            } // for ()

          } // else if ()
              
          else if ( error == "ERROR (attempt to apply non-function) : " ) {
            vector<Token> ptr ;
              
            for ( int i = 0 ; i < mTempStack.size() ; i++ ) {
              temp = mTempStack.at( i ) ;
              ptr.clear() ;
              ptr.push_back( temp ) ;
              
              if ( Is_Func( ptr ) && temp.token != "." && temp.token != "and" && temp.token != "or"
                   && temp.token != "not" ) {
                temp.type = "STRING" ;
                temp.token = "#<procedure " + mTempStack.at( i ).token + ">" ;
                mTempStack.at( i ) = temp ;
              } // if ()
                  
            } // for ()
          } // else if ()
          
          else ;
              
          if ( result && mTempStack.size() == 2 
               && mTempStack.at( 0 ).token == "(" && mTempStack.at( 1 ).token == ")" ) {
            temp.token = "nil" ;
            temp.type = "NIL" ;
            mTempStack.clear() ;
            mTempStack.push_back( temp ) ;
          } // if ()
              
          Pretty_Print( mTempStack ) ;
          mTempStack.clear() ;
        } // else if ( valid && match_at < last_token )
            
            
        else {
            
          if ( meof ) {
            endtype = false ;
            return ;
          } // if ()
            
          int zero = 0 ;
          cout << "> " ;
          if ( mTempStack.at( match_at ).type == "NO-CLOSING-QUOTE" ) {
            int string_size = strlen( mTempStack.at( match_at ).token.c_str() ) + 1 ;
            cout << "ERROR (no closing quote) : END-OF-LINE encountered at Line " ;
            cout << mTempStack.at( match_at ).line ;
            cout << " Column " << string_size + mTempStack.at( match_at ).column << endl << endl ;
          } // if ()
          
          else if ( merror_type == "RIGHT" ) {
            merror_type = "null" ;
            cout << "ERROR (unexpected token) : ')' expected when token at Line " ;
            cout << mTempStack.at( match_at ).line ;
            cout << " Column " << mTempStack.at( match_at ).column + 1 ;
            cout << " is >>" << mTempStack.at( match_at ).token << "<<" << endl << endl ;
          } // else if ()

          else if ( mTempStack.at( match_at ).token == ")" ) {
            cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " ;
            cout << mTempStack.at( match_at ).line ;
            cout << " Column " << mTempStack.at( match_at ).column + 1 ;
            cout << " is >>" << mTempStack.at( match_at ).token << "<<" << endl << endl ;
          } // else if ()

          else if ( mTempStack.at( match_at ).token != "(" && !Is_ATOM( match_at ) ) {
            cout << "ERROR (unexpected token) : atom or '(' expected when token at Line " ;
            cout << mTempStack.at( match_at ).line ;
            cout << " Column " << mTempStack.at( match_at ).column + 1 ;
            cout << " is >>" << mTempStack.at( match_at ).token << "<<" << endl << endl ;
          } // else if ()

          else {
            cout << "ERROR (unexpected token) : ')' expected when token at Line " ;
            cout << mTempStack.at( match_at ).line ;
            cout << " Column " << mTempStack.at( match_at ).column + 1 ;
            cout << " is >>" << mTempStack.at( match_at ).token << "<<" << endl << endl ;
          } // else
            
          line_count = 0 ;
          mTempStack.clear() ;
        } // else
        /*
        cout << "This is mNextLine.size() = " << mNextLine.size() << endl ;
        for ( int i = 0 ; i < mNextLine.size() ; i++ )
          cout << mNextLine.at( i ).token << "--(" << mNextLine.at( i ).type << ")    " ;
        cout << endl << "THIS IS TOKEN STRING" << endl << endl ;
            
        */
        if ( meof ) eof = true ;
        if ( !mNextLine.empty() && eof ) {
          check = true ;
          eof = false ;
        } // if ()
            
       
    
      } // if ( mTempStack.at( 0 ).token != ";" )
          
      else {
        mTempStack.clear() ;
      } // else

    } // while
    
    if ( eof ) endtype = false ;
    

  } // Read_And_Run_Until_End()

  void Run_Interpreter() {

    int uTestNum ;
    bool quit = false ;

    cin >> uTestNum ;
    

    cout << "Welcome to OurScheme!" << endl << endl ;

    Read_And_Run_Until_End( uTestNum, quit ) ;

    cout << "> " ;
    if ( !quit )
      cout << "ERROR (no more input) : END-OF-FILE encountered" ;
    cout << endl << "Thanks for using OurScheme!" << endl ;
    
    // if ( uTestNum == 2 ) cout << "That is uTestNum = " << uTestNum << endl ;

  } // Run_Interpreter()

}; // Parser






int main() {

  Parser parser ;
  parser.Run_Interpreter() ;

} // main()

