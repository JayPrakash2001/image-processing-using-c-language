///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>

///function to convert RGB image to grayscale
void color2gray()
{
  FILE *t = fopen("fruit.bmp","rb");					    ///Input File name
  FILE *f = fopen("color2gray.bmp","wb");		    		///Output File name

	int x;

    if(t==NULL)												/// check if the input file has not been opened successfully.
	{
		printf("File does not exist.\n");
	}

    unsigned char head[54];
	for(int i=0;i<54;i++)											/// read the 54 head header from t
	{
		head[i] = getc(t);
	}

	fwrite(head,sizeof(unsigned char),54,f);					/// write the header back


	int height = *(int*)&head[18];
	int width = *(int*)&head[22];
	int bitDepth = *(int*)&head[28];

	int size = height*width;									/// calculate image size

	unsigned char space[size][3];								/// to store the image data


	for(int i=0;i<size;i++)											/// RGB to gray
	{
		x=0;
		space[i][2]=getc(t);									///blue
		space[i][1]=getc(t);									///green
		space[i][0]=getc(t);									///red

		x=(space[i][0]*0.29) + (space[i][1]*0.59)	+ (space[i][2]*0.11);			/// conversion formula of rgb to gray

		putc(x,f);
		putc(x,f);
		putc(x,f);
	}

    printf("\nOUTPUT: output is stored in 'color2gray.bmp' FILE\n");
	fclose(f);
	fclose(t);

}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> for color to gray\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: color2gray();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

