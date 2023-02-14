/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           : main.c
 *   Deskripsi           :
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 21

int main(){
    int i,j;
   
    char filename[MAX_LEN];
    printf("Masukkan nama file input: ");
    scanf("%s", filename);
    FILE* fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\nError: file instruksi tidak tersedia!\n");
        exit(0);
    }

    //deklarasi peta awal
    char peta[MAX_LEN][MAX_LEN];
    for(i=0;i<MAX_LEN;i++){
        for(j=0;j<MAX_LEN;j++){
            peta[i][j] = '.';
        }
    }

    char line[MAX_LEN];
    char* token; 
    int koordinat[3];
    char command[MAX_LEN];
    fgets(line, MAX_LEN, fp);
    token = strtok(line, ",");
    koordinat[0] = atoi(token);
    token = strtok(NULL, "\n");
    koordinat[1] = atoi(token);
    fgets(line, MAX_LEN, fp);
    token = strtok(line, "\n");
    strcpy(command, token);

    printf("\nKoordinat awal robot adalah: (%d, %d)", koordinat[0], koordinat[1]);
    printf("\nGambar jalan yang ditempuh robot:\n");        
    
    //menerima input koordinat awal dan dikonversi ke indeks array
    int x_temp = koordinat[0]+10;
    int y_temp;
    if (y_temp<=0){
        y_temp = abs(koordinat[1])+10;}
    else{ y_temp = abs(koordinat[1]-10);}
    peta[y_temp][x_temp] = 'S';
    
    //menjalankan robot berdasarkan perintah arah dan menandai peta
    int count_command = strlen(command); //jumlah perintah
    for(i=0;i<(MAX_LEN-1);i++)
    {   
            if (i < (count_command-1)){
                if (command[i] == 'U'&& y_temp>=1){ //batas utara
                    y_temp--;
                    peta[y_temp][x_temp] = '*';
                    koordinat[1]++;
                }
                else if (command[i] == 'S'&& y_temp<=19){ //batas selatan
                    y_temp++;
                    peta[y_temp][x_temp] = '*';
                    koordinat[1]--;
                }
                else if (command[i] == 'B'&& x_temp>=1){ //batas barat
                    x_temp--;
                    peta[y_temp][x_temp] = '*';
                    koordinat[0]--;
                }      
                else if (command[i] == 'T'&& x_temp<=19){ //batas timur
                    x_temp++;
                    peta[y_temp][x_temp] = '*';
                    koordinat[0]++;
                }  
            }
            else{ //identifikasi perintah paling terakhir
                if (command[i] == 'X'){
                    peta[y_temp][x_temp] = 'E';
                    break;
                }
                else if(command[i] != 'X'){
                    j=i;
                    for(i;i<(MAX_LEN-1);i++){
                            if (command[j] == 'U' && y_temp>=1){
                                y_temp--;
                                peta[y_temp][x_temp] = '*';
                                koordinat[1]++;
                            }
                            else if (command[j] == 'S' && y_temp<=19){
                                y_temp++;
                                peta[y_temp][x_temp] = '*';
                                koordinat[1]--;
                            }
                            else if (command[j] == 'B' && x_temp>=1){
                                x_temp--;
                                peta[y_temp][x_temp] = '*';
                                koordinat[0]--;
                            }      
                            else if (command[j] == 'T' && x_temp<=19){
                                x_temp++;
                                peta[y_temp][x_temp] = '*';
                                koordinat[0]++;
                            }    
                        else{
                            peta[y_temp][x_temp] = 'E';
                            break;
                        }
                    }                 
                }
            }
    }
    peta[y_temp][x_temp] = 'E';

    //template cetak output
    for(i=0;i<MAX_LEN;i++){
        for(j=0;j<MAX_LEN;j++){
            printf("%c ", peta[i][j]);
        }
        printf("\n");
    }
    printf("\nKoordinat terakhir robot adalah: (%d, %d)", koordinat[0], koordinat[1]);
    fclose(fp);
}
