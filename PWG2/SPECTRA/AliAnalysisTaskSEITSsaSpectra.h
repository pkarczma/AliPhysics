#ifndef ALIANALYSISTASKSEITSSASPECTRA_H
#define ALIANALYSISTASKSEITSSASPECTRA_H

///////////////////////////////////////////////////////////////////////////
// AliAnalysisTaskSE for the extraction of the various histograms to
// study the pt spectra of identified hadrons:
// - log(dEdx)-log(dEdxBB) distributions for pions, kaons and protons in pt bins
// - Pt distributions of pions, kaons and protons with nSigma PID
// Authors: 
// E. Biolcati, biolcati@to.infn.it
// L. Milano, milano@to.infn.it
// F. Prino, prino@to.infn.it
///////////////////////////////////////////////////////////////////////////

class TString;
class TTree;
class TH1F;
class TH2F;
class TRandom3;
class AliESDEvent;
class TNtuple;

#include "AliAnalysisTaskSE.h"

class AliAnalysisTaskSEITSsaSpectra : public AliAnalysisTaskSE {
 public:
  AliAnalysisTaskSEITSsaSpectra();
  virtual ~AliAnalysisTaskSEITSsaSpectra();

  virtual void   UserCreateOutputObjects();
  virtual void   UserExec(Option_t *);
  virtual void   Terminate(Option_t *);

  void SetMaxChi2Clu(Double_t chi=1.){
    fMaxChi2Clu=chi;
  }
  void SetRapidityRange(Double_t dy=0.5){
    fMaxY=dy;
  }
  void SetMinNSigma(Double_t ns=3.){
    fMinNSigma=ns;
  }
  void SetMindEdx(Double_t mind=0.){
    fMindEdx=mind;
  }
  void SetMinSPDPoints(Int_t np=1){
    fMinSPDPts=np;
  }
  void SetMinNdEdxSamples(Int_t np=3){
    fMinNdEdxSamples=np;
  }
  void SetDCACuts(Double_t nsxy=7., Double_t nsz=7.){
    fNSigmaDCAxy=nsxy;
    fNSigmaDCAz=nsz; 
  }

  void SetReadMC(Bool_t flag = kTRUE) {fMC = flag;}
  void SetFillNtuple(Bool_t fill=kTRUE) {fFillNtuple=fill;}
  void SetSmearMC(Double_t smearp, Double_t smeardedx){
    fSmearMC=kTRUE;
    fSmearP=smearp;
    fSmeardEdx=smeardedx;
  }
  Double_t BetheBloch(Double_t bg,Bool_t optMC) const;
  Double_t CookdEdx(Double_t *s) const; 
  Double_t Eta2y(Double_t pt, Double_t m, Double_t eta) const;
  Bool_t DCAcut(Double_t impactXY, Double_t impactZ, Double_t pt, Bool_t optMC) const;

 private:
  AliAnalysisTaskSEITSsaSpectra(const AliAnalysisTaskSEITSsaSpectra &source); 
  AliAnalysisTaskSEITSsaSpectra& operator=(const AliAnalysisTaskSEITSsaSpectra &source);

  enum {kNbins=22};
  
  AliESDEvent *fESD; //ESD object
  TList *fOutput; //! tlist with output
  TH1F *fHistNEvents; //! histo with number of events
  TH1F *fHistNTracks; //! histo with number of tracks
  
  TH2F *fHistDEDX; //! histo with dedx versus momentum
  TH2F *fHistDEDXdouble; //! histo with dedx versus signed momentum
  
  TH1F *fHistBeforeEvSel; //! histo with pt distribution before my event selection
  TH1F *fHistAfterEvSel; //! histo with pt distribution after my event selection
  
  TH1F *fHistMCpos[3]; //! histo with spectra from the MC truth (positive)
  TH1F *fHistMCneg[3]; //! histo with spectra from the MC truth (negative)
  TH1F *fHistMCposBefEvSel[3]; //! histo with spectra from the MC truth (positive)
  TH1F *fHistMCnegBefEvSel[3]; //! histo with spectra from the MC truth (negative)
  
