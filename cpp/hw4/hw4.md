% Design using C++ \
HW 1 -- Time Machine
% Yogesh Garg (yg2482@columbia.edu)
% \today

<<<<<<< HEAD
\tableofcontents

# Time Machine

Dear Dennis

Your language is going to be used very widely, it will have more applications
than you can currently imagine, amongst which will be scientific computations
for satellites and probes to other planets. Your language will be used by
expert programs but they are all human beings, and prone to making errors if
not individually, because of collaboration of efforts.

## User defined Types
To avoid loss of many billions, people's life's worth of effort, and also to
improve the experience of expressing ideas using your programming language
safely to machine AND man, I would propose that instead of having
just the native types like integers, floats that are available currently,
please provide a facility to incorporate user defined types.

I will try to illustrate this with the following example:

### Correct but unsafe code
The following code is correct, but unsafe. The intention of lines 8-9 is to
increase the speed in steps of 1 second, using an acceleration value ```a```

~~~~~~{.c .numberLines startFrom="1" caption="ssup"}
#include"stdio.h"
int main() {
  
    float d = 10;                // meters
    float t = 10;                // seconds
    float v = 0;                 // meters/second
    float a = 1;                 // meters/second^2
    for( int i=0; i < t; ++i) {
        v += a*1;                // potential for bug
        d += v*1;                // potential for bug
        printf("time: %d, velocity: %f, total distance: %f\n",i,v,d);
    }
}
~~~~~~


### Incorrect and unsafe code
Notice how we are overloading floats to carry everything from time, distance,
velocity, to acceleration. This gives a potential for buggy code, for example
there is nothing that stops us from doing:

~~~~~~{.c .numberLines startFrom="8"}
    for( int i=0; i < t; ++i) {
        v += a;                 // potential for bug
        d += v;                 // potential for bug
        printf("time: %d, velocity: %f, total distance: %f\n",i,v,d);
    }
~~~~~~

to "optimize" because the program knows the time step is 1 second in every step.
so far, so good. But soon, someone (the program herself, or someone else
altogether) will come along and want to increase the timestep to 0.5 seconds.

~~~~~~{.c .numberLines startFrom="8"}
    for( float i=0; i < t; i+=0.5) {
        v += a;                 // bug realised
        d += v;                 // bug realised
        printf("time: %f, velocity: %f, total distance: %f\n",i,v,d);
    }
~~~~~~

This produces the following output, which is clearly different from the intent
of the program.

``` txt
time: 0.000000, velocity: 10.000000, total distance: 110.000000
time: 0.500000, velocity: 20.000000, total distance: 310.000000
...
time: 9.000000, velocity: 190.000000, total distance: 19010.000000
time: 9.500000, velocity: 200.000000, total distance: 21010.000000
```

### Safe and (thus) Correct code

If you can provide facility to declare explicit user defined types and rules to
operate on them, then such errors would become impossible (or atleast harder)
to make.

~~~~~~{.cpp .numberLines startFrom="1"}
#include"stdio.h"
#include"dimension.h"

typedef dimension<1,0,0> dis;       // meters
typedef dimension<0,1,0> tim;       // seconds
typedef dimension<1,-1,0> vel;      // meters/second
typedef dimension<1,-2,0> acc;      // meters/second^2

int main() {
  
    dis d = 10;
    tim t = 10;
    vel v = 0;
    acc a = 1;
    tim dt = 0.5;
    for( int i=0; dt*i < t; ++i) {
        v = v + a*dt;
        d = d + v*dt;
        printf("time: %f, velocity: %f, total distance: %f\n",dt.val,v.val,d.val);
    }
}
~~~~~~

In this case, lines 16-17 could not be written in any other way, for example
the following should throw errors:

~~~~~~{.cpp .numberLines startFrom="15"}
    for( float dt=0; dt < t; dt=dt+0.5) {
        v = v + a*dt;   // error: dimension<1,-2,0> * float not defined
        d = d + v*dt;   // error: dimension<1,-1,0> * float not defined
        printf("time: %f, velocity: %f, total distance: %f\n",dt.val,v.val,d.val);
    }
~~~~~~

~~~~~~{.cpp .numberLines startFrom="15"}
    for( tim dt=0; dt < t; dt=dt+0.5) {
        v = v + a;      // error: dimension<1,-1,0> + dimension<1,-2,0> not defined
        d = d + v;      // error: dimension<1,0,0> + dimension<1,-1,0> not defined
        printf("time: %f, velocity: %f, total distance: %f\n",dt.val,v.val,d.val);
    }
~~~~~~

## Specification of rules for dimensions

~~~~~~{.cpp .numberLines startFrom="1"}
// dimension is a type that depends on integers D, T, M
// these represent Distance units, Time units, Mass units
template<int D, int T, int M>
struct dimension {
    // it contains a value
    float val;
    // it can be initialised using a float value
    dimension(float x):val(x){};

    // you could multiply with another dimension of same units
    dimension<D,T,M> operator+(const dimension<D,T,M> another) const {
        return dimension<D,T,M> (val+another.val);
    }

    // you could compare with another dimension of same units
    bool operator<(const dimension<D,T,M> another) const {
        return (val<another.val);
    }

    // you could multiply with a scalar
    dimension<D,T,M> operator*(const float scalar) const {
        return dimension<D,T,M> (val*scalar);
    }
};

// If you want to multiply two dimensions, you will get a third dimension
// of units added up
template<int D, int T, int M, int D2, int T2, int M2>
dimension<D+D2,T+T2,M+M2> operator*( const dimension<D,T,M> a,
                                    const dimension<D2,T2,M2> b) {
        return dimension<D+D2,T+T2,M+M2> (a.val*b.val);
    }
~~~~~~


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

