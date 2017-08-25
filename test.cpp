#include <iostream>
#include <numeric>
#include <vector>

using namespace std;





int main(){
  vector<int> v = {1,3,5,7,9};
  vector<int> c(v.size());

  adjacent_difference(v.begin(), v.end(), c.begin());


  int i = 0 ;
  while(i<c.size()){
    cout<<c[i]<<" ";
    i++;
  }

  cout<<endl;
  
  return 0;
}
