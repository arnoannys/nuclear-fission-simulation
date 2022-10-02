// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#include "cilinder.h"
#include <math.h>
#include <vector>

using namespace std;

//constructor
cilinder::cilinder(const double R, const double h): m_radius(control(R)) , m_height(control(h))
     {make_rndm_gen();}  //aanroepen van functie uit kern die de Trandom een seed geeft


//destructor
cilinder::~cilinder(){}

const double cilinder::get_volume() const {
    const double vol = M_PI*m_radius*m_radius*m_height/1000. ; // straal en H in cm maar wil output in L dus delen door 1000
    return vol;
}

vector<double> cilinder::get_rndm_point() {
    double phi = m_rand->Uniform(0,2*M_PI);
    double u = m_rand->Uniform(0,1) ;
    double r = m_radius*sqrt(u) ;
    double h = m_rand->Uniform(0,m_height);

    double x = r*cos(phi);
    double y = r*sin(phi);

   vector<double> vec ;
   vec.push_back(x) ;
   vec.push_back(y) ;
   vec.push_back(h) ;
   return vec ;

}


bool cilinder::is_inside(vector<double> vec){
    if (vec[0]*vec[0] + vec[1]*vec[1]  <= m_radius*m_radius && vec[2] <= m_height && vec[2] > 0.) {return 1;}
        else return 0;
}

void cilinder::set_radius(double R){
    m_radius = R;
}
void cilinder::set_height(double H){
    m_height = H;
}
double cilinder::get_radius(){
    return m_radius ;
}
double cilinder::get_height(){
    return m_height ;
}
