#ifndef MyFit_hpp
#define MyFit_hpp
//=========================================
// File: MyFit.hpp
// Purpose: Custom histogram fit class
// Created: June 2019, Alexander Uzunyan (alexandruzunyan@gmail,com)
//=========================================
#include "TROOT.h"//Fail s opisaniem osnovnih obiektov ROOT (Dlia gROOT)
#include "TCanvas.h"//Fail dlia raboti s graficeskoi`y paneli`y ROOT (Dlia TCanvas)
#include "TF1.h"//Opisanie obiekta "fit" v ROOT (Dlia TH1)
#include "TH1F.h" //Opisanie obiekta "gistograma" v ROOT (Dlia TH1H)
#include "TText.h"

#include <fstream>//Fail s opisaniem raboti fynkcii cteniia iz faila (Dlia ifstream)
#include <iostream>//Fail s opisaniem raboti fynkcii zapisi v fail (Dlia iostream)
#include <cstdlib>// Fail standartnoi biblioteki iazika c, kotorii soderjit fynkcii videleniia pamiati, 
#include <sstream>//Fail s opisaniem fynkcii dlia raboti s stringstream
//using namespace std;

class MyFit 
{
    
    private:
    //Zdes pishytsia tolko zashishennie fynkcii i peremennie.
    
    
    public: 
    //Obshedostypnie fynkcii i peremennie
    const char* dataFileName;
    Float_t lf_xmin;
    Float_t lf_xmax;
    Float_t gf_xmin;
    Float_t gf_xmax;

    Float_t mean_gf;
    Float_t mpv_lf;
   
    TH1F* signal_hist;
    TF1* lf;
    TF1* gf;

    std::ifstream* inputDataStream;
    MyFit();//Konstructor
    
 //parametrom fynkcii iavliaetsia pointer na pervyy bykvy imeni "sc301_ch5.dat", etot ykazatel nelzia meniat
    MyFit(const char* dataFileName, Float_t lf_xmin,Float_t lf_xmax, Float_t gf_xmin, Float_t gf_xmax);

    int OpenDataStream();
    int CreateHist(const char* Histname,int nbin,float xmin,float xmax);    
    void SetHistAttributes(TH1F* hist, const char* htitle, const char* xtitle, const char* ytitle);
    //TH1F* hist, const char* htitle="test", const char* xtitle="test", const char* ytitle="Events/bin"
    void FillHist();
    void FitHist();
    void PlotHist();
    void SaveHist();
    //void PrintParameters(Float_t mean_gf, Float_t mpv_lf, TF1* lf, TF1* lf, TF1* gf);
};
   


#endif
