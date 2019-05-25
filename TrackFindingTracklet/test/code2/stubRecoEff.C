#define stubRecoEff_cxx
#include "stubRecoEff.h"
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


void stubRecoEff::eff(TString fname, TString pname)
{

typedef vector<int> Dim1;
typedef vector<Dim1> Dim2;
typedef vector<Dim2> Dim3;
typedef vector<Dim3> Dim4;
typedef vector<Dim4> Dim5;
typedef vector<Dim5> Dim6;
 
if (fChain == 0) return;
//Long64_t nentries = fChain->GetEntriesFast();
Int_t nentries = (Int_t) fChain->GetEntries();

Long64_t nbytes = 0, nb = 0;


cout<<nentries<<endl;

std::vector<TH1F*> Bhists_eta;
std::vector<TH1F*> Bhists_pt;
std::vector<TH1F*> Bhists_tot_eta;
std::vector<TH1F*> Bhists_tot_pt;


std::vector<TH1F*> Ehists_eta;
std::vector<TH1F*> Ehists_pt;
std::vector<TH1F*> Ehists_tot_eta;
std::vector<TH1F*> Ehists_tot_pt;

for (int k=0;k<6;++k){
  std::stringstream name;
  name <<k;
  TH1F *b_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"pt";
  TH1F *b_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Bhists_eta.push_back(b_eta);
  Bhists_pt.push_back(b_pt);
  name <<k;
  TH1F *b_tot_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"tot";
  TH1F *b_tot_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Bhists_tot_eta.push_back(b_tot_eta);
  Bhists_tot_pt.push_back(b_tot_pt);


  name <<"E";
  TH1F *e_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"pt";
  TH1F *e_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Ehists_eta.push_back(e_eta);
  Ehists_pt.push_back(e_pt);
  name <<"E";
  TH1F *e_tot_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"tot";
  TH1F *e_tot_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Ehists_tot_eta.push_back(e_tot_eta);
  Ehists_tot_pt.push_back(e_tot_pt);

}
for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (Cut(ientry) < 0) continue;
  displayProgress(jentry, nentries) ;
  int pid = 0;
  if (pname == "mu") pid = 13;
  if (pname == "ele") pid = 11;
  if (pname == "pi") pid = 211;
  for (unsigned int k=0; k<stubEff_tp_pt->size(); ++k) {
    if(abs(stubEff_tp_pdgid->at(k))!=pid) continue;
    if(abs(stubEff_tp_pt->at(k))<2) continue;

//if (2*stubEff_EL1->at(k) != clustEff_EL1->at(k)) cout<<"#stub= "<<stubEff_EL1->at(k)<<" #clusters = "<<clustEff_EL1->at(k) <<" eta ="<<stubEff_tp_eta->at(k)<<" pt="<<stubEff_tp_pt->at(k)<<endl;

    Bhists_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL1->at(k)));
    Bhists_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL2->at(k)));
    Bhists_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL3->at(k)));
    Bhists_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL4->at(k)));
    Bhists_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL5->at(k)));
    Bhists_eta[5]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL6->at(k)));

    Ehists_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL1->at(k)));
    Ehists_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL2->at(k)));
    Ehists_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL3->at(k)));
    Ehists_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL4->at(k)));
    Ehists_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL5->at(k)));

    Bhists_tot_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL1->at(k)));
    Bhists_tot_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL2->at(k)));
    Bhists_tot_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL3->at(k)));
    Bhists_tot_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL4->at(k)));
    Bhists_tot_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL5->at(k)));
    Bhists_tot_eta[5]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL6->at(k)));

    Ehists_tot_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL1->at(k)));
    Ehists_tot_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL2->at(k)));
    Ehists_tot_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL3->at(k)));
    Ehists_tot_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL4->at(k)));
    Ehists_tot_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL5->at(k)));


    if(abs(stubEff_tp_eta->at(k)) < 0.6){
      Bhists_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL1->at(k)));
      Bhists_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL2->at(k)));
      Bhists_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL3->at(k)));
      Bhists_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL4->at(k)));
      Bhists_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL5->at(k)));
      Bhists_pt[5]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL6->at(k)));

      Bhists_tot_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL1->at(k)));
      Bhists_tot_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL2->at(k)));
      Bhists_tot_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL3->at(k)));
      Bhists_tot_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL4->at(k)));
      Bhists_tot_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL5->at(k)));
      Bhists_tot_pt[5]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL6->at(k)));
    }
    if(abs(stubEff_tp_eta->at(k)) > 1.7 && abs(stubEff_tp_eta->at(k))<2.4) {
    Ehists_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL1->at(k)));
    Ehists_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL2->at(k)));
    Ehists_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL3->at(k)));
    Ehists_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL4->at(k)));
    Ehists_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL5->at(k)));

    Ehists_tot_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL1->at(k)));
    Ehists_tot_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL2->at(k)));
    Ehists_tot_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL3->at(k)));
    Ehists_tot_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL4->at(k)));
    Ehists_tot_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL5->at(k)));
    }
  }
}


