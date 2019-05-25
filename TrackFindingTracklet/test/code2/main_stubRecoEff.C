//#include "FE.h"
#include "stub_Eff.h"
#include "stubRate.h"
//root [0] .L main.C
//root [1] .L FE.C+
//root [2] main()

int main(){

TChain* TC;

//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../104_D36_RelValTTbar_14TeV_PU200_tightTune/104_D36_RelValTTbar_14TeV_PU200_1*");
//stub_Eff stubefftt200_tightTune(TC);
//stubefftt200_tightTune.eff("104D37-TT_PU200_tightTune","pion");
//delete TC;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../104_D36_RelValTTbar_14TeV_PU200_looseTune/104_D36_RelValTTbar_14TeV_PU200_looseTune1*");
//stub_Eff stubefftt200_looseTune(TC);
//stubefftt200_looseTune.eff("104D37-TT_PU200_looseTune","pion");
//delete TC;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../104_D36_RelValTTbar_14TeV_PU200_oldTune/104_D36_RelValTTbar_14TeV_PU200_oldTune1*");
//stub_Eff stubefftt200_oldTune(TC);
//stubefftt200_oldTune.eff("104D37-TT_PU200_oldTune","pion");
//delete TC;
//
TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D21_RelValSingleMuPt1p5to8_pythia8_oldTune/*");
stub_Eff stubeffttSmu_oldTune(TC);
stubeffttSmu_oldTune.eff("104D21-Single-mu_PU0_oldTune","mu");
delete TC;

TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D21_RelValSingleMuPt1p5to8_pythia8_looseTune/*");
stub_Eff stubeffttSmu_looseTune(TC);
stubeffttSmu_looseTune.eff("104D21-Single-mu_PU0_looseTune","mu");
delete TC;

TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D21_RelValSingleMuPt1p5to8_pythia8_tightTune/*");
stub_Eff stubeffttSmu_tightTune(TC);
stubeffttSmu_tightTune.eff("104D21-Single-mu_PU0_tightTune","mu");
delete TC;

TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D21_RelValSingleElPt1p5to8_pythia8_oldTune/*");
stub_Eff stubeffSele_oldTune(TC);
stubeffSele_oldTune.eff("104D21-Single-ele_PU0_oldTune","ele");
delete TC;

TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D21_RelValSingleElPt1p5to8_pythia8_tightTune/*");
stub_Eff stubeffSele_tightTune(TC);
stubeffSele_tightTune.eff("104D21-Single-ele_PU0_tightTune","ele");
delete TC;

TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D21_RelValSingleElPt1p5to8_pythia8_looseTune/*");
stub_Eff stubeffSele_looseTune(TC);
stubeffSele_looseTune.eff("104D21-Single-ele_PU0_looseTune","ele");
delete TC;

return 0;
}
