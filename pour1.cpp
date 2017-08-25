#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>


#define MORINO
#undef MORINO

using namespace std;



void state(int a, int b){
  cout << "STATE "<< a <<"  "<<b<<endl; 
}


int start_from(int p , int q){
  if(p<0){
    return p/q-1;
  }else{
    return p/q;
  }

}



//to find out the max step
int simulate(int a, int b, int c, int p, int q){


  //from the one which is bigger than zero
  int step = 0;



  //there should be one greater than 0

  if(p==0){
    if(q>1){
      return 2*q;
    }else{
      return q;
    }
  }else if(q==0){
    if(p>1){
      return 2*p;
    }else{
      return p;
    }
  }


  
  int pour_in, pour_out;
  int in_v, out_v;

  int  full_in = 0;
  int full_out = 0;


  //select a better situatioin
  if(p>0){
    pour_in = p;
    pour_out = abs(q);
    in_v = a;
    out_v = b;
  }else{
    pour_in = q;
    pour_out = abs(p);
    in_v = b;
    out_v = a;
  }

  #ifdef MORINO
  
  cout << "pour in TIME:"<<pour_in<<endl;
  cout << "pour out TIME:"<<pour_out<<endl;
  

  cout << "A: "<<in_v << " B:"<<out_v<<endl;

  

  //then let us do the simulation
  state(full_in, full_out);

  #endif
  
  step +=1;
  full_in = in_v;

  
  pour_in -=1;

  
  while((pour_in!=0 || pour_out!=0) && (full_in != c && full_out != c)){
    #ifdef MORINO
    state(full_in, full_out);
    #endif
    if(full_out >= out_v && pour_out > 0){
      	pour_out--;
	full_out = 0;
	step++;
	continue;
    }


    if(full_in == 0){
      full_in = in_v;
      pour_in--;
      step ++;
      continue;
    }

    //otherwise, do transfer;
    
    //transfer
    int old_full_out = full_out;
    full_out = (full_out + full_in >= out_v)? out_v: full_out+full_in ;
    full_in -= full_out - old_full_out;
    step++;

    
    #ifdef MORINO
    cout << pour_in <<":"<< pour_out<<endl;
    #endif

    
  }

  #ifdef MORINO
  state(full_in, full_out);
  #endif

  return step;

}



int pour_water(int a, int b, int c){
  //first let us implement the so-called extended euclidean algorithm to compute the special root for ax+by = gcd(a,b)


  //a boundary case
  if(a < c && b <c){
    return -1;
  }

  
  int s = 0, old_s = 1;
  int t = 1, old_t = 0;
  int r = b, old_r = a;

  int tmp, q;
  while(r!=0){
    q = old_r / r;
    tmp = r;
    r = old_r - q*r;
    old_r = tmp;


    tmp = s;
    s = old_s - q*s;
    old_s = tmp;

    tmp = t;
    t = old_t - q*t;
    old_t = tmp;
  }


  //now old_r is the greatest common divisor;

  //cout << "gcd("<<a<<","<<b<<")="<<old_r<<endl;

  //cout << "Bezout: x="<<old_s << ", y="<<old_t<<endl;

  if(c % old_r !=0){
    return -1; //which means no solution
  }else{
    //now the general solution should be
    // old_s + k*(b/old_r) // old_t - k*(a/old_r)
    int scale = c/old_r;
    old_s *= scale;
    old_t *= scale;

    int e1 = b/old_r;
    int e2 = a/old_r;

    
    int m  = start_from(-old_s, e1);
    int n  = start_from(old_t, e2);

    vector<int> out;

    out.push_back(simulate(a,b,c, old_s + m*e1, old_t - m*e2));
    out.push_back(simulate(a,b,c, old_s + (m+1)*e1, old_t - (m+1)*e2));
    out.push_back(simulate(a,b,c, old_s + n*e1, old_t - n*e2));
    out.push_back(simulate(a,b,c, old_s + (n+1)*e1, old_t - (n+1)*e2));
    
    

    return *min_element(out.begin(), out.end());
  }
}






int main(){
  int len;
  cin >> len;
  while(len > 0){
    int a, b, c;
    cin >> a >> b >> c;

    
    cout << pour_water(a,b,c)<<endl;
    
    len--;
  }
  return 0;
}
