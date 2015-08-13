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

TTree *tree;
TFile *f;
TCanvas* c1;

void setLeg(TLegend *leg){
leg->SetFillColor(18);
leg->SetFillStyle(0);
leg->SetTextSize(0.03);
leg->SetBorderSize(2);
}

void subJetParctice0811_605() {
	
  float  DRR[7]={0.2,0.3,0.4};
  TGraphAsymmErrors* TGrDR[3][13];
  TGraphAsymmErrors* TGrPt[3][13];
  TGraphAsymmErrors* TGrM[3][13];
  for (int DR=0;DR<3;DR++){
    c1 = new TCanvas("c1","",1360,768);
	string  masspoint[13]={"600","800","1000","1200","1400","1600","1800","2000","2500","3000","3500","4000","4500"};
	string  crabInf[13]={"150729_212416","150729_212459","150729_211555","150729_211640","150729_211727","150729_211727","150729_211855","150729_211940","150729_212023","150729_212110","150729_212159","150729_212245","150729_212331"};
    for (int massP=0;massP<13;massP++){
		TString endfix =Form("signal-%s",masspoint[massP].data());
		TH1F* th1=new TH1F("deltaR","deltaR",40,0,1);
		TH1F* th2=new TH1F("deltaRCut","deltaRCut",40,0,1);
		TH1F* th3,*th4;
		if(massP<5){
			double bins[7]={200,250,300,350,500,1000,2000};
			th3=new TH1F("Pt","Pt",6,bins);
		    th4=new TH1F("PtCut","PtCut",6,bins);
			
		}
		else{
			double bins[10]={200,300,400,500,700,1000,1300,1500,2000,2500};
			th3=new TH1F("Pt","Pt",9,bins);
		    th4=new TH1F("PtCut","PtCut",9,bins);
		}
		
		TH1F* th5=new TH1F("SDMass","SDMass",14,0,210);
		TH1F* th6=new TH1F("SDMassCut","SDMassCut",14,0,210);
		TH1F* th7,*th8;
		if(massP<5){
			double bins[7]={200,250,300,350,500,1000,2000};
			th7=new TH1F("P","P",6,bins);
		    th8=new TH1F("PCut","PCut",6,bins);
			
		}
		else{
		  double bins[11]={200,300,400,500,700,1000,1300,1500,2000,2500,3000};
			th7=new TH1F("P","P",10,bins);
		    th8=new TH1F("PCut","PCut",10,bins);
		}
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
				Float_t*  FATjetCISVV2 = data.GetPtrFloat("FATjetCISVV2");
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
				th7->Fill(FATjetP4_1->Mag());
				if(FATsubjet_1.DeltaR(FATsubjet_2)>DRR[DR] &&(FATsubjetSDCSV[0][0]<0.605|| FATsubjetSDCSV[0][1]<0.605))continue;
				if(FATsubjet_1.DeltaR(FATsubjet_2)<DRR[DR] && FATjetCISVV2[0]<0.605)continue;
				th2->Fill(FATsubjet_1.DeltaR(FATsubjet_2));
				th4->Fill(FATjetP4_1->Pt());
				th6->Fill(FATjetSDmass[0]);
				th8->Fill(FATjetP4_1->Mag());
			}
			
			
		}	
		
		th1->SetTitle(Form("deltaR,mass %s Gev",masspoint[massP].data()));
		th1->Draw();
		th2->Draw("same");
		//TH1F* th5=(TH1F*)th4->Clone("eff");
		//th5->Divide(th3);
		if(massP==0)c1->Print(Form("pdf/0807_deltaR_%0.2f_CSV605.pdf(",DRR[DR]));
		else if (massP==12)c1->Print(Form("pdf/0807_deltaR_%0.2f_CSV605.pdf)",DRR[DR]));
		else c1->Print(Form("pdf/0807_deltaR_%0.2f_CSV605.pdf",DRR[DR]));
		//th5->SetXTitle("Pt");
		//th5->SetTitle("efficiency");

	       
		TGraphAsymmErrors* g = new TGraphAsymmErrors(th2,th1);
		g->SetTitle(Form("deltaR eff %s",masspoint[massP].data()));
		g->Draw("AP");
		TGrDR[DR][massP]=new TGraphAsymmErrors(th2,th1);
		TGrDR[DR][massP]->SetTitle(Form("deltaR eff %s",masspoint[massP].data()));
		//TGrDR[DR][massP]->SetTitle(Form("deltaR eff %s",masspoint[massP].data()));
		if(massP==0)c1->Print(Form("pdf/0807_deltaR_eff_%0.2f_CSV605.pdf(",DRR[DR]));
		//else if (massP==12)c1->Print(Form("pdf/0807_deltaR_eff_%0.2f.pdf)",DRR[DR]));
		else c1->Print(Form("pdf/0807_deltaR_eff_%0.2f_CSV605.pdf",DRR[DR]));

		th3->Draw();
		th4->SetLineColor(2);
		th4->Draw("same");
		if(massP==0)c1->Print(Form("pdf/0807_Pt_%0.2f_CSV605.pdf(",DRR[DR]));
		else if (massP==12)c1->Print(Form("pdf/0807_Pt_%0.2f_CSV605.pdf)",DRR[DR]));
		else c1->Print(Form("pdf/0807_Pt_%0.2f_CSV605.pdf",DRR[DR]));

		g = new TGraphAsymmErrors(th4,th3);
		g->SetTitle(Form("Pt eff %s",masspoint[massP].data()));
		g->Draw("AP");
		TGrPt[DR][massP]= new TGraphAsymmErrors(th4,th3);
		TGrPt[DR][massP]->SetTitle(Form("Pt eff %s",masspoint[massP].data()));
		if(massP==0)c1->Print(Form("pdf/0807_Pt_eff_%0.2f_CSV605.pdf(",DRR[DR]));
		//else if (massP==12)c1->Print(Form("pdf/0807_Pt_eff_%0.2f.pdf)",DRR[DR]));
		else c1->Print(Form("pdf/0807_Pt_eff_%0.2f_CSV605.pdf",DRR[DR]));

		


		th5->Draw();
		th6->SetLineColor(2);
		th6->Draw("same");
		if(massP==0)c1->Print(Form("pdf/0807_SDMass_%0.2f_CSV605.pdf(",DRR[DR]));
		else if (massP==12)c1->Print(Form("pdf/0807_SDMass_%0.2f_CSV605.pdf)",DRR[DR]));
		else c1->Print(Form("pdf/0807_SDMass_%0.2f_CSV605.pdf",DRR[DR]));

		
		g = new TGraphAsymmErrors(th6,th5);
		g->SetTitle(Form("SDMass eff %s",masspoint[massP].data()));
		g->Draw("AP");
		if(massP==0)c1->Print(Form("pdf/0807_SDMass_eff_%0.2f_CSV605.pdf(",DRR[DR]));
		else if (massP==12)c1->Print(Form("pdf/0807_SDMass_eff_%0.2f_CSV605.pdf)",DRR[DR]));
		else c1->Print(Form("pdf/0807_SDMass_eff_%0.2f_CSV605.pdf",DRR[DR]));

		th7->Draw();
		th8->SetLineColor(2);
		th8->Draw("same");
		if(massP==0)c1->Print(Form("pdf/0807_M_%0.2f_CSV605.pdf(",DRR[DR]));
		else if (massP==12)c1->Print(Form("pdf/0807_M_%0.2f_CSV605.pdf)",DRR[DR]));
		else c1->Print(Form("pdf/0807_M_%0.2f_CSV605.pdf",DRR[DR]));

		g = new TGraphAsymmErrors(th8,th7);
		g->SetTitle(Form("Momentum eff %s",masspoint[massP].data()));
		g->Draw("AP");
		TGrM[DR][massP]= new TGraphAsymmErrors(th8,th7);
		TGrM[DR][massP]->SetTitle(Form("Momentum eff %s",masspoint[massP].data()));
		if(massP==0)c1->Print(Form("pdf/0807_M_eff_%0.2f_CSV605.pdf(",DRR[DR]));
		//else if (massP==12)c1->Print(Form("pdf/0807_Pt_eff_%0.2f.pdf)",DRR[DR]));
		else c1->Print(Form("pdf/0807_M_eff_%0.2f_CSV605.pdf",DRR[DR]));

		
    }	    
    double x1NDC = 0.6522;
    double y1NDC = 0.7835;
    double x2NDC = 0.9122;
    double y2NDC = 0.9860;
    
    TLegend* leg ;
    leg=new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
    setLeg(leg);
  
    
    TGrDR[DR][0]->SetLineColor(1);
    TGrDR[DR][2]->SetLineColor(2);
    TGrDR[DR][4]->SetLineColor(3);
    TGrDR[DR][0]->SetMarkerStyle(20);
    TGrDR[DR][2]->SetMarkerStyle(21);
    TGrDR[DR][4]->SetMarkerStyle(22);
    TGrDR[DR][0]->Draw("AP");
    TGrDR[DR][2]->Draw("P,same");
    TGrDR[DR][4]->Draw("P,same");
    leg->AddEntry(TGrDR[DR][0],"600");
    leg->AddEntry(TGrDR[DR][2],"1000");
    leg->AddEntry(TGrDR[DR][4],"1400");
    leg->Draw("same");
    c1->Print(Form("pdf/0807_deltaR_eff_%0.2f_CSV605.pdf",DRR[DR]));


    TGrDR[DR][5]->SetLineColor(1);
    TGrDR[DR][7]->SetLineColor(2);
    TGrDR[DR][9]->SetLineColor(3);
    TGrDR[DR][12]->SetLineColor(4);
    TGrDR[DR][5]->SetMarkerStyle(20);
    TGrDR[DR][7]->SetMarkerStyle(21);
    TGrDR[DR][9]->SetMarkerStyle(22);
    TGrDR[DR][12]->SetMarkerStyle(23);
    TGrDR[DR][5]->Draw("AP");
    TGrDR[DR][7]->Draw("P,same");
    TGrDR[DR][9]->Draw("P,same");
    TGrDR[DR][12]->Draw("P,same");
    leg->Clear();
    leg->AddEntry(TGrDR[DR][5],"1600");
    leg->AddEntry(TGrDR[DR][7],"2000");
    leg->AddEntry(TGrDR[DR][9],"3000");
    leg->AddEntry(TGrDR[DR][12],"4500");
    leg->Draw("same");
    c1->Print(Form("pdf/0807_deltaR_eff_%0.2f_CSV605.pdf)",DRR[DR]));

    TGrPt[DR][0]->SetLineColor(1);
    TGrPt[DR][2]->SetLineColor(2);
    TGrPt[DR][4]->SetLineColor(3);
    TGrPt[DR][0]->SetMarkerStyle(20);
    TGrPt[DR][2]->SetMarkerStyle(21);
    TGrPt[DR][4]->SetMarkerStyle(22);
    TGrPt[DR][0]->Draw("AP");
    TGrPt[DR][2]->Draw("P,same");
    TGrPt[DR][4]->Draw("P,same");
    leg->Clear();
    leg->AddEntry(TGrPt[DR][0],"600");
    leg->AddEntry(TGrPt[DR][2],"1000");
    leg->AddEntry(TGrPt[DR][4],"1400");
    leg->Draw("same");
    c1->Print(Form("pdf/0807_Pt_eff_%0.2f_CSV605.pdf",DRR[DR]));

    TGrPt[DR][5]->SetLineColor(1);
    TGrPt[DR][7]->SetLineColor(2);
    TGrPt[DR][9]->SetLineColor(3);
    TGrPt[DR][12]->SetLineColor(4);
    TGrPt[DR][5]->SetMarkerStyle(20);
    TGrPt[DR][7]->SetMarkerStyle(21);
    TGrPt[DR][9]->SetMarkerStyle(22);
    TGrPt[DR][12]->SetMarkerStyle(23);
    TGrPt[DR][5]->Draw("AP");
    TGrPt[DR][7]->Draw("P,same");
    TGrPt[DR][9]->Draw("P,same");
    TGrPt[DR][12]->Draw("P,same");
    leg->Clear();
    leg->AddEntry(TGrPt[DR][5],"1600");
    leg->AddEntry(TGrPt[DR][7],"2000");
    leg->AddEntry(TGrPt[DR][9],"3000");
    leg->AddEntry(TGrPt[DR][12],"4500");
    leg->Draw("same");
    c1->Print(Form("pdf/0807_Pt_eff_%0.2f_CSV605.pdf)",DRR[DR]));

    TGrM[DR][0]->SetLineColor(1);
    TGrM[DR][2]->SetLineColor(2);
    TGrM[DR][4]->SetLineColor(3);
    TGrM[DR][0]->SetMarkerStyle(20);
    TGrM[DR][2]->SetMarkerStyle(21);
    TGrM[DR][4]->SetMarkerStyle(22);
    TGrM[DR][0]->Draw("AP");
    TGrM[DR][2]->Draw("P,same");
    TGrM[DR][4]->Draw("P,same");
    leg->Clear();
    leg->AddEntry(TGrM[DR][0],"600");
    leg->AddEntry(TGrM[DR][2],"1000");
    leg->AddEntry(TGrM[DR][4],"1400");
    leg->Draw("same");
    c1->Print(Form("pdf/0807_M_eff_%0.2f_CSV605.pdf",DRR[DR]));

    TGrM[DR][5]->SetLineColor(1);
    TGrM[DR][7]->SetLineColor(2);
    TGrM[DR][9]->SetLineColor(3);
    TGrM[DR][12]->SetLineColor(4);
    TGrM[DR][5]->SetMarkerStyle(20);
    TGrM[DR][7]->SetMarkerStyle(21);
    TGrM[DR][9]->SetMarkerStyle(22);
    TGrM[DR][12]->SetMarkerStyle(23);
    TGrM[DR][5]->Draw("AP");
    TGrM[DR][7]->Draw("P,same");
    TGrM[DR][9]->Draw("P,same");
    TGrM[DR][12]->Draw("P,same");
    leg->Clear();
    leg->AddEntry(TGrM[DR][5],"1600");
    leg->AddEntry(TGrM[DR][7],"2000");
    leg->AddEntry(TGrM[DR][9],"3000");
    leg->AddEntry(TGrM[DR][12],"4500");
    leg->Draw("same");
    c1->Print(Form("pdf/0807_M_eff_%0.2f_CSV605.pdf)",DRR[DR]));



  }
  double x1NDC = 0.6522;
  double y1NDC = 0.7835;
  double x2NDC = 0.9122;
  double y2NDC = 0.9860;
  
  TLegend* leg ;
  leg=new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
  setLeg(leg);
  
  for (int massP=0;massP<13;massP++){
    TGrDR[0][massP]->SetLineColor(2);
    TGrDR[1][massP]->SetLineColor(3);
    TGrDR[2][massP]->SetLineColor(4);
    TGrDR[0][massP]->SetMarkerStyle(20);
    TGrDR[1][massP]->SetMarkerStyle(21);
    TGrDR[2][massP]->SetMarkerStyle(22);
    TGrDR[0][massP]->Draw("AP");
    TGrDR[1][massP]->Draw("P,same");
    TGrDR[2][massP]->Draw("P,same");
    leg->Clear();
    leg->AddEntry(TGrDR[0][massP],"0.2");
    leg->AddEntry(TGrDR[1][massP],"0.3");
    leg->AddEntry(TGrDR[2][massP],"0.4");
    leg->Draw("same");

    if(massP ==0 )c1->Print("pdf/0807_deltaR_same_CSV605.pdf(");
    else if (massP ==12)c1->Print("pdf/0807_deltaR_same_CSV605.pdf)");
    else c1->Print("pdf/0807_deltaR_same_CSV605.pdf");


  }
}
