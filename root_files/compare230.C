#include "TH1.h"
#include "TF1.h"
#include "TList.h"
#include "TMathBase.h"
#include "TMath.h"
#include <TFile.h>
#include "TROOT.h"
#include <TCanvas.h>
#include <TStyle.h>

void compare230() {
	TCanvas* c1;
	c1 = new TCanvas("c1","",1440,900);
	
	int mass[13]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
	TFile *f1,*f2;
	
	TH1F * h_Xm_extended1,* h_Xm_extended2, *h_D_dR01,*h_D_dR02,*h_Bpt01,*h_Bpt02;
	
	for(int j=0;j<13;j++){
		
		f1 = TFile::Open(Form("Zprime_Zh_Zlephbb_w0.05_M%d.root",mass[j]));
		f2 = TFile::Open(Form("2.3.0/Zprime_Zh_Zlephbb_w0.05_M%d.root",mass[j]));
		
		h_Xm_extended1=(TH1F*) f1->FindObjectAny("h_Xm_extended");
		h_Xm_extended2=(TH1F*) f2->FindObjectAny("h_Xm_extended");
		
		h_D_dR01=(TH1F*) f1->FindObjectAny("h_D_dR0");
		h_D_dR02=(TH1F*) f2->FindObjectAny("h_D_dR0");
		
		h_Bpt01=(TH1F*) f1->FindObjectAny("h_Bpt0");
		h_Bpt02=(TH1F*) f2->FindObjectAny("h_Bpt0");
		
		int bmin=0,bmax=0;

    for (int k=1;k<25001;k++){
		bmin=k;
		if (h_Xm_extended1->GetBinContent(k)!=0) break;
	}

	for (int k=25000;k>0;k--){
		bmax=k;
		if (h_Xm_extended1->GetBinContent(k)!=0) break;
	}
	if((bmin-300)<0)bmin=0;
	else bmin=bmin-300;
	bmax=bmax+bmax/10;
	
	    h_Xm_extended1->GetXaxis()->SetRangeUser(bmin,bmax);
		h_Xm_extended1->SetTitle(Form("Zprime_Zh_Zlephbb_w0.05_M%d.root",mass[j]));
		
		h_Xm_extended2->SetMarkerColor(2);
        h_Xm_extended2->SetLineColor(2);
		
		h_D_dR02->SetMarkerColor(2);
        h_D_dR02->SetLineColor(2);
		
		h_Bpt02->SetMarkerColor(2);
        h_Bpt02->SetLineColor(2);
		
		h_Xm_extended1->Draw();
		h_Xm_extended2->Draw("same");
		if(j==0)c1->Print("compare.pdf(");
		else c1->Print("compare.pdf");
		
		h_D_dR01->Draw();
		h_D_dR02->Draw("same");
		c1->Print("compare.pdf");
		h_Bpt01->Draw();
		h_Bpt02->Draw("same");
		if(j==12)c1->Print("compare.pdf)");
		else c1->Print("compare.pdf");
		
	}
	
}