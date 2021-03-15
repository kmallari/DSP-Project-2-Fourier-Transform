#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <complex>
#include "Fourier Functions.h"

using namespace std;

int main()
{
  cout << "Testing code" <<endl;
  vector<double> signal, AnalogFreq, DigitalFreq;
  double LowAnalogFreq, HighAnalogFreq, SampFreq;
  int steps, index, type; //remove index if di kailangan
  vector<complex<double>> FourierCmplx;
  vector<pair<double,double>> FourierMagPh;

  signal = extractSignals(index);

  userInput(LowAnalogFreq, HighAnalogFreq, SampFreq, steps, type);
  
  AnalogFreq = computeSteps(SampFreq, LowAnalogFreq, HighAnalogFreq,
   steps);
  DigitalFreq = computeDigitalFreq(AnalogFreq, SampFreq);

  if (type == 1)
  {
    cout << "\nComplex Output File..." <<endl;
    FourierCmplx = computeFourier(signal, DigitalFreq, AnalogFreq);
    FileWrite(AnalogFreq, FourierCmplx, FourierMagPh, type);
  }
  else if (type == 2)
  {
    cout << "\nMagnitude Phase Output File..." <<endl;
    FourierMagPh = computeFourierMagnitudePhase(signal, DigitalFreq,
     AnalogFreq);
    FileWrite(AnalogFreq, FourierCmplx, FourierMagPh, type);
  }
  else if (type == 3)
  {
    FourierCmplx = computeFourier(signal, DigitalFreq, AnalogFreq);
    FourierMagPh = computeFourierMagnitudePhase(signal, DigitalFreq,
     AnalogFreq);
    
    cout << "\nComplex Output File..." <<endl;
    FileWrite(AnalogFreq, FourierCmplx, FourierMagPh, type-1);
    cout << "\nMagnitude Phase Output File..." <<endl;
    FileWrite(AnalogFreq, FourierCmplx, FourierMagPh, type-2);
  }
}