Bhists_pt[0]->SetMarkerStyle(kOpenSquare);
Bhists_pt[1]->SetMarkerStyle(kFullCircle);
Bhists_pt[2]->SetMarkerStyle(kFullSquare);
Bhists_pt[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_pt[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_pt[5]->SetMarkerStyle(kOpenCircle);

Bhists_eta[0]->SetMarkerStyle(kOpenSquare);
Bhists_eta[1]->SetMarkerStyle(kFullCircle);
Bhists_eta[2]->SetMarkerStyle(kFullSquare);
Bhists_eta[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_eta[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_eta[5]->SetMarkerStyle(kOpenCircle);

Ehists_pt[0]->SetMarkerStyle(kOpenSquare);
Ehists_pt[1]->SetMarkerStyle(kFullCircle);
Ehists_pt[2]->SetMarkerStyle(kFullSquare);
Ehists_pt[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_pt[4]->SetMarkerStyle(kFullTriangleDown);
Ehists_pt[5]->SetMarkerStyle(kOpenCircle);

Ehists_eta[0]->SetMarkerStyle(kOpenSquare);
Ehists_eta[1]->SetMarkerStyle(kFullCircle);
Ehists_eta[2]->SetMarkerStyle(kFullSquare);
Ehists_eta[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_eta[4]->SetMarkerStyle(kFullTriangleDown);

Bhists_tot_pt[0]->SetMarkerStyle(kOpenSquare);
Bhists_tot_pt[1]->SetMarkerStyle(kFullCircle);
Bhists_tot_pt[2]->SetMarkerStyle(kFullSquare);
Bhists_tot_pt[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_tot_pt[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_tot_pt[5]->SetMarkerStyle(kOpenCircle);

Bhists_tot_eta[0]->SetMarkerStyle(kOpenSquare);
Bhists_tot_eta[1]->SetMarkerStyle(kFullCircle);
Bhists_tot_eta[2]->SetMarkerStyle(kFullSquare);
Bhists_tot_eta[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_tot_eta[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_tot_eta[5]->SetMarkerStyle(kOpenCircle);

Ehists_tot_pt[0]->SetMarkerStyle(kOpenSquare);
Ehists_tot_pt[1]->SetMarkerStyle(kFullCircle);
Ehists_tot_pt[2]->SetMarkerStyle(kFullSquare);
Ehists_tot_pt[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_tot_pt[4]->SetMarkerStyle(kFullTriangleDown);
Ehists_tot_pt[5]->SetMarkerStyle(kOpenCircle);

Ehists_tot_eta[0]->SetMarkerStyle(kOpenSquare);
Ehists_tot_eta[1]->SetMarkerStyle(kFullCircle);
Ehists_tot_eta[2]->SetMarkerStyle(kFullSquare);
Ehists_tot_eta[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_tot_eta[4]->SetMarkerStyle(kFullTriangleDown);

Bhists_pt[0]->SetTitle("Barrel");
Bhists_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Bhists_pt[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_pt[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_pt[0]->GetYaxis()->SetTitleOffset(0.5);

Bhists_eta[0]->SetTitle("Barrel");
Bhists_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Bhists_eta[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_eta[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_eta[0]->GetYaxis()->SetTitleOffset(0.5);

Ehists_pt[0]->SetTitle("Endcaps");
Ehists_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Ehists_pt[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_pt[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_pt[0]->GetYaxis()->SetTitleOffset(0.5);


Ehists_eta[0]->SetTitle("Endcaps");
Ehists_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Ehists_eta[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_eta[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_eta[0]->GetYaxis()->SetTitleOffset(0.5);


Bhists_tot_pt[0]->SetTitle("Barrel");
Bhists_tot_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Bhists_tot_pt[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_tot_pt[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_tot_pt[0]->GetYaxis()->SetTitleOffset(0.5);

Bhists_tot_eta[0]->SetTitle("Barrel");
Bhists_tot_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Bhists_tot_eta[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_tot_eta[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_tot_eta[0]->GetYaxis()->SetTitleOffset(0.5);

Ehists_tot_pt[0]->SetTitle("Endcaps");
Ehists_tot_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Ehists_tot_pt[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_tot_pt[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_tot_pt[0]->GetYaxis()->SetTitleOffset(0.5);


Ehists_tot_eta[0]->SetTitle("Endcaps");
Ehists_tot_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Ehists_tot_eta[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_tot_eta[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_tot_eta[0]->GetYaxis()->SetTitleOffset(0.5);


TLegend* leg = new TLegend(0.9,0.7,1,1);
leg->SetFillStyle ( 0);
leg->SetFillColor ( 0);
leg->SetBorderSize( 0);
leg->AddEntry(Bhists_pt[0], "Layer 1"                           , "p");
leg->AddEntry(Bhists_pt[1], "Layer 2"                           , "p");
leg->AddEntry(Bhists_pt[2], "Layer 3"                           , "p");
leg->AddEntry(Bhists_pt[3], "Layer 4"                           , "p");
leg->AddEntry(Bhists_pt[4], "Layer 5"                           , "p");
leg->AddEntry(Bhists_pt[5], "Layer 6"                          , "p");
leg->Draw("same");

TLegend* eleg = new TLegend(0.9,0.7,1,1);
eleg->SetFillStyle ( 0);
eleg->SetFillColor ( 0);
eleg->SetBorderSize( 0);
eleg->AddEntry(Ehists_pt[0], "Disk 1"                           , "p");
eleg->AddEntry(Ehists_pt[1], "Disk 2"                           , "p");
eleg->AddEntry(Ehists_pt[2], "Disk 3"                           , "p");
eleg->AddEntry(Ehists_pt[3], "Disk 4"                           , "p");
eleg->AddEntry(Ehists_pt[4], "Disk 5"                           , "p");

TCanvas *c;
TCanvas *ec;
TPad *pad1;
TPad *pad2;
TPad *epad1;
TPad *epad2;


//////DRAW N stubs
c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,0.9,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0,0,0.9,0.5);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();
pad1->cd();
gStyle->SetOptStat(0);

Bhists_pt[0]->GetYaxis()->SetTitle("Number of Stubs");
Bhists_eta[0]->GetYaxis()->SetTitle("Number of Stub");
Ehists_pt[0]->GetYaxis()->SetTitle("Number of Stubs");
Ehists_eta[0]->GetYaxis()->SetTitle("Number of Stub");

for (int k=0;k<6;++k){
  Bhists_pt[k]->SetMarkerColor(k+1);
  Bhists_pt[k]->Draw("p HIST SAME");
}

pad2->cd();
for (int k=0;k<5;++k){
  Ehists_pt[k]->SetMarkerColor(k+1);
  Ehists_pt[k]->Draw("P HIST SAME");
}
eleg->Draw("same");
c->Print(fname+"__"+pname+"__"+"pt_stubNumber.png","png");

ec = new TCanvas("ec","ec",800,600);
epad1 = new TPad("epad1", "epad1",0,0.5,0.9,1);
epad1->SetGrid(1,1);
epad1->SetBottomMargin(0.2);
epad1->Draw();
epad2 = new TPad("epad2", "epad2",0,0,0.9,0.5);
epad2->SetGrid(1,1);
epad2->SetBottomMargin(0.2);
epad2->Draw();
epad1->cd();


for (int k=0;k<6;++k){
  Bhists_eta[k]->SetMarkerColor(k+1);
  Bhists_eta[k]->Draw("P HIST SAME");
}

leg->Draw("same");
epad2->cd();
for (int k=0;k<5;++k){
  Ehists_eta[k]->SetMarkerColor(k+1);
  Ehists_eta[k]->Draw("P HIST SAME");
}
eleg->Draw("same");
ec->Print(fname+"__"+pname+"__"+"eta_stubNumber.png","png");
delete pad1;
delete pad2;
delete c;
delete epad1;
delete epad2;
delete ec;

//Draw N clusters
c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,0.9,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0,0,0.9,0.5);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();
pad1->cd();
gStyle->SetOptStat(0);

Bhists_tot_pt[0]->GetYaxis()->SetTitle("Number of clusters");
Bhists_tot_eta[0]->GetYaxis()->SetTitle("Number of clusters");
Ehists_tot_pt[0]->GetYaxis()->SetTitle("Number of clusters");
Ehists_tot_eta[0]->GetYaxis()->SetTitle("Number of clusters");

for (int k=0;k<6;++k){
  Bhists_tot_pt[k]->SetMarkerColor(k+1);
  Bhists_tot_pt[k]->Draw("p HIST SAME");
}

pad2->cd();
for (int k=0;k<5;++k){
  Ehists_tot_pt[k]->SetMarkerColor(k+1);
  Ehists_tot_pt[k]->Draw("P HIST SAME");
}
eleg->Draw("same");
c->Print(fname+"__"+pname+"__"+"pt_clusterNumber.png","png");

ec = new TCanvas("ec","ec",800,600);
epad1 = new TPad("epad1", "epad1",0,0.5,0.9,1);
epad1->SetGrid(1,1);
epad1->SetBottomMargin(0.2);
epad1->Draw();
epad2 = new TPad("epad2", "epad2",0,0,0.9,0.5);
epad2->SetGrid(1,1);
epad2->SetBottomMargin(0.2);
epad2->Draw();
epad1->cd();


for (int k=0;k<6;++k){
  Bhists_tot_eta[k]->SetMarkerColor(k+1);
  Bhists_tot_eta[k]->Draw("P HIST SAME");
}

leg->Draw("same");
epad2->cd();
for (int k=0;k<5;++k){
  Ehists_tot_eta[k]->SetMarkerColor(k+1);
  Ehists_tot_eta[k]->Draw("P HIST SAME");
}
eleg->Draw("same");
ec->Print(fname+"__"+pname+"__"+"eta_clusterNumber.png","png");
delete pad1;
delete pad2;
delete c;
delete epad1;
delete epad2;
delete ec;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,0.9,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0,0,0.9,0.5);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();
pad1->cd();
gStyle->SetOptStat(0);

Bhists_pt[0]->GetYaxis()->SetTitle("Stub efficiency");
Bhists_eta[0]->GetYaxis()->SetTitle("Stub efficiency");
Ehists_pt[0]->GetYaxis()->SetTitle("Stub efficiency");
Ehists_eta[0]->GetYaxis()->SetTitle("Stub efficiency");
Bhists_pt[0]->GetYaxis()->SetRangeUser(0.8,1.1);
Bhists_eta[0]->GetYaxis()->SetRangeUser(0.8,1.1);
Ehists_pt[0]->GetYaxis()->SetRangeUser(0.8,1.1);
Ehists_eta[0]->GetYaxis()->SetRangeUser(0.8,1.1);

for (int k=0;k<6;++k){
  Bhists_pt[k]->Divide(Bhists_tot_pt[k]);
  Bhists_pt[k]->SetMarkerColor(k+1);
  Bhists_pt[k]->Draw("p HIST SAME");
}

pad2->cd();
for (int k=0;k<5;++k){
  Ehists_pt[k]->Divide(Ehists_tot_pt[k]);
  Ehists_pt[k]->SetMarkerColor(k+1);
  Ehists_pt[k]->Draw("P HIST SAME");
}
eleg->Draw("same");
c->Print(fname+"__"+pname+"__"+"pt_stubEff.png","png");

ec = new TCanvas("ec","ec",800,600);
epad1 = new TPad("epad1", "epad1",0,0.5,0.9,1);
epad1->SetGrid(1,1);
epad1->SetBottomMargin(0.2);
epad1->Draw();
epad2 = new TPad("epad2", "epad2",0,0,0.9,0.5);
epad2->SetGrid(1,1);
epad2->SetBottomMargin(0.2);
epad2->Draw();
epad1->cd();


for (int k=0;k<6;++k){
  Bhists_eta[k]->Divide(Bhists_tot_eta[k]);
  Bhists_eta[k]->SetMarkerColor(k+1);
  Bhists_eta[k]->Draw("P HIST SAME");
}

leg->Draw("same");
epad2->cd();
for (int k=0;k<5;++k){
  Ehists_eta[k]->Divide(Ehists_tot_eta[k]);
  Ehists_eta[k]->SetMarkerColor(k+1);
  Ehists_eta[k]->Draw("P HIST SAME");
}
eleg->Draw("same");
ec->Print(fname+"__"+pname+"__"+"eta_stubEff.png","png");
delete pad1;
delete pad2;
delete c;
delete epad1;
delete epad2;
delete ec;
}


/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void stubRecoEff::eff2(TString fname, TString pname)
{

typedef vector<int> Dim1;
typedef vector<Dim1> Dim2;
typedef vector<Dim2> Dim3;
typedef vector<Dim3> Dim4;
typedef vector<Dim4> Dim5;
typedef vector<Dim5> Dim6;
 
if (fChain == 0) return;
//Long64_t nentries = fChain->GetEntriesFast();
Int_t nentries = (Int_t) fChain->GetEntries();

Long64_t nbytes = 0, nb = 0;


cout<<nentries<<endl;

std::vector<TH1F*> Bhists_eta;
std::vector<TH1F*> Bhists_pt;
std::vector<TH1F*> Bhists_tot_eta;
std::vector<TH1F*> Bhists_tot_pt;


std::vector<TH1F*> Ehists_eta;
std::vector<TH1F*> Ehists_pt;
std::vector<TH1F*> Ehists_tot_eta;
std::vector<TH1F*> Ehists_tot_pt;

for (int k=0;k<6;++k){
  std::stringstream name;
  name <<k;
  TH1F *b_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"pt";
  TH1F *b_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Bhists_eta.push_back(b_eta);
  Bhists_pt.push_back(b_pt);
  name <<k;
  TH1F *b_tot_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"tot";
  TH1F *b_tot_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Bhists_tot_eta.push_back(b_tot_eta);
  Bhists_tot_pt.push_back(b_tot_pt);


  name <<"E";
  TH1F *e_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"pt";
  TH1F *e_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Ehists_eta.push_back(e_eta);
  Ehists_pt.push_back(e_pt);
  name <<"E";
  TH1F *e_tot_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"tot";
  TH1F *e_tot_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Ehists_tot_eta.push_back(e_tot_eta);
  Ehists_tot_pt.push_back(e_tot_pt);

}
for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (Cut(ientry) < 0) continue;

  int pid = 0;
  if (pname == "mu") pid = 13;
  if (pname == "ele") pid = 11;
  if (pname == "pi") pid = 211;
  for (unsigned int k=0; k<stubEff_tp_pt->size(); ++k) {
    if(abs(stubEff_tp_pdgid->at(k))!=pid) continue;

//if (2*stubEff_EL1->at(k) != clustEff_EL1->at(k)) cout<<"#stub= "<<stubEff_EL1->at(k)<<" #clusters = "<<clustEff_EL1->at(k) <<" eta ="<<stubEff_tp_eta->at(k)<<" pt="<<stubEff_tp_pt->at(k)<<endl;

    Bhists_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL1->at(k)));
    Bhists_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL2->at(k)));
    Bhists_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL3->at(k)));
    Bhists_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL4->at(k)));
    Bhists_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL5->at(k)));
    Bhists_eta[5]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_BL6->at(k)));

    Ehists_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL1->at(k)));
    Ehists_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL2->at(k)));
    Ehists_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL3->at(k)));
    Ehists_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL4->at(k)));
    Ehists_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(2.*stubEff_EL5->at(k)));

    Bhists_tot_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL1->at(k)));
    Bhists_tot_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL2->at(k)));
    Bhists_tot_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL3->at(k)));
    Bhists_tot_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL4->at(k)));
    Bhists_tot_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL5->at(k)));
    Bhists_tot_eta[5]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL6->at(k)));

    Ehists_tot_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL1->at(k)));
    Ehists_tot_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL2->at(k)));
    Ehists_tot_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL3->at(k)));
    Ehists_tot_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL4->at(k)));
    Ehists_tot_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL5->at(k)));


    if(abs(stubEff_tp_eta->at(k)) < 0.6){
      Bhists_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL1->at(k)));
      Bhists_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL2->at(k)));
      Bhists_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL3->at(k)));
      Bhists_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL4->at(k)));
      Bhists_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL5->at(k)));
      Bhists_pt[5]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_BL6->at(k)));

      Bhists_tot_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL1->at(k)));
      Bhists_tot_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL2->at(k)));
      Bhists_tot_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL3->at(k)));
      Bhists_tot_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL4->at(k)));
      Bhists_tot_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL5->at(k)));
      Bhists_tot_pt[5]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL6->at(k)));
    }
    if(abs(stubEff_tp_eta->at(k)) > 1.7 && abs(stubEff_tp_eta->at(k))<2.4) {
    Ehists_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL1->at(k)));
    Ehists_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL2->at(k)));
    Ehists_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL3->at(k)));
    Ehists_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL4->at(k)));
    Ehists_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(2*stubEff_EL5->at(k)));

    Ehists_tot_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL1->at(k)));
    Ehists_tot_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL2->at(k)));
    Ehists_tot_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL3->at(k)));
    Ehists_tot_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL4->at(k)));
    Ehists_tot_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL5->at(k)));
    }
  }
}


