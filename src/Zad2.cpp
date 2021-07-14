double funkcjagest(double *x, double *p) {
  if (x[0] > 0 && x[0] < 5 && x[1] > 0 && x[1] < 5) {
    return p[0] * (x[0] + x[1]) * TMath::Exp(-1 * (sqrt(x[0]) + x[1]));
  } else {
    return 0;
  }
}

int Zad2() {

  double xmin = 0;
  double xmax = 5;
  double ymin = 0;
  double ymax = 5;

  TF2 *fun1 = new TF2("fun1", funkcjagest, xmin, xmax, ymin, ymax, 1);
  fun1->SetTitle("f(x);x;f(x)");
  fun1->SetParameter(0, 1);

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

  TCanvas *c = new TCanvas("c", "Zadanie 2 KOLOS", 800, 600);
  c->Divide(2, 2);

  c->cd(1); // przechodzimy do pierwszego padu
  fun1->Draw("SURF1");

  c->cd(2);
  g->Draw("SURF1");

  return 0;
}
