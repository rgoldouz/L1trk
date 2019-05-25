#define FE_cxx
#include "FE.h"
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
void FE::FE_eff(TString fname)
{
//   In a ROOT session, you can do:
//      root> .L FE.C
//      root> FE t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   float allstub_B[6], allstub_E[5][15];
   float los_CBC_B[6], los_CBC_E[5][15];
   float los_CIC_B[6], los_CIC_E[5][15];

   for (int i=0;i<6;++i){
     allstub_B[i] = 0;
     los_CBC_B[i] = 0;
     los_CIC_B[i] = 0;
   }

   for (int i=0;i<5;++i){
     for (int j=0;j<15;++j){
       allstub_E[i][j] = 0;
       los_CBC_E[i][j] = 0;
       los_CIC_E[i][j] = 0;
     }
   }

   for (Long64_t jentry=0; jentry<8;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      // loop over stubs

      for (unsigned int k=0; k<allstub_x->size(); ++k) {

        if (allstub_isBarrel->at(k)){
          allstub_B[allstub_layer->at(k)-1]++;
          if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) los_CBC_B[allstub_layer->at(k)-1]++;
          if (allstub_trigDisplace->at(k)>400) los_CIC_B[allstub_layer->at(k)-1]++;
        }

        else{
//if (allstub_layer->at(k)==2) cout<<"layer  "<<allstub_layer->at(k)<<"   ladder  "<<allstub_ladder->at(k)<<endl;
          allstub_E[allstub_layer->at(k)-1][allstub_ladder->at(k)-1]++;
          if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) los_CBC_E[allstub_layer->at(k)-1][allstub_ladder->at(k)-1]++;
          if (allstub_trigDisplace->at(k)>400) los_CIC_E[allstub_layer->at(k)-1][allstub_ladder->at(k)-1]++;
        }

      }
   }


   TCanvas *c = new TCanvas("c","c",800,600);
   TPad *pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
   pad1->Draw();
   pad1->SetGrid(1,1);
   pad1->SetBottomMargin(0.2);
   pad1->Draw();
   pad1->cd();

   gStyle->SetOptStat(0);
   TH2D *CBC_hB = new TH2D("CBC_hB","Barrel - CBC/MPA lose efficiency",6,1,7,1,0,1);
   TH2D *CBC_hBtext = new TH2D("CBC_hBtext","CBC_hBtext",6,1,7,1,0,1);
   for (Int_t i = 0; i < 6; i++) {
      CBC_hB->SetBinContent(i+1,1, los_CBC_B[i]/allstub_B[i]);
      CBC_hBtext->SetBinContent(i+1,1, los_CBC_B[i]/allstub_B[i]);
   }
   CBC_hBtext->SetMarkerSize(2.5);
   CBC_hB->GetXaxis()->SetTitle("Layer");
   CBC_hB->GetYaxis()->SetTitle("");
   CBC_hB->GetYaxis()->SetLabelSize(0);
   CBC_hB->GetXaxis()->SetLabelSize(0.07);
   CBC_hB->GetXaxis()->SetTitleSize(0.08);
   CBC_hB->GetXaxis()->SetTitleOffset(0.7);
   CBC_hB->GetXaxis()->SetNdivisions(6, kTRUE);
   CBC_hB->GetYaxis()->SetNdivisions(1, kTRUE);
   CBC_hB->Draw("COLZ");
   CBC_hBtext->SetBarOffset(0.2);
   CBC_hBtext->Draw("TEXT SAME");

   c->cd();
   TPad *pad2 = new TPad("pad", "pad",0,0,1,0.5);
   pad2->SetGrid(1,1);
   pad2->SetBottomMargin(0.2);
   pad2->Draw();
   pad2->cd();
   TH2D *CBC_hE = new TH2D("CBC_hE","Endcaps CBC lose efficiency",5,1,6,15,1,16);
   TH2D *CBC_hEtext = new TH2D("CBC_hEtext","CBC_hEtext",5,1,6,15,1,16);
   for (Int_t i = 0; i < 5; i++) {
     for (int j=0;j<15;++j){
      if (allstub_E[i][j] != 0 ) CBC_hE->SetBinContent(i+1,j+1, los_CBC_E[i][j] /allstub_E[i][j]);
      if (allstub_E[i][j] != 0 ) CBC_hEtext->SetBinContent(i+1,j+1, los_CBC_E[i][j] /allstub_E[i][j]);
     }
   }
   CBC_hEtext->SetMarkerSize(2.5);
   CBC_hE->SetTitleSize(0.3);
   CBC_hE->GetXaxis()->SetTitle("Disk");
   CBC_hE->GetYaxis()->SetTitle("Ring");
   CBC_hE->GetYaxis()->SetLabelSize(0.04);
   CBC_hE->GetXaxis()->SetLabelSize(0.07);
   CBC_hE->GetYaxis()->SetTitleSize(0.08);
   CBC_hE->GetXaxis()->SetTitleSize(0.08);
   CBC_hE->GetXaxis()->SetTitleOffset(0.7);
   CBC_hE->GetYaxis()->SetTitleOffset(0.4);
   CBC_hE->GetXaxis()->SetNdivisions(5, kTRUE);
   CBC_hE->Draw("COLZ");
   CBC_hEtext->SetBarOffset(0.1);
   CBC_hEtext->Draw("TEXT SAME");


    c->Print(fname+"CBC.png","png");

