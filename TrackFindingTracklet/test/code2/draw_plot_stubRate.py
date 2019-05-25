import math
import gc
import sys
import ROOT
import numpy as npi
import copy
from array import array
import os
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gROOT.ProcessLine("gErrorIgnoreLevel = 1;")
ROOT.TH1.AddDirectory(ROOT.kFALSE)
ROOT.gStyle.SetOptStat(0)
from ROOT import TColor
from ROOT import TGaxis
import gc
TGaxis.SetMaxDigits(2)
################################## MY SIGNAL AND SM BG ################################

def draw1dHist(A,textA="A", label_name="sample", can_name="can"):
    a,b,c,d = label_name.split("_")
    cc = int(c)+1
    canvas = ROOT.TCanvas(can_name,can_name,10,10,1100,628)
    canvas.cd()

    pad_name = "pad"
    pad1=ROOT.TPad(pad_name, pad_name, 0.05, 0.05, 1, 0.99 , 0)
    pad1.Draw()

    A.SetLineColor( 1 )
    A.SetLineWidth( 2 )
    A.SetTitle("")
    A.GetXaxis().SetTitle(b)
    A.GetYaxis().SetTitle('Stub rate '+d)
    A.GetXaxis().SetTitleSize(0.05)
    A.GetYaxis().SetTitleSize(0.05)
    A.SetMaximum(1.2*A.GetMaximum())
    A.SetMinimum(0);
    A.GetYaxis().SetTitleOffset(0.7)
    if b == "nstub":
        A.GetYaxis().SetTitle('Number of module')
    if "fail" in d:
        A.GetYaxis().SetTitle('fraction of stubs '+ d)
    if b == "type":
        A.GetXaxis().SetLabelSize(0.1)
    A.Draw()
    legend = ROOT.TLegend(0.6,0.9,1,1)
    legend.AddEntry(A ,textA,'l')
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
        label.DrawLatex(0.3,0.95, a + ", Layer " + str(cc))
    if a == 'Endcap':
        label.DrawLatex(0.3,0.95, a + ", Disk " + str(cc))
    canvas.Print("1D_" + can_name +"_"+ label_name + ".png")
    del canvas
    gc.collect()

def draw2dHist(inputfile = "F"):
    stub = ["_PBX","_PBXCBCfail", "_PBXCICfail"]
    text = ["rate PBX", "fraction of stubs failed by CBC/MPA", "fraction of stubs failed by CIC"]
    zscaleB = [6,0.01,0.01]
    zscaleE = [7,0.007,0.01]
    can_name = 'can'
    filem = ROOT.TFile.Open(inputfile)
    for num, st in enumerate(stub):
        for k in range(0, 6):
            canvas = ROOT.TCanvas(can_name,can_name,10,10,1100,628)
            canvas.cd()
            a = "Barrel_Rate2D_" + str(k) + st
            A = filem.Get(a)
            if st == "_PBX" or st == "_PBXCICfail": 
                A.GetZaxis().SetRangeUser(0, zscaleB[num])
            A.SetTitle("")
            A.GetXaxis().SetTitleSize(0.05)
            A.GetYaxis().SetTitleSize(0.05)
            A.GetYaxis().SetTitleOffset(0.7)
            A.GetXaxis().SetTitle("Module Z index");
            A.GetYaxis().SetTitle("Module #phi index")
