// this implements the COMPLETE THE SEQ on Sphere OJ

#include <iostream>


#include <vector>


#include <algorithm>

#include <numeric>

using namespace std;







// a helper function to display the diff tower 
void print_diff_tower(vector<vector<int> > diff_tower){
  int i = 0;

  while(i < diff_tower.size()){
    int j = 0;
    while(j < diff_tower[i].size()){
      cout << diff_tower[i][j]<<"\t";
      j++;
    }

    cout <<endl;

    
    i++;
  }
  
}






//given the origin seq and 
vector<int> fabricate(vector<int> origin, int fab_len){
  vector<vector<int> > diff_tower;
  
  //first let us construct the tower from the given origin
  vector<int> current_level = origin;
  //stop the constructing until the 
  while(true){
    //check whether the current level is trivial.
    if(current_level.size()==1 || all_of(current_level.begin(), current_level.end(), [](int i){return i==0;})){
      diff_tower.push_back(current_level);
      break;
    }
    int i = 0;
    diff_tower.push_back(current_level);
    
    adjacent_difference(current_level.begin(), current_level.end(), current_level.begin());

    //then update the current_level
    current_level.erase(current_level.begin());
  }

  //print_diff_tower(diff_tower);



  //let us do the fabrication process
  vector<int> fab_out(fab_len, diff_tower.back()[0]);

  
  int end_elem = 0;
  int i = diff_tower.size()-2;
  
  while(i>=0){
    end_elem = diff_tower[i].back();
    // diff_tower.pop_back(); // first pop out the back one, then the current back is the first seq that waits to be completed  
    int j = 0;
    while(j < fab_out.size()){
      fab_out[j] += end_elem;
      end_elem = fab_out[j];
      j++;
    }


    diff_tower[i].insert(diff_tower[i].end(), fab_out.begin(), fab_out.end());
    i--;
  }


  // print_diff_tower(diff_tower);

  
  return  fab_out;

  
}


int main(){
  int len = 0;
  cin >> len;


  while(len > 0){
    int seq_len, fab_len;

    cin >> seq_len >> fab_len;

    vector<int> seq;

    int val; 
    while(seq_len > 0){
      cin >> val; 
      seq.push_back(val);
      seq_len--;
    }


    vector<int> fab = fabricate(seq, fab_len);

    int i = 0;
    while(i < fab.size()){
      cout << fab[i];

      if(i < fab.size()-1){
	cout << " ";
      }

      i++;
    }

    cout << endl;
    

    len--;
  }


  return 0;
}
