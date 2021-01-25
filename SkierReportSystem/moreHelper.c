/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Andy Kim				   akim83@myseneca.ca
   2) Boae Park				   bpark12@myseneca.ca
   3) Joshua Chong			   jchong33@myseneca.ca

   +--------------------------------------------------------+
   |                   FILE: moreHelper.c                   |
   +--------------------------------------------------------+
   |           2  0  2  0  ~  S  U  M  M  E  R              |
   |                 I  P  C  :  B  T  P                    |
   |                 1  4  4  :  1  0  0                    |
   |              FINAL ASSESSMENT PART - 2                 |
   |                                                        |
   |     S  E  N  E  C  A            C  O  L  L  E  G  E    |
   +--------------------------------------------------------+ */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "file_helper.h"
#include "moreHelper.h"

void clearKeyboard(void)
{
    while (getchar() != '\n');
}

int getInt(void)
{
    char newline = 'x';
    int value;
    while (newline != '\n')
    {
        scanf("%d%c", &value, &newline);
        if (newline != '\n') {
            clearKeyboard();
            printf("*** INVALID INTEGER *** <Please enter an integer>: ");
        }
    }
    return value;
}

int getIntInRange(int min, int max)
{
    int done = 0;
    int value;
    while (done == 0)
    {
        value = getInt();
        if (min <= value && value <= max) {
            done = 1;
        }
        else {
            printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
        }
    }
    return value;
}

char validCategory(void)
{
    printf("Which category (S, M, L): ");
    char newline = 'x';
    char letter;
    int done = 0;
    char value = 'z';
    while (newline != '\n' || done == 0)
    {
        scanf("%c%c", &letter, &newline);
        if (newline != '\n') {
            clearKeyboard();
            printf("*** INVALID ENTRY *** <Only (S, M, L) are acceptable>: ");
        }
        else {
            if (letter == 's' || letter == 'S') {
                value = 'S';
                done = 1;
            }
            else if (letter == 'm' || letter == 'M') {
                value = 'M';
                done = 1;
            }
            else if (letter == 'l' || letter == 'L') {
                value = 'L';
                done = 1;
            }
            else {
                printf("*** INVALID ENTRY *** <Only (S, M, L) are acceptable>: ");
            }
        }
    }
    printf("\n");
    return value;
}

void ascendSort(struct SkierInfo sub[], int size)
{
    struct SkierInfo temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (sub[j].midwayTime != 0 && (sub[i].finishTime - sub[i].startTime) > (sub[j].finishTime - sub[j].startTime))
            {
                temp = sub[i];
                sub[i] = sub[j];
                sub[j] = temp;
            }
        }
    }
}

void descendSort(struct SkierInfo sub[], int size)
{
    struct SkierInfo temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (sub[j].midwayTime != 0 && (sub[i].finishTime - sub[i].startTime) < (sub[j].finishTime - sub[j].startTime))
            {
                temp = sub[i];
                sub[i] = sub[j];
                sub[j] = temp;
            }
        }
    }
}

void displayTop(struct SkierInfo info[], int size)
{
    struct SkierInfo sub[3] = { 0 };
    char category = validCategory();
    topHelper(info, sub, size, category);
    ascendSort(sub, 3);
    
    printf("Skier                    Age Group Time\n");
    printf("---------------------------------------\n");
    double durHour, durMin;
    char ageValue[8] = { '\0' };
    for (int i = 0; i < 3; i++)
    {
        if (sub[i].age != 0)
        {
            ageGroup(&sub[i], ageValue);
            durHour = sub[i].finishTime - sub[i].startTime;
            durMin = (durHour - floor(durHour)) * 60;
            printf("%-27s%7s %d:%02d\n", sub[i].name, ageValue, (int)durHour, (int)round(durMin));
        }
        else {
            printf("Not Awarded\t\t       N/A   N/A\n");
        }
    }
}

