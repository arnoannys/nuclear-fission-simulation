// ARNO ANNYS
// arno.annys@student.uantwerpen.be
// 31/03/2021


#include "kern.h"
#include <iostream>
#include <numeric>
#include <random>
using namespace std;

void kern::clear(){
    iso_map.clear();
    neut_map.clear();
    m_vulling = 0;
}
const double kern::control(double a){
    if (a <= 0)  {
        cout << "dimension must be > 0, double set to 1" << endl;
        return 1.;
    }
    else return a;
 }

void kern::make_rndm_gen(){
    m_rand  = new TRandom3();
    time_t t = time(0);
    m_rand->SetSeed(t);

}

void kern::add_isotope(string name,isotoop* iso){
    if(m_vulling + iso->get_volume() > get_volume()){                       //hoeveelheid al vol en nieuw volume vs. beschikbaar
    cout << "could not add " << name << " exceeds volume" << endl;
    }
    else{
    m_vulling = m_vulling + iso->get_volume() ;                             //aanpassing vulling beschikbaar volume
    iso_map.insert(pair<string,isotoop*>(name,iso)) ;                       // toevoegen aan map met alle isotopen
    }
}

void kern::add_water(double mass_mol){
    double volume_water = mass_mol/1000. ;
    if(m_vulling + volume_water > get_volume()){
    cout << "could not add water,  exceeds volume" << endl;
    }
    else{
    m_vulling = m_vulling + volume_water ;
    isotoop *hydrogen = new isotoop(2./18.*mass_mol,"H","1");        //aanmaken isotopen volgens verhouding nucleaire massa
    hydrogen->read_CRS("Cap");                                       //inlezen vectoren crosssections
    hydrogen->read_CRS("El");
    iso_map.insert(pair<string,isotoop*>("H1" , hydrogen));

    isotoop *oxygen = new isotoop(16./18.*mass_mol,"O","16");
    oxygen->read_CRS("Cap");
    oxygen->read_CRS("El");
    iso_map.insert(pair<string,isotoop*>("O16" , oxygen));}


}

void kern::add_zout1(double mass_mol){
    double volume_zout = mass_mol/4870. ;
    if(m_vulling + volume_zout > get_volume()){
    cout << "could not add salt 1,  exceeds volume" << endl;
    }
    else{
    m_vulling = m_vulling + volume_zout ;
    double tot = 235.+3.*35.+37. ;
    isotoop *chloor35 = new isotoop(mass_mol*(3.*35.+37.)*0.7577/tot,"Cl","35");          //in rekening brengen isotopische abundaties chloor 35 vs 37
    chloor35->read_CRS("Cap");
    chloor35->read_CRS("El");
    iso_map.insert(pair<string,isotoop*>("Cl35" , chloor35));

    isotoop *chloor37 = new isotoop(mass_mol*(3.*35.+37.)*0.2423/tot,"Cl","37");
    chloor37->read_CRS("Cap");
    chloor37->read_CRS("El");
    iso_map.insert(pair<string,isotoop*>("Cl37" , chloor37));

    isotoop *uranium = new isotoop(mass_mol*235./tot, "U","235");
    uranium->read_CRS("Fis");
    iso_map.insert(pair<string,isotoop*>("U235" , uranium));
    }
}

void kern::add_zout2(double mass_mol){
    double volume_zout = mass_mol/5100. ;
    if(m_vulling + volume_zout > get_volume()){
    cout << "could not add salt 2,  exceeds volume" << endl;
    }
    else{
    m_vulling = m_vulling + volume_zout ;
    double tot = (19.+16.)*2. + 235.;

    isotoop *uranium = new isotoop(mass_mol*235./tot, "U","235");
    uranium->read_CRS("Fis");
    iso_map.insert(pair<string,isotoop*>("U235" , uranium));

    isotoop *oxygen = new isotoop(mass_mol*2.*16./tot, "O","16");
    oxygen->read_CRS("Cap");
    oxygen->read_CRS("El");
    iso_map.insert(pair<string,isotoop*>("O16" , oxygen));

    isotoop *fluorine = new isotoop(mass_mol*2.*19./tot, "F","19");
    fluorine->read_CRS("Cap");
    fluorine->read_CRS("El");
    iso_map.insert(pair<string,isotoop*>("F19" , fluorine));}


}


