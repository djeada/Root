void splot(TF1 *f, int k, TH1D *h, int n){
	double sum = 0;
	for (int i = 0; i < n; i++){
		for(int j = 0; j < k; j++){
			sum += f->GetRandom();
		}
			h->Fill(sum);
			sum = 0;
	}
}

double funkcjagest(double *x, double *p){
	if (x[0] >= 0 && x[0] <= 2){
		return 5;
	}
	else {
		return 0;
	}
}

int Lab9b(){

  	TF1* fun1 = new TF1("fun1", funkcjagest, 0, 2, 1);
	fun1->SetTitle("f(x);x;f(x)");

	TH1D*h1 = new TH1D("h1", "Splot rozkladow jednostajnych", 100, 0, 15);

	int n = 7;
	
	splot(fun1,n,h1,10000);
	h1->Fit("gaus");

	TCanvas*c = new TCanvas("c","Zadanie 9b", 800, 600);
	c->Divide(2,2);
	c->cd(1); // przechodzimy do pierwszego padu

	h1->Draw();

	cout << h1->GetFunction("gaus")->GetChisquare() << endl;
	cout << h1->GetFunction("gaus")->GetNDF() << endl;

	double result = h1->GetFunction("gaus")->GetChisquare()/ h1->GetFunction("gaus")->GetNDF();
	cout << result  << endl;

	return 0;
}


