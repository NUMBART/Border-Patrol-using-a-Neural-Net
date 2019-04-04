#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	long int n;
	cin>>n;
	cout<<n<<endl;
	for(int i = 0; i < n; i++){
		double lat, lng;
		int c;
		cin>>lat>>lng>>c;
		cout<<lat<<" "<<lng<<endl;
	}
}
