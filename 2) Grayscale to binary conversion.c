///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX 255

/// to convert 8-Bmp grayscale image to binary image
void gray2binary()
{
    FILE *t = fopen("barbara.bmp", "rb");        /// Input file name
	FILE *f = fopen("graytobinary.bmp","wb");      /// Output File name

	int i;

        if (t == NULL)              /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];               /// to store the image header
	unsigned char colorTable[1024];         /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);               /// storing BMP header

 	}

	fwrite(header, sizeof(unsigned char), 54, f);        /// write the image header to output file

 	int width = *(int*)&header[18];                     /// read the width from the image header
 	int height = *(int*)&header[22];                    /// read the height from the image header
	int bitDepth = *(int*)&header[28];                  /// read the bitDepth from the image header


    int size=height*width;
    unsigned char space[height][width];
	if(bitDepth <= 8)
{
         fread(colorTable, sizeof(unsigned char), 1024, t);
		 fwrite(colorTable, sizeof(unsigned char), 1024, f);

		 fread(space,sizeof(unsigned char),size,t);	                 ///read image data

         for(int k=0;k<height;k++)
		{  for(int j=0;j<width;j++)
		    space[k][j]=(space[k][j] > THRESHOLD) ? WHITE : BLACK;    ///store 0(black) and 255(white) values to space
		}

         fwrite(space,sizeof(unsigned char),size,f);		///write back to the output image
}

 else{
       printf("NOT A 8-BIT BITMAP IMAGE!!!");
       exit(0);
 }

    printf("\nOUTPUT: output is stored in 'graytobinary.bmp' FILE\n");
	fclose(t);
 	fclose(f);

}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> for gray to binary format\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: gray2binary();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

