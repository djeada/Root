double funkcjagest(double *x, double *p) {
  if (x[0] < 0) {
    return 0;
  }

  else {
    return (1.0 / 6.0) * TMath::Exp(-x[0] / 6);
  }
}

double funkcjaDyst(double *y, double *p) {
  return (-1.0) * TMath::Exp(-y[0] / 6) + 1;
}

/*
int findMod(doube *array){
        int k = 0;
        double max = array[k];

        for (i = 0; i < N * N; ++i) {
        if (array[i] > max) {
                max = (int)array[i];
            k = i;
        }
        }
        return k;
}*/

int Lab2() {

  TF1 *fun1 = new TF1("fun1", funkcjagest, -1, 30, 1);
  fun1->SetTitle("f(x);x;f(x)");

  TF1 *fun2 = new TF1("fun2", funkcjaDyst, -1, 30, 1);
  fun2->SetTitle("f(x);x;f(x)");

  double tabX[100] = 0;
  double tabY[100] = 0;
  double x = 0;
  for (int i = 0; i < 100; i++) {
    if (i != 0) {
      x = -1 + 32.0 / 100 * i;
    } else {
      x = -1;
    }
    tabX[i] = x;
    tabY[i] = fun1->Integral(-1, x);
  }

  TGraph *gr1 = new TGraph(100, tabX, tabY);

  double P10 = fun2->Eval(10.0);
  double P5 = fun2->Eval(5.0);

  cout << "Prawdopodobiestwo P(5 <= X <= 10) = " << P10 - P5;

  cout << endl;
  cout << endl;

  cout << "Wartosc oczekiwana " << fun1->Mean(-1, 30);

  cout << endl;
  cout << endl;

  cout << "Wariancja " << fun1->Variance(-1, 30);

  cout << endl;
  cout << endl;

  cout << "Moda rozkladu to " << fun1->GetMaximum();

  cout << endl;
  cout << endl;

  TCanvas *c = new TCanvas("c", "Zadanie 2", 800, 600);
  c->Divide(2, 2);

  c->cd(1); // przechodzimy do pierwszego padu
  fun1->Draw("L");

  c->cd(2); // przechodzimy do drugiego.q padu
  fun2->Draw("L");

  c->cd(2);
  gr1->Draw("LP SAME");

  return 0;
}
