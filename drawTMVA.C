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

void drawSix(TFile *tf1,TFile *tf2,string s1,string s2,int drawOption){
    TH1F* th1[3],*th2[3];
	th1[0]=(TH1F*)tf1->FindObjectAny(Form("%sCut",s1.data()));
	th1[1]=(TH1F*)tf1->FindObjectAny(Form("%sFat",s1.data()));
	th1[2]=(TH1F*)tf1->FindObjectAny(Form("%sSub",s1.data()));
	th2[0]=(TH1F*)tf2->FindObjectAny(Form("%sCut",s1.data()));
	th2[1]=(TH1F*)tf2->FindObjectAny(Form("%sFat",s1.data()));
	th2[2]=(TH1F*)tf2->FindObjectAny(Form("%sSub",s1.data()));
	for(int i=0;i<3;i++){
		//th1[i]->SetLineColor(2);
		//th2[i]->SetLineColor(4);
		th1[i]->Scale(1/th1[i]->Integral());
		th2[i]->Scale(1/th2[i]->Integral());
	}
	th1[0]->SetLineColor(1);
	th1[1]->SetLineColor(2);
	th1[2]->SetLineColor(4);
	th2[0]->SetLineColor(6);
	th2[1]->SetLineColor(34);
	th2[2]->SetLineColor(kOrange);
	
	float temp=0;
	for(int i=0;i<3;i++){
		
		if(th1[i]->GetMaximum()>temp)temp=th1[i]->GetMaximum();
		if(th2[i]->GetMaximum()>temp)temp=th2[i]->GetMaximum();
	}
	

	th1[0]->SetTitle(s1.data());
	th1[0]->SetXTitle(s1.data());
	th1[0]->SetYTitle("normalized to 1");
	th1[0]->SetMaximum(temp*1.1);
	th1[0]->Draw();
	th1[1]->Draw("same");
	th1[2]->Draw("same");
	th2[1]->Draw("same");
	th2[2]->Draw("same");
	th2[0]->Draw("same");
	
	TLegend* leg ;
	leg=new TLegend(0.7,0.75,x2NDC,y2NDC);
	leg->SetFillColor(18);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(2);
	leg->AddEntry(th1[0],Form("%s-BDT>0",s2.data()));
	leg->AddEntry(th1[1],Form("%s-FatjetCSV>0.605",s2.data()));
	leg->AddEntry(th1[2],Form("%s-subjetCSV>0.605",s2.data()));
	leg->AddEntry(th2[0],"DY-BDT>0");
	leg->AddEntry(th2[1],"DY-FatjetCSV>0.605");
	leg->AddEntry(th2[2],"DY-subjetCSV>0.605");
	leg->Draw("same");
	
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA2.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA2.pdf)");
	else c1->Print ("TMVAPdf/TMVA2.pdf");
}

