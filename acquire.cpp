
// this implements the solution to the ACQUIRE problem using the convex hull trick for dp optimization


/* The convex hull trick here is useful*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <utility>



using namespace std;
typedef long long ll;


#define MORINO
#undef MORINO


#define O2_VERSION false





// this structure is mostly used for input
struct Land{
  ll w;
  ll h;
};


ostream& operator << (ostream& out, Land& a){
  out << "(" << a.w << "," << a.h << ")";
  return out;
}


bool land_h_compare(Land& a, Land& b){
  return a.h < b.h;
}



//this function ordered the lands list and remove the irrelevant things
void clean(vector<Land>& lands){
  if(lands.size()==1){
    return;
  }


  // here we ensure the size of the vector to be larger than 1
  sort(lands.begin(), lands.end(), land_h_compare);

  
  Land current_ld = lands.back();

  //then traverse from the beginning of the vector to sweep out the irrelevant lands
  int i = lands.size() - 2;

  while(i >= 0){
    if(lands[i].w <= current_ld.w){
      lands.erase(lands.begin()+i);
    }else{
      current_ld = lands[i]; //otherwise, use the current largest land to do the sweeping
    }

    i--;
  }

  
  #ifdef MORINO
  for(int i = 0; i < lands.size(); i++){
    cout << lands[i] << endl;
  }
  cout <<endl;
  #endif
}



/* BEGIN OF IMPLEMENTATION OF CONVEX HULL TRICK DS*/

// This code should be reusable


struct Line{
  ll k;
  ll b;
};



Line make_line(ll k, ll b){
  Line l;
  l.k = k;
  l.b = b;
  return l;
}




class Envelop {
public:
  vector<Line> hull; // this serves as a stack, the strict decreasing of the slope will always be garanteed
  vector<double> ends; // this saves the end points, the length of which is always hull.size()-1



  //this tries to add a line element into the hull, the new added line's slope can always be assured to be the lowest 
  void add_line(ll k, ll b){

    // if empty, just push
    if(hull.empty()){
      hull.push_back(make_line(k, b));
      return;
    }

    // if there is already a line in it, we need to calculate the end point
    if(hull.size() == 1){
      ends.push_back((hull[0].b - b)/(double)(k - hull[0].k));
      hull.push_back(make_line(k, b));
      return;
    }




    
    //else we first push back the one
    int m ;
      
    while(hull.size() >= 2){
      m = hull.size()-1;
      if((b - hull[m-1].b)*(hull[m-1].k - hull[m].k) <= (hull[m].b - hull[m-1].b)*(hull[m-1].k - k)){
	hull.pop_back(); // pop out the last one because it becomes irrelevant
	ends.pop_back(); // pop out the corresponding ends
	continue;
      }else{
	break; //we do not need to pop out anything
      }
    }


    m = hull.size() - 1;

    
    //finally push the new line into the hull
    hull.push_back(make_line(k, b));
    ends.push_back((hull[m].b - b)/(double)(k - hull[m].k)); //push back the new end
    

    
  }



  // this method should never be invoked if the size of the hull is zero.
  ll query(ll x){
    if(hull.empty()){
      return LLONG_MAX;
    }

    
    if(hull.size() == 1){
      return hull[0].k * x + hull[0].b;
    }

    //otherwise tries to find out the candidate segment with binary search
    //we assure there is some element in the ends
    int ind = lower_bound(ends.begin(), ends.end(), (double)x) - ends.begin();

    return hull[ind].k * x + hull[ind].b;
  }
};




ostream& operator << (ostream& out, Envelop& e){
  int i = 0;
  while(i < e.hull.size()){
    out <<  "y = " << e.hull[i].k << " x + "<< e.hull[i].b << endl;
    if(i < e.ends.size()){
      out << e.ends[i] << endl;
    }
    i++;
  }
  return out;
}










/* END OF IMPLEMENTATION OF CONVEX HULL TRICK DS*/


ll min_cost(vector<Land> lands){
  clean(lands);


  //after the cleaning, the vector will be thus in a height increasing and
  //weight decreasing order


  ll * cost_table = new ll[lands.size()+1];
  cost_table[0] = 0;

  
  

  
  //first implement the O^2 version
  #if O2_VERSION
  // we just implement the dp solution here without the convex hull optimization
  for(int i = 1; i <= lands.size(); i++){
    cost_table[i] = LLONG_MAX;
    for(int j = 0; j < i; j++){
      cost_table[i] = min(cost_table[i], cost_table[j] + lands[j].w * lands[i-1].h);
    }
  }
  #else
  //the o^2 version will cause a TLE, thus I will begin to implement the convex hull version
  Envelop e;

  e.add_line(lands[0].w, cost_table[0]);

  for(int i = 1; i <= lands.size(); i++){
    cost_table[i] = e.query(lands[i-1].h);
    #ifdef MORINO
    cout << "cost table "<< i << ":"<< cost_table[i] <<endl;
    #endif
    if(i < lands.size()){
      e.add_line(lands[i].w, cost_table[i]);
    }
  }



  #ifdef MORINO
  cout << e;
  #endif



  
  #endif
  
  
  ll outcome = cost_table[lands.size()];
  
  delete [] cost_table;

  
  return outcome;
}







int main(){
  int len;
  cin >> len;
  vector<Land> lands;



  while(len > 0){
    Land land;
    cin >> land.w >> land.h;
    lands.push_back(land);
    len--;
  }
  
  cout << min_cost(lands) << endl;
}
