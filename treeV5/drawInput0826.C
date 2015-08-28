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
#include "../untuplizer.h"

TCanvas* c1;
double x1NDC = 0.6522;
double y1NDC = 0.7835;
double x2NDC = 0.9122;
double y2NDC = 0.9860;

string output="pdf/inputVariable.pdf";

void drawTwoSame(TH1F* th1,TH1F* th2){
	th1->Draw();
	th2->SetLineColor(2);
	th2->Draw("same");
	
}

void drawTwoSameS(TH1F* th1,TH1F* th2){
	int temp=th1->GetNbinsX(),bmax=0;
	for (int k=temp;k>0;k--){
		bmax=k;
		if (th1->GetBinContent(k)!=0) break;
	}
	bmax=th1->GetBinCenter(bmax);
	bmax*=1.1;
	//cout<<bmax<<endl;
	th1->GetXaxis()->SetRangeUser(1,bmax);
	th2->GetXaxis()->SetRangeUser(1,bmax);
	th1->Draw();
	th2->SetLineColor(2);
	th2->Draw("same");
	
}

void drawRatio(TH1F* th1,TH1F* th2){
	TH1F* th3=(TH1F*)th2->Clone("th3");
	th3->Divide(th1);
	th3->SetLineColor(1);
	th3->SetMarkerSize(1);
	th3->SetMarkerStyle(20);
	th3->GetYaxis()->SetLabelSize(0.11);
	th3->SetYTitle("ratio");
	th3->SetTitle("");
	th3->Draw("p");
}

void drawTogether(TH1F* th1,TH1F* th2){
  TPad *pad1 = new TPad("pad1","This is pad1",0.05,0.3,0.95,0.97);
  TPad *pad2 = new TPad("pad2","This is pad2",0.05,0.02,0.95,0.35);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  drawTwoSame(th1,th2);
  pad2->cd();
  drawRatio(th1,th2);
	
}

void drawTogetherS(TH1F* th1,TH1F* th2){
  TPad *pad1 = new TPad("pad1","This is pad1",0.05,0.3,0.95,0.97);
  TPad *pad2 = new TPad("pad2","This is pad2",0.05,0.02,0.95,0.35);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  drawTwoSameS(th1,th2);
  pad2->cd();
  drawRatio(th1,th2);
	
}


