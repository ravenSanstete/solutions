/*
The key to this problem is trying to find out a recursive formula of the residual by moving the constant term from the right side to the left and then quotient both side with the 'complex base'


*/

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

vector<int> represent(int x_r, int x_i, int b_r, int b_i){
  vector<int> out;
  vector<int> empty;


  //boundary condition
  if(x_r == 0 && x_i == 0){
    out.push_back(0);
    return out;
  }

  int c_k = x_r;
  int d_k = x_i;

  int norm = b_r*b_r + b_i*b_i;


  int i = 0;
  int max_iter = 101;
  while(i< max_iter && (c_k!=0 || d_k!=0)){
    //do the search
    int a_k = 0;
    while(a_k*a_k < norm){
      int p = (c_k-a_k)*b_r+b_i*d_k;
      int q = b_r*d_k - b_i*(c_k-a_k);

      if(p % norm == 0 && q % norm ==0){
	out.push_back(a_k); //find a_k, break;
	//update c_k, d_k
	c_k = p / norm;
	d_k = q / norm;
	break;
      }
      
      a_k++;
    }


    //check whether find one;
    if(out.size()!=(i+1)){
      return empty;
    }
    
    i++;
  }

  if(c_k == 0 && d_k ==0){
    reverse(out.begin(), out.end());
    return out;
  }


  return empty;
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
