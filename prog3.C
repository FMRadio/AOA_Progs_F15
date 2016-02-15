/**************************************************************************//**
* @file
*
* @mainpage 372 Program 3 - FFT
*
* @section course_section Course Information
*
* @author Forrest Miller
*
* @date 12/1/15
*
* @par Professors
*     Antonette Logar & Edward Corwin
* @par Course
*     CSC 372  1:00am-1:50am
* @par Location
*     McLaury 205
* @section program_section Program Information
*
* @details This program calculates the FFT of k sine waves using a sliding
* door approach. It reads from a file, finds the first FFT and uses algebra to
* find the next k FFTs. Next I normalize the points and find the five largest
* which are printed to the file.
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
* @bug Off by .01 on p3b.out and off by .01, .02, or .03 on p3c.out
*
* @todo
*
* @par Modifications and Development Timeline
  @verbatim
  Date             Modification
  --------------   ------------------------------------------------------------
  Nov   18, 2015   Started working on sin program and fft program.
  Nov   20, 2015   Worked on sin program.
  Nov   21, 2015   Finished sin program and submitted test cases.
  Nov   30, 2015   Got correct FFT code from the website.
                   Worked on main and processing values.
  Dec    1, 2015   Got processing working. Output. Testing. Doxygen.
*
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <complex>

using namespace std;

const int MAX = 8096; //Max possible value
const double EPSILON = 1.0e-12; //Epsilon value
const complex<double> I (0, 1); //Imaginary value

/*
* @par description: The indexValue struct holds the value and it's index.
*/
struct indexValue
{
    double value;
    int index;
};

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: complex_round
*
* @par description: The complex_round function sets to zero values that are very
* small and makes output easier to read. Taken from Corwin/Logar webpage.
*
* @param[in] a[] - a complex array
*            n   - int for use in the loop
*
******************************************************************************/
void complex_round(complex <double> a[], int n)
{
    int    i;
    float  x;
    float  y;

    for (i = 0; i < n; i++)
    {
        x = a[i].real();
        y = a[i].imag();
        if (fabs(x) < EPSILON)
          x = 0;
        if (fabs(y) < EPSILON)
          y = 0;
        a[i] = complex<double>(x, y);
    }
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: print_polynomial
*
* @par description: The print_polynomial function finds the 5 max values and
* then outputs them. Taken from Corwin/Logar webpage.
*
* @param[in] a[] - a complex array
*            n   - an int for the loop
*
******************************************************************************/
void print_polynomial(double a[], int n, ofstream &fout)
{
    int i;
    indexValue topFive[5] = {0};

    for(i = 0; i < n/2; i++) //Find largest value
    {
        if(topFive[0].value < a[i])
        {
            topFive[0].value = a[i];
            topFive[0].index = i;
        }
    }
    for(i = 0; i < n/2; i++) //Find second largest value
    {
        if(topFive[1].value < a[i] && a[i] != topFive[0].value)
        {
            topFive[1].value = a[i];
            topFive[1].index = i;
        }
    }
    for(i = 0; i < n/2; i++) //Find third largest value
    {
        if(topFive[2].value < a[i] && a[i] != topFive[0].value
           && a[i] != topFive[1].value)
        {
            topFive[2].value = a[i];
            topFive[2].index = i;
        }
    }
    for(i = 0; i < n/2; i++) //Find fourth largest value
    {
        if(topFive[3].value < a[i] && a[i] != topFive[0].value
           && a[i] != topFive[1].value
           && a[i] != topFive[2].value)
        {
            topFive[3].value = a[i];
            topFive[3].index = i;
        }
    }
    for(i = 0; i < n/2; i++) //Find fifth largest value
    {
        if(topFive[4].value < a[i] && a[i] != topFive[0].value
           && a[i] != topFive[1].value && a[i] != topFive[2].value
           && a[i] != topFive[3].value)
        {
            topFive[4].value = a[i];
            topFive[4].index = i;
        }
    }

    for(i = 0; i < 5; i++) //Output top five values
    {
        fout << topFive[i].index << " " << fixed << setprecision(2)
             << topFive[i].value << endl;
    }
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: fft
*
* @par description: FFT based on CLRS page 911. Taken from Corwin/Logar webpage
*
* @param[in] a[] - a complex array
*            n   - an int for the loop
*            y[] - a complex array
*            dir - a direction value
*
******************************************************************************/
void fft(complex <double> a[], int n, complex <double> y[])
{
    complex  <double> even[n];
    complex  <double> even_fft[n];
    complex  <double> odd[n];
    complex  <double> odd_fft[n];
    complex  <double> omega;
    complex  <double> omega_power;
    int      i;
    int      j;
    int      n2;

    if (n == 1)
    {
        y[0] = a[0];
        return;
    }
  
    n2 = n / 2;
    j = 0;
    for (i = 0; i < n; i += 2)
    {
        even[j] = a[i];
        odd[j] = a[i + 1];
        j ++;
    }
    
    fft(even, n2, even_fft);
    fft(odd, n2, odd_fft);

    omega = cos(2.0 * M_PI / n) + I * sin(2.0 * M_PI / n);
    omega_power = 1;
    for (i = 0; i < n2; i ++)
    {
        y[i] = even_fft[i] + omega_power * odd_fft[i];
        y[i + n2] = even_fft[i] - omega_power * odd_fft[i];
        omega_power = omega * omega_power;
    }
}

/**************************************************************************//**
* @author Forrest Miller
*
* @function name: main
*
* @par description: The main function opens the input and output files. Then it
* reads n, k and the first n values from the file. It then computes the fft for
* those values. Next it reads in k more values, computing new ffts for each new
* value. Finally, it normalizes the points finds the maxes and calls the print.
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
    complex <double> initial[MAX]; //Array for initial n values
    complex <double> yvals[MAX] = {0}; //Array for FFT y values
    complex  <double> omega; //Omega for calculating x
    double total[MAX] = {0}; //Array to hold the total values
    double a_real[MAX]; //Array used for reading in values
    ifstream fin;
    int i,j,k,n;
    ofstream fout;
    string inputFile = "";
    string outputFile = "";

    if( argc != 2 )
    {
        cout << "ERROR: No input file provided." << endl;
        return -1;
    }
    inputFile = argv[1];
    fin.open(inputFile); //Open the input file
    if(!fin)
    {
        cout << "ERROR: Could not open input file: " << inputFile << endl;
        return -1;
    }
    outputFile = inputFile.substr(0, inputFile.find("."));
    outputFile = outputFile + ".out";
    fout.open(outputFile); //Create and open the output file
    if(!fout)
    {
        cout << "ERROR: Could not open output file: " << outputFile << endl;
        return -1;
    }

    fin>>n; //Read in n
    fin>>k; //Read in k

    for (i = 0; i < n; i++) //Read in first n values
    {
        fin >> a_real[i];
        initial[i] = a_real[i];
    }

    fft(initial, n, yvals); //Do initial FFT
    complex_round(yvals, n); //Round
    for(i = 0; i< n; i++)
    {
        total[i] += abs(yvals[i]); //Add to total array
    }

    //shift k times getting k more result sets
    for(i = 1; i < k; i++)
    {
        //Set x to 1 initially and find omega
        complex <double> x = 1;
        omega = cos(2.0 * M_PI / n) + I * sin(2.0 * M_PI / n);

        fin >> a_real[i]; //Read in next value
        for(j = 0; j < n; j++) //Calculate new y values
        {
            yvals[j] = (yvals[j] - initial[i-1] + a_real[i]) / x;
            x = x * omega; //Calculate next x value
        }

        complex_round(yvals, n); //Round
        for(j = 0; j< n; j++)
        {
            total[j] += abs(yvals[j]); //Add to total array
        }
    }
    for(i = 0; i < n; i++) //Divide all values by k
    {
        total[i] = total[i]/k;
    }

    //Took out Normalize because it messed up my answers
    /*for(i = 2; i < n-3; i++)
    {
        total[i] = total[i-2]+total[i-1]+total[i]+total[i+1]+total[i+2];
    }*/

    print_polynomial(total, n, fout);
    return 0;
}