void drawBase (TFile* f,int drawOpntion=3,string masspoint=""){
  TTree* tree=(TTree*)f->Get("treeP");
  TreeReader data(tree);
  //data.Print();
  Long64_t nentries = data.GetEntriesFast();
  
  TH1F* th1= new TH1F("BDT",Form("%s BDT",masspoint.data()),20,-0.8,0.8);
  TH1F* th2= new TH1F("fatPt","fatjetPt",100,200,3200);
  TH1F* th3= new TH1F("fatCSV","fatjetCSV",20,0,1);
  TH1F* th4= new TH1F("sub1Pt","subjet1Pt",100,0,3200);
  TH1F* th5= new TH1F("sub1CSV","subjet1CSV",20,0,1);
  TH1F* th6= new TH1F("sub2Pt","subjet2Pt",100,0,3200);
  TH1F* th7= new TH1F("sub2CSV","subjet2CSV",20,0,1);
  TH1F* th8= new TH1F("DR","deltaR",20,0,1);
  TH1F* th9= new TH1F("tau21","tau2/tau1",20,0,1);
  TH1F* th10= new TH1F("tau1","tau1",20,0,1);
  TH1F* th11= new TH1F("tau2","tau2",20,0,1);
  
  TH1F* th12= new TH1F("BDTCut","BDT",20,-0.8,0.8);
  TH1F* th13= new TH1F("fatPtCut","fatjetPt",100,200,3200);
  TH1F* th14= new TH1F("fatCSVCut","fatjetCSV",20,0,1);
  TH1F* th15= new TH1F("sub1PtCut","subjet1Pt",100,0,3200);
  TH1F* th16= new TH1F("sub1CSVCut","subjet1CSV",20,0,1);
  TH1F* th17= new TH1F("sub2PtCut","subjet2Pt",100,0,3200);
  TH1F* th18= new TH1F("sub2CSVCut","subjet2CSV",20,0,1);
  TH1F* th19= new TH1F("DRCut","deltaR",20,0,1);
  TH1F* th20= new TH1F("tau21Cut","tau2/tau1",20,0,1);
  TH1F* th21= new TH1F("tau1Cut","tau1",20,0,1);
  TH1F* th22= new TH1F("tau2Cut","tau2",20,0,1);
  
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    data.GetEntry(jentry);
    Float_t BDT=data.GetFloat("BDT");
    if(BDT<-990)continue;
    Float_t fatPt=data.GetFloat("fatPt");
    Float_t fatCSV=data.GetFloat("fatCSV");
    Float_t sub1Pt=data.GetFloat("sub1Pt");
    Float_t sub1CSV=data.GetFloat("sub1CSV");
    Float_t sub2Pt=data.GetFloat("sub2Pt");
    Float_t sub2CSV=data.GetFloat("sub2CSV");
    Float_t delta_R=data.GetFloat("delta_R");
    Float_t tau21=data.GetFloat("tau21");
    Float_t tau1=data.GetFloat("tau1");
    Float_t tau2=data.GetFloat("tau2");
	
	th1->Fill(BDT);
	th2->Fill(fatPt);
	th3->Fill(fatCSV);
	th4->Fill(sub1Pt);
	th5->Fill(sub1CSV);
	th6->Fill(sub2Pt);
	th7->Fill(sub2CSV);
	th8->Fill(delta_R);
	th9->Fill(tau21);
	th10->Fill(tau1);
	th11->Fill(tau2);
	
	if(BDT<0)continue;
	
    th12->Fill(BDT);
	th13->Fill(fatPt);
	th14->Fill(fatCSV);
	th15->Fill(sub1Pt);
	th16->Fill(sub1CSV);
	th17->Fill(sub2Pt);
	th18->Fill(sub2CSV);
	th19->Fill(delta_R);
	th20->Fill(tau21);
	th21->Fill(tau1);
	th22->Fill(tau2);
  }
  c1->Clear();
  c1->Divide(3,2);
  
  
  c1->cd(1);
  drawTogether(th1,th12);
  c1->cd(2);
  drawTogetherS(th2,th13);
  c1->cd(3);
  drawTogether(th3,th14);
  c1->cd(4);
  drawTogetherS(th4,th15);
  c1->cd(5);
  drawTogether(th5,th16);
  c1->cd(6);
  drawTogetherS(th6,th17);
  
  if(drawOpntion==1)c1->Print(Form("%s(",output.data()));
  else c1->Print(Form("%s",output.data()));
  
  
  c1->Clear();
  c1->Divide(3,2);
  c1->cd(1);
  drawTogether(th7,th18);
  c1->cd(2);
  drawTogether(th8,th19);
  c1->cd(3);
  drawTogether(th9,th20);
  c1->cd(4);
  drawTogether(th10,th21);
  c1->cd(5);
  drawTogether(th11,th22);
 
  if(drawOpntion==2)c1->Print(Form("%s)",output.data()));
  else c1->Print(Form("%s",output.data()));
  
  
  
}

