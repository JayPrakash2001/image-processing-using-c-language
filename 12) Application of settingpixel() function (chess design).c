///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>

///function to implement setpixel function
void chessboard()
{
    FILE *t = fopen("parrots.bmp", "rb");                 /// Input file name
	FILE *f = fopen("chessdesign.bmp","wb");              /// Output File name

	int i;


        if (t == NULL)                                     /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];                               /// to store the image header
	unsigned char colorTable[1024];                         /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);

 	}

	fwrite(header, sizeof(unsigned char), 54, f);           /// write the image header to output file

 	int width = *(int*)&header[18];                         /// read the width from the image header
 	int height = *(int*)&header[22];                        /// read the height from the image header
	int bitDepth = *(int*)&header[28];                      /// read the bitDepth from the image header


    int size=height*width;
    unsigned char space[height][width];
	if(bitDepth <= 8)
{        int i=0,z=0,j=0;
         fread(colorTable, sizeof(unsigned char), 1024, t);
		 fwrite(colorTable, sizeof(unsigned char), 1024, f);

		 fread(space,sizeof(unsigned char),size,t);

          while(z!=4)
        {
            while(i!=4)
        {
            for(int k=i*128;k<(i*128+64);k++)
        {
            for(j=z*128;j<(z*128+64);j++)
            {
             space[k][j]=space[j+64][k+64]=0;                     ///giving the value 0 at that pixel
            }
        }
         ++i;
        }i=0;
        ++z;
        }
         fwrite(space,sizeof(unsigned char),size,f);		      ///write back to the output image
}

 else{
        unsigned char buffer[height][width][3];

	 for(int k=0;k<height;k++)
		{  for(int j=0;j<width;j++){
        buffer[k][j][0]=getc(t);
		buffer[k][j][1]=getc(t);
		buffer[k][j][2]=getc(t);

		}}

        int i=0,z=0,j=0;
          while(z!=4)
        {
            while(i!=4)
        {
            for(int k=i*128;k<(i*128+64);k++)
        {
            for(j=z*128;j<(z*128+64);j++)
            {
              buffer[k][j][0]=buffer[j+64][k+64][0]=0;
              buffer[k][j][1]=buffer[j+64][k+64][1]=0;
              buffer[k][j][2]=buffer[j+64][k+64][2]=0;
            }
        }
            ++i;
        }i=0;
        ++z;
        }
     for(int k=0;k<height;k++)
        {for(int j=0;j<width;j++){
        fprintf(f,"%c",buffer[k][j][0]);
		fprintf(f,"%c",buffer[k][j][1]);
		fprintf(f,"%c",buffer[k][j][2]);

		}
        }
 }

    printf("\nOUTPUT: output is stored in 'chessdesign.txt' FILE\n");
	fclose(t);
 	fclose(f);
}


int main()
{ int a,r,c,v;
printf("\t\t**ENTER** \n\n<1> Application of set pixel() function (chessboard design)\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1:  chessboard();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

