#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
using namespace std;

#define LIMIT 10001
typedef long long ll;



bool test_prime(int n){
  if(n==1){
    return false;
  }
  
  int i = 2;
  while(i <= sqrt(n)){
    if(n % i==0){
      return false; // a premature return, which means it is not prime
    }
    i++;
  }

  return true;

}



// this function generates the prime number between the begin and the end into a vector structure
vector<int> generate_prime(int begin, int end){
  vector<int> out;

  int n = begin;
  while(n <= end){
    if(test_prime(n)){
      out.push_back(n);
    }
    n++;
  }


  return out;
}



// compute the totient with gauss formula
ll totient(int k, vector<int>& prime_table){
  ll divident = k;
  ll mod_val = 1;
  int i = 0;
  while(i < prime_table.size() && prime_table[i]<= k){
    if(k % prime_table[i] == 0){
      divident *= (prime_table[i] - 1);
      mod_val *= prime_table[i];
    }
    i++;
  }


  return divident / mod_val;
}






int main(){
  int len;
  vector<int> prime_table = generate_prime(2, LIMIT);
  vector<ll> totient_table;



  // do the precompute

  for(int i = 1; i<= LIMIT; i++){
    totient_table.push_back(totient(i, prime_table));
  }

  
  partial_sum(totient_table.begin(), totient_table.end(), totient_table.begin());

  
  

  
  cin >> len;


  while(len > 0){
    int n;
    cin >> n;

    cout << totient_table[n-1] * totient_table[n-1] << endl;
    len--;
    

  }

}
