/**
Author: Bruno Vasconcellos
USF ID: 93067202
Description: This program will take a user file as input then it will sort it according to the treatment cost, using a sorting algorithm.
Moreover, it will use a loop to only select hospitals in the file that have a rating of 3 or more, and that its quality is
average or better.
In the end, the program should return all this filtered information in "output.csv" file.
**/

#include<stdio.h>
#include<string.h>
#define NH 300
#define HOSP_LEN 150
#define CTST_LEN 50

//structure declaration
struct hospital{

    char hospital_name[HOSP_LEN+1];
    char city[CTST_LEN+1];
    char state[CTST_LEN+1];
    char value[NH+1];
    char quality[NH+1];
    int rating;
    int cost;

};

void sort_hospital(struct hospital list[], int n);

int main(){

    struct hospital list[NH];
    char file_name[NH];
    int i = 0, j = 0;

    FILE *iFile; //input file
    FILE *oFile; //output file

    //user prompt to input the file
    printf("Enter the file name: ");
    scanf("%s", file_name);

    //opening the input file
    iFile = fopen(file_name, "r");
    //oFile = fopen("output.csv", "w");

   //error handling(input)
   if(iFile == NULL){
        printf("Error opening the file.");
        return 1;
   }

   /*this while loop will fscanf all rows and columns in the original file to be used later on in the
   output file
   */
   while(!feof(iFile) && !ferror(iFile)){
        fscanf(iFile,"%[^,], %[^,], %[^,], %d, %d, %[^,], %s\n", list[i].hospital_name, list[i].city, list[i].state, &list[i].rating, &list[i].cost, list[i].quality, list[i].value);
        i++;
   }

   //function invoking -> this will sort all the previously scanned info in ascending cost of treatment
   sort_hospital(list, NH);

   //declaring the output file
   oFile = fopen("output.csv", "w");

   //error handling
   if(oFile == NULL){
        printf("Error opening the file.");
        return 1;
   }

    //filtering the result based on rating and quality
    for(j = 0; j < NH; j++){
        if(list[j].rating >= 3 && (strcmp(list[j].quality, "Better") == 0 || strcmp(list[j].quality, "Average") == 0)){
            fprintf(oFile, "%s, %s, %s, %d, %d, %s, %s \n", list[j].hospital_name, list[j].city, list[j].state, list[j].rating, list[j].cost, list[j].quality, list[j].value);
        }
        else
            continue;
   }

    //close the files
    fclose(iFile);
    fclose(oFile);

    return 0;
}

//sorting function -> will take a struct input of size n and sort it in ascending order
void sort_hospital(struct hospital list[], int n){
   struct hospital temp;
    int i, largest = 0;

    if (n == 1)
        return;

    for(i = 1; i < n; i++){
        if(list[i].cost > list[largest].cost)
            largest = i;
    }

    if (largest < n - 1){
        temp = list[n - 1];
        list[n - 1] = list[largest];
        list[largest] = temp;
    }

    sort_hospital(list, n - 1);

}//end of function
