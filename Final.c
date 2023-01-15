#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int Search_in_File(char *str);
void replacechar(char *s);
void checkdata();
char* trim(char str[]);
void datetime(char *str);
void cat(char *cattext);

char *start = "";
char *end = "";
char *AFD = "AFD";
char *MAS = "MAS";
char *blk = "   ";

char str1[512];
char date[512];
char _time[512];
char timetemp[512];
char datetag[512];

char delim[] = " ";
char delim1[] = "T";
char delim2[] = ".";
char delim3[] = " ";


int Fmas=0;
int Fafd=0;
int count = 0;

FILE *fp;
FILE *fpt;


int find_result = 0;
int result;
int blk_count = 0;
char temp[512],temp2[512],new1[512],new2[512];
char blank[512]=" ";
char  split[512];
char* afdstring[512];
char fname[100]="";

int main() { // Start Program


    fpt = fopen("data.csv", "w+");
    fprintf(fpt,"DATE,TIME,CAT1, CAT2, CAT3, CAT4, CAT5, CAT6,CAT7, CAT8, CAT9,CAT10, NUM\n");

	result = Search_in_File("Downlink");

	fclose(fpt);
	strncpy(datetag,date,512);
    strcat(datetag,"_RGS_GES.csv");
	rename("Data.csv", datetag);
	return(0);
}

int Search_in_File(char *str) { // Start  data Search

    fp = fopen ("data.txt", "r");

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
            find_result++;
			checkdata();
		}
	}

	if(find_result == 0) {
		printf("\nNo Downlink Data available\n");
	}

	if(fp) {
		fclose(fp);
	}
   	return(0);
}

char* trim(char str[]){ // trim data

	int init_size = strlen(str);
	char delim[] = "\n";

	char *ptr = strtok(str, delim);

	while (ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	}
    return ptr;
}

void checkdata(){          // read data line by line and sort accordingly
    printf("%s \n",temp);
    datetime(temp);
    printf("%s\n", date);
    printf("%s \n",_time);
    fgets(new1, 512, fp);
    fgets(new1, 512, fp);
    if((strstr(new1, start)) != NULL) {// Actual data starting position
        trim(new1);
        fprintf(fpt,"%s ",date);
        fprintf(fpt,",%s ",_time);
        fprintf(fpt,",%s ",new1);//CAT1

        fgets(temp2, 512, fp);
        trim(temp2);
        fprintf(fpt,",%s ",temp2);//CAT2

        fgets(temp2, 512, fp);
        trim(temp2);
        fprintf(fpt,",%s ",temp2);//CAT3

    if((strstr(temp2, MAS)) != NULL)
        Fmas = 1;
    if((strstr(temp2, AFD)) != NULL)
        Fafd = 1;

        fgets(temp2, 512, fp);
        trim(temp2);
        fprintf(fpt,",%s ",temp2);//CAT4

        fgets(temp2, 512, fp);
        trim(temp2);
        cat(temp2);//CAT5, CAT6, CAT7,CAT8,CAT9

     if(Fmas == 1){// MAS data
        fprintf(fpt," ,%s",blank);

        fgets(temp2, 512, fp);
        trim(temp2);
        fprintf(fpt,",%s ",temp2);
        Fmas = 0;

     }else if(Fafd == 1) { //AFD data

        fgets(new2, 512, fp);
        trim(new2);
        replacechar(new2);
        fprintf(fpt,",'%s' ",new2);//CAT10

        fgets(temp2, 512, fp);
        trim(temp2);
        fprintf(fpt,",%s ",temp2);//NUM
        Fafd = 0;
     }else {
        fgets(temp2, 512, fp);
        trim(temp2);
        replacechar(temp2);
        fprintf(fpt,",'%s' ",temp2);//CAT10

        fgets(temp2, 512, fp);
        trim(temp2);
        fprintf(fpt,",%s ",temp2);//NUM

     }
        printf("\n");
        fprintf(fpt,"\n");
            }
}

void replacechar(char *new2)//Replace "," with ";"
{
    int i=0;
    for(i=0;new2[i];i++)
	{
		if(new2[i]==0x2C)
		{
		   new2[i]=0x3B;
	    }
	}
}

void datetime(char *dttext){ // Extract DATE and TIME
    int init_size = strlen(dttext);
    char *ptr = strtok(dttext, delim);

	while(ptr != NULL)
	{
	    count++;
		ptr = strtok(NULL, delim);
		if(count == 3){
		    strncpy(str1,ptr,512);
   		    char *ptr1 = strtok(str1, delim1);
		    strncpy(date,ptr1,512);
           // printf("%s\n", date);
	        ptr = strtok(NULL, delim1);
	        strncpy(timetemp,ptr,512);
	        char *ptr2 = strtok(timetemp, delim2);
        	strncpy(_time,timetemp,512);
            //printf("%s \n",_time);
		}
	}
	count =0;
	printf("\n");

}

void cat(char *cattext){ // Sub Categories
    int init_size1 = strlen(cattext);
    char *ptr = strtok(cattext, delim);

	while(ptr != NULL)
	{
		//printf("'%s'\n", ptr);
		fprintf(fpt,",%s ",ptr);//CAT5, CAT6, CAT7, CAT8, CAT9
		ptr = strtok(NULL, delim3);
	}

}


