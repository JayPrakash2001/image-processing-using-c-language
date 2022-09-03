///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX 255

///function to convert grayscale into binary(0,1) text FILE
void binary()
{

    FILE *t = fopen("lenagray.bmp", "rb");                                 /// Input file name
	FILE *f = fopen("bin.txt","w+");                                      /// Output File name

	int i,x=0,y=1;

        if (t == NULL)                                                   /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];                                               /// to store the image header
    unsigned char colorTable[512];                                          /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);

 	}

 	int width = *(int*)&header[18];                                       /// read the width from the image header
 	int height = *(int*)&header[22];                                      /// read the height from the image header
	int bitDepth = *(int*)&header[28];                                    /// read the bitDepth from the image header


    int size=height*width;
    unsigned char space[height][width];
	if(bitDepth <= 8)
{

		 fread(space,sizeof(unsigned char),size,t);	                     ///read image data

        for(int k=0;k<height;k++)
        {
		    for(int j=0;j<width;j++)
		  {  space[k][j]= (space[k][j] > THRESHOLD) ? y : x;               //store 0 and 1 values to buffer
		  }
        }

         for(int k=height;k>0;k--)
       {
          for(int j=width;j>0;j--)
		  {
           fprintf(f,"%d",space[k][j]);
          }
       }
    printf("\nOUTPUT: output is stored in 'bin.txt' FILE\n");
	fclose(t);
 	fclose(f);

}
}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> for binary format\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: binary();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

