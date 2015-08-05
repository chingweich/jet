#include <TLegend.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TImage.h"
#include "TSystem.h"
#include "TStyle.h"
#include "untuplizer.h"
#include "TAxis.h"

TCanvas* c1;


void smalltask0804(){
	gStyle->SetOptStat(0000000000);
	c1 = new TCanvas("c1","",1360,768);
	TH1F* th1=new TH1F ("th1","",7,0,7);
    th1->SetMarkerStyle(20);
	th1->GetXaxis()->SetBinLabel(1,"600");
	th1->GetXaxis()->SetBinLabel(2,"700");
	th1->GetXaxis()->SetBinLabel(3,"800");
	th1->GetXaxis()->SetBinLabel(4,"900");
	th1->GetXaxis()->SetBinLabel(5,"1000");
	th1->GetXaxis()->SetBinLabel(6,"1200");
	th1->GetXaxis()->SetBinLabel(7,"1500");
	th1->GetXaxis()->SetLabelSize(0.06);
	th1->SetMarkerSize(3);
	th1->SetBinContent(1,1.0);
	th1->SetBinContent(2,1.2);
	th1->SetBinContent(3,1.4);
	th1->SetBinContent(4,1.5);
	th1->SetBinContent(5,1.6);
	th1->SetBinContent(6,1.7);
	th1->SetBinContent(7,1.8);
	th1->SetXTitle("M-{Z'}");
	TH1F* th2= (TH1F*)th1->Clone("Efficiency");
	th1->SetYTitle("Xsec");
	th2->SetYTitle("Efficiency");
	th1->SetXTitle("M-{Z'}");
	th1->Draw("P");
	c1->SaveAs("080401.png");
    //th2->SetTitle("Efficiency");
	th2->SetBinContent(1,0.5);
	th2->SetBinContent(2,0.6);
	th2->SetBinContent(3,0.7);
	th2->SetBinContent(4,0.8);
	th2->SetBinContent(5,0.5);
	th2->SetBinContent(6,0.6);
	th2->SetBinContent(7,0.9);
	th2->Draw("P");
	c1->SaveAs("080402.png");
}