///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct image     ///STRUCTURE DECLARATION TO STORE IMAGE INFORMATION
{
unsigned char buffer[512][512][3];
unsigned char space[512][512];
unsigned char spacex[512][512];

}r;

/// function to perform rotation of image
void rotate(int z)
{
    FILE *t = fopen("lenargb.bmp", "rb");         /// Input file name
	FILE *f = fopen("rotate.bmp","wb");           /// Output File name

	int i,tt=1,x=0,y=0,j=0;
	double a=0.017444444*z;

        if (t == NULL)                           /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];                         /// to store the image header
	unsigned char colorTable[1024];                   /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);

 	}

	fwrite(header, sizeof(unsigned char), 54, f);       /// write the image header to output file

 	int width = *(int*)&header[18];                    /// read the width from the image header
 	int height = *(int*)&header[22];                   /// read the height from the image header
	int bitDepth = *(int*)&header[28];                 /// read the bitDepth from the image header

    int size=height*width,center;
    center=height/2;

    unsigned char space[height][width];
    unsigned char spacex[height][width];
	if(bitDepth <= 8)
{
         fread(colorTable, sizeof(unsigned char), 1024, t);
		 fwrite(colorTable, sizeof(unsigned char), 1024, f);
         fread(space,sizeof(unsigned char),size,t);	                 ///read image data

         for(int k=0;k<height;k++)									///loops to perform rotation about the center
		{  for(int j=0;j<width;j++)
           {
               x=(k-center)*cos(a)-(j-center)*sin(a)+center;
               y=(k-center)*sin(a)+(j-center)*cos(a)+center;
               if((x<0||x>height)||(y<0||y>height))
               {
                 x=y=0;
               }
               spacex[k][j]=space[x][y];
           }
		}
         fwrite(spacex,sizeof(unsigned char),size,f);		         ///write back to the output image
}

 else{
        unsigned char buffer1[height][width][3];

	 for(int k=0;k<height;k++)
		{
		     for(int j=0;j<width;j++)
		    {
               buffer1[k][j][0]=getc(t);									///red
		       buffer1[k][j][1]=getc(t);									///green
		       buffer1[k][j][2]=getc(t);									///blue
	    	}
        }


            for(int k=0;k<height;k++)
        {
            for(int j=0;j<width;j++)
            {
               x=(k-center)*cos(a)-(j-center)*sin(a)+center;
               y=(k-center)*sin(a)+(j-center)*cos(a)+center;
               if((x<0||x>512)||(y<0||y>512))
               {
                 x=y=0;
               }
              r.buffer[k][j][0]=buffer1[x][y][0];
              r.buffer[k][j][1]=buffer1[x][y][1];
              r.buffer[k][j][2]=buffer1[x][y][2];
            }
        }

     for(int k=0;k<height;k++)
        {for(int j=0;j<width;j++){
        fprintf(f,"%c",r.buffer[k][j][0]);
		fprintf(f,"%c",r.buffer[k][j][1]);
		fprintf(f,"%c",r.buffer[k][j][2]);

		}
        }
 }

    printf("\nOUTPUT: output is stored in 'rotate.bmp' FILE\n");
	fclose(t);
 	fclose(f);
}

int main()
{ int a,z;
printf("\t\t**ENTER** \n\n<1> for rotation\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: printf("Enter the angle in degree :");
             scanf("%d",&z);
             rotate(z);
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

