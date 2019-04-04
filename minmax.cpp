#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	long int n;
	cin>>n;
	double in[5000][2];
	int ct[5000];
	double maxlat = -1000, maxlng = -1000, minlat = 1000, minlng = 1000;
	for(int i = 0; i < n; i++){
		double lat, lng;
		int c;
		cin>>lat>>lng>>c;
		in[i][0] = lat;
		in[i][1] = lng;
		ct[i] = c;
		if(lat > maxlat)
			maxlat = lat;
		if(lat < minlat)
			minlat = lat;
		if(lng > maxlng)
			maxlng = lng;
		if(lng < minlng)
			minlng = lng;
	}
	cout.precision(17);
	cout<<minlat<<" "<<minlng;
}