void displayAll(struct SkierInfo info[], int size)
{
    char category = validCategory();

    struct SkierInfo sub[2000] = { 0 };
    
    //copy to sub array if matches the raceLength
    int subIndex = 0;
    for (int i = 0; i < size; i++)
    {
        if (info[i].raceLength == category)
        {
            sub[subIndex] = info[i];
            subIndex++;
        }
    }
    struct SkierInfo temp;
    for (int i = 0; i < subIndex; i++)
    {
        // if skier withdrew
        if (sub[i].midwayTime == 0)
        {
            // we store that skier in temp and shift all the element to left by 1
            temp = sub[i];
            for (int j = i; j < subIndex - 1; j++)
            {
                sub[j] = sub[j + 1];
            }
            // move temp to the last index
            sub[subIndex - 1] = temp;
        }
    }
    ascendSort(sub, subIndex);

    printf("Skier                    Age Group Time Withdrew\n");
    printf("------------------------------------------------\n");
    double durHour, durMin;
    char ageValue[8] = { '\0' };
    char withdrew[4] = { '\0' };
    int done = 0;
    // check if there any participants
    if (sub[0].age == 0)
    {
        printf("No Participants\t\t       N/A  N/A      N/A\n");
        done = 1;
    }
    for (int k = 0; k < subIndex && done == 0; k++)
    {
        ageGroup(&sub[k], ageValue);
        if (sub[k].midwayTime != 0)
        {
            durHour = sub[k].finishTime - sub[k].startTime;
            durMin = (durHour - floor(durHour)) * 60;
            strcpy(withdrew, "No");
            printf("%-27s%7s %d:%02d%9s\n", sub[k].name, ageValue, (int)durHour, (int)round(durMin), withdrew);
        }
        else {
            char noTime[4] = "N/A";
            strcpy(withdrew, "Yes");
            printf("%-27s%7s  %s%9s\n", sub[k].name, ageValue, noTime, withdrew);
        }
    }
}

void displayLast(struct SkierInfo info[], int size)
{
    struct SkierInfo sub[3] = { 0 };
    char category = validCategory();
    lastHelper(info, sub, size, category);
    descendSort(sub, 3);
    
    printf("Skier                    Age Group Time\n");
    printf("---------------------------------------\n");
    double durHour, durMin;
    char ageValue[8] = { '\0' };
    int done = 0;
    if (sub[0].age == 0)
    {
        printf("No Participants\t\t       N/A  N/A\n");
        done = 1;
    }
    for (int i = 0; i < 3 && done == 0; i++)
    {
        ageGroup(&sub[i], ageValue);
        durHour = sub[i].finishTime - sub[i].startTime;
        durMin = (durHour - floor(durHour)) * 60;
        printf("%-27s%7s %d:%02d\n", sub[i].name, ageValue, (int)durHour, (int)round(durMin));
    }   
}

void displayWinners(struct SkierInfo info[], int size)
{
    struct SkierInfo shortDist[3] = {0};
    struct SkierInfo mediumDist[3] = {0};
    struct SkierInfo longDist[3] = {0};

    topHelper(info, shortDist, size, 'S');
    topHelper(info, mediumDist, size, 'M');
    topHelper(info, longDist, size, 'L');

    ascendSort(shortDist, 3);
    ascendSort(mediumDist, 3);
    ascendSort(longDist, 3);

    printf("Skier                    Age Group Category Time\n");
    printf("------------------------------------------------\n");
    double durHour, durMin;
    char ageValue[8] = { '\0' };

        if (shortDist[0].age != 0)
        {
            ageGroup(&shortDist[0], ageValue);
            durHour = shortDist[0].finishTime - shortDist[0].startTime;
            durMin = (durHour - floor(durHour)) * 60;
            printf("%-27s%7s    10 km %d:%02d\n", shortDist[0].name, ageValue, (int)durHour, (int)round(durMin));
        }
        else if (shortDist[0].age == 0)
        {
            printf("Not Awarded\t\t       N/A    10 km  N/A\n");
        }
        if (mediumDist[0].age != 0)
        {
            ageGroup(&mediumDist[0], ageValue);
            durHour = mediumDist[0].finishTime - mediumDist[0].startTime;
            durMin = (durHour - floor(durHour)) * 60;
            printf("%-27s%7s    25 km %d:%02d\n", mediumDist[0].name, ageValue, (int)durHour, (int)round(durMin));
        }
        else if (mediumDist[0].age == 0)
        {
            printf("Not Awarded\t\t       N/A    25 km  N/A\n");
        }
        if (longDist[0].age != 0)
        {
            ageGroup(&longDist[0], ageValue);
            durHour = longDist[0].finishTime - longDist[0].startTime;
            durMin = (durHour - floor(durHour)) * 60;
            printf("%-27s%7s    50 km %d:%02d\n", longDist[0].name, ageValue, (int)durHour, (int)round(durMin));
        }
        else if (longDist[0].age == 0)
        {
            printf("Not Awarded\t\t       N/A    50 km  N/A\n");
        }
}

