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


void NCU95() {
	
        //string output="output_95_LT.root";
	//string output="output_94_TTbar.root";
        string output="output_95_TTbar_RB.root"; 
	//string output="output_94_WJet.root";
	//string output="output_94_DY.root";
	//string output="output_94_QCD.root";
	//string output="output_94_Signal.root";

	
	TTree *tree;
	TFile *f;
	
   
   double bins[3]={0,1,M_PI};
   double bins2[3]={0,1.2,2};
      
	
   TH1F * th1 =new TH1F("HMass","HMass",600,0,600);
   TH1F * thPt =new TH1F("Pt","Pt",1000,0,1000);
   TH1F * th1MET =new TH1F("MET","MET",1000,0,1000);
   TH1F * th1MT =new TH1F("transverseMass","MT",1000,0,2000);
   TH1F * th1MTIn =new TH1F("transverseMassin100_150","MTin100_150",1000,0,2000);
   TH1F * th1MTOut =new TH1F("transverseMassout100_150","MTout100_150",1000,0,2000);
   TH1F * thr =new TH1F("deltaR","deltaR",30,0,3);
   TH1F * temp =new TH1F("temp","temp",30,0,3);
   TH1F * thdeltaPhi =new TH1F("deltaPhi","deltaPhi",300,0,M_PI);
   TH1F * th1Cut =new TH1F("HMassCut","HMassCut",600,0,600);
   TH1F * thPtCut =new TH1F("PtCut","PtCut",1000,0,1000);
   TH1F * th1METCut =new TH1F("METCut","METCut",1000,0,1000);
   TH1F * th1MTCut =new TH1F("transverseMassCut","MTCut",1000,0,2000);
   TH1F * th1MTCutIn =new TH1F("transverseMassCutin100_150","MTCutin100_150",1000,0,2000);
   TH1F * th1MTCutOut =new TH1F("transverseMassCutout100_150","MTCutout100_150",1000,0,2000);
   TH1F * thrCut =new TH1F("deltaRCut","deltaRCut",30,0,3);
   TH1F * thdeltaPhiCut =new TH1F("deltaPhiCut","deltaPhiCut",300,0,M_PI);
   TH1F * th1CutMET =new TH1F("HMassCutMET","HMassCutMET",600,0,600);
   TH1F * th1MTCutMETIn =new TH1F("transverseMassCutMETin100_150","MTCuMETtin100_150",1000,0,2000);
   TH1F * th1MTCutMETOut =new TH1F("transverseMassCutMETout100_150","MTCutMETout100_150",1000,0,2000);
   TH1F * th1MTCutMET =new TH1F("transverseMassCutMET","MTCutMET",1000,0,2000);
   TH1F * thPtCutMET =new TH1F("PtCutMET","PtCutMET",1000,0,1000);
   TH1F * csv =new TH1F("csvJet1+2","csv",200,0,2);
   TH1F * csvJet1 =new TH1F("csvJet1","csvJet1",200,0,1);
   TH1F * csvJet2 =new TH1F("csvJet2","csvJet2",200,0,1);
   TH1F * csvCut =new TH1F("csvJet1+2Cut","csvCut",200,0,2);
   TH1F * csvJet1Cut =new TH1F("csvJet1Cut","csvJet1Cut",200,0,1);
   TH1F * csvJet2Cut =new TH1F("csvJet2Cut","csvJet2Cut",200,0,1);
   TH2F * th2 =new TH2F("th2","th2",300,0,M_PI,200,0,2);
   TH2F * th2Cut =new TH2F("th2Cut","th2Cut",300,0,M_PI,200,0,2);
   TH2F * th2CutMass =new TH2F("th2CutMass","th2CutMass",300,0,M_PI,200,0,2);
   TH2F * th2FourBin =new TH2F("th2FourBin","th2FourBin",2,bins,2,bins2);
   TH2F * th2FourBinCut =new TH2F("th2FourBinCut","th2FourBinCut",2,bins,2,bins2);
   TH2F * th2FourBinCutMass =new TH2F("th2FourBinCutMass","th2FourBinCutMass",2,bins,2,bins2);
   TH2F * th2MTCutIn =new TH2F("th2MTCutIn","th2MTCutIn",1000,0,2000,600,0,600);
   TH2F * th2MTCutOut =new TH2F("th2MTCutOut","th2MTCutOut",1000,0,2000,600,0,600);
   TH2F * th2MTCut =new TH2F("th2MTCut","th2MTCut",1000,0,2000,600,0,600);
	
	cout<<"run  ,lumi  ,evnet "<<endl;
	
	
	//local test
	// for (int i=100;i<121;i++){
	//f = TFile::Open("NCUGlobalTuples_36.root");
	//TDirectory * dir = (TDirectory*)f->Get("NCUGlobalTuples_36.root:/tree");
   
   //WJets
   //for (int i=100;i<110;i++){ 
   //f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/WJets/0000/NCUGlobalTuples_%d.root",i));
   //TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/WJets/0000/NCUGlobalTuples_%d.root:/tree",i));

   //TTBar
   //for (int i=100;i<120;i++){ 
   //f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/TTBar/0000/NCUGlobalTuples_%d.root",i));
   //TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/TTBar/0000/NCUGlobalTuples_%d.root:/tree",i));

   //TTBar     RB o                                                                                                        
   //for (int i=1;i<229;i++){
     //if(i>95&&i<100) continue;
     //f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/Run2015B/TTBar/NCUGlobalTuples_%d.root",i));
     //TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/Run2015B/TTBar/NCUGlobalTuples_%d.root:/tree",i));

   //TTBar     RB   
	//for (int i=36;i<37;i++){cout<<i<<endl;                                                                                                        
	for (int i=1;i<229;i++){//cout<<i<<endl;
	if((i>94&&i<100)||i==34||i==111||i==112||i==142||i==146||(i>148&&i<153)||i==157||i==161||i==163||i==182) continue;
	 f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/TT_TuneCUETP8M1_13TeV-powheg-pythia8/NCUGlobalTuples_%d.root",i));  if (!f || !f->IsOpen())continue;
	 TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/TT_TuneCUETP8M1_13TeV-powheg-pythia8/NCUGlobalTuples_%d.root:/tree",i));    
  


   //QCD   
   //for (int i=100;i<118;i++){ 
   //f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/QCD/NCUGlobalTuples_%d.root",i));
   //TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/QCD/NCUGlobalTuples_%d.root:/tree",i));

   //DY
   //for (int i=100;i<121;i++){
   //f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJets/NCUGlobalTuples_%d.root",i));
   //TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJets/NCUGlobalTuples_%d.root:/tree",i));

   
   //Signal M900
   //for (int i=100;i<101;i++){
   //f = TFile::Open("/data7/khurana/NCUGlobalTuples/SPRING15/Signal/NCUGlobalTuples_M900.root");                                       
   //TDirectory * dir = (TDirectory*)f->Get("/data7/khurana/NCUGlobalTuples/SPRING15/Signal/NCUGlobalTuples_M900.root:/tree"); 

	  
	  
	  dir->GetObject("treeMaker",tree); 
    //tree =chain;
	TreeReader data(tree);
	//data.Print();
	
	
	  

   Long64_t nentries = data.GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   
   
   
   
   
   cout<<i<<endl;
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   
     //if (jentry % 50000 == 0)
	     //fprintf(stderr, "Processing event %lli of %lli\n", jentry + 1, nentries);
	   
      //Long64_t ientry = LoadTree(jentry);
	  //if (ientry < 0) break;
      //nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  //cout<<"jentry="<<jentry<<",nb="<< nb<<endl;
	  
	  //cout<<jentry<<",";
	  data.GetEntry(jentry);
	  
	  Float_t pfMetCorrPhi=data.GetFloat("pfMetCorrPhi");
      Float_t pfMetCorrPt=data.GetFloat("pfMetCorrPt");
	  Float_t* THINjetCISVV2=data.GetPtrFloat("THINjetCISVV2");
	  TClonesArray* THINjetP4 = (TClonesArray*) data.GetPtrTObject("THINjetP4");
	  //Float_t* THINjetPt=data.GetPtrFloat("THINjetPt");
	  //Float_t* THINjetEta=data.GetPtrFloat("THINjetEta");
	  //Float_t* THINgenjetPx=data.GetPtrFloat("THINgenjetPx");
	  //Float_t* THINgenjetPy=data.GetPtrFloat("THINgenjetPy");
	  //Float_t* THINgenjetPz=data.GetPtrFloat("THINgenjetPz");
	  //Float_t* THINgenjetEn=data.GetPtrFloat("THINgenjetEn");
	  Int_t    THINnJet    =data.GetInt("THINnJet");
	  Int_t    info_runId    =data.GetInt("runId");
	  Int_t    info_lumiSection    =data.GetInt("lumiSection");
	  Int_t    info_eventId    =data.GetInt("eventId");
	  
	  
	  
	  
	  //cout<<jentry<<",";
	  //for(int i=0;i<THINnJet;i++)cout<<THINjetPt[i]<<",";
	  //cout<<endl;
	  
	  //cout<<ARRAY_SIZE(THINjetCISVV2)<<endl;
	  
	  
	  if(THINnJet<2)continue;
	  
	  int b1=0,b2=1;
	  int flag=0;
	  
	  TLorentzVector* THINjetb1 = (TLorentzVector*)THINjetP4->At(b1);
	  TLorentzVector* THINjetb2 = (TLorentzVector*)THINjetP4->At(b2);
	  
	  if(THINjetb1->Pt()<80||THINjetb2->Pt()<30||THINjetb1->Eta()>2.5||THINjetb2->Eta()>2.5)continue;
	  
	  
	  
  
	   
	  //cout<<"b1="<<THINjetCISVV2->at(b1)<<",b2="<< THINjetCISVV2->at(b2)<<endl;
	  TLorentzVector  LorentzVectorB1,LorentzVectorB2,h1;
	  LorentzVectorB1.SetPxPyPzE(THINjetb1->Px(),THINjetb1->Py(),THINjetb1->Pz(),THINjetb1->Energy());
	  LorentzVectorB2.SetPxPyPzE(THINjetb2->Px(),THINjetb2->Py(),THINjetb2->Pz(),THINjetb2->Energy());
	  h1=LorentzVectorB1+LorentzVectorB2;
	  
	  
	  float deltaPhi= fabs(pfMetCorrPhi-LorentzVectorB1.Phi())<fabs(pfMetCorrPhi-LorentzVectorB2.Phi())?pfMetCorrPhi-LorentzVectorB1.Phi():pfMetCorrPhi-LorentzVectorB2.Phi();
	  if(deltaPhi>M_PI)deltaPhi=2*M_PI-deltaPhi;
	  if(deltaPhi<-M_PI)deltaPhi=deltaPhi+2*M_PI;
	  
	  float MT=h1.M()*h1.M()+2*(h1.Et()*pfMetCorrPt-h1.Pt()*pfMetCorrPt*cos(deltaPhi));
	  MT=sqrt(MT);
	  
	  //float deltaR=sqrt((LorentzVectorB1.Phi()-LorentzVectorB2.Phi())*(LorentzVectorB1.Phi()-LorentzVectorB2.Phi())+(LorentzVectorB1.Eta()-LorentzVectorB2.Eta())*(LorentzVectorB1.Eta()-LorentzVectorB2.Eta()));
	  //cout<<"deltaR="<<deltaR<<endl;
	  
	  float deltaR=sqrt((LorentzVectorB1.Phi()-LorentzVectorB2.Phi())*(LorentzVectorB1.Phi()-LorentzVectorB2.Phi())+(LorentzVectorB1.Eta()-LorentzVectorB2.Eta())*(LorentzVectorB1.Eta()-LorentzVectorB2.Eta()));
	  temp->Fill(deltaR);
	  
	  csv->Fill(THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  csvJet1->Fill(THINjetCISVV2[b1]);
	  csvJet2->Fill(THINjetCISVV2[b2]);
	  th2->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  th2FourBin->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  
	  th1->Fill(h1.M());
	  thr->Fill(deltaR);
	  thPt->Fill(h1.Pt());
	  th1MET->Fill(pfMetCorrPt);
	  th1MT->Fill(MT);
	  if(h1.M()>100 && h1.M()<150)th1MTIn->Fill(MT);
	  else th1MTOut->Fill(MT);
	  thdeltaPhi->Fill(fabs(deltaPhi));
	  
	  if(THINjetCISVV2[b1]<0.423||THINjetCISVV2[b2]<0.423)continue;
	  th1Cut->Fill(h1.M());
	  thrCut->Fill(deltaR);
	  thPtCut->Fill(h1.Pt());
	  th1METCut->Fill(pfMetCorrPt);
	  th1MTCut->Fill(MT);
	  th2MTCut->Fill(MT,h1.M());
	  
	  if(h1.M()>100 && h1.M()<150){
		  th2MTCutIn->Fill(MT,h1.M());
		  th1MTCutIn->Fill(MT);
	  }
	  else{
		  th1MTCutOut->Fill(MT);
		  th2MTCutOut->Fill(MT,h1.M());
	  } 
	  
	  if(pfMetCorrPt>100){
		  thPtCutMET->Fill(h1.Pt());
		  th1CutMET->Fill(h1.M());
		  th1MTCutMET->Fill(MT);
		  if(h1.M()>100 && h1.M()<150)th1MTCutMETIn->Fill(MT);
	      else th1MTCutMETOut->Fill(MT);
	  }
	  
	  //cout<<"deltaPhi="<<deltaPhi<<endl;
	  th2Cut->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  thdeltaPhiCut->Fill(fabs(deltaPhi));
	  csvCut->Fill(THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  csvJet1Cut->Fill(THINjetCISVV2[b1]);
	  csvJet2Cut->Fill(THINjetCISVV2[b2]);
	  th2FourBinCut->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  
	  if((h1.M()<90)||(h1.M()>150))continue;
	  th2CutMass->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  th2FourBinCutMass->Fill(fabs(deltaPhi),THINjetCISVV2[b1]+THINjetCISVV2[b2]);
	  
	  if((THINjetCISVV2[b1]+THINjetCISVV2[b2])>1.2 && fabs(deltaPhi)<0.5){
	    //cout<<"run="<<info_runId<<" ,";
	    //cout<<"lumi="<<info_lumiSection<<" ,";
	    //cout<<"event="<<info_eventId<<endl;
	  }
	  
   }
   
   	}
   TH1F *rRatio =(TH1F*)thrCut->Clone("rRatio");
   rRatio->Divide(temp); 
   //thrRatio=thr/thrRatio;
   TFile* ef = new TFile(output.data(),"recreate");
   th1->Write();
   th1Cut->Write();
   thr->Write();
   thrCut->Write();
   thPt->Write();
   thPtCut->Write();
   th1MET->Write();
   th1METCut->Write();
   th1MT->Write();
   th1MTIn->Write();
   th1MTOut->Write();
   th1MTCut->Write();
   th1MTCutIn->Write();
   th1MTCutOut->Write();
   rRatio->Write();
   thPtCutMET->Write();
   th1CutMET->Write();
   th1MTCutMET->Write();
   th1MTCutMETIn->Write();
   th1MTCutMETOut->Write();
   th2->Write();
   th2Cut->Write();
   th2CutMass->Write();
   th2FourBin->Write();
   th2FourBinCut->Write();
   th2FourBinCutMass->Write();
   thdeltaPhi->Write();
   thdeltaPhiCut->Write();
   csv->Write();
   csvCut->Write();
   csvJet1->Write();
   csvJet1Cut->Write();
   csvJet2->Write();
   csvJet2Cut->Write();
   temp   ->Write();
   th2MTCut->Write();
   th2MTCutIn->Write();
   th2MTCutOut->Write();
   th2->Draw("colz");
   //thr->Draw();
   ef->Write();

   
}
