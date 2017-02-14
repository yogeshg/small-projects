#include"stdio.h"
#include"stdlib.h"
int main() {
	int* arr;
	arr = malloc(sizeof(arr) * 10);
	int i;
	for( i=0; i<10; ++i ){
		arr[i] = 100*i;
	}
	for( i=1; i<10; i*=2){
		printf("%d ",arr[i]);		// potential for invalid access
	}
	printf("\n");
	free(arr);
	return 0;
}


