#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

#define MORINO
#undef MORINO


#define LIMIT 2002

#define RED 1
#define BLACK 2

#define GET_COLOR(X) ((X == RED)? BLACK: RED)
using namespace std;



bool interaction[LIMIT][LIMIT];





//if it returns false, it means that the current component could not be colored without collision
bool to_color(int n, bool* observed, int* color, int source){
  // do some bfs here;
  queue<int> q;
  q.push(source);
  observed[source] = true;
  color[source] = RED;
  

  while(!q.empty()){
    int header = q.front();
    q.pop();

    //first set the observed indicator to be true
    int set_color = GET_COLOR(color[header]);
    
    for(int i = 1; i <= n; i++){
      if(interaction[header][i]){
	if(!observed[i]){
	  q.push(i);
	  observed[i] = true;
	}

	//do some coloring and check
	if(color[i] == color[header]){
	  return false; // it means collision
	}else{
	  color[i] = set_color;
	}
      }
    }
  }



  return true; // it means it can be colored properly
}





// n: the bug number
bool find_susp(int n){
  //use bfs, from any 
  bool* observed = new bool[n+1];
  int* color = new int[n+1];

  //do some initialization
  for(int i = 0; i <= n; i++){
    observed[i] = false;
    color[i] = 0;
  }

  // color[i] == false means it has not been colored,
  // observed[i] == false means it has not been observed 

  int i = 1;
  while(i <= n){
    if(!observed[i]){
      if(!to_color(n, observed, color, i)){
	delete [] observed;
	delete [] color;
	return false;
      }
      //otherwise, to check whether the next component can be colored properly
     }

    i++;
  }

  
    #ifdef MORINO
    for(int i = 1; i <= n; i++){
      cout << i <<"(" << color[i] << ")" << endl;
    }
    

    #endif



  delete [] color;
  delete [] observed; 
  return true;
}


int main(){
  int len;
  scanf("%d", &len);
  

  int bug_num, link_num;  
  for(int i = 0; i < len; i++){
    scanf("%d%d", &bug_num, &link_num);
    //initialize the array
    memset(interaction, false, sizeof(interaction));

    
    int p, q;
    for(int j = 0; j < link_num; j++){
      scanf("%d%d", &p, &q);
      interaction[p][q] = true; //set the interaction link in the array
      interaction[q][p] = true;
    }



    
    printf("Scenario #%d:\n", i+1);

    if(!find_susp(bug_num))
      cout << "Suspicious bugs found!" << endl;
    else
      cout << "No suspicious bugs found!" << endl;
  }


  
  return 0;
}
