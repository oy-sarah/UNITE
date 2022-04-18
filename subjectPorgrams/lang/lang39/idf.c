#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



int main(argc,argv)
int argc;
char *argv[];
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6;
    char outFilename[30]; //the sfl result outputfile
    int componentNum; //the number of components
    strcpy(outFilename,"covMatrix1.txt");
    
    if( (fp1=fopen(argv[1],"r"))==NULL )  //the information of components
    {
        printf("open componentinfo.txt failed.\n");
        exit(0);
    }
    if( (fp2=fopen(argv[2],"r"))==NULL )  //the test results of all test cases
    {
        printf("open error.txt failed.\n");
        fclose(fp1);
        exit(0);
    }
    if( (fp3=fopen(argv[3],"r"))==NULL )  //the coverage information of all test cases
    {
        printf("open covMatrix.txt failed.\n");
        fclose(fp1);
        fclose(fp2);
        exit(0);
    }
    if( (fp4=fopen(argv[4],"r"))==NULL )  //the coverage information of all test cases
    {
        printf("open IDF.txt failed.\n");
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        exit(0);
    }
    if( (fp5=fopen(argv[5],"r"))==NULL )  //the coverage information of all test cases
    {
        printf("open IFnum.txt failed.\n");
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        fclose(fp4);
        exit(0);
    }
    if( (fp6=fopen(outFilename,"w"))==NULL )  //the sfl result
    {
        printf("open %s failed.\n",outFilename);
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        fclose(fp4);
        fclose(fp5);
        exit(0);
    }
    //malloc space
    fscanf(fp1,"%d",&componentNum);
    int IFnum=0;
    int cover=0;
    float IDF[componentNum];
    int j = 0;
    for(j=0; j<componentNum; j++)
    {
        fscanf(fp4,"%f", &IDF[j]);

    }
    while( fscanf(fp5,"%d", &IFnum) != EOF )
    {
        for(j=0; j<componentNum; j++)
        {
            fscanf(fp3,"%d",&cover);
            if(IFnum != 0)
            {
                //fprintf(fp6,"%f ", ((float)(cover)/(float)(IFnum))*IDF[j]);
                //fprintf(fp6,"%f ", (float)(cover)*IDF[j]);
                fprintf(fp6,"%f ", (float)(cover)*(float)(1/(log(IFnum)+1))*IDF[j] );
            }
            else
            {
                fprintf(fp6,"%f ", 0.0000);
            }
        }
        fprintf(fp6,"\n");
    }
}
