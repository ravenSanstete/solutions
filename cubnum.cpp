#include <iostream>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#define LIMIT 100001
#define PRECOMPUTE 40000
#define PRE 46


using namespace std;


//you should always be careful the superficial things, which may
//lead you across the limbo of WA and ACC
const int CUBE[PRE] = {1, 8, 27, 64, 125, 216, 343, 512, 729, 1000, 1331, 1728, 2197, 2744, 3375, 4096, 4913, 5832, 6859, 8000, 9261, 10648, 12167, 13824, 15625, 17576, 19683, 21952, 24389, 27000, 29791, 32768, 35937, 39304, 42875, 46656, 50653, 54872, 59319, 64000, 68921, 74088, 79507, 85184, 91125, 97336};


int main(){
  int n = 1;
  int i = 1;
  int *table = new int[LIMIT];

  //init the value to be zero
  for(int j = 0; j < LIMIT; j++){
    table[j] = INT_MAX;
  }

  //do some init of the table
  table[0] = 0;

  for(int k = 1; k < LIMIT; k++){
    for(int j = 0; j < PRE && k>=CUBE[j]; j++){
      table[k] = min(table[k], 1 + table[k - CUBE[j]]);
    } 
  }
  
  
  
  while(scanf("%d", &n) != EOF){
    printf("Case #%d: %d\n", i++, table[n]);
  }
  


  delete [] table;
  

  return 0;


  

}
