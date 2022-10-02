// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#ifndef BOL_H
#define BOL_H

#include "kern.h"


class bol: public kern{

   public:
    //constructor
    bol(const double);
    //destructor
    ~bol();

    virtual const double get_volume() const ;
    virtual std::vector<double> get_rndm_point() ;
    virtual bool is_inside(std::vector<double>);
    double get_radius();
    void set_radius(double);

   private:

    double m_radius ;


};

#endif // BOL_H