//CIC

   TCanvas *c2 = new TCanvas("c2","c2",800,600);
   TPad *pad3 = new TPad("pad3", "pad3",0,0.5,1,1);
   pad3->Draw();
   pad3->SetGrid(1,1);
   pad3->SetBottomMargin(0.2);
   pad3->Draw();
   pad3->cd();


   gStyle->SetOptStat(0);
   TH2D *CIC_hB = new TH2D("CIC_hB","Barrel - CIC/MPA lose efficiency",6,1,7,1,0,1);
   TH2D *CIC_hBtext = new TH2D("CIC_hBtext","CIC_hBtext",6,1,7,1,0,1);
   for (Int_t i = 0; i < 6; i++) {
      CIC_hB->SetBinContent(i+1,1, los_CIC_B[i]/(allstub_B[i]-los_CBC_B[i]));
      CIC_hBtext->SetBinContent(i+1,1, los_CIC_B[i]/(allstub_B[i]-los_CBC_B[i]));
   }

   CIC_hBtext->SetMarkerSize(2.5);
   CIC_hB->GetXaxis()->SetTitle("Layer");
   CIC_hB->GetYaxis()->SetTitle("");
   CIC_hB->GetYaxis()->SetLabelSize(0);
   CIC_hB->GetXaxis()->SetLabelSize(0.07);
   CIC_hB->GetXaxis()->SetTitleSize(0.08);
   CIC_hB->GetXaxis()->SetTitleOffset(0.7);
   CIC_hB->GetXaxis()->SetNdivisions(6, kTRUE);
   CIC_hB->GetYaxis()->SetNdivisions(1, kTRUE);
   CIC_hB->Draw("COLZ");
   CIC_hBtext->SetBarOffset(0.2);
   CIC_hBtext->Draw("TEXT SAME");

   c2->cd();
   TPad *pad4 = new TPad("pad4", "pad4",0,0,1,0.5);
   pad4->SetGrid(1,1);
   pad4->SetBottomMargin(0.2);
   pad4->Draw();
   pad4->cd();

   TH2D *CIC_hE = new TH2D("CIC_hE","Endcaps CIC lose efficiency",5,1,6,15,1,16);
   TH2D *CIC_hEtext = new TH2D("CIC_hEtext","CIC_hEtext",5,1,6,15,1,16);
   for (Int_t i = 0; i < 5; i++) {
     for (int j=0;j<15;++j){
     CIC_hE->SetBinContent(i+1,j+1,0);
     CIC_hEtext->SetBinContent(i+1,j+1,0);
      if (allstub_E[i][j] != 0 ) CIC_hE->SetBinContent(i+1,j+1, los_CIC_E[i][j] /(allstub_E[i][j]-los_CBC_E[i][j]));
      if (allstub_E[i][j] != 0 ) CIC_hEtext->SetBinContent(i+1,j+1, los_CIC_E[i][j] /(allstub_E[i][j]-los_CBC_E[i][j]));
     }
   }


   CIC_hE->SetTitleSize(0.3);
   CIC_hE->GetXaxis()->SetTitle("Disk");
   CIC_hE->GetYaxis()->SetTitle("Ring");
   CIC_hE->GetYaxis()->SetLabelSize(0.04);
   CIC_hE->GetXaxis()->SetLabelSize(0.07);
   CIC_hE->GetYaxis()->SetTitleSize(0.08);
   CIC_hE->GetXaxis()->SetTitleSize(0.08);
   CIC_hE->GetXaxis()->SetTitleOffset(0.7);
   CIC_hE->GetYaxis()->SetTitleOffset(0.4);
   CIC_hE->GetXaxis()->SetNdivisions(5, kTRUE);
   CIC_hE->Draw("COLZ");
   CIC_hEtext->SetBarOffset(0.1);
   CIC_hEtext->Draw("TEXT SAME");


    c2->Print(fname+"CIC.png","png");
}


