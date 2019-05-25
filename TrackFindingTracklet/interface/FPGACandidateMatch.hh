//Holds the candidate matches
#ifndef FPGACANDIDATEMATCH_H
#define FPGACANDIDATEMATCH_H

#include "FPGATracklet.hh"
#include "FPGAMemoryBase.hh"
#include "FPGAStub.hh"
#include "L1TStub.hh"

using namespace std;

class FPGACandidateMatch:public FPGAMemoryBase{

public:

  FPGACandidateMatch(string name, unsigned int iSector, 
		     double phimin, double phimax):
    FPGAMemoryBase(name,iSector){
    phimin_=phimin;
    phimax_=phimax;
    string subname=name.substr(8,2);
    if (hourglass) subname=name.substr(3,2);
    layer_ = 0;
    disk_ = 0;
    if (subname=="L1") layer_=1;
    if (subname=="L2") layer_=2;
    if (subname=="L3") layer_=3;
    if (subname=="L4") layer_=4;
    if (subname=="L5") layer_=5;
    if (subname=="L6") layer_=6;
    //if (subname=="F1") disk_=1;
    //if (subname=="F2") disk_=2;
    //if (subname=="F3") disk_=3;
    //if (subname=="F4") disk_=4;
    //if (subname=="F5") disk_=5;
    if (subname=="D1") disk_=1;
    if (subname=="D2") disk_=2;
    if (subname=="D3") disk_=3;
    if (subname=="D4") disk_=4;
    if (subname=="D5") disk_=5;
    //if (subname=="B1") disk_=-1;
    //if (subname=="B2") disk_=-2;
    //if (subname=="B3") disk_=-3;
    //if (subname=="B4") disk_=-4;
    //if (subname=="B5") disk_=-5;
    if (layer_==0&&disk_==0) {
      cout << name<<" subname = "<<subname<<" "<<layer_<<" "<<disk_<<endl;
    }   
    assert((layer_!=0)||(disk_!=0)); 
  }

  void addMatch(FPGATracklet* tracklet,std::pair<FPGAStub*,L1TStub*> stub) {
    std::pair<FPGATracklet*,std::pair<FPGAStub*,L1TStub*> > tmp(tracklet,stub);

    //Check for consistency
    for(unsigned int i=0;i<matches_.size();i++){
      if (tracklet->homeSector()==matches_[i].first->homeSector()) {
	if (tracklet->TCID()<matches_[i].first->TCID()) {
	  cout << "In "<<getName()<<" adding tracklet "<<tracklet<<" with lower TCID : "
	       <<tracklet->TCID()<<" than earlier TCID "<<matches_[i].first->TCID()<<endl;
	  assert(0);
	}
      }
    }
    
    matches_.push_back(tmp);    
  }

  unsigned int nMatches() const {return matches_.size();}

  FPGATracklet* getFPGATracklet(unsigned int i) const {return matches_[i].first;}
  std::pair<FPGAStub*,L1TStub*> getStub(unsigned int i) const {return matches_[i].second;}
	std::pair<FPGATracklet*,std::pair<FPGAStub*,L1TStub*> >
	getMatch(unsigned int i) const {return matches_[i];}

  void clean() {
    matches_.clear();
  }

  void writeCM(bool first) {

    std::string fname="MemPrints/Matches/CandidateMatches_";
    fname+=getName();
    fname+="_";
    ostringstream oss;
    oss << iSector_+1;
    if (iSector_+1<10) fname+="0";
    fname+=oss.str();
    fname+=".dat";
    if (first) {
      bx_=0;
      event_=1;
      out_.open(fname.c_str());
    }   
    else
      out_.open(fname.c_str(),std::ofstream::app);

    out_ << "BX = "<<(bitset<3>)bx_ << " Event : " << event_ << endl;

    for (unsigned int j=0;j<matches_.size();j++){
      string stubid = matches_[j].second.first->stubindex().str(); // stub ID
      string match= (layer_>0)? matches_[j].first->candmatchstr(layer_) 
        : matches_[j].first->candmatchdiskstr(disk_); // tracklet ID
        if (j<16) out_ <<"0";
        out_ << hex << j << dec ;
        out_ << " "<< match << stubid << endl;
    }   
    out_.close();

    bx_++;
    event_++;
    if (bx_>7) bx_=0;
    
  }

  int layer() const { return layer_;}
  int disk() const { return disk_;}

private:

  double phimin_;
  double phimax_;
  std::vector<std::pair<FPGATracklet*,std::pair<FPGAStub*,L1TStub*> > > matches_;

  int layer_;
  int disk_;

};

#endif
