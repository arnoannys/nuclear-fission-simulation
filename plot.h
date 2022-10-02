// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021

#ifndef PLOT_H
#define PLOT_H
#include <vector>
#include <string>
class plot{

   public:
    //constructor
    plot();
    //destructor
    ~plot();
    void vec_image(std::vector<double>,std::vector<double>, std::string, std::string) ;
    void vec_image2(std::vector<double>,std::vector<double>, std::string, std::string) ;
    private:

};


#endif // PLOT_H
