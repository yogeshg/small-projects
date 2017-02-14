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
    for( tim dt=0; dt < t; dt=dt+0.5) {
        v = v + a*dt;
        d = d + v*dt;
        printf("time: %f, velocity: %f, total distance: %f\n",dt.val,v.val,d.val);
    }
}