  TH1F *fHistCharge[4]; //! histo with charge distribution to check the calibration 
  
  TH1F *fHistPosPi[kNbins]; //! histo with dedx distibution in the pions hypotesis (positive)
  TH1F *fHistPosK[kNbins]; //! histo with dedx distibution in the kaons hypotesis (positive)
  TH1F *fHistPosP[kNbins]; //! histo with dedx distibution in the protons hypotesis (positive)
  TH1F *fHistNegPi[kNbins]; //! histo with dedx distibution in the pions hypotesis (negative)
  TH1F *fHistNegK[kNbins]; //! histo with dedx distibution in the kaons hypotesis (negative)
  TH1F *fHistNegP[kNbins]; //! histo with dedx distibution in the protons hypotesis (negative)
  
  TH1F *fHistDCAPosPi[kNbins]; //! histo with DCA distibution in the pions hypotesis (positive)
  TH1F *fHistDCAPosK[kNbins]; //! histo with DCA distibution in the kaons hypotesis (positive)
  TH1F *fHistDCAPosP[kNbins]; //! histo with DCA distibution in the protons hypotesis (positive)
  TH1F *fHistDCANegPi[kNbins]; //! histo with DCA distibution in the pions hypotesis (negative)
  TH1F *fHistDCANegK[kNbins]; //! histo with DCA distibution in the kaons hypotesis (negative)
  TH1F *fHistDCANegP[kNbins]; //! histo with DCA distibution in the protons hypotesis (negative)
  		
  TH1F *fHistMCPosPi[kNbins]; //! histo with dedx using the MC truth in the pions hypotesis (positive)
  TH1F *fHistMCPosK[kNbins]; //! histo with dedx  using the MC truth in the kaons hypotesis (positive)
  TH1F *fHistMCPosP[kNbins]; //! histo with dedx  using the MC truth in the protons hypotesis (positive)
  TH1F *fHistMCNegPi[kNbins]; //! histo with dedx using the MC truth in the pions hypotesis (negative)
  TH1F *fHistMCNegK[kNbins]; //! histo with dedx  using the MC truth in the kaons hypotesis (negative)
  TH1F *fHistMCNegP[kNbins]; //! histo with dedx  using the MC truth in the protons hypotesis (negative)
  
  TH1F *fHistPosNSigma[3];       //! NSigma histos for 6 species
  TH1F *fHistPosNSigmaPrim[3];   //! NSigma histos for 6 species
  TH1F *fHistPosNSigmaPrimMC[3]; //! NSigma histos for 6 species
  TH1F *fHistNegNSigma[3];       //! NSigma histos for 6 species
  TH1F *fHistNegNSigmaPrim[3];   //! NSigma histos for 6 species
  TH1F *fHistNegNSigmaPrimMC[3]; //! NSigma histos for 6 species

  Double_t fPtBinLimits[kNbins+1]; // limits of Pt Bins
  Int_t    fMinSPDPts;       // minimum number of SPD Points
  Int_t    fMinNdEdxSamples; // minimum number of SDD+SSD points
  Double_t fMindEdx;         // minimum dE/dx value in a layer (to cut noise)
  Double_t fMinNSigma;       // minimum number of sigmas
  Double_t fMaxY;            // maximum rapidity
  Double_t fMaxChi2Clu;      // maximum cluster
  Double_t fNSigmaDCAxy;     // DCA cut in bend. plane
  Double_t fNSigmaDCAz;      // DCA cut along z

  Bool_t   fMC;        //flag to switch on the MC analysis for the efficiency estimation
  Bool_t   fSmearMC;   // flag to apply extra smearing on MC 
  Double_t fSmearP;    // extra relative smearing on simulated momentum
  Double_t fSmeardEdx; // extra relative smearing on simulated dE/dx
  TRandom3* fRandGener;    // generator for smaring
  Bool_t       fFillNtuple;      // fill ntuple  
  TNtuple     *fNtupleNSigma;//! output ntuple
  TNtuple     *fNtupleMC;//! output MC ntuple
  
  ClassDef(AliAnalysisTaskSEITSsaSpectra, 1);
};

#endif
