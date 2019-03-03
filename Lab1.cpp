double funkcjaCos(double *x, double* par){
	return par[0]*TMath::Cos(x[0]);
}

int Lab1(){

	TF1* fun1 = new TF1("fun1","sin(x)",-TMath::Pi(),TMath::Pi());
	fun1->SetTitle("sinus x;x;sin(x)");

	TF1* fun2 = new TF1("fun2",funkcjaCos,-TMath::Pi(),TMath::Pi(),1);
	fun2->SetLineColor(kBlue);
	fun2->SetParameter(0,1);

	TCanvas*c = new TCanvas("c","Zadanie 1", 800, 600);
	c->Divide(2,2);
	
	c->cd(1); // przechodzimy do pierwszego padu
	fun1->Draw("L");

	c->cd(2); 
	fun2->Draw("L");

	c->cd(3); 
	fun1->Draw("L");
	fun2->Draw("L SAME");

	c->cd(4);
	
	double oczka[6] = {1, 2, 3, 4, 5, 6};
	double rzuty[6] = {2, 1, 5, 4, 10, 12};


	TH1D*h = new TH1D("h",";oczka;rzuty", 6, 0.5, 6.5);

	for(int i=0;i<6;++i){
		h->Fill(oczka[i],rzuty[i]);
	}
	
	h->Draw("HISTO");

	/*for(int i=0;i<6;++i){
		for(int j=0;j<rzuty[i];++j){
			h->Fill(oczka[i]);
		}
	}

	*/

	TCanvas*c2 = new TCanvas("c2","tytul", 400, 400);
	TGraph*g = new TGraph(6, oczka, rzuty);
	g->SetMarkerStyle(kFullCircle);
	g->SetMarkerColor(kBlack);
	g->Draw("ALP");

	return 0;
}


