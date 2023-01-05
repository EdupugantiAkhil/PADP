// mpi program to send and receive messages between processes
#include<bits/stdc++.h>
#include<mpi.h>

using namespace std;

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    

    if(rank==0){
        string s[2]={"Hello", "World"};
        for(int i=0; i<2; i++){
            MPI_Send(s[i].c_str(), s[i].length()+1, MPI_CHAR, i+1, 0, MPI_COMM_WORLD);
        }
    }
    else{
        string b;
        b.resize(100);
        MPI_Recv(&b[0], 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout<<"Rank"<<rank<<" received "<<b<<endl;
    }


    MPI_Finalize();
    return 0;
}