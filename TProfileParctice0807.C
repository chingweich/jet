#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include<iostream>
#include "TLorentzVector.h"
#include <TFile.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "untuplizer.h"
#include <vector>
#include <string>
#include <math.h>
#include <TClonesArray.h>
#include "TGraphAsymmErrors.h"
#include <TLegend.h>
#include "TProfile.h"


TTree *tree;
TFile *f;
TCanvas* c1;

void setLeg(TLegend *leg){
leg->SetFillColor(18);
leg->SetFillStyle(0);
leg->SetTextSize(0.03);
leg->SetBorderSize(2);
}

void TProfileParctice0807() {
	

    c1 = new TCanvas("c1","",1360,768);
	string  masspoint[13]={"600","800","1000","1200","1400","1600","1800","2000","2500","3000","3500","4000","4500"};

    for (int massP=0;massP<13;massP++){
		TString endfix =Form("signal-%s",masspoint[massP].data());
		TH1F* th1=new TH1F("deltaR","deltaR",40,0,1);
		TH1F* th2=new TH1F("deltaRCut","deltaRCut",40,0,1);
		TH1F* th3,*th4;
		TProfile* hprof;
		
		
		if(massP<5){
			double bins[7]={200,250,300,350,500,1000,2000};
			th3=new TH1F("Pt","Pt",6,bins);
		    th4=new TH1F("PtCut","PtCut",6,bins);
			hprof  = new TProfile("hprof","Profile of deltaR versus pt",6,bins,0,1);
		}
		else{
			double bins[10]={200,300,400,500,700,1000,1300,1500,2000,2500};
			th3=new TH1F("Pt","Pt",9,bins);
		    th4=new TH1F("PtCut","PtCut",9,bins);
			hprof  = new TProfile("hprof","Profile of deltaR versus pt",9,bins,0,1);
		}
		
		TH1F* th5=new TH1F("SDMass","SDMass",14,0,210);
		TH1F* th6=new TH1F("SDMassCut","SDMassCut",14,0,210);
		th2->SetLineColor(2);
	
		for(int w=1;w<2;w++){
		  f = TFile::Open(Form("/data2/syu/13TeV/ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-%s_13TeV-madgraph.root",masspoint[massP].data()));
		  if (!f || !f->IsOpen())continue;
		  TDirectory * dir = (TDirectory*)f->Get(Form("/data2/syu/13TeV/ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-%s_13TeV-madgraph.root:/tree",masspoint[massP].data()));
		  dir->GetObject("treeMaker",tree);

			

			cout<<w<<endl;
			TreeReader data(tree);
			//data.Print();
			Long64_t nentries = data.GetEntriesFast();
			
			
			
			for (Long64_t jentry=0; jentry<nentries;jentry++) {
				data.GetEntry(jentry);
				TClonesArray* FATjetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
				Float_t*  FATjetSDmass = data.GetPtrFloat("FATjetSDmass");
				Float_t*  FATjetCSV = data.GetPtrFloat("FATjetCSV");
				Int_t* FATnSubSDJet=data.GetPtrInt("FATnSubSDJet");
				Int_t FATnJet=data.GetInt("FATnJet");
				
				
				if(FATnJet==0)continue;
				TLorentzVector* FATjetP4_1 = (TLorentzVector*)FATjetP4->At(0);
				
				if(FATjetP4_1->Pt()<200)continue;
				//if(FATjetSDmass[0]<100||FATjetSDmass[0]>150)continue;
				if(FATnSubSDJet[0]<2)continue;
				
				TLorentzVector  FATsubjet_1,FATsubjet_2;
				
				vector<float>   *FATsubjetSDPx =  data.GetPtrVectorFloat("FATsubjetSDPx", FATnSubSDJet[0]);
				vector<float>   *FATsubjetSDPy =  data.GetPtrVectorFloat("FATsubjetSDPy", FATnSubSDJet[0]);
				vector<float>   *FATsubjetSDPz =  data.GetPtrVectorFloat("FATsubjetSDPz", FATnSubSDJet[0]);
				vector<float>   *FATsubjetSDCE =  data.GetPtrVectorFloat("FATsubjetSDCE", FATnSubSDJet[0]);
				vector<float>   *FATsubjetSDCSV =  data.GetPtrVectorFloat("FATsubjetSDCSV", FATnSubSDJet[0]);
				
				FATsubjet_1.SetPxPyPzE(FATsubjetSDPx[0][0],FATsubjetSDPy[0][0],FATsubjetSDPz[0][0],FATsubjetSDCSV[0][0]);
	            FATsubjet_2.SetPxPyPzE(FATsubjetSDPx[0][1],FATsubjetSDPy[0][1],FATsubjetSDPz[0][1],FATsubjetSDCSV[0][1]);
	            
				th1->Fill(FATsubjet_1.DeltaR(FATsubjet_2));
				th3->Fill(FATjetP4_1->Pt());
				th5->Fill(FATjetSDmass[0]);
				hprof->Fill(FATjetP4_1->Pt(),FATsubjet_1.DeltaR(FATsubjet_2));
				//if(FATsubjet_1.DeltaR(FATsubjet_2)>DRR[DR] &&(FATsubjetSDCSV[0][0]<0.432|| FATsubjetSDCSV[0][1]<0.432))continue;
				//if(FATsubjet_1.DeltaR(FATsubjet_2)<DRR[DR] && FATjetCSV[0]<0.432)continue;
				th2->Fill(FATsubjet_1.DeltaR(FATsubjet_2));
				th4->Fill(FATjetP4_1->Pt());
				th6->Fill(FATjetSDmass[0]);
			}
			
			
		}	
		
		hprof->Draw();
		if(massP==0)c1->Print("tp/tp.pdf(");
		else if (massP==12)c1->Print("tp/tp.pdf)");
		else c1->Print("tp/tp.pdf");
		
    }	    

  }

  
