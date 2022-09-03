///DATA STRUCTURE PROJECT WORK ON IMAGE PROSSESING
///SUBMITTED BY:JAY PRAKASH KUMAR(191220026)
#include<stdio.h>
#include<stdlib.h>


///function to preform flip operation along the axis
void flip()
{


    FILE *t = fopen("ships.bmp","rb");					///Input File name
	FILE *f = fopen("flip.bmp","wb");		    	///Output File name

	int i,j,s;
	unsigned char head[54],colorTable[1024];


	if(t==NULL)											/// check if the input file has not been opened successfully.
	{
		printf("File does not exist.\n");
	}

	for(i=0;i<54;i++)										///read the 54 byte header from t
	{
		head[i] = getc(t);
	}

	fwrite(head,sizeof(unsigned char),54,f);


	int height = *(int*)&head[18];
	int width = *(int*)&head[22];
	int bitDepth = *(int*)&head[28];

	printf("width: %d\n",width);
	printf("height: %d\n",height );


unsigned char spacex[width][height][3];
unsigned char space[width][height][3];


	printf("Enter your choice :\n");
	printf("1. To Flip Horizontally \n");
	printf("2. To Flip Vertically\n");
    scanf("%d",&s);
int p;
	switch(s)
	{
	case 2:

	      for(i=0;i<width;i++)								              ///to flip vertically
			{
				for(j=width, p=0;j>0,p<width;j--,p++)
				{
                    space[i][p][0]=getc(t);
		            space[i][p][1]=getc(t);
                    space[i][p][2]=getc(t);

					spacex[i][j][0]=space[i][p][0];
					spacex[i][j][1]=space[i][p][1];
					spacex[i][j][2]=space[i][p][2];
				}
			}

			for(i=0;i<height;i++)
			{
				for(j=0;j<width;j++)
				{
                    putc(spacex[i][j][0],f);
		            putc(spacex[i][j][1],f);
		            putc(spacex[i][j][2],f);
				}
			}

			break;

		case 1:                                                   ///to flip horizontally

        	for(i=0;i<height;i++)
			{
				for(j=0;j<width;j++)
				{
                    space[i][j][0]=getc(t);
		            space[i][j][1]=getc(t);
                    space[i][j][2]=getc(t);

					spacex[width-1-i][j][0]=space[i][j][0];
					spacex[width-1-i][j][1]=space[i][j][1];
					spacex[width-1-i][j][2]=space[i][j][2];
				}
			}

			for(i=0;i<height;i++)
			{
				for(j=0;j<width;j++)
				{
                    putc(spacex[i][j][0],f);
		            putc(spacex[i][j][1],f);
		            putc(spacex[i][j][2],f);
				}
			}
			break;

        }
printf("\nOUTPUT: output is stored in 'flip.bmp' FILE\n");
fclose(f);
fclose(t);
}

int main()
{ int a;
printf("\t\t**ENTER** \n\n<1> to flip\n");
printf("\nENTER INPUT : ");
scanf("%d",&a);
switch(a)
{
    case 1: flip();
             break;
    default: printf("\n!!invalid input!!\nterminating....\n\n");
}
    return 0;
}

