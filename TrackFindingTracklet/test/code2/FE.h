//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct  8 13:52:43 2018 by ROOT version 6.10/05
// from TTree eventTree/Event tree
// found on file: NuPU200.root
//////////////////////////////////////////////////////////

#ifndef FE_h
#define FE_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class FE {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *trk_pt;
   vector<float>   *trk_eta;
   vector<float>   *trk_phi;
   vector<float>   *trk_d0;
   vector<float>   *trk_z0;
   vector<float>   *trk_chi2;
   vector<int>     *trk_nstub;
   vector<int>     *trk_seed;
   vector<int>     *trk_genuine;
   vector<int>     *trk_loose;
   vector<int>     *trk_unknown;
   vector<int>     *trk_combinatoric;
   vector<int>     *trk_fake;
   vector<int>     *trk_matchtp_pdgid;
   vector<float>   *trk_matchtp_pt;
   vector<float>   *trk_matchtp_eta;
   vector<float>   *trk_matchtp_phi;
   vector<float>   *trk_matchtp_z0;
   vector<float>   *trk_matchtp_dxy;
   vector<int>     *trk_injet;
   vector<int>     *trk_injet_highpt;
   vector<int>     *trk_injet_vhighpt;
   vector<float>   *tp_pt;
   vector<float>   *tp_eta;
   vector<float>   *tp_phi;
   vector<float>   *tp_dxy;
   vector<float>   *tp_d0;
   vector<float>   *tp_z0;
   vector<float>   *tp_d0_prod;
   vector<float>   *tp_z0_prod;
   vector<int>     *tp_pdgid;
   vector<int>     *tp_nmatch;
   vector<int>     *tp_nloosematch;
   vector<int>     *tp_nstub;
   vector<int>     *tp_eventid;
   vector<int>     *tp_charge;
   vector<int>     *tp_injet;
   vector<int>     *tp_injet_highpt;
   vector<int>     *tp_injet_vhighpt;
   vector<float>   *matchtrk_pt;
   vector<float>   *matchtrk_eta;
   vector<float>   *matchtrk_phi;
   vector<float>   *matchtrk_z0;
   vector<float>   *matchtrk_d0;
   vector<float>   *matchtrk_chi2;
   vector<int>     *matchtrk_nstub;
   vector<int>     *matchtrk_seed;
   vector<int>     *matchtrk_injet;
   vector<int>     *matchtrk_injet_highpt;
   vector<int>     *matchtrk_injet_vhighpt;
   vector<float>   *loosematchtrk_pt;
   vector<float>   *loosematchtrk_eta;
   vector<float>   *loosematchtrk_phi;
   vector<float>   *loosematchtrk_z0;
   vector<float>   *loosematchtrk_d0;
   vector<float>   *loosematchtrk_chi2;
   vector<int>     *loosematchtrk_nstub;
   vector<int>     *loosematchtrk_seed;
   vector<int>     *loosematchtrk_injet;
   vector<int>     *loosematchtrk_injet_highpt;
   vector<int>     *loosematchtrk_injet_vhighpt;
   vector<float>   *allstub_x;
   vector<float>   *allstub_y;
   vector<float>   *allstub_z;
   vector<int>     *allstub_isBarrel;
   vector<int>     *allstub_layer;
   vector<int>     *allstub_isPSmodule;
   vector<float>   *allstub_trigDisplace;
   vector<float>   *allstub_trigOffset;
   vector<float>   *allstub_trigPos;
   vector<float>   *allstub_trigBend;
   vector<int>     *allstub_matchTP_pdgid;
   vector<float>   *allstub_matchTP_pt;
   vector<float>   *allstub_matchTP_eta;
   vector<float>   *allstub_matchTP_phi;
   vector<int>     *allstub_genuine;
   vector<int>     *allstub_isPS;
   vector<int>     *allstub_chip;
   vector<int>     *allstub_seg;
   vector<int>     *allstub_ladder;
   vector<int>     *allstub_module;
   vector<int>     *allstub_type;
   vector<float>   *allstub_module_x;
   vector<float>   *allstub_module_y;
   vector<float>   *allstub_module_z;
   vector<float>   *jet_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_pt;
   vector<float>   *jet_tp_sumpt;
   vector<float>   *jet_trk_sumpt;
   vector<float>   *jet_matchtrk_sumpt;
   vector<float>   *jet_loosematchtrk_sumpt;

   // List of branches
   TBranch        *b_trk_pt;   //!
   TBranch        *b_trk_eta;   //!
   TBranch        *b_trk_phi;   //!
   TBranch        *b_trk_d0;   //!
   TBranch        *b_trk_z0;   //!
   TBranch        *b_trk_chi2;   //!
   TBranch        *b_trk_nstub;   //!
   TBranch        *b_trk_seed;   //!
   TBranch        *b_trk_genuine;   //!
   TBranch        *b_trk_loose;   //!
   TBranch        *b_trk_unknown;   //!
   TBranch        *b_trk_combinatoric;   //!
   TBranch        *b_trk_fake;   //!
   TBranch        *b_trk_matchtp_pdgid;   //!
   TBranch        *b_trk_matchtp_pt;   //!
   TBranch        *b_trk_matchtp_eta;   //!
   TBranch        *b_trk_matchtp_phi;   //!
   TBranch        *b_trk_matchtp_z0;   //!
   TBranch        *b_trk_matchtp_dxy;   //!
   TBranch        *b_trk_injet;   //!
   TBranch        *b_trk_injet_highpt;   //!
   TBranch        *b_trk_injet_vhighpt;   //!
   TBranch        *b_tp_pt;   //!
   TBranch        *b_tp_eta;   //!
   TBranch        *b_tp_phi;   //!
   TBranch        *b_tp_dxy;   //!
   TBranch        *b_tp_d0;   //!
   TBranch        *b_tp_z0;   //!
   TBranch        *b_tp_d0_prod;   //!
   TBranch        *b_tp_z0_prod;   //!
   TBranch        *b_tp_pdgid;   //!
   TBranch        *b_tp_nmatch;   //!
   TBranch        *b_tp_nloosematch;   //!
   TBranch        *b_tp_nstub;   //!
   TBranch        *b_tp_eventid;   //!
   TBranch        *b_tp_charge;   //!
   TBranch        *b_tp_injet;   //!
   TBranch        *b_tp_injet_highpt;   //!
   TBranch        *b_tp_injet_vhighpt;   //!
   TBranch        *b_matchtrk_pt;   //!
   TBranch        *b_matchtrk_eta;   //!
   TBranch        *b_matchtrk_phi;   //!
   TBranch        *b_matchtrk_z0;   //!
   TBranch        *b_matchtrk_d0;   //!
   TBranch        *b_matchtrk_chi2;   //!
   TBranch        *b_matchtrk_nstub;   //!
   TBranch        *b_matchtrk_seed;   //!
   TBranch        *b_matchtrk_injet;   //!
   TBranch        *b_matchtrk_injet_highpt;   //!
   TBranch        *b_matchtrk_injet_vhighpt;   //!
   TBranch        *b_loosematchtrk_pt;   //!
   TBranch        *b_loosematchtrk_eta;   //!
   TBranch        *b_loosematchtrk_phi;   //!
   TBranch        *b_loosematchtrk_z0;   //!
   TBranch        *b_loosematchtrk_d0;   //!
   TBranch        *b_loosematchtrk_chi2;   //!
   TBranch        *b_loosematchtrk_nstub;   //!
   TBranch        *b_loosematchtrk_seed;   //!
   TBranch        *b_loosematchtrk_injet;   //!
   TBranch        *b_loosematchtrk_injet_highpt;   //!
   TBranch        *b_loosematchtrk_injet_vhighpt;   //!
   TBranch        *b_allstub_x;   //!
   TBranch        *b_allstub_y;   //!
   TBranch        *b_allstub_z;   //!
   TBranch        *b_allstub_isBarrel;   //!
   TBranch        *b_allstub_layer;   //!
   TBranch        *b_allstub_isPSmodule;   //!
   TBranch        *b_allstub_trigDisplace;   //!
   TBranch        *b_allstub_trigOffset;   //!
   TBranch        *b_allstub_trigPos;   //!
   TBranch        *b_allstub_trigBend;   //!
   TBranch        *b_allstub_matchTP_pdgid;   //!
   TBranch        *b_allstub_matchTP_pt;   //!
   TBranch        *b_allstub_matchTP_eta;   //!
   TBranch        *b_allstub_matchTP_phi;   //!
   TBranch        *b_allstub_genuine;   //!
   TBranch        *b_allstub_isPS;   //!
   TBranch        *b_allstub_chip;   //!
   TBranch        *b_allstub_seg;   //!
   TBranch        *b_allstub_ladder;   //!
   TBranch        *b_allstub_module;   //!
   TBranch        *b_allstub_type;   //!
   TBranch        *b_allstub_module_x;   //!
   TBranch        *b_allstub_module_y;   //!
   TBranch        *b_allstub_module_z;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_tp_sumpt;   //!
   TBranch        *b_jet_trk_sumpt;   //!
   TBranch        *b_jet_matchtrk_sumpt;   //!
   TBranch        *b_jet_loosematchtrk_sumpt;   //!

   FE(TTree *tree=0);
   virtual ~FE();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     FE_eff(TString);
   virtual void     Chip_occupancy(TString);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FE_cxx
