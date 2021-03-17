#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <complex>

using namespace std;

bool isDouble(string s, double &value)
{
  double tempValue;
  if ((istringstream(s) >> tempValue).eof())
  {
    value = tempValue;
    return true;
  }
  else
  {
    return false;
  }
}

bool isInt(string s, int &value)
{
  int tempValue;
  if ((istringstream(s) >> tempValue).eof())
  {
    value = tempValue;
    return true;
  }
  else
  {
    return false;
  }
}

void userInput(double &LAF, double &HAF, double &SF, int &steps,
 int &type)
{
  string temp;
  bool valid = 0;
  while(!valid)
  {
    cout << "Lower limit of Frequency to analyze: ";
    getline(cin, temp);
    if(!isDouble(temp, LAF))
    {
      cout << "Invalid! Please reinput!" <<endl;
      userInput(LAF, HAF, SF, steps, type);
      break;
    }
    cout << "Higher limit of Frequency to analyze: ";
    getline(cin, temp);
    if(!isDouble(temp, HAF) || HAF < LAF)
    {
      cout << "Invalid! Please reinput!" <<endl;
      userInput(LAF, HAF, SF, steps, type);
      break;
    }
    cout << "Sampling Frequency of the Input Signal: ";
    getline(cin, temp);
    if(!isDouble(temp, SF))
    {
      cout << "Invalid! Please reinput!" <<endl;
      userInput(LAF, HAF, SF, steps, type);
      break;
    }
    cout << "Steps to take: ";
    getline(cin, temp);
    if(!isInt(temp, steps) || steps <= 0)
    {
      cout << "Invalid! Please reinput!" <<endl;
      userInput(LAF, HAF, SF, steps, type);
      break;
    }
    cout << "Choose between which type of Fourier transform to output"
    << "\n[1] Complex Form\n[2] Polar Form\n[3] Both\nAnswer: ";
    getline(cin, temp);
    if(!isInt(temp, type) || type < 1 || type > 3)
    {
      cout << "Invalid! Please reinput!" <<endl;
      userInput(LAF, HAF, SF, steps, type);
      break;
    }
    valid = 1;
  }
}

void FileWrite(vector<double> x, vector<complex<double>> y,
 vector<pair<double,double>> z, int type) //file write function
{
  string FN;
  bool validName = true;
  
  vector<string> illegalCharacters;
  illegalCharacters.push_back("<");
  illegalCharacters.push_back(">");
  illegalCharacters.push_back(":");
  illegalCharacters.push_back("\"");
  illegalCharacters.push_back("/");
  illegalCharacters.push_back("\\");
  illegalCharacters.push_back("|");
  illegalCharacters.push_back("?");
  illegalCharacters.push_back("*");

  size_t found;

  while(validName)
  {
    cout << "File Name of Output:";
    getline(cin, FN);
    for (int i = 0; i < illegalCharacters.size(); i++){
      if (FN.find(illegalCharacters.at(i)) != string::npos)
      {
        validName = false;
      }
      if (i == illegalCharacters.size() - 1 && validName == true)
      {
        validName = false;
        break;
      }
      if (i == illegalCharacters.size() - 1 && validName == false)
      {
        cout << "Your file name must not include <, >,";
        cout << ":, \", /, \\, |, ?, or *. Please try again." <<endl; 
        validName = true;
      }
    }
  }

  ofstream fileWrite(FN.c_str(), ios::out);

  if (type == 1)
  {
    fileWrite << "Analog Frequency\tReal \tImaginary" << endl;
    for(int i=0; i<x.size(); i++)
    {
      fileWrite << x[i] << "\t\t" << y[i].real() << "\t\t"
       << y[i].imag() << endl;
    }
  }
  else if (type == 2)
  {
    fileWrite << "Analog Frequency\tMagnitude \tPhase" << endl;
    for(int i=0; i<x.size(); i++)
    {
      fileWrite << x[i] << "\t\t" << z[i].first << "\t\t"
       << z[i].second << endl;
    }
  }
  fileWrite.close();
}

