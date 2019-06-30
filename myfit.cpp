//g++ myfit.cpp MyFit.cpp --std=c++11  -L../lib  -lTreePlayer -lMinuit -lGui  $(root-config --libs) -lGpad  -lGX11 -lX3d  -o myfit 
//> out.txt 2>&1
// ./myfit sc301_sch.dat 50 300 -50 50


//=========================================
// File: myfit.cpp 
// Purpose: Main programm to use class MyFit
// Created: June 2019, Alexander Uzunyan (alexandruzunyan@gmail,com)
//=========================================
#include "MyFit.hpp"
using namespace std;
int main(int argc, char** argv)
{
  char* dFileName=argv[1];
  Float_t lf_min=atof(argv[2]);
  Float_t lf_max=atof(argv[3]);
  Float_t gf_min=atof(argv[4]);
  Float_t gf_max=atof(argv[5]);

  

  //Skonstruirovali class. 
  MyFit Fit1(dFileName,lf_min,lf_max,gf_min,gf_max);

  cout << "Done myfit Fit1" << endl;
  int fstatus = Fit1.OpenDataStream();
  cout<< "fstatus = "<< fstatus << endl;
  if (fstatus==1){
    return 1;
  }
  //CreateHist, FillHist, FitHist,  PlotHist, PrintParameters
  Fit1.CreateHist("Signal_hist",100,-100,400);  
  Fit1.FillHist();
  Fit1.FitHist();
  Fit1.PlotHist();
  
  //Fit1.PrintParameters();
 
   
  return 0;
}
