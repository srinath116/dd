#include<stdio.h>
#include<stdlib.h>
const char *kFileName ="/sys/kernel/debug/kisni/keys";
    
int main()
{

char input[100];
 FILE *fp;
	 fp = fopen(kFileName, "r");
      while(read(fp, &input, sizeof(input))!=-1)
   	 		printf("%s\n",input );      

   	 	fclose(fp);
return 0;
}