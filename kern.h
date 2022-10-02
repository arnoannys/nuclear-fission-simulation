// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#ifndef KERN_H
#define KERN_H

#include <vector>
#include <TRandom.h>
#include <TRandom3.h>
#include <map>
#include<string>
#include <TF1.h>
#include <cmath>
#include <math.h>
#include "isotoop.h"
#include "neutron.h"
#include "plot.h"
class kern{

   public:

    virtual const double get_volume() const = 0;
    virtual std::vector<double> get_rndm_point() = 0;
    virtual bool is_inside(std::vector<double>) = 0;
    void clear();                                       //leegmaken maps en vulling
    const double control(double) ;
    void make_rndm_gen() ;
    TRandom3* m_rand ;                                  //public want probleem als deze private
    void add_isotope(std::string , isotoop*);
    void add_water(double ) ;
    void add_zout1(double ) ;
    void add_zout2(double ) ;
    void list_contents() ;
    double fision_energy() ;
    double evolve(int,int,int,std::string,std::string,std::string);

   private:
     std::multimap<std::string, isotoop*> iso_map ;
     std::multimap<int,neutron*> neut_map ;
     double m_vulling = 0.;
     const double Emin = 0;
     const double Emax = 20; // uitzonderlijk in MeV , wordt later omgezet naar eV
     TF1 *f = new TF1("fissionfunction", "3.*sqrt((1.5/3.1415)*x)*pow(1.98,-3./2.)*exp(-1.5*x/1.98)", Emin, Emax);


};


#endif // KERN_H
