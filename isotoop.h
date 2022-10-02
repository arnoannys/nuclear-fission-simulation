// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#ifndef ISOTOOP_H
#define ISOTOOP_H

#include <string>
#include <vector>
#include <map>

class isotoop{


   public:
    //constructor
    isotoop(const double ,std::string,std::string);
    //destructor
    ~isotoop();

    void read_CRS(std::string);
    double get_volume();
    double get_aantaldeeltjes() ;
    double get_massa() ;
    double get_nuc_massa_ev() ;
    double get_CRS(std::string, double  );
    double get_CRS_tot(double );
    const double control(double) ;
    std::string get_element();
    std::string get_isonummer();
   private:

    std::map<std::string, double> massas_map ;     //maps die als soort database dienen
    std::map<std::string, double> density_map ;
    const double m_massa;
    double nuc_massa;
    double density;
    double volume;
    double aantal_deeltjes;

    const std::string m_element;                    //string die isotoop karakteriseren
    const std::string m_isotoop;


    std::vector<double> m_cap_crs;                  // vectoren met data van energie en crosssection
    std::vector<double> m_cap_E;

    std::vector<double> m_fis_crs;
    std::vector<double> m_fis_E;

    std::vector<double> m_el_crs;
    std::vector<double> m_el_E;
};



#endif // ISOTOOP_H
