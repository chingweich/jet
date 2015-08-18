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
#include <cstdlib>
#include <map>
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

TTree *tree;
TFile *f;
TCanvas* c1;

void setLeg(TLegend *leg){
leg->SetFillColor(18);
leg->SetFillStyle(0);
leg->SetTextSize(0.03);
leg->SetBorderSize(2);
}

using namespace TMVA;

void TMVAReaderPracticeDT0818() {
	
  bool isTT=0;
    
	string  masspoint[13]={"600","800","1000","1200","1400","1600","1800","2000","2500","3000","3500","4000","4500"};

	//for (int massP=0;massP<13;massP++){
	 for (int massP=0;massP<1;massP++){
		
		//Sig
	   //  TString endfix =Form("treeV4DT/signal-%s.root",masspoint[massP].data());for(int w=1;w<2;w++){f = TFile::Open(Form("/data2/syu/13TeV/ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-%s_13TeV-madgraph.root",masspoint[massP].data()));if (!f || !f->IsOpen())continue;TDirectory * dir = (TDirectory*)f->Get(Form("/data2/syu/13TeV/ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-%s_13TeV-madgraph.root:/tree",masspoint[massP].data()));dir->GetObject("treeMaker",tree);


	  //DY100-200
  
	   //for(int w=1;w<90;w++){ f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162742/0000/NCUGlobalTuples_%d.root",w));if (!f || !f->IsOpen())continue;TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162742/0000/NCUGlobalTuples_%d.root:/tree",w));   dir->GetObject("treeMaker",tree);TString endfix =Form("treeV4DT/DYHT100-%d.root",w);

    //DY200-400
 
	 
	   //  for(int w=1;w<45;w++){f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162821/0000/NCUGlobalTuples_%d.root",w));if (!f || !f->IsOpen())continue;TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162821/0000/NCUGlobalTuples_%d.root:/tree",w));   dir->GetObject("treeMaker",tree);TString endfix =Form("treeV4DT/DYHT200-%d.root",w);


    //DY400-600

	   //  for(int w=1;w<45;w++){f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162858/0000/NCUGlobalTuples_%d.root",w));if (!f || !f->IsOpen())continue;TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162858/0000/NCUGlobalTuples_%d.root:/tree",w));   dir->GetObject("treeMaker",tree);TString endfix =Form("treeV4DT/DYHT400-%d.root",w);


    //DY600-inf
   
	   //  for(int w=1;w<48;w++){f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162937/0000/NCUGlobalTuples_%d.root",w));if (!f || !f->IsOpen())continue;TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162937/0000/NCUGlobalTuples_%d.root:/tree",w));   dir->GetObject("treeMaker",tree);TString endfix =Form("treeV4DT/DYHT600-%d.root",w);


//tt
	     isTT=1; for (int w=1;w<174;w++){f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8_0803/150803_175618/0000/NCUGlobalTuples_%d.root",w));  if (!f || !f->IsOpen())continue;TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8_0803/150803_175618/0000/NCUGlobalTuples_%d.root:/tree",w));    dir->GetObject("treeMaker",tree);TString endfix =Form("treeV4DT/TT-%d.root",w);


      // TFile *fw;
      // TTree* treeP;
      // if(w==1){fw = new TFile("tree/DY.root","recreate");
      // 	 treeP=new TTree("treeP","treeP");
      // 	}
      // else {fw = new TFile("tree/DY.root","update");
      // 	treeP =(TTree*)fw->FindObjectAny("treeP");}
		   
       TFile *fw=new TFile(endfix.Data(),"recreate");
       
      float fatPt;
      float fatCSV;
      float sub1Pt;
      
      float sub1CSV;
      float sub2Pt;
     
      float sub2CSV;
      float delta_R;
      float tau21;
      float tau1;
      float tau2;
      
      cout<<massP<<","<<w<<endl;
      TreeReader data(tree);
      //data.Print();
      Long64_t nentries = data.GetEntriesFast();

      TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
      reader->AddVariable( "fatPt", &fatPt );
      reader->AddVariable( "fatCSV", &fatCSV );
      reader->AddVariable( "sub1Pt", &sub1Pt );
      reader->AddVariable( "sub1CSV", &sub1CSV );
      reader->AddVariable( "sub2Pt", &sub2Pt );
      reader->AddVariable( "sub2CSV", &sub2CSV );
      reader->AddVariable( "delta_R", &delta_R );
      reader->AddVariable( "tau21", &tau21 );
      reader->AddVariable( "tau1", &tau1 );
      reader->AddVariable( "tau2", &tau2 );

      reader->BookMVA("BDT method","weights/DT.xml"); 
      TH1F *th1 =new TH1F("BDT","BDT",100,-0.8,0.8);
		  
		  for (Long64_t jentry=0; jentry<nentries;jentry++) {
		    data.GetEntry(jentry);
		    Int_t FATnJet=data.GetInt("FATnJet");
		    if(FATnJet==0)continue;

		    TClonesArray* eleP4 = (TClonesArray*) data.GetPtrTObject("eleP4");
		    TClonesArray* muP4 = (TClonesArray*) data.GetPtrTObject("muP4");
		    vector<bool> eleIsPassVeto=  *((vector<bool>*) data.GetPtr("eleIsPassVeto"));
		    vector<bool> isLooseMuon=  *((vector<bool>*) data.GetPtr("isLooseMuon"));
		    Int_t nMu=data.GetInt("nMu");
		    Int_t nEle=data.GetInt("nEle");
		    vector<int> mus,eles;
		    for(int i=0;i<nEle;i++){
		      TLorentzVector* thisEle =(TLorentzVector*)eleP4->At(i) ;
		      if(thisEle->Pt()<10 ||fabs(thisEle->Eta())>2.5 || eleIsPassVeto[i]==0 )continue;
		      eles.push_back(i);
		    }
		    
		     for(int i=0;i<nMu;i++){
		       TLorentzVector* thisMu =(TLorentzVector*)muP4->At(i) ;
		       if(thisMu->Pt()<10 ||fabs(thisMu->Eta())>2.4 || isLooseMuon[i]==0 )continue;
		       mus.push_back(i);
		     }
		      
		    
		    TClonesArray* FATjetP4 = (TClonesArray*) data.GetPtrTObject("FATjetP4");
		    Float_t*  FATjetSDmass = data.GetPtrFloat("FATjetSDmass");
		    Float_t*  FATjetCISVV2 = data.GetPtrFloat("FATjetCISVV2");


		    //if(>1 )continue;    
		    
		    int FATi=0;
		    bool isFAT=0;
		    TLorentzVector* FATjetP4_1;
		    //cout<<FATnJet<<endl;
		    for (FATi=0;FATi<FATnJet;FATi++){
		      //cout<<"FATi="<<FATi<<endl;
		      if(FATjetCISVV2[FATi]<0 ||FATjetCISVV2[FATi]>1 )continue;
		      FATjetP4_1 = (TLorentzVector*)FATjetP4->At(FATi);
		      bool isOverlap=0;
		      for(int i=0;i<mus.size();i++){
			TLorentzVector* thisMu =(TLorentzVector*)muP4->At(mus[i]) ;
			if(FATjetP4_1->DeltaR(*thisMu)<0.8){
			  isOverlap=1;
			  break;
			}
		      }
		      if(!isOverlap){
			for(int i=0;i<eles.size();i++){
			  TLorentzVector* thisEle =(TLorentzVector*)eleP4->At(eles[i]) ;
			  if(FATjetP4_1->DeltaR(*thisEle)<0.8){
			    isOverlap=1;
			    break;
			  }
			}
			
		      }
		      if(isOverlap)continue;
		      
		      isFAT=1;
		    break;
		    }
		    if(!isFAT)continue;
		    
		    if(FATjetP4_1->Pt()<200)continue;
		    
		    Int_t* FATnSubSDJet=data.GetPtrInt("FATnSubSDJet");
		    
		    if(FATnSubSDJet[FATi]<2)continue;
		    
		    int nsub=FATnSubSDJet[FATi];
		    if(nsub!=2)cout<<"nsub="<<nsub<<endl;if(nsub!=2)cout<<"nsub="<<nsub<<endl;
		    //
		    
		    float* FATjetTau1=data.GetPtrFloat("FATjetTau1");
		    float* FATjetTau2=data.GetPtrFloat("FATjetTau2");
		    vector<float>   *FATsubjetSDCSV =  data.GetPtrVectorFloat("FATsubjetSDCSV");
		    vector<float>   *FATsubjetSDPx =  data.GetPtrVectorFloat("FATsubjetSDPx");
		    vector<float>   *FATsubjetSDPy =  data.GetPtrVectorFloat("FATsubjetSDPy");
		    vector<float>   *FATsubjetSDPz =  data.GetPtrVectorFloat("FATsubjetSDPz");
		    vector<float>   *FATsubjetSDCE =  data.GetPtrVectorFloat("FATsubjetSDCE");
		    
		 	

		    int subi=0,subj=0;
		    bool isSubi=0,isSubj=0;
		    
	         
		    for(int subij=0;subij<FATnSubSDJet[FATi];subij++){
		      if(FATsubjetSDCSV[FATi][subij]>1 ||FATsubjetSDCSV[FATi][subij]<0 )continue;
		      if(!isSubi && !isSubj){
			subi=subij;isSubi=1;continue;
		      }
		      if(isSubi && !isSubj){
			subj=subij;isSubj=1;break;
		      }
		    }
		    //
		    if (!isSubi || !isSubj)continue;
		    
		    TLorentzVector  FATsubjet_1,FATsubjet_2;
		    
		    
		    FATsubjet_1.SetPxPyPzE(FATsubjetSDPx[FATi][subi],FATsubjetSDPy[FATi][subi],FATsubjetSDPz[FATi][subi],FATsubjetSDCE[FATi][subi]);
	            FATsubjet_2.SetPxPyPzE(FATsubjetSDPx[FATi][subj],FATsubjetSDPy[FATi][subj],FATsubjetSDPz[FATi][subj],FATsubjetSDCE[FATi][subj]);
	           
		    
		    fatPt=FATjetP4_1->Pt();//BfatPt->Fill();
		    fatCSV=FATjetCISVV2[FATi];//BfatCSV->Fill();
		    sub1Pt=FATsubjet_1.Pt();//Bsub1Pt->Fill();
		    //sub1Eta=FATsubjet_1.Eta();//Bsub1Eta->Fill();
		    sub1CSV=FATsubjetSDCSV[FATi][subi];//Bsub1CSV->Fill();
		    sub2Pt=FATsubjet_2.Pt();//Bsub2Pt->Fill();
		    //sub2Eta=FATsubjet_2.Eta();//Bsub2Eta->Fill();
		    sub2CSV=FATsubjetSDCSV[FATi][subj];//Bsub2CSV->Fill();
		    delta_R=FATsubjet_1.DeltaR(FATsubjet_2);//BdeltaR->Fill();
		    tau21=FATjetTau2[FATi]/FATjetTau1[FATi];
		    tau1=FATjetTau1[FATi];
		    tau2=FATjetTau2[FATi];
		    
		    
		    th1 ->Fill( reader->EvaluateMVA("BDT method"));
		   
		  }
		  th1->Write();
		  
		  fw->Close();
		  
		}	
		
		
    }	    
    
}

  
