// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021



#ifndef NEUTRON_H
#define NEUTRON_H
#include <TROOT.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <cmath>
#include <math.h>
#include <random>
class neutron{

   public:
    //constructor
    neutron(double , const double xpos, const double ypos , const double zpos);
    //destructor
    ~neutron();

     const double get_energie() const;
     void elasticscat(const double M) ;
     void change_position(double);
     std::vector<double> get_pos() ;
     std::vector<double> get_dir() ;
     void set_dir(std::vector<double>);
   private:
    const double m_neutron = 939.56563e6 ; //eV
    double m_energie ;
    double m_xpos;
    double m_ypos;
    double m_zpos;
    double m_xdir;
    double m_ydir;
    double m_zdir;
    TRandom3* m_rand ;

};

#endif // NEUTRON_H

