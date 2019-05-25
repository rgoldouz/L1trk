#include "stub_Eff.h"
#include "stubRate.h"
int main(){
TChain* TC;
TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D36_RelValTTbar_14TeV_PU200FEold/104_D36_RelValTTbar_14TeV_PU200_FE-defTune11*");
//stub_Eff effFEold104_D36_RelValTTbar_14TeV_PU200(TC);
//effFEold104_D36_RelValTTbar_14TeV_PU200.eff("104_D36_RelValTTbar_14TeV_PU200FEold","ele");
stubRate rateFEold104_D36_RelValTTbar_14TeV_PU200(TC);
rateFEold104_D36_RelValTTbar_14TeV_PU200.SR("104_D36_RelValTTbar_14TeV_PU200FEold","ele");
delete TC;

TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D36_RelValTTbar_14TeV_PU200FEC12/104_D36_RelValTTbar_14TeV_PU200_FEC12Tune11*");
//stub_Eff effFEC12104_D36_RelValTTbar_14TeV_PU200(TC);
//effFEC12104_D36_RelValTTbar_14TeV_PU200.eff("104_D36_RelValTTbar_14TeV_PU200FEC12","ele");
stubRate rateFEC12104_D36_RelValTTbar_14TeV_PU200(TC);
rateFEC12104_D36_RelValTTbar_14TeV_PU200.SR("104_D36_RelValTTbar_14TeV_PU200FEC12","ele");
delete TC;

TC = new TChain("L1TrackNtuple/eventTree") ;
TC ->Add("../104_D36_RelValTTbar_14TeV_PU200FEC5/104_D36_RelValTTbar_14TeV_PU200_FEC5Tune11*");
//stub_Eff effFEC5104_D36_RelValTTbar_14TeV_PU200(TC);
//effFEC5104_D36_RelValTTbar_14TeV_PU200.eff("104_D36_RelValTTbar_14TeV_PU200FEC5","ele");
stubRate rateFEC5104_D36_RelValTTbar_14TeV_PU200(TC);
rateFEC5104_D36_RelValTTbar_14TeV_PU200.SR("104_D36_RelValTTbar_14TeV_PU200FEC5","ele");
delete TC;

}
