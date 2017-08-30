#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>


#define LIMIT 12
#define SUM_MAX 50
#define MORINO
#undef MORINO

typedef long long ll;
using namespace std;



ll dp[LIMIT][SUM_MAX][SUM_MAX]; 

vector<int> prime_table = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};





int test_luc(vector<int>& a){
  int diff = 0;
  for(int i = 0; i < a.size(); i++){
    if(i % 2){
      diff += a[i];
    }else{
      diff -= a[i];
    }
  }

  return (int)(find(prime_table.begin(), prime_table.end(), diff) != prime_table.end());
}



//for any integer, we will turn it into 
vector<int> to_digits(int n){
  vector<int> digits;
  for(int i = 0; i < LIMIT; i++){
    digits.push_back(n % 10);
    n /= 10;
  }

  return digits;
}






/* BEGIN OF THE KERNEL PART OF THIS DP*/

ll get_tab(int idx, int odd_sum, int even_sum, int tight, vector<int>& digits){
  
  if(idx == 0){
    return (find(prime_table.begin(), prime_table.end(), even_sum - odd_sum)) != prime_table.end();
  }


  if(!tight && (dp[idx][odd_sum][even_sum] >= 0)){
    return dp[idx][odd_sum][even_sum];
  }


  int bd = (tight)? digits[idx-1]: 9;


  ll ans = 0;

  
  for(int i = 0; i <= bd; i++){
    int new_tight = (i == digits[idx-1])? tight : 0;

    if(idx % 2){
      ans += get_tab(idx-1, odd_sum + i, even_sum, new_tight, digits);
    }else{
      ans += get_tab(idx-1, odd_sum, even_sum + i, new_tight, digits);
    }
    
  }


  if(!tight){
    dp[idx][odd_sum][even_sum] = ans;
  }

  return ans;
}





ll _luc(vector<int>& n){
  return get_tab(n.size(), 0, 0, 1, n);
}




/* END OF THE KERNEL PART OF THIS DP*/
ll luc(int from, int to){
  vector<int> from_dg = to_digits(from);
  vector<int> to_dg =  to_digits(to);

  ll val_1 = _luc(to_dg);
  ll val_2 = _luc(from_dg);


  

  #ifdef MORINO
  cout << "to: "<< val_1 << endl;
  cout << "from: " << val_2 << endl;
  #endif
  
  return  val_1 - val_2 + test_luc(from_dg);
}
 



int main(){
  memset(dp, -1, sizeof(dp));
  int len;
  cin >> len;


  while(len > 0){
    int from, to;
    cin >> from >> to;

    cout << luc(from, to) << endl;
    
    len--;
  }

}
