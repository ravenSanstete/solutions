#include <iostream>


typedef long long ll; 

#define MORINO
#undef MORINO



using namespace std;



ll or_of_subseq(string sub, string s){
  int sub_len = sub.size();
  int s_len = s.size();

  
  ll ** table = new ll*[s_len+1];
  for(int i = 0; i <= s_len; i++){
    table[i] = new ll[sub_len+1];
    table[i][0] = 1; // init value;
    if(i == 0){
      for(int j = 1; j <= sub_len; j++){
	table[i][j] = 0;
      }
    }
  }


  // let us begin the construction of the table
  // from top -> bottom, left -> right


  // the recursion formula
  for(int j = 1; j <= sub_len; j++){
    for(int i = 1; i <= s_len; i++){
      table[i][j] = table[i-1][j];
      if(s[s_len - i] == sub[sub_len - j]){
	table[i][j] += table[i-1][j-1];
      }
    }
  }



  // print out the table
  #ifdef MORINO
  cout <<"  ";
  for(int j = 0; j <= sub_len; j++){
    if(j == 0){
      cout << ". ";
    }else{
      cout << sub[j-1] << " ";
    }
  
  }
  cout << endl;
  for(int i = 0; i <= s_len; i++){
    if(i == 0){
      cout << ". "; 
    }else{
      cout << s[i-1] << " ";
    }
    for(int j = 0; j <= sub_len; j++){
      cout << table[i][j] << " ";
    }
    cout << endl;
  }
  #endif
 

  ll out = table[s_len][sub_len];
  

  for(int i = 0; i <= s_len; i++){
    delete [] table[i];
  }
  
  delete [] table;

  return out;
}






int main(){
  string subseq = "KEK";


  int len;
  cin >> len;

  string seq;
  while(len > 0){
    cin >> seq;
    cout << or_of_subseq(subseq, seq) << endl;
    len --;
  }

  
  return 0;

}
