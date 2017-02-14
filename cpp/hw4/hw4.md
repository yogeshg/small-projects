% Design using C++ \
HW 1 -- Time Machine
% Yogesh Garg (yg2482@columbia.edu)
% \today

# Time Machine

Dear Dennis

## User defined Types
Your language is going to be used very widely, it will have more applications
than you can currently imagine, amongst which will be scientific computations
for satellites and probes to other planets. Your language will be used by
expert programs but they are all human beings, and prone to making errors if
not individually, because of collaboration of efforts.

To avoid loss of many billions, people's life's worth of effort, and also to
improve the experience of expressing ideas using your programming language
safely to machine AND man, I would propose that instead of having
just the native types like integers, floats that are available currently,
please provide a facility to incorporate user defined types.

``` c
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
```

Notice how we are overloading floats to carry everything from time, distance,
velocity, to acceleration. This gives a potential for buggy code, for example
there's nothing stopping us from doing:
``` c
    for( int i=0; i < t; ++i) {
        v += a;                 // potential for bug
        d += v;                 // potential for bug
        printf("time: %d, velocity: %f, total distance: %f\n",i,v,d);
    }
```
to "optimize" because the program knows the time step is 1 second in every step.
so far, so good. But soon, someone (the program herself, or someone else
altogether) will come along and want to increase the timestep to 0.5 seconds.
``` c
    for( float i=0; i < t; i+=0.5) {
        v += a;                 // bug realised
        d += v;                 // bug realised
        printf("time: %f, velocity: %f, total distance: %f\n",i,v,d);
    }
```
``` txt
time: 0.000000, velocity: 10.000000, total distance: 110.000000
time: 0.500000, velocity: 20.000000, total distance: 310.000000
time: 1.000000, velocity: 30.000000, total distance: 610.000000
time: 1.500000, velocity: 40.000000, total distance: 1010.000000
time: 2.000000, velocity: 50.000000, total distance: 1510.000000
time: 2.500000, velocity: 60.000000, total distance: 2110.000000
time: 3.000000, velocity: 70.000000, total distance: 2810.000000
time: 3.500000, velocity: 80.000000, total distance: 3610.000000
time: 4.000000, velocity: 90.000000, total distance: 4510.000000
time: 4.500000, velocity: 100.000000, total distance: 5510.000000
time: 5.000000, velocity: 110.000000, total distance: 6610.000000
time: 5.500000, velocity: 120.000000, total distance: 7810.000000
time: 6.000000, velocity: 130.000000, total distance: 9110.000000
time: 6.500000, velocity: 140.000000, total distance: 10510.000000
time: 7.000000, velocity: 150.000000, total distance: 12010.000000
time: 7.500000, velocity: 160.000000, total distance: 13610.000000
time: 8.000000, velocity: 170.000000, total distance: 15310.000000
time: 8.500000, velocity: 180.000000, total distance: 17110.000000
time: 9.000000, velocity: 190.000000, total distance: 19010.000000
time: 9.500000, velocity: 200.000000, total distance: 21010.000000
```

Imagine how 

precisely because of how efficient it is

Arrays

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


