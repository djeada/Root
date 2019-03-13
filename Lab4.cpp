double funkcjagest(double *x, double *p){
	if (x[0] > 0 && x[0] < TMath::Pi() && x[1] > 0 && x[1] < TMath::Pi()){
		return p[0]*TMath::Cos(x[0]/2)*TMath::Sin(x[1]);
	}
	else {
		return 0;
	}
}

int Lab4(){

	double xmin=0;
	double xmax=3.14;
	double ymin=0;
	double ymax=3.14;
	
	TF2* fun1 = new TF2("fun1", funkcjagest, xmin, xmax, ymin, ymax, 1);
	fun1->SetTitle("f(x);x;f(x)");
	fun1->SetParameter(0,1);

	//constant A

	double integralValue = fun1->Integral(xmin,xmax,ymin,ymax);
	
	double paramA = 1/integralValue;
	
	cout << paramA << endl;

	fun1->SetParameter(0,paramA);

	//sampling
	double x, y;

	//TH2 (const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup, Int_t nbinsy, Double_t ylow, Double_t yup)

	TH2D* h1 = new TH2D("h1", "histogram 1", 10, xmin, xmax, 10, ymin, ymax);
	TH2D* h2 = new TH2D("h2", "histogram 2", 10, xmin, xmax, 10, ymin, ymax);
	TH2D* h3 = new TH2D("h3", "histogram 3", 10, xmin, xmax, 10, ymin, ymax);

	for(int i = 0; i < 100; i++){
		fun1->GetRandom2(x, y);
		h1->Fill(x, y);
	}

	for(int i = 0; i < 1000; i++){
		fun1->GetRandom2(x, y);
		h2->Fill(x, y);
	}

	for(int i = 0; i < 10000; i++){
		fun1->GetRandom2(x, y);
		h3->Fill(x, y);
	}
	
	h1->Sumw2();
	TH1D* hx1 = h1->ProjectionX();

	h2->Sumw2();
	TH1D* hx2 = h2->ProjectionX();

	h3->Sumw2();
	TH1D* hx3 = h3->ProjectionX();

	TCanvas*c1 = new TCanvas("c1","Zadanie 4", 800, 600);
	c1->Divide(2,2);
	
	c1->cd(1);
	hx1->Draw("Ep");

	c1->cd(2); 
	hx2->Draw("Ep");

	c1->cd(3); 
	hx3->Draw("Ep");

	//scalling

	double integralValueH1 = h1->Integral(xmin,xmax,ymin,ymax, "width");
	double paramB = 1/integralValueH1;
	h1->Scale(paramB);

	double integralValueH2 = h2->Integral(xmin,xmax,ymin,ymax, "width");
	double paramC = 1/integralValueH2;
	h2->Scale(paramC);

	double integralValueH3 = h3->Integral(xmin,xmax,ymin,ymax, "width");
	double paramD = 1/integralValueH3;
	h3->Scale(paramD);

	cout << "Expected Value H1: \n E(x): " << h1->GetMean(1) << " E(y): " << h1->GetMean(2) << endl;
	cout << "Expected Value H2: \n E(x): " << h2->GetMean(1) << " E(y): " << h2->GetMean(2) << endl;
	cout << "Expected Value H3: \n E(x): " << h3->GetMean(1) << " E(y): " << h3->GetMean(2) << endl;

	cout << endl;
	cout << endl;

	cout << "Standard Deviation H1: \n sigma(x): " << h1->GetRMS(1) << " sigma(y): " << h1->GetRMS(2) << endl;
	cout << "Standard Deviation H2: \n sigma(x): " << h2->GetRMS(1) << " sigma(y): " << h2->GetRMS(2) << endl;
	cout << "Standard Deviation H3: \n sigma(x): " << h3->GetRMS(1) << " sigma(y): " << h3->GetRMS(2) << endl;

	cout << endl;	
	cout << endl;

	cout << "Covariance H1: \n cov(x, y): " << h1->GetCovariance() << endl;
	cout << "Covariance H2: \n cov(x, y): " << h2->GetCovariance() << endl;
	cout << "Covariance H3: \n cov(x, y): " << h3->GetCovariance() << endl;

	cout << endl;	
	cout << endl;

	cout << "Correlation Factor H1: \n ro(x, y): " << h1->GetCorrelationFactor() <<  endl;
	cout << "Correlation Factor H2: \n ro(x, y): " << h2->GetCorrelationFactor() << endl;
	cout << "Correlation Factor H3: \n ro(x, y): " << h3->GetCorrelationFactor() <<  endl;

	TCanvas*c2 = new TCanvas("c2","Zadanie 4", 800, 600);
	c2->Divide(2,2);
	
	c2->cd(1); // przechodzimy do pierwszego padu
	fun1->Draw("SURF1");
	
	c2->cd(2);
	h1->Draw("LEGO2");

	c2->cd(3);
	h2->Draw("LEGO2");

	c2->cd(4);
	h3->Draw("LEGO2");

	return 0;
}