void FE::Chip_occupancy(TString fname)
{

typedef vector<int> Dim1;
typedef vector<Dim1> Dim2;
typedef vector<Dim2> Dim3;
typedef vector<Dim3> Dim4;
typedef vector<Dim4> Dim5;
typedef vector<Dim5> Dim6;
 
if (fChain == 0) return;
Long64_t nentries = fChain->GetEntriesFast();
Long64_t nbytes = 0, nb = 0;


//   float occ[E/B][layer][ladder][module][seg][chip];
float occ[2][6][100][100], CBCFailOcc[2][6][100][100],CICFailOcc[2][6][100][100];
Dim6 cbcChipOcc(2,Dim5(6,Dim4(100,Dim3(100,Dim2(2,Dim1(8)))))), mpaChipOcc(2,Dim5(6,Dim4(100,Dim3(100,Dim2(2,Dim1(8))))));
Dim5 cicChipOcc(2,Dim4(6,Dim3(100,Dim2(100,Dim1(2)))));

Dim4 stubsRate(2,Dim3(6,Dim2(100,Dim1(100))));
Dim4 stubsRate_z(2,Dim3(6,Dim2(100,Dim1(100))));
Dim4 stubsRate_rho(2,Dim3(6,Dim2(100,Dim1(100))));


for (int i=0;i<2;++i){
  for (int k=0;k<6;++k){
    for (int l=0;l<100;++l){
      for (int m=0;m<100;++m){
           occ[i][k][l][m] = 0;
           CBCFailOcc[i][k][l][m] = 0;
           CICFailOcc[i][k][l][m] = 0;
           stubsRate[i][k][l][m] = 0;
           stubsRate_z[i][k][l][m] = 0;
           stubsRate_rho[i][k][l][m] = 0;
        for (int n=0;n<2;++n){
        cicChipOcc[i][k][l][m][n] = 0; 
          for (int o=0;o<8;++o){
          cbcChipOcc[i][k][l][m][n][o] = 0;
          mpaChipOcc[i][k][l][m][n][o] = 0;
          }
        }  
      }
    }
  }
}  



for (Long64_t jentry=0; jentry<8;jentry++) {
  Long64_t ientry = LoadTree(jentry);
  if (ientry < 0) break;
  nb = fChain->GetEntry(jentry);   nbytes += nb;
  if (Cut(ientry) < 0) continue;

  // loop over stubs
  for (unsigned int k=0; k<allstub_x->size(); ++k) {
    if (allstub_matchTP_pt->at(k)<2) continue;

    occ[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)]++;

     if (allstub_trigDisplace->at(k)<200 || allstub_trigDisplace->at(k)>300) cicChipOcc[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)][allstub_seg->at(k)]++;
     if (allstub_trigDisplace->at(k)>200 && allstub_trigDisplace->at(k)<300) CBCFailOcc[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)]++;
     if (allstub_trigDisplace->at(k)>400) CICFailOcc[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)]++;

    if(jentry==0){
//cout<<"CBC chip "<<allstub_chip->at(k)<<" CIC chip "<<allstub_seg->at(k)<<"is barrell  "<< allstub_isPS->at(k)<<" layer "<<allstub_layer->at(k)<<" ladder " <<allstub_ladder->at(k)<<"  module  "<<allstub_module->at(k)<<"  z  "<<allstub_z->at(k)<<endl;
      cbcChipOcc[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)][allstub_seg->at(k)][allstub_chip->at(k)]++;
      stubsRate[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)]++;
      stubsRate_z[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)] = allstub_module_z->at(k);
      stubsRate_rho[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)] = sqrt(pow(allstub_module_x->at(k),2) + pow(allstub_module_y->at(k),2)) ;
     }
     if(jentry==0||jentry==1){
      mpaChipOcc[allstub_isBarrel->at(k)][allstub_layer->at(k)-1][allstub_ladder->at(k)-1][allstub_module->at(k)][allstub_seg->at(k)][allstub_chip->at(k)]++;
    }
  }
}

