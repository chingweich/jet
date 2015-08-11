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
	

    c1 = new TCanvas("c1","",1360,768);
	string  masspoint[13]={"600","800","1000","1200","1400","1600","1800","2000","2500","3000","3500","4000","4500"};

	for (int massP=0;massP<13;massP++){
	//for (int massP=0;massP<1;massP++){
		TString endfix =Form("tree/signal-%s.root",masspoint[massP].data());
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
	


		//TFile *f = new TFile(Form("tree/treePractice0810-%s.root",masspoint[massP].data()),"recreate");
		//TFile *fw = new TFile("tree/DY.root","recreate");
		//TTree* treeP = new TTree("treeP", "title");
		//float fatPt;treeP->Branch("fatPt",&fatPt,"fatPt/F");
		//float fatCSV;treeP->Branch("fatCSV",&fatCSV,"fatCSV/F");
		//float sub1Pt;treeP->Branch("sub1Pt",&sub1Pt,"sub1Pt/F");
		//float sub1Eta;treeP->Branch("sub1Eta",&sub1Eta,"sub1Eta/F");
		//float sub1CSV;treeP->Branch("sub1CSV",&sub1CSV,"sub1CSV/F");
		//float sub2Pt;treeP->Branch("sub2Pt",&sub2Pt,"sub2Pt/F");
		//float sub2Eta;treeP->Branch("sub2Eta",&sub2Eta,"sub2Eta/F");
		//float sub2CSV;treeP->Branch("sub2CSV",&sub2CSV,"sub2CSV/F");
		//float delta_R;treeP->Branch("delta_R",&delta_R,"delta_R/F");
		//		float tau21;treeP->Branch("tau21",&tau21,"tau21/F");






		//Sig
		   for(int w=1;w<2;w++){
		    f = TFile::Open(Form("/data2/syu/13TeV/ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-%s_13TeV-madgraph.root",masspoint[massP].data()));
		     if (!f || !f->IsOpen())continue;
		     TDirectory * dir = (TDirectory*)f->Get(Form("/data2/syu/13TeV/ZprimeZhbb/ZprimeToZhToZlephbb_narrow_M-%s_13TeV-madgraph.root:/tree",masspoint[massP].data()));
		     dir->GetObject("treeMaker",tree);TFile *fw=new TFile(endfix.Data(),"recreate");


		//DY
		//   for(int w=1;w<363;w++){
        // f = TFile::Open(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ForEIKO/150729_202330/0000/NCUGlobalTuples_%d.root",w));
        // if (!f || !f->IsOpen())continue;
        // TDirectory * dir = (TDirectory*)f->Get(Form("/data7/khurana/NCUGlobalTuples/SPRING15/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ForEIKO/150729_202330/0000/NCUGlobalTuples_%d.root:/tree",w));
        // dir->GetObject("treeMaker",tree);TFile *fw=new TFile(Form("tree/DY-%d.root",w),"recreate");


      // TFile *fw;
      // TTree* treeP;
      // if(w==1){fw = new TFile("tree/DY.root","recreate");
      // 	 treeP=new TTree("treeP","treeP");
      // 	}
      // else {fw = new TFile("tree/DY.root","update");
      // 	treeP =(TTree*)fw->FindObjectAny("treeP");}
		   

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
		    float* FATjetTau1=data.GetPtrFloat("FATjetTau1");
		    float* FATjetTau2=data.GetPtrFloat("FATjetTau2");
		    
		    FATsubjet_1.SetPxPyPzE(FATsubjetSDPx[0][0],FATsubjetSDPy[0][0],FATsubjetSDPz[0][0],FATsubjetSDCSV[0][0]);
	            FATsubjet_2.SetPxPyPzE(FATsubjetSDPx[0][1],FATsubjetSDPy[0][1],FATsubjetSDPz[0][1],FATsubjetSDCSV[0][1]);
	            if(FATsubjetSDCSV[0][0]>1 ||FATsubjetSDCSV[0][1]>1 || FATjetCISVV2[0]>1 )continue;
		    
		    fatPt=FATjetP4_1->Pt();//BfatPt->Fill();
		    fatCSV=FATjetCISVV2[0];//BfatCSV->Fill();
		    sub1Pt=FATsubjet_1.Pt();//Bsub1Pt->Fill();
		    sub1Eta=FATsubjet_1.Eta();//Bsub1Eta->Fill();
		    sub1CSV=FATsubjetSDCSV[0][0];//Bsub1CSV->Fill();
		    sub2Pt=FATsubjet_2.Pt();//Bsub2Pt->Fill();
		    sub2Eta=FATsubjet_2.Eta();//Bsub2Eta->Fill();
		    sub2CSV=FATsubjetSDCSV[0][1];//Bsub2CSV->Fill();
		    delta_R=FATsubjet_1.DeltaR(FATsubjet_2);//BdeltaR->Fill();
		    tau21=FATjetTau2[0]/FATjetTau1[0];
		    
		    th1->Fill(FATsubjet_1.DeltaR(FATsubjet_2));
		    th3->Fill(FATjetP4_1->Pt());
		    th5->Fill(FATjetSDmass[0]);
		    hprof->Fill(FATjetP4_1->Pt(),FATsubjet_1.DeltaR(FATsubjet_2));
		    //if(FATsubjet_1.DeltaR(FATsubjet_2)>DRR[DR] &&(FATsubjetSDCSV[0][0]<0.432|| FATsubjetSDCSV[0][1]<0.432))continue;
		    //if(FATsubjet_1.DeltaR(FATsubjet_2)<DRR[DR] && FATjetCSV[0]<0.432)continue;
		    th2->Fill(FATsubjet_1.DeltaR(FATsubjet_2));
		    th4->Fill(FATjetP4_1->Pt());
		    th6->Fill(FATjetSDmass[0]);
 treeP ->Fill();
		   
		  }
		 
		  treeP->Write();
		  fw->Close();
		  //treeP ->Scan();
		  // delete f;
		  //	  f->Close();
		}	
		
		 //treeP ->Write();
		// delete fw;
		//fw->Close();
		th1->Draw();
		if(massP==0)c1->Print("tp/tp.pdf(");
		else if (massP==12)c1->Print("tp/tp.pdf)");
		else c1->Print("tp/tp.pdf");
		
    }	    
    
}

  
