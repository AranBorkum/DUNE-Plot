#ifndef FIGURE_HH
#define FIGURE_HH

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

class FigureHist {
  
private:
  int fSetLogY = 0;
  int fSetLogX = 0;
  Variable* fVariable;
  TH1D* fHistogram;

public:
  //CONSTRUCTOR
  FigureHist (Variable* cVariable, TH1D* cHistogram, int cSetLogY, int cSetLogX)
  {
    fVariable  = cVariable;
    fHistogram = cHistogram;
    fSetLogY   = cSetLogY;
    fSetLogX   = cSetLogX;
  };
  
  //DESTRUCTOR
  ~FigureHist() {};
  
  //ACTUALLY MAKING THE PLOT
  void MakePlot() {
    
    //INITIATE THE CANVAS
    TCanvas *canvas_main = new TCanvas("canvas_main", "canvas_main");
    canvas_main->Print( (fVariable->GetVariableName() + ".pdf[").c_str() );
    
    //INITIATING THE SUBPLOTS
    TPad *canvas1 = new TPad("canvas1", "canvas1", 0.00, 0.30, 1.00, 1.00);
    canvas1->SetBottomMargin(0.02);
    canvas1->Draw();
    canvas_main->cd();
    
    if (fSetLogY == 1) {canvas1->SetLogy();}
    if (fSetLogX == 1) {canvas1->SetLogx();}
    
    TPad *canvas2 = new TPad("canvas2", "canvas2", 0.00, 0.00, 1.00, 0.30);
    canvas2->SetTopMargin   (0.00);
    canvas2->SetBottomMargin(0.40);
    canvas2->Draw();
    canvas2->cd();
    canvas1->cd();
    
    //WRITING LABEL ON THE CANVAS
    TLatex *l1 = new TLatex(0.15, 0.80, "DUNE");
    TLatex *l2 = new TLatex(0.15, 0.75, (fVariable->GetVariableName()).c_str());
    l1->SetNDC(); l1->SetTextFont(72); l1->SetTextSize(0.08);
    l2->SetNDC(); l2->SetTextFont(72); l2->SetTextSize(0.04);
    
    //INITIALISE THE LEGEND
    TLegend *legend = new TLegend(0.6, 0.8, 0.88, 0.90);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetLineColor(0);
    legend->SetTextSize(0.04);
    
    //SETTING THE AXIS LABELS AND FEATURES
    fHistogram->SetStats(kFALSE);
    fHistogram->SetLabelSize(0);
    fHistogram->SetLineColor(kBlue);
    fHistogram->SetFillColor(kBlue);
    fHistogram->GetYaxis()->SetTitle("Events");
    fHistogram->GetYaxis()->SetTitleSize(0.06);
    fHistogram->GetYaxis()->SetLabelSize(0.04);
    std::vector<float> limits = fVariable->GetLimits();
    if (limits[0] != -1 && limits[1] != -1) { fHistogram->GetYaxis()->SetRangeUser(limits[0], limits[1]); }
    
    fHistogram->Draw();
    
    //FINAL DRAWING THE FIGURE
    legend->AddEntry(fHistogram, (fVariable->GetVariableName()).c_str(), "f");
    legend->Draw();
    l1->Draw();
    l2->Draw();
    
    //FORMATTING THE BOTTOM CANVAS
    canvas2->cd();
    Double_t x[2] = {fHistogram->GetXaxis()->GetXmin(), fHistogram->GetXaxis()->GetXmax()};
    Double_t y[2] = {0, 0};
    
    TGraph *graph = new TGraph(2, x, y);
    graph->SetTitle("");
    graph->SetMinimum(-3);
    graph->SetMaximum( 3);
    graph->GetXaxis()->SetLimits(x[0], x[1]);
    graph->GetXaxis()->SetTitleSize(0.12);
    graph->GetXaxis()->SetLabelSize(0.10);
    graph->GetXaxis()->SetTitle((fVariable->GetVariableLabel() + " [" +
                                      fVariable->GetVariableUnits() + "]").c_str());
    
    graph->Draw();
    graph->GetYaxis()->SetNdivisions(505);
    
    //SAVING THE FIGURE
    canvas_main->Print( (fVariable->GetVariableName() + ".pdf").c_str() );
    canvas_main->Print( (fVariable->GetVariableName() + ".pdf]").c_str() );
    system( ("mv " + fVariable->GetVariableName() + ".pdf " + OutputFilePath).c_str() );
  }
  
};


#endif
