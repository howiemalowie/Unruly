//
// Created by howiemalowie on 5/6/19.
//

#include "/home/howiemalowie/hno014/sequential/ListColoring/listColoring.h"
//#include "/home/howiemalowie/hno014/sequential/ODDs/odd.h"
#include "/home/howiemalowie/hno014/ReadFile.c"
#include <string.h>
#include <stdbool.h>

int grid[8][8];

bool vComp(char* s1, char* s2, int i, int j){

    if(grid[i][j] == 0 && s1[0] != 0){
        return false;
    }
    if(grid[i][j] == 1 && s1[0] != 1){
        return false;
    }
    if(i != 7){
        if(grid[i+1][j] == 0 && s2[0] != 0){
            return false;
        }
        if(grid[i+1][j] == 1 && s2[0] != 1){
            return false;
        }
    }
    if(i == 1){
        if(s1[3] != 1){
            return false;
        }
        if(s1[0] == 0 && s1[2] != 1){
            return false;
        }
        if(s1[0] == 1 && s1[2] != -1){
            return false;
        }
    }
    if(s2[0] == 0 && s2[2] != (s1[2]+1)){
        return false;
    }
    if(s2[0] == 1 && s2[2] != (s1[2]-11)){
        return false;
    }
    if(i = 6 && s1[2] != 0){
        return false;
    }
    if(s1[0] == 0){
        if(s2[0] == 0 && s2[3] != 1){
            return false;
        }
        if(s2[0] == 0 && s2[3] != 2){
            return false;
        }
        if(s2[0] == 1 && s2[3] != 1){
            return false;
        }
    }
    if(s1[0] == 1){
        if(s2[0] == 1 && s2[3] != 1){
            return false;
        }
        if(s2[0] == 1 && s2[3] != 2){
            return false;
        }
        if(s2[0] == 0 && s2[3] != 1){
            return false;
        }
    }
    return true;
}

bool hComp(char* s1, char* s2, int i, int j){

    if(grid[i][j] == 0 && s1[0] != 0){
        return false;
    }
    if(grid[i][j] == 1 && s1[0] != 1){
        return false;
    }
    if(i != 7){
        if(grid[i+1][j] == 0 && s2[0] != 0){
            return false;
        }
        if(grid[i+1][j] == 1 && s2[0] != 1){
            return false;
        }
    }
    if(i == 1){
        if(s1[4] != 1){
            return false;
        }
        if(s1[0] == 0 && s1[1] != 1){
            return false;
        }
        if(s1[0] == 1 && s1[1] != -1){
            return false;
        }
    }
    if(s2[0] == 0 && s2[1] != (s1[1]+1)){
        return false;
    }
    if(s2[0] == 1 && s2[1] != (s1[1]-1)){
        return false;
    }
    if(i = 6 && s1[1] != 0){
        return false;
    }
    if(s1[0] == 0){
        if(s2[0] == 0 && s2[4] != 1){
            return false;
        }
        if(s2[0] == 0 && s2[4] != 2){
            return false;
        }
        if(s2[0] == 1 && s2[4] != 1){
            return false;
        }
    }
    if(s1[0] == 1){
        if(s2[0] == 1 && s2[4] != 1){
            return false;
        }
        if(s2[0] == 1 && s2[4] != 2){
            return false;
        }
        if(s2[0] == 0 && s2[4] != 1){
            return false;
        }
    }
    return true;
}

