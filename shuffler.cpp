#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;

int main(){
	cout.precision(8);
	srand((unsigned)time(0));
	double x[5000], y[5000];
    int n, c[5000];
    cin>>n;
    for(int i = 0; i < n; i++){
 		cin>>x[i]>>y[i]>>c[i];
    }
    int t = 10;
    while(t--){
    	for(int i = 0; i < n; i++){
    		int num = rand()%(n-1);
    		double temp = x[i];
    		x[i] = x[num];
    		x[num] = temp;
    		temp = y[i];
    		y[i] = y[num];
    		y[num] = temp;
    		int t = c[i];
    		c[i] = c[num];
    		c[num] = t;
    	}
    }
    cout << n << endl;
    for(int i = 0; i < n; i++, cout<<endl){
    	cout<<x[i]<<" "<<y[i]<<" "<<c[i];
    }
}
