// here we also adpot the so-called convex hull trick but with application to a family of two-order trajectory(parabola) of the same shape 



#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
using namespace std;
typedef long long ll;


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
  //vector<double> ends; // this saves the end points, the length of which is always hull.size()-1
  int cursor;



  Envelop(){
    cursor = 0;
  }
  
  //this tries to add a line element into the hull, the new added line's slope can always be assured to be the lowest 
  void add_line(ll k, ll b){

    // if empty, just push
    if(hull.empty()){
      hull.push_back(make_line(k, b));
      return;
    }

    // if there is already a line in it, we need to calculate the end point
    if(hull.size() == 1){
      //ends.push_back((hull[0].b - b)/(double)(k - hull[0].k));
      hull.push_back(make_line(k, b));
      return;
    }

    
    //else we first push back the one
    int m ;
      
    while(hull.size() >= 2){
      m = hull.size()-1;
      if((b - hull[m-1].b)*(hull[m-1].k - hull[m].k) <= (hull[m].b - hull[m-1].b)*(hull[m-1].k - k)){
	hull.pop_back(); // pop out the last one because it becomes irrelevant
	//ends.pop_back(); // pop out the corresponding ends
	continue;
      }else{
	break; //we do not need to pop out anything
      }
    }


    m = hull.size() - 1;

    
    //finally push the new line into the hull
    hull.push_back(make_line(k, b));
    // ends.push_back((hull[m].b - b)/(double)(k - hull[m].k)); //push back the new end
    

    
  }



  // this method should never be invoked if the size of the hull is zero.
  ll query(ll x){
    if (cursor >=hull.size()){
       cursor=hull.size()-1;
    }
         
        while (cursor<hull.size()-1&&
	       hull[cursor+1].k*x+hull[cursor+1].b>hull[cursor].k*x+hull[cursor].b)
                cursor++;
        return hull[cursor].k*x+hull[cursor].b;
  }





  // this is wrong but I do not know why

  /* Alright, I understand the reason, the boundary test in the first block of this solution is important because the size of the hull will be flex.*/
  //   // this method should never be invoked if the size of the hull is zero.
  // ll query(ll x){
  //   if(hull.empty()){
  //     return LLONG_MAX;
  //   }

    
  //   if(hull.size() == 1){
  //     return hull[0].k * x + hull[0].b;
  //   }

  //   //otherwise tries to find out the candidate segment with binary search
  //   //we assure there is some element in the ends
  //   while(cursor < ends.size() && ends[cursor] < x){
  //     cursor++;
  //   }

    

  //   return hull[cursor].k * x + hull[cursor].b;
  // }
};



/* END OF IMPLEMENTATION OF CONVEX HULL TRICK DS*/


ll g(ll a, ll b, ll c, ll x){
  return a*x*x + b*x + c;
}




ll max_effectiveness(vector<ll>& effects, ll a, ll b, ll c){
  int num = effects.size();
  // first let us compute the partial sum
  partial_sum(effects.begin(), effects.end(), effects.begin());

 
  
  ll * ef_table = new ll[num+1];

  ef_table[1] = g(a,b,c,effects[0]);

  Envelop e;


  e.add_line(-2*a*effects[0], ef_table[1] + a*effects[0]*effects[0] - b*effects[0]);
  
  for(int i = 2; i <= num; i++){
    ef_table[i] = max(g(a, b, c, effects[i-1]), g(a,b,c, effects[i-1]) + e.query(effects[i-1]));
    e.add_line(-2*a*effects[i-1], a*effects[i-1]*effects[i-1] - b*effects[i-1]+ef_table[i]);

  }


  ll out =  ef_table[num];
  delete [] ef_table;
  return out;
}








int main(){
  int len;
  cin >> len;

  while(len > 0){
    int n;
    ll a, b, c;
    vector<ll> effectivenez;
    cin >> n;
    cin >> a >> b >> c;

    while(n > 0){
      ll x_i;
      cin >> x_i;
      effectivenez.push_back(x_i);

      n--;
    }

    cout << max_effectiveness(effectivenez, a, b, c) << endl;
    
    len --;
  }

  
  


  return 0;
}
