#ifndef FOURIER_FUNCTION_H_INCLUDED
#define FOURIER_FUNCTION_H_INCLUDED
#include "Fourier Functions.cpp"

using namespace std;

bool isDouble(string s, double &value);

bool isInt(string s, int &value);

void userInput(double &LAF, double &HAF, double &SF, int &steps, int &type);

void FileWrite(vector<double> x, vector<complex<double>> y, vector<pair<double,double>> z, int type);//file write function

vector<double> extractSignals(int &signalsIndex);

vector<double> computeSteps(double SampFreq, double LowAnalog,
double HighAnalog, int steps);

vector<double> computeDigitalFreq(vector<double> Analog,
 double SampFreq);

double NormalCoeff(vector<double> x, vector<double> y);

double computePhi(vector<double> Sig, vector<double> Sinusoid);

double computeMagnitude(double sin, double cos);

double computePhase(double sin, double cos);

vector<double> computeSin(int SigSize, double DigFreq);

vector<double> computeCos(int SigSize, double DigFreq);

vector<complex<double>> computeFourier(vector<double> Sig, 
vector<double> DigFreq, vector<double> AnalogFreq);

/*vector<pair<double,double>> computeFourierMagnitudePhasev2(vector<double> Sig, vector<complex<double>> Fourier, vector<double> AnalogFreq, vector<double> DigitalFreq)*/ //delete

vector<pair<double,double>> computeFourierMagnitudePhase(vector<double> Sig, vector<double> DigFreq, vector<double> AnalogFreq);

#endif