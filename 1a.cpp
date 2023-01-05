// montacarlo pi 
#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main(){
    int n;
    cout<<"Enter the number of points: ";
    cin>>n;
    clock_t start=clock();
    int count=0;
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        double x=(double)rand()/RAND_MAX;
        double y=(double)rand()/RAND_MAX;
        if(x*x+y*y<=1){
            count++;
        }
    }
    cout<<4*(double)count/n<<endl;
    //print program runtime
    cout<<"Time taken: "<<(double)(clock()-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}