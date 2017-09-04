// morino will implement the problem with a segment tree

// implement the segment tree with an array



#include <iostream>
#include <vector>
#include <cmath>


typedef long long ll;

using namespace std;
#define MORINO
#undef MORINO

/* BEGIN THE IMPLEMENTATION OF THE SEGTREE*/




  

// helper function
int get_mid(int s, int e){
  return s + (e - s)/ 2;
}

int compute_size(int n){
  int k = 1;
  n *= 2;
  while(k < n){
    k *= 2;
  }

  //get the 2-exp that is the smallest which is greater or equal to n
  return k - 1;  
  
}



int parent(int i){
  return (i-1)/2;
}

int l_child(int p){
  return 2*p+1;
}

int r_child(int p){
  return 2*p+2;
}


class SegTree{
public:
  ll* data;
  int size; // size of the segtree
  int elem_num;
  

  // construct the segtree with no initial data, but only size
  SegTree(int n){
    size = compute_size(n);
    data = new ll[size];
    for(int i = 0;i < size; i++){
      data[i] = 0;
    }

    
    elem_num = n;
  }

  SegTree(vector<int>& preset){
    int n = preset.size();
    size = compute_size(n);
    data = new ll[size];
    elem_num = n;
    #ifdef MORINO
    cout << "size: " << size << endl;
    #endif
				    
     
 

    //then build the tree
    construct_tree(preset, 0, elem_num-1, 0);

  }

  ~SegTree(){
    delete [] data;
  }


  // construct the segtree structure recursively
  ll  construct_tree(vector<int>& preset, int s, int e, int current_node){

    // the terminal condition
    if(e  == s){
      data[current_node] = preset[s];
      #ifdef MORINO
      cout << current_node << ":" << data[current_node] <<  endl;
      #endif
      return data[current_node];
    }

    int mid = get_mid(s, e);

    data[current_node] = construct_tree(preset, s, mid, l_child(current_node)) + construct_tree(preset, mid+1, e, r_child(current_node));

    #ifdef MORINO
    cout << current_node << ":" << data[current_node] <<  endl;
    #endif

    return data[current_node];

  }




  void _update_value(int i, ll diff, int s, int e, int current_node){
    // we will always sure that i be in the [s, e]
    data[current_node] += diff;

    if(s == e){
      return;
    }

    

    int mid = get_mid(s , e);

    if(i <= mid){
      _update_value(i, diff, s, mid, l_child(current_node));
    }else{
      _update_value(i, diff, mid+1, e, r_child(current_node));
    }

    return;
  }


  void update_value(int i, ll diff){
    _update_value(i, diff, 0, elem_num - 1, 0);
  }



  ll _get_sum(int q_s, int q_e, int s, int e, int current_node){
    // an interval that is contained in the query interval
    if(q_s <= s && q_e >= e){
      return data[current_node];
    }


    // irrelevant interval
    if(q_e < s || q_s > e){
      return 0;
    }

    //otherwise intersection interval
    int mid = get_mid(s, e);


    return _get_sum(q_s, q_e, s, mid, l_child(current_node)) + _get_sum(q_s, q_e, mid+1, e, r_child(current_node));
  }



  ll get_sum(int q_s, int q_e){
    return _get_sum(q_s, q_e, 0, elem_num-1, 0);
  }

  
};






ostream& operator << (ostream& os, SegTree& tree){
  int base = 2;
  for(int i = 0 ; i < tree.size; i++){
     cout << tree.data[i] << " ";
     if(i == base - 2){
       cout << endl;
       base *=2;
     }


   
  }
  return os;
}

  






/* END OF THE IMPLEMENTATION OF THE SEGTREE*/








int main(){
  int pos_size, query_size;
  cin >> pos_size >> query_size;

  string command;
  int index,  x;

  SegTree t(pos_size);

  
  

  while(query_size > 0){
    cin >> command;
    cin >> index >> x;



    //add action
    if(command == "add"){
      t.update_value(index-1, x);
      //find action
    }else{
      cout << t.get_sum(index-1, x-1) << endl;
    }


    query_size --;
  }


  
  return 0;
}




