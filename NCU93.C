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


void NCU93() {
	
	string output="output_93.root";
	
	TTree *tree;
	TFile *f;
	
   
   double bins[3]={0,1,M_PI};
   double bins2[3]={0,1.2,2};
      
	
   TH1F * th1 =new TH1F("HMass","th1",200,0,200);
   TH1F * thr =new TH1F("deltaR","thr",30,0,3);
   TH1F * temp =new TH1F("temp","temp",30,0,3);
   TH1F * thdeltaPhi =new TH1F("deltaPhi","deltaPhi",300,0,M_PI);
   TH1F * csv =new TH1F("csv","csv",200,0,2);
   TH1F * csvJet1 =new TH1F("csvJet1","csvJet1",200,0,1);
   TH1F * csvJet2 =new TH1F("csvJet2","csvJet2",200,0,1);
   TH1F * csvCut =new TH1F("csvCut","csvCut",200,0,2);
   TH1F * csvJet1Cut =new TH1F("csvJet1Cut","csvJet1Cut",200,0,1);
   TH1F * csvJet2Cut =new TH1F("csvJet2Cut","csvJet2Cut",200,0,1);
   TH2F * th2 =new TH2F("th2","th2",300,0,M_PI,200,0,2);
   TH2F * th2Cut =new TH2F("th2Cut","th2Cut",300,0,M_PI,200,0,2);
   TH2F * th2CutMass =new TH2F("th2CutMass","th2CutMass",300,0,M_PI,200,0,2);
   TH2F * th2FourBin =new TH2F("th2FourBin","th2FourBin",2,bins,2,bins2);
   TH2F * th2FourBinCut =new TH2F("th2FourBinCut","th2FourBinCut",2,bins,2,bins2);
   TH2F * th2FourBinCutMass =new TH2F("th2FourBinCutMass","th2FourBinCutMass",2,bins,2,bins2);
	
	cout<<"run  ,lumi  ,evnet "<<endl;
	
      	for (int i=100;i<121;i++){
     	f = TFile::Open("NCUGlobalTuples_M1250.root");
        TDirectory * dir = (TDirectory*)f->Get("NCUGlobalTuples_M1250.root:/tree");
      
   //for (int i=100;i<118;i++){
   //f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/QCD/NCUGlobalTuples_%d.root",i));
   //TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/QCD/NCUGlobalTuples_%d.root:/tree",i));

   //for (int i=100;i<121;i++){
   //f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/NCUGlobalTuples_%d.root",i));
   //TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/NCUGlobalTuples_%d.root:/tree",i));

   //for (int i=100;i<101;i++){
   //f = TFile::Open("/data7/khurana/NCUGlobalTuples/SPRING15/Signal/NCUGlobalTuples_M900.root");                                       
   //TDirectory * dir = (TDirectory*)f->Get("/data7/khurana/NCUGlobalTuples/SPRING15/Signal/NCUGlobalTuples_M900.root:/tree"); 

	  
	  
	  dir->GetObject("treeMaker",tree); 
    //tree =chain;
	TreeReader data(tree);
	//data.Print();
	
	
	  

   Long64_t nentries = data.GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   
   
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   
	   if (jentry % 50000 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries);
	   
      //Long64_t ientry = LoadTree(jentry);
	  //if (ientry < 0) break;
      //nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  //cout<<"jentry="<<jentry<<",nb="<< nb<<endl;
	  
	  //cout<<jentry<<",";
	  data.GetEntry(jentry);
	  
	  Float_t pfMetCorrPhi=data.GetFloat("pfMetCorrPhi");
	  Float_t* THINjetCISVV2=data.GetPtrFloat("THINjetCISVV2");
	  Float_t* THINjetPt=data.GetPtrFloat("THINjetPt");
	  Float_t* THINjetEta=data.GetPtrFloat("THINjetEta");
	  Float_t* THINgenjetPx=data.GetPtrFloat("THINgenjetPx");
	  Float_t* THINgenjetPy=data.GetPtrFloat("THINgenjetPy");
	  Float_t* THINgenjetPz=data.GetPtrFloat("THINgenjetPz");
	  Float_t* THINgenjetEn=data.GetPtrFloat("THINgenjetEn");
	  Int_t    THINnJet    =data.GetInt("THINnJet");
	  Int_t    info_runId    =data.GetInt("info_runId");
	  Int_t    info_lumiSection    =data.GetInt("info_lumiSection");
	  Int_t    info_eventId    =data.GetInt("info_eventId");
	  
	  
	  //cout<<jentry<<",";
	  //for(int i=0;i<THINnJet;i++)cout<<THINjetPt[i]<<",";
	  //cout<<endl;
	  
	  //cout<<ARRAY_SIZE(THINjetCISVV2)<<endl;
	  
	  
	  if(THINnJet<2)continue;
	  
	  int b1=0,b2=1;
	  int flag=0;
	  
	  if(THINjetPt[b1]<80||THINjetPt[b2]<30||THINjetEta[b1]>2.5||THINjetEta[b2]>2.5)continue;
	  
	  
	  
	  
	  /*
	  for (int nentry=0; nentry<THINjetCISVV2->size();nentry++) {
		  if(THINjetCISVV2->at(nentry)<0.605)continue;
   		  if(THINjetCISVV2->at(nentry)>THINjetCISVV2->at(b1)){
			  b2=b1;
			  b1=nentry;
			  continue;
		  }
		  if((nentry!=0)&&(THINjetCISVV2->at(nentry)>THINjetCISVV2->at(b2))){
			  b2=nentry;
		  }
		  
		  flag++;
	   }
	   if(flag<2)continue;
	   */
	   
	  //cout<<"b1="<<THINjetCISVV2->at(b1)<<",b2="<< THINjetCISVV2->at(b2)<<endl;
	  TLorentzVector  LorentzVectorB1,LorentzVectorB2,h1;
	  LorentzVectorB1.SetPxPyPzE(THINgenjetPx[b1],THINgenjetPy[b1],THINgenjetPz[b1],THINgenjetEn[b1]);
	  LorentzVectorB2.SetPxPyPzE(THINgenjetPx[b2],THINgenjetPy[b2],THINgenjetPz[b2],THINgenjetEn[b2]);
	  h1=LorentzVectorB1+LorentzVectorB2;
	  
	  float deltaPhi= fabs(pfMetCorrPhi-LorentzVectorB1.Phi())<fabs(pfMetCorrPhi-LorentzVectorB2.Phi())?pfMetCorrPhi-LorentzVectorB1.Phi():pfMetCorrPhi-LorentzVectorB2.Phi();
	  if(deltaPhi>M_PI)deltaPhi=deltaPhi-M_PI;
	  if(deltaPhi<-M_PI)deltaPhi=deltaPhi+M_PI;
	  
	  //float deltaR=sqrt((LorentzVectorB1.Phi()-LorentzVectorB2.Phi())*(LorentzVectorB1.Phi()-LorentzVectorB2.Phi())+(LorentzVectorB1.Eta()-LorentzVectorB2.Eta())*(LorentzVectorB1.Eta()-LorentzVectorB2.Eta()));
	  //cout<<"deltaR="<<deltaR<<endl;
	  
	  float deltaR=sqrt((LorentzVectorB1.Phi()-LorentzVectorB2.Phi())*(LorentzVectorB1.Phi()-LorentzVectorB2.Phi())+(LorentzVectorB1.Eta()-LorentzVectorB2.Eta())*(LorentzVectorB1.Eta()-LorentzVectorB2.Eta()));
	  temp->Fill(deltaR);
	  
	  csv->Fill(THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  csvJet1->Fill(THINjetCISVV2[b1]);
	  csvJet2->Fill(THINjetCISVV2[b2]);
	  th2->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  th2FourBin->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  
	  if(THINjetCISVV2[b1]<0.423||THINjetCISVV2[b2]<0.423)continue;
	  th1->Fill(h1.M());
	  thr->Fill(deltaR);
	  
	  //cout<<"deltaPhi="<<deltaPhi<<endl;
	  th2Cut->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  thdeltaPhi->Fill(fabs(deltaPhi));
	  csvCut->Fill(THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  csvJet1Cut->Fill(THINjetCISVV2[b1]);
	  csvJet2Cut->Fill(THINjetCISVV2[b2]);
	  th2FourBinCut->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  
	  if((h1.M()<90)||(h1.M()>150))continue;
	  th2CutMass->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  th2FourBinCutMass->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  
	  if((THINjetCISVV2[b1]+THINjetCISVV2[b2])>1.2 && fabs(deltaPhi)<0.5){
		  cout<<"run="<<info_runId<<" ,";
		  cout<<"lumi="<<info_lumiSection<<" ,";
		  cout<<"event="<<info_eventId<<endl;
	  }
	  
   }
   
   	}
   TH1F *rRatio =(TH1F*)thr->Clone("rRatio");
   rRatio->Divide(temp); 
   //thrRatio=thr/thrRatio;
   TFile* ef = new TFile(output.data(),"recreate");
   th1->Write();
   thr->Write();
   rRatio->Write();
   th2->Write();
   th2Cut->Write();
   th2CutMass->Write();
   th2FourBin->Write();
   th2FourBinCut->Write();
   th2FourBinCutMass->Write();
   thdeltaPhi->Write();
   csv->Write();
   csvCut->Write();
   csvJet1->Write();
   csvJet1Cut->Write();
   csvJet2->Write();
   csvJet2Cut->Write();
   temp   ->Write();
   th2->Draw("colz");
   //thr->Draw();
   ef->Write();
   
   
}
