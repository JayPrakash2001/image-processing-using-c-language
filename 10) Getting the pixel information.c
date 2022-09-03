///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX 255

struct image     ///STRUCTURE DECLARATION TO STORE IMAGE INFORMATION
{
unsigned char buffer[512][512][3];
unsigned char space[512][512];
unsigned char spacex[512][512];

}r;

///function to get pixel information
void getpixel(int r,int c)
{
    FILE *t = fopen("fruit.bmp", "rb");                                    /// Input file name
	FILE *f = fopen("getpixel.txt","wb");                               /// Output File name

	int i;

        if (t == NULL)                                                  /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];                                           /// to store the image header
	unsigned char colorTable[1024];                                     /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);

 	}

 	int width = *(int*)&header[18];                                     /// read the width from the image header
 	int height = *(int*)&header[22];                                    /// read the height from the image header
	int bitDepth = *(int*)&header[28];                                  /// read the bitDepth from the image header


    int size=height*width;
    unsigned char space[height][width];
	if(bitDepth <= 8)
{
         fread(colorTable, sizeof(unsigned char), 1024, t);

		 fread(space,sizeof(unsigned char),size,t);	                     /// read image data
         fprintf(f,"pixel value at(%d,%d) is: %d",r,c,space[r][c]);

}

 else{
       unsigned char buffer[height][width][3];							         /// to store the image data


	 for(int k=0;k<height;k++)
		{ for(int j=0;j<width;j++)
		  {
               buffer[k][j][0]=getc(t);
		       buffer[k][j][1]=getc(t);
		       buffer[k][j][2]=getc(t);
		  }
        }

     fprintf(f,"pixel value at (%d,%d) : [(%d,%d,%d)]",r,c,buffer[r][c][0],buffer[r][c][1],buffer[r][c][2]);



 }  printf("\nOUTPUT: output is stored in 'getpixel.txt' FILE\n");
	fclose(t);
 	fclose(f);
}

int main()
{ int a,r,c;
printf("\t\t**ENTER** \n\n<1> to get information about the pixel t\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1:  printf("Enter the row : ");
             scanf("%d",&r);
             printf("Enter the column : ");
             scanf("%d",&c);
             getpixel(r,c);
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}
