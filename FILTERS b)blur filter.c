///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX 255

///function to perform blur operation
void blur()
{
    FILE *t = fopen("lenargb.bmp","rb");			        /// Input File name
	FILE *f = fopen("blurfilter.bmp","wb");		    	/// Output File name

	int i,j,y, x;
	unsigned char head[54];

	if(t==NULL)							              /// check if the input file has not been opened successfully.
	{
		printf("File does not exist.\n");
	}

	for(i=0;i<54;i++)						    /// read the 54 byte header from t
	{
		head[i] = getc(t);
	}

	fwrite(head,sizeof(unsigned char),54,f);			/// write the header back


	int height = *(int*)&head[18];
	int width = *(int*)&head[22];
	int bitDepth = *(int*)&head[28];


	int size = height*width;					       /// calculate the image size

	unsigned char buffer[size][3];					   /// store the input image data
	unsigned char out[size][3];					       /// store the output image data

	for(i=0;i<size;i++)
	{
		buffer[i][2]=getc(t);					/// blue
		buffer[i][1]=getc(t);					/// green
		buffer[i][0]=getc(t);					/// red
	}

	float v=1.0 / 10.0;						     /// initialize the blurring matrix
	float kernel[3][3]={{v,v,v},
						{v,v,v},
						{v,v,v}};

	for(x=1;x<height-1;x++)
	{
		for(y=1;y<width-1;y++)
		{
			float sum0= 0.0;
			float sum1= 0.0;
			float sum2= 0.0;
			for(i=-1;i<=1;++i)
			{
				for(j=-1;j<=1;++j)
				{

					sum0=sum0+(float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][0];
					sum1=sum1+(float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][1];
					sum2=sum2+(float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][2];
				}
			}
			out[(x)*width+(y)][0]=sum0;
			out[(x)*width+(y)][1]=sum1;
			out[(x)*width+(y)][2]=sum2;
		}
	}

	for(i=0;i<size;i++)						/// write image data back to the file
	{
		putc(out[i][2],f);
		putc(out[i][1],f);
		putc(out[i][0],f);
	}
    printf("\nOUTPUT: output is stored in 'blurfilter.bmp' FILE\n");
	fclose(f);
	fclose(f);
}


int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> for blur effect\\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: blur();
            break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

