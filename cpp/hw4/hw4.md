% Design using C++ \
HW 1 -- Time Machine
% Yogesh Garg (yg2482@columbia.edu)
% \today

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


## Arrays

 * Resource Safety

  1. Reference Counting
    -- Circular References
  2. RIIA
  Resource type
    -- Initialization, Copy, Move, Destruction

 * Vectors -- instead of array
 * c+11 std::array dependently typed
 * type

## Notes

### Language Model

Languages and programming in general can be viewed at two levels:

* First, where you write a program keeping in mind a machine model (the C-machine model).
    + This encourages a program to think about variables, memory access, and then using loops, operations etc.
    + This is where there is variability in each run time / computations at run time
    + This is where a programmer is instructing a machine how to search for a value in a container etc.
* Second would be to define a "language model" that will enable programmers to think about language
    + user-defined types/classes
    + and how to templatize them and write generic programs.
    + This is where a programmer can instruct the compiler on how to generate code for a certain generic programming

### Analogy
* Heavy machine operators and cranes
    - They are operating a machine they "feel" using a simple interface that does their job simple for them.
    - The machine is like an extension of their arms, and enables them to do what they previously did not have the
    strength to do, but had an idea of how to do.
* Programmer and old "C-Style" programming
    - developed by creating an abstraction on the assembly language
    - Where programmers were doing pretty much similar tasks
* Programming today: Big projects, one code in many different contexts
    - another layer of abstraction, fundamently different from the assembly-to-readable language abstraction
    - Comfort associated with Google searching for you from your voice without showing you what you said first.

### Expression
* Humans have long thrived for expression, created the media of paintings, theatre, music, language, etc.
* Somewhat, paradoxically, a lot of information is lost in the process of communication
* While theatre, paintings, and music can be left for interpretaion,
* Languages, would be much rather not
* Just as one seeks verbal or visual feedback from an audience of their speech, a PL should also give
  some sort of feedback for what has been understood, if the language model is fairly more complicated
  than the semantics.
* In this regard, PL can be viewed as Communication with an idiosyncratic alien species that is efficient
  at what it does, but not very "clever" about what it "should" do.
* This motivates the idea of a compilation report, where the compiler tells us about what it understood
  as a function of what we told it to understand.


