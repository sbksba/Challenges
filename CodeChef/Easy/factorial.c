#include <stdio.h>
#include <malloc.h>

/* The most important part of a GSM network is so called Base Transceiver 
 * Station (BTS). These transceivers form the areas called cells (this term gave
 * the name to the cellular phone) and every phone connects to the BTS with the 
 * strongest signal (in a little simplified view). Of course, BTSes need some 
 * attention and technicians need to check their function periodically.
 *
 * The technicians faced a very interesting problem recently. Given a set of 
 * BTSes to visit, they needed to find the shortest path to visit all of the 
 * given points and return back to the central company building. Programmers 
 * have spent several months studying this problem but with no results. They 
 * were unable to find the solution fast enough. After a long time, one of the
 * programmers found this problem in a conference article. Unfortunately, he 
 * found that the problem is so called "Traveling Salesman Problem" and it is 
 * very hard to solve. If we have N BTSes to be visited, we can visit them in 
 * any order, giving us N! possibilities to examine. The function expressing 
 * that number is called factorial and can be computed as a product
 *
 * 1.2.3.4....N. The number is very high even for a relatively small N.
 *
 * The programmers understood they had no chance to solve the problem. But 
 * because they have already received the research grant from the government, 
 * they needed to continue with their studies and produce at least some results.
 * So they started to study behavior of the factorial function.
 *
 * For example, they defined the function Z. For any positive integer N, Z(N) is
 * the number of zeros at the end of the decimal form of number N!. They noticed
 * that this function never decreases. If we have two numbers N1<N2, then 
 * Z(N1) <= Z(N2). It is because we can never "lose" any trailing zero by 
 * multiplying by any positive number. We can only get new and new zeros. 
 * The function Z is very interesting, so we need a computer program that can 
 * determine its value efficiently.
 * Input
 *
 * There is a single positive integer T on the first line of input (equal to 
 * about 100000). It stands for the number of numbers to follow. Then there are
 * T lines, each containing exactly one positive integer number N, 1 <= N <= 
 * 1000000000.
 * Output
 *
 * For every number N, output a single line containing the single non-negative 
 * integer Z(N).
 * Example
 *
 * Sample Input:
 *
 * 6
 * 3
 * 60
 * 100
 * 1024
 * 23456
 * 8735373
 *
 * Sample Output:
 *
 * 0
 * 14
 * 24
 * 253
 * 5861
 * 2183837
 */

static inline int readUInt()
{
  int res=0;
  char c=fgetc(stdin);
  do
    {
      res=10*res+(c-'0');
    }while((c=fgetc(stdin)) != '\n');
  return res;
}

static int z1(int n)
{
  int res=0;
  while(n>=5)
    {
      n/=5;
      res+=n;
    }
  return res;
}

static unsigned int z2(unsigned int n)
{
  return (n/5       + n/25       + n/125
	+ n/625)    + (n/3125    + n/15625
	+ n/78125   + n/390625)  + (n/1953125
	+ n/9765625 + n/48828125 + n/244140625);
}

static int z3(int n)
{
  int res=0;
  while(n)
    {
      res+= n/5 + n/25 + n/125 + n/625 + n/3125 + n/15625;
      res/=15625;
    }
  return res;
}

int main()
{
  int todo = readUInt();
  int bufLen = 10 * todo;
  char *inoutBuf = (char *)malloc(bufLen);
  char *p_in = inoutBuf;
  char *p_out= inoutBuf;
  int n, i;
  char reverse[10];
  
  fread(inoutBuf, 1, bufLen, stdin);
  
  while (todo--)
    {
      // read n
      n = (*p_in) - '0';
      while (*(++p_in) != '\n')
	{
	  n = 10*n + (*p_in - '0');
	}
      p_in++;
      // compute n = z(n)
      n = z2(n);
      // write n
      i = 0;
      do 
	{
	  reverse[i++] = n%10;
	  n = n/10;
	} while (n>0);
      
      while (--i>=0)
	{
	  *(p_out++) = '0' + reverse[i];
	}
      *(p_out++) = '\n';
    }
  fwrite(inoutBuf, 1, p_out-inoutBuf, stdout);
  free(inoutBuf);
  
  return 0;
}
