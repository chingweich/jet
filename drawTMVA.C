#include <string>
#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TSystem.h>
#include <TH1.h>
#include "TAttFill.h"
#include "TLine.h"
#include "TAxis.h"
#include "TStyle.h"
#include "TGaxis.h"
#include <TPad.h>
#include "TH2.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"

using namespace std;

TFile* f1;
TCanvas* c1;
double x1NDC = 0.6522;
double y1NDC = 0.7835;
double x2NDC = 0.9122;
double y2NDC = 0.9860;





TGraphAsymmErrors* getTGEff(TFile* tf1,string s1,string s2){
	TH1F* th1,*th2;
	th1=(TH1F*)tf1->FindObjectAny(s1.data());
	th2=(TH1F*)tf1->FindObjectAny(s2.data());

	TGraphAsymmErrors* temp=new TGraphAsymmErrors(th2,th1);
	return temp;
}

void drawEff(TGraphAsymmErrors *th2[],string s1,string s2,string s5,int drawOption,bool show=0){
	
	
	int color[5]={30,38,41,46,28};
	
	for(int i=0;i<2;i++){
		
		th2[i]->SetLineColor(color[i+1]);
	}
	
	th2[0]->SetTitle(s5.data());
	th2[0]->Draw("AP");
	th2[1]->Draw("P,same");
	
	TLegend* leg ;
    leg=new TLegend(0.8,0.85,x2NDC,y2NDC);
	leg->SetFillColor(18);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(2);
    leg->AddEntry(th2[0],s1.data());
	leg->AddEntry(th2[1],s2.data());
	
	leg->Draw("same");
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA.pdf)");
	else c1->Print ("TMVAPdf/TMVA.pdf");
}

void drawEff(TGraphAsymmErrors *th2[],string s1,string s2,string s3,string s4,string s5,int drawOption,bool show=0){
	
	
	int color[5]={30,38,41,46,28};
	
	for(int i=0;i<4;i++){
		
		th2[i]->SetLineColor(color[i+1]);
	}
	
	th2[0]->SetTitle(s5.data());
	th2[0]->Draw("AP");
	th2[1]->Draw("P,same");
	th2[2]->Draw("P,same");
	th2[3]->Draw("P,same");
	TLegend* leg ;
    leg=new TLegend(0.8,0.85,x2NDC,y2NDC);
	leg->SetFillColor(18);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(2);
    leg->AddEntry(th2[0],s1.data());
	leg->AddEntry(th2[1],s2.data());
	leg->AddEntry(th2[2],s3.data());
	leg->AddEntry(th2[3],s4.data());
	leg->Draw("same");
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA.pdf)");
	else c1->Print ("TMVAPdf/TMVA.pdf");
}


void drawB(TH1F *th1[],string s1,string s2,string s3,string s4,string s5,string s6,int drawOption){
	int color[5]={30,38,41,46,28};
	float temp=0;
	for(int i=0;i<5;i++){
		th1[i]->Scale(1/th1[i]->Integral());
		if(th1[i]->GetMaximum()>temp)temp=th1[i]->GetMaximum();
	}
	for(int i=0;i<5;i++){
		th1[i]->SetMaximum(temp*1.2);
		th1[i]->GetXaxis()->SetRangeUser(-0.6,+0.8);
		th1[i]->SetLineColor(color[i]);
	}
	
	th1[0]->SetTitle(s6.data());
	th1[0]->Draw();
	th1[1]->Draw("same");
	th1[2]->Draw("same");
	th1[3]->Draw("same");
	th1[4]->Draw("same");
	TLegend* leg ;
    leg=new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
	leg->SetFillColor(18);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(2);
    leg->AddEntry(th1[0],s1.data());
	leg->AddEntry(th1[1],s2.data());
	leg->AddEntry(th1[2],s3.data());
	leg->AddEntry(th1[3],s4.data());
	leg->AddEntry(th1[4],s5.data());
	leg->Draw("same");
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA.pdf)");
	else c1->Print ("TMVAPdf/TMVA.pdf");
}


TH1F* drawE(TH1F* th1,TH1F* th2,bool show=0){
	int nbins=200;
	TH1F* temp=new TH1F("ROC","ROC",nbins,0,1);
	int getNbin=th1->GetNbinsX();
	for(int i=nbins;i>0;i--){
		float temp2=(i/200.0),temp3=0;
		
		for(int j=getNbin;j>0;j--){
			//cout<<th1->Integral(j,getNbin)/th1->Integral()<<endl;
			if( (th1->Integral(j,getNbin)/th1->Integral())>=temp2){
				temp3=th2->Integral(1,j)/th2->Integral();
				if(show)cout<<temp2<<",BDT="<<th1->GetBinCenter(j)<<endl;
				//temp3=j;
				//cout<<"?"<<endl;
				break;
			}
		}
		
		temp->SetBinContent(i,temp3);
	}
	return temp;
}

void drawEE(TH1F *th1[],string s1,string s2,string s3,string s4,string s5,int drawOption,bool show=0){
	
	TH1F* th2[4];
	for(int i=0;i<4;i++){
		if (i==1&& show)th2[i]=drawE(th1[i+1],th1[0],1);
		else th2[i]=drawE(th1[i+1],th1[0]);
	}
	//cout<<"yes"<<endl;
	int color[5]={30,38,41,46,28};
	
	for(int i=0;i<4;i++){
		
		th2[i]->SetLineColor(color[i+1]);
	}
	
	th2[0]->SetTitle(s5.data());
	th2[0]->Draw();
	th2[1]->Draw("same");
	th2[2]->Draw("same");
	th2[3]->Draw("same");
	TLegend* leg ;
    leg=new TLegend(0.2,0.2,0.3,0.4);
	leg->SetFillColor(18);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(2);
    leg->AddEntry(th2[0],s1.data());
	leg->AddEntry(th2[1],s2.data());
	leg->AddEntry(th2[2],s3.data());
	leg->AddEntry(th2[3],s4.data());
	leg->Draw("same");
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA.pdf)");
	else c1->Print ("TMVAPdf/TMVA.pdf");
}

