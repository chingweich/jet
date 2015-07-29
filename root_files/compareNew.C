#include "TH1.h"
#include "TF1.h"
#include "TList.h"
#include "TMathBase.h"
#include "TMath.h"
#include <TFile.h>
#include "TROOT.h"
#include <TCanvas.h>
#include <TStyle.h>

void compareNew() {
	TCanvas* c1;
	c1 = new TCanvas("c1","",1440,900);
	
	int mass[13]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
	TFile *f1,*f2;
	
	TH1F  *h_D_dR01,*h_D_dR02,*h_Bpt01,*h_Bpt02,*h_By01,*h_By02,*h_cosTheta01,*h_cosTheta02;
	
	for(int j=0;j<13;j++){
		
		f1 = TFile::Open(Form("compare/new_RSGraviton_ZZ_ZlepZhad_narrow_M%d.root",mass[j]));
		f2 = TFile::Open(Form("compare/BulkGraviton_ZZ_ZlepZhad_narrow_M%d.root",mass[j]));
		
		
		
		h_D_dR01=(TH1F*) f1->FindObjectAny("h_D_dR0");
		h_D_dR02=(TH1F*) f2->FindObjectAny("h_D_dR0");
		
		h_Bpt01=(TH1F*) f1->FindObjectAny("h_Bpt0");
		h_Bpt02=(TH1F*) f2->FindObjectAny("h_Bpt0");
		
		h_By01=(TH1F*) f1->FindObjectAny("h_By0");
		h_By02=(TH1F*) f2->FindObjectAny("h_By0");
		
		h_cosTheta01=(TH1F*) f1->FindObjectAny("h_cosTheta0");
		h_cosTheta02=(TH1F*) f2->FindObjectAny("h_cosTheta0");
		
	
		h_D_dR01->Scale(1/h_D_dR01->Integral());
		h_D_dR02->Scale(1/h_D_dR02->Integral());
		h_Bpt01->Scale(1/h_Bpt01->Integral());
		h_Bpt02->Scale(1/h_Bpt02->Integral());
		h_By01->Scale(1/h_By01->Integral());
		h_By02->Scale(1/h_By02->Integral());
		h_cosTheta01->Scale(1/h_cosTheta01->Integral());
		h_cosTheta02->Scale(1/h_cosTheta02->Integral());
		
		
		
		
		h_Bpt01->SetTitle(Form("RedIsBulkGraviton_ZZ_ZlepZhad_narrow_M%d.root",mass[j]));
		
		
		
		h_D_dR02->SetMarkerColor(2);
        h_D_dR02->SetLineColor(2);
		
		h_Bpt02->SetMarkerColor(2);
        h_Bpt02->SetLineColor(2);
		
		h_By02->SetMarkerColor(2);
        h_By02->SetLineColor(2);
		
		h_cosTheta02->SetMarkerColor(2);
        h_cosTheta02->SetLineColor(2);
		
        h_Bpt01->Draw();
		h_Bpt02->Draw("same");
		if(j==0)c1->Print("compare_new_RSGraviton_and_BulkGraviton.pdf(");
		else c1->Print("compare_new_RSGraviton_and_BulkGraviton.pdf");
		
		h_D_dR01->Draw();
		h_D_dR02->Draw("same");
		c1->Print("compare_new_RSGraviton_and_BulkGraviton.pdf");

		h_By02->Draw();
        h_By01->Draw("same");
		
		c1->Print("compare_new_RSGraviton_and_BulkGraviton.pdf");
			
		h_cosTheta01->Draw();
		h_cosTheta02->Draw("same");
		

		if(j==12)c1->Print("compare_new_RSGraviton_and_BulkGraviton.pdf)");
		else c1->Print("compare_new_RSGraviton_and_BulkGraviton.pdf");
		
	}
	
}