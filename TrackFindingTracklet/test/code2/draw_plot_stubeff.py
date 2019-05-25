import math
import gc
import os,sys
import sys
import ROOT
import numpy as npi
import copy
from array import array
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gROOT.ProcessLine("gErrorIgnoreLevel = 1;")
ROOT.TH1.AddDirectory(ROOT.kFALSE)
ROOT.gStyle.SetOptStat(0)


import gc

################################## MY SIGNAL AND SM BG ################################

def compare3effHist(A, B, C, textA="A", textB="B", textC="C", label_name="sample", can_name="can"):
    a,i,b,c,d,p = label_name.split("_")
    cc = int(c)+1
    canvas = ROOT.TCanvas(can_name,can_name,10,10,1100,628)
    canvas.cd()
    A.SetLineColor( 1 )
    B.SetLineColor( 2 )
    C.SetLineColor( 4 )

    A.SetMaximum(1.1)
    A.SetMinimum(0.5)
    A.SetTitle("")
    A.GetXaxis().SetTitle(b)
    A.GetYaxis().SetTitle('Stub eff ')
    A.GetXaxis().SetTitleSize(0.05)
    A.GetYaxis().SetTitleSize(0.05)
    A.Draw('e')
    B.Draw('esame')
    C.Draw('esame')

    legend = ROOT.TLegend(0.7,0.8,1,1)
    legend.AddEntry(A ,textA,'l')
    legend.AddEntry(B ,textB,'l')
    legend.AddEntry(C ,textC,'l')
    legend.SetBorderSize(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.04)
    legend.Draw("same")

    label = ROOT.TLatex()
    label.SetTextAlign(12)
    label.SetTextFont(42)
    label.SetTextSize(0.08)
    label.SetNDC(ROOT.kTRUE)
    if a == 'Barrel':
        label.DrawLatex(0.1,0.95, a + ", Layer " + str(cc))
    if a == 'Endcap':
        label.DrawLatex(0.1,0.95, a + ", Disk " + str(cc))

    if not os.path.exists("plots_"+can_name):
        os.mkdir( "plots_"+can_name, 0755 );

    print str(A.Integral())
    if A.Integral()>0:
        canvas.Print("plots_"+can_name+"/3hist_stubeff_" + can_name +"_"+ label_name + ".png")
    del canvas
    gc.collect()

def compare2Hist(A, B, textA="A", textB="B", label_name="sample", can_name="can"):

    a,i,b,c,d,p = label_name.split("_")
    cc = int(c)+1
    canvas = ROOT.TCanvas(can_name,can_name,10,10,1100,628)
    canvas.cd()

    pad_name1 = "pad1"
    pad1=ROOT.TPad(pad_name1, pad_name1, 0.05, 0.3, 1, 0.99 , 0)
    pad1.Draw()
    pad_name2 = "pad2"
    pad2=ROOT.TPad(pad_name2, pad_name2, 0.05, 0.05, 1, 0.3 , 0)
    pad2.SetGridy();
    pad2.Draw()
