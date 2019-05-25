//#include "FE.h"
#include "stubRecoEff.h"
#include "stubRate.h"
//root [0] .L main.C
//root [1] .L FE.C+
//root [2] main()

int main(){

//TChain* ele = new TChain("L1TrackNtuple/eventTree") ;
////ele ->Add("../RelValSingleElPt2to100_pythia8.root");
//ele ->Add("../RelValSingleElPt1p5to8_pythia8.root");
//stubRecoEff stubeffele(ele);
//stubeffele.eff3("104X-SingleEl","ele");
//delete ele;

TChain* TC;
//TC = new TChain("L1TrackNtuple/eventTree") ;
////mu ->Add("../RelValSingleMuPt2to100_pythia8.root");
//TC ->Add("../RelValSingleMuPt1p5to8_pythia8.root");
//stubRecoEff stubeffmu(TC);
//stubeffmu.eff3("104X-SingleMu","mu");
//delete TC;
//
////TChain* Dmu = new TChain("L1TrackNtuple/eventTree") ;
////mu ->Add("../RelValDisplacedMu_Pt_1p5to8.root");
////stubRecoEff stubeffDmu(Dmu);
////stubeffDmu.eff3("104X-DisplacedMu","mu");
////delete Dmu;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../RelValTTbar_14TeV_PU000.root");
//stubRecoEff stubefftt0(TC);
//stubefftt0.eff3("104X-TTba__PU0","pi");
//delete TC;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../RelValTTbar_14TeV_PU200.root");
//stubRecoEff stubefftt200(TC);
//stubefftt200.eff3("104X-TTba__PU200","pi");
//delete TC;

//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../93RelValSingleMuPt1p5to8_pythia8.root");
//stubRecoEff stubeffmu93(TC);
//stubeffmu93.eff3("93X-SingleMu","mu");
//delete TC;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../93RelValTTbar_14TeV_PU000.root");
//stubRecoEff stubefftt093(TC);
//stubefftt093.eff3("93X-TTba__PU0","mu");
//delete TC;

//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../RelValSingleMuPt1p5to8_pythia8.root");
//stubRate stubRatemu(TC);
//stubRatemu.SR("104X-SingleMu","mu");
//delete TC;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../93RelValSingleMuPt1p5to8_pythia8.root");
//stubRate stubRate93mu(TC);
//stubRate93mu.SR("93X-SingleMu","mu");
//delete TC;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../104_D21_RelValTTbar_14TeV_PU200.root");
//stubRate stubRatett_104D21_200(TC);
//stubRatett_104D21_200.TPR("104D21-TT_PU200","");
//stubRatett_104D21_200.SR("104Pre2D21-TT_PU200_NormToAllTPs","");
//delete TC;
//
TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D36_RelValTTbar_14TeV_PU200_oldTune/104_D36_RelValTTbar_14TeV_PU200_oldTune11*");
stubRate stubRatett_104D36_200(TC);
//stubRatett_104D36_200.TPR("104D36-TT_PU200","");
stubRatett_104D36_200.SR("104D36-TT_PU200_oldTune","");
delete TC;
////
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("combine_104_D37_RelValTTbar_14TeV_PU200.root");
//stubRate stubRatett_104D37_200(TC);
////stubRatett_104D37_200.TPR("104D37-TT_PU200","");
//stubRatett_104D37_200.SR("104D37-TT_PU200_test","");
//delete TC;

//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../104_D37_RelValTTbar_14TeV_PU200_oldTune.root");
//stubRate stubRatettOT_104D37_200(TC);
//stubRatettOT_104D37_200.SR("104D37-TT_PU200_oldTune","");
//delete TC;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../93RelValTTbar_14TeV_PU200.root");
//stubRate stubRatett20093(TC);
//stubRatett20093.TPR("93X-TT_PU200","");
//stubRatett20093.SR("93X-TT_PU200","");
//delete TC;


//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../Emily.root");
//stubRate stubRatett20093(TC);
//stubRatett20093.TPR("104X-TT_PU200_NormToAllTPs","");
//stubRatett20093.SR("104X-TT_PU200_NormToAllTPs","");
//delete TC;

//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../RelValTTbar_14TeV_PU000.root");
//stubRate stubRatett000(TC);
//stubRatett000.SR("104X-TT__PU000","mu");
//delete TC;
//
//TC = new TChain("L1TrackNtuple/eventTree") ;
//TC ->Add("../93RelValTTbar_14TeV_PU000.root");
//stubRate stubRatett00093(TC);
//stubRatett00093.SR("93X-TT__PU000","mu");
//delete TC;

return 0;
}