void drawTMVA(){
	c1 = new TCanvas("c1","",1360,768);
	gStyle->SetOptStat(0000000000);
	TFile * TF[5];
	TF[0]=TFile::Open("treeV4DY/DY.root");
	TF[1]=TFile::Open("treeV4DY/signal-600.root");
	TF[2]=TFile::Open("treeV4DY/signal-800.root");
	TF[3]=TFile::Open("treeV4DY/signal-1000.root");
	TF[4]=TFile::Open("treeV4DY/signal-1200.root");
	TH1F* TH1[5];
	for(int i=0;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"DY","600","800","1000","1200","DY",1);
	drawEE(TH1,"600","800","1000","1200","DY",3,1);
	for(int i=1;i<5;i++)TF[i]->Close();
	
	TF[1]=TFile::Open("treeV4DY/signal-1600.root");
	TF[2]=TFile::Open("treeV4DY/signal-2000.root");
	TF[3]=TFile::Open("treeV4DY/signal-3000.root");
	TF[4]=TFile::Open("treeV4DY/signal-4500.root");
	for(int i=1;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"DY","1600","2000","3000","4500","DY",3);
	drawEE(TH1,"1600","2000","3000","4500","DY",3);
	for(int i=0;i<5;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("treeV4TT/TT.root");
	TF[1]=TFile::Open("treeV4TT/signal-600.root");
	TF[2]=TFile::Open("treeV4TT/signal-800.root");
	TF[3]=TFile::Open("treeV4TT/signal-1000.root");
	TF[4]=TFile::Open("treeV4TT/signal-1200.root");
	for(int i=0;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"TT","600","800","1000","1200","TT",3);
	drawEE(TH1,"600","800","1000","1200","TT",3);
	for(int i=1;i<5;i++)TF[i]->Close();
	
	TF[1]=TFile::Open("treeV4TT/signal-1600.root");
	TF[2]=TFile::Open("treeV4TT/signal-2000.root");
	TF[3]=TFile::Open("treeV4TT/signal-3000.root");
	TF[4]=TFile::Open("treeV4TT/signal-4500.root");
	for(int i=1;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"TT","1600","2000","3000","4500","TT",3);
	drawEE(TH1,"1600","2000","3000","4500","TT",3);
	for(int i=0;i<5;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("treeV4DT/DT.root");
	TF[1]=TFile::Open("treeV4DT/signal-600.root");
	TF[2]=TFile::Open("treeV4DT/signal-800.root");
	TF[3]=TFile::Open("treeV4DT/signal-1000.root");
	TF[4]=TFile::Open("treeV4DT/signal-1200.root");
	for(int i=0;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"DY+TT","600","800","1000","1200","DY+TT",3);
	drawEE(TH1,"600","800","1000","1200","DY+TT",3);
	for(int i=1;i<5;i++)TF[i]->Close();
	
	TF[1]=TFile::Open("treeV4DT/signal-1600.root");
	TF[2]=TFile::Open("treeV4DT/signal-2000.root");
	TF[3]=TFile::Open("treeV4DT/signal-3000.root");
	TF[4]=TFile::Open("treeV4DT/signal-4500.root");
	for(int i=1;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"DY+TT","1600","2000","3000","4500","DY+TT",3);
	drawEE(TH1,"1600","2000","3000","4500","DY+TT",3);
	//TH1F * test=drawE(TH1[1],TH1[0]);
	//test->Draw();
	//c1->Print ("TMVAPdf/TMVA.pdf)");
	for(int i=0;i<5;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("BDTEff/signal-600.root");
	TF[1]=TFile::Open("BDTEff/signal-800.root");
	TF[2]=TFile::Open("BDTEff/signal-1000.root");
	TF[3]=TFile::Open("BDTEff/signal-1200.root");
	TGraphAsymmErrors* TG[4];
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"deltaR","deltaRCut");
	drawEff(TG,"600","800","1000","1200","delta Eff",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtCut");
	drawEff(TG,"600","800","1000","1200","Pt Eff",3);
	for(int i=0;i<4;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("BDTEff/signal-1600.root");
	TF[1]=TFile::Open("BDTEff/signal-2000.root");
	TF[2]=TFile::Open("BDTEff/signal-3000.root");
	TF[3]=TFile::Open("BDTEff/signal-4500.root");
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"deltaR","deltaRCut");
	drawEff(TG,"1600","2000","3000","4500","delta Eff",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtCut");
	drawEff(TG,"1600","2000","3000","4500","Pt Eff",3);
	for(int i=0;i<4;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("BDTEff/TT.root");
	TF[1]=TFile::Open("BDTEff/DY.root");
	for (int i=0;i<2;i++)TG[i]=getTGEff(TF[i],"deltaR","deltaRCut");
	drawEff(TG,"TT","DY","delta Eff",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtCut");
	drawEff(TG,"TT","DY","Pt Eff",2);
	for(int i=0;i<2;i++)TF[i]->Close();
}