//plot 1D histogram per chip
int ntotcic=0;
int ntotmpa=0;
int ntotcbc=0;
int ncicfail=0;
int ncbcfail=0;
int nmpafail=0;


   for (int k=0;k<6;++k){

ntotcic=0;
ntotcbc=0;
ncicfail=0;
ncbcfail=0;
nmpafail=0;

   TCanvas *c = new TCanvas("c","c",800,600);
   TPad *pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
   pad1->SetGrid(1,1);
   pad1->SetBottomMargin(0.2);
   pad1->Draw();

  TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.5);
   pad2->SetGrid(1,1);
   pad2->SetBottomMargin(0.2);
   pad2->Draw();

   int bin = (k+1)*15000;
   if (k==0) bin=20000;
   pad1->cd();
   gStyle->SetOptStat(0);

   TH1F *cbcChip = new TH1F("cbcChip","CBC chip occupancy (1BX)",5*bin,0,bin);
   TH1F *mpaChip = new TH1F("mpaChip","MPA chip occupancy (2BX)",5*bin,0,bin);
   TH1F *cicChip = new TH1F("cicchip","CIC chip occupancy (8BX)",7*bin,0,bin);
       for (int l=0;l<100;++l){
         for (int m=0;m<100;++m){
           for (int n=0;n<2;++n){
             ntotcic = ntotcic + cicChipOcc[1][k][l][m][n];
             if (k<3 && cicChipOcc[1][k][l][m][n]>17) ncicfail = ncicfail +cicChipOcc[1][k][l][m][n]-17; 
             if (k>2 && cicChipOcc[1][k][l][m][n]>16) ncicfail = ncicfail +cicChipOcc[1][k][l][m][n]-16;
             cicChip->Fill(l*1000+m*10+n+0.1,cicChipOcc[1][k][l][m][n]);
             for (int o=0;o<8;++o){
             if (k<3) {
               ntotcbc = ntotcbc + mpaChipOcc[1][k][l][m][n][o];
               mpaChip->Fill(l*1000+m*10+o+float(n)/2+0.1,mpaChipOcc[1][k][l][m][n][o]*1.0);
               if (mpaChipOcc[1][k][l][m][n][o]>5) ncbcfail = ncbcfail + mpaChipOcc[1][k][l][m][n][o] - 5;}
             if (k>2) {
               ntotcbc = ntotcbc +cbcChipOcc[1][k][l][m][n][o];
               cbcChip->Fill(l*1000+m*10+o+float(n)/2+0.1,cbcChipOcc[1][k][l][m][n][o]*1.0);             
               if (cbcChipOcc[1][k][l][m][n][o]>3) ncbcfail = ncbcfail +cbcChipOcc[1][k][l][m][n][o]-3;}
             }
           }
         }
       }

