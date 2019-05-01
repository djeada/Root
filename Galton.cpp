#include <iostream>

using namespace std;

int Galton(){

	TCanvas*c = new TCanvas("c","Galton Table", 1600, 950);
	c->SetFillColor(kWhite);

	double p = 0.5;
	int n = 3000;

	for (int l = 10; l < 1000; l += 10) {
		TH1D*h = new TH1D("h", "Galton Table", 2 * l, -1 * l, l);

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
		sleep(500);
		h->Draw();
		c->Modified();
		c->Update();
	}

	return 0;
}


