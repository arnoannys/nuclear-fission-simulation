// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#include <iostream>
#include <vector>
#include <cmath>
#include "math.h"
#include "neutron.h"
#include "isotoop.h"
#include "kern.h"
#include "bol.h"
#include "cilinder.h"
#include "plot.h"
using namespace std;


int main(){
//zuiver water
{
    double m = 10000. ;
    double v = (m/1000.)*1000. ;
    cilinder cil(cbrt(v/M_PI)+0.00001 , cbrt(v/M_PI)+0.00001) ; // (R ,h)
    cil.add_water(m);
    cout << "R " << cil.evolve(20000,2500,250,"single","watertank","im6.png") << endl ; //(max aantal neutronen, initieel aantalneutronen, max aantal tijdstappen)
    cout<< "cilinder met 10L water, straal en hoogte in cm: " << cil.get_radius() << " en " << cil.get_height() << endl ;
}
//zuiver water
{
    double m = 100000. ;
    double v = (m/1000.)*1000. ;
    cilinder cil(cbrt(v/M_PI) +0.00001, cbrt(v/M_PI) +0.00001) ; // R h
    cil.add_water(m);
    cout << "R " << cil.evolve(20000,2500,250,"single","watertank","im7.png") << endl ;
    cout<< "cilinder met 100L water, straal en hoogte in cm: " << cil.get_radius() << " en " << cil.get_height() << endl ;
}
//zout1
{
     double m = 10000. ;
     double mz = 1000. ;
     double v = (m/1000.)*1000. ;
     cilinder cil(cbrt(v/M_PI)+0.00001 , cbrt(v/M_PI)+0.00001) ; // R h
     cil.add_water(m-mz);
     cil.add_zout1(mz);
     cout << "R " << cil.evolve(10000,2500,250,"single","10L watertank en 1kg zout 1","im8.png") << endl ;
     cout<< "cilinder met 10L water, straal en hoogte in cm: " << cil.get_radius() << " en " << cil.get_height() << endl ;
}
{
     double m = 10000. ;
     double mz = 100. ;
     double v = (m/1000.)*1000. ;
     cilinder cil(cbrt(v/M_PI)+0.00001 , cbrt(v/M_PI)+0.00001) ; // R h
     cil.add_water(m-mz);
     cil.add_zout1(mz);
     cout << "R " << cil.evolve(10000,2500,250,"single","10L watertank en 0.1kg zout 1","im9.png") << endl ;
     cout<< "cilinder met 10L water, straal en hoogte in cm: " << cil.get_radius() << " en " << cil.get_height() << endl ;
}
{
     vector<double> mass ;
     vector<double> R;
     cilinder cil(14.72,14.72) ;
     for( double mz = 0. ; mz <1500. ; mz+=  250.){ //loop over massas
        cil.clear();
        cil.add_water(10000.-mz);
        cil.add_zout1(mz);
        R.push_back(cil.evolve(10000,500,100,"","","")) ;
        mass.push_back(mz) ;
        }
     plot plt;
     plt.vec_image2(mass , R , "watertank met zout 1" , "im10.png");
}
//zout2
{
     double m = 10000. ;
     double mz = 1000. ;
     double v = (m/1000.)*1000. ;
     cilinder cil(cbrt(v/M_PI)+0.00001 , cbrt(v/M_PI)+0.00001) ; // R h
     cil.add_water(m-mz);
     cil.add_zout2(mz);
     cout << "R " << cil.evolve(10000,1000,100,"single","10L watertank en 1kg zout 2","im11.png") << endl ;
     cout<< "cilinder met 10L water, straal en hoogte in cm: " << cil.get_radius() << " en " << cil.get_height() << endl ;
}
{
     double m = 10000. ;
     double mz = 100. ;
     double v = (m/1000.)*1000. ;
     cilinder cil(cbrt(v/M_PI)+0.00001 , cbrt(v/M_PI)+0.00001) ; // R h
     cil.add_water(m-mz);
     cil.add_zout2(mz);
     cout << "R " << cil.evolve(10000,1000,100,"single","10L watertank en 0.1kg zout 2","im12.png") << endl ;
     cout<< "cilinder met 10L water, straal en hoogte in cm: " << cil.get_radius() << " en " << cil.get_height() << endl ;
}
{
     vector<double> mass ;
     vector<double> R;
     cilinder cil(14.72,14.72) ;
     for( double mz = 0. ; mz <1500. ; mz+=  250.){ //loop over massas
         cil.clear();
         cil.add_water(10000.-mz);
         cil.add_zout2(mz);
         R.push_back(cil.evolve(10000,500,100,"","","")) ;
         mass.push_back(mz) ;
         }
     plot plt;
     plt.vec_image2(mass , R , "watertank met zout 2" , "im13.png");
}

return 0;
}


