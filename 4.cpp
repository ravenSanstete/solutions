// this file implements the infix expression to the postfix expression
// the implementation is finished but it seems the test suite on the codewar is not robust enough


#include <iostream>

#include <vector>

#include <string>

using namespace std;



string convert(string convert);


bool is_op(char c){
  return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^'); 
}


int precedence(char c){
  if(c=='+' || c=='-'){
    return 3;
  }else if(c=='*' || c=='/'){
    return 4;
  }else if(c=='^'){
    return 5;
  }

  return -1;
}


bool is_l_brac(char c){
  return c=='(';
}

bool is_r_brac(char c){
  return c==')';
}


bool is_digit(char c){
  return (c>='a' && c<='z');
}

bool is_right_assoc(char c){
  return (c=='^');
}


string convert(string infix){
  string postfix = "";
  vector<char> op_stk;
  
  int cursor = 0;
  while(cursor <infix.size()){
    char c = infix[cursor]; // current token
    if(is_digit(c)){
      postfix.push_back(c);
    }else if(is_op(c)){
      while(!is_right_assoc(c) && !op_stk.empty() && precedence(op_stk.back())>=precedence(c)){
	postfix.push_back(op_stk.back());
	op_stk.pop_back();
      }

      //push the current operator into the operator stack
      op_stk.push_back(c);
    }else if(is_l_brac(c)){
      op_stk.push_back(c);
    }else if(is_r_brac(c)){
      bool found_l_brac = false; 
      while(!op_stk.empty()){
	//which means the peeked one is the (
	if(is_l_brac(op_stk.back())){
	  op_stk.pop_back();
	  found_l_brac = true;
	  break;
	}else{
	  postfix.push_back(op_stk.back());
	  op_stk.pop_back();
	}
      }
      //no matching l bracket
      if(!found_l_brac){
	return ""; //which means an error
      }
    }

    cursor++;
  }

  //finally pop all the operator on the stack onto the postfix output

  while(!op_stk.empty()){
    if(is_l_brac(op_stk.back()) || is_r_brac(op_stk.back())){
      return ""; //non matching parentese again
    }

    postfix.push_back(op_stk.back());
    op_stk.pop_back();
  }

  return postfix;
}






int main(){
  int length = 0;
  string infix = "";
  cin >> length;
  while(length > 0){
    cin >> infix; 
    cout<< convert(infix) << endl;
    length--;
  }
  
  return 0;
}
