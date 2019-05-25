
# In order to run the code
#cmsRun L1StubNtupleMaker_cfg.py file="XX" outfile="X"

import sys
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as opts
import copy
import os

options = opts.VarParsing ("analysis")
options.register("filein",
                 "0E4CD60A-0FC3-E611-BCB5-0CC47A7C3420.root",
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 "file to analyze")
options.register("outfile",
                 "out_file.root",
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 "output file name")
options.parseArguments()




############################################################
# define basic process
############################################################

import FWCore.ParameterSet.Config as cms
import os
process = cms.Process("L1TrackNtuple")

GEOMETRY = "D17"

 
############################################################
# import standard configurations
############################################################

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')

if GEOMETRY == "D10": 
    print "using geometry " + GEOMETRY + " (flat)"
    process.load('Configuration.Geometry.GeometryExtended2023D10Reco_cff')
    process.load('Configuration.Geometry.GeometryExtended2023D10_cff')
elif GEOMETRY == "D17":
    print "using geometry " + GEOMETRY + " (tilted)"
    process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
    process.load('Configuration.Geometry.GeometryExtended2023D17_cff')
elif GEOMETRY == "TkOnly": 
    print "using standalone tilted (T5) tracker geometry" 
    process.load('L1Trigger.TrackTrigger.TkOnlyTiltedGeom_cff')
else:
    print "this is not a valid geometry!!!"

process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgradePLS3', '')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
############################################################
# input and output
############################################################

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

#sampleName = 'RelValSingleElPt2to100_pythia8'
#sampleName ='RelValSingleElPt1p5to8_pythia8'
#sampleName ='93RelValSingleElPt1p5to8_pythia8'
#sampleName ='RelValDisplacedMu_Pt_1p5to8'
#sampleName ='RelValDisplacedMu_Pt_2to100'
#sampleName ='104_D21_RelValTTbar_14TeV_PU200'
sampleName ='104_D36_RelValTTbar_14TeV_PU200'
#sampleName ='104_D37_RelValTTbar_14TeV_PU200'
#sampleName ='104_D21_RelValTTbar_14TeV_PU200'
#sampleName ='104_D21_RelValSingleElPt1p5to8_pythia8'
#sampleName ='104_D21_RelValDisplacedMu_Pt_1p5to8'
#sampleName ='104_D21_RelValSingleMuPt1p5to8_pythia8'
#sampleName ='104_D21_RelValTTbar_14TeV_PU000'

if GEOMETRY == "D17":
    #D17 (tilted barrel -- latest and greatest with T5 tracker, see: https://github.com/cms-sw/cmssw/blob/CMSSW_9_3_0_pre2/Configuration/Geometry/README.md)
    Source_Files = cms.untracked.vstring(
#     "/store/relval/CMSSW_10_4_0_pre2/RelValSingleElPt2to100_pythia8/GEN-SIM-DIGI-RAW/103X_upgrade2023_realistic_v2_2023D21noPU-v1/20000/E74D908F-341D-D045-8230-4DA125F3DF60.root"
    )
    
elif GEOMETRY == "TkOnly":
    Source_Files = cms.untracked.vstring(
    "file:/afs/cern.ch/work/s/skinnari/public/L1TK_90X/MuMinus_1to10_TkOnly.root"
    )
process.source = cms.Source("PoolSource", 
                          fileNames = cms.untracked.vstring(),
#fileNames = Source_Files,
                          inputCommands = cms.untracked.vstring(
                              'keep *_*_*_*',
                              'drop l1tEMTFHit2016*_*_*_*',
                              'drop l1tEMTFTrack2016*_*_*_*'
                            )
)

process.source.fileNames.append(options.filein)
process.TFileService = cms.Service("TFileService", fileName = cms.string(options.outfile), closeFileFast = cms.untracked.bool(True))



############################################################
# L1 tracking
############################################################

# remake stubs ?
process.load('L1Trigger.TrackTrigger.TrackTrigger_cff')
from L1Trigger.TrackTrigger.TTStubAlgorithmRegister_cfi import *
process.load("SimTracker.TrackTriggerAssociation.TrackTriggerAssociator_cff")

if GEOMETRY == "D10": 
    TTStubAlgorithm_official_Phase2TrackerDigi_.zMatchingPS = cms.bool(False)

if GEOMETRY != "TkOnly":
    from SimTracker.TrackTriggerAssociation.TTClusterAssociation_cfi import *
    TTClusterAssociatorFromPixelDigis.digiSimLinks = cms.InputTag("simSiPixelDigis","Tracker")

process.TTClusterStub = cms.Path(process.TrackTriggerClustersStubs)
process.TTClusterStubTruth = cms.Path(process.TrackTriggerAssociatorClustersStubs)

