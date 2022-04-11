#include <stdio.h>

int main()
{
    char arr[10] = { '1', '2', '3' } ;
    char * ptr = &arr[1] ;
    
    printf("%s\n", arr) ;
    printf("%s\n", ptr) ;
    
    unsigned int l0, l1, l2 ;
    unsigned int * temp = &l0 ;
    
    l0 = 0x1 ;
    l1 = l0 << 2 ;
    l2 = l1 << 8 ;
    
    printf( "This is l0 :%d\n", l0 ) ;
    printf( "This is l1 :%d\n", l1 ) ;
    printf( "This is l2 :%d\n", l2 ) ;
    printf( "This is temp :%d\n", *temp ) ;

    return 0;
}
