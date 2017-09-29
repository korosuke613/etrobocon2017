#include <stdio.h>
#include <string.h>

int main ( int argc, char* argv[] ) {
	char str[64] ;
	
	system ( "make app=str" ) ;
	sprintf ( str, "mv app %s", argv[1] ) ;
	system ( str ) ;
	memset ( str, 0x00, 64 ) ;
	sprintf ( str, "cp %s e:/ev3rt/apps/", argv[1] ) ;
	system ( str ) ;

	return 0 ;
}