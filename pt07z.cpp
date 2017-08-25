#include <iostream>

#define MAXI 10001
using namespace std;

bool grid[MAXI][MAXI];





int** allocate_mat(int n){
  int i, j = 0;

  int ** m = new int*[n];
  
  while(i < n){
    m[i] = new int[n];
    j = 0;
    while(j < n){
      m[i][j] = 0;
      j++;
    }
    i++;
  }

  return m;
}



int I(int n){
  return n-1;
}

int E(int i){
  return i+1;
}

void deallocate_mat(int** m, int n){
  int i = 0;
  while(i < n){
    delete [] m[i];
    i++;
  }

  delete [] m;
}




// the current_node is the index of the node
void dfs(bool m[MAXI][MAXI], int current_node, int n , int level  ,int* max_level, int* last_node , bool** visited){
  int i = current_node-1;

  (*visited)[i] = true;


  //update the visit
  if(level > *max_level){
    *max_level = level;
    *last_node = current_node;
  }

  
  int j = 0;
    
  while(j < n){
    if(m[i][j] && !(*visited)[j]){
      dfs(m, E(j), n, level+1, max_level, last_node, visited);
    }


    j++;
  }



  //reset the visited
  (*visited)[i] = false;

  

}





int longest_path(bool m[MAXI][MAXI], int n){
  int max_level = 0;
  bool* visited = new bool[n];

  

  //just start from 0;
  int last_node = 1;

  dfs(m, 1, n , 0 ,&max_level, &last_node, &visited);
  

  int n_level = 0;

  int i = 0;


  //cout << "last node: "<<last_node << ", max_level:" << max_level<<endl; 
  
  dfs(m, last_node, n, 0 ,&n_level, &last_node, &visited);

  delete [] visited;
  
  return n_level;
}






int main(){
  int N;
  cin >> N;


 
  int i = N-1;
  int p, q;
  while(i >0){
    cin >> p >> q;
    grid[p-1][q-1] = true;
    grid[q-1][p-1] = true;
    i--;
  }
  
  cout << longest_path(grid, N)<<endl;



  return 0;
}
