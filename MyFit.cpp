#define MyFit_cpp 
//=========================================
// File: MyFit.cpp
// Purpose: Custom histogram fit class
// Created: June 2019, Alexander Uzunyan (alexandruzunyan@gmail,com)
//=========================================
#include "MyFit.hpp"

using namespace std;

//=======================================
MyFit::MyFit(){
    cout<< "MyFit Constructor" <<endl;
    
};// Konstruktor klassa MyFit

//=======================================
MyFit:: MyFit(const char* dFileName, Float_t lf_min_,Float_t lf_max_, Float_t gf_min_, Float_t gf_max_)
{
  dataFileName=dFileName;
  lf_xmin=lf_min_;
  lf_xmax=lf_max_;
  gf_xmin=gf_min_;
  gf_xmax=gf_max_;

}

//=======================================
int MyFit::OpenDataStream(){

  inputDataStream= new ifstream(dataFileName);
  
  if (inputDataStream->is_open()){
    return 0;
  }else{
    cout<< "File " << dataFileName << "not found" << endl; 
    return 1;
  }
}

//=======================================
int MyFit::CreateHist(const char* Histname,int nbin,float xmin,float xmax){

  signal_hist= new TH1F(Histname,"Signal Hist",nbin, xmin, xmax);
  SetHistAttributes(signal_hist,signal_hist->GetTitle(),"ADC counts", "Events/bin" );
}

//=======================================

void MyFit::FillHist(){

 while (!inputDataStream->eof()) //poka ne konec faila
   {
     Int_t ch, val;//obiavlenie peremennix
     (*inputDataStream) >> ch >> val; //scitivaem znacenii
     // cout<<"ch/val= "<<ch<<"/"<<val<<endl;
     signal_hist->Fill(ch, val); //stroim gistogramy
   }

}

//=======================================

void MyFit:: SetHistAttributes(TH1F* hist, const char* htitle="test", const char* xtitle="test", const char* ytitle="Events/bin"){

 hist->GetXaxis()->SetTitle(htitle);   //Ystanavlivaet nazvanie po X
 hist->GetXaxis()->CenterTitle(true);  //Centriryet zagolovok
 hist->GetYaxis()->SetNdivisions(505); //Ystanavlivaet shkaly deleniia po Y
 hist->GetYaxis()->SetTitle(ytitle);   //Ystanavlivaet zagolovok po Y
 hist->GetXaxis()->SetTitle(xtitle);    //Ystanavlivaet zagolovok po X
 hist->GetYaxis()->SetTitleOffset(1.4); //Ystanavlivaet rasstoianie mejdy osiy i nazvaniem osi
 hist->GetYaxis()->CenterTitle(true);  //Centriryet nazvanie po Y
}




//=======================================

void MyFit::FitHist(){

  if (gROOT->FindObject("fl")){
      delete lf; 
      delete gf;
  }else{
      lf = new TF1("fl","landau",lf_xmin,lf_xmax);
      gf = new TF1("fg","gaus",gf_xmin,gf_xmax);
  }

  signal_hist->Fit(lf,"RW","",lf_xmin,lf_xmax);//Fitiryetsia pervii otrezok gistogrami  
  signal_hist->Fit(gf,"RW+","",gf_xmin,gf_xmax);//Fitiryetsia vtoroi otrezok gistogrami

 lf->SetLineColor(4);//Vibiraetsia sinii cvet linii fita 
 gf->SetLineColor(2);//Vibiraetsia krasnii cvet linii fita

  lf->Draw("same");//Risyetsia pervii fit
  gf->Draw("same");//risyetsia vtoroi fit
    
    mpv_lf=lf->GetParameter(1);//p1 prisvaevaetsia znacenie pervogo parametra v fynkvii landau
    cout<<"p1_landau_MPV= "<<mpv_lf<<endl;//vivoditsia na ekran  
    mean_gf=gf->GetParameter(1);//p1 prisvaevaetsia znacenie pervogo parametra v fynkcii gausa
    cout<<"p2_gaus_Mean= "<<mean_gf<<endl;//vivoditsia na ekran 

}

void MyFit::PlotHist(){

  signal_hist->Draw("hist");
  lf->Draw("same");
  gf->Draw("same");
  gPad->SaveAs("signal_hist.pdf");
}

void MyFit::SaveHist(){

 

}
