///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX 255

///function to give brightning effect to the image
void bright(int BRIGHTNESS)
{


    FILE *t = fopen("fruit.bmp","rb");			/// Input File name
	FILE *f = fopen("bright.bmp","wb");	    	/// Output File name

	int i;
	unsigned char head[54],colorTable[1024];

	if(t==NULL)						/// check if the input file has not been opened successfully.
	{
		printf("File does not exist.\n");
		exit(1);
	}

	for(i=0;i<54;i++)
	{
		head[i] = getc(t);
	}

	fwrite(head,sizeof(unsigned char),54,f);		/// write the header back


	int height = *(int*)&head[18];
	int width = *(int*)&head[22];
	int bitDepth = *(int*)&head[28];


	int size = height*width;				///calculate image size

	if(bitDepth <= 8)					    ///if ColorTable present, extract it.
	{
		fread(colorTable,sizeof(unsigned char),1024,t);
		fwrite(colorTable,sizeof(unsigned char),1024,f);
	}


	unsigned char buffer[size][3];				///to store the image data
	int temp0,temp1,temp2;


	for(i=0;i<size;i++)					///increasing pixel values to get image bright
	{
        buffer[i][0]=getc(t);									///red
		buffer[i][1]=getc(t);									///green
		buffer[i][2]=getc(t);                                   ///blue

		temp0 = buffer[i][0] + BRIGHTNESS;
		temp1 = buffer[i][1] + BRIGHTNESS;
		temp2 = buffer[i][2] + BRIGHTNESS;

		buffer[i][0] = (temp0 > MAX) ? MAX : temp0;
        buffer[i][1] = (temp1 > MAX) ? MAX : temp1;
        buffer[i][2] = (temp2 > MAX) ? MAX : temp2;

        putc(buffer[i][0],f);
		putc(buffer[i][1],f);
		putc(buffer[i][2],f);
	}
    printf("\nOUTPUT: output is stored in 'bright.bmp' FILE\n");
	fclose(t);
	fclose(f);
}


int main()
{ int a,R;
printf("\t\t**ENTER** \n\n<1> for brighting the image\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: printf("Enter the BRIGHTNESS factor : ");
            scanf("%d",&R);
            bright(R);
            break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}