Bhists_pt[0]->SetMarkerStyle(kOpenSquare);
Bhists_pt[1]->SetMarkerStyle(kFullCircle);
Bhists_pt[2]->SetMarkerStyle(kFullSquare);
Bhists_pt[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_pt[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_pt[5]->SetMarkerStyle(kOpenCircle);

Bhists_eta[0]->SetMarkerStyle(kOpenSquare);
Bhists_eta[1]->SetMarkerStyle(kFullCircle);
Bhists_eta[2]->SetMarkerStyle(kFullSquare);
Bhists_eta[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_eta[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_eta[5]->SetMarkerStyle(kOpenCircle);

Ehists_pt[0]->SetMarkerStyle(kOpenSquare);
Ehists_pt[1]->SetMarkerStyle(kFullCircle);
Ehists_pt[2]->SetMarkerStyle(kFullSquare);
Ehists_pt[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_pt[4]->SetMarkerStyle(kFullTriangleDown);
Ehists_pt[5]->SetMarkerStyle(kOpenCircle);

Ehists_eta[0]->SetMarkerStyle(kOpenSquare);
Ehists_eta[1]->SetMarkerStyle(kFullCircle);
Ehists_eta[2]->SetMarkerStyle(kFullSquare);
Ehists_eta[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_eta[4]->SetMarkerStyle(kFullTriangleDown);

Bhists_tot_pt[0]->SetMarkerStyle(kOpenSquare);
Bhists_tot_pt[1]->SetMarkerStyle(kFullCircle);
Bhists_tot_pt[2]->SetMarkerStyle(kFullSquare);
Bhists_tot_pt[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_tot_pt[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_tot_pt[5]->SetMarkerStyle(kOpenCircle);

Bhists_tot_eta[0]->SetMarkerStyle(kOpenSquare);
Bhists_tot_eta[1]->SetMarkerStyle(kFullCircle);
Bhists_tot_eta[2]->SetMarkerStyle(kFullSquare);
Bhists_tot_eta[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_tot_eta[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_tot_eta[5]->SetMarkerStyle(kOpenCircle);

Ehists_tot_pt[0]->SetMarkerStyle(kOpenSquare);
Ehists_tot_pt[1]->SetMarkerStyle(kFullCircle);
Ehists_tot_pt[2]->SetMarkerStyle(kFullSquare);
Ehists_tot_pt[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_tot_pt[4]->SetMarkerStyle(kFullTriangleDown);
Ehists_tot_pt[5]->SetMarkerStyle(kOpenCircle);

Ehists_tot_eta[0]->SetMarkerStyle(kOpenSquare);
Ehists_tot_eta[1]->SetMarkerStyle(kFullCircle);
Ehists_tot_eta[2]->SetMarkerStyle(kFullSquare);
Ehists_tot_eta[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_tot_eta[4]->SetMarkerStyle(kFullTriangleDown);

Bhists_pt[0]->SetTitle("Barrel");
Bhists_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Bhists_pt[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_pt[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_pt[0]->GetYaxis()->SetTitleOffset(0.5);

Bhists_eta[0]->SetTitle("Barrel");
Bhists_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Bhists_eta[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_eta[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_eta[0]->GetYaxis()->SetTitleOffset(0.5);

Ehists_pt[0]->SetTitle("Endcaps");
Ehists_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Ehists_pt[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_pt[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_pt[0]->GetYaxis()->SetTitleOffset(0.5);


Ehists_eta[0]->SetTitle("Endcaps");
Ehists_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Ehists_eta[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_eta[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_eta[0]->GetYaxis()->SetTitleOffset(0.5);


Bhists_tot_pt[0]->SetTitle("Barrel");
Bhists_tot_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Bhists_tot_pt[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_tot_pt[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_tot_pt[0]->GetYaxis()->SetTitleOffset(0.5);

Bhists_tot_eta[0]->SetTitle("Barrel");
Bhists_tot_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Bhists_tot_eta[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_tot_eta[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_tot_eta[0]->GetYaxis()->SetTitleOffset(0.5);

Ehists_tot_pt[0]->SetTitle("Endcaps");
Ehists_tot_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Ehists_tot_pt[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_tot_pt[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_tot_pt[0]->GetYaxis()->SetTitleOffset(0.5);


Ehists_tot_eta[0]->SetTitle("Endcaps");
Ehists_tot_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Ehists_tot_eta[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_tot_eta[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_tot_eta[0]->GetYaxis()->SetTitleOffset(0.5);


TCanvas *c;
TPad *pad1;
TPad *pad2;
TPad *pad3;
TPaveText *pave;
TH1F *hist_new;
//////DRAW N stubs
c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,0.5,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0.5,0.5,1,1);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();
pad3 = new TPad("pad3", "pad3",0,0,1,0.5);
pad3->SetGrid(1,1);
pad3->SetBottomMargin(0.2);
pad3->Draw();


pad1->cd();
gStyle->SetOptStat(0);
Bhists_tot_eta[0]->SetTitle("Number of clusters");
for (int k=0;k<6;++k){
  Bhists_tot_eta[k]->SetMarkerColor(k+1);
  Bhists_tot_eta[k]->Draw("p HIST SAME");
}

pad2->cd();
gStyle->SetOptStat(0);
Bhists_eta[0]->SetTitle("Number of stubs");
for (int k=0;k<6;++k){
  Bhists_eta[k]->SetMarkerColor(k+1);
  Bhists_eta[k]->Draw("p HIST SAME");
}

pad3->cd();
for (int k=0;k<6;++k){
  hist_new = (TH1F*) Bhists_eta[k]->Clone();
  hist_new->Divide(Bhists_tot_eta[k]);
  hist_new->SetTitle("Stub eff");
  hist_new->GetYaxis()->SetRangeUser(0.8,1.1);
  hist_new->Draw("P HIST SAME");
}

pave = new TPaveText(0.05,0.8,0.3,1,"NDC");
pave->AddText(fname);
pave->AddText("Barrel");
pave->Draw("same");

TLegend* leg = new TLegend(0.9,0.7,1,1);
leg->SetFillStyle ( 0);
leg->SetFillColor ( 0);
leg->SetBorderSize( 0);
leg->AddEntry(Bhists_eta[0], "Layer 1"                           , "p");
leg->AddEntry(Bhists_eta[1], "Layer 2"                           , "p");
leg->AddEntry(Bhists_eta[2], "Layer 3"                           , "p");
leg->AddEntry(Bhists_eta[3], "Layer 4"                           , "p");
leg->AddEntry(Bhists_eta[4], "Layer 5"                           , "p");
leg->AddEntry(Bhists_eta[5], "Layer 6"                           , "p");
leg->Draw("same");

c->Print(fname+"_"+pname+"_Barrel_eta.png","png");

delete pave;
delete pad1;
delete pad2;
delete pad3;
delete c;
delete hist_new;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,0.5,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0.5,0.5,1,1);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();
pad3 = new TPad("pad3", "pad3",0,0,1,0.5);
pad3->SetGrid(1,1);
pad3->SetBottomMargin(0.2);
pad3->Draw();


pad1->cd();
gStyle->SetOptStat(0);
Ehists_tot_eta[0]->SetTitle("Number of clusters");
for (int k=0;k<5;++k){
  Ehists_tot_eta[k]->SetMarkerColor(k+1);
  Ehists_tot_eta[k]->Draw("p HIST SAME");
}

pad2->cd();
gStyle->SetOptStat(0);
Ehists_eta[0]->SetTitle("Number of stubs");
for (int k=0;k<5;++k){
  Ehists_eta[k]->SetMarkerColor(k+1);
  Ehists_eta[k]->Draw("p HIST SAME");
}

pad3->cd();
for (int k=0;k<5;++k){
  hist_new = (TH1F*) Ehists_eta[k]->Clone();
  hist_new->Divide(Ehists_tot_eta[k]);
  hist_new->SetTitle("Stub eff");
  hist_new->GetYaxis()->SetRangeUser(0.8,1.1);
  hist_new->Draw("P HIST SAME");
}

pave = new TPaveText(0.05,0.8,0.3,1,"NDC");
pave->AddText(fname);
pave->AddText("Endcap");
pave->Draw("same");

TLegend* eleg = new TLegend(0.9,0.7,1,1);
eleg->SetFillStyle ( 0);
eleg->SetFillColor ( 0);
eleg->SetBorderSize( 0);
eleg->AddEntry(Ehists_eta[0], "Disk 1"                           , "p");
eleg->AddEntry(Ehists_eta[1], "Disk 2"                           , "p");
eleg->AddEntry(Ehists_eta[2], "Disk 3"                           , "p");
eleg->AddEntry(Ehists_eta[3], "Disk 4"                           , "p");
eleg->AddEntry(Ehists_eta[4], "Disk 5"                           , "p");
eleg->Draw("same");

c->Print(fname+"_"+pname+"_Endcap_eta.png","png");
delete pave;
delete pad1;
delete pad2;
delete pad3;
delete c;
delete hist_new;

/////////////////////////PT/////////////////////
c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,0.5,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0.5,0.5,1,1);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();
pad3 = new TPad("pad3", "pad3",0,0,1,0.5);
pad3->SetGrid(1,1);
pad3->SetBottomMargin(0.2);
pad3->Draw();


pad1->cd();
gStyle->SetOptStat(0);
Bhists_tot_pt[0]->SetTitle("Number of clusters");
for (int k=0;k<6;++k){
  Bhists_tot_pt[k]->SetMarkerColor(k+1);
  Bhists_tot_pt[k]->Draw("p HIST SAME");
}

pad2->cd();
gStyle->SetOptStat(0);
Bhists_pt[0]->SetTitle("Number of stubs");
for (int k=0;k<6;++k){
  Bhists_pt[k]->SetMarkerColor(k+1);
  Bhists_pt[k]->Draw("p HIST SAME");
}

pad3->cd();
for (int k=0;k<6;++k){
  hist_new = (TH1F*) Bhists_pt[k]->Clone();
  hist_new->Divide(Bhists_tot_pt[k]);
  hist_new->SetTitle("Stub eff");
  hist_new->GetYaxis()->SetRangeUser(0.8,1.1);
  hist_new->Draw("P HIST SAME");
}

pave = new TPaveText(0.05,0.8,0.3,1,"NDC");
pave->AddText(fname);
pave->AddText("Barrel");
pave->Draw("same");

leg->Draw("same");

c->Print(fname+"_"+pname+"_Barrel_pt.png","png");

delete pave;
delete pad1;
delete pad2;
delete pad3;
delete c;
delete hist_new;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,0.5,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0.5,0.5,1,1);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();
pad3 = new TPad("pad3", "pad3",0,0,1,0.5);
pad3->SetGrid(1,1);
pad3->SetBottomMargin(0.2);
pad3->Draw();


pad1->cd();
gStyle->SetOptStat(0);
Ehists_tot_pt[0]->SetTitle("Number of clusters");
for (int k=0;k<5;++k){
  Ehists_tot_pt[k]->SetMarkerColor(k+1);
  Ehists_tot_pt[k]->Draw("p HIST SAME");
}

pad2->cd();
gStyle->SetOptStat(0);
Ehists_pt[0]->SetTitle("Number of stubs");
for (int k=0;k<5;++k){
  Ehists_pt[k]->SetMarkerColor(k+1);
  Ehists_pt[k]->Draw("p HIST SAME");
}

pad3->cd();
for (int k=0;k<5;++k){
  hist_new = (TH1F*) Ehists_pt[k]->Clone();
  hist_new->Divide(Ehists_tot_pt[k]);
  hist_new->SetTitle("Stub eff");
  hist_new->GetYaxis()->SetRangeUser(0.8,1.1);
  hist_new->Draw("P HIST SAME");
}

pave = new TPaveText(0.05,0.8,0.3,1,"NDC");
pave->AddText(fname);
pave->AddText("Endcap");
pave->Draw("same");

eleg->Draw("same");

c->Print(fname+"_"+pname+"_Endcap_pt.png","png");
delete pave;
delete pad1;
delete pad2;
delete pad3;
delete c;
delete hist_new;

for (int k=0;k<6;++k){
  delete Bhists_eta[k];
  delete Ehists_eta[k];
  delete Bhists_pt[k];
  delete Ehists_pt[k];
  delete Bhists_tot_eta[k];
  delete Ehists_tot_eta[k];
  delete Bhists_tot_pt[k];
  delete Ehists_tot_pt[k];
}
}



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//
void stubRecoEff::eff3(TString fname, TString pname)
{

cout<<fname <<" for  "<<pname;

typedef vector<int> Dim1;
typedef vector<Dim1> Dim2;
typedef vector<Dim2> Dim3;
typedef vector<Dim3> Dim4;
typedef vector<Dim4> Dim5;
typedef vector<Dim5> Dim6;
 
if (fChain == 0) return;
//Long64_t nentries = fChain->GetEntriesFast();
Int_t nentries = (Int_t) fChain->GetEntries();

Long64_t nbytes = 0, nb = 0;


cout<<nentries<<endl;

std::vector<TH1F*> Bhists_eta;
std::vector<TH1F*> Bhists_pt;
std::vector<TH1F*> Bhists_tot_eta;
std::vector<TH1F*> Bhists_tot_pt;


std::vector<TH1F*> Ehists_eta;
std::vector<TH1F*> Ehists_pt;
std::vector<TH1F*> Ehists_tot_eta;
std::vector<TH1F*> Ehists_tot_pt;
TH1F *b_eta;
TH1F *b_pt;
TH1F *b_tot_eta;
TH1F *b_tot_pt;
TH1F *e_eta;
TH1F *e_pt;
TH1F *e_tot_eta;
TH1F *e_tot_pt;

for (int k=0;k<6;++k){
  std::stringstream name;
  name <<k;
  b_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"pt";
  b_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Bhists_eta.push_back(b_eta);
  Bhists_pt.push_back(b_pt);
  name <<k;
  b_tot_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"tot";
  b_tot_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Bhists_tot_eta.push_back(b_tot_eta);
  Bhists_tot_pt.push_back(b_tot_pt);


  name <<"E";
  e_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"pt";
  e_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Ehists_eta.push_back(e_eta);
  Ehists_pt.push_back(e_pt);
  name <<"E";
  e_tot_eta = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,0,3);
  name <<"tot";
  e_tot_pt = new TH1F((name.str()).c_str(),(name.str()).c_str(),50,0,5);
  Ehists_tot_eta.push_back(e_tot_eta);
  Ehists_tot_pt.push_back(e_tot_pt);

}

for (Long64_t jentry=0; jentry<nentries;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (Cut(ientry) < 0) continue;

  int pid = 0;
  if (pname == "mu") pid = 13;
  if (pname == "ele") pid = 11;
  if (pname == "pi") pid = 211;
  float N = float(nentries); 
  for (unsigned int k=0; k<stubEff_tp_pt->size(); ++k) {
    if(abs(stubEff_tp_pdgid->at(k))!=pid) continue;

//if (2*stubEff_EL1->at(k) != clustEff_EL1->at(k)) cout<<"#stub= "<<stubEff_EL1->at(k)<<" #clusters = "<<clustEff_EL1->at(k) <<" eta ="<<stubEff_tp_eta->at(k)<<" pt="<<stubEff_tp_pt->at(k)<<endl;

    Bhists_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_BL1->at(k))/N);
    Bhists_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_BL2->at(k))/N);
    Bhists_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_BL3->at(k))/N);
    Bhists_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_BL4->at(k))/N);
    Bhists_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_BL5->at(k))/N);
    Bhists_eta[5]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_BL6->at(k))/N);

    Ehists_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_EL1->at(k))/N);
    Ehists_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_EL2->at(k))/N);
    Ehists_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_EL3->at(k))/N);
    Ehists_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_EL4->at(k))/N);
    Ehists_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(stubEff_EL5->at(k))/N);

    Bhists_tot_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL1->at(k))/N);
    Bhists_tot_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL2->at(k))/N);
    Bhists_tot_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL3->at(k))/N);
    Bhists_tot_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL4->at(k))/N);
    Bhists_tot_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL5->at(k))/N);
    Bhists_tot_eta[5]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_BL6->at(k))/N);

    Ehists_tot_eta[0]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL1->at(k))/N);
    Ehists_tot_eta[1]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL2->at(k))/N);
    Ehists_tot_eta[2]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL3->at(k))/N);
    Ehists_tot_eta[3]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL4->at(k))/N);
    Ehists_tot_eta[4]->Fill(abs(stubEff_tp_eta->at(k)),float(clustEff_EL5->at(k))/N);


    if(abs(stubEff_tp_eta->at(k)) < 0.6){
      Bhists_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_BL1->at(k))/N);
      Bhists_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_BL2->at(k))/N);
      Bhists_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_BL3->at(k))/N);
      Bhists_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_BL4->at(k))/N);
      Bhists_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_BL5->at(k))/N);
      Bhists_pt[5]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_BL6->at(k))/N);

      Bhists_tot_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL1->at(k))/N);
      Bhists_tot_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL2->at(k))/N);
      Bhists_tot_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL3->at(k))/N);
      Bhists_tot_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL4->at(k))/N);
      Bhists_tot_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL5->at(k))/N);
      Bhists_tot_pt[5]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_BL6->at(k))/N);
    }
    if(abs(stubEff_tp_eta->at(k)) > 1.7 && abs(stubEff_tp_eta->at(k))<2.4) {
    Ehists_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_EL1->at(k))/N);
    Ehists_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_EL2->at(k))/N);
    Ehists_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_EL3->at(k))/N);
    Ehists_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_EL4->at(k))/N);
    Ehists_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(stubEff_EL5->at(k))/N);

    Ehists_tot_pt[0]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL1->at(k))/N);
    Ehists_tot_pt[1]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL2->at(k))/N);
    Ehists_tot_pt[2]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL3->at(k))/N);
    Ehists_tot_pt[3]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL4->at(k))/N);
    Ehists_tot_pt[4]->Fill(abs(stubEff_tp_pt->at(k)),float(clustEff_EL5->at(k))/N);
    }
  }
}


