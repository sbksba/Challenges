#include <stdio.h>

/* In poker, you have 5 cards. There are 10 kinds of poker hands (from highest
 * to lowest):
 *
 * royal flush - ace, king, queen, jack and ten, all in the same suit
 * straight flush - five cards of the same suit in sequence, such
 * as 10,9,8,7,6 of clubs; ace can be counted both as the highest card or as the
 * lowest card - A,2,3,4,5 of hearts is a straight flush. But 4,3,2,A,K of
 * hearts is not a straight flush - it's just a flush.
 * four of a kind - four cards of the same rank, such as four kings.
 * full house - three cards of one rank plus two cards of another rank
 * flush - five cards of the same suit (but not a straight flush)
 * straight - five cards in order - just like the straight flush, but mixed suits
 * three of a kind - three cards of one rank and two other cards
 * two pairs - two cards of one rank, two cards of another rank, and one more card
 * pair - two cards of the same rank
 * high card - none of the above 
 *
 * Write a program that will help you play poker by telling you what kind of
 * hand you have.
 * Input
 *
 * The first line of input contains the number of test cases (no more than 20).
 * Each test case consists of one line - five space separated cards. Each card
 * is represented by a two-letter (or digit) word. The first character is the
 * rank (A,K,Q,J,T,9,8,7,6,5,4,3 or 2), the second character is the suit
 * (S,H,D,C standing for spades, hearts, diamonds and clubs).
 * The cards can be in any order (but they will not repeat).
 * Output
 *
 * For each test case output one line describing the type of a hand, exactly
 * like in the list above.
 * Example
 *
 * Input:
 * 3
 * AH KH QH TH JH
 * KH 5S 3C 5C 7D
 * QH QD 2S QC 2C
 *
 * Output:
 * royal flush
 * pair
 * full house
 */

#define TRUE 1
#define FALSE 0

const int ABS = 0, PRES = 1;

char card_package[22][20] = {"AH KH QH TH JH",\
			     "KH 5S 3C 5C 7D",\
			     "QH QD 2S QC 2C",\
			     "QH QD QS QC 2C",\
			     "6H 2H 3H 4H 5H",\
			     "6H 2H KH 4H 5H",\
			     "6H 2H 3S 4H 5H",\
			     "AH AS 2S AC 5H",\
			     "AH AS 3S 8C 8H",\
			     "AH KS 3S 8C 8H",\
			     "AH KS 3S 6C 8H"};

const char combination[11][20] = {"royal flush",\
				  "straight flush",\
				  "four of a kind",\
				  "full house",\
				  "flush",\
				  "straight",\
				  "three of a kind",\
				  "two pairs",\
				  "pair",\
				  "high card"};

char card_stack[4][16];

void Calculate_Result(char *cTemp)
{
 
  Adjust_Array(cTemp);

  if(Royal_Flush()) {printf("\nroyal flush");return;}

  if(Straight_Flush()) {printf("\nstraight flush");return;}

  if(Four_Of_A_Kind()) {printf("\nfour of a kind");return;}

  if(Full_House()) {printf("\nfull house");return;}

  if(Flush()) {printf("\nflush");return;}

  if(Straight()) {printf("\nstraight");return;}

  if(Three_Of_A_Kind()) {printf("\nthree of a kind");return;}

  if(Two_Pairs()) {printf("\ntwo pairs");return;}

  if(Pair()) {printf("\npair");return;}

  printf("\nhigh card"); return; 
}
 
//void Adjust_Array( char *cTemp)
//this array fills the card_stack global array with the cards present or not
//at the corresponding location.
void Adjust_Array( char *cTemp)
{
  int i,j;
  int tempValue, tempSet, Set;
  for(i=0; i< 4; i++)
    for(j=0; j< 16; j++)
      card_stack[i][j] = ABS;
 
  for(i = 0; i<14; i++)
    {
      tempValue = cTemp[i];
      i++; //move to next char in string.
      tempSet = cTemp[i];
      // printf("[%c%c]",tempValue,tempSet);
      i++; //skip the spaces.
      
      switch(tempSet)
	{
	case 'S': Set = 0; break;
	case 'H': Set = 1; break;
	case 'D': Set = 2; break;
	case 'C': Set = 3; break;
	}
      
      switch(tempValue)
	{
	case 'A':
	  card_stack[Set][0] = 'A';//PRES;
	  card_stack[Set][13] = 'A';//PRES;
	  break;
	case 'T':
	  card_stack[Set][9] = 'T';//PRES;
	  break;
	case 'J':
	  card_stack[Set][10] = 'J';//PRES;
	  break;
	case 'Q':
	  card_stack[Set][11] = 'Q';//PRES;
	  break;
	case 'K':
	  card_stack[Set][12] = 'K';//PRES;
	  break;
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  card_stack[Set][tempValue - '1'] = tempValue;
	  break;
	}
    }
}

