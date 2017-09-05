// implement monkey and apples with implicit segment tree
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


const int LIMIT = 1 << 30;




struct node{
  int count;
  node* l_child;
  node* r_child;
};

typedef node* node_t;


node_t make_node(int _count=0){
  node_t n = new node();
  
  n->count = _count;
  n->l_child = nullptr;
  n->r_child = nullptr;

  return n;
}




// to update the apple in the query range to be ripen
void _update(node_t &current_node, int q_s, int q_e, int s, int e){
  // current_node will always exist
  if(current_node->count == (e-s+1)){
    return;
  }

  if(q_s <= s && q_e >= e){
    current_node->count = e-s+1;
    return;
  }

  //init child node if not exists
  if(!current_node->l_child) current_node->l_child = make_node();
  if(!current_node->r_child) current_node->r_child = make_node();

  
  int mid = (e+s) >> 1;
  if(q_s <= mid){
    _update(current_node->l_child, q_s, min(q_e, mid), s, mid);
  }

  if(q_e >= mid+1){
    _update(current_node->r_child, max(q_s, mid+1), q_e, mid+1, e);
  }


  current_node->count = current_node->l_child->count + current_node->r_child->count;
}



// to count the apple ripen in the query range
int _count(node_t &current_node, int q_s, int q_e, int s, int e){
  if(current_node->count == 0){
    return 0; 
  }

  if(current_node->count == (e-s+1)){
    return q_e - q_s + 1;
  }

  //the two cases above ensure that the current_node won't be null

  int mid = (e+s) >> 1;
  int c = 0;

  if(q_s <= mid){
    c += _count(current_node->l_child, q_s, min(q_e, mid), s, mid);
  }

  if(q_e >= mid+1){
    c += _count(current_node->r_child, max(q_s, mid+1), q_e, mid+1, e);
  }
  
  return c;
  
}




void _deallocate(node_t &n){
  if(!n){
    return;
  }

  _deallocate(n->l_child);
  _deallocate(n->r_child);

  delete n;
}



void update(node_t &root, int q_s, int q_e){
  _update(root, q_s, q_e, 1, LIMIT);
}

int count(node_t &root, int q_s, int q_e){
  return _count(root, q_s, q_e, 1, LIMIT);
}


void deallocate(node_t &root){
  _deallocate(root);
}






int main(){
  node_t root = make_node(0);
  

  
  int len;
  scanf("%d", &len);
  
  int type, q_s, q_e;
  int c = 0;
  while(len > 0){
    scanf("%d%d%d", &type, &q_s, &q_e);
    if(type == 1){
      c = count(root, q_s+c, q_e+c);
      printf("%d\n", c);
    }else{
      update(root, q_s+c, q_e+c);
    }
    len--;
  }


  //deallocate(root);
  return 0;
  

  

}
