#include<vector>
#include"stdio.h"

int main(){
	std::vector<int> v;
	int i;
	for(i=0; i< 5; ++i) {
		v.push_back(100*i);
	}
	for(i=1; i< 5; i*=2) {
		v.at(i)+=1;
		printf("%d ", v.at(i));
	}
	printf("\n");
	for(i=0; i<v.size(); ++i)
		printf("%d ", v.at(i));
	printf("\n");
	return 0;
}
