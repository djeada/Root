double funkcjagest(double *x, double *p){
	return TMath::Exp(TMath::Sin(x[0])-TMath::Cos(2*x[0]));
}


double losujVonNeumann(TF1 *g, double min, double max){
	double x, y;	
	int interval = 100;

	do{
		x = double(rand() % (interval + 1)) / interval; 
   	 	y = double(rand() % (interval + 1)) / interval; 
	}while ( g->Eval(x) < y && x > min && x < max);

	return x;
}


double wydajnoscVonNeumann(TF1 *g, double min, double max, int n){
	double efficency, origin_dist;
	int circle_points = 0, square_points = 0; 
	double x, y;	
	int interval = n;
	TRandom3 rand;
	do {
		x = double(rand() % (interval + 1)) / interval; 
		y = rand.Uniform(0, g->Eval(0));

    	// Distance between (x, y) from the origin 
    	origin_dist = x* x + y * y; 
  
   		// Checking if (x, y) lies inside the definecircle with R=1 
		if (origin_dist <= 1) {
            circle_points++; 
		}
  
    	// Total number of points generated 
    	square_points++; 
	}while ( g->Eval(x) < y && x > min && x < max && y > min && y < max);

	efficency= (double)circle_points/square_points;

	return efficency;
}


double calkaVonNeumann(TF1 *g, double min, double max, int n){
	return wydajnoscVonNeumann(g, min, max, n)*max*max;
}

double bladCalki(TF1 *g, double min, double max, int n){

	double Aprim = 0;
	
	if ( max*min > 0 ){
		if(g->GetMaximum()*g->GetMinimum() > 0)
			Aprim = abs((abs(max) - abs(min))*(abs(g->GetMaximum())-abs(g->GetMinimum())));
		else
			Aprim = abs((abs(max) - abs(min))*(abs(g->GetMaximum())+abs(g->GetMinimum())));
	}

	else {
		if(g->GetMaximum()*g->GetMinimum() > 0)
			Aprim = abs((abs(max) + abs(min))*(abs(g->GetMaximum())-abs(g->GetMinimum())));
		else
			Aprim = abs((abs(max) + abs(min))*(abs(g->GetMaximum())+abs(g->GetMinimum())));
	}

	double p = calkaVonNeumann(g, min, max, n)/Aprim;
	return (Aprim/sqrt(n))*sqrt(p*(1-p));
}

int Zad3(){
	double xmin=0;
	double xmax=2*TMath::Pi();

	TF1* fun1 = new TF1("fun1", funkcjagest, xmin, xmax, 1);
	fun1->SetTitle("f(x);x;f(x)");

	int iloscProbek = 300;

	double integral = calkaVonNeumann(fun1, xmin, xmax, iloscProbek);
	cout << "calka: " << integral << endl;
	cout << "blad wzgledny: " << bladCalki(fun1, xmin, xmax, iloscProbek) << endl;
	cout << "blad bezwzgledny: " << bladCalki(fun1, xmin, xmax, iloscProbek)/integral << endl;

	return 0;
}


