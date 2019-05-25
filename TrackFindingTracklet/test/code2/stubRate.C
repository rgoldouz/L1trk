#define stubRate_cxx
#include "stubRate.h"
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
#include <TVector3.h>

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

void stubRate::TPR(TString fname, TString pname)
{

  cout<<fname <<" for TP rate "<<pname;
  Long64_t nbytes = 0, nb = 0;
  Int_t nentries = (Int_t) fChain->GetEntries();
  
  TH1F *TP_cutflow;
  TH1F *TP_eta;
  TH1F *TP_pt;
  TH1F *TP_nstub;
  TH1F *TP_nstubg;
  TH1F *TP_nlayer;
  
  TP_cutflow = new TH1F("TP_cutflow","TP_cutflow",4,0,4);
  TP_eta     = new TH1F("TP_eta","TP_eta",30,-3,3);
  TP_pt      = new TH1F("TP_pt","TP_pt",20,0,10);
  TP_nstub   = new TH1F("TP_nstub","TP_nstub",15,0,15);
  TP_nstubg  = new TH1F("TP_nstubg","TP_nstubg",10,0,10);
  TP_nlayer  = new TH1F("TP_nlayer","TP_nlayer",10,0,10);
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(ientry) < 0) continue;
  
    float N = float(nentries);

   
  
    TP_cutflow->Fill(0.5,float(tp_N)/N);
    TP_cutflow->Fill(1.5,float(tp_pt->size())/N);
  
    for (unsigned int k=0; k<tp_pt->size(); ++k) {
      TP_pt->Fill(tp_pt->at(k), 1/N);
      TP_eta->Fill(abs(tp_eta->at(k)), 1/N);
      TP_nstub->Fill(tp_nstub->at(k), 1/N);
      TP_nstubg->Fill(tp_nstub_layer_g->at(k), 1/N);
      TP_nlayer->Fill(tp_nstub_layer->at(k), 1/N);
      if (tp_nstub_layer->at(k)>3) TP_cutflow->Fill(2.5,1/N);
      if (tp_eventid->at(k)==0 && tp_nstub_layer->at(k)>3) TP_cutflow->Fill(3.5,1/N);
    }
  }

gStyle->SetOptStat(0);
gStyle->SetPaintTextFormat("4.1f");

TCanvas *c;
TPad *pad1;
TPaveText *pave;

pave = new TPaveText(0.05,0.92,0.3,1,"NDC");
pave->AddText(fname);

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0,1,1);
pad1->SetLogy();
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad1->cd();
const Int_t nx = 4;
const char *type[nx] = {"All","P_{T}>3,|#eta |<2.4","N_layer>3","From PI"};

Int_t i;
for (i=1;i<=nx;i++) {
TP_cutflow->GetXaxis()->SetBinLabel(i,type[i-1]);
}

TP_cutflow->SetTitle("Average number of TP");
TP_cutflow->GetXaxis()->SetTitle("");
TP_cutflow->GetYaxis()->SetTitleSize(0.06);
TP_cutflow->GetXaxis()->SetLabelOffset(0.03);
TP_cutflow->GetXaxis()->SetLabelSize(0.08);
TP_cutflow->SetFillColor(2);
TP_cutflow->SetLineColor(0);
TP_cutflow->SetMarkerSize(2.5);
TP_cutflow->Draw("HIST TEXT0 SAME");
TP_cutflow->Draw("XY AXIS SAME");
pave->Draw("same");

c->Print("TPcutflow_"+fname+".png","png");
delete pad1;
delete c;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0,1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad1->cd();
TP_eta->SetTitle("Average number of TP");
TP_eta->GetXaxis()->SetTitle("|#eta|");
TP_eta->GetXaxis()->SetTitleSize(0.08);
TP_eta->SetFillColor(2);
TP_eta->SetLineColor(2);
TP_eta->SetMarkerSize(1.5);
TP_eta->Draw("HIST TEXT0 SAME");
TP_eta->Draw("XY AXIS SAME");
pave->Draw("same");
c->Print("TPeta_"+fname+".png","png");
delete pad1;
delete c;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0,1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad1->cd();
TP_pt->SetTitle("Average number of TP");
TP_pt->GetXaxis()->SetTitle("Pt");
TP_pt->GetXaxis()->SetTitleSize(0.08);
TP_pt->SetFillColor(2);
TP_pt->SetLineColor(2);
TP_pt->SetMarkerSize(1.5);
TP_pt->Draw("HIST TEXT90 SAME");
TP_pt->Draw("XY AXIS SAME");
pave->Draw("same");
c->Print("TPpt_"+fname+".png","png");
delete pad1;
delete c;


