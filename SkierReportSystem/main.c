/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Andy Kim				   akim83@myseneca.ca
   2) Boae Park				   bpark12@myseneca.ca
   3) Joshua Chong			   jchong33@myseneca.ca

   +--------------------------------------------------------+
   |                   FILE: main.c                         |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  S  U  M  M  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   +--------------------------------------------------------+ */

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "file_helper.h"
#include "moreHelper.h"

#define MAXSKIERS 2000

int main(void)
{
	// TODO: Code the necessary logic for your solution below
	//
	// NOTE: Use modularity whenever possible in your design
	//
	// HINTS:
	// 1) You will need to load the file data and store
	//    it to a data structure array 
	//    (MUST USE: provided "readFileRecord" function)
	//
	// 2) Create a menu system to provide the user with
	//    the reporting options
	//
	// 3) Generate the user-selected report

	struct SkierInfo skiers[MAXSKIERS];

	int result;
	int numSkiers = 0;
	int i = 0;

	FILE* fp = NULL;
	fp = fopen("data.txt", "r");

	if (fp != NULL)
	{
		do
		{
			result = readFileRecord(fp, &skiers[i]);
			numSkiers++;
			i++;
		} while (result != 1);
	}
	fclose(fp);

	reportManagerSystem(skiers, numSkiers);

	return 0;
}

