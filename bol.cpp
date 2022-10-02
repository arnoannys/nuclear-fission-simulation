// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021



#include "bol.h"
#include <math.h>
#include <vector>
#include <TRandom.h>
#include <TRandom3.h>
#include <cmath>
using namespace std;

//constructor
bol::bol(const double R): m_radius(control(R))
     { make_rndm_gen();}    //aanroepen van functie uit kern die de Trandom een seed geeft


//destructor
bol::~bol(){}

const double bol::get_volume() const {
    const double vol = (4.*M_PI*m_radius*m_radius*m_radius/3.)/1000. ; // straal in cm maar wil output in L dus delen door 1000
    return vol;
}
 vector<double> bol::get_rndm_point(){

     double phi = m_rand->Uniform(0,2*M_PI);
     double costheta = m_rand->Uniform(-1, 1);
     double u = m_rand->Uniform(0,1) ;
     double theta = acos(costheta) ;
     double r = m_radius*cbrt(u) ;

     double x = r*sin(theta)*cos(phi);
     double y = r*sin(theta)*sin(phi);
     double z = r*cos(theta);

    vector<double> vec ;
    vec.push_back(x) ;
    vec.push_back(y) ;
    vec.push_back(z) ;
    return vec ;
}



 bool bol::is_inside(vector<double> vec){
     if (vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] <= m_radius*m_radius) {
         return 1;}
     else return 0;
 }

 double bol::get_radius(){
     return m_radius ;
 }

 void bol::set_radius(double R){
     m_radius = R;
 }
