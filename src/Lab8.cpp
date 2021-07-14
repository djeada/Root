double funkcjagest(double *x, double *p) {
  if (x[0] >= 0 && x[0] <= 2) {
    return 5;
  } else {
    return 0;
  }
}

void splot(TF1 **f, int k, TH1D *h, int n) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      sum += f[j]->GetRandom();
    }
    h->Fill(sum);
    sum = 0;
  }
}

TH1D *galton(int n, int l, double p) {

  TH1D *h = new TH1D("h", "Tablica Galtona", 2 * l, -1 * l, l);

  double randomino = 0;
  int position = 0;
  TRandom3 rand;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < l; j++) {
      randomino = rand.Uniform(0, 1);

      if (randomino > p)
        position++;
      else
        position--;
    }
    h->Fill(position);
    position = 0;
  }

  return h;
}

int Lab8() {

  TF1 *fun1 = new TF1("fun1", funkcjagest, 0, 2, 1);
  fun1->SetTitle("f(x);x;f(x)");

  TH1D *h1 = new TH1D("h1", "Splot rozkladow jednostajnych", 100, 0, 10);
  TH1D *h2 = new TH1D("h2", "Rozklad;x;y", 100, 0, 10);
  TH1D *h3 = new TH1D("h3", "Rozklad;x;y", 100, 0, 10);

  TF1 *arr1[4] = {fun1, fun1, fun1, fun1};
  TF1 *arr2[3] = {fun1, fun1, fun1};
  TF1 *arr3[2] = {fun1, fun1};

  splot(arr1, 4, h1, 10000);
  splot(arr2, 3, h2, 10000);
  splot(arr3, 2, h3, 10000);

  TCanvas *c = new TCanvas("c", "Zad 8", 800, 600);
  c->Divide(2, 2);

  c->cd(1);
  h1->Draw();
  h3->SetLineColor(kGreen);
  h2->Draw("SAME");
  h3->SetLineColor(kRed);
  h3->Draw("SAME");

  TF1 *fun2 = new TF1("fun2", "TMath::Gaus(x, 1.0, 0.2)", 0, 10);
  TF1 *fun3 = new TF1("fun3", "TMath::Gaus(x, 3.0, 0.5)", 0, 10);

  TF1 *arrGauss[2] = {fun2, fun3};

  TH1D *hGauss = new TH1D("hGauss", "Splot rozkladow normalnych", 100, 0, 10);

  splot(arrGauss, 2, hGauss, 10000);

  c->cd(2);
  hGauss->Draw();

  cout << "Wartosc oczekiwana Gaus1: \n E(x): " << fun2->Mean(0, 10) << endl;
  cout << "Wartosc oczekiwana Gaus2: \n E(x): " << fun3->Mean(0, 10) << endl;
  cout << "Wartosc oczekiwana Splot Gausow: \n E(x): " << hGauss->GetMean()
       << endl;

  cout << endl;
  cout << endl;

  cout << "Odchylenie standardowe Gaus1: \n sigma(x): " << fun2->Variance(0, 10)
       << endl;
  cout << "Odchylenie standardowe Gaus2: \n sigma(x): " << fun3->Variance(0, 10)
       << endl;
  cout << "Odchylenie standardowe Splot Gausow: \n sigma(x): "
       << hGauss->GetRMS() * hGauss->GetRMS() << endl;

  TH1D *hGalton = galton(10000, 100, 0.5);

  c->cd(3);
  hGalton->Draw();

  return 0;
}
