#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAXLEN 30
#define MINIMAL 0
#define Russel_Rao 0
#define GP02 1
#define GP03 2
#define Dstar 3
#define OPTIMAL_P 4  
#define GP19 5
#define Ochiai 6   


struct Component
{
  int line;  //the sequence number
  float suspiciousness;  //the suspiciousness of the component
};

struct SliceComponent
{
  int sliceLine;  
  float sliceSuspiciousness;  //the suspiciousness of the slicecomponent
};

int SFLComponentCmp(const void *a, const void *b) 
{
  return ((struct Component*)a)->suspiciousness < ((struct Component*)b)->suspiciousness;
}

main(argc,argv)
int argc;
char *argv[];
{
  FILE *fp1,*fp2,*fp3,*fp4,*fp5;
  int componentNum; //the number of components
  int sfltype=atoi(argv[1]);  //the sfl type
  char outFilename[MAXLEN]; //the sfl result outputfile
  struct Component *components;  //the components
  struct SliceComponent *sliceComponents;  //the components
  float *a00;  //the number of succesful test cases that unexecute the component
  float *a01;  //the number of failed test cases that unexecute the component
  float *a10;  //the number of succesful test cases that execute the component
  float *a11;  //the number of failed test cases that execute the component

  //identify the outFilename
  switch(sfltype)
  {
    case Russel_Rao:
      strcpy(outFilename,"0_Russel_Rao.txt");
      break;
    case GP02:
      strcpy(outFilename,"1_GP02.txt");
      break;
    case GP03:
      strcpy(outFilename,"2_GP03.txt");
      break;
    case Dstar:
      sprintf(outFilename,"3_Dstar.txt");
      break;    	
    case OPTIMAL_P:
      sprintf(outFilename,"4_OPTIMAL_P.txt");
      break;  
    case GP19:
      sprintf(outFilename,"5_GP19.txt");
      break; 
    case Ochiai:
      sprintf(outFilename,"6_Ochiai.txt");
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
   if( (fp5=fopen(argv[5],"r"))==NULL )  //the coverage information of all test cases
  {
    printf("open sliceResult.txt failed.\n");
    fclose(fp1);
    fclose(fp2);
	fclose(fp3);
    exit(0);
  }

  if( (fp4=fopen(outFilename,"w"))==NULL )  //the sfl result
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
  components=(struct Component*)malloc(componentNum*sizeof(struct Component));
  sliceComponents=(struct SliceComponent*)malloc(componentNum*sizeof(struct SliceComponent));
  a00=(float*)malloc(componentNum*sizeof(float));
  a01=(float*)malloc(componentNum*sizeof(float));
  a10=(float*)malloc(componentNum*sizeof(float));
  a11=(float*)malloc(componentNum*sizeof(float));
  if(components==NULL || a00==NULL || a01==NULL || a10==NULL || a11==NULL)
  {
	free(sliceComponents);
    free(components);
    free(a00);
    free(a01);
    free(a10);
    free(a11);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
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
  float cover=0;
  while( fscanf(fp2,"%d", &error) != EOF )
  {
     int j;
     for(j=0; j<componentNum; j++)
     {
       
       fscanf(fp3,"%f",&cover);
       if(0==cover && 0==error)
         a00[j]++;
       if(0==cover && 1==error)
         a01[j]++;
       if(0!=cover && 0==error)
         a10[j] = a10[j]+cover;
       if(0!=cover && 1==error)
         a11[j] = a11[j]+cover;
         
     } 
  }

  
  //compute the suspiciousness of each component
  
  switch(sfltype)
  {
    case Russel_Rao:
      fprintf(fp4,"Russel_Rao\n");
      	for(i=0; i<componentNum; i++)
      {
        if( 0 == (a11[i]+a01[i]+a10[i]+a00[i]) ){
        	components[i].suspiciousness = MINIMAL;
        }else{
        	components[i].suspiciousness = (float)(a11[i])/(float)(a11[i]+a01[i]+a10[i]+a00[i]);
        }
      }
      break;
    case GP02:
      fprintf(fp4,"GP02\n");
      	for(i=0; i<componentNum; i++)
      {
          components[i].suspiciousness = (float)(2*(a11[i]+sqrt((float)(a00[i])))) + sqrt((float)(a10[i]));
      }
      break;
    case GP03:
      fprintf(fp4,"GP03\n");
     for(i=0; i<componentNum; i++)
      {
          components[i].suspiciousness=(float)(a11[i]*a11[i])-sqrt((float)(a10[i]));
          if(components[i].suspiciousness<0)
               components[i].suspiciousness=0-components[i].suspiciousness;
          components[i].suspiciousness=sqrt(components[i].suspiciousness);
      }
      break;
    case Dstar:
    	fprintf(fp4,"D*\n");
    	for(i=0; i<componentNum; i++)
      {
          components[i].suspiciousness = (float)((a11[i]*a11[i])/(float)(a01[i]+a10[i]));
          if(components[i].suspiciousness<0)
               components[i].suspiciousness=0-components[i].suspiciousness;
          components[i].suspiciousness=(float)(a11[i])*sqrt(components[i].suspiciousness);
      }
      break;
    case OPTIMAL_P: 
    	fprintf(fp4,"optimal_p\n");
    	for(i=0; i<componentNum; i++)
      {
        components[i].suspiciousness = (float)a11[i] - (float)(a10[i])/(float)(a10[i]+a00[i]+1);
      }
      break;
    case GP19:
    	fprintf(fp4,"GP19\n");
    	for(i=0; i<componentNum; i++)
      {
          components[i].suspiciousness = (float)(a10[i]-a11[i]+a01[i]-a00[i]);
          if(components[i].suspiciousness<0)
               components[i].suspiciousness=0-components[i].suspiciousness;
          components[i].suspiciousness=(float)(a11[i])*sqrt(components[i].suspiciousness);
      }
      break;
    case Ochiai:
    	fprintf(fp4,"Ochiai\n");
    	for(i=0; i<componentNum; i++)
      {
          components[i].suspiciousness = (float)(a10[i]-a11[i]+a01[i]-a00[i]);
          if(components[i].suspiciousness<0)
               components[i].suspiciousness=0-components[i].suspiciousness;
          components[i].suspiciousness=(float)(a11[i])*sqrt(components[i].suspiciousness);
      }
      break;
    default:
      break;
  }
  //record every slice statement's line number
  int sliceResult;
  int sliceNum = 0;
  int statementRecord = 0;
  i = 0;
  while( fscanf(fp5,"%d", &sliceResult) != EOF )
  {
     sliceComponents[sliceNum].sliceLine = sliceResult;
     sliceComponents[sliceNum].sliceSuspiciousness = 0;
	 for(i=statementRecord;i<componentNum;i++)//supposing slicing statements order is increasing,or use 0 replace statementRecord
	 {
               if(sliceComponents[sliceNum].sliceLine == components[i].line)
		{
		   sliceComponents[sliceNum].sliceSuspiciousness = components[i].suspiciousness;
		   statementRecord = i;
		}
	 }
	 sliceNum++;
  }
//sort
  i = 0;
  int tmp = 0;
  int k = 0;
  double tmpLine = 0;
  double tmpSuspicious = 0;
  for(i = 0; i<sliceNum-1; i++)
  {
	  tmp = i;
	  for(k = i+1; k<sliceNum; k++)
	  {
		  if(sliceComponents[tmp].sliceSuspiciousness < sliceComponents[k].sliceSuspiciousness)
		  {
              tmp = k;
		  }
	  }
	  if(i!=tmp)
	  {
		  tmpSuspicious = sliceComponents[tmp].sliceSuspiciousness;
		  tmpLine = sliceComponents[tmp].sliceLine;

          sliceComponents[tmp].sliceSuspiciousness = sliceComponents[i].sliceSuspiciousness;
		  sliceComponents[tmp].sliceLine = sliceComponents[i].sliceLine;

		  sliceComponents[i].sliceSuspiciousness = tmpSuspicious;
		  sliceComponents[i].sliceLine = tmpLine;
	  }
  }

  //qsort(components,componentNum,sizeof(struct Component),SFLComponentCmp);
 // qsort(sliceComponents,sliceNum,sizeof(struct SliceComponent),SFLComponentCmp);
  i=0;
  for(i=0;i<sliceNum;i++)
  {
    fprintf(fp4,"%d:  %d   %f\n",i+1, sliceComponents[i].sliceLine,sliceComponents[i].sliceSuspiciousness);
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