#    pad1.SetLogy()
    pad1.cd()
    
    A.SetLineColor( 2 )
    B.SetLineColor( 4 )    

    A.SetTitle("")
    A.GetXaxis().SetTitle(b)
    A.GetYaxis().SetTitle('rate for TP (p_{T}>2) '+d)
    A.GetXaxis().SetTitleSize(0.05)
    A.GetYaxis().SetTitleSize(0.05)
    A.SetMaximum(1.2*max(A.GetMaximum(),B.GetMaximum()));
    A.Draw()
    B.Draw('esame')

    legend = ROOT.TLegend(0.7,0.8,1,1)
    legend.AddEntry(A ,'2*'+textA,'l')
    legend.AddEntry(B ,textB,'l')
    legend.SetBorderSize(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.04)
    legend.Draw("same")

    label = ROOT.TLatex()
    label.SetTextAlign(12)
    label.SetTextFont(42)
    label.SetTextSize(0.08)
    label.SetNDC(ROOT.kTRUE)
    if a == 'Barrel':
        label.DrawLatex(0.1,0.95, a + "-Layer " + str(cc) + ", " + can_name + " (" + p + ")")
    if a == 'Endcap':
        label.DrawLatex(0.1,0.95, a + "Disk " + str(cc) + ", " + can_name + " (" + p + ")")

    pad2.cd()    
    ratio = A.Clone()
    ratio.Divide(B)
    r = ratio.Clone()
    fontScale = 2
    nbin = ratio.GetNbinsX()
    x_min= ratio.GetBinLowEdge(1)
    x_max= ratio.GetBinLowEdge(nbin)+ratio.GetBinWidth(nbin)
    ratio_y_min=0.95*r.GetBinContent(r.FindFirstBinAbove(0))
    ratio_y_max=1.05*r.GetBinContent(r.GetMaximumBin()) 
    dummy_ratio = ROOT.TH2D("dummy_ratio","",nbin,x_min,x_max,1,ratio_y_min,ratio_y_max)
    dummy_ratio.SetStats(ROOT.kFALSE)
    dummy_ratio.GetYaxis().SetTitle('Stub eff')
    dummy_ratio.GetXaxis().SetTitle(b)
    dummy_ratio.GetXaxis().SetTitleSize(0.05*fontScale)
    dummy_ratio.GetXaxis().SetLabelSize(0.05*fontScale)
    dummy_ratio.GetXaxis().SetMoreLogLabels()
    dummy_ratio.GetXaxis().SetNoExponent()
    dummy_ratio.GetYaxis().SetNdivisions(505)
    dummy_ratio.GetYaxis().SetTitleSize(0.07*fontScale)
    dummy_ratio.GetYaxis().SetLabelSize(0.05 *fontScale)
    dummy_ratio.GetYaxis().SetTitleOffset(0.3)
    dummy_ratio.Draw()
    ratio.Draw("esame")
    if not os.path.exists("plots_"+can_name):
        os.mkdir( "plots_"+can_name, 0755 );
    if A.Integral()>0:
        canvas.Print("plots_"+can_name+"/2D_stubeff_" + can_name +"_"+ label_name + ".png")
    del canvas
    gc.collect()


def compare6Hist(A,label_name="sample", can_name="can"):

    a,b,c,d = label_name.split("_")
    canvas = ROOT.TCanvas(can_name,can_name,10,10,1100,628)
    canvas.cd()

    pad_name = "pad"
    pad1=ROOT.TPad(pad_name, pad_name, 0, 0, 1, 1 , 0)
    pad1.Draw()
    pad1.cd()
#    pad1.SetLogy()
    A[0].SetTitle("")
    A[0].GetXaxis().SetTitle(b)
    A[0].GetYaxis().SetTitle('Stub rate '+d)
    A[0].SetMarkerStyle(25);
    A[1].SetMarkerStyle(20);
    A[2].SetMarkerStyle(21);
    A[3].SetMarkerStyle(22);
    A[4].SetMarkerStyle(23);
    A[5].SetMarkerStyle(4);
    
    A[0].SetMarkerColor(2);
    A[1].SetMarkerColor(3);
    A[2].SetMarkerColor(4);
    A[3].SetMarkerColor(1);
    A[4].SetMarkerColor(6);
    A[5].SetMarkerColor(7);

    A[0].SetTitle("");
    A[0].SetMinimum(0);
    A[0].SetMaximum(1.2*A[0].GetMaximum());

    A[0].Draw("p HIST SAME")
    A[1].Draw("p HIST SAME")
    A[2].Draw("p HIST SAME")
    A[3].Draw("p HIST SAME")
    A[4].Draw("p HIST SAME")
    if a == "Barrel":
        A[5].Draw("p HIST SAME")

    leg = ROOT.TLegend(0.85,0.7,1,0.98)
    if a == "Barrel":
        leg.AddEntry(A[0], "Layer 1"                           , "p");
        leg.AddEntry(A[1], "Layer 2"                           , "p");
        leg.AddEntry(A[2], "Layer 3"                           , "p");
        leg.AddEntry(A[3], "Layer 4"                           , "p");
        leg.AddEntry(A[4], "Layer 5"                           , "p");
        leg.AddEntry(A[5], "Layer 6"                           , "p");
    if a == "Endcap":
        leg.AddEntry(A[0], "Disk 1"                           , "p");
        leg.AddEntry(A[1], "Disk 2"                           , "p");
        leg.AddEntry(A[2], "Disk 3"                           , "p");
        leg.AddEntry(A[3], "Disk 4"                           , "p");
        leg.AddEntry(A[4], "Disk 5"                           , "p");

    leg.SetBorderSize(0)
    leg.SetTextFont(42)
    leg.SetTextSize(0.04)
    leg.Draw("same")

    label = ROOT.TLatex()
    label.SetTextAlign(12)
    label.SetTextFont(42)
    label.SetTextSize(0.08)
    label.SetNDC(ROOT.kTRUE)
    label.DrawLatex(0.1,0.95, a + " , "+ can_name)

    canvas.Print("6D_"+a+"_"+b+can_name + ".png")
    del canvas
    gc.collect()