void kern::list_contents(){
    multimap<string,isotoop*>::iterator it;
    multimap<string,isotoop*>::iterator end_it = iso_map.end();
    for (it = iso_map.begin(); it != end_it; ++it){
        cout << it->first <<  endl  ;
    }

}

double kern::fision_energy(){
    double rand_E = f->GetRandom(Emin,Emax) ;
    return rand_E;
}

double kern::evolve(int max_amount, int init_amount, int maxsteps, string MODE, string title, string filename){
    double V = get_volume()*1000.; //L to cm3 //totaal volume kern
    random_device device;          // verder nodig voor kiezen reactie adhv crosssection
    mt19937 engine(device()) ;
    vector<double> reproductionnumber ; //reproductie van elke stap , wordt later uitgemiddeld
    vector<double> stepsvec ;           //nummer elke stap
    vector<double> neutronvec ;         //vector met aantal neutronen in elke stap
    for( int count = 0; count < init_amount; count++){   //loop aanmaken initieel aantal neutronen
        vector<double> pos = get_rndm_point();
        neutron *neut = new neutron(fision_energy()*1000000.,pos[0],pos[1],pos[2]) ;
        //er wordt van uit gegaan dat de initiele neutronen enrgie verdeling volgens fissie hebben , plus omzetting MeV tot eV
        neut_map.insert(pair<int,neutron*>(count,neut)) ;
    } 
    multimap<int,neutron*>::iterator it_n;  //iterator alle neutronen in de map
    multimap<int,neutron*>::iterator end_it_n = neut_map.end();  //iterator naar einde zodat niet elke loop stap keer gezocht moet worden
    int t = 0 ;
    int neutronnumber = init_amount;
    int size = neut_map.size() ;
    stepsvec.push_back(t) ;
    neutronvec.push_back(size) ;  //eertse values in vector

   while( size < max_amount && size > 0 && t< maxsteps){   //loop tot maximaal of geen neutronen of te veel tijdstappen in geval R = 1
        multimap<string,isotoop*>::iterator it_iso;        //iterator alle isotopen in map
        multimap<string,isotoop*>::iterator end_it_iso = iso_map.end(); //iterator naar einde zodat niet elke loop stap keer gezocht moet worden
        multimap<int,neutron*> new_neut_map ;  //map met alle neutronen die naar de volgende tijdstap mee mogen
        for (it_n = neut_map.begin(); it_n != end_it_n; ++it_n){   //loop die voor elk neutron een tijdstap zet
            vector<double> CRS ;                                   //vector met crosssecties alle mogelijke reacties
            vector<string> reaction ;                              // 3 vectoren die even lang zijn als de vector met alle mogelijke crosssectns
            vector<string> isotoopname ;                           //wanneer dan een crossec gekozen is kan adhv de index de matchende reactie
            vector<string> isotoopnummer ;                         // en isotoop gevonden worden
            vector<double> termen ;                                // zal gebruikt worden om de som over alle crossec in grote sigma te doen
            for(it_iso = iso_map.begin() ; it_iso != end_it_iso; ++it_iso){  //loop die de vectoren met crosssec en reactie types vult
                double CRS_tot =  ((it_iso->second)->get_CRS_tot((it_n->second)->get_energie()))*1.0e-24; //barn to cm2 totale crossec
                double N_deeltjes = (it_iso->second)->get_aantaldeeltjes() ;
                termen.push_back(CRS_tot*N_deeltjes/V) ; //in de som zetten
                CRS.push_back(N_deeltjes*(it_iso->second)->get_CRS("Cap",((it_n->second)->get_energie()))) ; //zet de capture CRS in de vector
                reaction.push_back("Cap");                                                        // houd bij dat deze CRS een cap was
                isotoopname.push_back((it_iso->second)->get_element());                           // houd bij aan welk element er cap was
                isotoopnummer.push_back((it_iso->second)->get_isonummer());                       //houd bij aan welk isotoop er cap was
                CRS.push_back(N_deeltjes*(it_iso->second)->get_CRS("El",((it_n->second)->get_energie()))) ;  //idem
                reaction.push_back("El");
                isotoopname.push_back((it_iso->second)->get_element());
                isotoopnummer.push_back((it_iso->second)->get_isonummer());
                CRS.push_back(N_deeltjes*(it_iso->second)->get_CRS("Fis",((it_n->second)->get_energie()))) ;
                reaction.push_back("Fis");
                isotoopname.push_back((it_iso->second)->get_element());
                isotoopnummer.push_back((it_iso->second)->get_isonummer());
            }
           double SIGMA = accumulate(termen.begin(),termen.end(), 0.0) ; //som uitvoeren
           double lambda = 1./SIGMA ; //cm
           discrete_distribution<> dist(CRS.begin(), CRS.end()) ; // disctrete distributie crossecties
           int picked = (dist(engine)) ;                          // kies er een met kans volgens CRS
           string dummy_str = reaction[picked] ;                  // nu uit eerdere vectoren halen waar deze CRS mee overeenkomt
           (it_n->second)->change_position(lambda) ;              //positie aanpassen
           if (is_inside((it_n->second)->get_pos()) == 0){        //controleer nog in kern
               dummy_str = "out" ;                                //als er uit zorgen dat volgende if else statements niet voldaan worden
               delete (it_n->second) ;                            //verwijderer neutron
           }

           if (dummy_str == "Cap"){
                delete it_n->second ;
           }
           else if (dummy_str == "El"){
                /* nu zou het best zijn het neutron dat elastic scattered gewoon aan te passen en te houden, dit kreeg ik niet werkend
                 de pointer naar het neutron is na de for loop nog wel hetzelfde maar de energie , postie , ... zijn allemaal nul geworden
                 het lijkt me niet dat het neutron uit de scope is want het was al veel eerder aangemaakt, daarom wordt gekozen voor de
                 mindere optie om en nieuw neutron aan te maken met zelfde energie, positie en richting.
                 */
                isotoop *dummy_iso = (iso_map.find(isotoopname[picked] + isotoopnummer[picked]))->second ;
                //iterator over isotopen al uit scope dus via omweg het istoop waaraan gescatterd was vinden
                (it_n->second)->elasticscat(dummy_iso->get_nuc_massa_ev()) ;
                neutron *neut = new neutron((it_n->second)->get_energie(),((it_n->second)->get_pos())[0],((it_n->second)->get_pos())[1],((it_n->second)->get_pos())[2]) ;
                neut->set_dir((it_n->second)->get_dir());
                new_neut_map.insert(pair<int,neutron*>(it_n->first,neut)) ; // mee nemen volgende stap
           }
           else if (dummy_str == "Fis"){
                vector<double> pos = (it_n->second)->get_pos() ; //positie bijhouden om hier de nieuwe neutronen te starten
                delete it_n->second ;

               double dummy = m_rand->Uniform(0,1) ;
               if (dummy < 0.59){   //2 of 3 met gemiddeld 2.41 maken
                   for( int count = 0; count < 2; count++){
                       neutronnumber++;
                       neutron *neut = new neutron(fision_energy()*1000000.,pos[0],pos[1],pos[2]) ;
                       new_neut_map.insert(pair<int,neutron*>(neutronnumber,neut)) ;
                   }
               }
               else{
                   for( int count = 0; count < 3; count++){
                       neutronnumber++ ;
                       neutron *neut = new neutron(fision_energy()*1000000.,pos[0],pos[1],pos[2]) ;
                       new_neut_map.insert(pair<int,neutron*>(neutronnumber ,neut)) ;
                   }
               }


           }

       } // end loop neutronrn
       t++ ;
       double startamount = neut_map.size() ;
       double restingamount = new_neut_map.size() ;
       double r = restingamount/startamount ;
       reproductionnumber.push_back(r) ;
       neut_map = new_neut_map ;
       new_neut_map.clear() ;
       size = neut_map.size() ;
       stepsvec.push_back(t) ;
       neutronvec.push_back(size) ;
    } //end while loop
   if(MODE == "single"){
    plot plt ;
    plt.vec_image(stepsvec , neutronvec, title, filename);
   }
    double mean_reprd = (accumulate(reproductionnumber.begin(),reproductionnumber.end(), 0.0))/(reproductionnumber.size());
  return mean_reprd;
}
