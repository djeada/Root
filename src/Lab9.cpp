double funkcjagest(Double_t *x, Double_t *par) {
  // Chisquare density distribution for nrFree degrees of freedom

  double nrFree = par[0];
  double chi2 = x[0];

  if (chi2 > 0) {
    double lambda = nrFree / 2.;
    double norm = TMath::Gamma(lambda) * TMath::Power(2., lambda);
    return TMath::Power(chi2, lambda - 1) * TMath::Exp(-0.5 * (chi2)) / norm;
  } else
    return 0.0;
}

int Lab9() {

  TCanvas *c = new TCanvas("c", "Zadanie 9", 800, 600);
  c->Divide(2, 2);
  c->cd(1); // przechodzimy do pierwszego padu
  gPad->SetLogy();

  int num = 20;
  double xmin = 0;
  double xmax = 30;

  TF1 **functions = new TF1 *[num];
  for (int i = 0; i < num; i++) {
    char fname[20];
    sprintf(fname, "f%d", i);
    functions[i] = new TF1(fname, funkcjagest, 0.01, 30, 1);
    functions[i]->SetParameter(0, i);
    if (i == 0)
      functions[i]->Draw();
    else {
      functions[i]->Draw("lsame");
      functions[i]->SetLineColor(i);
    }
  }

  c->cd(2);

  double tabX[100] = 0;
  double tabY[100] = 0;
  double x = 0;

  for (int i = 0; i < num; i++) {
    char fname[20];
    sprintf(fname, "f%d", i);
    functions[i] = new TF1(fname, funkcjagest, 0.01, 30, 1);
    functions[i]->SetParameter(0, i);
    for (int j = 0; j < 100; j++) {
      x = (j / 100.0) * xmax;
      if (x != 0) {
        tabX[j] = x;
        tabY[j] = functions[i]->Integral(xmin, x);
      }
    }
    TGraph *k = new TGraph(100, tabX, tabY);

    if (i == 0)
      k->Draw("ALP");
    else {
      k->Draw("lsame");
      k->SetLineColor(i);
    }
  }
  return 0;
}
