double funkcjagest(double *x, double *p) {
  if (x[0] > 0 && x[0] < TMath::Pi()) {
    return p[0] * TMath::Sin(x[0]) * TMath::Exp(-x[0]);
  } else {
    return 0;
  }
}

int Zad1() {

  double xmin = 0;
  double xmax = TMath::Pi();

  TF1 *fun1 = new TF1("fun1", funkcjagest, xmin, xmax, 1);
  fun1->SetTitle("f(x);x;f(x)");
  fun1->SetParameter(0, 1);

  double integralValue = fun1->Integral(xmin, xmax);

  double paramC = 1 / integralValue;

  cout << paramC << endl;

  fun1->SetParameter(0, paramC);

  double tabX[100] = 0;
  double tabY[100] = 0;
  double x = 0;

  for (int i = 0; i < 100; i++) {
    x = (i / 100) * xmax;
    if (x != 0) {
      tabX[i] = x;
      tabY[i] = fun1->Integral(xmin, x);
    }
  }

  TGraph *k = new TGraph(100, tabX, tabY);

  cout << "Wartosc oczekiwana " << fun1->Mean(xmin, xmax);

  cout << endl;
  cout << endl;

  cout << "Odchylenie standardowe " << sqrt(fun1->Variance(xmin, xmax));

  cout << endl;
  cout << endl;

  TCanvas *c = new TCanvas("c", "Zadanie 1 KOLOS", 800, 600);
  c->Divide(2, 2);

  c->cd(1); // przechodzimy do pierwszego padu
  fun1->Draw("L");

  c->cd(2);
  k->Draw("LP");

  return 0;
}
