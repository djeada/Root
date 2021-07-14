double funkcjagest(double *x, double *p) { return TMath::Exp(-x[0] * 3); }

double losujVonNeumann(TF1 *g, double min, double max) {
  double x, y;
  int interval = 100;

  do {
    x = double(rand() % (interval + 1)) / interval;
    y = double(rand() % (interval + 1)) / interval;
  } while (g->Eval(x) < y && x > min && x < max);

  return x;
}

double wydajnoscVonNeumann(TF1 *g, double min, double max, int n) {
  double efficency, origin_dist;
  int circle_points = 0, square_points = 0;
  double x, y;
  int interval = n;
  TRandom3 rand;
  do {
    x = double(rand() % (interval + 1)) / interval;
    y = rand.Uniform(0, g->Eval(0));

    // Distance between (x, y) from the origin
    origin_dist = x * x + y * y;

    // Checking if (x, y) lies inside the definecircle with R=1
    if (origin_dist <= 1) {
      circle_points++;
    }

    // Total number of points generated
    square_points++;
  } while (g->Eval(x) < y && x > min && x < max && y > min && y < max);

  efficency = (double)circle_points / square_points;

  return efficency;
}

double calkaVonNeumann(TF1 *g, double min, double max, int n) {
  return wydajnoscVonNeumann(g, min, max, n) * max * max;
}

double znajdzPI() {
  int interval = 1000;
  int i;
  double rand_x, rand_y, origin_dist, pi;
  int circle_points = 0, square_points = 0;

  TGraph *g = new TGraph();
  TGraph *h = new TGraph();

  // Initializing rand()
  srand(time(NULL));

  // Total Random numbers generated = possible x
  // values * possible y values

  for (i = 0; i < (interval * interval); i++) {

    // Randomly generated x and y values
    rand_x = double(rand() % (interval + 1)) / interval;
    rand_y = double(rand() % (interval + 1)) / interval;

    // Distance between (x, y) from the origin
    origin_dist = rand_x * rand_x + rand_y * rand_y;

    // Checking if (x, y) lies inside the definecircle with R=1

    if (origin_dist <= 1) {
      circle_points++;
      g->SetPoint(i, rand_x, rand_y);
    } else {
      h->SetPoint(i, rand_x, rand_y);
    }

    // Total number of points generated
    square_points++;

    // estimated pi after this iteration
    pi = double(4 * circle_points) / square_points;
  }

  // For visual understanding (Optional)
  TCanvas *c = new TCanvas("c", "Liczba Pi = 3.142420", 800, 600);
  c->Divide(2, 2);

  c->cd(1); // przechodzimy do pierwszego padu
  g->Draw("AP");
  g->SetMarkerColor(kRed);
  h->Draw("SAMEP");

  return pi;
}

int Lab7() {

  double pi = znajdzPI();

  TF1 *fun1 = new TF1("fun1", funkcjagest, 0, 1, 1);
  fun1->SetTitle("f(x);x;f(x)");

  TH1D *h = new TH1D("h", "Rozklad;x;y", 100, 0, 1);

  for (int i = 0; i < 10000; ++i) {
    h->Fill(losujVonNeumann(fun1, 0, 1));
  }
  TCanvas *c = new TCanvas("c", "Zad 7", 800, 600);
  c->Divide(2, 2);
  c->cd(1);
  h->Draw("HISTO");

  double eff = wydajnoscVonNeumann(fun1, 0, 1, 30000);
  double integral = calkaVonNeumann(fun1, 0, 1, 30000);
  cout << "eff: " << eff << endl;
  cout << "calka: " << integral;

  return 0;
}
