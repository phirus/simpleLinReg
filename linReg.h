#ifndef LINREG_H
#define LINREG_H

#include<vector>
#include<cmath>
#include<iostream>
#include<fstream>

typedef std::vector<double> vec;
/// lineare Regression nach der Beschreibung im Bronstein(S. 804)

class LinReg
{
    public:
    LinReg():a(0),b(0),sigma2(0),meanX(0),meanY(0){};
    LinReg(const vec& X, const vec& Y);

    /// set methods
    void setXY(const vec& X, const vec& Y);

    /// get methods
    const double getA()const{return a;};
    const double getB()const{return b;};
    const double getSigma()const{return sigma2;};
    const vec getX()const{return x;};
    const vec getY()const{return y;};
    const double calcCor()const; /// <- empirischer Korrelationskoeffizient R² (16.152b)

    private:
    vec x,y;
    double a,b,sigma2;
    double meanX,meanY;

    /// inernal calculations
    void calcMean(); /// <- berechnet die Mittelwerte
    const double calcSy2()const; /// <- mittlere quadratische Abweichung (16.155b)
    void calcsigma2();          /// <- berechnet die Streuung
    void calcAB();
    void calculate(); /// <- Zusammenfassung
};

LinReg readFile(std::string filename);

#endif
