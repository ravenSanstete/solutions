#include <iostream>
#include <cmath>
#include <time.h>

#define OBSERVED 2
#define ANCHOR 2


using namespace std;



int** allocate_map(int w, int h){
  int** m = new int* [h];
  int j = 0;
  while(j < h){
    m[j] = new int[w];
    j++;
  }

  return m;
}



void dealloc_map(int** m, int w, int h){
  int j = 0;
  while(j < h){
    delete [] (m[j]);

    j++;
  }



  delete [] m;

  return;

}





void show_map(int** m, int w, int h){
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



// begin from x, y and has no restriction about searching direction
int bfs(int** map, int w, int h, int x, int y){
  int max_len = 0;

  int tmp = 0;

  map[y][x] = OBSERVED;

  int dist[4] = {0,0,0,0};
  // only if it is not observed, we should then search it
  if(x-1>=0 && map[y][x-1]==0){
    dist[0] =1+ bfs(map, w, h, x-1, y);
  }
  
  if(x+1<w && map[y][x+1]==0){
    dist[2] = 1+bfs(map, w, h, x+1, y);
  }

 

  
  if(y-1 >=0 && map[y-1][x]==0){
    dist[1]  = 1+ bfs(map, w, h, x, y-1);
  }

  

  
  if(y+1 < h && map[y+1][x]==0){
    dist[3] = 1+ bfs(map, w, h, x, y+1);
  }


  int j = 0;
  int max_ind = -1;
  while(j < 4){
    if(dist[j] > max_len){
      max_len = dist[j];
      max_ind = j;
    }
    j++;
  }



  map[y][x] = 0;
 
  return max_len;
}





// this tries to find out the longest path from a given point 
int bfs_from(int** map, int w, int h, int x, int y){
  //first set the current point to be observed

  
  // the longest path on four distinct direction
  int dist [4] = {-1,-1,-1,-1};

  map[y][x] = 2;

  if(x-1>=0 && map[y][x-1]==0){
    dist[0] = bfs(map, w, h, x-1, y);
  }

  if(x+1<w && map[y][x+1]==0){
    dist[2] = bfs(map, w, h, x+1, y);
  }

  if(y-1 >=0 && map[y-1][x]==0){
    dist[1] = bfs(map, w, h, x, y-1);
  }

  if(y+1 < h && map[y+1][x]==0){
    dist[3] = bfs(map, w, h, x, y+1);
  }

  map[y][x] = 0;

  //try to find the largest two in 4
  int max_1 = -1, max_2 = -1;
  int i = 0;
  
  while(i < 4){


    //cout << "dist:" <<dist[i] << endl;
    if(dist[i] >= max_1){
      max_2 = max_1;
      max_1 = dist[i];
      i++;
      continue;
    }

    if(dist[i] >= max_2){
      max_2 = dist[i];
    }

    i++;
  }

  if(max_1>=0 && max_2>=0){
    return max_1 + max_2 +2;
  }else if(max_1 >=0){
    return max_1+1;
  }else{
    return 0;
  }


  

  //cout << max_1 << ":" << max_2<<endl;


}



int nbr_num(int** map, int w, int h, int x, int y){
  int num = 4;
  if(x-1>=0 && map[y][x-1]!=0){
    num--;
  }

  if(x+1<w && map[y][x+1]!=0){
    num--;
  }

  if(y-1 >=0 && map[y-1][x]!=0){
    num--;
  }

  if(y+1 < h && map[y+1][x]!=0){
    num--;
  }


  return num;
}



//first find a free block and then invoke the function above
int longest_rope(int** m, int w, int h){
  int i = 0;
  int j = 0;
  bool p = false;

  int max_l = 0;

  

  while(i < h){
    j = 0;
    while(j < w){
      if(m[i][j] == 0){
	max_l = max(max_l, bfs_from(m, w, h, j, i));
      }

      j++;
    }

    
    i++;

  }





  //cout << j << ":"<< i <<endl;




  return max_l;
  


}






int main(){
  int len = 0;

  cin >> len;



  int w, h;
  while(len > 0){
    cin >> w >> h;
  
 
    int** m = allocate_map(w, h);
    int i = 0;

    while(i < h){
      int j=0;
      while(j < w){
	char c;
	cin >> c;
	m[i][j] = (c == '#')? 1:0;

	j++;
      }


     
      i++;
    }

    //show_map(m, w, h);


    

    cout<<"Maximum rope length is "<< longest_rope(m, w, h) <<"."<<endl;



    //show_map(m, w, h);
    dealloc_map(m, w, h);
    
    
    len--;
  }

  

}