#            A.GetZaxis().SetRangeUser(0, zscale[num])
            A.Draw("COLZ")
            label = ROOT.TLatex()
            label.SetTextAlign(12)
            label.SetTextFont(42)
            label.SetTextSize(0.06)
            label.SetNDC(ROOT.kTRUE)
            label.DrawLatex(0.1,0.95, "Barrel, Layer " + str(k+1) + "-" + text[num])
            canvas.Print("2D_" + st + a + ".png")
            del canvas
            gc.collect()
    
        for k in range(0, 5):
            cadre = ROOT.TH2F("","",30,-15.,15.,30,-15.,15.)
            canvas = ROOT.TCanvas(can_name,can_name,10,10,1000,1000)
            canvas.SetRightMargin(0.1340206)
            cadre.GetXaxis().SetLabelSize(0.)
            cadre.GetXaxis().SetLabelOffset(999)
            cadre.GetYaxis().SetLabelSize(0.)
            cadre.GetYaxis().SetLabelOffset(999)
            canvas.cd()
            cadre.Draw("col");
            a = "Endcap_Rate2D_" + str(k) + st
            for l in range(0, 15):
                b = "Endcap_Rate2D_" + str(k) + st +"_"+ str(l)
                A = filem.Get(b)
                A.GetZaxis().SetRangeUser(0, zscaleE[num])
                if l ==3:
                    A.Draw("POL colz SAME")  
                else:
                    A.Draw("POL col SAME")
                del A
                gc.collect()
            label = ROOT.TLatex()
            label.SetTextAlign(12)
            label.SetTextFont(42)
            label.SetTextSize(0.035)
            label.SetNDC(ROOT.kTRUE)
            label.DrawLatex(0.1,0.95, "Endcap (+Z), Disk " + str(k+1)+ "-" + text[num])
            canvas.Print("2D_"+ st  + a + ".png")
            del cadre
            del canvas
            gc.collect()

def compare2Hist(A, B, textA="A", textB="B", label_name="sample", can_name="can"):

    a,b,c,d = label_name.split("_")
    cc = int(c)+1
    canvas = ROOT.TCanvas(can_name,can_name,10,10,1100,628)
    canvas.cd()

    pad_name = "pad"
    pad1=ROOT.TPad(pad_name, pad_name, 0.05, 0.3, 1, 0.99 , 0)
    pad1.Draw()
    pad2=ROOT.TPad(pad_name, pad_name, 0.05, 0.05, 1, 0.3 , 0)
    pad2.SetGridy();
    pad2.Draw()
#    pad1.SetLogy()
    pad1.cd()
    
    A.SetLineColor( 2 )
    B.SetLineColor( 4 )    

    A.SetTitle("")
    A.GetXaxis().SetTitle(b)
    A.GetYaxis().SetTitle('Stub rate '+d)
    A.GetXaxis().SetTitleSize(0.05)
    A.GetYaxis().SetTitleSize(0.05)
    if b == "nstub":
        A.GetYaxis().SetTitle('Number of module')  
    A.SetMaximum(1.2*max(A.GetMaximum(),B.GetMaximum()));
    A.Draw()
    B.Draw('esame')

    legend = ROOT.TLegend(0.7,0.8,1,1)
    legend.AddEntry(A ,textA,'l')
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
        label.DrawLatex(0.1,0.95, a + ", Layer " + str(cc))
    if a == 'Endcap':
        label.DrawLatex(0.1,0.95, a + ", Disk " + str(cc))

    pad2.cd()    
    ratio = A.Clone()
    ratio.Divide(B)
    ratio.SetMaximum(1.05)
    ratio.SetMinimum(0.95)
    ratio.GetXaxis().SetTitle('')
    ratio.GetYaxis().SetTitle('')
    ratio.GetXaxis().SetLabelSize(0.1)
    ratio.GetYaxis().SetLabelSize(0.1)
    ratio.GetYaxis().SetNdivisions(505);
    ratio.SetTitleSize(1)
    ratio.SetTitle(textA +"/"+textB)
    ratio.Draw("e")

    canvas.Print("2H_" + can_name +"_"+ label_name + ".png")
    del canvas
    gc.collect()

