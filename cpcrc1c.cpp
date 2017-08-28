#include <iostream>
#include <cstring>
#include <vector>

#define LIMIT 10



using namespace std;




long long dp_table[LIMIT][90][2];








//for any integer, we will turn it into 
vector<int> to_digits(int n){
  vector<int> digits;
  for(int i = 0; i < LIMIT; i++){
    digits.push_back(n % 10);
    n /= 10;
  }

  return digits;
}




long long get_dp_table(int ind, int sum, int tight, vector<int>& digits){
  if(ind < 0){
    return sum; // this line is for the tight digits
  }
  if(tight == 0 && dp_table[ind][sum][tight] >= 0){
    return dp_table[ind][sum][tight];
  }


  long long val = 0;

  int k = (tight)? digits[ind] : 9;
  
  for(int i = 0; i <= k; i++){

    int new_tight = (digits[ind] == i)? tight: 0;
    val += get_dp_table(ind-1, sum + i, new_tight, digits);
  }


  
  if(!tight){
    dp_table[ind][sum][tight] = val;
  }
 
  return val;
  
  
}


// this computes the sum of the digits of numbers {1 ... n}
long _digit_sum(int n){
  vector<int> digits =to_digits(n);
  long long n_sum = get_dp_table(LIMIT-1, 0, 1, digits);
  return n_sum;
}







long long digit_sum(int a, int b){
  return _digit_sum(b) - _digit_sum(a-1);
}





int main(){
  memset(dp_table, -1, sizeof(dp_table));
  
  


  int a, b;
  cin >> a >> b;

  while(a != -1 && b != -1){
    cout << digit_sum(a,b) << endl;
    cin >> a >> b;
  }


  return 0;
}


