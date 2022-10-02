// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#include "isotoop.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


//constructor
isotoop::isotoop(const double m ,string str1 , string str2 ):m_massa(control(m)), m_element(str1) ,
    m_isotoop(str2)
     {
    massas_map.insert(pair<string,double>("Cl35",34.968852682)) ;                       //maken soort database
    massas_map.insert(pair<string,double>("Cl37",36.965902591)) ;
    massas_map.insert(pair<string,double>("O16",15.99491461956)) ;
    massas_map.insert(pair<string,double>("H1",1.00782503207)) ;
    massas_map.insert(pair<string,double>("F19",18.998403224)) ;
    massas_map.insert(pair<string,double>("U235",235.043929918)) ;

    nuc_massa = massas_map.find(str1+str2)->second  ;                                   //vinden juiste values bij isotoop

    density_map.insert(pair<string,double>("Cl35",3.214)) ; // g/l
    density_map.insert(pair<string,double>("Cl37",3.214)) ;
    density_map.insert(pair<string,double>("O16",1.429)) ;
    density_map.insert(pair<string,double>("H1",0.08988)) ;
    density_map.insert(pair<string,double>("F19",1.696)) ;
    density_map.insert(pair<string,double>("H1",0.08988)) ;
    density_map.insert(pair<string,double>("U235",19000.)) ;

    density = density_map.find(str1+str2)->second  ;
    volume = m_massa/density ;
    aantal_deeltjes = m/(nuc_massa*1.66053904e-24) ;
}

//destructor
isotoop::~isotoop(){}


void isotoop::read_CRS(string str1){
        vector<double>* ptr_E;
        vector<double>* ptr_crs;

        if(str1 == "Cap"){
            ptr_E = &m_cap_E ;                  //via pointer de member vector bij juiste reactie in invullen
            ptr_crs = &m_cap_crs ;
        }
        else if(str1 == "Fis"){
            ptr_E = &m_fis_E ;
            ptr_crs = &m_fis_crs ;
        }
        else if(str1 == "El"){
            ptr_E = &m_el_E ;
            ptr_crs = &m_el_crs ;
        }
        else {cerr << "invalid reaction type" ;
            exit(1) ;}


        string line ;
        string filenameE = "crosssections/ENER_" + m_element + "-" + m_isotoop + "_" + str1 + ".txt" ; //naam bestand zoals gemaakt in bash script
        ifstream inFile;
        inFile.open(filenameE);
        if (!inFile){
            cerr << "kon bestand niet openen" ;
            exit(1) ;
        }
        while (getline(inFile,line) ){
            if (!line.empty()){
            string::size_type sz;
            ptr_E->push_back(stod(line, &sz)) ;}    //zet tekst om in double
        }
        inFile.close() ;


        string filenameCRS = "crosssections/CROS_" + m_element + "-" + m_isotoop + "_" + str1 + ".txt" ;
        inFile.open(filenameCRS);
        if (!inFile){
            cerr << "kon bestand niet openen" ;
            exit(1) ;
        }
        while (getline(inFile,line) ){
            if (!line.empty()){
            string::size_type sz;
            ptr_crs->push_back(stod(line, &sz)) ;}
        }
        inFile.close() ;


}

double isotoop::get_CRS(string type,double E){
    vector<double>* ptr_E;
    vector<double>* ptr_crs;

    if(type == "Cap"){
        ptr_E = &m_cap_E ;
        ptr_crs = &m_cap_crs ;
    }
    else if(type == "Fis"){
        ptr_E = &m_fis_E ;
        ptr_crs = &m_fis_crs ;
    }
    else if(type == "El"){
        ptr_E = &m_el_E ;
        ptr_crs = &m_el_crs ;
    }
    else {cerr << "invalid reaction type" ;
        exit(1) ;}

    if(ptr_crs->empty() || ptr_E->empty()){
        return 0;                                   //design flaw zie verslag
    }
    else{

        if(E > (*ptr_E)[ptr_E->size() -1] ){
                    return 0.;
           };
        if(E < (*ptr_E)[0] ){
                 return 0.;
        };
        vector<double>::iterator it ;
        it = lower_bound(ptr_E->begin() , ptr_E->end() , E); //pakt eerste value groter dan of gelijk aan als upper interpolatie punt
        int UP = it-ptr_E->begin() ;                         //iteratot omzetten in index
        int UN = (it-ptr_E->begin())-1 ;                     //exploit de van klein naar groot rangschikking om under interpolatie punt te vinden

        double CROSSEC = (*ptr_crs)[UN] + ((*ptr_crs)[UP] - (*ptr_crs)[UN])/((*ptr_E)[UP] - (*ptr_E)[UN])*(E - (*ptr_E)[UN]) ;

        return CROSSEC;
     }
}


const double isotoop::control(double a){
    if (a < 0.)  {
        cout << "double must be greater or equal to zero, double set to zero" << endl;
        return 0.;
    }
    else return a;
 }

double isotoop::get_CRS_tot(double E){

    return get_CRS("Cap",E) + get_CRS("El",E) + get_CRS("Fis",E) ;
}

double isotoop::get_volume(){ return volume;}
double isotoop::get_aantaldeeltjes(){ return aantal_deeltjes; }
double isotoop::get_massa(){return m_massa ; }
double isotoop::get_nuc_massa_ev(){
    double m = nuc_massa*931493614.8 ;
    return m ;
}
string isotoop::get_element(){
    return m_element;
}
string isotoop::get_isonummer(){
    return m_isotoop;
}