def compare3Hist(A, B, C, textA="A", textB="B", textC="C",label_name="sample", can_name="can"):

    a,b,c,d = label_name.split("_")
    cc = int(c)+1
    canvas = ROOT.TCanvas(can_name,can_name,10,10,1100,628)
    canvas.SetRightMargin(0.15)
    canvas.cd()

    pad_name = "pad"
    pad1=ROOT.TPad(pad_name, pad_name, 0.05, 0.3, 1, 0.99 , 0)
    pad1.Draw()
    pad2=ROOT.TPad(pad_name, pad_name, 0.05, 0.05, 1, 0.3 , 0)
    pad2.SetGridy();
    pad2.Draw()
    pad1.cd()

    A.SetLineColor( 1 )
    B.SetLineColor( 2 )
    C.SetLineColor( 4 )

    A.SetTitle("")
    A.GetXaxis().SetTitle(b)
    A.GetYaxis().SetTitle('Stub rate '+ d)
    A.GetXaxis().SetTitleSize(0.05)
    A.GetYaxis().SetTitleSize(0.05)
    if b == "nstub":
        A.GetYaxis().SetTitle('Number of module')
    if "fail" in d:
        A.GetYaxis().SetTitle('fraction of stubs '+ d)
    if b == "type":
        A.GetXaxis().SetLabelSize(0.1)
    A.SetMaximum(1.4*max(A.GetMaximum(),B.GetMaximum(),C.GetMaximum()));
    A.SetMinimum(0);
    A.GetYaxis().SetTitleOffset(0.7)
    A.Draw()
    B.Draw('esame')
    C.Draw('esame')

    legend = ROOT.TLegend(0.7,0.75,1,1)
    legend.AddEntry(A ,textA,'l')
    legend.AddEntry(B ,textB,'l')
    legend.AddEntry(C ,textC,'l')
    legend.SetBorderSize(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.05)
    legend.Draw("same")

    label = ROOT.TLatex()
    label.SetTextAlign(12)
    label.SetTextFont(42)
    label.SetTextSize(0.08)
    label.SetNDC(ROOT.kTRUE)
    if a == 'Barrel':
        label.DrawLatex(0.2,0.95, a + ", Layer " + str(cc))
    if a == 'Endcap':
        label.DrawLatex(0.2,0.95, a + ", Disk " + str(cc))

    pad2.cd()
    ratioB = A.Clone()
    ratioB.Divide(B)
    ratioB.SetLineColor( 2 )
    ratioB.SetMaximum(2)
    ratioB.SetMinimum(0)
    r = ratioB.Clone()
    fontScale = 2
    nbin = ratioB.GetNbinsX()
    x_min= ratioB.GetBinLowEdge(1)
    x_max= ratioB.GetBinLowEdge(nbin)+ratioB.GetBinWidth(nbin)
#    ratio_y_min=0.95*r.GetBinContent(r.FindFirstBinAbove(0))
#    ratio_y_max=1.05*r.GetBinContent(r.GetMaximumBin())
    dummy_ratio = ROOT.TH2D("dummy_ratio","",nbin,x_min,x_max,1,0,2)
    dummy_ratio.SetStats(ROOT.kFALSE)
    dummy_ratio.GetYaxis().SetTitle('Ratio')
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
    ratioB.Draw("esame")

    ratioC = A.Clone()
    ratioC.Divide(C)
    ratioC.SetLineColor( 4 )
    ratioC.Draw("esame")

    canvas.Print("2D3H_" + can_name +"_"+ label_name + ".png")
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
#    A[0].GetXaxis().SetTitleSize(0.08);
#    A[0].GetYaxis().SetTitleSize(0.06);
#    A[0].GetYaxis().SetTitleOffset(0.5);
#    A[0].GetXaxis().SetLabelSize(0.08);
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
#["104D36-TT_PU200_output.root","104D37-TT_PU200_output.root"]
#["104D36-TT_PU200_oldTune_output.root","104D36-TT_PU200_looseTune_output.root","104D36-TT_PU200_tightTune_output.root"]
"104_D36_RelValTTbar_14TeV_PU200FEold_output.root","104_D36_RelValTTbar_14TeV_PU200FEC12_output.root","104_D36_RelValTTbar_14TeV_PU200FEC5_output.root"
#["104_D36_RelValTTbar_14TeV_PU200FEold_output.root"]
]

samplename = [
#"104D36-TT_PU200","104D37-TT_PU200"
"104D36-TT_PU200_FEold","104D36-TT_PU200_FEC12","104D36-TT_PU200_FEC5"
#"104D36-TT_PU200_FEold"
]
#cn = '104_D36TOD37'
#cn = '104D36_oldloosetighttune'
cn = '104D36_FEcomp'
region = ['Barrel', 'Endcap']
variable = ['rho','type', 'eta', 'z','nstub']
twoDvariable = ['Rate2D']
BX = ['PBX', 'PbxPmodule','PBXCICfail','PBXCBCfail','PbxPmoduleCICfail','PbxPmoduleCBCfail']

