/**************************************************************************//**
* @file
*
* @mainpage 372 Program 2 - Half-and-Half
*
* @section course_section Course Information
*
* @author Forrest Miller
*
* @date 11/1/15
*
* @par Professors
*     Antonette Logar & Edward Corwin
* @par Course
*     CSC 372  1:00am-1:50am
* @par Location
*     McLaury 205
* @section program_section Program Information
*
* @details This program takes a list of points and checks if they make a convex
* shape. If so, it then calculates the bisection of the shape and prints that
* to the output file. If not, it outputs 'No Solution' to the file.
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions - Please use -std=c++11 when compiling. This is
* needed for the fin.open and fout.open to work.
*
* @par Usage
  @verbatim
  c:\> <prog2>.exe
  d:\> c:\bin\<prog2>.exe
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
  Oct.  18, 2015   Started program on paper/notepad++.
  Oct.  20, 2015   Mapped out print, area, and straddle functions.
  Oct.  22, 2015   Finally got into Opp Lab. Wrote point struct, printCase, &
                   most of main function.
  Oct.  23, 2015   Worked on convex.
  Oct.  24, 2015   Added given geometry functions.
  Oct.  27, 2015   Worked on adding convex to file in Opp Lab.
  Oct.  29, 2015   Finished writing convex, started bisection, wrote doxygen.
  Nov.   1, 2015   Finished program and Doxygen. Submitted.
*
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

/*
* @par description: The point struct holds the x and y values for a coordinate.
*/
struct point
{
    double x_value; //double to hold x-value
    double y_value; //double to hold y-value
};

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: printCase
*
* @par description: The printCase function outputs to the file. "Case" followed
* by the case number we are currently on is printed first. If the points
* provided for the case do not make a convex polygon "No solution" is printed.
* Otherwise, the x-value for where the convex polygon should be split is
* printed with precision to 5 decimal places.
*
* @param[in] caseNum - integer that holds the current case number
*            convex  - bool that says whether the points made a convex polygon
*            answer  - double that holds the answer for the case
*            fout    - ofstream for file output
*
******************************************************************************/
void printCase(int caseNum, bool convex, double answer, ofstream &fout)
{
    if(convex)
    {
        fout << fixed << setprecision(5);
        fout << "Case " << caseNum << ": " << answer << endl;
    }
    else
    {
        fout << "Case " << caseNum << ": No solution" << endl;
    }
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: area
*
* @par description: The area function uses a vector of pionts to find the area.
* Got this code from Corwin and Logar's website.
*
* @param[in] points - an array that holds points
*            n      - an integer to hold how many points are in points[]
*
* @returns result: returns a double to show the area
*
******************************************************************************/
double area(vector<point> points, int n)
{
    int i, j;
    double result = 0.0;
    
    for( i = 0; i < n; i++ )
    {
        j = ( i + 1 ) % n;
        result += points[i].x_value * points[j].y_value;
        result -= points[i].y_value * points[j].x_value;
    }
    return fabs( result / 2 );
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: min
*
* @par description: The min function compares two doubles and returns the
* smaller of the two. Got this code from Corwin and Logar's website.
*
* @param[in] a - a double to hold the first value
*            b - a double to hold the second value
*
* @returns result: returns the smaller of the two doubles
*
******************************************************************************/
double min(double a, double b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: max
*
* @par description: The max function compares two doubles and returns the
* larger of the two. Got this code from Corwin and Logar's website.
*
* @param[in] a - a double to hold the first value
*            b - a double to hold the second value
*
* @returns result: returns the larger of the two doubles
*
******************************************************************************/
double max(double a, double b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: findMaxPoint
*
* @par description: The findMaxPoint function compares all the points and then
* returns the largest x valued point.
*
* @param[in] points - a vector of the points read in
*
* @returns result: returns the largest point
*
******************************************************************************/
int findMaxPoint(vector<point> points)
{
    int temp = 0;

    for(int i = 1; i < points.size(); i++)
    {
        if(points[i].x_value > points[temp].x_value)
        {
            temp = i;
        }
    }
    return temp;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: findMinPoint
*
* @par description: The findMinPoint function compares all the points and then
* returns the smallest x valued point.
*
* @param[in] points - a vector of the points read in
*
* @returns result: returns the smallest point
*
******************************************************************************/
int findMinPoint(vector<point> points)
{
    int temp = 0;

    for(int i = 1; i < points.size(); i++)
    {
        if(points[i].x_value < points[temp].x_value)
        {
            temp = i;
        }
    }
    return temp;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: cross
*
* @par description: Calculates the cross product of vectors a and b. Got this
* code from Corwin and Logar's website.
*
* @param[in] a - a point struct that holds the x and y values of a point
*            b - a point struct that holds the x and y values of a point
*
* @returns result: returns the cross product of the two points passed in
*
******************************************************************************/
double cross(point a, point b)
{
    return a.x_value * b.y_value - a.y_value * b.x_value;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: direction
*
* @par description: Compute cross product of vector from a to b and vector from
* b to c. Set to zero if close to zero. Got this code from Corwin and Logar's
* website.
*
* @param[in] a - a point struct that holds the x and y values of a point
*            b - a point struct that holds the x and y values of a point
*            c - a point struct that holds the x and y values of a point
*
* @returns result: returns a double telling whether the turn is left or right
*
******************************************************************************/
double direction(point a, point b, point c)
{
    point ab;
    point bc;
    double result;

    ab.x_value = b.x_value - a.x_value;
    ab.y_value = b.y_value - a.y_value;
    bc.x_value = c.x_value - b.x_value;
    bc.y_value = c.y_value - b.y_value;
    result =  cross(ab, bc);
    if (fabs(result) < 1.0e-6)
    {
        result = 0.0;
    }
    return result;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: turn
*
* @par description: Is the turn from a to b to c clockwise? Got this code from
* Corwin and Logar's website.
*
* @param[in] a - a point struct that holds the x and y values of a point
*            b - a point struct that holds the x and y values of a point
*            c - a point struct that holds the x and y values of a point
*
* @returns result: true  - right turn
*                  false - left turn
*
******************************************************************************/
bool turn(point a, point b, point c)
{
    return (direction(a, b, c) > 0);
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: isConvex
*
* @par description: The isConvex function goes through all the points and
* checks the turns to see if the shape is convex.
*
* @param[in] points - vector of points read in
*
* @returns result: true  - the shape is convex
*                  false - the shape is not convex
*
******************************************************************************/
bool isConvex(vector<point> points)
{
    int i = 0;
    int j = 1;
    int k = 2;
    bool answer1, answer2;

    answer1 = turn(points[i], points[j], points[k]);

    while(k < points.size()-1)
    {
        i++;
        j++;
        k++;
        answer2 = turn(points[i], points[j], points[k]);
        if (answer1 != answer2)
            return false;
    }
    return true;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: interpolate
*
* @par description: The interpolate function finds the y value for the
* intersection.
*
* @param[in] p1     - point struct that holds the first point
*            p2     - point struct that holds the second point
*            xValue - a double to hold the cut line value
*
* @returns result: returns a double for the y value
*
******************************************************************************/
double interpolate(point p1, point p2, double xValue)
{
    double slope;
    double intercept;
    double yValue;

    slope = (p2.y_value - p1.y_value) / (p2.x_value - p1.x_value);
    intercept = p2.y_value - slope * p2.x_value;
    yValue = slope * xValue + intercept;
    
    return yValue;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: splitArea
*
* @par description: The splitArea function finds the area on the left side of
* cut line.
*
* @param[in] points - vector of points read in
*            xValue - a double to hold the cut line value
*
* @returns result: returns a double for the area of the left half
*
******************************************************************************/
double splitArea(vector<point> points, double xValue)
{
    bool isGreaterThanX = false;
    int size = points.size();
    point newPoint;
    vector<point> tempVect;

    newPoint.x_value = xValue;

    for(int i = 0; i < size+1; i++)
    {
        if(points[i%size].x_value < xValue)
        {
            if(isGreaterThanX)
            {
                newPoint.y_value = interpolate(points[i%size],points[(i-1)%size],xValue);
                tempVect.push_back(newPoint);
                isGreaterThanX = false;
            }
            tempVect.push_back(points[i%size]);
        }
        else
        {
            if(!isGreaterThanX)
            {
                newPoint.y_value = interpolate(points[i%size],points[(i-1)%size],xValue);
                tempVect.push_back(newPoint);
                isGreaterThanX = true;
            }
        }
    }
    return area(tempVect, tempVect.size());
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: bisection
*
* @par description: The bisection function calculates the x value that will cut
* the area of the convex shape in half.
*
* @param[in] points - vector of points read in
*
* @returns result: returns the x value to cut the convex shape at in order to
* cut the shape in half
*
******************************************************************************/
double bisection(vector<point> points, int maxPoint, int minPoint)
{
    double highPoint = points[maxPoint].x_value;
    double lowPoint = points[minPoint].x_value;
    double cutLine = (highPoint + lowPoint) / 2;
    double totalArea = area(points, points.size());
    double desiredArea = totalArea / 2;
    double leftArea = 0.0;

    leftArea = splitArea(points, cutLine);
    
    while(fabs(leftArea - desiredArea) >= 1.0e-6)
    {
        if(leftArea - desiredArea > 0)
        {
            highPoint = cutLine;
            cutLine = (highPoint + lowPoint) / 2;
        }
        else
        {
            lowPoint = cutLine;
            cutLine = (highPoint + lowPoint) / 2;
        }
        leftArea = splitArea(points, cutLine);
    }
    return cutLine;
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: Main
*
* @par description: The main function reads in the points from the input file
* as well as creates the output file. It calls the convex and bisection
* functions in order to figure out the answer for each case. It then calls the
* print method to output the result.
*
* @param[in] argc - number of arguments given in command line
*            argv - arguments given in command line
*
* @returns result:  0 - no errors occured
*                  -1 - file error occured
*
******************************************************************************/
int main(int argc, char ** argv)
{
    bool convex = false;
    double answer_x_value = 0.0;
    ifstream fin;
    int i;
    int caseNumber = 0;
    int numOfPoints = 0;
    ofstream fout;
    string inputFile = "";
    string outputFile = "";
    vector<point> points;
    
    if( argc != 2 )
    {
        cout << "ERROR: No input file provided." << endl;
        return -1;
    }
    inputFile = argv[1];
    fin.open(inputFile); //Open the input file
    if(!fin)
    {
        cout << "Could not open input file: " << inputFile << endl;
        return -1;
    }
    outputFile = inputFile.substr(0, inputFile.find("."));
    outputFile = outputFile + ".out";
    fout.open(outputFile); //Create and open the output file
    if(!fout)
    {
        cout << "" << outputFile << endl;
        return -1;
    }

    while( fin >> numOfPoints ) //Read in the num of points for each test case
    {
        points.clear();
        caseNumber++;
        for(i = 0; i< numOfPoints; i++)
        {
            point p;
            fin >> p.x_value;
            fin >> p.y_value;
            points.push_back(p);
        }
        convex = isConvex(points);
        if(!convex)
        {
            printCase(caseNumber, convex, answer_x_value, fout);
        }
        else
        {
            answer_x_value = bisection(points, findMaxPoint(points),
                                       findMinPoint(points));
            printCase(caseNumber, convex, answer_x_value, fout);
        }
    }
}
