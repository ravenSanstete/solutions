#include <iostream>
#include <sstream>

#define FACE 6
#define MORINO
#undef MORINO


using namespace std;


/* the first index of the sum table means the time of */







double dice(int n, int k){
  if(n > 545 && k>1908){
    return 0;
  }
  //this is a quite general problem if we can let the face of dice to be of arbitrary number
  if(FACE*n <= k){
    double out = (double)FACE*n==k;
    int i = 0;
    while(i < n){
      out /= 6.0;
      i++;
    }
    return out;
  }

  
  if(n >= k){
    double out = (double)n==k;
    int i = 0;
    while(i < n){
      out /= 6.0;
      i++;
    }

    return out;	     
  }

  if(n==1){
    return (double)(k<=FACE)/6.0;
  }


  double** sum_table = new double*[n+1];

  for(int i = 0; i<=n; i++){
    sum_table[i] = new double[k+1];
    for(int j = 0; j <=k; j++){
      sum_table[i][j] = 0;
    }

  }
  

  for(int i = 1; i <= n; i++){
    for(int j = 1; j<= k; j++){
      sum_table[i][j] = 0;
    }
  }

  //here n is always larger than 2
  
  //initialize the table
  int i = 0;
  while(i < FACE){
    sum_table[1][i+1] = 1.0/6.0; // let the (1,  1 ... 6) to be 1
    i++;
  }


  
  for(int p =2; p<=n; p++){
    for(int q = 1; q <=k; q++){
      for(int i = 1; i<= FACE && i < q; i++){
	sum_table[p][q] += sum_table[p-1][q-i]/6.0;
      }
    }
  }


  #ifdef MORINO
  for(int i = 1;  i<=n; i++){
    for(int j = 1; j<=k; j++){
      cout << sum_table[i][j]<<" ";
    }

    cout << endl;
  }
  #endif

  #ifdef MORINO
  cout << sum_table[n][k] << endl;
  #endif
  
  return sum_table[n][k];
}




int format_dice(int n, int k){
  double ways = dice(n, k);

  return (int)(ways*100);
}







int main(){
  int len;
  cin >> len;

  int n, k;
  while(len > 0){
    cin >> n >> k;

    cout << format_dice(n, k) <<endl;
    len--;
  }

}
