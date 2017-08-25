#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include <iomanip>

using namespace std;


struct Point {
  double x;
  double y;
};


Point make_pt(double x, double y){
  Point pt;
  pt.x = x;
  pt.y = y;
  return pt;
}
  
  
//X, Y stores the coordinates, while n the number of points that composes the polygon
Point c_of_gravity(int* X, int* Y, int n){
  //we first compute the reusable things
  vector<double> cross_products;
  double cx = 0.0, cy =0.0;

  int i = 0;
  while(i < n){
    cross_products.push_back(X[i]*Y[(i+1)%n]-Y[i]*X[(i+1)%n]);
    i++;
  }


  //the next thing is to first compute
  i = 0;

  //for the possibility of overflow, first compute the area
  double area = (double)accumulate(cross_products.begin(), cross_products.end(), 0.0)/2.0;

  

  while(i < n){
    cx += (X[i]+X[(i+1)%n])*cross_products[i];
    cy += (Y[i]+Y[(i+1)%n])*cross_products[i];

    i++;					 
  }

  cx /=(6.0*area);
  cy /=(6.0*area);

  Point p;
  p.x = cx;
  p.y = cy;
  

  return p;
}




int main(){
  int len = 0;
  cin >> len;

  int pt_num = 0;
  while(len > 0){
    cin >> pt_num;
    double grad_x=0.0, grad_y=0.0;

    int x, y;


    int* pts_X = new int[pt_num];
    int* pts_Y = new int[pt_num];
    
    int j = 0;

    while(j < pt_num){
      cin >> x >> y;
      pts_X[j] = x;
      pts_Y[j] = y;
      j++;
    }

    Point p = c_of_gravity(pts_X, pts_Y, pt_num);

    delete [] pts_X;
    delete [] pts_Y;

    //be careful about the format of the output
    printf("%.2lf %.2lf\n", p.x, p.y);
    len --;
  }
  
}