int Royal_Flush(void)
{
  int i,j,ser;
  ser = 0;
  for(i=0; i< 4; i++)
    {
      for(j=9; j< 16; j++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	  else ser = 0;
	  if(ser == 5) return (TRUE);
	}
    }
  return (FALSE);
}

int Straight_Flush(void)
{
  int i,j,ser;
  ser = 0;
  for(i=0; i< 4; i++)
    {
      for(j=0; j< 16; j++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	  else ser = 0;
	  if(ser == 5) return (TRUE);
	}
    }
  return (FALSE);
}

int Four_Of_A_Kind(void)
{
  int i,j,ser;
  ser = 0;
  for(j=0; j< 16; j++)
    {
      ser = 0;
      for(i=0; i< 4; i++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	}
      if(ser == 4) return (TRUE);
    }
  return (FALSE);
}

int Full_House(void)
{
  int i,j,ser;
  ser = 0;
  for(j=0; j< 16; j++)
    {
      ser = 0;
      for(i=0; i< 4; i++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	}
      if(ser == 3) break;
    }
  if(ser != 3) return (FALSE);
  for(j=0; j< 16; j++)
    {
      ser = 0;
      for(i=0; i< 4; i++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	}
      if(ser == 2) return (TRUE);
    }
  return (FALSE);
  
}

int Flush(void)
{
  int i,j,ser;
  ser = 0;
  for(i=0; i< 4; i++)
    {
      ser = 0;
      for(j=0; j< 13; j++)
	{ //ACE Should not be counted twice!!!!
	  if(card_stack[i][j] != ABS) ser += 1;
	  if(ser == 5) return (TRUE);
	}
    }
  return (FALSE);
}

int Straight(void)
{
  int i,j,ser;
  char Temp_Stack[16];
  
  for(j=0; j< 16; j++)
    {
      Temp_Stack[j] = card_stack[0][j] | card_stack[1][j] | card_stack[2][j] | card_stack[3][j] ;
    }
  ser = 0;
  for(j=0; j< 16; j++)
    {
      if(Temp_Stack[j] != ABS) ser += 1;
      else ser = 0;
      if(ser == 5) return (TRUE);
    }
  return (FALSE);
}
 
int Three_Of_A_Kind(void)
{
  int i,j,ser;
  ser = 0;
  for(j=0; j< 16; j++)
    {
      ser = 0;
      for(i=0; i< 4; i++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	}
      if(ser == 3) return (TRUE);
    }
  return (FALSE);
}

int Two_Pairs(void)
{
  int i,j,ser;
  ser = 0;
  for(j=0; j< 13; j++)
    {
      ser = 0;
      for(i=0; i< 4; i++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	}
      if(ser == 2) break;
    }
  if(ser != 2) return (FALSE);
  j++;
  for(; j< 13; j++)
    {
      ser = 0;
      for(i=0; i< 4; i++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	}
      if(ser == 2) return (TRUE);
    }
  return (FALSE); 
}

int Pair(void)
{
  int i,j,ser;
  ser = 0;
  for(j=0; j< 13; j++)
    {
      ser = 0;
      for(i=0; i< 4; i++)
	{
	  if(card_stack[i][j] != ABS) ser += 1;
	}
      if(ser == 2) return(TRUE);
    }
  return (FALSE);
}

int main(void)
{
  int i,j;
  int iInput;
  char Garbage[10];
  
  scanf("%d",&iInput);
  for(i= 0; i < iInput;i++)
    {
      for(j=0;j<5;j++)
	{
	  scanf("%s",&Garbage);
	  card_package[i][0+(j*3)] = Garbage[0];
	  card_package[i][1+(j*3)] = Garbage[1];
	  card_package[i][2+(j*3)] = ' ';
	}
    }
  
  for(i=0; i< iInput; i++)
    {
      Calculate_Result(card_package[i]);
    }

  printf("\n");

  return(0);
}
