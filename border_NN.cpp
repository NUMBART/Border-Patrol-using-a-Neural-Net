#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<fstream>
using namespace std;

#define i 3
#define h 31
#define o 2
class node{
	public:
		double u;
		double v;
		void calcv()
		{
			v = (1/(1 + exp(-1*u)));
		}
};

node hidden[h], output[o];					//o-1 ouput nodes 1 useless kept for convenience in indexing
double input[i];							//i-1 actual inputs + 1 bias
double w1[h][i], w2[o][h];					//1 useless layer also present with garbage
int y[2000][o];
double x[2000][i];	
double woi[2000][i];						//wrongly predicated testcase input ,output and iterator
int woo[2000][o];
long int woit = 0;

void calcHiddenNodes(){
	hidden[0].v = 1;
	for( int a = 1; a <= h-1; a++)				// h-1 nodes to be processed
	{
		hidden[a].u = 0;
		for(int b = 0; b <= i-1; b++)
		{
			hidden[a].u += input[b]*w1[a][b];
		}
		hidden[a].calcv();
	}
}

void calcOutputNodes(){
	for( int a = 1; a <= o-1; a++)				
	{
		output[a].u = 0;
		for(int b = 0; b <= h-1; b++)
		{
			output[a].u += hidden[b].v*w2[a][b];
		}
		output[a].calcv();
	}
}

double sig(double x){
	return (1/(1+exp(-x)));
}

double dsig(double x){
	return (sig(x)*(1-sig(x)));
}

double weightModSecondLayer(int y, double ov, double ou, double hv){
	return (0.1 * ((double)y-ov) * dsig(ou) * hv);
}

double weightModFirstLayer(int a, int p, double in){
	double sum = 0;
	for(int b = 1; b <= o-1; b++){			//b same as k p as j for i, j, k ref. to copy 
		sum += ( ((double)y[a][b]-output[b].v) * dsig(output[b].u) * w2[b][p]);
	}
	return (0.1 * dsig(hidden[p].u) * in * sum);
}

int main()
{
	cout.precision(8);
	//SEEDING TIMER
	srand((unsigned)time(0));
	//TAKING INPUT FOR TRAINING
	cout<<"Enter number of instances : ";
	int n;
	cin>>n;
	cout<<"Enter instance sets";
	for(int a = 1; a <= n; a++)				//instance number starts from 1
	{
		x[a][0] = 1;
		for(int b = 1; b <= i-1; b++)
			cin>>x[a][b];
		for(int b = 1; b <= o-1; b++)
			cin>>y[a][b];
	}
	
	//INITIALIZING WEIGHTS
	for(int a = 0; a <= i-1; a++)for(int b = 0; b <= h-1; b++)w1[b][a] = rand()%10 - 5;
	for(int a = 0; a <= h-1; a++)for(int b = 0; b <= o-1; b++)w2[b][a] = rand()%10 - 5;
	
	//LEARNING PHASE
	int count = 0;
	do{
		count = 0;
		woit = 0;
		ofstream myfile;
		myfile.open ("wrongOutputs.txt");
		myfile.precision(8);
		double neterror = 0.0;		
		double modw1[h][i], modw2[o][h];
		for(int a = 0; a <= i-1; a++)for(int b = 0; b <= h-1; b++)modw1[b][a] = 0;
		for(int a = 0; a <= h-1; a++)for(int b = 0; b <= o-1; b++)modw2[b][a] = 0;
		
		//FINDING MODIFICATION REQUIRED FOR BATCH
		for(int a = 1; a <= n; a++)
		{
			//CALCULATING NETWORK OUTPUT
			for(int p = 0; p < i; p++)
				input[p] = x[a][p];
				
			calcHiddenNodes();
			calcOutputNodes();	
					
			//CALCULATING ERROR ONLY FOR TRACKING TRAINING
			double error = 0;
			for(int p = 1; p <= o-1; p++)
			{
				double term = y[a][p] - output[p].v;
				if(term < 0)
					term = term*(-1);
				error += term;
			}
			error = error/(o-1)*100;
			neterror += error;
			if(error > 20){
				count++;
				for(int p = 1; p < i; p++){
					woi[woit][p] = input[p];
					myfile<<input[p]<<" ";
				}
				for(int b = 1; b <= o-1; b++){
					woo[woit][b] = y[a][b];
					myfile<<y[a][b]<<" "<<output[b].v;
				}
				woit++;
				myfile<<endl;
			}
			
			//CALCULATING WEIGHT UPDATES
			//2nd layer
			for(int p = 1; p <= o-1; p++)
				for(int q = 0; q <= h-1; q++)
					modw2[p][q] += weightModSecondLayer(y[a][p], output[p].v, output[p].u, hidden[q].v);
				
			//1st layer
			for(int p = 1; p <= h-1; p++)
				for(int q = 0; q <= i-1; q++)
					modw1[p][q] += weightModFirstLayer(a, p, input[q]);
				
		}
		//UPDATING WEIGHTS
		//2nd layer
		for(int p = 1; p <= o-1; p++)for(int q = 0; q <= h-1; q++)w2[p][q] += modw2[p][q]/n;
		//1st layer
		for(int p = 1; p <= h-1; p++)for(int q = 0; q <= i-1; q++)w1[p][q] += modw1[p][q]/n;
		
		//STORING WRONG PREDICTIONS
		ofstream file;
		file.open("wrongOutputsCopy.txt");
		file.precision(8);
		
		for(int e = 0; e < woit; e++, file<<endl){
			for(int p = 1; p < i; p++)
				file<<woi[e][p]<<" ";
			for(int p = 1; p < o; p++)
				file<<woo[e][p];
		}
		file.close();
		
		//STORING WEIGHTS
		ofstream wfile;
		wfile.open("weights.txt");
		wfile.precision(15);
		wfile<< "\n";
		for(int p = 1; p <= o-1; p++,wfile<<endl)
			for(int q = 0; q <= h-1; q++)
				wfile<<w2[p][q]<<" ";
		wfile<< "\n";
		for(int p = 1; p <= h-1; p++,wfile<<endl)
			for(int q = 0; q <= i-1; q++)
				wfile<<w1[p][q]<<" ";
		wfile.close();
		
		ofstream wcfile;
		wcfile.open("weightsCopy.txt");
		wcfile.precision(15);
		wcfile<< "2nd layer weights\n";
		for(int p = 1; p <= o-1; p++,wcfile<<endl)
			for(int q = 0; q <= h-1; q++)
				wcfile<<w2[p][q]<<" ";
		wcfile<< "1st layer weights\n";
		for(int p = 1; p <= h-1; p++,wcfile<<endl)
			for(int q = 0; q <= i-1; q++)
				wcfile<<w1[p][q]<<" ";
		wcfile.close();
		
		
		neterror = neterror/n;
		cout<<"count = "<< count<<" neterror = "<<setprecision(17)<< neterror<<endl;
		myfile.close();
		
	}while(count > 40);
	
	long long int tim = 1000000000;
	while(tim--);


			cout<< "2nd layer weights\n";
			for(int p = 1; p <= o-1; p++,cout<<endl)
				for(int q = 0; q <= h-1; q++)
					cout<<w2[p][q];
			cout<< "1st layer weights\n";
			for(int p = 1; p <= h-1; p++,cout<<endl)
				for(int q = 0; q <= i-1; q++)
					cout<<w1[p][q];
 
}
