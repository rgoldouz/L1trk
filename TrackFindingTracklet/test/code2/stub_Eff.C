#define stub_Eff_cxx
#include "stub_Eff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <cstdlib>
#include <TLine.h>
#include <TPaveText.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>    
#include <iomanip>
#include <TLegend.h>
#include <THStack.h>

void displayProgress(long current, long max){
  using std::cerr;
  if (max<1000) return;
  if (current%(max/1000)!=0 && current<max-1) return;

  int width = 52; // Hope the terminal is at least that wide.
  int barWidth = width - 2;
  cerr << "\x1B[2K"; // Clear line
  cerr << "\x1B[2000D"; // Cursor left
  cerr << '[';
  for(int i=0 ; i<barWidth ; ++i){ if(i<barWidth*current/max){ cerr << '=' ; }else{ cerr << ' ' ; } }
  cerr << ']';
  cerr << " " << Form("%8d/%8d (%5.2f%%)", (int)current, (int)max, 100.0*current/max) ;
  cerr.flush();
}

void stub_Eff::eff(TString fname, TString pname)
{
  
  typedef vector<int> Dim1;
  typedef vector<Dim1> Dim2;
  typedef vector<Dim2> Dim3;
  typedef vector<Dim3> Dim4;
  typedef vector<Dim4> Dim5;
  typedef vector<Dim5> Dim6;
   
  if (fChain == 0) return;
  Int_t nentries = (Int_t) fChain->GetEntries();
  
  Long64_t nbytes = 0, nb = 0;
  
  
  cout<<nentries<<endl;
 
  std::vector<TH1F*> Barrel_Stub_eta_PBX;
  std::vector<TH1F*> Barrel_Cluster_eta_PBX;
  std::vector<TH1F*> Barrel_Stub_pt_PBX;
  std::vector<TH1F*> Barrel_Cluster_pt_PBX;

  std::vector<TH1F*> Endcap_Stub_eta_PBX;
  std::vector<TH1F*> Endcap_Cluster_eta_PBX;
  std::vector<TH1F*> Endcap_Stub_pt_PBX;
  std::vector<TH1F*> Endcap_Cluster_pt_PBX;

  TH1F *b_Stub_eta_PBX;
  TH1F *b_Cluster_eta_PBX;
  TH1F *b_Stub_pt_PBX;
  TH1F *b_Cluster_pt_PBX;

  TH1F *e_Stub_eta_PBX;
  TH1F *e_Cluster_eta_PBX;
  TH1F *e_Stub_pt_PBX;
  TH1F *e_Cluster_pt_PBX;

  
  for (int k=0;k<6;++k){
    std::stringstream name;
    name<<"Barrel_Stub_eta_"<<k<<"_PBX_"<<pname;
    b_Stub_eta_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),15,0,3);
    name.str("");
    name<<"Barrel_Cluster_eta_"<<k<<"_PBX_"<<pname;
    b_Cluster_eta_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),15,0,3);
    name.str("");
    name<<"Barrel_Stub_pt_"<<k<<"_PBX_"<<pname;
    b_Stub_pt_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),20,0,10);
    name.str("");
    name<<"Barrel_Cluster_pt_"<<k<<"_PBX_"<<pname;
    b_Cluster_pt_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),20,0,10);
    name.str("");

    Barrel_Stub_eta_PBX.push_back(b_Stub_eta_PBX);
    Barrel_Cluster_eta_PBX.push_back(b_Cluster_eta_PBX);
    Barrel_Stub_pt_PBX.push_back(b_Stub_pt_PBX);
    Barrel_Cluster_pt_PBX.push_back(b_Cluster_pt_PBX);

    name<<"Endcap_Stub_eta_"<<k<<"_PBX_"<<pname;
    e_Stub_eta_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),15,0,3);
    name.str("");
    name<<"Endcap_Cluster_eta_"<<k<<"_PBX_"<<pname;
    e_Cluster_eta_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),15,0,3);
    name.str("");
    name<<"Endcap_Stub_pt_"<<k<<"_PBX_"<<pname;
    e_Stub_pt_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),20,0,10);
    name.str("");
    name<<"Endcap_Cluster_pt_"<<k<<"_PBX_"<<pname;
    e_Cluster_pt_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),20,0,10);
    name.str("");

    Endcap_Stub_eta_PBX.push_back(e_Stub_eta_PBX);
    Endcap_Cluster_eta_PBX.push_back(e_Cluster_eta_PBX);
    Endcap_Stub_pt_PBX.push_back(e_Stub_pt_PBX);
    Endcap_Cluster_pt_PBX.push_back(e_Cluster_pt_PBX);
  }

  for (int k=0;k<6;++k){
    Barrel_Stub_eta_PBX[k]->Sumw2()          ;
    Barrel_Cluster_eta_PBX[k]->Sumw2()          ;
    Barrel_Stub_pt_PBX[k]->Sumw2()          ;
    Barrel_Cluster_pt_PBX[k]->Sumw2()          ;
    Endcap_Stub_eta_PBX[k]->Sumw2()          ;
    Endcap_Cluster_eta_PBX[k]->Sumw2()          ;
    Endcap_Stub_pt_PBX[k]->Sumw2()          ;
    Endcap_Cluster_pt_PBX[k]->Sumw2()          ;
  }

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(ientry) < 0) continue;
    displayProgress(jentry, nentries) ;
    float N = float(nentries); 
    int pid = 0;
    if (pname == "mu") pid = 13;
    if (pname == "ele") pid = 11;
    if (pname == "pion") pid = 211;
    for (unsigned int k=0; k<stubEff_tp_pt->size(); ++k) {
      if(abs(stubEff_tp_pdgid->at(k))!=pid) continue;
      if(abs(stubEff_tp_pt->at(k))<2) continue;
  
  //if (2*stubEff_EL1->at(k) != clustEff_EL1->at(k)) cout<<"#stub= "<<stubEff_EL1->at(k)<<" #clusters = "<<clustEff_EL1->at(k) <<" eta ="<<stubEff_tp_eta->at(k)<<" pt="<<stubEff_tp_pt->at(k)<<endl;
  
      Barrel_Stub_eta_PBX[0]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL1->at(k))/N);
      Barrel_Stub_eta_PBX[1]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL2->at(k))/N);
      Barrel_Stub_eta_PBX[2]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL3->at(k))/N);
      Barrel_Stub_eta_PBX[3]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL4->at(k))/N);
      Barrel_Stub_eta_PBX[4]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL5->at(k))/N);
      Barrel_Stub_eta_PBX[5]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL6->at(k))/N);
  
      Endcap_Stub_eta_PBX[0]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL1->at(k))/N);
      Endcap_Stub_eta_PBX[1]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL2->at(k))/N);
      Endcap_Stub_eta_PBX[2]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL3->at(k))/N);
      Endcap_Stub_eta_PBX[3]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL4->at(k))/N);
      Endcap_Stub_eta_PBX[4]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL5->at(k))/N);
  
      Barrel_Cluster_eta_PBX[0]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL1->at(k))/N);
      Barrel_Cluster_eta_PBX[1]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL2->at(k))/N);
      Barrel_Cluster_eta_PBX[2]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL3->at(k))/N);
      Barrel_Cluster_eta_PBX[3]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL4->at(k))/N);
      Barrel_Cluster_eta_PBX[4]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL5->at(k))/N);
      Barrel_Cluster_eta_PBX[5]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL6->at(k))/N);
  
      Endcap_Cluster_eta_PBX[0]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL1->at(k))/N);
      Endcap_Cluster_eta_PBX[1]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL2->at(k))/N);
      Endcap_Cluster_eta_PBX[2]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL3->at(k))/N);
      Endcap_Cluster_eta_PBX[3]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL4->at(k))/N);
      Endcap_Cluster_eta_PBX[4]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL5->at(k))/N);
  
  
      if(abs(stubEff_tp_eta->at(k)) < 0.6){
        Barrel_Stub_pt_PBX[0]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL1->at(k))/N);
        Barrel_Stub_pt_PBX[1]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL2->at(k))/N);
        Barrel_Stub_pt_PBX[2]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL3->at(k))/N);
        Barrel_Stub_pt_PBX[3]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL4->at(k))/N);
        Barrel_Stub_pt_PBX[4]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL5->at(k))/N);
        Barrel_Stub_pt_PBX[5]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL6->at(k))/N);
  
        Barrel_Cluster_pt_PBX[0]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL1->at(k))/N);
        Barrel_Cluster_pt_PBX[1]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL2->at(k))/N);
        Barrel_Cluster_pt_PBX[2]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL3->at(k))/N);
        Barrel_Cluster_pt_PBX[3]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL4->at(k))/N);
        Barrel_Cluster_pt_PBX[4]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL5->at(k))/N);
        Barrel_Cluster_pt_PBX[5]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL6->at(k))/N);
      }
      if(abs(stubEff_tp_eta->at(k)) > 1.7 && abs(stubEff_tp_eta->at(k))<2.4) {
      Endcap_Stub_pt_PBX[0]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL1->at(k))/N);
      Endcap_Stub_pt_PBX[1]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL2->at(k))/N);
      Endcap_Stub_pt_PBX[2]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL3->at(k))/N);
      Endcap_Stub_pt_PBX[3]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL4->at(k))/N);
      Endcap_Stub_pt_PBX[4]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL5->at(k))/N);
  
      Endcap_Cluster_pt_PBX[0]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL1->at(k))/N);
      Endcap_Cluster_pt_PBX[1]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL2->at(k))/N);
      Endcap_Cluster_pt_PBX[2]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL3->at(k))/N);
      Endcap_Cluster_pt_PBX[3]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL4->at(k))/N);
      Endcap_Cluster_pt_PBX[4]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL5->at(k))/N);
      }
    }
  }

  TFile *f = new TFile(fname+"_stubeff_output.root","RECREATE");
  f->cd();
  for (int k=0;k<6;++k){
    Barrel_Stub_eta_PBX[k]   ->Write("",TObject::kOverwrite)          ;
    Barrel_Cluster_eta_PBX[k]->Write("",TObject::kOverwrite)          ;
    Barrel_Stub_pt_PBX[k]    ->Write("",TObject::kOverwrite)          ;
    Barrel_Cluster_pt_PBX[k] ->Write("",TObject::kOverwrite)          ;
    Endcap_Stub_eta_PBX[k]   ->Write("",TObject::kOverwrite)          ;
    Endcap_Cluster_eta_PBX[k]->Write("",TObject::kOverwrite)          ;
    Endcap_Stub_pt_PBX[k]    ->Write("",TObject::kOverwrite)          ;
    Endcap_Cluster_pt_PBX[k] ->Write("",TObject::kOverwrite)          ;
  }

  for (int k=0;k<6;++k){
    delete    Barrel_Stub_eta_PBX[k]   ;
    delete    Barrel_Cluster_eta_PBX[k];
    delete    Barrel_Stub_pt_PBX[k]    ;
    delete    Barrel_Cluster_pt_PBX[k] ;
    delete    Endcap_Stub_eta_PBX[k]   ;
    delete    Endcap_Cluster_eta_PBX[k];
    delete    Endcap_Stub_pt_PBX[k]    ;
    delete    Endcap_Cluster_pt_PBX[k] ;
  }
  f->Close();
}

