// this is the redundunt version to implement the solution to play with seven
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;


#define MORINO


int tab [501][7];


// think on the contrary side

// compute the number that can not be divied by 7 and at the same time has no digit 7



void precompute(){
  tab[1][0]=1;
  tab[1][1]=2;
  tab[1][2]=2;
  tab[1][3]=1;
  tab[1][4]=1;
  tab[1][5]=1;
  tab[1][6]=1;
  for(int i = 1; i <= 500; i++){
    for(int j = 0; j < 7; j++){
      for(int k = 0; k <= 9; k++){
	if(k != 7){
	  tab[i+1][(10 * j + k) % 7] += tab[i][j];
	}
      }
    }
  }


  
  return ; // we only need to compute from 1 to [9]*n  tab[0][0] = 1;
  

}


// first write a int version to show the correctness
int seven(int n){
  #ifdef MORINO
  for(int i = 1; i <= n; i++){
    for(int j = 0; j < 7; j++){
      cout << tab[i][j] << " ";
    }
    cout << endl;
  }

  #endif
  int sum = 0;
  for(int j = 1 ; j < 7; j++){
    sum += tab[n][j];
  }
  
  return (int)pow(10, n) - sum - 1; // this minus 1 actually remove the 10^n, which has actually (n+1) digits
}


int main(){
  memset(tab, 0, sizeof(tab));
  precompute();
  int len;
  cin >> len;
  int n;
  while(len > 0){
    cin >> n;
    cout << seven(n)  << endl;
    len --;
  }
  
}
