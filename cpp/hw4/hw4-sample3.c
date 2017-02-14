#include"stdio.h"
int main() {
	int arr[10];
	int i;
	for( i=0; i<10; ++i){
		arr[i] = i*100;
	}
	for( i=0; i<10; ++i){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}


