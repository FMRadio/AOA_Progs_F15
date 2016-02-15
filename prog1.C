/**************************************************************************//**
* @file
*
* @mainpage 372 Program 1 - Repeated Pairs
*
* @section course_section Course Information
*
* @author Forrest Miller
*
* @date 10/4/15
*
* @par Professors
*     Antonette Logar & Edward Corwin
* @par Course
*     CSC 372  1:00am-1:50am
* @par Location
*     McLaury 205
* @section program_section Program Information
*
* @details This program reads in each line of a file called "pairs.in" and
* checks if it contains all pair strings. It then outputs to a file called
* "pairs.out". The output is the case number followed by a space and either
* a yes or no depending on the result.
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions
*
* @par Usage
  @verbatim
  c:\> <prog1>.exe
  d:\> c:\bin\<prog1>.exe
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug
*
* @todo
*
* @par Modifications and Development Timeline
  @verbatim
  Date             Modification
  --------------   ------------------------------------------------------------
  Sept 18, 2015    Started program. Made print and initializeTable functions.
  Sept 23, 2015    Worked on main function.
  Sept 26, 2015    Finished main function. Started thinking about findPairs.
  Sept 30, 2015    Started working on findPairs function.
  Oct   1, 2015    Working on recursive version of findPairs.
  Oct   2, 2015    Debugged findPairs function. Getting closer to a solution.
  Oct   3, 2015    Added dynamic table. Finished program and added doxygen.
*
******************************************************************************/
#include <iostream>
#include <fstream>
using namespace std;

//constant integer that has the max value a string can be
const int MAX_CASE = 5000;
//integer 2d array size 5000 by 5000
static int pairTable[MAX_CASE][MAX_CASE];

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: initializeTable
*
* @par description: The initializeTable function initializes the table with the
* length of the string to all -1's.
*
* @param[in] length - integer that holds length of test string
*
******************************************************************************/
void initializeTable(int length)
{
    //integers i and j for looping
    int i;
    int j;

    //loop through length of string
    for( i=0; i <= length; i++ )
    {
        for( j = 0; j <= length; j++ )
        {
            //initialize table to all -1
            pairTable[i][j] = -1;
        }//End inner for loop
    }//End outer for loop
}//End initializeTable

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: printCase
*
* @par description: The printCase function outputs to the file in the formatted
* way requested.
*
* @param[in] caseNum - integer that holds the case number
*            answer  - bool that holds the answer of the case
*            fout    - ofstream for file output
*
******************************************************************************/
void printCase(int caseNum, bool answer, ofstream &fout)
{
    if(answer)
    {
        //If true output case number and a yes
        fout << caseNum << " yes" << endl;
    }//End if
    else
    {
        //Else output case number and a no
        fout << caseNum << " no" << endl;
    }//End else
}//End printCase

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: findPairs
*
* @par description: The findPairs function checks if we have already found the
* answer for the specific string. It then checks if the start and end are the
* same. Finally, it loops through starting at the end and compares the halves.
* If they are equal then make a recursive call with a substring of the main
* string. Increment count for each time through the loop. Return the result
* when done.
*
* @param[in] testcase - string that holds the test string
*            start    - integer that holds the start of the test string
*            end      - integer that holds the end of the test string
*
* @returns result: True  - if pairs
*                  False - if not pairs
*
******************************************************************************/
bool findPairs(string testcase, int start, int end)
{
    int count = 1; //integer to hold count used in substring creation
    bool result = false; //boolean to hold final result
    string firstString = ""; //string to hold front substring
    string secondString = ""; //string to hold back substring
    string testString = testcase; //string to hold testcase string

    if(pairTable[start][end] != -1)
    {
        //if answer is in the table return the table value
        return (bool)pairTable[start][end];
    }//End if
    if ( start == end )
    {
        //if start is equal to end return true
        return true;
    }//End if

    //starting at end-2 decrement by 2 each time through
    for ( int i = end - 2; i >= 0; i-= 2 )
    {
        //get substrings
        firstString = testString.substr( i, count );
        secondString = testString.substr( i + count, count );

        if( firstString == secondString )
        {
            //if strings are equal recusive call with substring
            result = findPairs(testString.substr(start,(end-(count+1))),
                               start, end-(count*2));
        }//End if
        count++; //increment count
    }//End for

    //Add result to table and return result
    pairTable[start][end] = (int)result;

    return result;
}//End findPairs

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: main
*
* @par description: The main function opens the input and output files and then
* starts reading in line by line. With each read in case, the program
* reinitializes the pairTable. It then checks the strings length and calls the
* findPairs function. Finally it calls the print method.
*
* @returns result: 0  - no errors occured
*                  -1 - file error occured
*
******************************************************************************/
int main()
{
    ifstream fin; //ifstream used for reading in file
    ofstream fout; //ofstream used for writing to file
    int caseNum = 0; //integer used to hold the case number
    bool answer; //boolean used to hold the results for each case
    string testcase = ""; //string to hold each testcase

    //open in file
    fin.open("pairs.in");
    if(!fin)
    {
        //if not open - error and exit
        cout << "Unable to open file: pairs.in" << endl;
        return -1;
    }//End if

    //open out file
    fout.open("pairs.out");
    if(!fout)
    {
        //if not open - error and exit
        cout << "Unable to open file: pairs.out" << endl;
        return -1;
    }//End if
    
    //while a string can be read in
    while(fin >> testcase)
    {
        //increment caseNum++
        caseNum++;
        //initialize the table
        initializeTable(testcase.length());
        if (testcase.length() % 2 != 0)
        {
            //if testcase length is not even then answer is false
            answer = false;
        }//End if
        else
        {
            //otherwise call findPairs to calculate answer
            answer = findPairs(testcase, 0, testcase.length());
        }//End else
        //print the case result
        printCase(caseNum, answer, fout);
    }//End while
    return 0;
}//End main
