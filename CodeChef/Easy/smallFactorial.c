#include <stdio.h>

/* You are asked to calculate factorials of some small positive integers.
 *
 *Input
 * An integer t, 1<=t<=100, denoting the number of testcases, followed by t
 * lines, each containing a single integer n, 1<=n<=100.
 *
 * Output
 * For each integer n given at input, display a line with the value of n!
 *
 * Example
 * Sample input:
 *
 * 4
 * 1
 * 2
 * 5
 * 3
 *
 * Sample output:
 *
 * 1
 * 2
 * 120
 * 6
 */

#define BASE 1000

int main()
{
  int i, j, m, n, t, x;
  unsigned int out[160], res, tmp;

  scanf("%d",&t);

  for (i=1; i<=t; i++)
    {
      scanf("%d",&n);
      out[0]=1;m=1;
      for (j=2; j<=n; j++)
	{
	  tmp=0;
	  for (x=0; x<m; x++)
	    {
	      res=out[x]*j+tmp;
	      out[x]=res%BASE;
	      tmp=res/BASE;
	    }
	  
	  while(tmp != 0)
	    {
	      out[m++]=tmp%BASE;
	      tmp/=BASE;
	    }
	}
      
      printf("%d",out[m-1]);
      for(j=m-2; j>=0; j--)
	printf("%.3d",out[j]);
      printf("\n");
    }

  return 0;
}
