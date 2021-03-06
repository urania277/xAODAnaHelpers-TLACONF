#ifndef xAODAnaHelpers_ElectronEfficiencyCorrector_H
#define xAODAnaHelpers_ElectronEfficiencyCorrector_H

// EDM include(s):
#include "xAODEgamma/ElectronContainer.h"

// CP interface includes
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/SystematicSet.h"
#include "PATInterfaces/SystematicsUtil.h"
#include "PATInterfaces/SystematicVariation.h"

// external tools include(s):
#include "ElectronEfficiencyCorrection/AsgElectronEfficiencyCorrectionTool.h"

// algorithm wrapper
#include "xAODAnaHelpers/Algorithm.h"

class ElectronEfficiencyCorrector : public xAH::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // configuration variables
  std::string m_inContainerName;

  // systematics
  std::string m_inputAlgoSystNames;  // this is the name of the vector of names of the systematically varied containers produced by the
  			             // upstream algo (e.g., the SC containers with calibration systematics)

  float m_systValPID;
  float m_systValReco;
  float m_systValTrig;
  std::string m_systNamePID;
  std::string m_systNameReco;
  std::string m_systNameTrig;
  std::string m_outputSystNamesPID;
  std::string m_outputSystNamesReco;
  std::string m_outputSystNamesTrig;

  std::string m_corrFileNamePID;
  std::string m_corrFileNameReco;
  std::string m_corrFileNameTrig;

private:
  int m_numEvent;         //!
  int m_numObject;        //!

  bool m_isMC;            //!

  std::string m_PID_WP;   //!

  std::vector<CP::SystematicSet> m_systListPID; //!
  std::vector<CP::SystematicSet> m_systListReco; //!
  std::vector<CP::SystematicSet> m_systListTrig; //!

  // tools
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_PID; //!
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_Reco; //!
  AsgElectronEfficiencyCorrectionTool  *m_asgElEffCorrTool_elSF_Trig; //!

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)

public:

  // Tree *myTree; //!
  // TH1 *myHist;  //!


  // this is a standard constructor
  ElectronEfficiencyCorrector (std::string className = "ElectronEfficiencyCorrector");

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // these are the functions not inherited from Algorithm
  virtual EL::StatusCode configure ();
  virtual EL::StatusCode executeSF (  const xAOD::ElectronContainer* inputElectrons, const xAOD::EventInfo* eventInfo, unsigned int countSyst  );

  /// @cond
  // this is needed to distribute the algorithm to the workers
  ClassDef(ElectronEfficiencyCorrector, 1);
  /// @endcond

};

#endif
