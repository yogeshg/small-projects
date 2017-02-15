#include<array>
#include"stdio.h"

int main(){
	std::array<int,5> arr;
	int i;
	for( i=0; i<10; ++i ){
		arr[i] = 100*i;
	}
	for(i=1; i<10; i*=2) {
		arr[i]+=1;
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