from L1Trigger.TrackFindingTracklet.Tracklet_cfi import *

### floating-point version
#process.load("L1Trigger.TrackFindingTracklet.L1TrackletTracks_cff")
#if GEOMETRY == "D10": 
#    TTTracksFromTracklet.trackerGeometry = cms.untracked.string("flat")
#TTTracksFromTracklet.asciiFileName = cms.untracked.string("evlist.txt")
#TTTracksFromTracklet.failscenario = cms.untracked.int32(0)
#process.TTTracks = cms.Path(process.L1TrackletTracks)
#process.TTTracksWithTruth = cms.Path(process.L1TrackletTracksWithAssociators)


### emulation instead 
process.load("L1Trigger.TrackFindingTracklet.L1TrackletEmulationTracks_cff")
process.TTTracksEmulation = cms.Path(process.L1TrackletEmulationTracks)
process.TTTracksEmulationWithTruth = cms.Path(process.L1TrackletEmulationTracksWithAssociators)
#TTTracksFromTrackletEmulation.asciiFileName = cms.untracked.string("evlist.txt")
#TTTracksFromTrackletEmulation.failscenario = cms.untracked.int32(0)



############################################################
# Define the track ntuple process, MyProcess is the (unsigned) PDGID corresponding to the process which is run
# e.g. single electron/positron = 11
#      single pion+/pion- = 211
#      single muon+/muon- = 13 
#      pions in jets = 6
#      taus = 15
#      all TPs = 1
############################################################

process.L1TrackNtuple = cms.EDAnalyzer('L1TrackNtupleMaker',
                                       MyProcess = cms.int32(1),
                                       DebugMode = cms.bool(False),      # printout lots of debug statements
                                       SaveAllTracks = cms.bool(False),   # save *all* L1 tracks, not just truth matched to primary particle
                                       SaveStubs = cms.bool(True),      # save some info for *all* stubs
                                       L1Tk_nPar = cms.int32(4),         # use 4 or 5-parameter L1 track fit ??
                                       L1Tk_minNStub = cms.int32(4),     # L1 tracks with >= 4 stubs
                                       TP_minNStub = cms.int32(4),       # require TP to have >= X number of stubs associated with it
                                       TP_minNStubLayer = cms.int32(4),  # require TP to have stubs in >= X layers/disks
                                       TP_minPt = cms.double(3.0),       # only save TPs with pt > X GeV
                                       TP_maxEta = cms.double(2.4),      # only save TPs with |eta| < X
                                       TP_maxZ0 = cms.double(30.0),      # only save TPs with |z0| < X cm
                                       TP_maxR = cms.double(30.0),      # only save TPs with |dxy| < X cm
                                       #L1TrackInputTag = cms.InputTag("TTTracksFromTracklet", "Level1TTTracks"),                ## TTTrack input
                                       L1TrackInputTag = cms.InputTag("TTTracksFromTrackletEmulation", "Level1TTTracks"),        ## TTTrack input
                                       MCTruthTrackInputTag = cms.InputTag("TTTrackAssociatorFromPixelDigis", "Level1TTTracks"), ## MCTruth input 
                                       # other input collections
                                       L1StubInputTag = cms.InputTag("TTStubsFromPhase2TrackerDigis","StubAccepted"),
                                       MCTruthClusterInputTag = cms.InputTag("TTClusterAssociatorFromPixelDigis", "ClusterAccepted"),
                                       MCTruthStubInputTag = cms.InputTag("TTStubAssociatorFromPixelDigis", "StubAccepted"),
                                       TrackingParticleInputTag = cms.InputTag("mix", "MergedTrackTruth"),
                                       TrackingVertexInputTag = cms.InputTag("mix", "MergedTrackTruth"),
                                       ## tracking in jets stuff (--> requires AK4 genjet collection present!)
                                       TrackingInJets = cms.bool(True),
                                       GenJetInputTag = cms.InputTag("ak4GenJets", ""),
                                       GenParticleInputTag = cms.InputTag("genParticles"),
                                       )
process.ana = cms.Path(process.L1TrackNtuple)

# use this if you want to re-run the stub making
process.schedule = cms.Schedule(process.TTClusterStub,process.TTClusterStubTruth,process.TTTracksEmulationWithTruth,process.ana)

# use this if cluster/stub associators not available 
#process.schedule = cms.Schedule(process.TTClusterStubTruth,process.TTTracksEmulationWithTruth,process.ana)

# use this to only run tracking + track associator
#process.schedule = cms.Schedule(process.TTTracksEmulationWithTruth,process.ana)

