// http://hihocoder.com/contest/hiho139

#include <stdio.h>

float prices[50];
int weights[50];

void updateMax(float price, int weight, int *max) {
    if ( weight <= *max ) return;
    int i = (int)price;
    if ( ( price - i ) < 0.1 && ( i % 5 == 0 ) ) {
        *max = weight;    
    }
}

void f(){
    int N, i, j, k;
    int max = 0;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%f%d", &prices[i], &weights[i]);
        updateMax(prices[i], weights[i], &max); 
    }
    float price;
    int weight;
    for ( i=0; i<N; i++ ) {
        for ( j=i+1; j<N; j++ ) {
            price = prices[i] + prices[j];
            weight = weights[i] + weights[j];
            updateMax(price, weight, &max);
            for ( k=j+1; k<N; k++ ) {
                updateMax(prices[k]+price, weights[k]+weight, &max);
            } 
        }
    }
    printf("%d\n", max);
}

int main() {
    int Q;
    scanf("%d", &Q);
    while( Q-- > 0 ) f();
    return 0;
}
