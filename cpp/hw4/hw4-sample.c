#include"stdio.h"
int main() {
  
    float d = 10;       // meters
    float t = 10;       // seconds
    float v = 0;        // meters/second
    float a = 1;        // meters/second^2
    for( float i=0; i < t; i+=0.5) {
        v += a*t;
        d += v*t;
        printf("time: %f, velocity: %f, total distance: %f\n",i,v,d);
    }
}

