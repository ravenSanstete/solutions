// this implements the problem 6 ARITH on spoj


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MORINO
#undef MORINO


#define BLANK ' '

// helper functions
int dtoi(char n){
  return n-'0';
}

string itos(int i){
  ostringstream ostr;
  ostr << (char)(i+'0');
  return ostr.str();
}


string morino_reverse(string s){
  reverse(s.begin(), s.end());

  return s;
}


string trim_right_zero(string s){
  int i = s.find_last_not_of("0");
  return s.substr(0,i+1);
}

// to preprocess the input data
vector <string> decompose_arith(string line){
  vector<string> out;
  int i = line.find_first_of("+-*");

  out.push_back(line.substr(0, i));
  out.push_back(line.substr(i,1));
  out.push_back(line.substr(i+1, string::npos));


  return out;

}




// functions for processing arithm. ops

// a+b is promised
string add_large(string a, string b){
  string longer = "";
  string shorter = "";

  #ifdef MORINO
  cout << "ADD "<< a << " "<<b<<endl;

  #endif
  
  if(a.size()>b.size()){
    longer = morino_reverse(a);
    shorter = morino_reverse(b);
  }else{
    longer = morino_reverse(b);
    shorter = morino_reverse(a);
  }



  
  int remainder = 0; //this is for storing the overflowed value;

  int i = 0;

  string c = ""; //use to store the result

  int current_sum = 0;
  while(i<longer.size()){
    if(i<shorter.size()){
      current_sum = dtoi(longer[i])+ dtoi(shorter[i])+remainder;
    }else{
      current_sum = dtoi(longer[i])+remainder;
    }

    c += itos(current_sum % 10);

    remainder = (current_sum/10);

    if(i >= shorter.size() && remainder==0){
      //which means we only need to copy from the next position to the end
      c += longer.substr(i+1, string::npos);
      break;
    }
    i++;
  }

  if(remainder!=0){
    c += itos(remainder);
  }

  string outcome = morino_reverse(c);

  #ifdef MORINO
  cout <<"OUT "<<outcome<<endl;
  #endif
  return outcome;
}


//a>b is promised
string sub_large(string a, string b){
  //since b is always lower than a, we can be assured that a is the longer one
  string longer = morino_reverse(a);
  string shorter = morino_reverse(b);

  
  int i  = 0;
  int remainder = 0;
  string outcome = "";

  int current_sub = 0;
  //let us do the substraction
  while(i < longer.size()){
    if(i<shorter.size()){
      current_sub = dtoi(longer[i]) - dtoi(shorter[i]) - remainder;      
    }else{
      current_sub = dtoi(longer[i]) - remainder;
    }


    if(current_sub<0){
      current_sub += 10;
      remainder = 1;
    }else{
      remainder = 0;
    }

    //put the current digit
    outcome += itos(current_sub);

    if(i>=shorter.size() && remainder==0){
      //which means we only needs to copy the substr
      outcome += longer.substr(i+1, string::npos);
      break;
    }
    i++;
  }

  return morino_reverse(trim_right_zero(outcome));
  
}




// this multiplies a scalar with a
string scalar_mult_large(string a, int scalar){
  if(scalar == 0){
    return "0";
  }
  string a_p = morino_reverse(a);
  string result = "";
  int i = 0;

  int current_mult_out = 0;
  int remainder = 0;
  
  while(i < a_p.size()){
    current_mult_out = dtoi(a_p[i]) * scalar + remainder ;
    result += itos(current_mult_out % 10);
    remainder = current_mult_out / 10;
    i++;
  }

  if(remainder != 0){
    result += itos(remainder);
  }

  return morino_reverse(result);
}


vector<string> mult_large(string a, string b){
  vector<string> procedure;

  string b_p = morino_reverse(b);

  int i = 0;

  string out="0";
  string partial_out = "";
  while(i < b_p.size()){
    partial_out = scalar_mult_large(a, dtoi(b_p[i]));
    
    procedure.push_back(partial_out);
    out = add_large(out, (partial_out !="0" ? (partial_out+string(i, '0')): partial_out));
    i++;
  }

  procedure.push_back(out);
  return procedure;
}








//the visualization of add, sub and one digit mult 
string trivial_visual(string a, string b, string out, string op){
  ostringstream ostr;
  int width = max(a.size(), max(b.size()+1, out.size()));
  int dash_num = max(b.size()+1, out.size());

  ostr << string(width - a.size(), BLANK)<< a <<endl;
  ostr << string(width - b.size()-1, BLANK) << op << b <<endl;
  ostr << string(width-dash_num, BLANK)<<string(dash_num, '-') <<endl;;
  ostr << string(width - out.size(),BLANK) << out <<endl;

  return ostr.str();
}


string advanced_visual(string a, string b, vector<string> partials, string op){
  //first let determine the number of the first dashes
  int over_dash_num = max(b.size()+1, partials[0].size());
  int width = max(over_dash_num, (int)partials.back().size()); // which determines the max width of the thing
  
  ostringstream ostr;


  ostr<< string(width-a.size(), BLANK)<<a<<endl;
  ostr<< string(width-b.size()-1, BLANK)<<op<<b<<endl;
  ostr<< string(width-over_dash_num, BLANK)<<string(over_dash_num, '-')<<endl;

  int i = 0;
  //only prints the internal results, partials is garanteed to be larger than 1
  while(i<partials.size()-1){
    ostr<<string(width-partials[i].size()-i, BLANK)<<partials[i]<<endl;
    i++;
  }


  int lower_dash_num = max(partials[partials.size()-2].size()+partials.size()-2, partials.back().size());

  ostr<<string(width-lower_dash_num, BLANK)<<string(lower_dash_num, '-')<<endl; // print out the lower level dashes

  
  ostr<<string(width-partials.back().size(),BLANK)<<partials.back()<<endl;
  
  return ostr.str();

}






string arith_visual(string a, string b, string op){
  // + and - can be done in the same way

  if(op=="+"){
    return trivial_visual(a, b, add_large(a,b), op);
  }else if(op=="*"){
    vector<string> out = mult_large(a,b);
    if(b.size()==1){
      return trivial_visual(a, b, out[1], op);
    }
    //otherwise the procedure should be shown
    return advanced_visual(a, b, out, op);
  }else if(op=="-"){
    return trivial_visual(a,b,sub_large(a,b), op);
      
  }

  return "";


  
}



int main(){
  int len =0;
  
  string line;
  vector<string> out;

  cin >> len;
    
    while(len > 0){
      cin >> line;
      out = decompose_arith(line);
      cout<<arith_visual(out[0], out[2], out[1])<<endl;
      len--;
    }

  
  return 0;
}
