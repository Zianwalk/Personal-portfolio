#include <stdio.h>

int main()
{
    char arr[10] = { '1', '2', '3' } ;
    char * ptr = &arr[1] ;
    
    printf("%s\n", arr) ; // cout << "123" ;  
    printf("%s\n", ptr) ; // cout << "23" ;
    
    // endl of course //
    
    unsigned int l0, l1, l2 ;
    unsigned int * temp = &l0 ;
    
    l0 = 0x1 ;
    l1 = l0 << 2 ;
    l2 = l1 << 8 ;
    
    printf( "This is l0 :%d\n", l0 ) ; // cout << 1 ;
    printf( "This is l1 :%d\n", l1 ) ; // cout << 4 ;
    printf( "This is l2 :%d\n", l2 ) ; // cout << 1024 ;
    printf( "This is temp :%d\n", *temp ) ; // cout << 1 ;
    
    l2 = l2 | ( *temp ) ;
    printf( "This is l2 :%d\n", l2 ) ; // cout << 1025 ;
    
    return 0;
}
