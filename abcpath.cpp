#include <iostream>
#include <vector>
#include <utility>
#define MAX 52
#define PADDING '*'
#define MORINO
#undef MORINO


#define LIMIT 26





using namespace std;








int compute_path_len(char g[MAX][MAX], bool indicator[MAX][MAX] ,int w, int h, bool init){
  // we will maintain a table of longest path;
  bool total = init;
  int iter = 1;



  bool copied [MAX][MAX];


  

  while(total && iter < LIMIT){
    total = false;

    for(int i = 0; i<= w+1; i++){
      for(int j = 0; j<=h+1; j++){
	copied[i][j] = indicator[i][j];
      }
    }

    
    for(int i = 1; i <= w; i++){
      for(int j = 1; j <= h; j++){
	indicator[i][j] = (g[i][j] == (char)('A'+iter)) && (copied[i-1][j-1] || copied[i-1][j] || copied[i-1][j+1] || copied[i][j-1] || copied[i][j+1] || copied[i+1][j-1] || copied[i+1][j] || copied[i+1][j+1]);
	total = indicator[i][j] || total;
      }
    }



    #ifdef MORINO
    cout << "NOW "<< (char)('A'+iter) << endl;
    for(int i = 1; i <= w; i++){
      for(int j = 1 ; j <= h; j++){
	cout << indicator[i][j];
      }
      cout <<endl;
    }
    

    #endif

    
    iter++;
  }
  
  
  
  return (total)? iter: iter-1;
}



int main(){
  int w, h;
  
  char grid [MAX][MAX];
  bool indicator [MAX][MAX];
  bool total = true;
  
  // vector<pair<int, int> > table;


  // // the adjacent table in clockwise order 
  // table.push_back(make_pair(-1, -1));
  // table.push_back(make_pair(-1, 0));
  // table.push_back(make_pair(-1, 1));
  // table.push_back(make_pair(0, 1));
  // table.push_back(make_pair(1, 1));
  // table.push_back(make_pair(1, 0));
  // table.push_back(make_pair(1, -1));
  // table.push_back(make_pair(0, -1));
  


  cin >> w >> h;
  int i = 1;

  while(w != 0 && h !=0){

    total = false;

    // get the initial value of the indicator matrix and the total
    for(int i = 0; i <= w+1; i++){
      for(int j = 0; j<=h+1; j++){
	if(i == 0 || j == 0 || i == w+1 || j == h+1){
	  grid[i][j] = PADDING;
	  indicator[i][j] = false;
	}else{
	  cin >> grid [i][j] ;
	  indicator[i][j] = (grid[i][j] == 'A');
	  total = total || indicator[i][j];
	}
      }    
    }

    
    #ifdef MORINO
    cout << "NOW A" << endl;
    for(int i = 1; i <= w; i++){
      for(int j = 1; j <= h; j++){
	cout << indicator[i][j];
      }

      cout << endl;
    }
    #endif

    printf("Case %d: %d\n", i  ,compute_path_len(grid, indicator ,w, h, total));


	   i++;
    cin >> w >> h;
	   
  }
}
