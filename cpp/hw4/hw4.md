% Design using C++ \
HW 1 -- Time Machine
% Yogesh Garg (yg2482@columbia.edu)
% \today

# Time Machine


## Safer Arrays

Arrays are nice, but there are also going to be a nightmare for new programmers
to learn and even experts to debug, the reason being that it is so easy to leak
through them. This is going to become one of the most prevelant bug in the code
written in your language. Why? Here is how:

~~~{ .c .numberLines startFrom="1"
#include"stdio.h"
int main() {
	int arr[10];
	int i;
	for( i=0; i<10; ++i){
		arr[i] = i*100;
	}
	for( i=1; i<10; i*=2){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}
~~~