//cout<<"ntot = "<<ntot<<" ncicfail "<<ncicfail<<" ratio "<<float(ncicfail/ntot)<<endl;

   if (k<3) mpaChip->Draw("hist");   
   if (k>2) cbcChip->Draw("hist");

  int ymax = 3;
  if (k<3) ymax=5;
  TLine *line = new TLine(0,ymax,bin,ymax);
  line->SetLineColor(kRed);
  line->Draw("same");

   std::stringstream text,Leg1, Leg2, Leg3,Leg4, Leg5;
   text<<fname<<"Chip_Occupancy-BL"<<k+1<<".png";
   Leg1<<"Barrel- Layer "<<k+1;
   Leg2<<"1000*ladder + 10*Module + chip + seg/2" ;
   Leg3<<"1000*ladder + 10*Module + seg" ;
   Leg4<<"Nstubs(fail)/Nstubs="<<ncbcfail<<"/"<<ntotcbc<<" eff loss=";
   Leg5<<"Nstubs(fail)/Nstubs="<<ncicfail<<"/"<<ntotcic<<" eff loss=";
   Leg4<<std::fixed <<std::setprecision(6)<<float(ncbcfail)/float(ntotcbc);
   Leg5<<std::fixed <<std::setprecision(6)<<float (ncicfail)/float(ntotcic);

   TPaveText *pave = new TPaveText(0.7,0.7,1,1,"NDC");
   pave->AddText((Leg1.str()).c_str());
   pave->AddText((Leg2.str()).c_str());
   pave->AddText((Leg4.str()).c_str());
   pave->Draw("same");

   pad2->cd();
   cicChip->Draw("hist");
  ymax=16;
  if (k<3) ymax=17;
  TLine *line2 = new TLine(0,ymax,bin,ymax);
  line2->SetLineColor(kRed);
  line2->Draw("same");

   TPaveText *pave2 = new TPaveText(0.7,0.7,1,1,"NDC");
   pave2->AddText((Leg1.str()).c_str());
   pave2->AddText((Leg3.str()).c_str());
   pave2->AddText((Leg5.str()).c_str());
   pave2->Draw("same");

   c->Print((text.str()).c_str(),"png");

   delete pad1;
   delete pad2;
   delete c;
   delete pave;
   delete pave2;
   delete cicChip;
   delete mpaChip;
   delete cbcChip;
   delete line;
   delete line2;


   }


   for (int k=0;k<5;++k){

ntotcic=0;
ntotcbc=0;
ntotmpa=0;
ncicfail=0;
ncbcfail=0;
nmpafail=0;

   TCanvas *c = new TCanvas("c","c",800,600);
   TPad *pad1 = new TPad("pad1", "pad1",0,0.6,1,1);
   pad1->SetGrid(1,1);
   pad1->SetBottomMargin(0.2);
   pad1->Draw();

  TPad *pad2 = new TPad("pad2", "pad2",0,.3,1,0.6);
   pad2->SetGrid(1,1);
   pad2->SetBottomMargin(0.2);
   pad2->Draw();

  TPad *pad3 = new TPad("pad2", "pad2",0,0,1,0.3);
   pad3->SetGrid(1,1);
   pad3->SetBottomMargin(0.2);
   pad3->Draw();

   int bin = 16000;
   pad1->cd();
   gStyle->SetOptStat(0);

   TH1F *cbcChip = new TH1F("cbcChip","CBC chip occupancy (1BX)",5*bin,0,bin);
   TH1F *mpaChip = new TH1F("mpaChip","MPA chip occupancy (2BX)",5*bin,0,bin);
   TH1F *cicChip = new TH1F("cicchip","CIC chip occupancy (8BX)",7*bin,0,bin);
       for (int l=0;l<100;++l){
         for (int m=0;m<100;++m){
           for (int n=0;n<2;++n){
             cicChip->Fill(l*1000+m*10+n+0.1,cicChipOcc[0][k][l][m][n]);
             ntotcic = ntotcic + cicChipOcc[0][k][l][m][n];
             if (((k<2 && l<10)|| (k>1 && l<7) ) && cicChipOcc[0][k][l][m][n]>17) ncicfail = ncicfail +cicChipOcc[0][k][l][m][n]-17;
             if (((k<2 && l>9) || (k>1 && l>6) ) && cicChipOcc[0][k][l][m][n]>16) ncicfail = ncicfail +cicChipOcc[0][k][l][m][n]-16;
             for (int o=0;o<8;++o){
             if ((k<2 && l<10) || (k>1 && l<7) ) {
               ntotmpa = ntotmpa + mpaChipOcc[0][k][l][m][n][o];
               mpaChip->Fill(l*1000+m*10+o+float(n)/2+0.1,mpaChipOcc[0][k][l][m][n][o]);
               if (mpaChipOcc[0][k][l][m][n][o]>5) nmpafail = nmpafail + mpaChipOcc[0][k][l][m][n][o] - 5;}
             else {
               ntotcbc = ntotcbc + cbcChipOcc[1][k][l][m][n][o];
               cbcChip->Fill(l*1000+m*10+o+float(n)/2+0.1,cbcChipOcc[0][k][l][m][n][o]);
               if (cbcChipOcc[0][k][l][m][n][o]>3) ncbcfail = ncbcfail +cbcChipOcc[0][k][l][m][n][o]-3;
}
             }
           }
         }
       }


  cbcChip->Draw("HIST");


  TLine *line = new TLine(0,3,bin,3);
  line->SetLineColor(kRed);
  line->Draw("same");



   std::stringstream text,Leg1, Leg2, Leg3,Leg4, Leg5,Leg6;
   text<<fname<<"Chip_Occupancy-EL"<<k+1<<".png";
   Leg1<<"Endcap- Layer "<<k+1;
   Leg2<<"1000*ladder + 10*Module + chip + seg/2" ;
   Leg3<<"1000*ladder + 10*Module + seg" ;
   Leg4<<"Nstubs(fail)/Nstubs="<<ncbcfail<<"/"<<ntotcbc<<" eff loss=";
   Leg5<<"Nstubs(fail)/Nstubs="<<nmpafail<<"/"<<ntotmpa<<" eff loss=";
   Leg6<<"Nstubs(fail)/Nstubs="<<ncicfail<<"/"<<ntotcic<<" eff loss=";
   Leg4<<std::fixed <<std::setprecision(6)<<float(ncbcfail)/float(ntotcbc);
   Leg5<<std::fixed <<std::setprecision(6)<<float (nmpafail)/float(ntotmpa);
   Leg6<<std::fixed <<std::setprecision(6)<<float (ncicfail)/float(ntotcic);

   TPaveText *pave = new TPaveText(0.7,0.7,1,1,"NDC");
   pave->AddText((Leg1.str()).c_str());
   pave->AddText((Leg2.str()).c_str());
   pave->AddText((Leg4.str()).c_str());
   pave->Draw("same");

   pad2->cd();
   mpaChip->Draw("hist");

  TLine *line2 = new TLine(0,5,bin,5);
  line2->SetLineColor(kRed);
  line2->Draw("same");

   TPaveText *pave2 = new TPaveText(0.7,0.7,1,1,"NDC");
   pave2->AddText((Leg1.str()).c_str());
   pave2->AddText((Leg2.str()).c_str());
   pave2->AddText((Leg5.str()).c_str());
   pave2->Draw("same");


   pad3->cd();
   cicChip->Draw("hist");
  TLine *line3 = new TLine(0,16,bin,16);
  line3->SetLineColor(kRed);
  line3->Draw("same");
  TLine *line4 = new TLine(0,17,bin,17);
  line4->SetLineColor(kRed);
  line4->Draw("same");

   TPaveText *pave3 = new TPaveText(0.7,0.7,1,1,"NDC");
   pave3->AddText((Leg1.str()).c_str());
   pave3->AddText((Leg3.str()).c_str());
   pave3->AddText((Leg6.str()).c_str());
   pave3->Draw("same");

   c->Print((text.str()).c_str(),"png");

   delete pad1;
   delete pad2;
   delete pad3;
   delete c;
   delete pave;
   delete pave2;
   delete pave3;
   delete cicChip;
   delete cbcChip;
   delete mpaChip;
   }







   for (int k=0;k<6;++k){
   TCanvas *c = new TCanvas("c","c",800,600);
   TPad *pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
   pad1->SetGrid(1,1);
   pad1->SetBottomMargin(0.2);
   pad1->Draw();

  TPad *pad2 = new TPad("pad2", "pad2",0,0,0.5,0.5);
   pad2->SetGrid(1,1);
   pad2->SetBottomMargin(0.2);
   pad2->Draw();

  TPad *pad3 = new TPad("pad3", "pad3",0.5,0,1,0.5);
   pad3->SetGrid(1,1);
   pad3->SetBottomMargin(0.2);
   pad3->Draw();

   pad1->cd();

   gStyle->SetOptStat(0);
   TH2D *BL1 = new TH2D("BL","Barrel - Module occupancy",100,0,100,40,0,40);
   TH2D *BL1_CBCFail = new TH2D("BL1_CBCFail","Barrel - Module CBC fail occupancy",100,0,100,40,0,40);
   TH2D *BL1_CICFail = new TH2D("BL_CICFail","Barrel - Module CIC fail occupancy",100,0,100,40,0,40);

   for (int l=0;l<100;++l){
     for (int m=0;m<100;++m){
     BL1->SetBinContent(l+1,m+1,   occ[1][k][l][m]);
     BL1_CBCFail->SetBinContent(l+1,m+1,   CBCFailOcc[1][k][l][m]);
     BL1_CICFail->SetBinContent(l+1,m+1,   CICFailOcc[1][k][l][m]);
     }
   }

   BL1->GetXaxis()->SetTitle("Ladder");
   BL1->GetYaxis()->SetTitle("Module");
   BL1->Draw("COLZ");
   std::stringstream text,Leg1, Leg2;
   text<<fname<<"Occupancy-BL"<<k+1<<".png";
   Leg1<<"Barrel";
   Leg2<<"Layer   "<<k+1;

   TPaveText *pave = new TPaveText(0.6,0.7,0.9,0.9,"NDC");
   pave->AddText((Leg1.str()).c_str());
   pave->AddText((Leg2.str()).c_str());
   pave->Draw("same");


   pad2->cd();
   BL1_CBCFail->Draw("COLZ SAME");

   pad3->cd();
   BL1_CICFail->Draw("COLZ SAME");

   c->Print((text.str()).c_str(),"png");
   delete BL1;
   delete BL1_CBCFail;
   delete BL1_CICFail;
   delete pad1;
   delete pad2;
   delete pad3;
   delete c;
   delete pave;
   }


   for (int k=0;k<5;++k){
   TCanvas *c = new TCanvas("c","c",800,600);
   TPad *pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
   pad1->SetGrid(1,1);
   pad1->SetBottomMargin(0.2);
   pad1->Draw();

  TPad *pad2 = new TPad("pad2", "pad2",0,0,0.5,0.5);
   pad2->SetGrid(1,1);
   pad2->SetBottomMargin(0.2);
   pad2->Draw();

  TPad *pad3 = new TPad("pad3", "pad3",0.5,0,1,0.5);
   pad3->SetGrid(1,1);
   pad3->SetBottomMargin(0.2);
   pad3->Draw();

   pad1->cd();

   gStyle->SetOptStat(0);
   TH2D *BL1 = new TH2D("BL","Barrel - Module occupancy",20,0,20,100,0,100);
   TH2D *BL1_CBCFail = new TH2D("BL1_CBCFail","Barrel - Module CBC fail occupancy",20,0,20,100,0,100);
   TH2D *BL1_CICFail = new TH2D("BL_CICFail","Barrel - Module CIC fail occupancy",20,0,20,100,0,100);

   for (int l=0;l<100;++l){
     for (int m=0;m<100;++m){
     BL1->SetBinContent(l+1,m+1,   occ[0][k][l][m]);
     BL1_CBCFail->SetBinContent(l+1,m+1,   CBCFailOcc[0][k][l][m]);
     BL1_CICFail->SetBinContent(l+1,m+1,   CICFailOcc[0][k][l][m]);
     }
   }

   BL1->GetXaxis()->SetTitle("Ring");
   BL1->GetYaxis()->SetTitle("Module");
   BL1->Draw("COLZ");
   std::stringstream text,Leg1, Leg2;
   text<<fname<<"Occupancy-E"<<k+1<<".png";
   Leg1<<"Endcaps";
   Leg2<<"Layer   "<<k+1;

   TPaveText *pave = new TPaveText(0.7,0.7,0.9,0.9,"NDC");
   pave->AddText((Leg1.str()).c_str());
   pave->AddText((Leg2.str()).c_str());
   pave->Draw("same");


   pad2->cd();
   BL1_CBCFail->Draw("COLZ SAME");

   pad3->cd();
   BL1_CICFail->Draw("COLZ SAME");

   c->Print((text.str()).c_str(),"png");
   delete BL1;
   delete BL1_CBCFail;
   delete BL1_CICFail;
   delete pad1;
   delete pad2;
   delete pad3;
   delete c;
   delete pave;
  }