void drawSixEff(TFile *tf1,TFile *tf2,string s1,string s2,int drawOption){
    TGraphAsymmErrors* th1[3],*th2[3];
	th1[0]=getTGEff(tf1,s1,Form("%sCut",s1.data()));
	th1[1]=getTGEff(tf1,s1,Form("%sFat",s1.data()));
	th1[2]=getTGEff(tf1,s1,Form("%sSub",s1.data()));
	th2[0]=getTGEff(tf2,s1,Form("%sCut",s1.data()));
	th2[1]=getTGEff(tf2,s1,Form("%sFat",s1.data()));
	th2[2]=getTGEff(tf2,s1,Form("%sSub",s1.data()));
	
	
	
	th1[0]->SetLineColor(1);
	th1[1]->SetLineColor(2);
	th1[2]->SetLineColor(4);
	th2[0]->SetLineColor(6);
	th2[1]->SetLineColor(34);
	th2[2]->SetLineColor(kOrange);
	
	
	
	
	th1[0]->SetMarkerStyle(20);
	th2[0]->SetMarkerStyle(20);
	th1[1]->SetMarkerStyle(21);
	th2[1]->SetMarkerStyle(24);
	th1[2]->SetMarkerStyle(25);
	th2[2]->SetMarkerStyle(26);
	
	th1[0]->SetMarkerSize(1.2);
	th1[2]->SetMarkerSize(1.2);
	th1[1]->SetMarkerSize(1.2);
	th2[0]->SetMarkerSize(1.2);
	th2[2]->SetMarkerSize(1.2);
	th2[1]->SetMarkerSize(1.2);
	
	th2[0]->SetTitle(s1.data());
	th2[0]->GetXaxis()->SetTitle(s1.data());
	th2[0]->GetYaxis()->SetTitle("efficiency");
	th2[0]->SetMaximum(1.1);
	th2[0]->SetMinimum(0);
	
	th2[0]->Draw("AP");
	th1[1]->Draw("P,same");
	th1[2]->Draw("P,same");
	th2[1]->Draw("P,same");
	th2[2]->Draw("P,same");
	th1[0]->Draw("P,same");
	
	TLegend* leg ;
	leg=new TLegend(0.7,0.75,x2NDC,y2NDC);
	leg->SetFillColor(18);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(2);
	leg->AddEntry(th1[0],Form("%s-BDT>0",s2.data()));
	leg->AddEntry(th1[1],Form("%s-FatjetCSV>0.605",s2.data()));
	leg->AddEntry(th1[2],Form("%s-subjetCSV>0.605",s2.data()));
	leg->AddEntry(th2[0],"DY-BDT>0");
	leg->AddEntry(th2[1],"DY-FatjetCSV>0.605");
	leg->AddEntry(th2[2],"DY-subjetCSV>0.605");
	leg->Draw("same");
	
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA2.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA2.pdf)");
	else c1->Print ("TMVAPdf/TMVA2.pdf");
}

void draw2D(TFile *tf1,string s1,int drawOption){
	TH2F* th1;
	th1=(TH2F*)tf1->FindObjectAny("2D");
	th1->SetTitle(s1.data());
	th1->SetXTitle("deltaR");
	th1->SetYTitle("Pt");
	th1->GetXaxis()->SetLabelSize(0.045);
	th1->GetYaxis()->SetLabelSize(0.045);
	th1->Draw("colz");
	
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA2D.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA2D.pdf)");
	else c1->Print ("TMVAPdf/TMVA2D.pdf");
	
	
}

//draw TG on same canvas
void drawEff(TGraphAsymmErrors *th2,string s1,string s5,int drawOption,bool show=0){
	
	
	
		
	th2->SetLineColor(42);
	
	th2->SetTitle(s5.data());
	th2->GetXaxis()->SetLabelSize(0.045);
	th2->GetYaxis()->SetLabelSize(0.045);
	th2->Draw("AP");

	
	TLegend* leg ;
    leg=new TLegend(0.8,0.85,x2NDC,y2NDC);
	leg->SetFillColor(18);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(2);
    leg->AddEntry(th2,s1.data());

	
	leg->Draw("same");
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA.pdf)");
	else c1->Print ("TMVAPdf/TMVA.pdf");
}

