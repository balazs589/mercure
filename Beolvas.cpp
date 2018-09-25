#include <iostream>
#include <stdlib.h>

#include "Beolvas.h"

using namespace std;

namespace mercure
{

/*****************************************************************************/
//a Beolvas fuggveny egy a hazi feladat leirasanak megfelelo, parameterkent
//megkapott szoveges fajl feldolgozasat vegzi
//visszateresi ertekkent egy a kiolvasott kezdeti ertekekeket tartalmazo
//tombokre mutato pointert ad
//referenciakon keresztul visszaadja a feladatok szamat
//es a kivalasztott modszert is

//(a fuggveny nincs felkeszitve a nem megfelelo formatumot tartalmazo fajlok kezelesere:
//kizarolag a hazi feladatban szereplo formatumot varja egyebb esetben hibauzenetet nem ad)
/*****************************************************************************/

double** Beolvas(ifstream& infile, ModszerValaszto& _Modszer, int& _FeladatokSzama)
{
    ModszerValaszto Modszer = RK4;      //alapertelmezett modszer Runge-Kutta4

    int SorokSzama = 0;             //csak az ertekes sorokat szamoljuk
    int FeladatokSzama = 0;         //kezdeti ertekeket tartalmazo sorok szama

    int ModszerSor = 0;             //ha van opcionalisan megadott modszervalasztas
                                    //a 3. sorban ModszerSor erteke 1 lesz

    while(infile)
    {
        string Sor;
        getline(infile, Sor);                           //beolvasunk egy sort
        Sor = Sor.substr(0, Sor.find_first_of('#') );   //elhagyjuk a kommenteket

        //maj megszabadulunk az esetleges sorvegei whitespace -ektol:
        if(Sor.find_last_not_of(" \t\f\v\n\r") == string::npos)
        {
            Sor.clear();
        }

        //ha ezutan marad valami, akkor azt ertekes sorkent ertelmezzuk:
        if(Sor.length() != 0)
        {
            SorokSzama++;           //szamoljuk ezeket
            if(SorokSzama == 1)     //az elso sor tartalmat osszevetjuk a feleadatban szereplo ertekkel
            {
                if(Sor == "Programozas 2. 2012. II. hazi feladat")
                {
                    cout << Sor << endl;
                    cerr << "Az elso sor megegyezik a megadott szoveggel." << endl;
                }
                else
                {
                    cerr << "Az elso sor nem egyezik a megadott ertekkel." << endl;
                    break;
                }
            }

            if(SorokSzama == 3)         //megvizsgaljuk, hogy a 3. sor tartalmaz-e modszervalasztast
            {
                if(Sor[0] == '-')       // ha igen akkor a hasznalt modszert ennek alapjan modositjuk
                {
                    if(Sor[2] == 'e') Modszer = EULER;
                    if(Sor[2] == '2') Modszer = RK2;
                    if(Sor[2] == '4') Modszer = RK4;

                    ModszerSor = 1;     //es jelezzuk, hogy nem 2 hanem 3 nem kezdeti erteket
                                        //tartalmazo ertekes sor van a fajl elejen
                }
            }
        }
    }
    //osszeszamoltuk az eretekes sorokat
    //ezaltal ismerjuk a megoldando feladatok szamat:

    FeladatokSzama = SorokSzama - 2 - ModszerSor;

    double** KezdetiErtekek;
    KezdetiErtekek = new double*[FeladatokSzama];   //ennek megfeleo szamu tombunk lesz
                                                    //darabonkent 6 elemmel

    for(int iii = 0; iii < FeladatokSzama; iii++)
    {
        KezdetiErtekek[iii] = new double[6];
    }

    infile.clear();                 //
    infile.seekg(0, ios::beg);      //a beolvasast ujra a fajl elejetol kezdjuk

    SorokSzama = 0;                 //az eddigi valtozokat seged valtozokent hasznaljuk
    FeladatokSzama = 0;             //

    while(infile)
    {
        string Sor;
        getline(infile, Sor);
        Sor = Sor.substr(0, Sor.find_first_of('#') );

        if(Sor.find_last_not_of(" \t\f\v\n\r") == string::npos)
        {
            Sor.clear();
        }
                                //elvegezzuk a sorok fentivel egyezo beolvasasat
        if(Sor.length() != 0)
        {
            SorokSzama++;       //szamoljuk hogy hol tartunk

            if(SorokSzama > 2 + ModszerSor)     //modszervalasztas tenyetol fuggoen
                                                // a 2. vagy 3. sortol kezdeti ertekekkent ertelmezzuk a tovabbi ertekes sorokat
            {
                string Sor2;

                //a beolvasott sorokbol az elejuktol a vegukig fele haladva
                //egymas utan kiemeljuk az '=' jeltol a ',' -ig tarto reszeket
                //amelyeket utana (a megadott sorrend szerint) kezdeti ertekkent
                //ertelemzunk

                Sor = Sor.substr(Sor.find_first_of('=') + 1);
                Sor2 = Sor.substr(0, Sor.find_first_of(',') );
                KezdetiErtekek[FeladatokSzama][0] = atof(Sor2.c_str());     //tmax

                Sor = Sor.substr(Sor.find_first_of('=') + 1);
                Sor2 = Sor.substr(0, Sor.find_first_of(',') );
                KezdetiErtekek[FeladatokSzama][1] = atof(Sor2.c_str());     //dt

                Sor = Sor.substr(Sor.find_first_of('=') + 1);
                Sor2 = Sor.substr(0, Sor.find_first_of(',') );
                KezdetiErtekek[FeladatokSzama][2] = atof(Sor2.c_str());     //x0

                Sor = Sor.substr(Sor.find_first_of('=') + 1);
                Sor2 = Sor.substr(0, Sor.find_first_of(',') );
                KezdetiErtekek[FeladatokSzama][3] = atof(Sor2.c_str());     //y0

                Sor = Sor.substr(Sor.find_first_of('=') + 1);
                Sor2 = Sor.substr(0, Sor.find_first_of(',') );
                KezdetiErtekek[FeladatokSzama][4] = atof(Sor2.c_str());     //vx0

                Sor = Sor.substr(Sor.find_first_of('=') + 1);
                Sor2 = Sor.substr(0, Sor.find_first_of(',') );
                KezdetiErtekek[FeladatokSzama][5] = atof(Sor2.c_str());     //vy0

                FeladatokSzama++;       //ujra szamoljuk a feladatokat
            }
        }
    }
    //melyek szamat a beolvasas elvegzese utan referencian keresztul adjuk vissza

    _FeladatokSzama = FeladatokSzama;       //fealadatok szama referenciakent
    _Modszer = Modszer;                     //modszer referenciakent
    return KezdetiErtekek;                  //rogzitett adatokat tartalmazo tombokre mutato pointer
}

}