Bhists_pt[0]->SetMarkerStyle(kOpenSquare);
Bhists_pt[1]->SetMarkerStyle(kFullCircle);
Bhists_pt[2]->SetMarkerStyle(kFullSquare);
Bhists_pt[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_pt[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_pt[5]->SetMarkerStyle(kOpenCircle);

Bhists_eta[0]->SetMarkerStyle(kOpenSquare);
Bhists_eta[1]->SetMarkerStyle(kFullCircle);
Bhists_eta[2]->SetMarkerStyle(kFullSquare);
Bhists_eta[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_eta[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_eta[5]->SetMarkerStyle(kOpenCircle);

Ehists_pt[0]->SetMarkerStyle(kOpenSquare);
Ehists_pt[1]->SetMarkerStyle(kFullCircle);
Ehists_pt[2]->SetMarkerStyle(kFullSquare);
Ehists_pt[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_pt[4]->SetMarkerStyle(kFullTriangleDown);
Ehists_pt[5]->SetMarkerStyle(kOpenCircle);

Ehists_eta[0]->SetMarkerStyle(kOpenSquare);
Ehists_eta[1]->SetMarkerStyle(kFullCircle);
Ehists_eta[2]->SetMarkerStyle(kFullSquare);
Ehists_eta[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_eta[4]->SetMarkerStyle(kFullTriangleDown);

Bhists_tot_pt[0]->SetMarkerStyle(kOpenSquare);
Bhists_tot_pt[1]->SetMarkerStyle(kFullCircle);
Bhists_tot_pt[2]->SetMarkerStyle(kFullSquare);
Bhists_tot_pt[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_tot_pt[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_tot_pt[5]->SetMarkerStyle(kOpenCircle);

Bhists_tot_eta[0]->SetMarkerStyle(kOpenSquare);
Bhists_tot_eta[1]->SetMarkerStyle(kFullCircle);
Bhists_tot_eta[2]->SetMarkerStyle(kFullSquare);
Bhists_tot_eta[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_tot_eta[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_tot_eta[5]->SetMarkerStyle(kOpenCircle);

Ehists_tot_pt[0]->SetMarkerStyle(kOpenSquare);
Ehists_tot_pt[1]->SetMarkerStyle(kFullCircle);
Ehists_tot_pt[2]->SetMarkerStyle(kFullSquare);
Ehists_tot_pt[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_tot_pt[4]->SetMarkerStyle(kFullTriangleDown);
Ehists_tot_pt[5]->SetMarkerStyle(kOpenCircle);

Ehists_tot_eta[0]->SetMarkerStyle(kOpenSquare);
Ehists_tot_eta[1]->SetMarkerStyle(kFullCircle);
Ehists_tot_eta[2]->SetMarkerStyle(kFullSquare);
Ehists_tot_eta[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_tot_eta[4]->SetMarkerStyle(kFullTriangleDown);

Bhists_pt[0]->SetTitle("Barrel");
Bhists_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Bhists_pt[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_pt[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_pt[0]->GetYaxis()->SetTitleOffset(0.5);
Bhists_pt[0]->SetMinimum(0);

Bhists_eta[0]->SetTitle("Barrel");
Bhists_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Bhists_eta[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_eta[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_eta[0]->GetYaxis()->SetTitleOffset(0.5);
Bhists_eta[0]->SetMinimum(0);

Ehists_pt[0]->SetTitle("Endcaps");
Ehists_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Ehists_pt[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_pt[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_pt[0]->GetYaxis()->SetTitleOffset(0.5);
Ehists_pt[0]->SetMinimum(0);

Ehists_eta[0]->SetTitle("Endcaps");
Ehists_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Ehists_eta[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_eta[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_eta[0]->GetYaxis()->SetTitleOffset(0.5);
Ehists_eta[0]->SetMinimum(0);

Bhists_tot_pt[0]->SetTitle("Barrel");
Bhists_tot_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Bhists_tot_pt[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_tot_pt[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_tot_pt[0]->GetYaxis()->SetTitleOffset(0.5);
Bhists_tot_pt[0]->SetMinimum(0);

Bhists_tot_eta[0]->SetTitle("Barrel");
Bhists_tot_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Bhists_tot_eta[0]->GetXaxis()->SetTitleSize(0.08);
Bhists_tot_eta[0]->GetYaxis()->SetTitleSize(0.06);
Bhists_tot_eta[0]->GetYaxis()->SetTitleOffset(0.5);
Bhists_tot_eta[0]->SetMinimum(0);

Ehists_tot_pt[0]->SetTitle("Endcaps");
Ehists_tot_pt[0]->GetXaxis()->SetTitle("Particle p_T (GeV)");
Ehists_tot_pt[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_tot_pt[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_tot_pt[0]->GetYaxis()->SetTitleOffset(0.5);
Ehists_tot_pt[0]->SetMinimum(0);

Ehists_tot_eta[0]->SetTitle("Endcaps");
Ehists_tot_eta[0]->GetXaxis()->SetTitle("Particle #eta");
Ehists_tot_eta[0]->GetXaxis()->SetTitleSize(0.08);
Ehists_tot_eta[0]->GetYaxis()->SetTitleSize(0.06);
Ehists_tot_eta[0]->GetYaxis()->SetTitleOffset(0.5);
Ehists_tot_eta[0]->SetMinimum(0);

TCanvas *c;
TPad *pad1;
TPad *pad2;
TPad *pad3;
TPaveText *pave;
//////DRAW N stubs
c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0,0,1,0.5);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();

pad1->cd();
gStyle->SetOptStat(0);
Bhists_tot_eta[0]->SetTitle("Average number of clusters");
for (int k=0;k<6;++k){
  Bhists_tot_eta[k]->SetMarkerColor(k+1);
  Bhists_tot_eta[k]->Draw("p HIST SAME");
}

pad2->cd();
gStyle->SetOptStat(0);
Bhists_eta[0]->SetTitle("Average number of stubs");
for (int k=0;k<6;++k){
  Bhists_eta[k]->SetMarkerColor(k+1);
  Bhists_eta[k]->Draw("p HIST SAME");
}

pave = new TPaveText(0.05,0.85,0.3,1,"NDC");
pave->AddText(fname+"   - Barrel");
pave->Draw("same");

TLegend* leg = new TLegend(0.9,0.7,1,1);
leg->SetFillStyle ( 0);
leg->SetFillColor ( 0);
leg->SetBorderSize( 0);
leg->AddEntry(Bhists_eta[0], "Layer 1"                           , "p");
leg->AddEntry(Bhists_eta[1], "Layer 2"                           , "p");
leg->AddEntry(Bhists_eta[2], "Layer 3"                           , "p");
leg->AddEntry(Bhists_eta[3], "Layer 4"                           , "p");
leg->AddEntry(Bhists_eta[4], "Layer 5"                           , "p");
leg->AddEntry(Bhists_eta[5], "Layer 6"                           , "p");
leg->Draw("same");

c->Print("comp"+fname+"_"+pname+"_Barrel_eta.png","png");

delete pave;
delete pad1;
delete pad2;
delete c;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0,0,1,0.5);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();

pad1->cd();
gStyle->SetOptStat(0);
Ehists_tot_eta[0]->SetTitle("Average number of clusters");
for (int k=0;k<5;++k){
  Ehists_tot_eta[k]->SetMarkerColor(k+1);
  Ehists_tot_eta[k]->Draw("p HIST SAME");
}

pad2->cd();
gStyle->SetOptStat(0);
Ehists_eta[0]->SetTitle("Average number of stubs");
for (int k=0;k<5;++k){
  Ehists_eta[k]->SetMarkerColor(k+1);
  Ehists_eta[k]->Draw("p HIST SAME");
}


pave = new TPaveText(0.05,0.85,0.3,1,"NDC");
pave->AddText(fname+"   - Endcap");
pave->Draw("same");

TLegend* eleg = new TLegend(0.9,0.7,1,1);
eleg->SetFillStyle ( 0);
eleg->SetFillColor ( 0);
eleg->SetBorderSize( 0);
eleg->AddEntry(Ehists_eta[0], "Disk 1"                           , "p");
eleg->AddEntry(Ehists_eta[1], "Disk 2"                           , "p");
eleg->AddEntry(Ehists_eta[2], "Disk 3"                           , "p");
eleg->AddEntry(Ehists_eta[3], "Disk 4"                           , "p");
eleg->AddEntry(Ehists_eta[4], "Disk 5"                           , "p");
eleg->Draw("same");

c->Print("comp"+fname+"_"+pname+"_Endcap_eta.png","png");
delete pave;
delete pad1;
delete pad2;
delete c;

/////////////////////////PT/////////////////////
c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0,0,1,0.5);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();

pad1->cd();
gStyle->SetOptStat(0);
Bhists_tot_pt[0]->SetTitle("Average number of clusters");
for (int k=0;k<6;++k){
  Bhists_tot_pt[k]->SetMarkerColor(k+1);
  Bhists_tot_pt[k]->Draw("p HIST SAME");
}

pad2->cd();
gStyle->SetOptStat(0);
Bhists_pt[0]->SetTitle("Average number of stubs");
for (int k=0;k<6;++k){
  Bhists_pt[k]->SetMarkerColor(k+1);
  Bhists_pt[k]->Draw("p HIST SAME");
}

pave = new TPaveText(0.05,0.85,0.3,1,"NDC");
pave->AddText(fname+"   - Barrel");
pave->Draw("same");

leg->Draw("same");

c->Print("comp"+fname+"_"+pname+"_Barrel_pt.png","png");

delete pave;
delete pad1;
delete pad2;
delete c;

c = new TCanvas("c","c",800,600);
pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
pad2 = new TPad("pad2", "pad2",0,0,1,0.5);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();

pad1->cd();
gStyle->SetOptStat(0);
Ehists_tot_pt[0]->SetTitle("Average number of clusters");
for (int k=0;k<5;++k){
  Ehists_tot_pt[k]->SetMarkerColor(k+1);
  Ehists_tot_pt[k]->Draw("p HIST SAME");
}

pad2->cd();
gStyle->SetOptStat(0);
Ehists_pt[0]->SetTitle("Average number of stubs");
for (int k=0;k<5;++k){
  Ehists_pt[k]->SetMarkerColor(k+1);
  Ehists_pt[k]->Draw("p HIST SAME");
}

pave = new TPaveText(0.05,0.85,0.3,1,"NDC");
pave->AddText(fname+"   - Endcap");
pave->Draw("same");

eleg->Draw("same");

c->Print("comp"+fname+"_"+pname+"_Endcap_pt.png","png");
delete pave;
delete pad1;
delete pad2;
delete c;

for (int k=0;k<6;++k){
  delete Bhists_eta[k];
  delete Ehists_eta[k];
  delete Bhists_pt[k];
  delete Ehists_pt[k];
  delete Bhists_tot_eta[k];
  delete Ehists_tot_eta[k];
  delete Bhists_tot_pt[k];
  delete Ehists_tot_pt[k];
}
std::vector<TH1F*>().swap(Bhists_eta);
std::vector<TH1F*>().swap(Bhists_pt);
std::vector<TH1F*>().swap(Ehists_eta);
std::vector<TH1F*>().swap(Ehists_pt);
std::vector<TH1F*>().swap(Bhists_tot_eta);
std::vector<TH1F*>().swap(Bhists_tot_pt);
std::vector<TH1F*>().swap(Ehists_tot_eta);
std::vector<TH1F*>().swap(Ehists_tot_pt);

cout<<fname<<"  is done"<<endl;

}




