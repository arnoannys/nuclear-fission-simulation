// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#include "neutron.h"
#include <iostream>
#include <TRandom.h>
#include <TRandom3.h>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <random>

using namespace std;


//constructor
neutron::neutron(double E , const double xpos, const double ypos , const double zpos ):
    m_energie(E) , m_xpos(xpos) , m_ypos(ypos), m_zpos(zpos) {

    random_device rd;
    mt19937 gen(rd());                                       //als enkel tijd als seed dan zijn alle richingen hetzelfde
    uniform_real_distribution<> dis(0. , 100.) ;             // wanneer de neutronen in een loop worden aangemaakt. Daarom
    m_rand = new TRandom3() ;                                // wordt de seed zelf random gemaakt a.d.h.v. std functies
    time_t t = time(0);
    m_rand->SetSeed(dis(gen)*t);
    m_rand->Sphere( m_xdir, m_ydir , m_zdir ,1.);

}
//destructor
neutron::~neutron(){

}


const double neutron::get_energie() const{
    return m_energie;
}

void neutron::elasticscat(const double M){   //in MeV
    double new_xdir ;
    double new_ydir ;
    double new_zdir ;
    m_rand->Sphere( new_xdir, new_ydir , new_zdir ,1.);
    double costheta = m_xdir*new_xdir + m_ydir*new_ydir + m_zdir*new_zdir ;
    m_energie = m_energie*((1.-(costheta*costheta))*(((m_neutron - M)/(m_neutron + M))*((m_neutron - M)/(m_neutron + M))-1.)+1.);
    m_xdir = new_xdir ;
    m_ydir = new_ydir ;
    m_zdir = new_zdir ;
}

void neutron::change_position(double dist){
    double xchange = m_xdir*dist;
    double ychange = m_ydir*dist;
    double zchange = m_zdir*dist;

    m_xpos = m_xpos + xchange;
    m_ypos = m_ypos + ychange;
    m_zpos = m_zpos + zchange;

}

vector<double> neutron::get_pos(){
    vector<double> pos{ m_xpos ,  m_ypos ,  m_zpos} ;
    return pos ;
}

vector<double> neutron::get_dir(){
    vector<double> dir{ m_xdir ,  m_ydir ,  m_zdir} ;
    return dir ;
}

void neutron::set_dir(vector<double> vec){    //nodig als trukje in evolve
    m_xdir = vec[0];
    m_ydir = vec[1];
    m_zdir = vec[2];
}
