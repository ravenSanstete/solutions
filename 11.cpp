//Implement the socalled legendre formula to compute the trailing zero
#include <iostream>
#include <cmath>


using namespace std;




long long compute_expo(long long n, int p){
  long long expo = 0;

  long long  current_num = n/p;
  while(current_num !=0){
    expo += current_num;
    current_num /= p;
  }


  return expo;
}




long long trailing_zero(long long n){
  return min(compute_expo(n, 2), compute_expo(n,5));
}


int main(){
  int len;
  
  cin >> len;


  long long n;
  while(len > 0){
    cin >> n;
    cout << trailing_zero(n)<< endl;
    len--;
  }
  return 0;
}
