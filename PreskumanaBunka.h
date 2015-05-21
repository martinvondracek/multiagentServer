/* 
 * File:   PreskumanaBunka.h
 * Author: root
 *
 * Created on Nedeľa, 2015, marec 29, 9:37
 * 
 * for saving covered / uncovered area
 */

#ifndef PRESKUMANABUNKA_H
#define	PRESKUMANABUNKA_H

class PreskumanaBunka {
public:
    PreskumanaBunka(int id, int idSpustenia, int x0, int y0, int radius, int n, int rozmerBunky, int k, int l, bool obsadene);
    
    virtual ~PreskumanaBunka();

    int GetId();
    void SetId(int id);
    int GetIdSpustenia();
    void SetIdSpustenia(int idSpustenia);
    int GetK();
    void SetK(int k);
    int GetL();
    void SetL(int l);
    int GetN();
    void SetN(int n);
    bool IsObsadene();
    void SetObsadene(bool obsadene);
    int GetRadius();
    void SetRadius(int radius);
    int GetRozmerBunky();
    void SetRozmerBunky(int rozmerBunky);
    int GetX0();
    void SetX0(int x0);
    int GetY0();
    void SetY0(int y0);

private:
    int id;
    int idSpustenia;
    int x0;
    int y0;
    int radius;
    int n;
    int rozmerBunky;
    int k; //riadok
    int l; //stlpec
    bool obsadene;
};

#endif	/* PRESKUMANABUNKA_H */

