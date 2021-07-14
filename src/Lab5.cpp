double funkcjagest(double *x, double *p) {}

int Lab5() {

  double xmin = 0;
  double xmax = 6;
  double ymin = 0;
  double ymax = 18;

  double x1, x2, x3;

  TH2D *h12 = new TH2D("h12", "histogram 12", 100, xmin, xmax, 100, 0, 3);
  TH2D *h13 = new TH2D("h13", "histogram 13", 100, xmin, xmax, 100, ymin, ymax);
  TH2D *h23 = new TH2D("h23", "histogram 23", 100, xmin, 4, 100, ymin, ymax);

  ifstream in1, in2, in3;
  in1.open("lab05-dane1.dat");
  in2.open("lab05-dane2.dat");
  in3.open("lab05-dane3.dat");

  while (in1 >> x1) {
    in2 >> x2;
    in3 >> x3;
    h12->Fill(x1, x2);
    h13->Fill(x1, x3);
    h23->Fill(x2, x3);
  }

  cout << "X1 = " << h12->GetMean(1) << " +/- " << h12->GetRMS(1) << endl;
  cout << "X2 = " << h12->GetMean(2) << " +/- " << h12->GetRMS(2) << endl;
  cout << "X3 = " << h13->GetMean(2) << " +/- " << h13->GetRMS(2) << endl;

  cout << endl;
  cout << endl;

  cout << "Cov(X1,X2) = " << h12->GetCovariance() << endl;
  cout << "Cov(X1,X3) = " << h13->GetCovariance() << endl;
  cout << "Cov(X2,X3) = " << h23->GetCovariance() << endl;

  cout << endl;
  cout << endl;

  cout << "rho(X1,X2) = " << h12->GetCorrelationFactor() << endl;
  cout << "rho(X1,X3) = " << h13->GetCorrelationFactor() << endl;
  cout << "rho(X2,X3) = " << h23->GetCorrelationFactor() << endl;

  cout << endl;
  cout << endl;

  TMatrixD T1(3, 3);
  T1(0, 0) = h12->GetRMS(1) * h12->GetRMS(1);
  T1(0, 1) = h12->GetCovariance();
  T1(0, 2) = h13->GetCovariance();
  T1(1, 0) = h12->GetCovariance();
  T1(1, 1) = h12->GetRMS(2) * h12->GetRMS(2);
  T1(1, 2) = h23->GetCorrelationFactor();
  T1(2, 0) = h13->GetCovariance();
  T1(2, 1) = h23->GetCorrelationFactor();
  T1(2, 2) = h13->GetRMS(2) * h13->GetRMS(2);

  T1.Print();

  double y1 = 2 * h12->GetMean(1) + 5 * h12->GetMean(2) + h13->GetMean(2);
  double y2 = 3 + h12->GetMean(1) / 2 + 4 * h12->GetMean(2);

  TMatrixD T2(2, 3);
  T2(0, 0) = 2;
  T2(0, 1) = 5;
  T2(0, 2) = 1;
  T2(1, 0) = 0.5;
  T2(1, 1) = 4;
  T2(1, 2) = 0;

  TMatrixD T2t(3, 2);
  T2t.Transpose(T2);

  TMatrixD T3(2, 2);
  T3 = T2 * T1 * T2t;

  T3.Print();

  cout << "Y1 = " << y1 << " +/- " << T3(0, 0) << endl;
  cout << "Y2 = " << y2 << " +/- " << T3(1, 1) << endl;

  cout << "Wspolczynnik korelacji Y1, Y2: "
       << T3(0, 1) / (sqrt(T3(0, 0)) * sqrt(T3(1, 1))) << endl;
  cout << "Wspolczynnik korelacji Y2, Y1: "
       << T3(1, 0) / (sqrt(T3(0, 0)) * sqrt(T3(1, 1))) << endl;

  TCanvas *c = new TCanvas("c2", "Zadanie 4", 800, 600);
  c->Divide(2, 2);

  c->cd(1);
  h12->Draw("COLZ");

  c->cd(2);
  h13->Draw("COLZ");

  c->cd(3);
  h23->Draw("COLZ");

  return 0;
}
