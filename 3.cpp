// sieve of eratosthenes using openmp

#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main(){
    int n;
    cout<<"Enter the number: ";
    cin>>n;
    clock_t start=clock();
    vector<bool> prime(n+1, true);
    #pragma omp parallel for num_threads(1)
    for(int i=2;i*i<=n;i++){
        if(prime[i]){
            for(int j=i*i;j<=n;j+=i){
                prime[j]=false;
            }
        }
    }
    cout<<"Time taken: "<<(double)(clock()-start)/CLOCKS_PER_SEC<<endl;
    
    for(int i=2;i<=n;i++){
        if(prime[i]){
            cout<<i<<" ";
        }
    }
    cout<<endl;
    return 0;
}