#include <iostream>

using namespace std;





int atoi(char c){
  return c-'0';
}

char itoa(int i){
  return i+'0';
}



string find_palin(string start_pt){
  if(start_pt.empty()){
    return "0";
  }
  
  int i = 0;

  int bound = 0;

  

  int size = start_pt.size();
  
  if(size % 2 ==0){
    bound = size/2;
  }else{
    bound = size/2+1;
  }

  
  int not_greater_sgno = 2;
 
  while(i < bound){
    int high = atoi(start_pt[i]);
    int low  = atoi(start_pt[size-1-i]);
    

    //do the check

    if(high < low){
      not_greater_sgno = 1;
    }else if(high > low){
      not_greater_sgno = 3;
    }

    //which means the last one
    if(i==bound-1 && not_greater_sgno<=2){
      int j = i;
      while(j >=0 && start_pt[j]=='9'){
	start_pt[j] = '0';
	start_pt[size-1-j]='0';
	j--;
      }


      //if the last one still be zero
      if(j==-1){
	start_pt.insert(0, "1");
	size +=1;
	j++;

	start_pt[size-1-j] =start_pt[j];
      }else{
	//find a possible one to do the increment

	start_pt[j] = itoa(atoi(start_pt[j])+1);
	start_pt[size-1-j] = start_pt[j];

      }


      

      break;
    }
    

    
    start_pt[size-1-i] = start_pt[i]; 
    
    i++;
  }


  return start_pt;
}



int main(){
  int length = 0;

  cin >> length;

  string large_num = "";

  
  while(length > 0){
    cin >> large_num;
  
    large_num.erase(0, large_num.find_first_not_of('0'));
    
    cout << find_palin(large_num) << endl;
    length--;
  }
  return 0;

}
