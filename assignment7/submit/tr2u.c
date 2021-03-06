#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char translate(char* from, char* to, char c)
{
  int i;
  for(i = 0; *(from+i) != '\0'; i++)
    {
      if(c == *(from+i))
	return *(to+i);
    }
  return c;
}

int main(int argc, char* argv[])
{
  int count1 = 0;
  int count2 = 0;
  char* from = argv[1];
  char* to = argv[2];

  //check if number of arguments is correct
  if(argc != 3)
    {
      printf("Error: must have 2 arguments\n");
      exit(0);
    }

  //check if arguments have same number of characters and for duplicates
  char* first = from;
  char* second = to;
  for(; *first != '\0'; first++)
    {
      int i;
      for(i = 1; *(first+i) != '\0'; i++)
	{
	  if(*first == *(first+i))
	    {
	      printf("Error: first argument must not have duplicates\n");
	      exit(0);
	    }
	}
      count1++;
    }
  for(; *second != '\0'; second++)
    {
      int i;
      for(i = 1; *(second+i) != '\0'; i++)
	{
	  if(*second == *(second+i))
	    {
	      printf("Error: second argument must not have duplicates\n");
	      exit(0);
	    }
	}
      count2++;
      }
  if(count1 != count2)
    {
      printf("Error: arguments must be same size\n");
      exit(0);
      }


  //translate the inputs one by one and output the result
  char c[1];
  int bytes = 1;
  
  while(bytes=read(0,c,1))
  {
    *c = translate(from, to, *c);
    write(1,c,1);
  }
  
  return 0;

}
