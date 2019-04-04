#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>
using namespace std;

#define PI 3.14159265
#define i 3
#define h 31
#define o 2
#define minlat 32.506402
#define minlng 74.6793
//20 metres
#define dlat 0.00000899*20*1.3
#define dlng 0.00001067*20*1.3

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

bool isIndia(double lat, double lng){
	lat = (double)((int)(lat*1000000))/1000000;
	lng = (double)((int)(lng*1000000))/1000000;
	input[0] = 1;
	input[1] = 100000*(lat-minlat);
	input[2] = 100000*(lng-minlng);			
	calcHiddenNodes();
	calcOutputNodes();
	if(output[1].v < 0.5)
		return true;
	else 
		return false;
}

int main()
{
	
	cout.precision(8);
	//LOADING WEIGHTS
	ifstream wfile;
	wfile.open("weights.txt", std::ios_base::in);
	for(int p = 1; p <= o-1; p++)
		for(int q = 0; q <= h-1; q++)
			wfile>>w2[p][q];
	for(int p = 1; p <= h-1; p++)
		for(int q = 0; q <= i-1; q++)
			wfile>>w1[p][q];
	wfile.close();
	
	
	cout<<"Enter number of instances : ";
	int n;
	cin>>n;
	cout<<"Enter instance sets";
	for(int a = 1; a <= n; a++)				//instance number starts from 1
	{
		x[a][0] = 1;
		for(int b = 1; b <= i-1; b++)
			cin>>x[a][b];
	}
	for(int a = 1; a <= n; a++)
	{	
		double blat	= x[a][1];
		double blng = x[a][2];
		if(!isIndia(blat, blng)){
			for(double a = 0.0; a < 360.0; a += 30.0){
				double modlat = dlat * cos(a * PI/180.0);
				double modlng = dlng * sin(a * PI/180.0);
				double nlat = blat + modlat;
				double nlng = blng + modlng;
				if(isIndia(nlat, nlng)){
					cout<<blat<<" "<<blng<<endl;
					break;
				}
			}
		}
	}
}
