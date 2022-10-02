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
    cout << "main 1" << endl ;
//DEEL1
{
    isotoop uranium0(100000.,"U","235") ; //massa in gram
    uranium0.read_CRS("Fis");
    bol bol0(  cbrt(3./(M_PI*4.)*(uranium0.get_volume())*1000.) +0.00001 ); // straal uit volume uranium en extra speling om numerieke fout te coveren
    cout<< "straal van bol uranium 100kg in cm: " << bol0.get_radius() << endl ;
    bol0.add_isotope("uranium235",&uranium0);
    double R = bol0.evolve(10000,2500,100,"single","bol uranium m = 100 kg" , "im0.png") ; //(max aantal neutronen, initieel aantalneutronen, max aantal tijdstappen)
    cout << "Reproductiegetal van bol uranium 100kg: "<< R << endl ;

    isotoop uranium1(600000.,"U","235") ; //massa in gram
    uranium1.read_CRS("Fis");
    bol bol1(  cbrt(3./(M_PI*4.)*(uranium1.get_volume())*1000.) +0.00001 );
    cout<< "straal van bol uranium 600kg in cm: " << bol1.get_radius() << endl ;
    bol1.add_isotope("uranium235",&uranium1);
    R = bol1.evolve(10000,2500,100,"single","bol uranium m = 600 kg", "im1.png") ;
    cout<< "Reproductiegetal van bol uranium 600kg: " << R << endl ;

    isotoop uranium2(1000000.,"U","235") ; //massa in gram
    uranium2.read_CRS("Fis");
    bol bol2(  cbrt(3./(M_PI*4.)*(uranium2.get_volume())*1000.) +0.00001 );
    cout<< "straal van bol uranium 1000kg in cm: "<< bol2.get_radius() << endl ;
    bol2.add_isotope("uranium235",&uranium2);
    R = bol2.evolve(10000,2500,100,"single","bol uranium m = 1000 kg", "im2.png") ;
    cout<< "Reproductiegetal van bol uranium 1000kg: " << R << endl ;
}
{
    vector<double> mass ;
    vector<double> R;
    bol bol3(1.) ;
    for( double m = 0. ; m <1400000. ; m+=  200000.){ //loop over massas
        isotoop *uranium = new isotoop(m,"U","235") ; //massa in gram
        uranium->read_CRS("Fis");

        bol3.clear();
        bol3.set_radius(cbrt(3./(M_PI*4.)*(uranium->get_volume())*1000.) +0.00001 );
        bol3.add_isotope("uranium235",uranium);
        R.push_back(bol3.evolve(10000,2500,100,"","","")) ;
        mass.push_back(m) ;
        delete uranium;
    }
    plot plt;
    plt.vec_image2(mass , R , "bol uranium" , "im3.png");
}
//DEEL2
//zout 1
{
    vector<double> mass ;
    vector<double> R;
    bol bol1(1.) ;
    for( double m = 0. ; m <2000000. ; m+=  250000.){
        double v = (m/4870.)*1000. ;
        bol1.clear();
        bol1.set_radius(  cbrt(3./(M_PI*4.)*v)+0.00001);
        bol1.add_zout1(m);
        R.push_back(bol1.evolve(10000,2500,100,"","","")) ;
        mass.push_back(m) ;
        }
     plot plt;
     plt.vec_image2(mass , R , "bol zout 1" , "im4.png");
}
{
     double m = 1500000.;
     double v = (m/4870.)*1000. ;
     bol bol0(cbrt(3./(M_PI*4.)*v)+0.00001);
     cout<< "straal van bol zout1 1500kg in cm: " << bol0.get_radius() << endl ;
     bol0.add_zout1(m);
     double R = bol0.evolve(10000,2500,100,"single","bol zout1 m = 1500 kg" , "im4.1.png") ;
     cout << "Reproductiegetal van bol zout1  1500kg: "<< R << endl ;
}
{
     double m = 50000.;
     double v = (m/4870.)*1000. ;
     bol bol0(cbrt(3./(M_PI*4.)*v)+0.00001);
     cout<< "straal van bol zout1 50kg in cm: " << bol0.get_radius() << endl ;
     bol0.add_zout1(m);
     double R = bol0.evolve(10000,2500,100,"single","bol zout1 m = 50 kg" , "im4.2.png") ;
     cout << "Reproductiegetal van bol zout1  50kg: "<< R << endl ;
}
//zout 2
{
     vector<double> mass ;
     vector<double> R;
     bol bol1(1.) ;
     for( double m = 0. ; m <250000. ; m+=  50000.){
         double v = (m/5100.)*1000. ;
         bol1.clear();
         bol1.set_radius(  cbrt(3./(M_PI*4.)*v)+0.00001);
         bol1.add_zout2(m);
         R.push_back(bol1.evolve(10000,2500,100,"","","")) ;
         mass.push_back(m) ;
         }
      plot plt;
      plt.vec_image2(mass , R , "zout 2  bol" , "im5.png");
}
{
     double m = 500000.;
     double v = (m/5100.)*1000. ;
     bol bol0(cbrt(3./(M_PI*4.)*v)+0.00001);
     cout<< "straal van bol zout2 500kg in cm: " << bol0.get_radius() << endl ;
     bol0.add_zout2(m);
     double R = bol0.evolve(10000,2500,100,"single","bol zout2 m = 500 kg" , "im5.1.png") ;
     cout << "Reproductiegetal van bol zout2  500kg: "<< R << endl ;
}
{
     double m = 50000.;
     double v = (m/5100.)*1000. ;
     bol bol0(cbrt(3./(M_PI*4.)*v)+0.00001);
     cout<< "straal van bol zout2 50kg in cm: " << bol0.get_radius() << endl ;
     bol0.add_zout2(m);
     double R = bol0.evolve(10000,2500,100,"single","bol zout2 m = 50 kg" , "im5.2.png") ;
     cout << "Reproductiegetal van bol zout2  50kg: "<< R << endl ;
}
return 0;
}


