#include<iostream>
#include<iomanip>
using namespace std;

int main(){
		cout.precision(8);
        double x1[5000], y1[5000], x, y;
        double x2[5000], y2[5000];
        int n, t1 = 0, t2 = 0, a;
        cin>>n;
        for(int i = 1; i <= n; i++){
                cin>>y>>x>>a;
                if(a == 1){
                	x1[t1] = x;
                	y1[t1] = y;
                	t1++;
                }
                else{
                	x2[t2] = x;
                	y2[t2] = y;
                	t2++;
                }
        }
        cout<<"x1 = [";
        for(int i = 0; i < t1-1; i++){
        	cout<<x1[i]<<", ";
        }
        cout<<x1[t1-1]<<"];"<<endl;
        cout<<"y1 = [";
        for(int i = 0; i < t1-1; i++){
        	cout<<y1[i]<<", ";
        }
		cout<<y1[t1-1]<<"];"<<endl;
        cout<<"x2 = [";
        for(int i = 0; i < t2-1; i++){
        	cout<<x2[i]<<", ";
        }
        cout<<x2[t2-1]<<"];"<<endl;
        cout<<"y2 = [";
        for(int i = 0; i < t2-1; i++){
        	cout<<y2[i]<<", ";
        }
		cout<<y2[t2-1]<<"];"<<endl;
		cout<<"scatter(x1,y1);"<<endl;
		cout<<"hold on;"<<endl;
		cout<<"scatter(x2,y2);"<<endl;
		cout<<"hold off;"<<endl;
}
