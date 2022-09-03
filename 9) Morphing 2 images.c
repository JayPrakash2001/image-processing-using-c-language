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

///function to combine two image i.e. morphing of two images
void morph()
{

    FILE *t = fopen("lenargb.bmp","rb");                        /// Input file 1
	FILE *f = fopen("morped.bmp","wb");                          /// Output File
    FILE *s = fopen("fruit.bmp","rb");                           /// Input file 2
	int i;
	float tt;
    printf("Enter combining ratio(0,0.1...1) : ");
    scanf("%f",&tt);


        if ((s == NULL)||(t == NULL))                             /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header1[54];                                    /// to store the image header of image 1
	unsigned char header2[54];                                    /// to store the image header of image 2
	unsigned char colorTable[1024];

 	for(i=0;i<54;i++)
 	{
 		header1[i] = getc(t);
        header2[i] = getc(s);
 	}

	fwrite(header1, sizeof(unsigned char), 54, f);                /// write the image header to output file

 	int width = *(int*)&header1[18];                               /// read the width from the image header
 	int height = *(int*)&header1[22];                              /// read the height from the image header
	int bitDepth = *(int*)&header1[28];                            /// read the bitDepth from the image header

    printf("\nsuccess!!\n");
	printf("width: %d\n",width);
	printf("height: %d\n",height );

    int size=height*width;

        unsigned char buffer1[height][width][3];
        unsigned char buffer2[height][width][3];
        if(bitDepth <= 8)
{
         fread(colorTable, sizeof(unsigned char), 1024, t);
		 fwrite(colorTable, sizeof(unsigned char), 1024, f);

		 fread(r.space,sizeof(unsigned char),size,t);	            ///read image data
         fread(r.spacex,sizeof(unsigned char),size,s);

         for(int k=0;k<height;k++)
		{  for(int j=0;j<width;j++)
		    r.space[k][j]=(1-tt)*r.space[k][j]+tt*r.spacex[k][j];    ///combining the two images in a particular ratio
        }

         fwrite(r.space,sizeof(unsigned char),size,f);		          ///write back to the output image
}
else{
	 for(int k=0;k<512;k++)
		{ for(int j=0;j<width;j++)
		{
        buffer1[k][j][0]=getc(t);
        buffer2[k][j][0]=getc(s);
		buffer1[k][j][1]=getc(t);
		buffer2[k][j][1]=getc(s);
		buffer1[k][j][2]=getc(t);
		buffer2[k][j][2]=getc(s);

  			r.buffer[k][j][0] =  (1-tt)*buffer1[k][j][0]+tt*buffer2[k][j][0];          ///combining the two images in a particular ratio
			r.buffer[k][j][1] =  (1-tt)*buffer1[k][j][1]+tt*buffer2[k][j][1];          ///combining the two images in a particular ratio
		    r.buffer[k][j][2] =  (1-tt)*buffer1[k][j][2]+tt*buffer2[k][j][2];          ///combining the two images in a particular ratio
		}
		}
       for(int k=0;k<height;k++)                                                       ///writing back to the file
        {for(int j=0;j<width;j++){
        fprintf(f,"%c",r.buffer[k][j][0]);
		fprintf(f,"%c",r.buffer[k][j][1]);
		fprintf(f,"%c",r.buffer[k][j][2]);

		}
        }
}

    printf("\nOUTPUT: output is stored in 'morphed.bmp' FILE\n");
	fclose(t);
 	fclose(f);
 	fclose(s);

}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> to morph 2 image\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: morph();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

