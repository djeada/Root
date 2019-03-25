double funkcjagest(double *x, double *p){
	if (x[0] >= 0 ){
		return (1/p[0])*TMath::Exp(-x[0]/p[0]);
	}
	else {
		return 0;
	}
}

double funkcjaOdwrotna(double *x, double *p){
	if (x[0] >= 0 ){
		return -p[0]*TMath::Log(-x[0]);
	}
	else {
		return 0;
	}
}

unsigned long long m,g,c,x,x0;

void LCG(unsigned int g, int m, int d){

    unsigned int x = 1, c = 0;

	string Result;         

	ostringstream convert;   

	convert << d;     

	Result = convert.str();	

	string str = "losowe";
	str = str + "" + Result + ""+ ".dat";

	ofstream myfile (str.c_str());

    if (myfile.is_open()){
		for(int i=0; i<100000; i++){
			x = (g * x + c) % m;
			double value = static_cast<double>(x) / (double)(1.0 * (m*1));
	
        	myfile << value  << endl; 
		}

        myfile.close();
    }   
}



int Lab6(){

	LCG(97,23,1);
	LCG(32363,157,2);
	LCG(147483647,16807,3);

	double xmin=0;
	double xmax=1;
	double ymin=0;
	double ymax=1;
	int n = 0;
	
	TH2D* h12 = new TH2D("h12", "histogram 12", 100, xmin, xmax, 100, ymin, ymax);
	TH2D* h13 = new TH2D("h13", "histogram 13", 100, xmin, xmax, 100, ymin, ymax);
	TH2D* h23 = new TH2D("h23", "histogram 23", 100, xmin, xmax, 100, ymin, ymax);

	ifstream in1, in2, in3;
	in1.open("losowe1.dat");
	in2.open("losowe2.dat");
	in3.open("losowe3.dat");

    double arr1[100000];
	double arr2[100000];
	double arr3[100000];
	
	while(in1 >> arr1[n]){
		in2 >> arr2[n];
		in3 >> arr3[n];
  		n++;
	}
	for(int i=1; i<100000; i++){
		h12->Fill(arr1[i-1], arr1[i]);
		h13->Fill(arr2[i-1], arr2[i]);
		h23->Fill(arr3[i-1], arr3[i]);
	}

	TCanvas*c = new TCanvas("c2","Zadanie 5", 800, 600);
	c->Divide(2,2);

	c->cd(1);
	h12->Draw("COLZ");

	c->cd(2);
	h13->Draw("COLZ");

	c->cd(3);
	h23->Draw("COLZ");


	TF1* fun1 = new TF1("fun1", funkcjagest, xmin, xmax, 1);
	fun1->SetTitle("f(x);x;f(x)");
	fun1->SetParameter(0,2); 


	TF1* fun2 = new TF2("fun1", funkcjaOdwrotna, xmin, xmax, 1);
	fun2->SetTitle("f(x);x;f(x)");
	fun2->SetParameter(0,2); 

	TH1D* h1 = new TH1D("h1", "histogram 1", 10, xmin, xmax);
	TH1D* h2 = new TH1D("h2", "histogram 2", 10, xmin, xmax);
	TH1D* h3 = new TH1D("h3", "histogram 3", 10, xmin, xmax);

	for(int i = 0; i < 100; i++){
		fun1->GetRandom(x);
		h1->Fill(x);
	}

	for(int i = 0; i < 1000; i++){
		fun1->GetRandom(x);
		h2->Fill(x);
	}

	for(int i = 0; i < 10000; i++){
		fun1->GetRandom(x);
		h3->Fill(x);
	}

	TCanvas*c2 = new TCanvas("c2","Zadanie 5", 800, 600);
	c2->Divide(2,2);
	
	c2->cd(1);
	h1->Draw("Ep");

	c2->cd(2); 
	h2->Draw("Ep");

	c2->cd(3); 
	h3->Draw("Ep");

	return 0;
}




