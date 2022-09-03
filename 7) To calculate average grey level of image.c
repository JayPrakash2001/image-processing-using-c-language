///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>


///to calculate mean value of a gray image
void meangray()
{
    FILE *t = fopen("lenagray.bmp", "rb");            /// Input file name
	FILE *f = fopen("meangray.txt","wb");            /// Output File name

	int i;
	long int count=0;

        if (t == NULL)                               /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];                      /// to store the image header
	unsigned char colorTable[1024];                /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);

 	}


 	int width = *(int*)&header[18];                 /// read the width from the image header
 	int height = *(int*)&header[22];                /// read the height from the image header
	int bitDepth = *(int*)&header[28];              /// read the bitDepth from the image header


    int size=height*width;
    unsigned char space[height][width];
	if(bitDepth <= 8)
{
         fread(colorTable, sizeof(unsigned char), 1024, t);

		 fread(space,sizeof(unsigned char),size,t);	                     ///read image data

         for(int k=0;k<height;k++)
		{  for(int j=0;j<width;j++)
		    count=count+(int)space[k][j];                                 ///adding pixel values
		}
        count=count/size;
         fprintf(f,"Mean gray value is : %d ",count);		              ///write back to the output image
}
printf("\nOUTPUT: output is stored in 'meangray.txt' FILE\n");
fclose(f);
fclose(t);
}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> to calculate average gray level of image \n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: meangray();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}