c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0,1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad1->cd();
TP_nstub->SetTitle("Average number of TP");
TP_nstub->GetXaxis()->SetTitle("N_stubs");
TP_nstub->GetYaxis()->SetTitleSize(0.08);
TP_nstub->SetFillColor(2);
TP_nstub->SetLineColor(2);
TP_nstub->SetMarkerSize(1.5);
TP_nstub->Draw("HIST TEXT0 SAME");
TP_nstub->Draw("XY AXIS SAME");
pave->Draw("same");
c->Print("Tnstub_"+fname+".png","png");
delete pad1;
delete c;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0,1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad1->cd();
TP_nstubg->SetTitle("Average number of TP");
TP_nstubg->GetXaxis()->SetTitle("N_Genuine_stubs");
TP_nstubg->GetXaxis()->SetTitleSize(0.08);
TP_nstubg->SetFillColor(2);
TP_nstubg->SetLineColor(0);
TP_nstubg->SetMarkerSize(1.5);
TP_nstubg->Draw("HIST TEXT0 SAME");
TP_nstubg->Draw("XY AXIS SAME");
pave->Draw("same");
c->Print("Tstubg_"+fname+".png","png");
delete pad1;
delete c;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0,1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad1->cd();
TP_nlayer->SetTitle("Average number of TP");
TP_nlayer->GetXaxis()->SetTitle("N_layer");
TP_nlayer->GetXaxis()->SetTitleSize(0.08);
TP_nlayer->SetFillColor(2);
TP_nlayer->SetLineColor(0);
TP_nlayer->SetMarkerSize(1.5);
TP_nlayer->Draw("HIST TEXT0 SAME");
TP_nlayer->Draw("XY AXIS SAME");
pave->Draw("same");
c->Print("TPnlayer_"+fname+".png","png");
delete pad1;
delete c;



delete TP_cutflow;
delete TP_eta;
delete TP_pt;
delete TP_nstub;
delete TP_nstubg;
delete TP_nlayer;
}




