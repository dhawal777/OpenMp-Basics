#include<stdio.h>
#include<omp.h>
#define THREADS 1
int main() {
const int REPS = 1000000;
int i;
double balance = 0.0;

printf("\nYour starting bank account balance is %0.2f\n", balance);
// simulate many deposits
#pragma omp parallel for  num_threads(THREADS)    //A1
// #pragma omp parallel for private(balance) num_threads(THREADS)//B1
for (i = 0; i < REPS; i++) {
// #pragma omp atomic     
# pragma omp reduction ( + : balance )       //C1
balance += 10.0;
}

printf("\nAfter %d $10 deposits, your balance is %0.2f\n",
REPS, balance);

// simulate the same number of withdrawals
#pragma omp parallel for  num_threads(THREADS) //A2
// #pragma omp parallel for private(balance) num_threads(THREADS) //B2
for (i = 0; i < REPS; i++) {
// #pragma omp atomic                   // C2
# pragma omp reduction ( - : balance )  
balance -= 10.0;
}
// balance should be zero
printf("\nAfter %d $10 withdrawals, your balance is %0.2f\n\n",
REPS, balance);
return 0;
}
