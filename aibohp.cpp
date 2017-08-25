#include <iostream>
#include <algorithm>
#include <cmath>
#define MORINO
using namespace std;



// here we could be sure that a and b is of the same length
// this function computes the longest common substring of the input pair
int lcs(string a, string b){
  int a_len = a.size();
  int b_len = b.size();
  
  int ** table = new int* [a_len];

  for(int i = 0; i < a_len; i++){
    table[i] = new int[b_len];
    for(int j = 0; j < b_len; j++){
      table[i][j] = 0;
    }
    
  }


  for(int i = 0; i < a_len; i++){
    table[i][0] = (int)(a[i] == b[0]);
  }

  for(int j = 0; j < b_len; j++){
    table[0][j] = (int)(a[0] == b[j]);
  }


  for(int i = 1; i < a_len; i++){
    for(int j = 1; j < b_len; j++){
      if(a[i] == b[j]){
	table[i][j] = table[i-1][j-1] + 1;
      }else{
	table[i][j] = max(table[i][j-1], table[i-1][j]);
      }
    } 
  }


  int out = table[a_len-1][b_len-1];


  
  for(int i = 0; i < a_len; i++){
    delete [] table[i];
  }

  delete [] table;

  #ifdef MORINO
  cout << out << endl;
  #endif

  return out;
}




int min_edit_parlindrome(string s){
  string r_s = s;
  reverse(r_s.begin(), r_s.end());

  return s.size() - lcs(s, r_s);
}



int main(){
  int len;
  cin >> len;


  while(len > 0){
    string s;
    cin >> s;
    cout << min_edit_parlindrome(s) << endl;
    len--;
  }

  return 0;
}
