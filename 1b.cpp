//using mpi to parallelize the code to find  pi using monte carlo method
#include<bits/stdc++.h>
#include<mpi.h>

using namespace std;

int main(int argc, char *argv[]){
    int rank, size;
    clock_t start=clock();
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int n;
    if(rank==0){
        cout<<"Enter the number of points: ";
        cin>>n;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int count=0;
    for(int i=rank;i<n;i+=size){
        double x=(double)rand()/RAND_MAX;
        double y=(double)rand()/RAND_MAX;
        if(x*x+y*y<=1){
            count++;
        }
    }
    int total;
    MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank==0){
        cout<<4*(double)total/n<<endl;
    }
    int endTime = clock();
    if(rank==0){
        cout<<"Time taken: "<<(double)(endTime-start)/CLOCKS_PER_SEC<<endl;
    }
    MPI_Finalize();
    return 0;
}