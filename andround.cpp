#include <iostream>
#include <cstring>
#include <vector>


#define MORINO
#undef MORINO
using namespace std;


// this segtree is for bit operation
int alloc_size(int n){
  int k = 1;
  n *= 2;
  while(k < n){
    k *=2;
  }

  return  k - 1;
}

int mid(int s, int e){
  return s + (e-s)/2;
}

int p(int c){
  return (c-1)/2;
}

int l_c(int p){
  return 2*p+1;
}

int r_c(int p){
  return 2*p+2;
}



class SegTree{
public:
  int* data;
  int elem_len;
  int size;
  
  SegTree(vector<int>& elem){
    elem_len = elem.size();
    size = alloc_size(elem_len);
    data = new int[size];
    memset(data, -1, size * sizeof(int));
    _construct_tree(elem, 0, elem_len - 1, 0);
  }

  ~SegTree(){
    delete [] data;
  }

  int _construct_tree(vector<int>& elem, int s, int e, int current){
    if(s == e){
      data[current] = elem[s];
      #ifdef MORINO
      cout << current << ":" << data[current] << endl;
      #endif
      return data[current];
    }

    int mid_i = mid(s, e);
    data[current] = _construct_tree(elem, s, mid_i, l_c(current)) & _construct_tree(elem, mid_i+1, e, r_c(current));
    
    #ifdef MORINO
    cout << current << ":" << data[current] << endl;
    #endif

    return data[current];
    
  }

  // here we don't need to update actually

  int _query(int q_s, int q_e, int s, int e, int current){
    if(q_s <= s && q_e >= e){
      return data[current];
    }

    if(q_s > e || q_e < s){
      return -1;
    }

    int mid_i = mid(s, e);

    return _query(q_s, q_e, s, mid_i, l_c(current)) & _query(q_s, q_e, mid_i + 1, e, r_c(current));
  }


  int query(int q_s, int q_e){
    return _query(q_s, q_e, 0, elem_len-1, 0);
  }
};


ostream& operator << (ostream& os, SegTree& t){
  int base = 2;
  for(int i = 0; i < t.size; i++){
    os << t.data[i] << " ";


    if(i == base-2){
      os << endl;
      base *= 2;
    }
  }

  return os;

  
}


void  compute_K(SegTree& t, int K, vector<int>& out){
  // which means [i-K, i+K] will always cover the cyclic array
  if(2*K+1 >= t.elem_len){
    out.resize(t.elem_len, t.data[0]);
    return;
  }

  //otherwise

  int q_s, q_e;
  for(int i = 0; i < t.elem_len; i++){
    q_s = i - K;
    q_e = i + K;

    if(q_s >= 0 && q_e <t.elem_len){
      out.push_back(t.query(q_s, q_e));
    }else{
      if(q_s < 0){
	q_s += t.elem_len;
      }else{ // which means q_e >= t.elem_len
	q_e -= t.elem_len;
      }
      out.push_back(t.query(0, q_e) & t.query(q_s, t.elem_len));
    }
    
  }

}




int main(){
  int len;
  cin >> len;
  int N, K;
  while(len > 0){
    cin >> N >> K;
    vector<int> input;
    int val;
    while(N > 0){
      cin >> val;
      input.push_back(val);
      N--;
    }

    SegTree t(input);
    vector<int> out;
    compute_K(t, K, out);

    for(int i = 0; i < out.size(); i++){
      cout << out[i];
      if(i < out.size()-1){
	cout << " ";
      }else{
	cout << endl;
      }
    }
    
    len --;
  }


  
}
