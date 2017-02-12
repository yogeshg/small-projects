% Design using C++ \
HW 1 -- Time Machine
% Yogesh Garg (yg2482@columbia.edu)
% \today

# Time Machine

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
* While theatre, paintings, and music can be left for interpretaion,
* Languages, would be much rather not
* Just as one seeks verbal or visual feedback from an audience of their speech, a PL should also give
  some sort of feedback for what has been understood, if the language model is fairly more complicated
  than the semantics.
* In this regard, PL can be viewed as Communication with an idiosyncratic alien species that is efficient
  at what it does, but not very "clever" about what it "should" do.
* This motivates the idea of a compilation report, where the compiler tells us about what it understood
  as a function of what we told it to understand.


