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

~~~{ .c .numberLines startFrom="1" }
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

I would like to propose two solutuions to avoid these kind of mistakes. First
solution will store the number of elements that a "sequence" has, and allocate
the memory required for this on the free store. There is a minimal overhead in
this solution for storing the size of the sequence, but this will enable you to
provide a safe way for your users to iterate through a sequence.

The second solution will remove this overhead and also allocate the sequence on
the heap, but will not be able to increase in size (just as arrays are intended)
but this will provide compiler additional information about the size of the
array and hence allow to check for certain errors at compile time.

### Vectors
As discussed, the vectors will store the size and point to a contiguous memory
location in the free store. This enables us to increase the size of the
sequence when required. Consider the following example:

```c++

	vector<int> v;              // allocate contiguous memory of length, say 8
                                // and initialize size=0
	for( int i=0; i<8; ++i ) {
		v.push_back(100*i);     // increment size, and save at next location
	}
    v.push_back(800);           // for the 9th element, because we do not have
                                // any more space, re allocate contiguous memory
                                // of length, say two times, 16, and then
                                // move old elements here, increment size, save
                                // at next location

    for(int a: v) {             // provide a safe way to iterate through elem
        printf("%d ", a);       // note that no unsafe access can happen
    }

    auto it=v.begin();
    for(int i=1; (it=i+v.begin())!=v.end(); i**2){
        printf("%d ", *it);     // this is a safe equivalent of the previous code
    }

```

### Arrays as a type with length

This can be used to allocate on the stack, and you can also check at compile
time if there is a potential for accessing unsafely during compiling.

```c++
    array<int,5> arr;
    arr[0];                     // should be safe to access, checkable at compile time
    arr[5];                     // unsafe, checable at run time
```

### Making Vectors default sequences

You can use the same syntax for both, but make vectors default, so that
programmers (as humans) become more inclined towards using those, as opposed
to static length arrays.

``` c++
    seq<int> s1;
    s1.push_back(100);
    s1.push_back(200);
    

    seq<int,5> s2;
    s2.push_back(100); // will throw compile time error, "push_back not supported in static length seq"
    s2[0] = s1[1] = s2[2] = s1[3] = s2[4] = 100;
    s2[5]; // will throw compile time error, "cannot access (5+1)th element of static seq of size 5"

```

Safe iterations using a "for each x in sequence" loop and iterators can be
provided.

