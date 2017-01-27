#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int COMPARISONS = 0;

int frobcmp( char const *a, char const *b)
{
  COMPARISONS++;
  while (1)
    {
      if (*a == 32 || *b == 32) //break when either a or b gets to space
	break;

      if ((*a^42) > (*b^42))
	return 1;
      else if ((*a^42) < (*b^42))
	return -1;

      a++;
      b++;
    }

  //a is prefix to b or vice versa, or a and b are the same

  //a is prefix

  if ( *a == 32 && *b != 32 )
    return -1;
  else if (*a != 32 && *b == 32)  // b is a prefix
    return 1;

  //equal
  return 0;
}

  
int frobcmp_void(const void *a, const void *b)   //this function is made so that qsort calls a function with const void* as
{                                                //arguments while frobcmp still has char const
  char const *arg1 = *(char const **)a;
  char const *arg2 = *(char const **)b;
  return frobcmp(arg1, arg2);
}

int main(void)
{

  
  struct stat buf;
  fstat(0, &buf);

  int maxsize = 500;
  int sizeoffile = buf.st_size;
  char *init;

  int isreg = 0;
  if (S_ISREG(buf.st_mode))
    {
      isreg = 1;
      maxsize = sizeoffile;
      init = (char*)malloc(sizeof(char) * sizeoffile);

      if (init == NULL)
	{
	  fprintf(stderr, "allocation failed\n");
	  fprintf(stderr, "Comparisons: %d\n", COMPARISONS);
	  exit(1);
	}
    }
  else
    {
      init = (char*)malloc(sizeof(char) * maxsize);

      if (init == NULL)
	{
	  fprintf(stderr, "allocation failed\n");
	  fprintf(stderr, "Comparisons: %d\n", COMPARISONS);
	  exit(1);
	}
    }

  int isempty = 1;
  int size = 0;//character count
  int nwords = 0;//word count
  char ch;
  int i;
  for (i = 0;;i++)                              //never ending loop with counter
    {
      if (isreg = 1 && sizeoffile < buf.st_size)
	{
	  sizeoffile = buf.st_size;
	  maxsize = sizeoffile;
	  init = (char*)realloc(init, sizeoffile);
	  if (init == NULL)
	    {
	      fprintf(stderr, "allocation failed\n");
	      fprintf(stderr, "Comparisons: %d\n", COMPARISONS);
	      exit(1);
	    }
	}
      if (isreg = 0 && i == maxsize)                             //reallocates if run out of space
	{
	  maxsize *= 2;
	  init = (char*)realloc(init, maxsize);
	  if (init == NULL)
	    {
	      fprintf(stderr, "allocation failed\n");
	      fprintf(stderr, "Comparisons: %d\n", COMPARISONS);
	      exit(1);
	    }
	}

      if (read(0,&ch,1) == 0)
	break;
      
      //int input = getchar();                        //get next character
      //if (input == EOF)
      //	break;

      if (ch == '\n')                      //dont add newline
	break;
      
      init[i] = ch;                        //store it, increase size
      size++;

      if (init[i] == ' ')                          //count words
	nwords++;
 
      if (isempty == 1)                             //set isempty to false if not empty
	isempty = 0;
    }

  if (isempty)                                     //return if no string
    return 0;

  if (init[size-1] != ' ')                        //add space if no space
    {
      init[size]=' ';
      size++;
      nwords++;
    }

  //now I have a string of the input words separated by spaces ending in a space

  char **word_ptr = (char**)malloc(sizeof(char*) * nwords);   //create an array of cstrings

  if (word_ptr == NULL)
    {
      fprintf(stderr, "allocation failed");
      fprintf(stderr, "Comparisons: %d\n", COMPARISONS);
      exit(1);
    }

  char *iterator = init;                                    //create an iterator to move along the string

  
  for (i = 0; i < nwords; i++)           //visit every character, record the address of first character of each string
    {
      word_ptr[i] = iterator;

      while (*iterator != ' ')
	iterator++;

      if (i == nwords-1)
	break;
      
      iterator++;
    }
      
  qsort(word_ptr, nwords, sizeof(char*), frobcmp_void);

  char *print; //acts like an iterator

  
  for ( i = 0; i < nwords; i++)
    {
      print = word_ptr[i];

      while (*print != ' ') //print everything up until space
	{
	  write(1,&(*print),1);
	  print++;
	}

      write(1,&(*print),1); //print the space
    }

  free(init);
  free(word_ptr);

  fprintf(stderr,"Comparisons: %d\n", COMPARISONS);
  return 0;
}
