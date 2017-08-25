#include <iostream>
#include <vector>
#include <cmath>

using namespace std;



bool test_prime(long long n){
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
vector<long long> generate_prime(long long begin, long long end){
  vector<long long> out;

  long long n = begin;
  while(n <= end){
    if(test_prime(n)){
      out.push_back(n);
    }
    n++;
  }


  return out;

}




int main(){
  int length = 0;

  cin >> length;
  long long begin, end;
  vector<long long> results;
  
  while(length >0){
    cin >> begin >> end;
    results = generate_prime(begin, end);
    //do the print

    vector<long long>::iterator iter = results.begin();
    while(iter != results.end()){
      cout << *iter << endl;
      iter++;
    }

    cout << " "<<endl;
    length--;
  }

  return 0;
}
