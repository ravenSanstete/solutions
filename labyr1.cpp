#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#define OBSERVED 'Q'
#define ANCHOR 2
#define MAXI 1001


using namespace std;

struct State{
  int x;
  int y;
};


State make_state(int x, int y){
  State s;
  s.x = x;
  s.y = y;
  return s;
}

  


void show_map(char m[MAXI][MAXI], int w, int h){
  int i = 0, j = 0;
  while(i < h){

    j=0;
    while(j < w){
      cout << m[i][j];
      j++;
    }

    cout << endl;

    i++;
  }
   

}

bool operator ==(State a, State b){
  return  (a.x == b.x) && (a.y == b.y);
}

ostream& operator << (ostream& os, State a){
  os << "("<<a.x << "," << a.y << ")" <<endl;
  return os;
}




vector<State> dfs(char m[MAXI][MAXI], int w, int h, int x, int y){
  vector<State> empty_list;
  if(x<0 || x>=w || y<0 || y>=h || m[y][x]!='.'){
    return empty_list;
  }

  m[y][x] = OBSERVED;



  vector<State> v0, v1, v2, v3;

  v0 = dfs(m, w, h, x-1, y);
  v1 = dfs(m, w, h, x+1, y);
  v2 = dfs(m, w, h, x, y-1);
  v3 = dfs(m, w, h, x, y+1);


  
  vector<State> v;
  v = v0;

  if(v.size() < v1.size()){
    v = v1;
  }

  if(v.size() < v2.size()){
    v = v2;
  }

  if(v.size() < v3.size()){
    v = v3;
  }

  m[y][x] = '.';

  v.insert(v.begin(), make_state(x, y));

  return v;
   


  
}



//first find a free block and then invoke the function above
int longest_rope(char m[MAXI][MAXI], int w, int h){
  int i = 0;
  int j = 0;

  vector<State> s;
  bool p = false;
  

  while(i < h){
    j = 0;
    while(j < w){
      if(m[i][j] == '.'){
	s = dfs(m, w, h, j, i);
	p =true;
	break;
      }

      j++;
    }

    if(p){
      break;
    }


    

    i++;
  }


  if(s.size()<=1){
    return 0;
  }

  State new_pt = s.back();

  return (int)((dfs(m, w, h, new_pt.x, new_pt.y)).size()-1);
  


}





int main(){
  int len = 0;

  cin >> len;



  int w, h;
  char m[MAXI][MAXI];

  
  while(len > 0){
    cin >> w >> h;
  


    
    int i = 0;

    while(i < h){
      int j=0;
      while(j < w){
	char c;
	cin >> c;
	m[i][j] = c;
	j++;
      }
      i++;
    }


    cout<<"Maximum rope length is "<< longest_rope(m, w, h) <<"."<<endl;
    
    len--;
  }

  

}
