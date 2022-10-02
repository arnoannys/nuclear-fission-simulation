// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#ifndef CILINDER_H
#define CILINDER_H

#include "kern.h"


class cilinder: public kern{

   public:
    //constructor
    cilinder(const double , const double);
    //destructor
    ~cilinder();

    virtual const double get_volume() const ;
    virtual std::vector<double> get_rndm_point();
    virtual bool is_inside(std::vector<double>);
    void set_radius(double);
    void set_height(double);
    double get_radius();
    double get_height();
   private:

    double m_radius ;
    double m_height ;

};

#endif // CILINDER_H
