from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()
import os
#General section: In this section, the user specifies generic parameters about the request (e.g. request name).
#config.section_('General')
#config.General.requestName = 'WZ_TuneCUETP8M1_13TeV-pythia8'
#config.General.requestName = 'ZToEE_NNPDF30_13TeV-powheg_M_4500_6000'
#config.General.requestName ='DoubleEG_Run2015D-16Dec2015-v2_MINIAOD'
#config.General.requestName ='RelValSingleMuPt2to100_pythia8'
#config.General.requestName ='RelValSingleMuPt1p5to8_pythia8'
#config.General.requestName ='RelValSingleElPt2to100_pythia8'
#config.General.requestName ='RelValSingleElPt1p5to8_pythia8'
#config.General.requestName ='RelValTTbar_14TeVnoPU'
#config.General.requestName = 'RelValTTbar_14TeVPU200'
#config.General.requestName = 'RelValDisplacedMuonsDxy_0_500_noPU_Pt2To100'
config.General.requestName = 'RelValDisplacedMuonsDxy_0_500_noPU_Pt1p5To8'


config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

#JobType section: This section aims to contain all the parameters of the user job type and related configurables (e.g. CMSSW parameter-set configuration file, additional input files, etc.).
#config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'L1TrackNtupleMaker_cfg.py'
config.JobType.inputFiles   = [ 'fitpattern.txt' , 'memorymodules_hourglass.dat', 'processingmodules_hourglass.dat', 'wires_hourglass.dat' ,'calcNumDTCLinks.txt', 'modules_T5v3_27SP_nonant_tracklet.dat']
#config.JobType.pyCfgParams = ['DataProcessing=mc', 'grid=True']
#config.JobType.outputFiles = ['outfile.root']

#Data section: This section contains all the parameters related to the data to be analyzed, including the splitting parameters.
#config.section_('Data')
#config.Data.inputDataset = '/WZ_TuneCUETP8M1_13TeV-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'
#config.Data.inputDataset = '/RelValSingleMuPt2to100_pythia8/CMSSW_9_3_7-93X_upgrade2023_realistic_v5_2023D17noPU-v1/GEN-SIM-DIGI-RAW'
#config.Data.inputDataset = '/RelValSingleMuPt1p5to8_pythia8/CMSSW_9_3_7-93X_upgrade2023_realistic_v5_2023D17noPU-v1/GEN-SIM-DIGI-RAW'
#config.Data.inputDataset = '/RelValSingleElPt2to100_pythia8_cfi/CMSSW_9_3_7-93X_upgrade2023_realistic_v5_2023D17noPU-v1/GEN-SIM-DIGI-RAW'
#config.Data.inputDataset = '/RelValSingleElPt1p5to8_pythia8/CMSSW_9_3_7-93X_upgrade2023_realistic_v5_2023D17noPU-v1/GEN-SIM-DIGI-RAW'
#config.Data.inputDataset = '/RelValTTbar_14TeV/CMSSW_9_3_7-93X_upgrade2023_realistic_v5_2023D17noPU-v2/GEN-SIM-DIGI-RAW'
#config.Data.inputDataset = '/RelValTTbar_14TeV/CMSSW_9_3_7-PU25ns_93X_upgrade2023_realistic_v5_2023D17PU200-v1/GEN-SIM-DIGI-RAW'
#config.Data.inputDataset = '/RelValDisplacedMuonsDxy_0_500/CMSSW_10_2_0_pre6-102X_upgrade2023_realistic_v5_2023D17noPU_Pt2To100-v1/GEN-SIM-DIGI-RAW'
config.Data.inputDataset = '/RelValDisplacedMuonsDxy_0_500/CMSSW_10_2_0_pre6-102X_upgrade2023_realistic_v5_2023D17noPU_Pt1p5To8-v1/GEN-SIM-DIGI-RAW'

config.Data.inputDBS = 'global'
#config.Data.splitting = 'FileBased'
#config.Data.unitsPerJob = 1
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 3000
NJOBS = 300  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.JobType.allowUndistributedCMSSW = True
#config.Data.ignoreLocality = True
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions12/8TeV/Prompt/Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
#config.Data.runRange = '193093-193999' # '193093-194075'
#config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
#config.Data.publication = True
#config.Data.outputDatasetTag = 'CRAB3_tutorial_May2015_Data_analysis'

#Site section: Grid site parameters are defined in this section, including the stage out information (e.g. stage out destination site, white/black lists, etc.).
config.section_("Site")
config.Site.storageSite = 'T2_BE_IIHE'
