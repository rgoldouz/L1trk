import sys
import os
import subprocess
import readline
import string

#sample ='104_D21_RelValSingleMuPt1p5to8_pythia8'
samples = [
#'104_D21_RelValSingleMuPt1p5to8_pythia8',
#'104_D21_RelValSingleElPt1p5to8_pythia8',
#'104_D21_RelValDisplacedMu_Pt_1p5to8'
#'104_D21_RelValTTbar_14TeV_PU000',
#'104_D36_RelValTTbar_14TeV_PU200'
'104_D36_RelValTTbar_14TeV_PU200'
]
pdg =[
#"mu",
"ele",
#"mu",
#"pion",
#"pion"
]
Tune =[ 
#"tight",
#"loose",
#"old",
"FEold",
"FEC12",
"FEC5"]

text = ''
for num, sample in enumerate(samples):
    for T in Tune:
        text += 'TC = new TChain("L1TrackNtuple/eventTree") ;\n' +\
        'TC ->Add("../' + sample + T +'/*");\n' +\
        '//stub_Eff eff' + T + sample +'(TC);\n' +\
        '//eff' + T + sample + '.eff("' + sample + T +'","'+pdg[num]  + '");\n' +\
        'stubRate rate' + T + sample +'(TC);\n' +\
        'rate' + T + sample + '.SR("' + sample + T +'","'+pdg[num]  + '");\n' +\
        'delete TC;\n' +\
        '\n' +\
        ''


SHNAME = 'main_sEff.C'
SHFILE='#include "stub_Eff.h"\n' +\
'#include "stubRate.h"\n' +\
'int main(){\n' +\
'TChain* TC;\n' +\
text +\
'}'

open(SHNAME, 'wt').write(SHFILE)
os.system("chmod +x "+SHNAME)
