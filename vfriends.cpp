#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


#define MORINO
#undef MORINO




// to test whether a graph can be constructed a.t the given degrees 
bool is_happy(vector<int>& degs){
  if(degs.empty()) return true; // no dog will be sad

  int highest = degs.back();

  if(highest == 0){
    return true; // which means possible
  }

  //otherwise, pop the last one
  degs.pop_back();

  if(degs.size() < highest || degs[degs.size()-highest]  < 1){
    return false; 
  }


  //otherwise, do decre and insertion
  int j = degs.size()- highest;

  while(j < degs.size()){
    degs[j]--;
    int key = degs[j];
    int k = j-1;
    while(k >= 0 && key < degs[k]){
      degs[k+1] = degs[k];
      k--;
    }

    degs[k+1] = key;
    j++;
  }
  


  #ifdef MORINO
  for(int i = 0; i < degs.size(); i++){
    cout << degs[i] << " ";
  }

  cout << endl;
  #endif
  


  return is_happy(degs);
}


int main(){
  int len;
  scanf("%d", &len);


  int n;
  
  
  while(len > 0){
    scanf("%d", &n);
    vector<int> degs;

    int deg;
    while(n > 0){
      scanf("%d", &deg);
      degs.push_back(deg);
      n--;
    }

    sort(degs.begin(), degs.end());

    
    if(is_happy(degs)){
      cout << "HAPPY" << endl;
    }else{
      cout << "SAD" << endl;
    }

    

    len --;
  }

  
  return 0;
}
