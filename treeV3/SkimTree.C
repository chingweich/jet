
#include <TFile.h>
#include "TTree.h"

void SkimTree(){
  TFile* inputfile = new TFile("signal-600to4500.root","READ");
  //inputfile->cd();
  //tree->cd();
  TTree*  treeP = (TTree*) inputfile->Get("treeP");
  TFile* outputfile = new TFile("signal-ML400.root","RECREATE");
  TTree* newtree =treeP->CopyTree("fatPt>400","",1000000000,0);
  
  outputfile->cd();
  //newtree->Write();
  outputfile->Write();
    
}