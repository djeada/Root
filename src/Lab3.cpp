double funkcjagest(double *x, double *p) {
  if (x[0] >= 0 && x[1] >= 0) {
    return p[0] * TMath::Power(x[0], p[1]) * TMath::Power(x[1], p[2]);
  } else {
    return 0;
  }
}

int Lab3() {

  double xmin = 0;
  double xmax = 1;
  double ymin = 0;
  double ymax = 1;

  TF2 *fun1 = new TF2("fun1", funkcjagest, xmin, xmax, ymin, ymax, 3);
  fun1->SetTitle("f(x);x;f(x)");
  fun1->SetParameter(0, 1);
  fun1->SetParameter(1, 1);
  fun1->SetParameter(2, 2);

  double integralValue = fun1->Integral(xmin, xmax, ymin, ymax);

  double paramC = 1 / integralValue;

  cout << paramC << endl;

  fun1->SetParameter(0, paramC);

  TGraph2D *g = new TGraph2D(400);
  double x = 0;
  double y = 0;
  double z = 0;
  int n = 0;

  for (int i = 0; i < 20; i++) {
    x = i / 20.0;

    for (int j = 0; j < 20; j++) {
      y = j / 20.0;
      z = fun1->Integral(0, x, 0, y);
      g->SetPoint(n, x, y, z);
      n++;
    }
  }

  TGraph *gx = new TGraph(20);
  for (int i = 0; i < 20; i++) {
    x = i / 20.0;
    y = fun1->Integral(0, xmax, 0, x);
    gx->SetPoint(i, x, y);
  }

  TGraph *hy = new TGraph(20);
  for (int i = 0; i < 20; i++) {
    x = i / 20.0;
    y = fun1->Integral(0, x, 0, ymax);
    hy->SetPoint(i, x, y);
  }

  TCanvas *c = new TCanvas("c", "Zadanie 3", 800, 600);
  c->Divide(2, 2);

  c->cd(1); // przechodzimy do pierwszego padu
  fun1->Draw("SURF1");

  c->cd(2);
  g->Draw("SURF1");

  c->cd(3);
  gx->Draw("ALP");

  c->cd(4);
  hy->Draw("ALP");

  return 0;
}