//////////////////////////////////////////////////Stub rate
void stubRate::SR(TString fname, TString pname)
{

  cout<<fname <<" for  stub rate"<<pname;
  
  typedef vector<float> Dim1;
  typedef vector<Dim1> Dim2;
  typedef vector<Dim2> Dim3;
  typedef vector<Dim3> Dim4;
  typedef vector<Dim4> Dim5;
  typedef vector<Dim5> Dim6;
   
  if (fChain == 0) return;
  Int_t nentries = (Int_t) fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  TH1F *stub_type;
  TH1F *stub_eta;

  stub_type = new TH1F("stub_type","stub_type",4,0,4);
  stub_eta     = new TH1F("stub_eta","stub_eta",30,-3,3);
  cout<<nentries<<endl;

  Dim4 stubsRate(2,Dim3(6,Dim2(100,Dim1(100))));
  Dim4 stubsRateCBCfail(2,Dim3(6,Dim2(100,Dim1(100))));
  Dim4 stubsRateCICfail(2,Dim3(6,Dim2(100,Dim1(100))));
  Dim4 tmpstubsRate(2,Dim3(6,Dim2(100,Dim1(100))));
  Dim4 stubsRate_z(2,Dim3(6,Dim2(100,Dim1(100))));
  Dim4 stubsRate_rho(2,Dim3(6,Dim2(100,Dim1(100))));
  Dim4 stubsRate_eta(2,Dim3(6,Dim2(100,Dim1(100))));

  for (int i=0;i<2;++i){
    for (int k=0;k<6;++k){
      for (int l=0;l<100;++l){
        for (int m=0;m<100;++m){
             stubsRate[i][k][l][m] = 0;
             stubsRateCBCfail[i][k][l][m] = 0;
             stubsRateCICfail[i][k][l][m] = 0;
             tmpstubsRate[i][k][l][m] = 0;
             stubsRate_z[i][k][l][m] = 0;
             stubsRate_rho[i][k][l][m] = 0;
             stubsRate_eta[i][k][l][m] = 0;
         }
      }
    }
  }

  std::vector<TH2D*> Barrel_2D;
  std::vector<TH2D*> Barrel_2DCBCfail;
  std::vector<TH2D*> Barrel_2DCICfail;
  std::vector<TH2D*> Endcap_2D;
  std::vector<TH2D*> Endcap_2DCBCfail;
  std::vector<TH2D*> Endcap_2DCICfail;
  std::vector<TH1F*> Barrel_eta_PBX;
  std::vector<TH1F*> Barrel_eta_PBXCBCfail;
  std::vector<TH1F*> Barrel_eta_PBXCICfail;
  std::vector<TH1F*> Barrel_type_PBX;
  std::vector<TH1F*> Barrel_type_PBXCBCfail;
  std::vector<TH1F*> Barrel_type_PBXCICfail;
  std::vector<TH1F*> Barrel_eta_PbxPmodule;
  std::vector<TH1F*> Barrel_eta_PbxPmoduleCBCfail;
  std::vector<TH1F*> Barrel_eta_PbxPmoduleCICfail;
  std::vector<TH1F*> Barrel_z_PbxPmodule;
  std::vector<TH1F*> Barrel_rho_PbxPmodule;
  std::vector<TH1F*> Barrel_nstub_PbxPmodule;

  std::vector<TH1F*> Endcap_eta_PBX;
  std::vector<TH1F*> Endcap_eta_PBXCBCfail;
  std::vector<TH1F*> Endcap_eta_PBXCICfail;
  std::vector<TH1F*> Endcap_type_PBX;
  std::vector<TH1F*> Endcap_type_PBXCBCfail;
  std::vector<TH1F*> Endcap_type_PBXCICfail;
  std::vector<TH1F*> Endcap_eta_PbxPmodule;
  std::vector<TH1F*> Endcap_eta_PbxPmoduleCBCfail;
  std::vector<TH1F*> Endcap_eta_PbxPmoduleCICfail;
  std::vector<TH1F*> Endcap_z_PbxPmodule;
  std::vector<TH1F*> Endcap_rho_PbxPmodule;
  std::vector<TH1F*> Endcap_nstub_PbxPmodule;

  TH1F *b_eta_PBX;
  TH1F *b_eta_PBXCBCfail;
  TH1F *b_eta_PBXCICfail;
  TH1F *b_type_PBX;
  TH1F *b_type_PBXCBCfail;
  TH1F *b_type_PBXCICfail;
  TH1F *b_eta_PbxPmodule;
  TH1F *b_eta_PbxPmoduleCBCfail;
  TH1F *b_eta_PbxPmoduleCICfail;
  TH1F *b_z_PbxPmodule;
  TH1F *b_rho_PbxPmodule;
  TH1F *b_nstub_PbxPmodule;

  TH1F *e_eta_PBX;
  TH1F *e_eta_PBXCBCfail;
  TH1F *e_eta_PBXCICfail;
  TH1F *e_type_PBX;
  TH1F *e_type_PBXCBCfail;
  TH1F *e_type_PBXCICfail;
  TH1F *e_eta_PbxPmodule;
  TH1F *e_eta_PbxPmoduleCBCfail;
  TH1F *e_eta_PbxPmoduleCICfail;
  TH1F *e_z_PbxPmodule;
  TH1F *e_rho_PbxPmodule;
  TH1F *e_nstub_PbxPmodule;

  TH1F *eta_PbxPmodule;
  TH1F *z_PbxPmodule;
  TH1F *rho_PbxPmodule;
  TH1F *nstub_PbxPmodule;

  TVector3 sEta;
  TVector3 mEta;

  for (int k=0;k<6;++k){
    std::stringstream name;
    name<<"Barrel_eta_"<<k<<"_PBX";
    b_eta_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Barrel_eta_"<<k<<"_PBXCBCfail";
    b_eta_PBXCBCfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Barrel_eta_"<<k<<"_PBXCICfail";
    b_eta_PBXCICfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Barrel_type_"<<k<<"_PBX";
    b_type_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),4,0,4);
    name.str("");
    name<<"Barrel_type_"<<k<<"_PBXCBCfail";
    b_type_PBXCBCfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),4,0,4);
    name.str("");
    name<<"Barrel_type_"<<k<<"_PBXCICfail";
    b_type_PBXCICfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),4,0,4);
    name.str("");
    name<<"Barrel_eta_"<<k<<"_PbxPmodule";
    b_eta_PbxPmodule = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Barrel_eta_"<<k<<"_PbxPmoduleCBCfail";
    b_eta_PbxPmoduleCBCfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Barrel_eta_"<<k<<"_PbxPmoduleCICfail";
    b_eta_PbxPmoduleCICfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Barrel_z_"<<k<<"_PbxPmodule";
    b_z_PbxPmodule = new TH1F((name.str()).c_str(),(name.str()).c_str(),40,-300,300);
    name.str("");
    name<<"Barrel_rho_"<<k<<"_PbxPmodule";
    b_rho_PbxPmodule = new TH1F((name.str()).c_str(),(name.str()).c_str(),40,0,120);
    name.str("");
    name<<"Barrel_nstub_"<<k<<"_PbxPmodule";
    b_nstub_PbxPmodule = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,30);

    Barrel_eta_PBX.push_back(b_eta_PBX);
    Barrel_eta_PBXCBCfail.push_back(b_eta_PBXCBCfail);
    Barrel_eta_PBXCICfail.push_back(b_eta_PBXCICfail);
    Barrel_type_PBX.push_back(b_type_PBX);
    Barrel_type_PBXCBCfail.push_back(b_type_PBXCBCfail);
    Barrel_type_PBXCICfail.push_back(b_type_PBXCICfail);
    Barrel_eta_PbxPmodule.push_back(b_eta_PbxPmodule);
    Barrel_eta_PbxPmoduleCBCfail.push_back(b_eta_PbxPmoduleCBCfail);
    Barrel_eta_PbxPmoduleCICfail.push_back(b_eta_PbxPmoduleCICfail);
    Barrel_z_PbxPmodule.push_back(b_z_PbxPmodule);
    Barrel_rho_PbxPmodule.push_back(b_rho_PbxPmodule);
    Barrel_nstub_PbxPmodule.push_back(b_nstub_PbxPmodule);

    name.str("");
    name<<"Endcap_eta_"<<k<<"_PBX";
    e_eta_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Endcap_eta_"<<k<<"_PBXCBCfail";
    e_eta_PBXCBCfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Endcap_eta_"<<k<<"_PBXCICfail";
    e_eta_PBXCICfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,-3,3);
    name.str("");
    name<<"Endcap_type_"<<k<<"_PBX";
    e_type_PBX = new TH1F((name.str()).c_str(),(name.str()).c_str(),4,0,4);
    name.str("");
    name<<"Endcap_type_"<<k<<"_PBXCBCfail";
    e_type_PBXCBCfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),4,0,4);
    name.str("");
    name<<"Endcap_type_"<<k<<"_PBXCICfail";
    e_type_PBXCICfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),4,0,4);
    name.str("");
    name<<"Endcap_eta_"<<k<<"_PbxPmodule";
    e_eta_PbxPmodule = new TH1F((name.str()).c_str(),(name.str()).c_str(),15,0,3);
    name.str("");
    name<<"Endcap_eta_"<<k<<"_PbxPmoduleCBCfail";
    e_eta_PbxPmoduleCBCfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),15,0,3);
    name.str("");
    name<<"Endcap_eta_"<<k<<"_PbxPmoduleCICfail";
    e_eta_PbxPmoduleCICfail = new TH1F((name.str()).c_str(),(name.str()).c_str(),15,0,3);
    name.str("");
    name<<"Endcap_z_"<<k<<"_PbxPmodule";
    e_z_PbxPmodule = new TH1F((name.str()).c_str(),(name.str()).c_str(),40,-300,300);
    name.str("");
    name<<"Endcap_rho_"<<k<<"_PbxPmodule";
    e_rho_PbxPmodule = new TH1F((name.str()).c_str(),(name.str()).c_str(),40,0,120);
    name.str("");
    name<<"Endcap_nstub_"<<k<<"_PbxPmodule";
    e_nstub_PbxPmodule = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,30);
    name.str("");
    Endcap_eta_PBX.push_back(e_eta_PBX);
    Endcap_eta_PBXCBCfail.push_back(e_eta_PBXCBCfail);
    Endcap_eta_PBXCICfail.push_back(e_eta_PBXCICfail);
    Endcap_type_PBX.push_back(e_type_PBX);
    Endcap_type_PBXCBCfail.push_back(e_type_PBXCBCfail);
    Endcap_type_PBXCICfail.push_back(e_type_PBXCICfail);
    Endcap_eta_PbxPmodule.push_back(e_eta_PbxPmodule);
    Endcap_eta_PbxPmoduleCBCfail.push_back(e_eta_PbxPmoduleCBCfail);
    Endcap_eta_PbxPmoduleCICfail.push_back(e_eta_PbxPmoduleCICfail);
    Endcap_z_PbxPmodule.push_back(e_z_PbxPmodule);
    Endcap_rho_PbxPmodule.push_back(e_rho_PbxPmodule);
    Endcap_nstub_PbxPmodule.push_back(e_nstub_PbxPmodule);
    }

  for (int k=0;k<6;++k){
    Barrel_eta_PBX[k]->Sumw2()          ;
    Barrel_eta_PBXCBCfail[k]->Sumw2()          ;
    Barrel_eta_PBXCICfail[k]->Sumw2()          ;
    Barrel_type_PBX[k]->Sumw2()         ;
    Barrel_type_PBXCBCfail[k]->Sumw2()         ;
    Barrel_type_PBXCICfail[k]->Sumw2()         ;
    Barrel_eta_PbxPmodule[k]->Sumw2()   ;
    Barrel_eta_PbxPmoduleCBCfail[k]->Sumw2()   ;
    Barrel_eta_PbxPmoduleCICfail[k]->Sumw2()   ;
    Barrel_z_PbxPmodule[k]->Sumw2()     ;
    Barrel_rho_PbxPmodule[k]->Sumw2()   ;
    Barrel_nstub_PbxPmodule[k]->Sumw2()   ;
    
    Endcap_eta_PBX[k]->Sumw2()          ;
    Endcap_eta_PBXCBCfail[k]->Sumw2()          ;
    Endcap_eta_PBXCICfail[k]->Sumw2()          ;
    Endcap_type_PBX[k]->Sumw2()         ;
    Endcap_type_PBXCBCfail[k]->Sumw2()         ;
    Endcap_type_PBXCICfail[k]->Sumw2()         ;
    Endcap_eta_PbxPmodule[k]->Sumw2()   ;
    Endcap_eta_PbxPmoduleCBCfail[k]->Sumw2()   ;
    Endcap_eta_PbxPmoduleCICfail[k]->Sumw2()   ;
    Endcap_z_PbxPmodule[k]->Sumw2()     ;
    Endcap_rho_PbxPmodule[k]->Sumw2()   ;
    Endcap_nstub_PbxPmodule[k]->Sumw2()   ;
  }

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(ientry) < 0) continue;
    displayProgress(jentry, nentries) ;
    float N = float(nentries); 
  
    for (unsigned int k=0; k<allstub_x->size(); ++k) {
      //only look at the z+ Disks
      bool zminusdisk = (!allstub_isBarrel->at(k) && allstub_module_z->at(k) <0);
      sEta.SetXYZ(allstub_x->at(k),allstub_y->at(k),allstub_z->at(k));
      mEta.SetXYZ(allstub_module_x->at(k),allstub_module_y->at(k),allstub_module_z->at(k));
      stub_eta->Fill(sEta.Eta(), 1/N);

      if(!zminusdisk) {
        stubsRate[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)]++;
        tmpstubsRate[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)]++;
        if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) stubsRateCBCfail[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)]++;
        if (allstub_trigDisplace->at(k)>400) stubsRateCICfail[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)]++;
        stubsRate_z[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)] = allstub_module_z->at(k);
        stubsRate_rho[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)] = sqrt(pow(allstub_module_x->at(k),2) + pow(allstub_module_y->at(k),2)) ;
        stubsRate_eta[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)] = mEta.Eta() ;
      }
