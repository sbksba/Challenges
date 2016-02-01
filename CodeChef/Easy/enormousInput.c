#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* The purpose of this problem is to verify whether the method you are using to 
 * read input data is sufficiently fast to handle problems branded with the 
 * enormous Input/Output warning. You are expected to be able to process at 
 * least 2.5MB of input data per second at runtime.
 * Input :
 * The input begins with two positive integers n k (n, k<=107). The next n lines
 * of input contain one positive integer ti, not greater than 109, each.
 * Output :
 * Write a single integer to output, denoting how many integers ti are divisible
 * by k.
 * Example
 *
 * Input:
 * 7 3
 * 1
 * 51
 * 966369
 * 7
 * 9
 * 999996
 * 11
 *
 * Output:
 * 4
 */

#define SIZE 65536

int main(int argc, char **argv)
{ 
  char buf[SIZE];
  unsigned long n, k, input, cpt;
  int c, i;
  
  cpt=0;
  scanf("%lu %lu\n",&n, &k);
  input=0;
  
  while( (c=fread(buf, sizeof(char),SIZE, stdin)) > 0)
    {
      for(i=0; i<c; i++)
	{
	  if (buf[i] == '\n')
	    {
	      if ((input%k) == 0)
		{
		  cpt++;
		}
	      input=0;
	    }
	  else
	    {
	      input=(input*10) + (buf[i] - '0');
	    }
	}
    }
  
  printf("%lu\n",cpt);
  
  return 0;
}