TH1F * getCSV(string tf,string CSVName){
	TFile* tf1 = TFile::Open(tf.data());
	TH1F * tempCSV= new TH1F(CSVName.data(),CSVName.data(),100,0,1.2);
	TTree* tree=(TTree*) tf1->Get("treeP");
    TreeReader data(tree);
    //data.Print();
    Long64_t nentries = data.GetEntriesFast();
	for (Long64_t jentry=0; jentry<nentries;jentry++){
		
		data.GetEntry(jentry);
		Float_t BDT=data.GetFloat("BDT");
		if(BDT<-990)continue;
		Float_t CSV=data.GetFloat(CSVName.data());
		tempCSV->Fill(CSV);
		//cout<<CSV<<endl;
		
	}
	return tempCSV;
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

TH1F* drawE(string s1,string s2,bool show=0){
	TFile* f1 = TFile::Open(s1.data());
	TFile* f2 = TFile::Open(s2.data());
	
	TTree* tree=(TTree*)f1->Get("treeP");
    TreeReader data(tree);
    //data.Print();
    Long64_t nentries = data.GetEntriesFast();
	
	TTree* tree2=(TTree*)f2->Get("treeP");
	TreeReader data2(tree2);
    Long64_t nentries2= data2.GetEntriesFast();
	
	int nbins=100;
	TH1F* temp=new TH1F("ROC","ROC",nbins,0,1);
	float CSV=1,sumNum=0;
	for(int i=100;i>0 ;i--){
		float tempNum=nentries *(101-i) /100;
		//float CSV=1;
		while(sumNum<tempNum){
			sumNum=0;
			for (Long64_t jentry=0; jentry<nentries;jentry++) {
			data.GetEntry(jentry);
			Float_t BDT=data.GetFloat("BDT");
			if(BDT<-990)continue;
			//Float_t fatPt=data.GetFloat("fatPt");
			//Float_t sub1Pt=data.GetFloat("sub1Pt");
			//Float_t sub2Pt=data.GetFloat("sub2Pt");
			//Float_t fatCSV=data.GetFloat("fatCSV");
			Float_t sub1CSV=data.GetFloat("sub1CSV");
			Float_t sub2CSV=data.GetFloat("sub2CSV");
			if(sub1CSV > CSV && sub2CSV> CSV)sumNum++;

			}
			CSV-=0.005;
			if(CSV<0)break;
		}
		cout<<"csv="<<CSV<<endl;
		
		float sumNum2=0;
		for (Long64_t jentry=0; jentry<nentries2;jentry++) {
			data2.GetEntry(jentry);
			Float_t BDT=data.GetFloat("BDT");
			if(BDT<-990)continue;
			//Float_t fatPt=data.GetFloat("fatPt");
			//Float_t sub1Pt=data.GetFloat("sub1Pt");
			//Float_t sub2Pt=data.GetFloat("sub2Pt");
			//Float_t fatCSV=data.GetFloat("fatCSV");
			Float_t sub1CSV=data2.GetFloat("sub1CSV");
			Float_t sub2CSV=data2.GetFloat("sub2CSV");
			
			if(sub1CSV < CSV && sub2CSV < CSV) {
				
				//cout<<"jentry="<<jentry<<",sumNum2="<<	sumNum2<<",sub1CSV="<<sub1CSV<<",sub12CSV="<<sub2CSV<<endl;
				continue;
			}
			
			//cout<<"jentry="<<jentry<<",sumNum2="<<	sumNum2<<endl;
			sumNum2=sumNum2+1;

		}
		
		//cout<<sumNum2<<","<<nentries2<<",sumNum2/nentries2="<<sumNum2/nentries2<<endl;
		temp->SetBinContent(i,sumNum2/nentries2);
		
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
	if(drawOption==1)c1->Print ("pdf/ROC.pdf(");
	else if (drawOption==2)c1->Print ("pdf/ROC.pdf)");
	else c1->Print ("pdf/ROC.pdf");
}

void drawEE(string s1,string s2,string s3,string s4,string s5,int drawOption){
	
	TH1F* th2[4];
	
		th2[0]=drawE(Form("signal-%s.root",s1.data()),"DY.root");
		th2[1]=drawE(Form("signal-%s.root",s2.data()),"DY.root");
		th2[2]=drawE(Form("signal-%s.root",s3.data()),"DY.root");
		th2[3]=drawE(Form("signal-%s.root",s4.data()),"DY.root");
	
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
	if(drawOption==1)c1->Print ("pdf/ROC.pdf(");
	else if (drawOption==2)c1->Print ("pdf/ROC.pdf)");
	else c1->Print ("pdf/ROC.pdf");
}

void drawB(TH1F *th1[],string s1,string s2,string s3,string s4,string s5,string s6,int drawOption,string s7="",string s8=""){
	int color[5]={30,38,41,46,28};
	float temp=0;
	for(int i=0;i<5;i++){
		th1[i]->Scale(1/th1[i]->Integral());
		if(th1[i]->GetMaximum()>temp)temp=th1[i]->GetMaximum();
	}
	for(int i=0;i<5;i++){
		th1[i]->SetMaximum(temp*1.2);
		//th1[i]->GetXaxis()->SetRangeUser(-0.6,+0.8);
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
	if(drawOption==1)c1->Print ("pdf/ROC.pdf(");
	else if (drawOption==2)c1->Print ("pdf/ROC.pdf)");
	else c1->Print ("pdf/ROC.pdf");
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
	if(drawOption==1)c1->Print ("pdf/ROC.pdf(");
	else if (drawOption==2)c1->Print ("pdf/ROC.pdf)");
	else c1->Print ("pdf/ROC.pdf");
	c1->SetLogy(0);
}

void drawPt2to1 (TFile* f,int drawOption=3,string masspoint="",int cut=0){
  TTree* tree=(TTree*)f->Get("treeP");
  TreeReader data(tree);
  //data.Print();
  Long64_t nentries = data.GetEntriesFast();
  
  TH1F* th9= new TH1F("tau21",Form("%s subjet2Pt/subjet1Pt",masspoint.data()),20,0,1);
  TH1F* th10= new TH1F("sub1tofat",Form("%s subjet1Pt/fatjetPt",masspoint.data()),20,0,1);
  TH1F* th1= new TH1F("CSV1tofat",Form("%s subjet1CSV/fatjetCVS",masspoint.data()),50,0,5);
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    data.GetEntry(jentry);
    Float_t BDT=data.GetFloat("BDT");
    if(BDT<-990)continue;
	Float_t fatPt=data.GetFloat("fatPt");
    Float_t sub1Pt=data.GetFloat("sub1Pt");
    Float_t sub2Pt=data.GetFloat("sub2Pt");
	Float_t fatCSV=data.GetFloat("fatCSV");
    Float_t sub1CSV=data.GetFloat("sub1CSV");
	
	if(cut>0 && fatPt<300) continue;
    if(cut>1 && fatPt<300 && fatCSV <0.8) continue;
	
	th9->Fill(sub2Pt/sub1Pt);
	th10->Fill(sub1Pt/fatPt);
	th1->Fill(sub1CSV/fatCSV);
	
  }
    if(cut>0 ){
		th9->SetTitle(Form("%s subjet2Pt/subjet1Pt,fatPt>300",masspoint.data()));
		th10->SetTitle(Form("%s subjet1Pt/fatjetPt,fatPt>300",masspoint.data()));
		th1->SetTitle(Form("%s subjet1CSV/fatjetCVS,fatPt>300",masspoint.data()));
		
	}
	
	if(cut>1 ){
		th9->SetTitle(Form("%s subjet2Pt/subjet1Pt,fatPt>300,fatCSV>0.8",masspoint.data()));
		th10->SetTitle(Form("%s subjet1Pt/fatjetPt,fatPt>300,fatCSV>0.8",masspoint.data()));
		th1->SetTitle(Form("%s subjet1CSV/fatjetCVS,fatPt>300,fatCSV>0.8",masspoint.data()));
		
	}
	
  
    c1->cd(0);
	//th9->SetTitle(Form("%s subjet2Pt/subjet1Pt",masspoint.data()));
	th9->Draw();
    
    if(drawOption==1)c1->Print ("pdf/sub.pdf(");
	//else if (drawOption==2)c1->Print ("pdf/sub.pdf)");
	else c1->Print ("pdf/sub.pdf");
  
    th1->Draw();
    c1->Print ("pdf/sub.pdf");
  
  
    th10->Draw();
	
    if (drawOption==2)c1->Print ("pdf/sub.pdf)");
	else c1->Print ("pdf/sub.pdf");
}

void drawInput0826(){
  TFile* f = TFile::Open("signal-600to4500.root");
  c1 = new TCanvas("c1","",1360,768);
  gStyle->SetOptStat(0000000000);
  drawBase(f,1,"signal 600-4500GeV");
  f->Close();
  
  string  masspoint[13]={"600","800","1000","1200","1400","1600","1800","2000","2500","3000","3500","4000","4500"};
  for (int massP=0;massP<13;massP++){
   TFile* f = TFile::Open(Form("signal-%s.root",masspoint[massP].data()));
   drawBase(f,3,Form("signal %sGeV",masspoint[massP].data()));
   if(massP==0)drawPt2to1(f,1,Form("signal %sGeV",masspoint[massP].data()));
   else drawPt2to1(f,3,Form("signal %sGeV",masspoint[massP].data()));
   f->Close();
  }
  f = TFile::Open("DY.root");
  drawBase(f,2,"DY");
  drawPt2to1(f,3,"DY");
  drawPt2to1(f,3,"DY",1);
  drawPt2to1(f,2,"DY",2);
  
  
  TH1F * fatCSV[14], * sub1CSV [14], *sub2CSV[14];
  for (int massP=0;massP<13;massP++){
   //TFile* f = TFile::Open(Form("signal-%s.root",masspoint[massP].data()));
   //drawBase(f,3,Form("signal %sGeV",masspoint[massP].data()));
   //f->Close();
   fatCSV[massP]=getCSV(Form("signal-%s.root",masspoint[massP].data()),"fatCSV");
   sub1CSV[massP]=getCSV(Form("signal-%s.root",masspoint[massP].data()),"sub1CSV");
   sub2CSV[massP]=getCSV(Form("signal-%s.root",masspoint[massP].data()),"sub2CSV");
  }
  
  fatCSV[13]=getCSV("DY.root","fatCSV");
  sub1CSV[13]=getCSV("DY.root","sub1CSV");
  sub2CSV[13]=getCSV("DY.root","sub2CSV");
  
  c1->cd(0);
  c1->SetGrid();
  TH1F* TH1[5];
  TH1[0]=fatCSV[13];
  for(int i=0;i<5;i++)TH1[i+1]=fatCSV[i];
  drawB(TH1,"DY","600","800","1000","1200","fatCSV",1,"CSV");
  drawEE(TH1,"600","800","1000","1200","fatCSV ROC",3);
  
  TH1[1]=fatCSV[5];
  TH1[2]=fatCSV[7];
  TH1[3]=fatCSV[9];
  TH1[4]=fatCSV[12];
  
  drawB(TH1,"DY","1600","2000","3000","4500","fatCSV",3,"CSV");
  drawEE(TH1,"1600","2000","3000","4500","fatCSV ROC",3);
  
  
  //TH1F* test =drawE("signal-600.root","DY.root");
  //test->Draw();
  
  
  drawEE("600","800","1000","1200","subCSV ROC",3);
  drawEE("1600","2000","3000","4500","subCSV ROC",2);
}
