///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>

///function to convert to a negative  image
void negative()
{

    FILE *t = fopen("barbara.bmp", "rb");     /// Input file name
    FILE *f = fopen("negative.bmp","wb");     /// Output File name
	int i;

        if (t == NULL)                /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];            /// to store the image header
	unsigned char colorTable[1024];      /// to store the colorTable, if it exists.
    unsigned char *iData,*oData;

 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);             /// storing image header

 	}

	fwrite(header, sizeof(unsigned char), 54, f);         /// write the image header to output file

 	int width = *(int*)&header[18];              /// read the width from the image header
 	int height = *(int*)&header[22];             /// read the height from the image header
	int bitDepth = *(int*)&header[28];           /// read the bitDepth from the image header

    int size=height*width;
    iData = (unsigned char*)malloc (size * sizeof(unsigned char));      /// allocate the block of memory as big as the image size
    oData = (unsigned char*)malloc (size * sizeof(unsigned char));

	if(bitDepth <= 8)
    {
         fread(colorTable, sizeof(unsigned char), 1024, t);
		 fwrite(colorTable, sizeof(unsigned char), 1024, f);
    }

	fread(iData,sizeof(unsigned char),size,t);		     /// read image data


	for(int  i = 0; i < height; i++)
        {
	      for(int j = 0; j < width; j++)
	      {
		     oData[i*width + j] = 255 - iData[i*width + j];

		  }
	    }

	fwrite(oData,sizeof(unsigned char),size,f);		       ///    write back to the output image
    printf("\nOUTPUT: output is stored in 'negative.bmp' FILE\n");
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
    case 1: negative();
            break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

