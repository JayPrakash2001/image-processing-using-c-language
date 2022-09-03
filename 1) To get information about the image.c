///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>

void getinfo()
{
    FILE *t = fopen("lenagray.bmp","rb"); /// Input file name
	FILE *f = fopen("getinfo.txt","wb"); /// Output File name

	int i;
    unsigned char header[54];
        if (t == NULL) /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred.\n");
            exit(0);
 	}

 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);  /// storing BMP header
 	}
    i=0;

 	    fprintf(f,"%d.NO. OF ROWS:%d\n",++i,*(int*)&header[18]);
 	    fprintf(f,"%d.NO. OF COLUMN:%d\n",++i,*(int*)&header[22]);
 	    fprintf(f,"%d.BIT DEPTH :%d\n",++i,*(int*)&header[28]);
 	    fprintf(f,"%d.COMPrESSION TYPE :%d\n",++i,*(int*)&header[30]);

 	    printf("\nOUTPUT: output is stored in 'getinfo.txt' FILE\n");
 	    fclose(t);
 	    fclose(f);

}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> to get information of image \n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: getinfo();
            break;

    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}
