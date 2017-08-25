// this implements the complex basis code problem on spoj, I think this is a search problem
#define MAX_DIGIT 100
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <queue>





using namespace std;



//this serves as a state
struct State{
  vector<int> path;
  int r_r;
  int r_i;
};


// operator
bool operator < (State a, State b){
  return (a.path.size()>= b.path.size()) &&  max(abs(a.r_r), abs(a.r_i)) > max(abs(b.r_r), abs(b.r_i));
}




State new_state(int _r, int _i, vector<int> old_path){
  State s;
  s.path = old_path;
  s.r_r = _r;
  s.r_i = _i;
  return s;
}

State update_state(State s, int a_k, int base_r, int base_i){
  s.path.push_back(a_k);
  s.r_r -= a_k * base_r;
  s.r_i -= a_k * base_i;
  return s;
  
}





vector<int> represent(int x_r, int x_i, int b_r, int b_i){
  int max_norm = (int)(sqrt(b_r*b_r + b_i*b_i));
  int base_table [MAX_DIGIT][2];
  //cout << max_norm <<endl;


  // we first input the init val
  base_table[0][0] = b_r;
  base_table[0][1] = b_i;


  int i = 1;
  while(i<MAX_DIGIT){
    base_table[i][0] = base_table[i-1][0]*b_r - base_table[i-1][1]*b_i;
    base_table[i][1] = base_table[i-1][0]*b_i + base_table[i-1][1]*b_r;
    i++;
  }

  



  
  

  // do a dfs
  vector<int> empty_vec;
  
  // after constructing the table, do the search
  // let us use the bfs search



  priority_queue<State, vector<State>, less<State> > q;

  

  int a0 = 0;
  while(a0 < max_norm+1){
    State s;
    s.r_r = x_r - a0;
    s.r_i = x_i;
    s.path.push_back(a0);
    q.push(s);
    a0++;
  }


  int max_iter = 5000;

  int iter = 0;

  while(!q.empty() && iter < max_iter){
    //give the boundary condition
    State current_state = q.top();
    q.pop();
    //cout << "search "<< current_state.r_r << ":" << current_state.r_i << " level "<<current_state.path.size() <<endl; 

    //first check is it a successful terminal
    if(current_state.r_r ==0 && current_state.r_i == 0){
      reverse(current_state.path.begin(), current_state.path.end());
      return current_state.path;
    }

    int level = current_state.path.size();
    //check whether the current state is a terminal state
    if(current_state.path.size() > MAX_DIGIT){
      continue; //nothing to do then
    }

    //otherwise generate new state and insert it into the head of the
    int j = 0;
    while(j < max_norm+1){
      q.push(update_state(current_state, j, base_table[level-1][0], base_table[level-1][1]));
      j++;
    }

    iter++;
  }
  



  return empty_vec;

}











int main(){
  int len;

  cin >> len;


  while(len > 0){
    int x_r, x_i, b_r, b_i;

    cin >> x_r >> x_i >> b_r >> b_i;


    vector<int> out = represent(x_r, x_i, b_r, b_i);


    int i = 0;
    if(out.empty()){
      cout << "The code cannot be decrypted."<<endl;
      len --;
      continue;
    }

    
    while(i < out.size()){
      cout<< out[i];
      if(i!=out.size()-1){
	cout<<",";
      }else{
	cout<<endl;
      }

      i++;
    }
    
    len--;
  }

}
