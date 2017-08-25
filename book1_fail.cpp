#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;


typedef long long llong;

#define MORINO







// never try to modify the data in the array, @return the index of element which is the largest one smaller than the base
int binary_search(vector<llong>& arr, llong val){
  int lo = 0;
  int hi = arr.size()-1;
  int mid;

  while(lo <= hi){
    mid = (lo+hi)/2;
    if(arr[mid] == val){
      return mid+1;
    }else{
      if(val < arr[mid]){
	hi = mid -1;
      }else{
	lo = mid+1;
      }
    }
   
  }


  return lo+1;
}





//b: from where 
//@return: where to do the partition
void _partition(vector<llong> arr, llong bias, int k, vector<int>& out, llong* maxim){
  if(k==1){
    out.push_back(arr.size());
    return;
  }
  
  //two trivial case
  if(k == arr.size()){
    for(int j =0; j < k; j++){
      out.push_back(1);
    }

    return;
  }


  
  vector<llong> biasas(arr.size(), bias);

  
  // first substract each element in arr with the bias 
  transform(arr.begin(), arr.end(), biasas.begin(), arr.begin(), [](llong x, llong y)-> llong {return x-y;});

  
  #ifdef MORINO

  int mrn = 0;
  while(mrn < arr.size()){
    cout << arr[mrn] << endl;
    mrn++;
  }


  #endif

  llong base = max(arr.back()/k, *maxim);
  
  int j = binary_search(arr, base);

  

  if(j >=arr.size()){
     j = arr.size();  
  }

  if(j>=2 && arr[j-1]-base >= base - arr[j-2]){
     j = j-1;
  }


  
  if(arr.size() - j < k){
    j = arr.size() - k+1;
  }

  


  #ifdef MORINO
  cout << "BIAS: "<< bias << " AVG or MAX: "<< base << " K:" << k <<" J:"<< j << " MAX:"<<*maxim<<endl;
  #endif

  


  out.push_back(j);

  llong _bias = arr[j-1];

  

  *maxim = max(*maxim, _bias);
  
  arr.erase(arr.begin(), arr.begin()+j);

  
  
  _partition(arr, _bias, k-1, out, maxim);
  

  


  return;
  

}







void partition_array(vector<llong> arr, int k){

  // to deal with some boundary condition
  if(arr.size()==1){
    cout << arr[0] <<endl;
    return;
  }


  llong maxim = 0;
  
  vector<int> out;
  
  //first to compute the partial sum of the array
  vector<llong> c_arr = arr;

  //first reverse it
  reverse(c_arr.begin(), c_arr.end());
  

  partial_sum(c_arr.begin(), c_arr.end(), c_arr.begin());

  //after compute the partial_sum, begin the recursion
  _partition(c_arr, 0, k, out, &maxim);

  #ifdef MORINO
  int mrn = 0;
  while(mrn < out.size()){
    cout << out[mrn] << " ";
    mrn++;
  }


  cout << endl;
  #endif


  reverse(out.begin(), out.end());

  partial_sum(out.begin(), out.end(), out.begin());


  #ifdef MORINO
  mrn = 0;
  while(mrn < out.size()){
    cout << out[mrn] << " ";
    mrn++;
  }


  cout << endl;
  #endif

  // no need to have the last one
  out.pop_back();

  
  


 

  // then to do the print out
  int i = 0;
  int N = arr.size();
  while(i < arr.size()){
    cout << arr[i];

    if(i <=arr.size()-2){
      cout <<" ";
    }else{
      cout << endl;
    }
    
   
    i++;

    if(!out.empty() && i == out[0]){
      cout << "/ ";
      out.erase(out.begin());
    }
  }

}



int main(){
  int len;
  cin >> len;
  while(len > 0){
    int m, k;
    cin >> m >> k;

    llong  p;
    vector<llong> arr;
    while(m > 0){
      cin >> p;
      arr.push_back(p);
      m--;
    }

    //cout << binary_search(t, 250) <<endl;

    partition_array(arr, k);
    len--;
  }


  return 0;
}
