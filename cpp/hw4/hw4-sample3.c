#include"stdio.h"
int main() {
	int arr[] = {100,200,300,400,500};
	int i;
	for( i=1; i<10; i*=2){
		printf("%d ",arr[i]);		// potential for invalid access
	}
	printf("\n");
	return 0;
}


