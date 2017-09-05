// learn this data structure from @tr0j4n034's, a great algorithm designer(with an implicit segment tree)

#include <iostream>
#include <cmath>



using namespace std;
#define LIMIT (1<<30)



struct node{
  int val; //always store the max value of its child node
  node* l_child; 
  node* r_child;
};

//helper functions

node* make_node(int _val){
  node* n = new node();
  n->val = _val;
  n->l_child = NULL;
  n->r_child = NULL;

  return n;
}


int get_val(node* &n){
  return (n)? n->val : -LIMIT;  
}


int get_mid(int s, int e){
  return s + (e-s)/2;
}


// to update an index to be occupied
void _update(node* &current_node, int s, int e, int index, int val){
  if(!current_node){
    current_node = make_node(e);
  }
  
  // terminal condition
  if(s == e && e == index){
    current_node -> val = val;
    return;
  }


  //do recursion
  int mid = get_mid(s, e);

  if(index <= mid){
    _update(current_node->l_child, s, mid, index, val);
  }else{
    _update(current_node->r_child, mid+1, e, index, val);
  }

  if(!current_node -> l_child){
    current_node -> l_child = make_node(mid);
  }

  if(!current_node -> r_child){
    current_node -> r_child = make_node(e);
  }

  

  //finally maintain the property that the value of the node should be that of the greatest value among its children
  current_node -> val = max(get_val(current_node->l_child), get_val(current_node->r_child));

  return;
}




void update(node* &root, int index, int val){
  _update(root, 1, LIMIT, index, val);
}








// the index is the prefered one
int _query(node* &current_node, int s, int e, int index){
  if(s == e){
    return s; // which means we could find find the perfect one
  }

  //otherwise
  if(!current_node){
    current_node = make_node(e);
  }

  int mid = get_mid(s, e);
  if(!current_node->l_child){
    current_node->l_child = make_node(mid);
  }

  if(!current_node->r_child){
    current_node->r_child = make_node(e);
  }

  
  
  if(index <= get_val(current_node->l_child)){
    return _query(current_node->l_child, s, mid, index);
  }else{
    return _query(current_node->r_child, mid+1, e, index);
  }  
}

int query(node* &root, int index){
  return _query(root, 1, LIMIT, index);
}



void _dealloc(node* &n){
  if(!n) return;

  _dealloc(n->l_child);
  _dealloc(n->r_child);

  delete n;
}


int main(){
  node* root = NULL;

  
  int len;
  cin >> len;
  int type, index;
  while(len){
    cin >> type >> index;
    if(type == 1){
      int q = query(root, index);
      //occupy it
      update(root, q, -LIMIT);
      cout << q << endl;
    }else{
      //return the key
      update(root, index, index);
    }

    len--;
  }


  //clean the space
  _dealloc(root);
  


  
  return 0;
}
