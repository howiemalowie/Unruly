//
// Created by howiemalowie on 5/6/19.
//

#include <stdio.h>
#include <stdlib.h>

int readGrid(char* filename, int grid[8][8]){

    FILE *reader = fopen(filename, "r");
    char line[1];


    fgets(line, sizeof(line), reader);
    int n = line;

    int rowCountBlack[8] = {};
    int colCountBlack[8] = {};
    int rowCountWhite[8] = {};
    int colCountWhite[8] = {};


    //Validity check and read input
    for(int i=0; i<2*n; i++){
        for(int j=0; j<2*n; j++){

            fgets(line, sizeof(line), reader);

            grid[i][j] = line;

            int a = grid[i][j];
            if(a == 0){
                rowCountBlack[i]++;
                colCountBlack[j]++;
                if(rowCountBlack[i] > n || colCountBlack[j] > n){
                    printf("instance not valid");
                    return 0;
                }
            }
            else if(a == 1){
                rowCountWhite[i]++;
                colCountWhite[j]++;
                if(rowCountWhite[i] > n || colCountWhite[j] > n){
                    printf("instance not valid");
                    return 0;
            }
        }

            if(j>=2){
                if(grid[i][j-1] == a && grid[i][j-2] == a){
                    printf("instance not valid");
                    return 0;
                }
            }
            if(i>=2){
                if(grid[i-1][j] == a && grid[i-2][j] == a){
                    printf("instance not valid");
                    return 0;
                }
            }
        }
    }

    return 1;
}