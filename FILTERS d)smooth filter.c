///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX 255

///function to perform smoothening of image
void smooth()
{
    FILE *t = fopen("parrots.bmp", "rb");                                       /// Input file name
	FILE *f = fopen("smooth.bmp","wb");                                         /// Output File name

	int i,p=0,tt=0;

        if (t == NULL)                                                          /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];                                                   /// to store the image header
	unsigned char colorTable[1024];                                             /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);
 	}

	fwrite(header, sizeof(unsigned char), 54, f);                                 /// write the image header to output file

 	int width = *(int*)&header[18];
 	int height = *(int*)&header[22];
	int bitDepth = *(int*)&header[28];


    int size=height*width;
    unsigned char space[height][width];
     unsigned char buffer[height][width][3];
	if(bitDepth <= 8)
{
         fread(colorTable, sizeof(unsigned char), 1024, t);
		 fwrite(colorTable, sizeof(unsigned char), 1024, f);

		 fread(space,sizeof(unsigned char),size,t);	                            ///read image data

         for(int k=0;k<height;k++)									            ///performing mean operation
		{  for(int j=0;j<width;j++)
		    space[k][j]=(space[k][j]+space[k+1][j]+space[k+1][j+1]+space[k][j+1]+space[k-1][j+1]+space[k-1][j]+space[k-1][j-1]+space[k-1][j]+space[k+1][j-1])/9;
		}

         fwrite(space,sizeof(unsigned char),size,f);		                    ///write back to the output image
}

 else{

	 for(int k=0;k<height;k++)
		{
		    for(int j=0;j<width;j++)
		    {

                buffer[k][j][0]=getc(t);									///red
		        buffer[k][j][1]=getc(t);									///green
		        buffer[k][j][2]=getc(t);									///blue

  		      	buffer[k][j][0] =  (buffer[k][j][0]+buffer[k+1][j][0]+buffer[k+1][j+1][0]+buffer[k][j+1][0]+buffer[k-1][j+1][0]+buffer[k-1][j][0]+buffer[k-1][j-1][0]+buffer[k][j-1][0]+buffer[k+1][j-1][0])/5;          ///performing mean operation
		    	buffer[k][j][1] =  (buffer[k][j][1]+buffer[k+1][j][1]+buffer[k+1][j+1][1]+buffer[k][j+1][1]+buffer[k-1][j+1][1]+buffer[k-1][j][1]+buffer[k-1][j-1][1]+buffer[k][j-1][1]+buffer[k+1][j-1][1])/5;          ///performing mean operation
		        buffer[k][j][2] =  (buffer[k][j][2]+buffer[k+1][j][2]+buffer[k+1][j+1][2]+buffer[k][j+1][2]+buffer[k-1][j+1][2]+buffer[k-1][j][2]+buffer[k-1][j-1][2]+buffer[k][j-1][2]+buffer[k+1][j-1][2])/5;          ///performing mean operation
            }
		}
       for(int k=0;k<height;k++)
        {    for(int j=0;j<width;j++)
            {
                  fprintf(f,"%c",buffer[k][j][0]);
		          fprintf(f,"%c",buffer[k][j][1]);
		          fprintf(f,"%c",buffer[k][j][2]);

	  	    }
        }
 }
    printf("\nOUTPUT: output is stored in 'smooth.bmp' FILE\n");
	fclose(t);
 	fclose(f);

}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> for smoothening filter\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: smooth();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