void topHelper(const struct SkierInfo info[], struct SkierInfo sub[], int size, char category)
{
    int count = 0;
    int max_index = 0;
    for (int i = 0; i < size; i++)
    {
        // if the element matches with category and (midwayTime != 0 checks both withdrawn and if there even is a skier)
        if (info[i].raceLength == category && info[i].midwayTime != 0)
        {
            // add first 3 in sub array
            if (count < 3)
            {
                sub[count] = info[i];
                count++;
            }
            else {
                struct SkierInfo max = sub[0];
                for (int j = 1; j < 3; j++)
                {
                    if ((max.finishTime - max.startTime) < (sub[j].finishTime - sub[j].startTime))
                    {
                        max = sub[j];
                        max_index = j;
                    }
                }
                if ((info[i].finishTime - info[i].startTime) < (max.finishTime - max.startTime))
                {
                    sub[max_index] = info[i];
                }
            }
        }
    }
}

void lastHelper(const struct SkierInfo info[], struct SkierInfo sub[], int size, char category)
{
    int count = 0;
    int min_index = 0;
    for (int i = 0; i < size; i++)
    {
        // if the element matches with category and skier did not withdrawn
        if (info[i].raceLength == category && info[i].midwayTime != 0)
        {
            // add first 3 in sub array
            if (count < 3)
            {
                sub[count] = info[i];
                count++;
            }
            else {
                struct SkierInfo min = sub[0];
                for (int j = 1; j < 3; j++)
                {
                    if ((sub[j].finishTime - sub[j].startTime) < (min.finishTime - min.startTime))
                    {
                        min = sub[j];
                        min_index = j;
                    }
                }
                if ((min.finishTime - min.startTime) < (info[i].finishTime - info[i].startTime))
                {
                    sub[min_index] = info[i];
                }
            }
        }
    }
}

void ageGroup(struct SkierInfo* info, char* ageValue)
{
    if (info->age >= 16 && info->age <= 20)
    {
        strcpy(ageValue, "Junior");
    }
    else if (info->age >= 21 && info->age <= 34)
    {
        strcpy(ageValue, "Adult");
    }
    else if (info->age >= 35)
    {
        strcpy(ageValue, "Senior");
    }
}

int menu(void)
{
    printf("What would you like to do?\n");
    printf("0 - Exit\n");
    printf("1 - Print top 3 skiers in a category\n");
    printf("2 - Print all skiers in a category\n");
    printf("3 - Print last 3 skiers in a category\n");
    printf("4 - Print winners in all categories\n");
    printf(": ");
    
    return getIntInRange(0, 4);
}

void reportManagerSystem(struct SkierInfo info[], int size)
{
    printf("************** X-Country Ski Race Reporting **************\n");

    int choice;
    int done = 0;

    while (done != 1)
    {
        choice = menu();

        switch (choice)
        {
        case 1:
            printf("\n");
            displayTop(info, size);
            printf("\n");
            break;

        case 2:
            printf("\n");
            displayAll(info, size);
            printf("\n");
            break;

        case 3:
            printf("\n");
            displayLast(info, size);
            printf("\n");
            break;

        case 4:
            printf("\n");
            displayWinners(info, size);
            printf("\n");
            break;

        default:
            printf("\nKeep on Skiing!\n");
            done = 1;
            break;
        }
    }
}
