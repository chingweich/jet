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

TFile*  f;
void getNumber(std::string s1){

   f= new TFile(s1.data());
   TH2F * th2;
   TH2F * th2Cut;
   TH2F * th2CutMass;
   
   th2=(TH2F*) f->FindObjectAny("th2");
   th2Cut=(TH2F*) f->FindObjectAny("th2Cut");
   th2CutMass=(TH2F*) f->FindObjectAny("th2CutMass");
   
   
   cout<<"----NoMassCut----"<<endl;
   for (int k=0 ;k<5;k++){
	   int CSVBin=101+10*k;
	   float a=0.0,b=0.0,c=0.0,d=0.0;
	   
	   
	    for(int i=1;i<97;i++){
	        for(int j=1;j<CSVBin;j++){
		        b=b+th2Cut->GetBinContent(i,j);
	        }
        }
        for(int i=97;i<301;i++){
	        for(int j=1;j<CSVBin;j++){
		        d=d+th2Cut->GetBinContent(i,j);
	        } 
        }
        for(int i=1;i<97;i++){
	        for(int j=CSVBin;j<201;j++){
		        a=a+th2Cut->GetBinContent(i,j);
	        }
        }
        for(int i=97;i<301;i++){
	        for(int j=CSVBin;j<201;j++){
		        c=c+th2Cut->GetBinContent(i,j);
	        }
        }
   //cout<<"a="<<a<<" ,b="<<b<<" ,c="<<c<<" ,d="<<d;
   
   cout<<"CSVBin=[0,"<<(CSVBin-1)/100.0<<",2]"<<"     ";
   cout<<"A*D/B="<<a*d/b<<"  ,  c="<<c<<endl;
   
	   
	   
   }
   cout<<"-----------------"<<endl;

   cout<<"----WithMassCut----"<<endl;
   for (int k=0 ;k<5;k++){
	   int CSVBin=101+10*k;
	   float a=0.0,b=0.0,c=0.0,d=0.0;
	   
	   
	    for(int i=1;i<97;i++){
	        for(int j=1;j<CSVBin;j++){
		        b=b+th2CutMass->GetBinContent(i,j);
	        }
        }
        for(int i=97;i<301;i++){
	        for(int j=1;j<CSVBin;j++){
		        d=d+th2CutMass->GetBinContent(i,j);
	        } 
        }
        for(int i=1;i<97;i++){
	        for(int j=CSVBin;j<201;j++){
		        a=a+th2CutMass->GetBinContent(i,j);
	        }
        }
        for(int i=97;i<301;i++){
	        for(int j=CSVBin;j<201;j++){
		        c=c+th2CutMass->GetBinContent(i,j);
	        }
        }
   //cout<<"a="<<a<<" ,b="<<b<<" ,c="<<c<<" ,d="<<d;
   
   cout<<"CSVBin=[0,"<<(CSVBin-1)/100.0<<",2]"<<"     ";
   cout<<"A*D/B="<<a*d/b<<"  ,  c="<<c<<endl;
   
	   
	   
   }
   cout<<"-----------------"<<endl;
   
   float sumX=0,sumX2=0,sumY=0,sumY2=0,sumXY=0;
   for(int i=1;i<301;i++){
	    for(int j=1;j<201;j++){
		    sumX=sumX+(((i+0.5)*M_PI)/300)*(th2->GetBinContent(i,j));
			sumX2=sumX2+(((i*M_PI)/300)*(th2->GetBinContent(i,j)))*(((i*M_PI)/300)*(th2->GetBinContent(i,j)));
			sumY=sumY+j*(th2->GetBinContent(i,j))/100;
			sumY2=sumY2+j*j*(th2->GetBinContent(i,j))/10000;
			sumXY=sumXY+j*((i*M_PI)/300)*(th2->GetBinContent(i,j))/100;
	    }
    }
    //cout<<"sumX="<<sumX<<" ,sumX2="<<sumX2<<endl;
    //cout<<"sumY="<<sumY<<" ,sumY2="<<sumY2<<endl;
    //cout<<"sumXY="<<sumXY<<endl;
	
	cout<<"correlation factor="<<th2->GetCorrelationFactor()<<endl;
	cout<<"correlation factorWith CSV cut="<<th2Cut->GetCorrelationFactor()<<endl;
	cout<<"correlation factorWith CSV and Mass cut="<<th2CutMass->GetCorrelationFactor()<<endl;
} 