//Barrel stubs 
      if(allstub_isBarrel->at(k)){
        stub_type->Fill(0.5, 1/N);
        Barrel_type_PBX[allstub_layer->at(k)-1]->Fill(0.5, 1/N);
        Barrel_eta_PBX[allstub_layer->at(k)-1]->Fill(sEta.Eta(), 1/N);
        if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) {
          Barrel_type_PBXCBCfail[allstub_layer->at(k)-1]->Fill(0.5, 1/N);
          Barrel_eta_PBXCBCfail[allstub_layer->at(k)-1]->Fill(sEta.Eta(), 1/N);}

        if (allstub_trigDisplace->at(k)>400) {
          Barrel_type_PBXCICfail[allstub_layer->at(k)-1]->Fill(0.5, 1/N);
          Barrel_eta_PBXCICfail[allstub_layer->at(k)-1]->Fill(sEta.Eta(), 1/N);}

        if(allstub_genuine->at(k)){
          Barrel_type_PBX[allstub_layer->at(k)-1]->Fill(1.5, 1/N);
          if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) Barrel_type_PBXCBCfail[allstub_layer->at(k)-1]->Fill(1.5, 1/N);
          if (allstub_trigDisplace->at(k)>400) Barrel_type_PBXCICfail[allstub_layer->at(k)-1]->Fill(1.5, 1/N);
          stub_type->Fill(1.5, 1/N);
        }
        if(allstub_isCombinatoric->at(k)){
          Barrel_type_PBX[allstub_layer->at(k)-1]->Fill(2.5, 1/N);
          if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) Barrel_type_PBXCBCfail[allstub_layer->at(k)-1]->Fill(2.5, 1/N);
          if (allstub_trigDisplace->at(k)>400) Barrel_type_PBXCICfail[allstub_layer->at(k)-1]->Fill(2.5, 1/N);
          stub_type->Fill(2.5, 1/N);
        }  
        if (allstub_isUnknown->at(k)){
          Barrel_type_PBX[allstub_layer->at(k)-1]->Fill(3.5, 1/N);
          if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) Barrel_type_PBXCBCfail[allstub_layer->at(k)-1]->Fill(3.5, 1/N);
          if (allstub_trigDisplace->at(k)>400) Barrel_type_PBXCICfail[allstub_layer->at(k)-1]->Fill(3.5, 1/N);
          stub_type->Fill(3.5, 1/N);
        }
      }
