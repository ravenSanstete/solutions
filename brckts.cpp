#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


#define TRANSLATE(ch) ((ch == '(')? 1: -1)

// solve this problem with an array based segment tree
const int LIMIT = 1 << 15;


// some helper functions
int r_child(int p){
  return 2*p + 2;
}

int l_child(int p){
  return 2*p + 1;
}

int get_mid(int s, int e){
  return (e+s) >> 1;
}

// compute the size of the segtree that is needed
int get_size(int n){
  int k  = 1;
  n *= 2;
  while(k < n){
    k *= 2;
  }

  return k - 1;
}

struct Node {
  int un_l; //unmatched left bracket
  int un_r; // unmatched right bracket
};

Node make_node(int l, int r){
  Node n;
  n.un_l = l;
  n.un_r = r;
  return n;
}

Node merge(Node left, Node right){
  int min_val = min(left.un_l, right.un_r);

    return make_node(left.un_l + right.un_l - min_val, left.un_r + right.un_r - min_val);
  
}



class SegTree {
public:
  Node* data ;
  int elem_len;
  int size; // the size of the segment tree structure


  SegTree(char word[LIMIT], int word_len){
    elem_len = word_len;
    size = get_size(elem_len);
    data = new Node[size];
    _construct_tree(word, 0, elem_len - 1, 0); // start from the dummy node
    
  }

  ~SegTree(){
    delete [] data;
  }


  Node _construct_tree(char word[LIMIT], int s, int e , int current){
    if(s == e){
      data[current]  = (word[s] == '(')? make_node(1, 0) : make_node(0, 1);
      return data[current];
    }

    int mid = get_mid(s, e);
    
    data[current] = merge(_construct_tree(word, s, mid, l_child(current)), _construct_tree(word, mid+1, e, r_child(current)));

    return data[current];
  }




  void _update(int s , int e,  int pos, int current){
    if(pos == s && s == e){
      if(data[current].un_l == 1){
	data[current] = make_node(0, 1);
      }else{
	data[current] = make_node(1, 0);
      }

      return;
    }

    int mid = get_mid(s, e);
    if(pos <= mid){
      _update(s, mid, pos, l_child(current));
    }else{
      _update(mid+1, e, pos, r_child(current));
    }

    data[current] = merge(data[l_child(current)], data[r_child(current)]);
    return;
  }



  void update(int pos){
    _update(0, elem_len-1, pos, 0);
  }

  bool check(){
    return (data[0].un_l == 0 && data[0].un_r == 0);
  }


  
};


ostream& operator << (ostream& os, Node& n){
  os << "(" << n.un_l << "," << n.un_r << ")";
  return os;
}


ostream& operator << (ostream& os, SegTree& t){
  int base = 2;
  for(int i = 0; i < t.size; i++){
    os << t.data[i] << "  "; 


    if(i == base-2){
      os << endl;
      base *= 2;
    }
  }

  return os;

  
}




int main(){
  // first let us deal with the input
  int len = 10;
  int word_len, query_len;
  char word[LIMIT];

  
  while(len > 0){
    scanf("%d", &word_len);
    scanf("%s", word);
    
    scanf("%d", &query_len);
    //construct the segment tree
    
    
    int op;
    
    SegTree t(word, word_len);

    //cout << t << endl;
    printf("Test %d:\n", 11 - len);
    while(query_len > 0){
      cin >> op;
      if(op == 0){
	//cout << t << endl;
	if(t.check()){
	  cout << "YES" << endl;
	}else{
	  cout << "NO" << endl;
	}
      }else{
	
	op -= 1;
        t.update(op);
	
      }
      
      query_len --;
    }
    
    


    len --;
  }

  return 0;
}