//stub rate Barrel

std::vector<TH1F*> Bhists;
std::vector<TH1F*> Bhistsn;
std::vector<TH1F*> Bhists_z;

std::vector<TH1F*> Ehists;
std::vector<TH1F*> Ehistsn;
std::vector<TH1F*> Ehists_z;

Double_t xEdges[7] = {0, 30, 45, 60, 75, 95, 120};
Double_t ExEdges[6] = {100, 145, 165, 200, 240, 300};

for (int k=0;k<6;++k){
  std::stringstream name;
  name <<k;
  TH1F *bl = new TH1F((name.str()).c_str(),(name.str()).c_str(),35,-100,100);
  name <<"l";
  TH1F *bln = new TH1F((name.str()).c_str(),(name.str()).c_str(),35,-100,100);
  name <<"z";
  TH1F *blz = new TH1F((name.str()).c_str(),(name.str()).c_str(),6,xEdges);
  Bhists.push_back(bl);
  Bhistsn.push_back(bln);
  Bhists_z.push_back(blz);

  name <<"E";
  TH1F *el = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,20,120);
  name <<"El";
  TH1F *eln = new TH1F((name.str()).c_str(),(name.str()).c_str(),30,20,120);
  name <<"Ez";
  TH1F *elz = new TH1F((name.str()).c_str(),(name.str()).c_str(),5,ExEdges);
  Ehists.push_back(el);
  Ehistsn.push_back(eln);
  Ehists_z.push_back(elz);
}
Bhists[0]->SetMarkerStyle(kOpenSquare);
Bhists[1]->SetMarkerStyle(kFullCircle);
Bhists[2]->SetMarkerStyle(kFullSquare);
Bhists[3]->SetMarkerStyle(kFullTriangleUp);
Bhists[4]->SetMarkerStyle(kFullTriangleDown);
Bhists[5]->SetMarkerStyle(kOpenCircle);

