// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#include "plot.h"
#include <TROOT.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <cstring>
using namespace std;


//constructor
plot::plot( ) {
}
//destructor
plot::~plot(){

}

void plot::vec_image(std::vector<double> vecx,std::vector<double> vecy, string str, string str2){

   string strN = "aantal neutronen doorheen tijd, " + str + "; aantal tijd stappen ; aantal neutronen" ; //aparte functies tittel
   char cstr[strN.size() + 1];          //omzetten is c style array om in de title te kunnen
   strcpy(cstr,strN.c_str());

   char cstr2[str2.size() + 1];
   strcpy(cstr2,str2.c_str());

   TCanvas* c = new TCanvas(cstr2,"results");
   int n = vecx.size() ;
   TGraph* gr = new TGraph(n,&vecx[0],&vecy[0]);

   gr->SetTitle(cstr);
   gr->Draw();
   c->Print(cstr2, "png");
}

void plot::vec_image2(std::vector<double> vecx,std::vector<double> vecy, string str, string str2){

   string strN = "Reproductiegetal i.f.v. massa, " + str + "; massa (g) ; Reproductiegetal R" ;        //aparte functies tittel
   char cstr[strN.size() + 1];
   strcpy(cstr,strN.c_str());

   char cstr2[str2.size() + 1];
   strcpy(cstr2,str2.c_str());

   TCanvas* c = new TCanvas(cstr2,"results");
   int n = vecx.size() ;
   TGraph* gr = new TGraph(n,&vecx[0],&vecy[0]);

   gr->SetTitle(cstr);
   gr->Draw();
   c->Print(cstr2, "png");
}
