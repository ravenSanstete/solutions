#include <iostream>
#include <cstring>
#include <vector>



#define LIMIT 52
using namespace std;
typedef long long ll;


#define T 3
#define S 6
#define N 9
#define MODULE 1000000007



ll dp [LIMIT][LIMIT][LIMIT][LIMIT];




bool check_tsn(vector<int>& digits){
  int t = 0, s = 0, n = 0;
  int i = 0 ;
  while(i < digits.size()){
    if(digits[i] == T){
      t++;
    }

    if(digits[i] == S){
      s++;
    }


    if(digits[i] == N){
      n++;
    }

    
    i++;
  }


  return (t > 0) && (t == s) && (s == n);
}



vector<int> str_to_digits(string beg){
  vector<int> out;
  for(int i = beg.size()-1;  i >= 0; i--){
    out.push_back(beg[i] - '0');
  }


  return out;
}





/* BEGIN OF THE KERNEL PART OF THIS SOLUTION*/
ll get_tab(int idx, int tight, int i, int j, int k, vector<int>& digits){
  if(idx == 0){
    return (int)(i > 0 && i == j && j == k);
  }

  
  if((tight == 0) && (dp[idx][i][j][k] >= 0))
    return dp[idx][i][j][k];


  int bd = tight ? digits[idx-1] : 9;

 
  
  ll val = 0;

  
  for(int h = 0; h <= bd; h++){
    int new_tight = (digits[idx-1] == h)? tight: 0;
    
    if(h == T)
      val = (val + get_tab(idx-1, new_tight, i+1, j, k, digits)) % MODULE;
    else if(h == S)
      val = (val + get_tab(idx-1, new_tight, i, j+1, k, digits)) % MODULE;
    else if(h == N)
      val = (val + get_tab(idx-1, new_tight, i, j, k+1, digits)) % MODULE;
    else
      val = (val + get_tab(idx-1, new_tight, i, j, k, digits)) % MODULE;
  }

  
  val = val % MODULE;
  if(tight == 0){
    dp[idx][i][j][k] = val;
  }


  return val;  
}







// compute the tsn number from 1 to n
ll _tsn_num(vector<int>& n){
  ll val = get_tab(n.size(), 1, 0, 0, 0, n);

  return val % MODULE;
}


/* END OF THE KERNEL PART OF THIS SOLUTION*/






ll tsn_num(string beg, string end){
  vector<int> beg_dg = str_to_digits(beg);
  vector<int> end_dg = str_to_digits(end);
  ll val_1 = _tsn_num(end_dg);
  ll val_2 = _tsn_num(beg_dg);

  if(val_1 < val_2){
    val_1 += MODULE;
  }

  return (val_1 - val_2)% MODULE + (int)check_tsn(beg_dg);
}




int main(){
  memset(dp, -1, sizeof(dp));

  int len;
  cin >> len;
  while(len > 0){
    string beg, end;

    cin >> beg >> end;
    cout << tsn_num(beg, end) << endl;

    len --;
  }

  
  return 0;
}
