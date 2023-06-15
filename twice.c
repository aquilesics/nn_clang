#include <stdatomic.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] =
 {
        {0,0},
        {1,2},
        {2,4},
        {3,6},
        {4,8}
    };
#define train_count ( sizeof(train)/sizeof(train[0]) )
//model     
//y = x*w;

float  rand_float(void){
    return (float) rand()/ (float) RAND_MAX; 
};
float cost(float w,  float bias){
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i ){
        float x = train[i][0];
        float y = x*w + bias;
        float dist = y - train[i][1]; //distance
        result += dist*dist;
        // printf("actual: %f; expected: %"d"f\n",y,train[i][1]);
    }; 
    result /= train_count;
    return result;
}

int main(){
    // srand(time(0));
    srand(69);
    float w = rand_float()*10.0f;
    float b = rand_float()*5.0f;
    float eps = 1e-3;
    float rate = 1e-3;
    printf("before: %f\n",cost(w,b));

    for (size_t i = 0; i <= 10; i++ ){
        float dcost_w = ( cost( w + eps,b ) - cost(w,b)) /eps;
        float dcost_b = ( cost( w , b + eps)  - cost(w,b))/eps;

        w -= rate*dcost_w;
        b -= rate*dcost_b;
        printf("cost: %f, w=%f, b = %f\n",cost(w,b),w,b) ;
    }   

    printf("-----------------------\n");
    printf("w = %f, b = %f",w,b);

    return 0;
}