int main(){

    int dunce = readGrid("/home/howiemalowie/hno014/instances/instance_8x8_1.txt", grid);

    LCInstance* instance;

    instance->nRows = 8;
    instance->nColumns = 8;

    int rowCountBlack[8] = {};
    int colCountBlack[8] = {};
    int rowCountWhite[8] = {};
    int colCountWhite[8] = {};

    instance->IntermediateColors = malloc(instance->nRows * sizeof(AlphabetMap*));
    instance->FinalColors = malloc(instance->nRows * sizeof(AlphabetMap*));
    instance->colorMap = malloc(instance->nRows * sizeof(ColorMap*));

    for(int i=0; i<instance->nRows; i++) {

        //??? Allocate size of structs
        instance->IntermediateColors[i] = malloc(instance->nColumns * sizeof(AlphabetMap));
        instance->FinalColors[i] = malloc(instance->nColumns * sizeof(AlphabetMap));
        instance->colorMap[i] = malloc(instance->nColumns * sizeof(ColorMap));

        for(int j=0; j<instance->nColumns; j++){

            //Final colors
            instance->FinalColors[i][j].sizeAlphabet = 3;

            instance->FinalColors[i][j].N2S = malloc(3 * sizeof(char));
            instance->FinalColors[i][j].S2N = malloc(3 * sizeof(int));

            instance->FinalColors[i][j].N2S[0] = 'b';
            instance->FinalColors[i][j].N2S[1] = 'w';
            instance->FinalColors[i][j].N2S[2] = 'g';

            instance->FinalColors[i][j].S2N[0] = 0;
            instance->FinalColors[i][j].S2N[1] = 1;
            instance->FinalColors[i][j].S2N[2] = 2;

            //Intermediate colors
            instance->IntermediateColors[i][j].sizeAlphabet = 648;

            instance->IntermediateColors[i][j].N2S = malloc(648 * sizeof(char));
            instance->IntermediateColors[i][j].S2N = malloc(648 * sizeof(int));

            int a = grid[i][j];

            if(a == 0){
                rowCountBlack[i]++;
                colCountBlack[j]++;
            }
            else if(a == 1){
                rowCountWhite[i]++;
                colCountWhite[j]++;
            }

            int x = rowCountBlack[i] - rowCountWhite[i];
            int y = colCountBlack[j] - colCountWhite[j];
            int v, h;

            if(i>0){
                if(grid[i-1][j] == a){
                   v = 2;
                }
                else{
                    v = 1;
                }
            }
            else{
                v = 1;
            }

            if(j>0){
                if(grid[i][j-1] == a){
                    h = 2;
                }
                else{
                    h = 1;
                }
            }
            else{
                h = 1;
            }

            char aa[25];
            char xx[10];
            char yy[10];
            char vv[10];
            char hh[10];

            sprintf(aa, "%d", a);
            sprintf(xx, "%d", x);
            sprintf(yy, "%d", y);
            sprintf(vv, "%d", v);
            sprintf(hh, "%d", h);

            strcat(aa,xx);
            strcat(aa,yy);
            strcat(aa,vv);
            strcat(aa,hh);

            //TODO: Figure out how to categorize colors
            instance->IntermediateColors[i][j].N2S[a] = aa;
            instance->IntermediateColors[i][j].S2N[a] = aa;


            //ColorMap
            instance->colorMap[i][j].nColors = 648;
            instance->colorMap[i][j].map = malloc(648 * sizeof(int));

            for(int k=0; k<648; k++){
                char* c = instance->IntermediateColors[i][j].N2S[k];

                if(c[0] == '0'){
                    instance->colorMap[i][j].map[k] = 0;
                }
                else{
                    instance->colorMap[i][j].map[k] = 1;
                }
            }


            //vConstraints
            instance->vConstraints[i][j].pairs = malloc(648 * sizeof(ColorPair));
            int d = 0;

            for(int s=0; s<648; s++){
                for(int t=0; t<648; t++){
                    if(vComp(instance->IntermediateColors[i][j].N2S[s], instance->IntermediateColors[i][j].N2S[t], i, j)){
                        instance->vConstraints[i][j].pairs[d].color1 = instance->IntermediateColors[i][j].N2S[s];
                        instance->vConstraints[i][j].pairs[d].color2 = instance->IntermediateColors[i][j].N2S[t];
                        d++;
                    }
                }
            }
            instance->vConstraints[i][j].nConstraints = d;


            //hConstraints
            instance->hConstraints[i][j].pairs = malloc(648 * sizeof(ColorPair));
            d = 0;

            for(int s=0; s<648; s++){
                for(int t=0; t<648; t++){
                    if(hComp(instance->IntermediateColors[i][j].N2S[s], instance->IntermediateColors[i][j].N2S[t], i, j)){
                        instance->hConstraints[i][j].pairs[d].color1 = instance->IntermediateColors[i][j].N2S[s];
                        instance->hConstraints[i][j].pairs[d].color2 = instance->IntermediateColors[i][j].N2S[t];
                        d++;
                    }
                }
            }
            instance->hConstraints[i][j].nConstraints = d;
        }
    }


}