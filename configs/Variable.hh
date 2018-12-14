#ifndef VARIABLE_HH
#define VARIABLE_HH

#include <iostream>
#include <vector>
#include <string>

class Variable {
  
private:
  std::string fVariableName;
  std::string fVariableUnits;
  std::string fVariableLabel;
  
  std::vector<float>       fBinning;
  std::vector<float>       fLimits = {-1, -1, -1, -1};
  std::vector<std::string> fVariableUnits2 = {"", ""};
  std::vector<std::string> fVariableLabels = {"", ""};
  
public:
  // CONSTRUCTORs FOR VARIABLE OBJECT
  Variable (std::string cVariableName,
            std::string cVariableUnits,
            std::string cVariableLabel,
            std::vector<float> cBinning)
  {
    fVariableName  = cVariableName;
    fVariableUnits = cVariableUnits;
    fVariableLabel = cVariableLabel;
    fBinning       = cBinning;
  };
  
  Variable (std::string cVariableName,
            std::string cVariableUnits,
            std::string cVariableLabel,
            std::vector<float> cBinning,
            std::vector<float> cLimits)
  {
    fVariableName  = cVariableName;
    fVariableUnits = cVariableUnits;
    fVariableLabel = cVariableLabel;
    fBinning       = cBinning;
    fLimits        = cLimits;
  };
  
  Variable (std::string cVariableName,
            std::vector<std::string> cVariableUnits2,
            std::vector<std::string> cVariableLabels,
            std::vector<float> cBinning,
            std::vector<float> cLimits)
  {
    fVariableName   = cVariableName;
    fVariableUnits2 = cVariableUnits2;
    fVariableLabels = cVariableLabels;
    fBinning        = cBinning;
    fLimits         = cLimits;
  };
  
  
  Variable() {};
  
  // DESTRUCTOR FOR VARIABLE OBJECT
  ~Variable() {};
  
  // GET FUNCTIONS
  std::string        GetVariableName () { return fVariableName;   };
  std::string        GetVariableUnits() { return fVariableUnits;  };
  std::string        GetVariableLabel() { return fVariableLabel;  };
  std::vector<float> GetBinning      () { return fBinning;        };
  std::vector<float> GetLimits       () { return fLimits;         };
  std::vector<std::string> GetLabels () { return fVariableLabels; };
  std::vector<std::string> GetUnits2 () { return fVariableUnits2; };

  //SET FUNCTIONS
  void SetVariableName (std::string str)              { fVariableName   = str; };
  void SetVariableUnits(std::string str)              { fVariableUnits  = str; };
  void SetVariableLabel(std::string str)              { fVariableLabel  = str; };
  void SetBinning      (std::vector<float> vec)       { fBinning        = vec; };
  void SetLimits       (std::vector<float> vec)       { fLimits         = vec; };
  void SetLabels       (std::vector<std::string> vec) { fVariableLabels = vec; };
  void SetUnits2       (std::vector<std::string> vec) { fVariableUnits2 = vec; };
  
  void Print() {
    std::cout << "Descriptors of the variable: " << fVariableName << std::endl;
    std::cout << "|" << std::endl;
    std::cout << "|\tVariable name        : \t" << fVariableName << std::endl;
    std::cout << "|" << std::endl;
    std::cout << "|\tVariable units       : \t" << fVariableUnits << std::endl;
    std::cout << "|" << std::endl;
    std::cout << "|\tVariable label       : \t" << fVariableLabel << std::endl;
    std::cout << "|" << std::endl;
    std::cout << "|\tBinning configuration: \t" << "(" << fBinning[0] << ", "
                                                       << fBinning[1] << ", "
                                                       << fBinning[2] << ")"
                                                       << std::endl
                                                       << std::endl;
  }
  
};

#endif
