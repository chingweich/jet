#include <TLegend.h>
#include <vector>
#include <string>
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
//#include "untuplizer.h"
#include "TAxis.h"

using namespace std;

TCanvas* c1;
//TTree *tree;
TFile *f;

void smalltask0805(){
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
	th1->SetBinContent(1,292.13);
	th1->SetBinContent(2,242.33);
	th1->SetBinContent(3,181.05);
	th1->SetBinContent(4,130.54);
	th1->SetBinContent(5,94.104);
	th1->SetBinContent(6,49.366);
	th1->SetBinContent(7,20.386);
	th1->SetXTitle("M-{Z'}");
	
	th1->SetYTitle("Xsec(fb)");
	
	th1->SetXTitle("M_{Z'}");
	th1->Draw("P");
	TH1F* th2= (TH1F*)th1->Clone("Efficiency");
	c1->SaveAs("080501.png");
	th2->SetYTitle("Efficiency");
    //th2->SetTitle("Efficiency");
	
	th2->SetBinContent(1,0);
	th2->SetBinContent(2,0);
	th2->SetBinContent(3,0);
	th2->SetBinContent(4,0);
	th2->SetBinContent(5,0);
	th2->SetBinContent(6,0);
	th2->SetBinContent(7,0);
	
	string massPoint[7] = {"600","700","800","900","1000","1200","1500"};
	double c[7];
	for (int massP=0;massP<7;massP++){
		
		f= TFile::Open(Form("SignalFiles_0804-runallAnalysis/runallAnalysis-NCUGlobalTuples_M%sGeV.root",massPoint[massP].data()));
		TDirectory * dir = (TDirectory*)f->Get(Form("SignalFiles_0804-runallAnalysis/runallAnalysis-NCUGlobalTuples_M%sGeV.root:/CutFlowAndEachCut",massPoint[massP].data()));
		TH1F* th1=(TH1F*) dir->FindObjectAny("h_cutflow_0");
		TH1F* th2=(TH1F*)f->FindObjectAny("nEvents_weight");
		double a=th2->Integral(),b=0;
		bool isB=0;
		for(int i=th1->GetNbinsX();i>0;i--){
			//cout<<"cont="<<th1->GetBinContent(i)<<endl;
			if(th1->GetBinContent(i)!=0 && isB==0){
				
				b=th1->GetBinContent(i);
				isB=1;
			}
			
		}
		cout<<"a="<<a<<",b="<<b<<endl;
		c[massP]=b/a;
		
	}
	
	for (int i=0;i<7;i++)th2->SetBinContent(i+1,c[i]);
	th2->Draw("P");
	c1->SaveAs("080502.png");
}