FE::FE(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("NuPU200.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("NuPU200.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("NuPU200.root:/L1TrackNtuple");
      dir->GetObject("eventTree",tree);

   }
   Init(tree);
}

FE::~FE()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FE::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FE::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void FE::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   trk_pt = 0;
   trk_eta = 0;
   trk_phi = 0;
   trk_d0 = 0;
   trk_z0 = 0;
   trk_chi2 = 0;
   trk_nstub = 0;
   trk_seed = 0;
   trk_genuine = 0;
   trk_loose = 0;
   trk_unknown = 0;
   trk_combinatoric = 0;
   trk_fake = 0;
   trk_matchtp_pdgid = 0;
   trk_matchtp_pt = 0;
   trk_matchtp_eta = 0;
   trk_matchtp_phi = 0;
   trk_matchtp_z0 = 0;
   trk_matchtp_dxy = 0;
   trk_injet = 0;
   trk_injet_highpt = 0;
   trk_injet_vhighpt = 0;
   tp_pt = 0;
   tp_eta = 0;
   tp_phi = 0;
   tp_dxy = 0;
   tp_d0 = 0;
   tp_z0 = 0;
   tp_d0_prod = 0;
   tp_z0_prod = 0;
   tp_pdgid = 0;
   tp_nmatch = 0;
   tp_nloosematch = 0;
   tp_nstub = 0;
   tp_eventid = 0;
   tp_charge = 0;
   tp_injet = 0;
   tp_injet_highpt = 0;
   tp_injet_vhighpt = 0;
   matchtrk_pt = 0;
   matchtrk_eta = 0;
   matchtrk_phi = 0;
   matchtrk_z0 = 0;
   matchtrk_d0 = 0;
   matchtrk_chi2 = 0;
   matchtrk_nstub = 0;
   matchtrk_seed = 0;
   matchtrk_injet = 0;
   matchtrk_injet_highpt = 0;
   matchtrk_injet_vhighpt = 0;
   loosematchtrk_pt = 0;
   loosematchtrk_eta = 0;
   loosematchtrk_phi = 0;
   loosematchtrk_z0 = 0;
   loosematchtrk_d0 = 0;
   loosematchtrk_chi2 = 0;
   loosematchtrk_nstub = 0;
   loosematchtrk_seed = 0;
   loosematchtrk_injet = 0;
   loosematchtrk_injet_highpt = 0;
   loosematchtrk_injet_vhighpt = 0;
   allstub_x = 0;
   allstub_y = 0;
   allstub_z = 0;
   allstub_isBarrel = 0;
   allstub_layer = 0;
   allstub_isPSmodule = 0;
   allstub_trigDisplace = 0;
   allstub_trigOffset = 0;
   allstub_trigPos = 0;
   allstub_trigBend = 0;
   allstub_matchTP_pdgid = 0;
   allstub_matchTP_pt = 0;
   allstub_matchTP_eta = 0;
   allstub_matchTP_phi = 0;
   allstub_genuine = 0;
   allstub_isPS = 0;
   allstub_chip = 0;
   allstub_seg = 0;
   allstub_ladder = 0;
   allstub_module = 0;
   allstub_type = 0;
   allstub_module_x = 0;
   allstub_module_y = 0;
   allstub_module_z = 0;
   jet_eta = 0;
   jet_phi = 0;
   jet_pt = 0;
   jet_tp_sumpt = 0;
   jet_trk_sumpt = 0;
   jet_matchtrk_sumpt = 0;
   jet_loosematchtrk_sumpt = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("trk_pt", &trk_pt, &b_trk_pt);
   fChain->SetBranchAddress("trk_eta", &trk_eta, &b_trk_eta);
   fChain->SetBranchAddress("trk_phi", &trk_phi, &b_trk_phi);
   fChain->SetBranchAddress("trk_d0", &trk_d0, &b_trk_d0);
   fChain->SetBranchAddress("trk_z0", &trk_z0, &b_trk_z0);
   fChain->SetBranchAddress("trk_chi2", &trk_chi2, &b_trk_chi2);
   fChain->SetBranchAddress("trk_nstub", &trk_nstub, &b_trk_nstub);
   fChain->SetBranchAddress("trk_seed", &trk_seed, &b_trk_seed);
   fChain->SetBranchAddress("trk_genuine", &trk_genuine, &b_trk_genuine);
   fChain->SetBranchAddress("trk_loose", &trk_loose, &b_trk_loose);
   fChain->SetBranchAddress("trk_unknown", &trk_unknown, &b_trk_unknown);
   fChain->SetBranchAddress("trk_combinatoric", &trk_combinatoric, &b_trk_combinatoric);
   fChain->SetBranchAddress("trk_fake", &trk_fake, &b_trk_fake);
   fChain->SetBranchAddress("trk_matchtp_pdgid", &trk_matchtp_pdgid, &b_trk_matchtp_pdgid);
   fChain->SetBranchAddress("trk_matchtp_pt", &trk_matchtp_pt, &b_trk_matchtp_pt);
   fChain->SetBranchAddress("trk_matchtp_eta", &trk_matchtp_eta, &b_trk_matchtp_eta);
   fChain->SetBranchAddress("trk_matchtp_phi", &trk_matchtp_phi, &b_trk_matchtp_phi);
   fChain->SetBranchAddress("trk_matchtp_z0", &trk_matchtp_z0, &b_trk_matchtp_z0);
   fChain->SetBranchAddress("trk_matchtp_dxy", &trk_matchtp_dxy, &b_trk_matchtp_dxy);
   fChain->SetBranchAddress("trk_injet", &trk_injet, &b_trk_injet);
   fChain->SetBranchAddress("trk_injet_highpt", &trk_injet_highpt, &b_trk_injet_highpt);
   fChain->SetBranchAddress("trk_injet_vhighpt", &trk_injet_vhighpt, &b_trk_injet_vhighpt);
   fChain->SetBranchAddress("tp_pt", &tp_pt, &b_tp_pt);
   fChain->SetBranchAddress("tp_eta", &tp_eta, &b_tp_eta);
   fChain->SetBranchAddress("tp_phi", &tp_phi, &b_tp_phi);
   fChain->SetBranchAddress("tp_dxy", &tp_dxy, &b_tp_dxy);
   fChain->SetBranchAddress("tp_d0", &tp_d0, &b_tp_d0);
   fChain->SetBranchAddress("tp_z0", &tp_z0, &b_tp_z0);
   fChain->SetBranchAddress("tp_d0_prod", &tp_d0_prod, &b_tp_d0_prod);
   fChain->SetBranchAddress("tp_z0_prod", &tp_z0_prod, &b_tp_z0_prod);
   fChain->SetBranchAddress("tp_pdgid", &tp_pdgid, &b_tp_pdgid);
   fChain->SetBranchAddress("tp_nmatch", &tp_nmatch, &b_tp_nmatch);
   fChain->SetBranchAddress("tp_nloosematch", &tp_nloosematch, &b_tp_nloosematch);
   fChain->SetBranchAddress("tp_nstub", &tp_nstub, &b_tp_nstub);
   fChain->SetBranchAddress("tp_eventid", &tp_eventid, &b_tp_eventid);
   fChain->SetBranchAddress("tp_charge", &tp_charge, &b_tp_charge);
   fChain->SetBranchAddress("tp_injet", &tp_injet, &b_tp_injet);
   fChain->SetBranchAddress("tp_injet_highpt", &tp_injet_highpt, &b_tp_injet_highpt);
   fChain->SetBranchAddress("tp_injet_vhighpt", &tp_injet_vhighpt, &b_tp_injet_vhighpt);
   fChain->SetBranchAddress("matchtrk_pt", &matchtrk_pt, &b_matchtrk_pt);
   fChain->SetBranchAddress("matchtrk_eta", &matchtrk_eta, &b_matchtrk_eta);
   fChain->SetBranchAddress("matchtrk_phi", &matchtrk_phi, &b_matchtrk_phi);
   fChain->SetBranchAddress("matchtrk_z0", &matchtrk_z0, &b_matchtrk_z0);
   fChain->SetBranchAddress("matchtrk_d0", &matchtrk_d0, &b_matchtrk_d0);
   fChain->SetBranchAddress("matchtrk_chi2", &matchtrk_chi2, &b_matchtrk_chi2);
   fChain->SetBranchAddress("matchtrk_nstub", &matchtrk_nstub, &b_matchtrk_nstub);
   fChain->SetBranchAddress("matchtrk_seed", &matchtrk_seed, &b_matchtrk_seed);
   fChain->SetBranchAddress("matchtrk_injet", &matchtrk_injet, &b_matchtrk_injet);
   fChain->SetBranchAddress("matchtrk_injet_highpt", &matchtrk_injet_highpt, &b_matchtrk_injet_highpt);
   fChain->SetBranchAddress("matchtrk_injet_vhighpt", &matchtrk_injet_vhighpt, &b_matchtrk_injet_vhighpt);
   fChain->SetBranchAddress("loosematchtrk_pt", &loosematchtrk_pt, &b_loosematchtrk_pt);
   fChain->SetBranchAddress("loosematchtrk_eta", &loosematchtrk_eta, &b_loosematchtrk_eta);
   fChain->SetBranchAddress("loosematchtrk_phi", &loosematchtrk_phi, &b_loosematchtrk_phi);
   fChain->SetBranchAddress("loosematchtrk_z0", &loosematchtrk_z0, &b_loosematchtrk_z0);
   fChain->SetBranchAddress("loosematchtrk_d0", &loosematchtrk_d0, &b_loosematchtrk_d0);
   fChain->SetBranchAddress("loosematchtrk_chi2", &loosematchtrk_chi2, &b_loosematchtrk_chi2);
   fChain->SetBranchAddress("loosematchtrk_nstub", &loosematchtrk_nstub, &b_loosematchtrk_nstub);
   fChain->SetBranchAddress("loosematchtrk_seed", &loosematchtrk_seed, &b_loosematchtrk_seed);
   fChain->SetBranchAddress("loosematchtrk_injet", &loosematchtrk_injet, &b_loosematchtrk_injet);
   fChain->SetBranchAddress("loosematchtrk_injet_highpt", &loosematchtrk_injet_highpt, &b_loosematchtrk_injet_highpt);
   fChain->SetBranchAddress("loosematchtrk_injet_vhighpt", &loosematchtrk_injet_vhighpt, &b_loosematchtrk_injet_vhighpt);
   fChain->SetBranchAddress("allstub_x", &allstub_x, &b_allstub_x);
   fChain->SetBranchAddress("allstub_y", &allstub_y, &b_allstub_y);
   fChain->SetBranchAddress("allstub_z", &allstub_z, &b_allstub_z);
   fChain->SetBranchAddress("allstub_isBarrel", &allstub_isBarrel, &b_allstub_isBarrel);
   fChain->SetBranchAddress("allstub_layer", &allstub_layer, &b_allstub_layer);
   fChain->SetBranchAddress("allstub_isPSmodule", &allstub_isPSmodule, &b_allstub_isPSmodule);
   fChain->SetBranchAddress("allstub_trigDisplace", &allstub_trigDisplace, &b_allstub_trigDisplace);
   fChain->SetBranchAddress("allstub_trigOffset", &allstub_trigOffset, &b_allstub_trigOffset);
   fChain->SetBranchAddress("allstub_trigPos", &allstub_trigPos, &b_allstub_trigPos);
   fChain->SetBranchAddress("allstub_trigBend", &allstub_trigBend, &b_allstub_trigBend);
   fChain->SetBranchAddress("allstub_matchTP_pdgid", &allstub_matchTP_pdgid, &b_allstub_matchTP_pdgid);
   fChain->SetBranchAddress("allstub_matchTP_pt", &allstub_matchTP_pt, &b_allstub_matchTP_pt);
   fChain->SetBranchAddress("allstub_matchTP_eta", &allstub_matchTP_eta, &b_allstub_matchTP_eta);
   fChain->SetBranchAddress("allstub_matchTP_phi", &allstub_matchTP_phi, &b_allstub_matchTP_phi);
   fChain->SetBranchAddress("allstub_genuine", &allstub_genuine, &b_allstub_genuine);
   fChain->SetBranchAddress("allstub_isPS", &allstub_isPS, &b_allstub_isPS);
   fChain->SetBranchAddress("allstub_chip", &allstub_chip, &b_allstub_chip);
   fChain->SetBranchAddress("allstub_seg", &allstub_seg, &b_allstub_seg);
   fChain->SetBranchAddress("allstub_ladder", &allstub_ladder, &b_allstub_ladder);
   fChain->SetBranchAddress("allstub_module", &allstub_module, &b_allstub_module);
   fChain->SetBranchAddress("allstub_type", &allstub_type, &b_allstub_type);
   fChain->SetBranchAddress("allstub_module_x", &allstub_module_x, &b_allstub_module_x);
   fChain->SetBranchAddress("allstub_module_y", &allstub_module_y, &b_allstub_module_y);
   fChain->SetBranchAddress("allstub_module_z", &allstub_module_z, &b_allstub_module_z);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_tp_sumpt", &jet_tp_sumpt, &b_jet_tp_sumpt);
   fChain->SetBranchAddress("jet_trk_sumpt", &jet_trk_sumpt, &b_jet_trk_sumpt);
   fChain->SetBranchAddress("jet_matchtrk_sumpt", &jet_matchtrk_sumpt, &b_jet_matchtrk_sumpt);
   fChain->SetBranchAddress("jet_loosematchtrk_sumpt", &jet_loosematchtrk_sumpt, &b_jet_loosematchtrk_sumpt);
   Notify();
}

Bool_t FE::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FE::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FE::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FE_cxx
