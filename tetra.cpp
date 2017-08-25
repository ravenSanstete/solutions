#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;




double S(double a, double b, double c){
  return 0.25*sqrt((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c));

}



// let us just use the formula for the volume of a tetra
double radius(double U, double V, double W, double u, double v, double w){
  double X = (w-U+v)*(U+v+w);
  double x = (U-v+w)*(v-w+U);
  double Y = (u-V+w)*(V+w+u);
  double y = (V-w+u)*(w-u+V);
  double Z = (v-W+u)*(W+u+v);
  double z = (W-u+v)*(u-v+W);


  double a = sqrt(x*Y*Z);
  double b = sqrt(y*Z*X);
  double c = sqrt(z*X*Y);
  double d = sqrt(x*y*z);

  double vol = sqrt((-a+b+c+d)*(a-b+c+d)*(a+b-c+d)*(a+b+c-d))/(64*u*v*w);


  return vol/(S(U, V, W)+S(w,U,v)+S(w,V,u)+S(u,v,W));
}






int main(){
  int len;
  cin >> len;

  cout.setf(ios::fixed);
  while(len > 0){
    int WX, WY, WZ, XY, XZ, YZ;

    cin >> WX >> WY >> WZ >> XY >> XZ >> YZ;
    
    cout <<setprecision(4) <<radius(XY,XZ,YZ,WZ,WY,WX) << endl;

    len --;
  }
  return 0;
}
