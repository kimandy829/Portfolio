/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Andy Kim				   akim83@myseneca.ca
   2) Boae Park				   bpark12@myseneca.ca
   3) Joshua Chong			   jchong33@myseneca.ca

   +--------------------------------------------------------+
   |                   FILE: moreHelper.h                   |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  S  U  M  M  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   +--------------------------------------------------------+ */

void clearKeyboard(void);

int getInt(void);

int getIntInRange(int min, int max);

char validCategory(void);

void ascendSort(struct SkierInfo sub[], int size);

void descendSort(struct SkierInfo sub[], int size);

void displayTop(struct SkierInfo info[], int size);

void displayAll(struct SkierInfo info[], int size);

void displayLast(struct SkierInfo info[], int size);

void displayWinners(struct SkierInfo info[], int size);

void topHelper(const struct SkierInfo info[], struct SkierInfo sub[], int size, char category);

void lastHelper(const struct SkierInfo info[], struct SkierInfo sub[], int size, char category);

void ageGroup(struct SkierInfo* info, char* ageValue);

int menu(void);

void reportManagerSystem(struct SkierInfo info[], int size);