samples = [
"104D37-TT_PU200_stubeff_output.root",
"104D37-TT_PU0_stubeff_output.root",
"104D21-Single-mu_PU0_stubeff_output.root",
"104D21-Displaced-mu_PU0_stubeff_output.root",
"104D21-Single-ele_PU0_stubeff_output.root"
]

samplename = [
#"104_D36_RelValTTbar_14TeV_PU200"
#"104_D21_RelValSingleMuPt1p5to8_pythia8",
#"104_D21_RelValDisplacedMu_Pt_1p5to8",
"104_D21_RelValSingleElPt1p5to8_pythia8"
]

pname = [
#"pion",
#"mu",
#"mu",
"ele"
]

region = ['Barrel', 'Endcap']
SC = ['Stub', 'Cluster']
variable = ['eta', 'pt']
BX = ['PBX']


#for num, sample in enumerate(samples):
#    file1 = ROOT.TFile.Open(sample)
#    for r in region:
#        for v in variable:
#            for b in BX:
#                for i in range(0, 6):
#                    v1=r+'_'+SC[0]+'_'+v+'_'+str(i)+'_'+b+'_'+pname[num]
#                    v2=r+'_'+SC[1]+'_'+v+'_'+str(i)+'_'+b+'_'+pname[num]
#                    histA = file1.Get(v1)
#                    histB = file1.Get(v2)
#                    compare2Hist(histA, histB, SC[0], SC[1], v1,samplename[num] )
#                    del histA
#                    del histB

for num, sample in enumerate(samplename):
    file1 = ROOT.TFile.Open(sample + 'old_stubeff_output.root')
    file2 = ROOT.TFile.Open(sample + 'loose_stubeff_output.root')
#    file3 = ROOT.TFile.Open(sample + 'tight_stubeff_output.root')
    file3 = ROOT.TFile.Open(sample + 'test_stubeff_output.root')

    for r in region:
        for v in variable:
            for b in BX:
                for i in range(0, 6):
                    v1=r+'_'+SC[0]+'_'+v+'_'+str(i)+'_'+b+'_'+pname[num]
                    v2=r+'_'+SC[1]+'_'+v+'_'+str(i)+'_'+b+'_'+pname[num]
                    histA1 = file1.Get(v1)
                    histA2 = file1.Get(v2)
                    histB1 = file2.Get(v1)
                    histB2 = file2.Get(v2)
                    histC1 = file3.Get(v1)
                    histC2 = file3.Get(v2)
                    histA1.Divide(histA2)
                    histB1.Divide(histB2)
                    histC1.Divide(histC2)
                    compare3effHist(histA1, histB1, histC1, 'oldTune', 'looseTune', 'tightTune', v1,samplename[num] )
                    del histA1
                    del histA2
                    del histB1
                    del histB2
                    del histC1
                    del histC2
