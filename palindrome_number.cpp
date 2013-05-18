#include <iostream>
#include <cstdlib>

bool is_palindrome_number(int x) {
	if( x < 0 ) { return is_palindrome_number( -x ); }

	int scale = 1;
	while( x / scale >= 10 ) {
		scale *= 10;
	}

	int l_scale = scale;
	int r_scale = 1;

	while( l_scale >= r_scale ) {
		int l = ( x / l_scale ) % 10;
		int r = ( x / r_scale ) % 10;
		if( l != r ) { return false; }
		l_scale /= 10;
		r_scale *= 10;
	}
	return true;
}

int main(int argc, char* argv[]) {
	int x = atoi( argv[1] );
	if( is_palindrome_number( x ) ) {
		std::cout<<x<<" is palindrome number"<<std::endl;
	} else {
		std::cout<<x<<" is not palindrome number"<<std::endl;
	}
}
