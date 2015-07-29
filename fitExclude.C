#include "TH1.h"
#include "TF1.h"
#include "TList.h"
#include "TMathBase.h"
#include "TMath.h"
#include <TFile.h>
#include "TROOT.h"
#include <TCanvas.h>
#include <TStyle.h>


Bool_t reject;
Double_t fline(Double_t *x, Double_t *par)
{
    if (reject && x[0] > 100 && x[0] < 150) {
      TF1::RejectPoint();
      return 0;
   }
   //return par[0] + par[1]*x[0];
   return par[0]*TMath::Landau(x[0],par[1],par[2],kFALSE);
}

void fitExclude() {
		TCanvas* c1;
	c1 = new TCanvas("c1","",1440,900);
	
    //Create a source function
   //TF1 *f1 = new TF1("f1","[0] +[1]*x +gaus(2)",0,5);
   //f1->SetParameters(6,-1,5,3,0.2);
   // create and fill histogram according to the source function
   //TH1F *h = new TH1F("h","background + signal",100,0,5);
   //h->FillRandom("f1",2000);
   TF1 *fl = new TF1("fl",fline,0,400,3);
   TFile *f;
   f = TFile::Open("output_95_TTbar_RB.root");
   TH1F* h =(TH1F*) f->FindObjectAny("HMassCutMET");
   h->Rebin(4);
   TH1F*  h2=(TH1F*)  h->Clone("h2");
      fl->SetParameters(1,0,0.3);  
   //fl->SetParameters(2,-1);      
   //fit only the linear background excluding the signal area
   reject = kTRUE;
   h2->Fit(fl);
   reject = kFALSE;
   //store 2 separate functions for visualization
   h =(TH1F*) f->FindObjectAny("HMassCutMET");
   /*
   TF1 *fleft = new TF1("fleft",fline,0,100,3);
   fleft->SetParameters(fl->GetParameters());
   h->GetListOfFunctions()->Add(fleft);
   gROOT->GetListOfFunctions()->Remove(fleft);
   TF1 *fright = new TF1("fright",fline,150,400,3);
   fright->SetParameters(fl->GetParameters());
   h->GetListOfFunctions()->Add(fright);
   gROOT->GetListOfFunctions()->Remove(fright);
   */
   
   gStyle->SetOptFit(111111);
	gStyle->SetStatW       (0.3);
    gStyle->SetStatH       (0.3);
    gStyle->SetStatX          (0.941349);
    gStyle->SetStatY          (0.912491);
   TF1 *fleft = new TF1("fleft",fline,0,100,3);
   fleft->SetParameters(fl->GetParameters());
   TF1 *fright = new TF1("fright",fline,150,600,3);
   fright->SetParameters(fl->GetParameters());
   h->Draw();
   fleft->Draw("same");
   fright->Draw("same");   
   //fl->Draw("same");
     c1->Print("fitt.pdf(");
   
   TH1F*  h3=(TH1F*)  h->Clone("h3");
   fl->SetParameters(1,0,0.3);  
   h3->Fit(fl);

c1->Print("fitt.pdf)");


/*
	TCanvas* c1;
	c1 = new TCanvas("c1","",1440,900);
	
   TFile *f;
   f = TFile::Open("output_94_WJet.root");
   TH1F* h =(TH1F*) f->FindObjectAny("HMassCutMET");
   //Create a source function
   //TF1 *f1 = new TF1("f1","Landau([0],[1],[2])",0,400);
   //f1->SetParameters(6,-1,5,3,0.2);
   // create and fill histogram according to the source function
   //TH1F *h = new TH1F("h","background + signal",100,0,5);
   //h->FillRandom("f1",2000);
   TF1 *fl = new TF1("fl",fline,0,400,3);
   fl->SetParameters(1,0,0.3);      
   //fit only the linear background excluding the signal area
   reject = kTRUE;
   h->Fit(fl);
   reject = kFALSE;
   //store 2 separate functions for visualization
   TF1 *fleft = new TF1("fleft",fline,0,100,3);
   fleft->SetParameters(fl->GetParameters());
   h->GetListOfFunctions()->Add(fleft);
   gROOT->GetListOfFunctions()->Remove(fleft);
   //TF1 *fright = new TF1("fright",fline,150,400,3);
   //fright->SetParameters(fl->GetParameters());
   //h->GetListOfFunctions()->Add(fright);
   //gROOT->GetListOfFunctions()->Remove(fright);
   h->Draw();
   //fleft->Draw("same");
   //fright->Draw("same");   
   c1->Print("fit.pdf(");
 
   TF1 *fl1 = new TF1("fl",fline,0,400,3);
   h->Fit(fl1);
   fleft = new TF1("fleft",fline,0,100,2);
   fleft->SetParameters(fl1->GetParameters());
   //h->GetListOfFunctions()->Add(fleft);
   //gROOT->GetListOfFunctions()->Remove(fleft);
   fright = new TF1("fright",fline,150,400,2);
   fright->SetParameters(fl1->GetParameters());
   //h->GetListOfFunctions()->Add(fright);
   //gROOT->GetListOfFunctions()->Remove(fright);
   h->Draw();
   fleft->Draw("same");
   fright->Draw("same");  
   c1->Print("fit.pdf)");
   
   
   */
}