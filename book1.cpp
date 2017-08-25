// this problem is actually a general version of binary search

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>


#define MORINO
#undef MORINO


typedef long long llong;


using namespace std;



//the lowest requirement of workers, given the max_heap_size
int slot_required(vector<llong> arr, llong max_heap_size){
  llong current_workload = 0;
  int required = 1;

  int i = 0 ;
  while(i < arr.size()){
    if(current_workload + arr[i] <= max_heap_size){
      current_workload += arr[i];
    }else{
      current_workload = arr[i];
      required++;
    }

    
    i++;
  }

  
  return required;
  
}



// use the binary search to find the optimum
llong minimum_workload(vector<llong> arr, int k){
  llong lo = *max_element(arr.begin(), arr.end());
  llong hi = accumulate(arr.begin(), arr.end(), 0);

  

  
  while(lo < hi){
    #ifdef MORINO
    cout << lo << ":" << hi <<endl;
    #endif
    //first check whether the mid point satisfies the predicate that will be defined in future
    llong mid = lo + (hi - lo)/2;

    int required = slot_required(arr, mid);
    //cout << required <<endl;

    //which means it is possible to distribute the workload into k heap
    if(required <= k){
      hi = mid; 
    }else{
      lo = mid+1; 
    }
  }


  return lo;
}


// this gives a proper solution to the lower bound by a relative slash position seq
vector<int> simulate(vector<llong> arr, int k, llong mini){
  vector<int> out;
  int p_k = k;

  if(k == arr.size()){
    int j = 0;
    while(j < k){
      out.push_back(1);
      j++;
    }
    return out;
  }

  //to assure that k is smaller than the arr size

  reverse(arr.begin(), arr.end());
  
  int i = 0;


  int heap_size = 0;
  llong current_wl = 0;
  int N = arr.size();
  
  while(i < arr.size()){
    #ifdef MORINO
    cout <<"pos "<<i <<" current wl:" << current_wl <<  " k:"<< k << " N-i:"<<N-i<<endl;
    #endif
    if(current_wl + arr[i] <= mini){
      ///which means the size decreases
      current_wl += arr[i];
      heap_size ++;
      if(i<arr.size()-1 && k>=N-i){
	//which means we need to break the loop by first push the current_wl
	k--;
	out.push_back(heap_size);
	int j = 0;
	while(j < k){
	  out.push_back(1);
	  j++;
	}
	heap_size = 0;
	break;
      }
    }else{ //otherwise, we only need to reduce the element
      current_wl = arr[i];
      out.push_back(heap_size);
      heap_size = 1;
      k--;
    }

    i++;
  }

  if(heap_size != 0){
    out.push_back(heap_size);
  }


  return out;
}



// k is called the parition number
void partition_array(vector<llong> arr, int k){
  if(arr.size()==1){
    cout << arr[0] << endl; // a trivial case
    return;
  }

  
  llong mini = minimum_workload(arr, k);

  #ifdef MORINO
  cout << mini <<endl;
  #endif

  //we then find out the possible assignment from the end to the beginning
  vector<int> slash_pos = simulate(arr, k, mini);





  #ifdef MORINO
  int mrn = 0 ;
  while(mrn < slash_pos.size()){
    cout << slash_pos[mrn] << " ";
    mrn ++;
  }

  cout << endl;
  #endif
  

  reverse(slash_pos.begin(), slash_pos.end());
    partial_sum(slash_pos.begin(), slash_pos.end(), slash_pos.begin());
    slash_pos.pop_back();

    
    int i = 0;
    while(i < arr.size()){
      cout << arr[i];

      if(i <=arr.size()-2){
	cout <<" ";
      }else{
	cout << endl;
      }
    
   
      i++;

      if(!slash_pos.empty() && i == slash_pos[0]){
	cout << "/ ";
	slash_pos.erase(slash_pos.begin());
      }
    }
  



  

  

  return ;

  

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

    partition_array(arr, k);
    len--;
  }


  return 0;
}