Bhists_z[0]->SetMarkerStyle(kOpenSquare);
Bhists_z[1]->SetMarkerStyle(kFullCircle);
Bhists_z[2]->SetMarkerStyle(kFullSquare);
Bhists_z[3]->SetMarkerStyle(kFullTriangleUp);
Bhists_z[4]->SetMarkerStyle(kFullTriangleDown);
Bhists_z[5]->SetMarkerStyle(kOpenCircle);

Ehists[0]->SetMarkerStyle(kOpenSquare);
Ehists[1]->SetMarkerStyle(kFullCircle);
Ehists[2]->SetMarkerStyle(kFullSquare);
Ehists[3]->SetMarkerStyle(kFullTriangleUp);
Ehists[4]->SetMarkerStyle(kFullTriangleDown);
Ehists[5]->SetMarkerStyle(kOpenCircle);

Ehists_z[0]->SetMarkerStyle(kOpenSquare);
Ehists_z[1]->SetMarkerStyle(kFullCircle);
Ehists_z[2]->SetMarkerStyle(kFullSquare);
Ehists_z[3]->SetMarkerStyle(kFullTriangleUp);
Ehists_z[4]->SetMarkerStyle(kFullTriangleDown);
Ehists_z[5]->SetMarkerStyle(kOpenCircle);


Bhists[0]->SetTitle("Barrel");
Bhists[0]->GetXaxis()->SetTitle("Module z position (cm)");
Bhists[0]->GetYaxis()->SetTitle("stub rate (in stub/Module/BX)");

Bhists_z[0]->SetTitle("Barrel");
Bhists_z[0]->GetXaxis()->SetTitle("Module z position (cm)");
Bhists_z[0]->GetYaxis()->SetTitle("stub rate (in stub/Module/BX)");

