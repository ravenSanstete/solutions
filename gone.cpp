#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define LIMIT 10
#define SUM_MAX 100




using namespace std;
typedef long long ll;




vector<int> prime_table = {2,3,5,7,11,13,17,19,
			   23,29,31,37,41,43,47,53,59,61,67,71,73};


ll dp[LIMIT][SUM_MAX];

//for any integer, we will turn it into 
vector<int> to_digits(int n){
  vector<int> digits;
  for(int i = 0; i < LIMIT; i++){
    digits.push_back(n % 10);
    n /= 10;
  }

  return digits;
}




/* BEGIN OF THE DP PART*/



ll get_tab(int idx, int sum, int tight, vector<int>& digits){
  if(idx == 0){
    return (int)binary_search(prime_table.begin(), prime_table.end(), sum);
  }

  if(!tight && (dp[idx][sum] >= 0)){
    return dp[idx][sum];
  }


  int bd = (tight)? digits[idx-1] : 9;

  ll ans = 0;
  
  for(int i = 0; i <= bd; i++){
    int new_tight = (i == digits[idx-1])? tight : 0;
    ans += get_tab(idx-1, sum + i, new_tight, digits);
  }


  if(!tight){
    dp[idx][sum] = ans;
  }

  return ans;
}



/* END OF THE DP PART*/






ll _gone(int n){
  if(n <= 0){
    return 0;
  }

  vector<int> digits = to_digits(n);
  return get_tab(digits.size(), 0, 1, digits);

  
}





ll gone(int beg, int end){
  return _gone(end) - _gone(beg-1);
}




int main(){
  memset(dp, -1, sizeof(dp));
  int len;
  cin >> len;
  while(len > 0){
    int beg, end;
    cin >> beg >> end;


    cout << gone(beg, end) << endl;
    
    len --;
  }

}