//Endcap stubs  
      if(!allstub_isBarrel->at(k)){

        stub_type->Fill(0.5, 1/N);
        Endcap_type_PBX[allstub_layer->at(k)-1]->Fill(0.5, 1/N);
        Endcap_eta_PBX[allstub_layer->at(k)-1]->Fill(sEta.Eta(), 1/N);

        if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) {
          Endcap_type_PBXCBCfail[allstub_layer->at(k)-1]->Fill(0.5, 1/N);
          Endcap_eta_PBXCBCfail[allstub_layer->at(k)-1]->Fill(sEta.Eta(), 1/N);}

        if (allstub_trigDisplace->at(k)>400) {
          Endcap_type_PBXCICfail[allstub_layer->at(k)-1]->Fill(0.5, 1/N);
          Endcap_eta_PBXCICfail[allstub_layer->at(k)-1]->Fill(sEta.Eta(), 1/N);}


        if(allstub_genuine->at(k)){
          Endcap_type_PBX[allstub_layer->at(k)-1]->Fill(1.5, 1/N);
          if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) Endcap_type_PBXCBCfail[allstub_layer->at(k)-1]->Fill(1.5, 1/N);
          if (allstub_trigDisplace->at(k)>400) Endcap_type_PBXCICfail[allstub_layer->at(k)-1]->Fill(1.5, 1/N);
          stub_type->Fill(1.5, 1/N);
        }
        if(allstub_isCombinatoric->at(k)){
          Endcap_type_PBX[allstub_layer->at(k)-1]->Fill(2.5, 1/N);
          if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) Endcap_type_PBXCBCfail[allstub_layer->at(k)-1]->Fill(2.5, 1/N);
          if (allstub_trigDisplace->at(k)>400) Endcap_type_PBXCICfail[allstub_layer->at(k)-1]->Fill(2.5, 1/N);
          stub_type->Fill(2.5, 1/N);
        }
        if (allstub_isUnknown->at(k)){
          Endcap_type_PBX[allstub_layer->at(k)-1]->Fill(3.5, 1/N);
          if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) Endcap_type_PBXCBCfail[allstub_layer->at(k)-1]->Fill(3.5, 1/N);
          if (allstub_trigDisplace->at(k)>400) Endcap_type_PBXCICfail[allstub_layer->at(k)-1]->Fill(3.5, 1/N);
          stub_type->Fill(3.5, 1/N);
        }
      }
    }
    for (int k=0;k<6;++k){
      for (int l=0;l<100;++l){
        for (int m=0;m<100;++m){
          if (stubsRate_rho[1][k][l][m]==0) continue;
          if (stubsRate_eta[1][k][l][m]<0.5 && stubsRate_rho[1][k][l][m]>0) Barrel_nstub_PbxPmodule[k]->Fill(tmpstubsRate[1][k][l][m]);
          if (stubsRate_eta[0][k][l][m]>2 && stubsRate_rho[0][k][l][m]>0) Endcap_nstub_PbxPmodule[k]->Fill(tmpstubsRate[0][k][l][m]);
          tmpstubsRate[1][k][l][m] = 0;
          tmpstubsRate[0][k][l][m] = 0;
        }
      }
    }      
  }

   Int_t n_lad_barrel[6] = {18,26,36,48,60,78};
   Int_t n_mod_barrel[6] = {31,35,39,24,24,24};
   Int_t n_lad_endcapF[15] = {20,24,24,28,32,32,36,40,40,44,52,60,64,72,76};
   Int_t n_lad_endcapL[15] = {28,28,32,36,36,40,44,52,56,64,72,76,100,100,100};

   TH2D *BL, *BLCBCfail, *BLCICfail;
   TH2D *EL, *ELCBCfail, *ELCICfail;

  for (int k=0;k<6;++k){
    eta_PbxPmodule = new TH1F("eta_PbxPmodule","eta_PbxPmodule",30,-3,3);
    eta_PbxPmodule->Sumw2();
    z_PbxPmodule   = new TH1F("z_PbxPmodule","z_PbxPmodule",40,-300,300);
    z_PbxPmodule->Sumw2();
    rho_PbxPmodule = new TH1F("rho_PbxPmodule","rho_PbxPmodule",40,0,120);
    rho_PbxPmodule->Sumw2();

    std::stringstream name;
    name<<"Barrel_Rate2D_"<<k<<"_PBX";
    BL = new TH2D((name.str()).c_str(),(name.str()).c_str(),n_mod_barrel[k],0,n_mod_barrel[k], n_lad_barrel[k],0,n_lad_barrel[k]);
    name.str("");
    name<<"Barrel_Rate2D_"<<k<<"_PBXCBCfail";
    BLCBCfail = new TH2D((name.str()).c_str(),(name.str()).c_str(),n_mod_barrel[k],0,n_mod_barrel[k], n_lad_barrel[k],0,n_lad_barrel[k]);
    name.str("");
    name<<"Barrel_Rate2D_"<<k<<"_PBXCICfail";
    BLCICfail = new TH2D((name.str()).c_str(),(name.str()).c_str(),n_mod_barrel[k],0,n_mod_barrel[k], n_lad_barrel[k],0,n_lad_barrel[k]);
    name.str("");

    for (int l=0;l<100;++l){
      for (int m=0;m<100;++m){
        Barrel_eta_PbxPmodule[k]->Fill(stubsRate_eta[1][k][l][m], float(stubsRate[1][k][l][m])/float(nentries));
        if(stubsRate[1][k][l][m]>0) Barrel_eta_PbxPmoduleCBCfail[k]->Fill(stubsRate_eta[1][k][l][m], float(stubsRateCBCfail[1][k][l][m])/float(stubsRate[1][k][l][m]));
        if(stubsRate[1][k][l][m]>0) Barrel_eta_PbxPmoduleCICfail[k]->Fill(stubsRate_eta[1][k][l][m], float(stubsRateCICfail[1][k][l][m])/float(stubsRate[1][k][l][m]));
        Barrel_z_PbxPmodule[k]  ->Fill(stubsRate_z[1][k][l][m]  , float(stubsRate[1][k][l][m])/float(nentries));
        Barrel_rho_PbxPmodule[k]->Fill(stubsRate_rho[1][k][l][m], float(stubsRate[1][k][l][m])/float(nentries));
        BL->SetBinContent(m+1,l+1, float(stubsRate[1][k][l][m])/float(nentries));        
        if(stubsRate[1][k][l][m]>0) BLCBCfail->SetBinContent(m+1,l+1, float(stubsRateCBCfail[1][k][l][m])/float(stubsRate[1][k][l][m]));
        if(stubsRate[1][k][l][m]>0) BLCICfail->SetBinContent(m+1,l+1, float(stubsRateCICfail[1][k][l][m])/float(stubsRate[1][k][l][m]));

        if(stubsRate_rho[1][k][l][m]>0) {
          eta_PbxPmodule->Fill(stubsRate_eta[1][k][l][m]);
          z_PbxPmodule->Fill(stubsRate_z[1][k][l][m]);
          rho_PbxPmodule->Fill(stubsRate_rho[1][k][l][m]);
        }

      }
    }
    Barrel_2D.push_back(BL);
    Barrel_2DCBCfail.push_back(BLCBCfail);
    Barrel_2DCICfail.push_back(BLCICfail);
    Barrel_eta_PbxPmodule[k]->Divide(eta_PbxPmodule);
    Barrel_eta_PbxPmoduleCBCfail[k]->Divide(eta_PbxPmodule);
    Barrel_eta_PbxPmoduleCICfail[k]->Divide(eta_PbxPmodule);
    Barrel_z_PbxPmodule[k]->Divide(z_PbxPmodule);
    Barrel_rho_PbxPmodule[k]->Divide(rho_PbxPmodule);
    delete eta_PbxPmodule;
    delete z_PbxPmodule;
    delete rho_PbxPmodule;
  }
  for (int k=0;k<5;++k){
    eta_PbxPmodule = new TH1F("eta_PbxPmodule","eta_PbxPmodule",15,0,3);
    eta_PbxPmodule->Sumw2();
    z_PbxPmodule   = new TH1F("z_PbxPmodule","z_PbxPmodule",40,-300,300);
    z_PbxPmodule->Sumw2();
    rho_PbxPmodule = new TH1F("rho_PbxPmodule","rho_PbxPmodule",40,0,120);
    rho_PbxPmodule->Sumw2();

    std::stringstream name;
    int RING = 0;
    int nbins = 0;
    for (int l=0;l<15;++l){
       RING = l ;
       nbins =n_lad_endcapF[l];
       if (k>1) {
         RING = l + 3;
         nbins =n_lad_endcapL[l];
       }
       name<<"Endcap_Rate2D_"<<k<<"_PBX_"<<l;
       EL = new TH2D((name.str()).c_str(),(name.str()).c_str(),nbins,0, 2*TMath::Pi(), 15,0,15);
       name.str("");
       name<<"Endcap_Rate2D_"<<k<<"_PBXCBCfail_"<<l;
       ELCBCfail = new TH2D((name.str()).c_str(),(name.str()).c_str(),nbins,0, 2*TMath::Pi(), 15,0,15);
       name.str("");
       name<<"Endcap_Rate2D_"<<k<<"_PBXCICfail_"<<l;
       ELCICfail = new TH2D((name.str()).c_str(),(name.str()).c_str(),nbins,0, 2*TMath::Pi(), 15,0,15);
       name.str("");

      for (int m=0;m<100;++m){
        Endcap_eta_PbxPmodule[k]->Fill(stubsRate_eta[0][k][l][m], float(stubsRate[0][k][l][m])/float(nentries));
        if(stubsRate[0][k][l][m]>0) Endcap_eta_PbxPmoduleCBCfail[k]->Fill(stubsRate_eta[0][k][l][m], float(stubsRateCBCfail[0][k][l][m])/float(stubsRate[0][k][l][m]));
        if(stubsRate[0][k][l][m]>0) Endcap_eta_PbxPmoduleCICfail[k]->Fill(stubsRate_eta[0][k][l][m], float(stubsRateCICfail[0][k][l][m])/float(stubsRate[0][k][l][m]));
        Endcap_z_PbxPmodule[k]  ->Fill(stubsRate_z[0][k][l][m]  , float(stubsRate[0][k][l][m])/float(nentries));
        Endcap_rho_PbxPmodule[k]->Fill(stubsRate_rho[0][k][l][m], float(stubsRate[0][k][l][m])/float(nentries));
        EL->SetBinContent(m+1,RING+1, float(stubsRate[0][k][l][m])/float(nentries));
        if(stubsRate[0][k][l][m]>0) ELCBCfail->SetBinContent(m+1,RING+1, float(stubsRateCBCfail[0][k][l][m])/float(stubsRate[0][k][l][m]));
        if(stubsRate[0][k][l][m]>0) ELCICfail->SetBinContent(m+1,RING+1, float(stubsRateCICfail[0][k][l][m])/float(stubsRate[0][k][l][m]));

        if(stubsRate_rho[0][k][l][m]>0) {
          eta_PbxPmodule->Fill(stubsRate_eta[0][k][l][m]);
          z_PbxPmodule->Fill(stubsRate_z[0][k][l][m]);
          rho_PbxPmodule->Fill(stubsRate_rho[0][k][l][m]);
        }
      }
      Endcap_2D.push_back(EL);
      Endcap_2DCBCfail.push_back(ELCBCfail);
      Endcap_2DCICfail.push_back(ELCICfail);
    }
    Endcap_eta_PbxPmodule[k]->Divide(eta_PbxPmodule);
    Endcap_eta_PbxPmoduleCBCfail[k]->Divide(eta_PbxPmodule);
    Endcap_eta_PbxPmoduleCICfail[k]->Divide(eta_PbxPmodule);
    Endcap_z_PbxPmodule[k]->Divide(z_PbxPmodule);
    Endcap_rho_PbxPmodule[k]->Divide(rho_PbxPmodule);
    delete eta_PbxPmodule;
    delete z_PbxPmodule;
    delete rho_PbxPmodule;
  }

  const Int_t nx = 4;
  const char *type[nx] = {"All","Genuine","Combinatoric","Unknown"};

  Int_t i;
  for (i=1;i<=nx;i++) {
      stub_type->GetXaxis()->SetBinLabel(i,type[i-1]);
    for (int k=0;k<6;++k){
      Barrel_type_PBX[k]->GetXaxis()->SetBinLabel(i,type[i-1]);
      Barrel_type_PBXCBCfail[k]->GetXaxis()->SetBinLabel(i,type[i-1]);
      Barrel_type_PBXCICfail[k]->GetXaxis()->SetBinLabel(i,type[i-1]);
      Endcap_type_PBX[k]->GetXaxis()->SetBinLabel(i,type[i-1]);
      Endcap_type_PBXCBCfail[k]->GetXaxis()->SetBinLabel(i,type[i-1]);
      Endcap_type_PBXCICfail[k]->GetXaxis()->SetBinLabel(i,type[i-1]);
    }
  }
  for (int k=0;k<6;++k){
    Barrel_eta_PBXCBCfail[k]->Divide(Barrel_eta_PBX[k]);
    Barrel_eta_PBXCICfail[k]->Divide(Barrel_eta_PBX[k]);
    Barrel_type_PBXCBCfail[k]->Divide(Barrel_type_PBX[k]);
    Barrel_type_PBXCICfail[k]->Divide(Barrel_type_PBX[k]);
  }
  TFile *f = new TFile(fname+"_output.root","RECREATE");
  f->cd();
  for (int k=0;k<6;++k){
    Barrel_2D[k]          ->Write("",TObject::kOverwrite);
    Barrel_2DCBCfail[k]          ->Write("",TObject::kOverwrite);
    Barrel_2DCICfail[k]          ->Write("",TObject::kOverwrite);
    Barrel_eta_PBX[k]          ->Write("",TObject::kOverwrite);
    Barrel_eta_PBXCBCfail[k]   ->Write("",TObject::kOverwrite);
    Barrel_eta_PBXCICfail[k]   ->Write("",TObject::kOverwrite);
    Barrel_type_PBX[k]         ->Write("",TObject::kOverwrite);
    Barrel_type_PBXCBCfail[k]  ->Write("",TObject::kOverwrite);
    Barrel_type_PBXCICfail[k]  ->Write("",TObject::kOverwrite);
    Barrel_eta_PbxPmodule[k]   ->Write("",TObject::kOverwrite);
    Barrel_eta_PbxPmoduleCBCfail[k]   ->Write("",TObject::kOverwrite);
    Barrel_eta_PbxPmoduleCICfail[k]   ->Write("",TObject::kOverwrite);
    Barrel_z_PbxPmodule[k]     ->Write("",TObject::kOverwrite);
    Barrel_rho_PbxPmodule[k]   ->Write("",TObject::kOverwrite);
    Barrel_nstub_PbxPmodule[k] ->Write("",TObject::kOverwrite);
 }
  for (int k=0;k<5;++k){
    Endcap_eta_PBXCBCfail[k]->Divide(Barrel_eta_PBX[k]);
    Endcap_eta_PBXCICfail[k]->Divide(Barrel_eta_PBX[k]);
    Endcap_type_PBXCBCfail[k]->Divide(Barrel_type_PBX[k]);
    Endcap_type_PBXCICfail[k]->Divide(Barrel_type_PBX[k]);
  }
  for (int k=0;k<Endcap_2D.size();++k){
    Endcap_2D[k]               ->Write("",TObject::kOverwrite);
    Endcap_2DCBCfail[k]               ->Write("",TObject::kOverwrite);
    Endcap_2DCICfail[k]               ->Write("",TObject::kOverwrite);
  }
  for (int k=0;k<5;++k){
    Endcap_eta_PBX[k]          ->Write("",TObject::kOverwrite);
    Endcap_eta_PBXCBCfail[k]   ->Write("",TObject::kOverwrite);
    Endcap_eta_PBXCICfail[k]   ->Write("",TObject::kOverwrite);
    Endcap_type_PBX[k]         ->Write("",TObject::kOverwrite);
    Endcap_type_PBXCBCfail[k]  ->Write("",TObject::kOverwrite);
    Endcap_type_PBXCICfail[k]  ->Write("",TObject::kOverwrite);
    Endcap_eta_PbxPmodule[k]   ->Write("",TObject::kOverwrite);
    Endcap_eta_PbxPmoduleCBCfail[k]   ->Write("",TObject::kOverwrite);
    Endcap_eta_PbxPmoduleCICfail[k]   ->Write("",TObject::kOverwrite);
    Endcap_z_PbxPmodule[k]     ->Write("",TObject::kOverwrite);
    Endcap_rho_PbxPmodule[k]   ->Write("",TObject::kOverwrite);
    Endcap_nstub_PbxPmodule[k] ->Write("",TObject::kOverwrite);
  }
  stub_type->Write("",TObject::kOverwrite);
  stub_eta->Write("",TObject::kOverwrite);

  f->Close();

  for (int k=0;k<6;++k){
    delete Barrel_2D[k];
    delete Barrel_2DCBCfail[k];
    delete Barrel_2DCICfail[k];
    delete Barrel_eta_PBX[k]          ;
    delete Barrel_eta_PBXCBCfail[k]   ;
    delete Barrel_eta_PBXCICfail[k]   ;
    delete Barrel_type_PBX[k]         ;
    delete Barrel_type_PBXCBCfail[k]  ;
    delete Barrel_type_PBXCICfail[k]  ;
    delete Barrel_eta_PbxPmodule[k]   ;
    delete Barrel_eta_PbxPmoduleCBCfail[k]   ;
    delete Barrel_eta_PbxPmoduleCICfail[k]   ;
    delete Barrel_z_PbxPmodule[k]     ;
    delete Barrel_rho_PbxPmodule[k]   ;
    delete Barrel_nstub_PbxPmodule[k]   ;
    }
  for (int k=0;k<6;++k){
    delete Endcap_eta_PBX[k]          ;
    delete Endcap_eta_PBXCBCfail[k]   ;
    delete Endcap_eta_PBXCICfail[k]   ;
    delete Endcap_type_PBX[k]         ;
    delete Endcap_type_PBXCBCfail[k]  ;
    delete Endcap_type_PBXCICfail[k]  ;
    delete Endcap_eta_PbxPmodule[k]   ;
    delete Endcap_eta_PbxPmoduleCBCfail[k]   ;
    delete Endcap_eta_PbxPmoduleCICfail[k]   ;
    delete Endcap_z_PbxPmodule[k]     ;
    delete Endcap_rho_PbxPmodule[k]   ;
    delete Endcap_nstub_PbxPmodule[k]   ;

  }

  for (int k=0;k<Endcap_2D.size();++k){
    delete Endcap_2D[k];
    delete Endcap_2DCBCfail[k];
    delete Endcap_2DCICfail[k];
  }

  delete stub_type;
  delete stub_eta;
}
