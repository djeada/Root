double funkcjaPois(double *x, double *par) {
  return par[0] * TMath::PoissonI(x[0], par[1]);
}

int Lab10() {

  int pairs[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  int freq[] = {47, 69, 84, 76, 49, 16, 10, 6, 0};

  TH1D *h1 = new TH1D("h1", ";pairs;freq", 9, 0, 9);

  for (int i = 0; i < 9; ++i) {
    h1->Fill(pairs[i], freq[i]);
  }

  // h1->Fit("gaus");

  TF1 *f1 = new TF1("f1", funkcjaPois, 0, 10, 2); // "xmin" = 0, "xmax" = 10
  f1->SetParameter(1, 1);
  h1->Fit("f1", "R");

  TCanvas *c = new TCanvas("c", "Zadanie 10", 800, 600);
  c->Divide(2, 2);
  c->cd(1); // przechodzimy do pierwszego padu

  h1->Draw();

  cout << "Chi2: " << h1->GetFunction("f1")->GetChisquare() << endl;
  cout << "Chi2/ndf: "
       << h1->GetFunction("f1")->GetChisquare() /
              h1->GetFunction("f1")->GetNDF()
       << endl;

  cout << "Kwantyl ChiSquare: 16.81" << endl;
  cout << "Warunek 10.31 > 16.81 nie jest spełniony, zatem na poziomie "
          "istotności 1% nie ma podstaw do odrzucenia hipotezy"
       << endl;

  return 0;
}
