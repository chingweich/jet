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




void fitExclude0728_02()
{
  ////////////////////////////////////////////////////////
  // I m p o r t i n g   R O O T   h i s t o g r a m s  //
  ////////////////////////////////////////////////////////

  // I m p o r t   T H 1   i n t o   a   R o o D a t a H i s t
  // ---------------------------------------------------------

 
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
  
  x.setRange("Range1",0,200) ; 
  x.setRange("Range2",0,200) ;
  x.setRange("Range3",0,200) ; 
  x.setRange("Range4",0,300) ; 
  x.setRange("Range5",0,400) ; 
  x.setRange("Range6",0,200) ; 
  x.setRange("Range7",50,100) ; 
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
    
  // Fit a Gaussian p.d.f to the dataㄒ
  RooRealVar mean("mean","mean",140,0,400) ;

  RooRealVar sigma("sigma","sigma",50,0.1,500) ;
  RooGaussian gauss("gauss","gauss",x,mean,sigma) ;
  gauss.fitTo(dh) ;
  gauss.plotOn(frame[0]) ;
  gauss.paramOn(frame[0],Layout(0.55)) ;
  
  //fit with Landau
  
  RooRealVar ml("ml","mean landau",150,1,200) ;
  RooRealVar sl("sl","sigma landau",40,0.1,100) ;
  RooLandau landau("lx","lx",x,ml,sl) ;
  landau.fitTo(dh,Range("Range7,Range8")) ;
  landau.plotOn(frame[1]) ;
  landau.paramOn(frame[1],Layout(0.55)) ;
  
   RooAbsReal* intLandau = landau.createIntegral(x,NormSet(x),Range("Range6")) ; 
  //RooChi2Var* varLandau ("lx","dh",4);
   //Double_t chi2 = xframe->chiSquare("model", "data", 4);
 //RooChi2Var * varLandau("chi2_lowstat","chi2",landau,dh) ;
   

  
   landau.fitTo(dh,Range("Range1,Range2")) ;
   landau.plotOn(frame[9]) ;
   landau.paramOn(frame[9],Layout(0.55)) ;
 
  //fit with Landau convoluted with guass
  RooRealVar mg("mg","mg",140,1,400) ;
  //mg.setConstant(kTRUE) ; 
  RooRealVar sg("sg","sg",50,0.1,500) ;
  RooGaussian gaussx("gaussx","gaussx",x,mg,sg) ; 
   gaussx.fitTo(dh) ;

  x.setBins(10000);
  RooFFTConvPdf lxg("lxg","landau (X) gauss",x,landau,gaussx) ; 
  lxg.fitTo(dh,Range("Range6")) ; 
  lxg.plotOn(frame[2],LineColor(kRed)) ;
  //landau.plotOn(frame[2],LineStyle(kDashed)) ;
  //gaussx.plotOn(frame[2]) ;
  lxg.paramOn(frame[2],Layout(0.55)) ;
  
  RooAbsReal* intlxg = lxg.createIntegral(x,NormSet(x),Range("Range6")) ; 
  
     lxg.fitTo(dh,Range("Range7")) ;
     lxg.plotOn(frame[10],LineColor(kRed)) ;
	 lxg.paramOn(frame[10],Layout(0.55)) ;
	 
   /* 
	 
	
   RooFFTConvPdf lxg4("lxg","landau (X) gauss",x,landau,gaussx) ; 
	 lxg4.fitTo(dh,Range("Range7")) ;
     lxg4.plotOn(frame[11],LineColor(kRed)) ;
	 lxg4.paramOn(frame[11],Layout(0.55)) ;
	 RooAbsReal* intlxg4 = lxg4.createIntegral(x,NormSet(x),Range("Range7")) ; 
	 
RooFFTConvPdf lxg5("lxg","landau (X) gauss",x,landau,gauss) ; 	 
	 lxg5.fitTo(dh,Range("Range8")) ;
     lxg5.plotOn(frame[12],LineColor(kRed)) ;
	 lxg5.paramOn(frame[12],Layout(0.55)) ;
	 RooAbsReal* intlxg5 = lxg5.createIntegral(x,NormSet(x),Range("Range8")) ; 
	 
	 RooFFTConvPdf lxg6("lxg","landau (X) gauss",x,landau,gaussx) ; 	 
	 lxg6.fitTo(dh,Range("Range3,Range5")) ;
     lxg6.plotOn(frame[13],LineColor(kRed)) ;
	 lxg6.paramOn(frame[13],Layout(0.55)) ;
  
  */
  //fit with bifurcated_Gaussian
  /*
   RooRealVar meanb("meanb","meanb",100,0,500) ;
   RooRealVar sigmaL("sigmaL","sigmaL",10,0.1,100) ;
   RooRealVar sigmaR("sigmaR","sigmaR",50,0.1,100) ;
   
   RooBifurGauss bifurcated_Gaussian("bi","bi",x,meanb,sigmaL,sigmaR);
   bifurcated_Gaussian.fitTo(dh) ;
   bifurcated_Gaussian.plotOn(frame[3],LineColor(kRed)) ;
   bifurcated_Gaussian.paramOn(frame[3],Layout(0.55)) ;
   
  */
   //fit with RooHistPdf.h
   /*  

   RooHistPdf Po ("Po","Po",x,dh);
   Po.fitTo(dh) ;
   Po.plotOn(frame[4],LineColor(kRed)) ;
   Po.paramOn(frame[4],Layout(0.55)) ;
   
   */
   //fit with RooBreitWigner
   
   RooRealVar meanW("meanW", "meanW",100,0,200) ;
   
   //meanW.setConstant(kTRUE) ; 
   RooRealVar width("width","width",10,0.1,300) ;
   RooBreitWigner BW("BW","BW",x,meanW,width);
   BW.fitTo(dh) ;
   BW.plotOn(frame[5],LineColor(kRed)) ;
   BW.paramOn(frame[5],Layout(0.55)) ;
   
   //fit with Landau convoluted with BreitWigner
   
   /*
   
   RooRealVar mls("mls","mean landau",100,0,500) ;
   RooRealVar sls("sls","sigma landau",40,0.1,100) ;
   RooLandau landaus("lxs","lxs",x,mls,sls) ;
   RooFFTConvPdf lxg2("lxg2","landau (X) BreitWigner",x,landau,BW) ;
   lxg2.plotOn(frame[6],LineColor(kRed)) ;
   landau.plotOn(frame[6]) ;
   BW.plotOn(frame[6],LineStyle(kDashed)) ;
   lxg2.paramOn(frame[6],Layout(0.55)) ;
   lxg2.fitTo(dh,Range("Range6")) ; 
  
  */
   //fit with RooNovosibirsk
   /*

   RooRealVar peak("peak", "peak",100,0,200) ;
   RooRealVar width2("width2","width2",100,0.1,200) ;
   RooRealVar tail("tail","tail",50,0.1,200) ;
   RooNovosibirsk NV("NV","NV",x,peak,width2,tail);
   
   NV.fitTo(dh) ;
   NV.plotOn(frame[7],LineColor(kRed)) ;
   NV.paramOn(frame[7],Layout(0.55)) ;
   */
     // fit with BW convoluted with guass   
   
   
   RooFFTConvPdf lxgB("lxgB","landau (X) BreitWigner",x,gauss,BW) ;

   lxgB.paramOn(frame[14],Layout(0.55)) ;
   lxgB.fitTo(dh) ; 
   //gauss.plotOn(frame[14]) ;
   //BW.plotOn(frame[14],LineStyle(kDashed)) ;
   lxgB.plotOn(frame[14],LineColor(kRed)) ;  
   
   
   // fit with BW convoluted with guass   
   
   RooFFTConvPdf lxg3("lxg3","landau (X) BreitWigner",x,BW,gauss) ;
 
   lxg3.fitTo(dh) ; 
   lxg3.plotOn(frame[8],LineColor(kRed)) ;
   lxg3.paramOn(frame[8],Layout(0.55)) ;
   
   //add exp
   
   /*
   RooRealVar c("c", "c",100,0,500) ;
   RooExponential RExp ("RExp","RExp",x,c);
   RooRealVar sig1frac("sig1frac","fraction of component 1 in signal",0.8,0.,1.) ;
   RooAddPdf Exp1("Exp1","Exp1",RooArgList(RExp,lxg),sig1frac) ;
     Exp1.fitTo(dh,Range("Range3,Range5")) ;
     Exp1.plotOn(frame[14],LineColor(kRed)) ;
	 Exp1.paramOn(frame[14],Layout(0.55)) ;
   */
   
   //#include "RooCBShape.h"
   /*   

   //RooRealVar m("m","m",100,0,200);
   RooRealVar m0("m0","m0",117,100,200);
   RooRealVar sigmaCB("sigmaCB","sigmaCB",12,0,100);
   RooRealVar alpha("alpha","alpha",1,0,10);
   RooRealVar n("n","n",1,0,50);
   RooCBShape CB("CB","CB",x,m0,sigmaCB,alpha,n);
   CB.fitTo(dh) ; 
   CB.plotOn(frame[15],LineColor(kRed)) ;
   CB.paramOn(frame[15],Layout(0.55)) ;
   
   */
   //#include "RooVoigtian.h"
   /*
   RooRealVar meanV("meanV","meanV",117,100,200);
   RooRealVar widthV("widthV","widthV",12,0,100);
   RooRealVar sigmaV("sigmaV","sigmaV",1,0,100);
   RooVoigtian V("V","V",x,meanV,widthV,sigmaV);
   V.fitTo(dh) ; 
   V.plotOn(frame[16],LineColor(kRed)) ;
   V.paramOn(frame[16],Layout(0.55)) ;
   
   //CB con with  BW
   RooFFTConvPdf lxgV("lxg3","landau (X) BreitWigner",x,V,BW) ;
 
   lxgV.fitTo(dh) ; 
   lxgV.plotOn(frame[17],LineColor(kRed)) ;
   lxgV.paramOn(frame[17],Layout(0.55)) ;
   */
   // gauConBW +Landau

   
   RooRealVar sig1frac("sig1frac","fraction of component 1 in signal",0.1,0.,1.) ;
   RooLandau landauA("landauA","landauA",x,ml,sl) ;
   RooAddPdf Exp2("Exp2","Exp2",RooArgList(lxgB,landauA),sig1frac) ;
   landauA.fitTo(dh,Range("Range7,Range8")) ;
   //landauA.plotOn(frame[18],LineColor(3)) ;
   lxgB.fitTo(dh,Range("Range6")) ;
   Exp2.fitTo(dh) ; 
   Exp2.plotOn(frame[18],LineColor(kRed)) ;
   Exp2.paramOn(frame[18],Layout(0.55)) ;
   Exp2.plotOn(frame[18],Components("lxgB")) ;
   Exp2.plotOn(frame[18],Components(landauA),LineStyle(kDashed)) ;
   //lxgB.plotOn(frame[18]) ;
   //landau.plotOn(frame[18],LineStyle(kDashed)) ;
   
   // gauConBW+LandauConGa
   RooRealVar sig1frac2("sig1frac","fraction of component 1 in signal",0.1,0.,1.) ;
   //RooAddPdf Exp3("Exp3","Exp3",RooArgList(lxgB,lxg),sig1frac2) ;
   RooRealVar nsig("nsig","signal events",0,50000);
   RooRealVar nbkg("nbkg","background events",0,600000);
   RooAddPdf Exp3("Exp3","Exp3",RooArgList(lxgB,lxg),RooArgList(nsig,nbkg)) ;
   lxg.fitTo(dh,Range("Range7,Range8")) ;
   lxgB.fitTo(dh,Range("Range6")) ;
   //lxg.plotOn(frame[19],LineColor(3)) ;
   Exp3.fitTo(dh,Range("Range4"),PrintLevel(-1),Extended()) ; 
   Exp3.plotOn(frame[19],LineColor(kRed)) ;
   Exp3.paramOn(frame[19],Layout(0.55)) ;
   Exp3.plotOn(frame[19],Components("lxgB"),LineColor(1)) ;
   Exp3.plotOn(frame[19],Components(lxg),LineStyle(kDashed)) ;
   //lxgB.plotOn(frame[18]) ;
   //landau.plotOn(frame[18],LineStyle(kDashed)) ;
   RooAbsReal* intExp3 = Exp3.createIntegral(x,Range("Range5")) ; 
   RooAbsReal* intExp4 =lxgB.createIntegral(x,Range("Range5")) ;
   
  
   /*
   //Voigtian +Landau
   RooRealVar sig1frac3("sig1frac","fraction of component 1 in signal",0.1,0.,1.) ;
   RooAddPdf Exp4("Exp2","Exp2",RooArgList(CB,landauA),sig1frac3) ;
   Exp4.fitTo(dh) ; 
   Exp4.plotOn(frame[20],LineColor(kRed)) ;
   Exp4.paramOn(frame[20],Layout(0.55)) ;
   Exp4.plotOn(frame[20],Components("CB")) ;
   Exp4.plotOn(frame[20],Components(landauA),LineStyle(kDashed)) ;
   
   //Voigtian +LandauConGa
   RooRealVar sig1frac4("sig1frac","fraction of component 1 in signal",0.1,0.,1.) ;
   RooAddPdf Exp5("Exp2","Exp2",RooArgList(CB,lxg),sig1frac4) ;
   Exp5.fitTo(dh) ; 
   Exp5.plotOn(frame[21],LineColor(kRed)) ;
   Exp5.paramOn(frame[21],Layout(0.55)) ;
   Exp5.plotOn(frame[21],Components("CB")) ;
   Exp5.plotOn(frame[21],Components(lxg),LineStyle(kDashed)) ;
   
   */
   
  	TCanvas* c1;
	c1 = new TCanvas("c1","",1440,900);
	c1->Divide(2,2);
	c1->cd(1);
	frame[18]->Draw() ;
	c1->cd(2);
	frame[19]->Draw() ;
	c1->cd(3);
	frame[20]->Draw() ;
	c1->cd(4);
	frame[21]->Draw() ;
	
	//cout<<inte1<<","<<inte2<<","<<inte3<<endl;
	//cout<<intLandau->getVal() * entry<<endl;
    //cout << "chi^2 = " << frame[1]->chiSquare() << endl ;
	//cout<<intlxg->getVal() * entry<<endl;
	cout << "chi^2 = " << frame[2]->chiSquare() << endl ;
	//cout<<intlxg4->getVal() * entry<<endl;
	//cout << "chi^2 = " << frame[11]->chiSquare() << endl ;
	//cout<<intlxg5->getVal() * entry<<endl;
	//cout << "chi^2 = " << frame[12]->chiSquare() << endl ;
	cout<<nsig.getVal() <<endl;
        cout<<nbkg.getVal() <<endl;
	//cout<< entry-sig1frac2.getVal()*entry <<endl;
	//cout << intExp4->getVal() <<endl;
	//cout << intExp3->getVal() <<endl;
}
