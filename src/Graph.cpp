#include <iostream>

using namespace std;

int Graph() {

  TCanvas *c = new TCanvas("c", "Galton Table", 1600, 950);
  c->Divide(2, 2);
  c->SetFillColor(kWhite);

  // reading data from files
  c->cd(1);
  TGraph *g = new TGraph("data.txt");
  g->Draw("ALP");
  g->SetMarkerStyle(21);
  g->SetLineColor(kRed);
  g->SetTitle("Data Plot with TGraph;GW;ms");

  // linear fit
  c->cd(2);
  double x, y;
  TGraph *g2 = new TGraph();
  for (int i = 0; i < 100; i++) {
    x = i * 2;
    y = 0.4 * x + gRandom->Gaus(0, 5);
    g2->SetPoint(i, x, y);
  }

  TF1 *f = new TF1("linear fit", "[0]*x+[1]", 0, 5);
  g2->Fit(f);

  g2->SetMarkerStyle(24);
  g2->Draw("AP");

  // exponential fit
  c->cd(3);
  TGraph *g3 = new TGraph();
  for (int i = 0; i < 30; i++) {
    x = i * 2;
    y = 0.4 * x * x + exp(-x / 3) + gRandom->Gaus(0, 5);
    g3->SetPoint(i, x, y);
  }

  TF1 *f1 = new TF1("linear fit", "[0]*x^2 +exp(-x*[1])", 0, 5);
  g3->Fit(f1);

  g3->SetMarkerStyle(8);
  g3->Draw("AP");

  // histograms
  c->cd(4);

  TH1D *h = new TH1D("h", "Some histo;X;Counts", 100, -20, 20);
  for (int i = 0; i < 30000; i++) {
    x = gRandom->Gaus(0, 5);
    h->Fill(x);
  }
  h->Fit("gaus");
  h->Draw();

  return 0;
}
