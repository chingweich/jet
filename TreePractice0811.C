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

void TreePractice0811() {
	

    
	string  masspoint[13]={"600","800","1000","1200","1400","1600","1800","2000","2500","3000","3500","4000","4500"};

	//for (int massP=0;massP<13;massP++){
	for (int massP=0;massP<1;massP++){
		
		//Sig
	  //TString endfix =Form("tree/signal-%s.root",masspoint[massP].data());
		    // for(int w=1;w<2;w++){
		    //  f = TFile::Open(Form("/data2/syu/13TeV/ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-%s_13TeV-madgraph.root",masspoint[massP].data()));
		    //   if (!f || !f->IsOpen())continue;
		    //   TDirectory * dir = (TDirectory*)f->Get(Form("/data2/syu/13TeV/ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-%s_13TeV-madgraph.root:/tree",masspoint[massP].data()));
		    //   dir->GetObject("treeMaker",tree);


		//DY
		  //  for(int w=1;w<363;w++){
         // f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ForEIKO/150729_202330/0000/NCUGlobalTuples_%d.root",w));
         // if (!f || !f->IsOpen())continue;
         // TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ForEIKO/150729_202330/0000/NCUGlobalTuples_%d.root:/tree",w));
         // dir->GetObject("treeMaker",tree);TFile *fw=new TFile(Form("tree/DY-%d.root",w),"recreate");



		        //DY100-200
     // double scaleF=0,xsecF=139.4;
      TString endfix ="tree/DYHT100.root"; for(int w=1;w<90;w++){ f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162742/0000/NCUGlobalTuples_%d.root",w));if (!f || !f->IsOpen())continue;
        TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162742/0000/NCUGlobalTuples_%d.root:/tree",w));   dir->GetObject("treeMaker",tree);

    //DY200-400
  // double scaleF=0,xsecF=42.75;
  //     TString endfix ="tree/DYHT200.root";
  //     for(int w=1;w<45;w++){
  //       f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162821/0000/NCUGlobalTuples_%d.root",w));if (!f || !f->IsOpen())continue;
  //       TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162821/0000/NCUGlobalTuples_%d.root:/tree",w));   dir->GetObject("treeMaker",tree);


    //DY400-600
	  // double scaleF=0,xsecF=5.497;
      //  TString endfix ="tree/DYHT400.root";
      // for(int w=1;w<45;w++){
      //    f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162858/0000/NCUGlobalTuples_%d.root",w));if (!f || !f->IsOpen())continue;
      //    TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162858/0000/NCUGlobalTuples_%d.root:/tree",w));   dir->GetObject("treeMaker",tree);


    //DY600-inf
   
	  // TString endfix ="tree/DYHT600.root";for(int w=1;w<48;w++){f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162937/0000/NCUGlobalTuples_%d.root",w));if (!f || !f->IsOpen())continue;TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsHTBins25nsSamples/DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0803/150812_162937/0000/NCUGlobalTuples_%d.root:/tree",w));   dir->GetObject("treeMaker",tree);


// 	 //tt
// 	 TString endfix ="tree/TT.root"; 
// for (int w=1;w<229;w++){//cout<<i<<endl;
	
// 	 f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/TT_TuneCUETP8M1_13TeV-powheg-pythia8/NCUGlobalTuples_%d.root",w));  if (!f || !f->IsOpen())continue;
// 	 TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/TT_TuneCUETP8M1_13TeV-powheg-pythia8/NCUGlobalTuples_%d.root:/tree",w));    dir->GetObject("treeMaker",tree);

  


      // TFile *fw;
      // TTree* treeP;
      // if(w==1){fw = new TFile("tree/DY.root","recreate");
      // 	 treeP=new TTree("treeP","treeP");
      // 	}
      // else {fw = new TFile("tree/DY.root","update");
      // 	treeP =(TTree*)fw->FindObjectAny("treeP");}
		   
       TFile *fw=new TFile(endfix.Data(),"recreate");
		      TTree* treeP=new TTree("treeP","treeP");
      float fatPt;treeP->Branch("fatPt",&fatPt,"fatPt/F");
      float fatCSV;treeP->Branch("fatCSV",&fatCSV,"fatCSV/F");
      float sub1Pt;treeP->Branch("sub1Pt",&sub1Pt,"sub1Pt/F");
      float sub1Eta;treeP->Branch("sub1Eta",&sub1Eta,"sub1Eta/F");
      float sub1CSV;treeP->Branch("sub1CSV",&sub1CSV,"sub1CSV/F");
      float sub2Pt;treeP->Branch("sub2Pt",&sub2Pt,"sub2Pt/F");
      float sub2Eta;treeP->Branch("sub2Eta",&sub2Eta,"sub2Eta/F");
      float sub2CSV;treeP->Branch("sub2CSV",&sub2CSV,"sub2CSV/F");
      float delta_R;treeP->Branch("delta_R",&delta_R,"delta_R/F");
      float tau21;treeP->Branch("tau21",&tau21,"tau21/F");

		  
      cout<<massP<<","<<w<<endl;
		  TreeReader data(tree);
		  //data.Print();
		  Long64_t nentries = data.GetEntriesFast();
		  
		  
		  
		  for (Long64_t jentry=0; jentry<nentries;jentry++) {
		    data.GetEntry(jentry);
		    Int_t FATnJet=data.GetInt("FATnJet");
		    if(FATnJet==0)continue;

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
		    sub1Eta=FATsubjet_1.Eta();//Bsub1Eta->Fill();
		    sub1CSV=FATsubjetSDCSV[FATi][subi];//Bsub1CSV->Fill();
		    sub2Pt=FATsubjet_2.Pt();//Bsub2Pt->Fill();
		    sub2Eta=FATsubjet_2.Eta();//Bsub2Eta->Fill();
		    sub2CSV=FATsubjetSDCSV[FATi][subj];//Bsub2CSV->Fill();
		    delta_R=FATsubjet_1.DeltaR(FATsubjet_2);//BdeltaR->Fill();
		    tau21=FATjetTau2[FATi]/FATjetTau1[FATi];
		    
		    
		    treeP ->Fill();
		   
		  }
		 
		  treeP->Write();
		  fw->Close();
		  
		}	
		
		
    }	    
    
}

  
