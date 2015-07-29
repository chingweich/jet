#include "TH1.h"
#include "TF1.h"
#include "TList.h"
#include "TMathBase.h"
#include "TMath.h"
#include <TFile.h>
#include "TROOT.h"
#include <TCanvas.h>
#include <TStyle.h>

float fiveWidthLow=0,fiveWidthUp=0;
Double_t fline(Double_t *x, Double_t *par)
{
    if (x[0]<fiveWidthLow || x[0]>fiveWidthUp ) {
      TF1::RejectPoint();
      return 0;
   }
   //return par[0] + par[1]*x[0];
   return par[2]*TMath::BreitWigner(x[0],par[0],par[1]);
}


void fit_h_Xm_extended() {
    TCanvas* c1;
	c1 = new TCanvas("c1","",1440,900);
	
    
	
    TFile *f;
	int mass[13]={600,800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
	float width [4]={0.05,0.1,0.2,0.3};
	string widthdata[4]={"0.05","0.1","0.2","0.3"};
	
	//for(int i=0 ;i<4;i++){
		//for(int j=0)
	//}
for(int i=0;i<4;i++){
	for(int j=0;j<13;j++){

    


    f = TFile::Open(Form("offshell_root_files/Zprime_Zh_Zlephbb_w%s_M%d.root",widthdata[i].data(),mass[j]));
    TH1F* h =(TH1F*) f->FindObjectAny("h_Xm_extended");
	

    
    
	
	int bmin=0,bmax=0;

    for (int k=1;k<25001;k++){
		bmin=k;
		if (h->GetBinContent(k)!=0) break;
	}

	for (int k=25000;k>0;k--){
		bmax=k;
		if (h->GetBinContent(k)!=0) break;
	}
	if((bmin-300)<0)bmin=0;
	else bmin=bmin-300;
	bmax=bmax+bmax/10;
	
	
	cout <<bmin<<","<<bmax<<endl;
    //gStyle->SetOptFit(111111);
	//gStyle->SetStatW       (0.1);
    //gStyle->SetStatH       (0.1);
    //gStyle->SetStatX          (0.941349);
    //gStyle->SetStatY          (0.912491);
	
	fiveWidthLow= mass[j] -5* (width [i])*mass[j];
	fiveWidthUp= mass[j] +5* (width [i])*mass[j];
	
	float inte=h->Integral(fiveWidthLow,fiveWidthUp);
	inte=inte*100/(bmax-bmin);

	//h->Rebin((bmax-bmin)/100);
	int massfix=200;
	if(i>1&&j>8)massfix=400;
	if(i>2&&j>9)massfix=500;
	float widthfix=0;
	if(i>2&&j>9)widthfix=0.1;
	
	
	
	TF1* f1 = new TF1("f1","[2]*TMath::BreitWigner(x,[0],[1])");
	f1->SetNpx(2500);
	f1->SetParameters(mass[j],width [i]*mass[j],h->Integral());  
	//f1->SetLineColor(3);
	
	
	h->GetXaxis()->SetRangeUser(bmin,bmax);
    h->SetTitle(Form("offshell_root_files/Zprime_Zh_Zlephbb_w%s_M%d.root",widthdata[i].data(),mass[j]));
	TH1F*  h2=(TH1F*)  h->Clone("h2");
    //h->Fit(f1,"","",fiveWidthLow,fiveWidthUp);
	//h->Fit(f1,"L");
	TF1* f2 = new TF1("f2",fline,bmin,bmax,3);
	
	if(j>2)inte=h->Integral();
	f2->SetParameters(mass[j],width [i]*mass[j],h->Integral());  
	f2->SetNpx(2500);
	//f2->SetLineColor(3);
    //h2->Fit(f2);
	//TF1* fleft = new TF1("fleft","[2]*TMath::BreitWigner(x,[0],[1])");
    //TF1 *fleft = new TF1("fleft","[2]*TMath::BreitWigner(x,[0],[1])",bmin,bmax,3);
    //fleft->SetParameters(f2->GetParameters());
    //fleft->SetLineColor(3);
    h->SetMinimum(0);
    h->Draw();
	//fleft->Draw();
	//h2->Draw("same");
    //f1->Draw();
	if (i==0 && j==0)c1->Print("fit_h_Xm_extended.pdf(");
	else if (i==3 && j==12)c1->Print("fit_h_Xm_extended.pdf)");
    else c1->Print("fit_h_Xm_extended.pdf");
   
    
    c1->SaveAs(Form("png/Zprime_Zh_Zlephbb_w%s_M%d.png",widthdata[i].data(),mass[j]));
  

    //c1->Print("fit_h_Xm_extended.pdf)");
	
}
}

}