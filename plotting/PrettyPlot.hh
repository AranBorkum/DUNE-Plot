#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <unistd.h>
#include "../configs/GenParticle.hh"
#include "../configs/Hit.hh"
#include "../configs/Variable.hh"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMath.h"
#include "TMultiGraph.h"
#include "TPad.h"
#include "TProfile.h"
#include "TText.h"
#include "TTree.h"


std::string OutputFilePath = "/Users/aranborkum/Docterate/Scripts/DUNE-Plot/output";

class PrettyHist {
  
private:
  int         fSetLogy   , fSetLogX  ;
  std::string fCanvasName, fPlotTitle, fLegendEntry, fXLabel, fYLabel;
  TH1D*       fHistogram ;

public:
  PrettyHist(std::string cCanvasName, std::string cPlotTitle, std::string cLegendEntry,
             TH1D*       cHistogram ,
             std::string cXLabel    , std::string cYLabel   ,
             int         cSetLogY   , int         cSetLogX)
  {
    fCanvasName  = cCanvasName;
    fPlotTitle   = cPlotTitle;
    fLegendEntry = cLegendEntry;
    fHistogram   = cHistogram;
    fXLabel      = cXLabel;
    fYLabel      = cYLabel;
    fSetLogy     = cSetLogY;
    fSetLogX     = cSetLogX;
  };

  ~PrettyHist() {};

  void MakePlot() {
    
/*
|   Canvas setup:
|   Making the main plot:        canvas1
|   making a subplot underneath: canvas2
|   stacking the two
|   blah blah blah
*/
    
    TCanvas *canvas_main = new TCanvas("canvas_main", "canvas_main");
    canvas_main->Print((fPlotTitle + ".pdf[").c_str());
    TPad *canvas1 = new TPad("canvas1", "canvas1", 0.00, 0.30, 1.00, 1.00);
    canvas1->SetBottomMargin(0.02);
    canvas1->Draw();
    canvas_main->cd();
    TPad *canvas2 = new TPad("canvas2", "canvas2", 0.00, 0.00, 1.00, 0.30);
    canvas2->SetTopMargin(0);
    canvas2->SetBottomMargin(0.4);
    canvas2->Draw();
    canvas2->cd();
    canvas1->cd();
    if (fSetLogy == 1) {canvas1->SetLogy();}
    if (fSetLogX == 1) {canvas_main->SetLogx();}
/*
|   Setting up the legend
*/
  
    TLegend *legend = new TLegend(0.6, 0.8, 0.88, 0.90);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetLineColor(0);
    legend->SetTextSize(0.04);
    
/*
|   Setting up the LaTeX label on the plot
*/
    
    TLatex  *l1 = new TLatex(0.15, 0.80, "DUNE")            ;
    TLatex  *l2 = new TLatex(0.15, 0.75, fPlotTitle.c_str());
    l1->SetNDC(); l1->SetTextFont(72); l1->SetTextSize(0.08);
    l2->SetNDC(); l2->SetTextFont(72); l2->SetTextSize(0.04);
  
/*
|   Plotting on the upper canvas
*/
    
    fHistogram->SetStats     (kFALSE);
    fHistogram->SetLabelSize (0     );
//    fHistogram->SetFillColor (kBlue );
    fHistogram->SetLineColor (kBlue );
    
    fHistogram->GetXaxis()->SetTitle (fXLabel.c_str());
    fHistogram->GetYaxis()->SetTitle (fYLabel.c_str());

    fHistogram->GetYaxis()->SetRangeUser(10e-3, 10e2);
    fHistogram->GetXaxis()->SetLabelOffset();

    fHistogram->Draw();
    
    std::ostringstream strs;
    strs << fHistogram->GetEntries();
    std::string str = strs.str();
    
    legend->SetHeader(("Total Entries: " + str).c_str(), "c");
    legend->AddEntry(fHistogram, fLegendEntry.c_str());
    legend->Draw();
    l1->Draw();
    l2->Draw();
    
/*
|   Plotting on the lower canvas
*/
    
    canvas2->cd();
    Double_t x[2] = {0, 20};
    Double_t y[2] = {0, 0};
    TGraph *g1 = new TGraph(2, x, y);
    g1->SetTitle(""); g1->SetMinimum(-3); g1->SetMaximum( 3);
    g1->GetXaxis()->SetLimits(0, 20);
    
    g1->GetXaxis()->SetTitle(fXLabel.c_str());
    g1->GetXaxis()->SetTitleSize(0.12);
    g1->GetXaxis()->SetLabelSize(0.1);
    
    g1->Draw("AL");
    g1->GetYaxis()->SetNdivisions(505);

    
    
    
/*
|   Saving the final plot
*/
    
    canvas_main->Print((fPlotTitle + ".pdf" ).c_str());
    canvas_main->Print((fPlotTitle + ".pdf]").c_str());
    system(("mv " + fPlotTitle + ".pdf " + OutputFilePath).c_str());
    
  }
  
};

class PrettyProfile {
  
private:
  int         fSetLogy   , fSetLogX  ;
  std::string fCanvasName, fPlotTitle, fXLabel, fYLabel;
  TProfile*   fProfile   ;
  
public:
  PrettyProfile(std::string cCanvasName, std::string cPlotTitle, TProfile* cProfile,
                std::string cXLabel    , std::string cYLabel   ,
                int cSetLogY           , int cSetLogX)
  {
    fCanvasName = cCanvasName;
    fPlotTitle  = cPlotTitle;
    fProfile    = cProfile;
    fXLabel     = cXLabel;
    fYLabel     = cYLabel;
    fSetLogy    = cSetLogY;
    fSetLogX    = cSetLogX;
  };
  
  ~PrettyProfile() {};
  
  void MakePlot() {
    
    TCanvas *canvas_main = new TCanvas("canvas_main");
    TLatex  *l1 = new TLatex(0.15, 0.75, "DUNE")            ; l1->SetNDC();
    TLatex  *l2 = new TLatex(0.15, 0.68, fPlotTitle.c_str()); l2->SetNDC();
  
    l1->SetTextFont(72); l1->SetTextSize(0.10);
    l2->SetTextFont(72); l2->SetTextSize(0.04);

    canvas_main->Print((fPlotTitle + ".pdf[").c_str());

    
    fProfile->SetStats(kFALSE);
    fProfile->GetXaxis()->SetTitle(fXLabel.c_str());
    fProfile->GetYaxis()->SetTitle(fYLabel.c_str());
    fProfile->Draw();
    l1->Draw();
    l2->Draw();
    
    if (fSetLogy == 1) {canvas_main->SetLogy();}
    if (fSetLogX == 1) {canvas_main->SetLogx();}
    
    canvas_main->Print((fPlotTitle + ".pdf" ).c_str());
    canvas_main->Print((fPlotTitle + ".pdf]").c_str());
    system(("mv " + fPlotTitle + ".pdf " + OutputFilePath).c_str());
  }
  
};