Ehists[0]->SetTitle("Endcaps");
Ehists[0]->GetXaxis()->SetTitle("Module #rho position (cm)");
Ehists[0]->GetYaxis()->SetTitle("stub rate (in stub/Module/BX)");

Ehists_z[0]->SetTitle("Endcaps");
Ehists_z[0]->GetXaxis()->SetTitle("Disk z position");
Ehists_z[0]->GetYaxis()->SetTitle("stub rate (in stub/BX)");

TCanvas *c = new TCanvas("c","c",800,600);
TPad *pad1 = new TPad("pad1", "pad1",0,0.5,1,1);
pad1->SetGrid(1,1);
pad1->SetBottomMargin(0.2);
pad1->Draw();
TPad *pad2 = new TPad("pad2", "pad2",0,0,1,0.5);
pad2->SetGrid(1,1);
pad2->SetBottomMargin(0.2);
pad2->Draw();
pad1->cd();

for (int k=0;k<6;++k){
  for (int l=0;l<100;++l){
    for (int m=0;m<100;++m){
    Bhists[k]->Fill(stubsRate_z[1][k][l][m], stubsRate[1][k][l][m]);
    if(stubsRate[1][k][l][m]>0) Bhistsn[k]->Fill(stubsRate_z[1][k][l][m]); 
    Bhists_z[k]->Fill(stubsRate_rho[1][k][l][m], stubsRate[1][k][l][m]);
    }
  }
  Bhists[k]->Divide(Bhistsn[k]);
  Bhists[k]->Draw("P HIST SAME");
}
TLegend* leg = new TLegend(0.8,0.7,1,1);
leg->SetFillStyle ( 0);
leg->SetFillColor ( 0);
leg->SetBorderSize( 0);
leg->AddEntry(Bhists[0], "#rho = 24 cm"                           , "p");
leg->AddEntry(Bhists[1], "#rho = 37 cm"                           , "p");
leg->AddEntry(Bhists[2], "#rho = 52 cm"                           , "p");
leg->AddEntry(Bhists[3], "#rho = 69 cm"                           , "p");
leg->AddEntry(Bhists[4], "#rho = 86 cm"                           , "p");
leg->AddEntry(Bhists[5], "#rho = 111 cm"                          , "p");
leg->Draw("same");

pad2->cd();
for (int k=0;k<6;++k){
  Bhists_z[k]->Draw("P HIST SAME");
}
leg->Draw("same");
c->Print(fname+"rate_module_B.png","png");

delete leg;
delete pad1;
delete pad2;
delete c;
TCanvas *ec = new TCanvas("ec","ec",800,600);
TPad *epad1 = new TPad("epad1", "epad1",0,0.5,1,1);
epad1->SetGrid(1,1);
epad1->SetBottomMargin(0.2);
epad1->Draw();
TPad *epad2 = new TPad("epad2", "epad2",0,0,1,0.5);
epad2->SetGrid(1,1);
epad2->SetBottomMargin(0.2);
epad2->Draw();
epad1->cd();

for (int k=0;k<5;++k){
  for (int l=0;l<100;++l){
    for (int m=0;m<100;++m){
    Ehists[k]->Fill(stubsRate_rho[0][k][l][m], stubsRate[0][k][l][m]);
    if(stubsRate[0][k][l][m]>0) Ehistsn[k]->Fill(stubsRate_rho[0][k][l][m]);
    Ehists_z[k]->Fill(stubsRate_z[0][k][l][m], stubsRate[0][k][l][m]);
    }
  }

  Ehists[k]->Divide(Ehistsn[k]);
  Ehists[k]->SetMaximum(15);
  Ehists[k]->Draw("P HIST SAME");
}
TLegend* eleg = new TLegend(0.8,0.7,1,1);
eleg->SetFillStyle ( 0);
eleg->SetFillColor ( 0);
eleg->SetBorderSize( 0);
eleg->AddEntry(Ehists[0], "|z| = 136 cm"                           , "p");
eleg->AddEntry(Ehists[1], "|z| = 155 cm"                           , "p");
eleg->AddEntry(Ehists[2], "|z| = 185 cm"                           , "p");
eleg->AddEntry(Ehists[3], "|z| = 222 cm"                           , "p");
eleg->AddEntry(Ehists[4], "|z| = 265 cm"                           , "p");
eleg->Draw("same");

epad2->cd();
for (int k=0;k<5;++k){
  Ehists_z[k]->Draw("P HIST SAME");
  Ehists_z[k]->SetMaximum(250);
}
eleg->Draw("same");
ec->Print(fname+"rate_module_E.png","png");
}
