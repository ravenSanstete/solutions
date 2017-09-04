// this is a practice for the BIT structure

#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

/* BEGIN OF IMPLEMENTATION OF BIT */
struct BIT{
  vector<ll> data;
};



void init_bit_tree(BIT& bit_tree, int size){
  bit_tree.data.resize(size+1); // we only use the index from 1 to size
  
}




// update the value of an array element, which will lead to
// the update-parent updated
void update_bit_tree(BIT& bit_tree, int index, int val, int size){
  while(index <= size){
    bit_tree.data[index] += val;
    index += index & (-index);
  }
  return;
}


// the sum from 1 to index
ll get_sum(BIT& bit_tree, int index){
  ll sum = 0;
  while(index > 0){
    sum += bit_tree.data[index];
    index -= index & (-index);
  }

  return sum;
}


/* END OF IMPLEMENTATION OF BIT */


ll get_fan(BIT& bit_tree, int from, int end){
  return get_sum(bit_tree, end) - get_sum(bit_tree, from-1);
}






int main(){
  int pos_size, query_size;
  cin >> pos_size >> query_size;

  string command;
  int index,  x;

  BIT bit_tree;
  init_bit_tree(bit_tree, pos_size);
  

  while(query_size > 0){
    cin >> command;
    cin >> index >> x;
    if(command == "add"){
      update_bit_tree(bit_tree, index, x, pos_size);
    }else{
      cout << get_fan(bit_tree, index, x) << endl;
    }

    
    query_size --;
  }
  

}