onedinputPlots = []

for r in region:
    for v in variable:
        for b in BX:
            for i in range(0, 6):
                onedinputPlots.append(r+'_'+v+'_'+str(i)+'_'+b)

onedinputPlots.append('BarrelpEndcap_type_*_PBX')
onedinputPlots.append('BarrelpEndcap_eta_*_PBX')

twodinputPlots = []
for r in region:
    for v in twoDvariable:
        for b in BX:
            for i in range(0, 6):
                twodinputPlots.append(r+'_'+v+'_'+str(i)+'_'+b)

sixdinputPlots=[]

for r in region:
    for v in variable:
        for b in BX:
            arr = []
            for i in range(0, 6):
                arr.append(r+'_'+v+'_'+str(i)+'_'+b)
            sixdinputPlots.append(arr)

is1D = True
is2D = False
is3D = False

if is1D:
    for num, sample in enumerate(samples):
        file1 = ROOT.TFile.Open(sample)
        for v in onedinputPlots:
            if v not in  [file1.GetListOfKeys()[ih].GetName() for ih in range(file1.GetListOfKeys().GetSize())]:
    #            print('do not find the hist')
                continue
            print samplename[num]
            print v
            histA = file1.Get(v)
            draw1dHist(histA, samplename[num], v,cn )
            del histA
        os.system("mkdir plot_rate1D" + samplename[num])
        os.system("mv *.png plot_rate1D" + samplename[num])
        draw2dHist(sample)
        os.system("mkdir plot_rate2D" + samplename[num])
        os.system("mv *.png plot_rate2D" + samplename[num])

if is2D:
    for num, sample in enumerate(samples):
        file1 = ROOT.TFile.Open(sample[0])
        file2 = ROOT.TFile.Open(sample[1])
        for v in onedinputPlots:
            if v not in  [file1.GetListOfKeys()[ih].GetName() for ih in range(file1.GetListOfKeys().GetSize())]:
    #            print('do not find the hist')
                continue
            if v not in  [file2.GetListOfKeys()[ih].GetName() for ih in range(file2.GetListOfKeys().GetSize())]:
    #            print('do not find the hist')
                continue
            print samplename[0]
            print v
            
            histA = file1.Get(v)
            histB = file2.Get(v)
            compare2Hist(histA, histB, samplename[0], samplename[1], v,cn )
            del histA
            del histB
    
    
        for v in sixdinputPlots:
            print v[0]
            if v[0] not in  [file1.GetListOfKeys()[ih].GetName() for ih in range(file1.GetListOfKeys().GetSize())]:
                continue
            plots1=[]
            plots2=[]
            for i in range(0, 6):
                plots1.append(file1.Get(v[i]))
                plots2.append(file2.Get(v[i]))
            compare6Hist(plots1, v[0],samplename[0])
            compare6Hist(plots2, v[0],samplename[1])

if is3D:
    file1 = ROOT.TFile.Open(samples[0])
    file2 = ROOT.TFile.Open(samples[1])
    file3 = ROOT.TFile.Open(samples[2])
    for v in onedinputPlots:
        if v not in  [file1.GetListOfKeys()[ih].GetName() for ih in range(file1.GetListOfKeys().GetSize())]:
            continue
        if v not in  [file2.GetListOfKeys()[ih].GetName() for ih in range(file2.GetListOfKeys().GetSize())]:
            continue
        if v not in  [file3.GetListOfKeys()[ih].GetName() for ih in range(file2.GetListOfKeys().GetSize())]:
            continue

        histA = file1.Get(v)
        histB = file2.Get(v)
        histC = file3.Get(v)
        compare3Hist(histA, histB, histC, samplename[0], samplename[1], samplename[2], v,cn )
        del histA
        del histB
        del histC

     
