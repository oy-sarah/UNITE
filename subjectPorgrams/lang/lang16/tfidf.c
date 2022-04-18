#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAXLEN 30
#define MINIMAL 0
#define Russel_Rao 0
#define GP02 1
#define GP03 2
#define GP19 3
#define OPTIMAL_P 4  


struct Component
{
  int line;  //the sequence number
  float suspiciousness;  //the suspiciousness of the component
  float IF;
  float IDF;
};

int SFLComponentCmp(const void *a, const void *b) 
{
  return ((struct Component*)a)->suspiciousness < ((struct Component*)b)->suspiciousness;
}

int main(argc,argv)
int argc;
char *argv[];
{
  FILE *fp1,*fp2,*fp3,*fp4,*fp5;
  int componentNum; //the number of components
  int sfltype=atoi(argv[1]);  //the sfl type
  char outFilename[MAXLEN]; //the sfl result outputfile
  char outFilename1[MAXLEN]; //the sfl result outputfile
  struct Component *components;  //the components
  int *a00;  //the number of succesful test cases that unexecute the component
  int *a01;  //the number of failed test cases that unexecute the component
  int *a10;  //the number of succesful test cases that execute the component
  int *a11;  //the number of failed test cases that execute the component

  //identify the outFilename
  switch(sfltype)
  {
    case Russel_Rao:
      strcpy(outFilename,"IDF.txt");
      strcpy(outFilename1,"IFnum.txt");
      break;
    case GP02:
      strcpy(outFilename1,"IFnum.txt");
      break;
    case GP03:
      strcpy(outFilename,"2_GP03.txt");
      break;
    case GP19:
      sprintf(outFilename,"3_GP19.txt");
      break;    	
    case OPTIMAL_P:
      sprintf(outFilename,"4_OPTIMAL_P.txt");
      break;       
    default:
      printf("sfltype undefined. It will perform Russel_Rao type.\n");
      strcpy(outFilename,"0_Russel_Rao.txt");
      break;
  }

  //open file
  if( (fp1=fopen(argv[2],"r"))==NULL )  //the information of components
  {
    printf("open componentinfo.txt failed.\n");
    exit(0);
  }
  if( (fp2=fopen(argv[3],"r"))==NULL )  //the test results of all test cases
  {
    printf("open error.txt failed.\n");
    fclose(fp1);
    exit(0);
  }
  if( (fp3=fopen(argv[4],"r"))==NULL )  //the coverage information of all test cases
  {
    printf("open covMatrix.txt failed.\n");
    fclose(fp1);
    fclose(fp2);
    exit(0);
  }
  if( (fp4=fopen(outFilename,"w"))==NULL )  //the sfl result
  {
    printf("open %s failed.\n",outFilename);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    exit(0);
  }
  if( (fp5=fopen(outFilename1,"w"))==NULL )  //the sfl result
  {
        printf("open %s failed.\n",outFilename);
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        fclose(fp4);
        exit(0);
  }
    
    //malloc space
  fscanf(fp1,"%d",&componentNum);
  components=(struct Component*)malloc(componentNum*sizeof(struct Component));
  a00=(int*)malloc(componentNum*sizeof(int));
  a01=(int*)malloc(componentNum*sizeof(int));
  a10=(int*)malloc(componentNum*sizeof(int));
  a11=(int*)malloc(componentNum*sizeof(int));
  if(components==NULL || a00==NULL || a01==NULL || a10==NULL || a11==NULL)
  {
    free(components);
    free(a00);
    free(a01);
    free(a10);
    free(a11);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    printf("malloc error.\n");
    exit(0);
  }

  //get the a** of each component
  int i;
  for(i=0; i<componentNum; i++)
  {
     int temp;
     fscanf(fp1,"%d",&temp);
     components[i].line=temp;
     a00[i]=0;
     a01[i]=0;
     a10[i]=0;
     a11[i]=0;
  }
  int error=0;
  int cover=0;
  int testNum = 0;
  while( fscanf(fp2,"%d", &error) != EOF )
  {
     int j;
     int if1 = 0;
     for(j=0; j<componentNum; j++)
     {
       
       fscanf(fp3,"%d",&cover);
       if(0==cover && 0==error)
         a00[j]++;
       if(0==cover && 1==error)
         a01[j]++;
       if(1==cover && 0==error)
        {
         a10[j]++;
         if1++;
        }
       if(1==cover && 1==error)
        {
         a11[j]++;
         if1++;
        }
     }
     testNum++;
     fprintf(fp5,"%d", if1);
     fprintf(fp5,"\n");
  }
  for(i=0; i<componentNum; i++)
  {
    // components[i].IDF = log10((float)(componentNum)/(float)(a11[i]+a10[i]+1));
      if((float)(a11[i]+a10[i]) != 0)
      {
          components[i].IDF = log10((float)(testNum)/(float)(a11[i]+a10[i]));
      }
      else
     {
         components[i].IDF = 0;
     }
  }

  //compute the suspiciousness of each component
  
  
  i=0;
  for(i=0;i<componentNum;i++)
  {
    fprintf(fp4,"%f ", components[i].IDF);
  }

  //free space  
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  fclose(fp4);
  free(components);
  free(a00);
  free(a01);
  free(a10);
  free(a11);
  exit(0);
}
