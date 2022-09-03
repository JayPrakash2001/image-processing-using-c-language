///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX 255

/// function to perform sepia filter operation
void sepiafilter()
{

    FILE *t = fopen("parrots.bmp","rb");					    /// Input File name
	FILE *f = fopen("sepiafilter.bmp","wb");		    		/// Output File name

	int i,r,g,b;
	unsigned char head[54];

	if(t==NULL)												/// check if the input file has not been opened successfully.
	{
		printf("File does not exist.\n");
	}

	for(i=0;i<54;i++)
	{
		head[i] = getc(t);
	}

	fwrite(head,sizeof(unsigned char),54,f);					///write the header back

	int height = *(int*)&head[18];
	int width = *(int*)&head[22];
	int bitDepth = *(int*)&head[28];

	int size = height*width;									///calculate image size

	unsigned char buffer[size][3];								///to store the image data

	for(i=0;i<size;i++)
	{
		r = 0;
		g = 0;
		b = 0;
		buffer[i][2] = getc(t);									///blue
		buffer[i][1] = getc(t);									///green
		buffer[i][0] = getc(t);									///red

		///conversion formula of rgb to sepia
		r = (buffer[i][0]*0.393) + (buffer[i][1]*0.769)	+ (buffer[i][2]*0.189);
		g = (buffer[i][0]*0.349) + (buffer[i][1]*0.686)	+ (buffer[i][2]*0.168);
		b = (buffer[i][0]*0.272) + (buffer[i][1]*0.534)	+ (buffer[i][2]*0.131);

		if(r > MAX){											///if value exceeds
			r = MAX;
		}
		if(g > MAX){
			g = MAX;
		}
		if(b > MAX){
			b = MAX;
		}
		putc(b,f);
		putc(g,f);
		putc(r,f);

	}

    printf("\nOUTPUT: output is stored in 'sepiafilter.bmp' FILE\n");
	fclose(f);
	fclose(t);
}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> for applying sepia filter\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: sepiafilter();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