void drawEff(TGraphAsymmErrors *th2[],string s1,string s2,string s5,int drawOption,bool show=0){
	
	
	int color[5]={30,38,41,46,28};
	
	for(int i=0;i<2;i++){
		
		th2[i]->SetLineColor(color[i+1]);
	}
	
	th2[0]->SetTitle(s5.data());
	th2[0]->GetXaxis()->SetLabelSize(0.045);
	th2[0]->GetYaxis()->SetLabelSize(0.045);
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
	
	th2[3]->SetTitle(s5.data());
	th2[3]->SetMaximum(1.1);
	th2[3]->GetXaxis()->SetLabelSize(0.045);
	th2[3]->GetYaxis()->SetLabelSize(0.045);
	th2[3]->Draw("AP");
	th2[1]->Draw("P,same");
	th2[2]->Draw("P,same");
	th2[0]->Draw("P,same");
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

//draw BDt on same canvas
void drawB(TH1F *th1[],string s1,string s2,string s3,string s4,string s5,string s6,int drawOption,string s7="",string s8=""){
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
	th1[0]->SetTitleSize(0.04);
	th1[0]->SetXTitle(s7.data());
	th1[0]->SetYTitle(s8.data());
	th1[0]->GetXaxis()->SetLabelSize(0.045);
	th1[0]->GetYaxis()->SetLabelSize(0.045);
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

void drawB(TH1F *th1[],string s1,string s2,string s3,string s4,string s6,int drawOption,double upRange=1000,bool log=0){
	int color[5]={30,38,41,46,28};
	float temp=0;
	for(int i=0;i<4;i++){
		th1[i]->Scale(1/th1[i]->Integral());
		if(th1[i]->GetMaximum()>temp)temp=th1[i]->GetMaximum();
	}
	for(int i=0;i<4;i++){
		th1[i]->SetMaximum(temp*1.2);
		th1[i]->GetXaxis()->SetRangeUser(200,upRange);
		th1[i]->SetLineColor(color[i]);
	}
	
	c1->SetLogy(log);
	th1[0]->SetTitle(s6.data());
	th1[0]->SetYTitle("normalize to 1");
	th1[0]->GetXaxis()->SetLabelSize(0.045);
	th1[0]->GetYaxis()->SetLabelSize(0.045);
	th1[0]->Draw();
	th1[1]->Draw("same");
	th1[2]->Draw("same");
	th1[3]->Draw("same");
	
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
	
	leg->Draw("same");
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA.pdf)");
	else c1->Print ("TMVAPdf/TMVA.pdf");
	c1->SetLogy(0);
}

void drawBS(TH1F *th1[],string s1,string s2,string s3,string s4,string s5,string s6,int drawOption,string s7="",string s8=""){
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
	th1[0]->SetTitleSize(0.04);
	th1[0]->SetXTitle(s7.data());
	th1[0]->SetYTitle(s8.data());
	th1[0]->GetXaxis()->SetLabelSize(0.045);
	th1[0]->GetYaxis()->SetLabelSize(0.045);
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
	
	leg->Draw("same");
	if(drawOption==1)c1->Print ("TMVAPdf/TMVAS.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVAS.pdf)");
	else c1->Print ("TMVAPdf/TMVAS.pdf");
	c1->SetLogy(0);
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

void drawEES(TH1F *th1[],string s1,string s2,string s3,string s4,string s5,int drawOption,bool show=0){
	
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
	th2[0]->GetXaxis()->SetLabelSize(0.045);
	th2[0]->GetYaxis()->SetLabelSize(0.045);
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
	if(drawOption==1)c1->Print ("TMVAPdf/TMVAS.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVAS.pdf)");
	else c1->Print ("TMVAPdf/TMVAS.pdf");
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
	th2[0]->GetXaxis()->SetLabelSize(0.045);
	th2[0]->GetYaxis()->SetLabelSize(0.045);
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

void drawB(TH1F *th1,string s1,string s5,int drawOption,bool show=0){
	
	
	
		//th1->SetMaximum(temp*1.2);
		
		th1->SetLineColor(42);
	
	
	th1->SetTitle(s5.data());
	th1->GetXaxis()->SetLabelSize(0.045);
	th1->GetYaxis()->SetLabelSize(0.045);
	th1->Draw();
	
	TLegend* leg ;
    leg=new TLegend(x1NDC,y1NDC,x2NDC,y2NDC);
	leg->SetFillColor(18);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.03);
    leg->SetBorderSize(2);
    leg->AddEntry(th1,s1.data());
	
	leg->Draw("same");
	if(drawOption==1)c1->Print ("TMVAPdf/TMVA.pdf(");
	else if (drawOption==2)c1->Print ("TMVAPdf/TMVA.pdf)");
	else c1->Print ("TMVAPdf/TMVA.pdf");
}

void drawTMVA(){
	c1 = new TCanvas("c1","",1360,768);
	c1->SetGrid();
	
	gStyle->SetOptStat(0000000000);
	TFile * TF[5];
	TF[0]=TFile::Open("treeV4DY/DY.root");
	TF[1]=TFile::Open("treeV4DY/signal-600.root");
	TF[2]=TFile::Open("treeV4DY/signal-800.root");
	TF[3]=TFile::Open("treeV4DY/signal-1000.root");
	TF[4]=TFile::Open("treeV4DY/signal-1200.root");
	TH1F* TH1[5];
	for(int i=0;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"DY","600","800","1000","1200","DY",1,"BDT");
	drawEE(TH1,"600","800","1000","1200","DY",3,1);
	for(int i=1;i<5;i++)TF[i]->Close();
	
	TF[1]=TFile::Open("treeV4DY/signal-1600.root");
	TF[2]=TFile::Open("treeV4DY/signal-2000.root");
	TF[3]=TFile::Open("treeV4DY/signal-3000.root");
	TF[4]=TFile::Open("treeV4DY/signal-4500.root");
	for(int i=1;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"DY","1600","2000","3000","4500","DY",3,"BDT");
	drawEE(TH1,"1600","2000","3000","4500","DY",3);
	for(int i=0;i<5;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("treeV4DYS/DY.root");
	TF[1]=TFile::Open("treeV4DYS/signal-600.root");
	TF[2]=TFile::Open("treeV4DYS/signal-800.root");
	TF[3]=TFile::Open("treeV4DYS/signal-1000.root");
	TF[4]=TFile::Open("treeV4DYS/signal-1200.root");
	for(int i=0;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawBS(TH1,"DY","600","800","1000","1200","DY",1,"BDT");
	drawEES(TH1,"600","800","1000","1200","DY",3);
	for(int i=1;i<5;i++)TF[i]->Close();
	
	TF[1]=TFile::Open("treeV4DYS/signal-1600.root");
	TF[2]=TFile::Open("treeV4DYS/signal-2000.root");
	TF[3]=TFile::Open("treeV4DYS/signal-3000.root");
	TF[4]=TFile::Open("treeV4DYS/signal-4500.root");
	for(int i=1;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawBS(TH1,"DY","1600","2000","3000","4500","DY",3,"BDT");
	drawEES(TH1,"1600","2000","3000","4500","DY",2);
	for(int i=0;i<5;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("treeV4TT/TT.root");
	TF[1]=TFile::Open("treeV4TT/signal-600.root");
	TF[2]=TFile::Open("treeV4TT/signal-800.root");
	TF[3]=TFile::Open("treeV4TT/signal-1000.root");
	TF[4]=TFile::Open("treeV4TT/signal-1200.root");
	for(int i=0;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"TT","600","800","1000","1200","TT",3,"BDT");
	drawEE(TH1,"600","800","1000","1200","TT",3);
	for(int i=1;i<5;i++)TF[i]->Close();
	
	TF[1]=TFile::Open("treeV4TT/signal-1600.root");
	TF[2]=TFile::Open("treeV4TT/signal-2000.root");
	TF[3]=TFile::Open("treeV4TT/signal-3000.root");
	TF[4]=TFile::Open("treeV4TT/signal-4500.root");
	for(int i=1;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"TT","1600","2000","3000","4500","TT",3,"BDT");
	drawEE(TH1,"1600","2000","3000","4500","TT",3);
	for(int i=0;i<5;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("treeV4DT/DT.root");
	TF[1]=TFile::Open("treeV4DT/signal-600.root");
	TF[2]=TFile::Open("treeV4DT/signal-800.root");
	TF[3]=TFile::Open("treeV4DT/signal-1000.root");
	TF[4]=TFile::Open("treeV4DT/signal-1200.root");
	for(int i=0;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"DY+TT","600","800","1000","1200","DY+TT",3,"BDT");
	drawEE(TH1,"600","800","1000","1200","DY+TT",3);
	for(int i=1;i<5;i++)TF[i]->Close();
	
	TF[1]=TFile::Open("treeV4DT/signal-1600.root");
	TF[2]=TFile::Open("treeV4DT/signal-2000.root");
	TF[3]=TFile::Open("treeV4DT/signal-3000.root");
	TF[4]=TFile::Open("treeV4DT/signal-4500.root");
	for(int i=1;i<5;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("BDT");
	drawB(TH1,"DY+TT","1600","2000","3000","4500","DY+TT",3,"BDT");
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
	drawEff(TG,"600","800","1000","1200","delta Eff (BDT>0)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtCut");
	drawEff(TG,"600","800","1000","1200","Eff vs. Pt (BDT>0)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","Pt15");
	drawEff(TG,"600","800","1000","1200","Eff vs. Pt (BDT>0.15)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","Pt3");
	drawEff(TG,"600","800","1000","1200","Eff vs. Pt (BDT>0.3)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtFat");
	drawEff(TG,"600","800","1000","1200","Eff vs. Pt (FatjetCSV>0.605)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtSub");
	drawEff(TG,"600","800","1000","1200","Eff vs. Pt (subjetCSV>0.605)",3);
	
	for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtCut");
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (BDT>0)",3,1000);
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (BDT>0)",3,1600,1);
	for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("Pt15");
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (BDT>0.15)",3,1000);
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (BDT>0.15)",3,1600,1);
	for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("Pt3");
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (BDT>0.3)",3,1000);
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (BDT>0.3)",3,1600,1);
	for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtFat");
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (FatjetCSV>0.605)",3,1000);
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (FatjetCSV>0.605)",3,1600,1);
    for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtSub");
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (subjetCSV>0.605)",3,1000);
	drawB(TH1,"600","800","1000","1200","Fatjet Pt (subjetCSV>0.605)",3,1600,1);
	for(int i=0;i<4;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("BDTEff/signal-1600.root");
	TF[1]=TFile::Open("BDTEff/signal-2000.root");
	TF[2]=TFile::Open("BDTEff/signal-3000.root");
	TF[3]=TFile::Open("BDTEff/signal-4500.root");
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"deltaR","deltaRCut");
	drawEff(TG,"1600","2000","3000","4500","delta Eff (BDT>0)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtCut");
	drawEff(TG,"1600","2000","3000","4500","Eff vs. Pt (BDT>0)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","Pt15");
	drawEff(TG,"1600","2000","3000","4500","Eff vs. Pt (BDT>0.15)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","Pt3");
	drawEff(TG,"1600","2000","3000","4500","Eff vs. Pt (BDT>0.3)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtFat");
	drawEff(TG,"1600","2000","3000","4500","Eff vs. Pt (FatjetCSV>0.605)",3);
	for (int i=0;i<4;i++)TG[i]=getTGEff(TF[i],"Pt","PtSub");
	drawEff(TG,"1600","2000","3000","4500","Eff vs. Pt (subjetCSV>0.605)",3);
	
	for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtCut");
	drawB(TH1,"1600","2000","3000","4500","Fatjet Pt (BDT>0)",3,3000);
	for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("Pt15");
	drawB(TH1,"1600","2000","3000","4500","Fatjet Pt (BDT>0.15)",3,3000);
	for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("Pt3");
	drawB(TH1,"1600","2000","3000","4500","Fatjet Pt (BDT>0.3)",3,3000);
	for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtFat");
	drawB(TH1,"1600","2000","3000","4500","Fatjet Pt (FatjetCSV>0.605)",3,3000);
    for(int i=0;i<4;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtSub");
	drawB(TH1,"1600","2000","3000","4500","Fatjet Pt (subjetCSV>0.605)",3,3000);
	for(int i=0;i<4;i++)TF[i]->Close();
	
	TF[0]=TFile::Open("BDTEff/TT.root");
	TF[1]=TFile::Open("BDTEff/DY.root");
	for (int i=0;i<2;i++)TG[i]=getTGEff(TF[i],"deltaR","deltaRCut");
	//drawEff(TG,"TT","DY","delta Eff",3);
	drawEff(TG[1],"DY","deltaR Eff (BDT>0)",3);
	for (int i=0;i<2;i++)TG[i]=getTGEff(TF[i],"Pt","PtCut");
	//drawEff(TG,"TT","DY","Pt Eff",3);
	drawEff(TG[1],"DY","Eff vs. Pt (BDT>0)",3);
	for (int i=1;i<2;i++)TG[i]=getTGEff(TF[i],"Pt","Pt15");
	drawEff(TG[1],"DY","Eff vs. Pt (BDT>0.15)",3);
	for (int i=1;i<2;i++)TG[i]=getTGEff(TF[i],"Pt","Pt3");
	drawEff(TG[1],"DY","Eff vs. Pt (BDT>0.3)",3);
	for (int i=1;i<2;i++)TG[i]=getTGEff(TF[i],"Pt","PtFat");
	drawEff(TG[1],"DY","Eff vs. Pt (FatjetCSV>0.605)",3);
	for (int i=1;i<2;i++)TG[i]=getTGEff(TF[i],"Pt","PtSub");
	drawEff(TG[1],"DY","Eff vs. Pt (subjetCSV>0.605)",3);
	
	for(int i=1;i<2;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtCut");
	drawB(TH1[1],"DY","Fatjet Pt (BDT>0)",3);
	for(int i=1;i<2;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("Pt15");
	drawB(TH1[1],"DY","Fatjet Pt (BDT>0.15)",3);
	for(int i=1;i<2;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("Pt3");
	drawB(TH1[1],"DY","Fatjet Pt (BDT>0.3)",3);
	for(int i=1;i<2;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtFat");
	drawB(TH1[1],"DY","Fatjet Pt (FatjetCSV>0.605)",3);
    for(int i=1;i<2;i++)TH1[i]=(TH1F*)TF[i]->FindObjectAny("PtSub");
	drawB(TH1[1],"DY","Fatjet Pt (subjetCSV>0.605)",2);
	for(int i=0;i<2;i++)TF[i]->Close();

	string  masspoint[13]={"600","800","1000","1200","1400","1600","1800","2000","2500","3000","3500","4000","4500"};
	for(int i=0;i<13;i++){
		TFile* temp2D=TFile::Open(Form("BDTEff/signal-%s.root",masspoint[i].data()));
		if(i==0)draw2D(temp2D,masspoint[i].data(),1);
		else draw2D(temp2D,masspoint[i].data(),3);
		temp2D->Close();
	}
	TF[0]=TFile::Open("BDTEff/DY.root");
    draw2D(TF[0],"DY",2);
	string  masspoint2[5]={"800","1000","1600","2000","4500"};
	for(int i=0;i<5;i++){
		TF[1]=TFile::Open(Form("BDTEff/signal-%s.root",masspoint2[i].data()));
	    if(i==0)drawSix(TF[1],TF[0],"Pt",masspoint2[i],1);
		else drawSix(TF[1],TF[0],"Pt",masspoint2[i],3);
		drawSix(TF[1],TF[0],"deltaR",masspoint2[i],3);
		TF[0]->Close();TF[1]->Close();
		TF[0]=TFile::Open("BDTEff/DY.root");
		TF[1]=TFile::Open(Form("BDTEff/signal-%s.root",masspoint2[i].data()));
		drawSixEff(TF[1],TF[0],"Pt",masspoint2[i],3);
		if(i==4)drawSixEff(TF[1],TF[0],"deltaR",masspoint2[i],2);
		else drawSixEff(TF[1],TF[0],"deltaR",masspoint2[i],3);
	}
	
	TF[0]->Close();
}