vector<double> extractSignals(int &signalsIndex)
{
  string signalText, tempString, fileName;
  stringstream ss, ss2;
  int lineNumber = 0;
  double tempDouble, tempDouble2;
  vector<double> signals;

  cout << "Enter file name for the signals: ";
  getline(cin, fileName);

  fstream signalFile(fileName);

  if (!signalFile.is_open())
  {
    cout << "Invalid File Name, Please try again..." <<endl;
    signals = extractSignals(signalsIndex);
  }
  else if (signalFile.is_open())
  {
    while (getline(signalFile, signalText) && signalText != "")
    {
      if (lineNumber == 0)
      {
        ss << signalText;
        ss >> tempString;
        if(!isDouble(tempString, tempDouble) 
        && !isInt(tempString, signalsIndex))
        {
          cout << "Invalid Signal File!" <<endl;
          signalFile.close();
          signals = extractSignals(signalsIndex);
          break;
        }
        else if (!isInt(tempString, signalsIndex))
        {
          if (isDouble(tempString, tempDouble))
          {
            ss >> tempString;
            if (isDouble(tempString,tempDouble2))
            {
              cout << "Invalid Index! " << tempDouble; 
              cout << " is not a valid index." <<endl;
              signalFile.close();
              signals = extractSignals(signalsIndex);
              break;
            }
            signals.push_back(tempDouble);
            signalsIndex = 0;
          }
          
        }
        else
        {
          ss >> tempString;
          if (isDouble(tempString, tempDouble))
          {
            signals.push_back(tempDouble);
          }
          ss.clear();
        }
        lineNumber++;
      }
      else
      {
        ss2.str(string());
        ss2 << signalText;
        ss2 >> tempString;
        ss2.clear();

        if (isDouble(tempString, tempDouble))
        {
          signals.push_back(tempDouble);
        }
        tempString = "";
      }
    }
    signalFile.close();
  }
  return signals;
}

vector<double> computeSteps(double SampFreq, double LowAnalog,
double HighAnalog, int steps)
{
  double temp = (HighAnalog - LowAnalog)/(steps*1.0);
  vector<double> AnalogFreq;

  for(int n=0; n<=steps; n++)
  {
    AnalogFreq.push_back((n*temp + LowAnalog));
  }

  return AnalogFreq;
}

vector<double> computeDigitalFreq(vector<double> Analog,
 double SampFreq)
{
  vector<double> DigitalFreq;

  for(int n=0; n<Analog.size(); n++)
  {
    DigitalFreq.push_back((2*M_PI*Analog[n])/SampFreq);
  }
  return DigitalFreq;
}

double NormalCoeff(vector<double> x, vector<double> y)
{
  double sum1=0, sum2=0;
  for(int n=0; n<x.size(); n++)
  {
    sum1+= x[n]*x[n];
  }
  for(int n=0; n<y.size(); n++)
  {
    sum2+= y[n]*y[n];
  }
  return sqrt(sum1*sum2);
}

double computePhi(vector<double> Sig, vector<double> Sinusoid)
{
  double sum=0;
  for(int n=0; n<Sig.size(); n++)
  {
    sum+= Sig[n]*Sinusoid[n];
  }
  return sum;
}

double computeMagnitude(double sin, double cos)
{
  return sqrt((sin*sin) + (cos*cos));
}

double computePhase(double sin, double cos)
{
  return ((atan2(sin, cos)*180)/M_PI);
}

vector<double> computeSin(int SigSize, double DigFreq)
{
  vector<double> Sin;
  for(int n=0; n<SigSize; n++)
  {
    Sin.push_back(sin(n*DigFreq));
  }
  return Sin;
}

vector<double> computeCos(int SigSize, double DigFreq)
{
  vector<double> Cos;
  for(int n=0; n<SigSize; n++)
  {
    Cos.push_back(cos(n*DigFreq));
  }
  return Cos;
}

vector<complex<double>> computeFourier(vector<double> Sig,
 vector<double> DigFreq, vector<double> AnalogFreq)
{
  vector<complex<double>> Fourier;
  complex<double> temp, sum;
  double samplesize = Sig.size();
  for(double z=0; z<DigFreq.size(); z++)
  {
    sum = 0;
    temp = 0;
    
    for(double n=0; n<Sig.size(); n++)
    {
      temp = Sig[n] * exp(-1i *DigFreq[z]*n);
      sum+=temp;
    }
    Fourier.push_back(sum);
  }
  return Fourier;
}

vector<pair<double,double>> computeFourierMagnitudePhase
(vector<double> Sig, vector<double> DigFreq,
 vector<double> AnalogFreq)
{
  vector<pair<double,double>> Fourier;
  double magni, phase;

  for(double n=0; n<DigFreq.size(); n++)
  {
    magni = computeMagnitude(computePhi(Sig, 
    computeSin(Sig.size(),DigFreq[n])), 
    computePhi(Sig,computeCos(Sig.size(),DigFreq[n])));

    phase = computePhase(-1*computePhi(Sig, 
    computeSin(Sig.size(),DigFreq[n])), 
    computePhi(Sig, computeCos(Sig.size(),DigFreq[n])));

    Fourier.push_back(make_pair(magni,phase));
  }
  return Fourier;
}