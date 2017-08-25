#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
#define MORINO
#undef MORINO


struct Act {
  int s;
  int e;
};




Act make_act(int _s, int _e){
  Act a;
  a.s = _s;
  a.e = _e;
  return a;
}



bool act_compare(Act a, Act b){
  return (a.e < b.e);
}




void display_act(Act a){
  cout << "(" << a.s << "," << a.e << ")" <<endl;
}





int prev(vector<int>& end_list, int start_time){
  if(end_list[0] > start_time){
    return -1;
  }


  return upper_bound(end_list.begin(), end_list.end(), start_time) - end_list.begin()-1;
}







string subset_num(vector<Act> act_list){
  ostringstream ostr;


  //first sort the list according to the end time of each activity in an increasing order
  sort(act_list.begin(), act_list.end(), act_compare);


  int i  = 0;


  //generate an array only contains the end time
  vector<int> end_list; 

  while(i < act_list.size()){
    end_list.push_back(act_list[i].e);
    #ifdef MORINO
    cout << end_list[i] << endl;
    #endif
    i++;
  }

  int * f = new int[act_list.size()]; //an array for doing the dynamic programming

  f[0] = 1;


  i = 1;
  while(i < act_list.size()){
    //let us compute the prev
    int _prev = prev(end_list, act_list[i].s);
    f[i] = (f[i-1] + 1 + ((_prev >= 0)? f[_prev]: 0)) % 100000000;
    #ifdef MORINO
    cout <<"prev: "<< _prev  << " f["<<i<<"]:" <<f[i] <<endl;
    #endif
    i++;
  }
 
  int out = f[act_list.size()-1];

  out %= 100000000;

  

  //here we begin to consider about the output
  ostringstream s_out;
  s_out << out;
  

  ostr << string(8-s_out.str().size(), '0')<<s_out.str();
 
  return ostr.str();  
}





int main(){
  int len;

  cin >> len;


  while(len>0){
    int i = 0;
    vector<Act> act_list;
    while(i < len){
      int s,e;
      cin >> s >> e;
      act_list.push_back(make_act(s,e));
      i++;
    }

    cout << subset_num(act_list) << endl;
    
    cin >> len;

  }



  return 0;
}
