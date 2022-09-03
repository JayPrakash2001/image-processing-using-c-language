///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>


struct image     ///STRUCTURE DECLARATION TO STORE IMAGE INFORMATION
{
unsigned char buffer[512][512][3];
unsigned char space[512][512];
unsigned char spacex[512][512];

}r;

///function to perform translation in horizontal and vertical direction
void translate(int a,int b)
{

    FILE *t = fopen("fruit.bmp", "rb");                        /// Input file name
	FILE *f = fopen("translate.bmp","wb");                     /// Output File name

	int i,x=0,y=0,tt,ttt;
    tt=51.2*a;
    ttt=51.2*b;

        if (t == NULL)                                         /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];                                   /// to store the image header
	unsigned char colorTable[1024];                             /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);

 	}

	fwrite(header, sizeof(unsigned char), 54, f);                /// write the image header to output file

 	int width = *(int*)&header[18];
 	int height = *(int*)&header[22];
	int bitDepth = *(int*)&header[28];


    int size=height*width;
    unsigned char space[height][width];
	if(bitDepth <= 8)
{
         fread(colorTable, sizeof(unsigned char), 1024, t);
		 fwrite(colorTable, sizeof(unsigned char), 1024, f);
         fread(space,sizeof(unsigned char),size,t);              	///read image data

         for(int k=0;k<height;k++)
		{  for(int j=0;j<width;j++)
           {
               x=k+tt;                                              /// modifying the "x" coordinate of the image
               y=j+ttt;                                             /// modifying the "y" coordinate of the image
               if(x>height)
               x=x-height;
               r.space[k][j]=space[x][y];
           }
		}
          for(int k=0;k<height;k++)									///write back to the output image
		{  for(int j=0;j<width;j++)
           {
              fprintf(f,"%c",r.space[k][j]);
           }
		}
}
 else{
        unsigned char buffer1[height][width][3];							///to store the image data

	 for(int k=0;k<height;k++)
		{
		     for(int j=0;j<width;j++)
		    {
               buffer1[k][j][0]=getc(t);
		       buffer1[k][j][1]=getc(t);
		       buffer1[k][j][2]=getc(t);
	    	}
        }


           for(int k=0;k<height;k++)
        {
            for(int j=0;j<width;j++)
            {
               x=k+ttt;                                                   /// modifying the "x" coordinate of the image
               y=j+tt;                                                    /// modifying the "x" coordinate of the image
               if(x>512)
               x=x-512;

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

    printf("\nOUTPUT: output is stored in 'translate.bmp' FILE\n");
	fclose(t);
 	fclose(f);
}


int main()
{ int a,r,c,v;
printf("\t\t**ENTER** \n\n<1> to translate by factor of t(1,2..10)\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1:  printf("Enter the row translate: ");
             scanf("%d",&r);
             printf("Enter the column translate: ");
             scanf("%d",&c);
             translate(r,c);
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}
