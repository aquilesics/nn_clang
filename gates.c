#include <stdatomic.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//OR-gate
float train[][3] =
 {
       {0,0,0},
       {1,0,1},
       {0,1,1},
       {1,1,1}
    };
#define train_count ( sizeof(train)/sizeof(train[0]) )

float  rand_float(void){
    return (float) rand()/ (float) RAND_MAX; 
};

float cost(float w1,  float w2){
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i ){
        float x1 = train[i][0];
        float x2 = train[i][1];

        float y = x1*w1 + x2*w2;
        float dist = y - train[i][2]; //distance
        result += dist*dist;
        // printf("actual: %f; expected: %"d"f\n",y,train[i][1]);
    }; 
    result /= train_count;
    return result;
}

int main(void){
    srand(69);
    float w1 = rand_float();
    float w2 = rand_float();
    float eps = 1e-3;
    float rate = 1e-3;

    for( size_t i = 0; i < 5050; ++i ){
        float c = cost(w1,  w2);
        printf("w1 = %f , w2 = %f\n",w1,w2);

        float d1 = (cost(w1 + eps, w2) - c)/eps;
        float d2 = (cost(w1, w2 + eps) - c)/eps;

        w1 -= rate*d1;
        w2 -= rate*d2;

        printf("%f\n",c);
    }
    
    return 0;
}