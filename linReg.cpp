#include"linReg.h"

LinReg::LinReg(const vec& X, const vec& Y):a(0),b(0),sigma2(0){
    if(X.size() == Y.size()){
        x=X;
        y=Y;
    }
    else throw "vector-size mismatch";
    calculate();
};

void LinReg::setXY(const vec& X, const vec& Y){
    if(X.size() == Y.size()){
        x=X;
        y=Y;
    }
    else throw "vector-size mismatch";
    calculate();
};

void LinReg::calcMean(){
    meanX = 0;
    if(x.empty() == false){
        for (std::vector<double>::const_iterator it = x.begin() ; it != x.end(); it++){
            meanX += *it;
        }
        meanX /= x.size();
    }

    meanY = 0;
    if(y.empty() == false){
        for (std::vector<double>::const_iterator it = y.begin() ; it != y.end(); it++){
            meanY += *it;
        }
        meanY /= y.size();
    }
};

const double LinReg::calcSy2()const{
    double sy2 = 0;
    if(y.size() > 1){
        for (std::vector<double>::const_iterator it = y.begin() ; it != y.end(); it++){
            sy2 += (*it - meanY) * (*it - meanY);
        }
        sy2 /= y.size()-1;
    }
    return sy2;
};

const double LinReg::calcCor()const{
    double rxy2;
    double lowerX=0, lowerY=0, upper=0; // different sums
    int max = x.size();
    for (int i = 0; i<max; i++){
        upper += (x[i] - meanX) * (y[i] - meanY);
        lowerX += (x[i] - meanX) * (x[i] - meanX);
        lowerY += (y[i] - meanY) * (y[i] - meanY);
    }
    double lower = lowerX * lowerY;
    if(lower > 0) rxy2 = upper*upper/lower;
    else rxy2 = 0;

    return rxy2;
}

vec LinReg::yFit(){
    vec yF;
    int size = x.size();
    for(int i = 0; i<size; i++){
        yF.push_back(x[i]*a+b);
    }
    return yF;
}

void LinReg::writeToFile(std::string filename, bool verboose){
    std::fstream file;
    vec yF = yFit();

    file.open(filename.c_str(),std::ios::out | std::ios::trunc);
    if(verboose == true){
        file << "# a=" << a << std::endl;
        file << "# b=" << b << std::endl;
        file << "# sigma^2=" << sigma2 << std::endl;
    }    
    int size = x.size();
    for(int i = 0; i<size; i++){
        file << x[i] << "\t" << y[i] << "\t" << yF[i] << std::endl;
    }
    file.close();
}

void LinReg::calcsigma2(){
    double n = x.size();
    if(n > 2){
        double sy2 = calcSy2();
        double rxy2 = calcCor();
        sigma2 = (n-1)/(n-2) *sy2 * (1- rxy2);
    }
    else sigma2 = 0;
}
void LinReg::calcAB(){
    double upper=0, lower=0;
    int max = x.size();
    for (int i = 0; i<max; i++){
        upper += (x[i] - meanX) * (y[i] - meanY);
        lower += (x[i] - meanX) * (x[i] - meanX);
    }
    if(lower <= 0) throw "use different x-values";

    a = upper/lower;
    b = meanY - a*meanX;
}

void LinReg::calculate(){
    calcMean();
    calcAB();
    calcsigma2();
}

LinReg readFile(std::string filename){
    std::fstream file;
    std::string dummy;
    double tmp;
    vec x,y;

    file.open(filename.c_str());

    while (file.good()){
        file >> tmp;
        x.push_back(tmp);
        file >> tmp;
        y.push_back(tmp);
        getline(file,dummy); // gets the rest of the line and ensures that everything after the first two columns gets ignored
    }
    file.close();
    LinReg lin(x,y);
    return lin;
};
