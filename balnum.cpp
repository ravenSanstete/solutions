#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>

typedef long long ll;
typedef unsigned int uint;

#define LIMIT 21
#define COL 1024
#define N 10
#define MORINO
#undef MORINO
using namespace std;


ll dp[LIMIT][COL][COL];


uint term = 0x155;




void update(int i, uint& p, uint& a){
  if(!((a >> i) & 1)){ // whicm means it never appears
    a |= 1 << i;
    p |= 1 << i;
  }else{
    p ^= 1 << i;
  }
}





ll get_tab(int idx, uint p, int tight, int suffix_zero, uint a ,vector<int>& digits){
  #ifdef MORINO
  cout << "("  << idx <<"," << p << "," << a << ")" << endl;
  #endif
  if(idx == 0){
    return (((p ^ term) & a)==0);
  }


  ll prob = dp[idx][a][p];
  if(!tight && (prob >= 0)){    
    return prob;
  }

  
  int k = (tight)? digits[idx-1] : 9;

  ll val = 0;

  
  for(int i = 0; i <= k; i++){
    int new_tight = (i == digits[idx-1])? tight : 0;
    uint new_p = p;
    uint new_a = a;
   
    if(!suffix_zero || i != 0){
      update(i, new_p, new_a);
    }
    
    val += get_tab(idx-1, new_p, new_tight, suffix_zero && (i==0), new_a ,digits);
  }


  if(!tight){
    dp[idx][a][p] = val;
  }

  return val;


  
}




/* END OF THE KERNEL PART OF THE DP*/





vector<int> to_digits(ll n){
  vector<int> digits;
  while(n){
    digits.push_back(n % 10);
    n /= 10;
  }

  return digits;
}






//we count it from 1
ll _balnum(ll n){
  if(n <= 0){
    return 1;
  }

  vector<int> digits = to_digits(n);


  
  return get_tab(digits.size(), 0, 1, 1, 0, digits);
}






ll balnum(ll beg, ll end){
  ll val_a = _balnum(beg - 1);
  ll val_b = _balnum(end);

  #ifdef MORINO
  cout << "val beg:" << val_a << endl;
  cout <<"val end:" << val_b << endl;
  #endif
  
  return (val_b - val_a);

}




int main(){
  memset(dp, -1, sizeof(dp));
  int len;

  // cout << _balnum(1000000000000000000) << endl;

  cin >> len;

  while(len > 0){
    ll beg, end;
    cin >> beg >> end;
    cout << balnum(beg, end) << endl;
    len--;
  }



  return 0;

}


