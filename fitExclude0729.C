#include "TH1.h"
#include "TF1.h"
#include "TList.h"
#include "TMathBase.h"
#include "TMath.h"
#include <TFile.h>
#include "TROOT.h"
#include <TCanvas.h>
#include <string>
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include "RooTFnBinding.h" 
#include "RooLandau.h"
#include "RooFFTConvPdf.h"
#include "TVirtualFFT.h"
#include "RooBifurGauss.h"
#include "RooHistPdf.h"
#include "RooBreitWigner.h"
#include "RooNovosibirsk.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "TText.h"
#include "RooChi2Var.h"
#include "RooCBShape.h"
#include "RooVoigtian.h"

using namespace RooFit ;




void fitExclude0729()
{
  

 
   TFile *f,*f2,*f3;
   f = TFile::Open("output_95_TTbar_RB.root");
   f2 = TFile::Open("output_93_Signal.root");
   
   f3 = TFile::Open("Merged_SigTT.root");
   TH1F* h =(TH1F*) f->FindObjectAny("transverseMassCutMETout100_150");
   TH1F* h3 =(TH1F*) f2->FindObjectAny("HMassCutMET");
   
   h->Add(h3);
   TH1F* h4 =(TH1F*) f3->FindObjectAny("HMassCutMET");
   //float inte1= h->Integral(75,800);
   //float inte2= h->Integral(75,700);
   //float inte3= h->Integral(75,600);
   int   entry=h->Integral(0,600);
   //h->Rebin(4);
   h3->Rebin(4);
   TH1F* h2 =(TH1F*) h->Clone("h2");
   

   
  // Declare observable x
  RooRealVar x("x","x",0,600) ;
  
 
  x.setRange("Range5",0,380) ; 
  x.setRange("Range6",0,200) ; 
  x.setRange("Range7",0,100) ; 
  x.setRange("Range8",150,400) ; 

  // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
  RooDataHist dh("dh","dh",x,Import(*h4)) ;

  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  // ---------------------------------------------------
  // Make plot of binned dataset showing Poisson error bars (RooFit default)
  RooPlot* frame[30];
  string TitleName[30]={"fit with Gauss","fit with Landau","fit with Landau convoluted with guass","fit with bifurcated_Gaussian",
  "fit with RooHistPdf","fit with RooBreitWigner","fit with Landau convoluted with BreitWigner",
  "fit with RooNovosibirsk","fit with BW convoluted with guass   ","10"
  ,"11","12","13","14","fit with  guass convoluted with BW ","Crystal ball","Voigtian"
  ,"Voigtian convoluted with BreitWigner","gaussConvoltedWithBW + Landau","gaussConvWithBW + landauConvWtihGau",
   "Crystal ball +Landau" ,"Crystal ball +landauConvWtihGau"
  };
  for(int i=0;i<30;i++){
	  frame[i]=x.frame(Title(TitleName[i].data())) ;
	  dh.plotOn(frame[i]) ; 
  }
    
   x.setRange("Range4",35,400) ;
  RooRealVar mean("mean","mean",68,0,400) ;
  RooRealVar meanW("meanW", "meanW",119,0,200) ;
  RooRealVar mg("mg","mg",140,0,400) ;
  RooRealVar ml("ml","mean landau",125,1,200) ;
  RooRealVar sg("sg","sg",26,0.1,500) ;
  RooRealVar sigma("sigma","sigma",17,0.1,500) ;
  RooRealVar sl("sl","sigma landau",56.85,0.1,100) ;
  RooRealVar width("width","width",14,0.1,300) ;

  RooGaussian gauss("gauss","gauss",x,mean,sigma) ;
  RooLandau landau("lx","lx",x,ml,sl) ;

  RooGaussian gaussx("gaussx","gaussx",x,mg,sg) ;  
  RooFFTConvPdf lxg("lxg","landau (X) gauss",x,landau,gaussx) ; 

   RooBreitWigner BW("BW","BW",x,meanW,width);
 
   
   RooFFTConvPdf lxgB("lxgB","landau (X) BreitWigner",x,gauss,BW) ;


   RooRealVar nsig("nsig","signal events",0,40000);
   RooRealVar nbkg("nbkg","background events",0,600000);
   RooAddPdf Exp3("Exp3","Exp3",RooArgList(lxgB,lxg),RooArgList(nsig,nbkg)) ;

   Exp3.fitTo(dh,Range("Range4"),PrintLevel(-1),Extended()) ; 
   Exp3.plotOn(frame[19],LineColor(kRed)) ;
   Exp3.paramOn(frame[19],Layout(0.55)) ;
   Exp3.plotOn(frame[19],Components("lxgB"),LineColor(1)) ;
   Exp3.plotOn(frame[19],Components(lxg),LineStyle(kDashed)) ;

   RooAbsReal* intExp3 = Exp3.createIntegral(x,Range("Range5")) ; 
   RooAbsReal* intExp4 =lxgB.createIntegral(x,Range("Range5")) ;
   
  
   
  	TCanvas* c1;
	c1 = new TCanvas("c1","",1440,900);

	frame[19]->Draw() ;

	

	cout << "chi^2 = " << frame[2]->chiSquare() << endl ;

	cout<<nsig.getVal() <<endl;
        cout<<nbkg.getVal() <<endl;

}
