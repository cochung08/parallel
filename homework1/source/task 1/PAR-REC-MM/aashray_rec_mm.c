#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>
#define M 13
#define N (1<<M)
int X[N+1][N+1];
int Y[N+1][N+1];
int Z[N+1][N+1];

void set_rand() {
        for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                	X[i][j] = 1;//rand() % 10;
			Y[i][j] = 1;
			Z[i][j] = 0;
                }
        }
}

void printMatrix() {
         for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                        printf("%d ", Z[i][j]);
                }
                printf("\n");
        }
}

void rec_mm (int ztopleftX, int ztopleftY, int xtopleftX, int xtopleftY, int ytopleftX, int ytopleftY, int size, int base){
	if (size <= base){
		//Z[ztopleftX][ztopleftY] = Z[ztopleftX][ztopleftY] + X[xtopleftX][xtopleftY]*Y[ytopleftX][ytopleftY];
		for ( int i = 0; i < size; i++) {
                	for ( int k = 0; k < size; k++) {
                        	for ( int j = 0; j < size; j++) {
                                	Z[ztopleftX+i][ztopleftY+j] = Z[ztopleftX+i][ztopleftY+j]+ X[xtopleftX+i][xtopleftY+k] * Y[ytopleftX+k][ytopleftY+j];
                        	}
                        //res[i][j] = sum;
                        //sum = 0;
                	}
		}	
	} else {
		cilk_spawn rec_mm(ztopleftX, ztopleftY, xtopleftX, xtopleftY, ytopleftX, ytopleftY, size/2, base);
		cilk_spawn rec_mm(ztopleftX, ztopleftY+size/2, xtopleftX, xtopleftY, ytopleftX, ytopleftY+size/2,size/2, base);
		cilk_spawn rec_mm(ztopleftX+size/2, ztopleftY, xtopleftX+size/2, xtopleftY, ytopleftX, ytopleftY,size/2, base);
		rec_mm(ztopleftX+size/2, ztopleftY+size/2, xtopleftX+size/2, xtopleftY, ytopleftX, ytopleftY+size/2,size/2, base);
		cilk_sync;
		cilk_spawn rec_mm(ztopleftX, ztopleftY, xtopleftX, xtopleftY+size/2, ytopleftX+size/2, ytopleftY,size/2, base);
		cilk_spawn rec_mm(ztopleftX, ztopleftY+size/2, xtopleftX, xtopleftY+size/2, ytopleftX+size/2, ytopleftY+size/2,size/2, base);
		cilk_spawn rec_mm(ztopleftX+size/2, ztopleftY, xtopleftX+size/2, xtopleftY+size/2, ytopleftX+size/2, ytopleftY,size/2, base);
		rec_mm(ztopleftX+size/2, ztopleftY+size/2, xtopleftX+size/2, xtopleftY+size/2, ytopleftX+size/2, ytopleftY+size/2,size/2, base);
		cilk_sync;
	}
}

int main(){
	clock_t start, end;
  	double cpu_time_used;
	set_rand();
	//printMatrix();
	for (int i = 2; i <= 1024; i=i*2){
		start = clock();	
		rec_mm(1,1,1,1,1,1,N,i);
		end = clock();
        	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        	printf("CPU time used for m=%d is : %f\n", i, cpu_time_used);
	}//printMatrix();
	return 0;
}
