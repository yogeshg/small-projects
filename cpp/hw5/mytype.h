#include<string>
#include<iostream>

class MyType{

    public:
        MyType() {}
        void run() {
            std::cout << "MyType is doing something.\n";
            return;
        }
};


template<typename R>
concept bool Runnable = requires(R r) {
    {r.run()}->void;
};

template<Runnable RunnableType>
class Runner {

    public:
        Runner() : r() {
            r.run();
        }
        ~Runner() {
            r.run();
        }

    private:
        RunnableType r;
};



