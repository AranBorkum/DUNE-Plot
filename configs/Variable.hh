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
  
  std::vector<int>   fBinning;
  std::vector<float> fLimits = {-1, -1};
  
public:
  // CONSTRUCTORs FOR VARIABLE OBJECT
  Variable (std::string cVariableName,
            std::string cVariableUnits,
            std::string cVariableLabel,
            std::vector<int> cBinning)
  {
    fVariableName  = cVariableName;
    fVariableUnits = cVariableUnits;
    fVariableLabel = cVariableLabel;
    fBinning       = cBinning;
  };
  
  Variable (std::string cVariableName,
            std::string cVariableUnits,
            std::string cVariableLabel,
            std::vector<int> cBinning,
            std::vector<float> cLimits)
  {
    fVariableName  = cVariableName;
    fVariableUnits = cVariableUnits;
    fVariableLabel = cVariableLabel;
    fBinning       = cBinning;
    fLimits        = cLimits;
  };
  
  Variable() {};
  
  // DESTRUCTOR FOR VARIABLE OBJECT
  ~Variable() {};
  
  // GET FUNCTIONS
  std::string        GetVariableName () { return fVariableName;  };
  std::string        GetVariableUnits() { return fVariableUnits; };
  std::string        GetVariableLabel() { return fVariableLabel; };
  std::vector<int>   GetBinning      () { return fBinning;       };
  std::vector<float> GetLimits       () { return fLimits;        };

  //SET FUNCTIONS
  void SetVariableName (std::string str)        { fVariableName  = str; };
  void SetVariableUnits(std::string str)        { fVariableUnits = str; };
  void SetVariableLabel(std::string str)        { fVariableLabel = str; };
  void SetBinning      (std::vector<int>   vec) { fBinning       = vec; };
  void SetLimits       (std::vector<float> vec) { fLimits        = vec; };
  
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
