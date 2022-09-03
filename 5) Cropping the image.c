///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#define THRESHOLD 128


///function to perform crop operation
void crop(int ULr,int ULc,int LRr,int LRc)
{
    FILE *t = fopen("fruit.bmp", "rb");               /// Input file name
	FILE *f = fopen("crop.bmp","wb");                   /// Output File name

	int i;
	unsigned int resizeheight=ULr-LRr,resizewidth=LRc-ULc;

        if (t == NULL||f==NULL)                         /// check if the input file has not been opened successfully.
	{
            printf("File opening error occurred. Exiting program.\n");
            exit(0);
 	}

 	unsigned char header[54];                           /// to store the image header
	unsigned char colorTable[1024];                     /// to store the colorTable, if it exists.


 	for(i=0;i<54;i++)
 	{
 		header[i] = getc(t);

 	}

 	int width = *(int*)&header[18];                     /// read the width from the image header
 	int height = *(int*)&header[22];                    /// read the height from the image header
	int bitDepth = *(int*)&header[28];                  /// read the bitDepth from the image header

    char space[height][width];

    int crop_h=ULc;
    int crop_v=LRr;
    *(int*)&header[18]=resizewidth;
    *(int*)&header[22]=resizeheight;
	fwrite(header, sizeof(unsigned char), 54, f);                         /// write the image header to output file

    printf("resizewidth=%d\nresizeheight=%d\n",resizewidth,resizeheight);

  if(bitDepth <= 8)                                                        ///for grayscale
{
         fread(colorTable, sizeof(unsigned char), 1024, t);
		 fwrite(colorTable, sizeof(unsigned char), 1024, f);

         fread(space,sizeof(unsigned char),height*width,t);	               ///read image data


        for(int k=crop_v;k<resizeheight+crop_v;k++)
		{  for(int j=crop_h;j<resizewidth+crop_h;j++)
		    {
		        fprintf(f,"%c",space[k][j]);		                     ///write back to the output image
		    }
        }
}
else
    {
        unsigned char buffer[height][width][3];

       for(int k=0;k<height;k++)
		{  for(int j=0;j<width;j++)
		    {
              buffer[k][j][0]=getc(t);									///red
		      buffer[k][j][1]=getc(t);									///green
		      buffer[k][j][2]=getc(t);									///blue
            }
		}
      for(int k=crop_v;k<resizeheight+crop_v;k++)
		{  for(int j=crop_h;j<resizewidth+crop_h;j++)
		    {
                fprintf(f,"%c",buffer[k][j][0]);
		        fprintf(f,"%c",buffer[k][j][1]);
                fprintf(f,"%c",buffer[k][j][2]);

		    }
        }


    }
printf("\nOUTPUT: output is stored in 'crop.bmp' FILE\n");
fclose(f);
fclose(t);
}


int main()
{ int a,r,c,z,v,R,C;
printf("\t\t**ENTER** \n\n<1> to crop the image  \n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: printf("Enter the Upper Left row(ULr) : ");
            scanf("%d",&R);
            printf("Enter the Upper Left column(ULc) : ");
            scanf("%d",&C);
            printf("Enter the Lower Right row(LRr) : ");
            scanf("%d",&r);
            printf("Enter the Lower Right column(LRc) : ");
            scanf("%d",&c);
            crop(R,C,r,c);
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

