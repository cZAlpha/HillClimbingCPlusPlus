//
// Created by Noah Klaus on 2/13/24.
//

// START - Imports
#include <iostream>
#include <cmath> // For the math involved in the function given for the assignment
#include <iomanip> // Include the header for setprecision
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP  - Namespaces

// START - Global Variables
const double PI = 3.14159265358979323846; // Constant variable representing pi relatively accurately
double hillArrayF[256];
double hillArrayG[256];
// STOP  - Global Variables



// START - Supporting Functions
double f(int x) { // f(x) = sin(pi * x / 256) over the range such that 0 <= x <= 255
    double result = sin(PI * x / 256); // Find f(x)
    result = std::floor(result * 100000 + 0.5) / 100000; // Round to 5 decimal points
    return result;
} // End of f(x)

double g(double x) {
    double exponent_term = -2 * pow(((x - 0.1) / 0.9), 2);
    double sine_term = pow((sin(5 * PI * x)), 6);
    double result = pow(2, exponent_term) * sine_term;

    // Truncate the result to 5 decimal points
    result = std::floor(result * 100000 + 0.5) / 100000; // Round to 5 decimal points

    return result;
} // End of g(x)

int* makeValuesF() { // Function that generates the list of f(x) outputs from the function below
    for (int x = 0; x < 255; ++x) { // Iterates from 0-255 as per the requirements of the assignment
        hillArrayF[x] = f(x); // Appends the values to the result array hillArrayF
    }
} // End of makeValueF function

int* makeValuesG() { // Function that generates the list of f(x) outputs from the function below
    for (int x = 0; x <= 255; ++x) { // Iterates from 0-255 as per the requirements of the assignment
        double gVal = x * 0.00390625; // Finds the applicable value between 0-256 for g(x)
        hillArrayG[x] = g(gVal); // Appends the values to the result array hillArrayG
        }
} // End of makeValues function

double findGoalForG() { // Function to find the goal for the HillArrayG array using basic brute force algorithm
    double goal = 0;
    for (int x = 0; x <= 255; ++x) {
        double gVal = x * 0.00390625; // Finds the applicable value between 0-256 for g(x)
        if ( g(gVal) > goal ) {
            goal = g(gVal);
        }
    }
    return goal;
} // End of findGoalForG function

double findGoalForF() { // Function to find the goal for the HillArrayG array using basic brute force algorithm
    double goal = 0;
    for (int x = 0; x <= 255; ++x) {
        if ( f(x) > goal ) {
            goal = f(x);
        }
    }
    return goal;
} // End of findGoalForG function
// STOP - Supporting Functions



// START - Hill Climbing Algorithms
    // HILL CLIMBING Algorithm # 1:
    // max_it : max iterations
    // g      : goal (highest value, the top of hill)
double hillClimbing(int max_it, double g, double *hillArray) { // FIRST ALGORITHM
    // START - Init. Vars
    int t = 1; // Init. loop var to 1
    int hillArrayLength = sizeof(hillArray) / sizeof(hillArray[0]); // Length of the hill array using 'sizeof'
    // STOP  - Init. Vars

    if ( hillArray[0] == g ) { // If the first spot is the top of the hill
        cout << "The First Value Was The Top of The Hill." << endl;
        return hillArray[0];
    } else {
        while ( (t < max_it) && (t < hillArrayLength - 1 ) ) { // Iterates over the space, stopping if you reach the max amount of steps or the highest point
            double currentValue = hillArray[t];
            double nextValue    = hillArray[t + 1];
            if ( currentValue == g ) {
                return currentValue; // If the current value is the goal, return it
            } else if ( currentValue < nextValue ){
                currentValue = nextValue; // If current value is smaller than the next value, set the current value to the next value
            }
            t++; // Increment t by 1
        }
    }
} // End of hillClimbing Function



// STOP  - Hill Climbing Algorithms



// START - Main
int main() {
    cout << "Main Function Has Started..." << endl;

    // This code that is commented out is an example that visualizes how the hillArray array is populated
    // through the use of the console.
    cout << "Blank Array f(x):" << endl;
    for (int x = 0; x < 255; ++x) { // Print values of the BLANK array to the console
        cout << hillArrayF[x] << " "; // No 'endl' so that it prints in one line
    }
    cout << "Blank Array g(x):" << endl;
    for (int x = 0; x < 255; ++x) { // Print values of the BLANK array to the console
        cout << hillArrayG[x] << " "; // No 'endl' so that it prints in one line
    }

    makeValuesF(); // Populates the f(x) hill array
    makeValuesG(); // Populates the g(x) hill array

    cout << endl << "Full Array f(x):" << endl;
    for (int x = 0; x < 255; ++x) { // Print values of the FULL array to the console
        cout << hillArrayF[x] << " "; // No 'endl' so that it prints in one line
    }
    cout << endl << "Full Array g(x):" << endl;
    for (int x = 0; x < 255; ++x) { // Print values of the FULL array to the console
        cout << hillArrayG[x] << " "; // No 'endl' so that it prints in one line
    }

    cout << endl; // Blank space

    // First Algorithm On f(x) and g(x) hills:
    double topOfFHillUsingFirstAlg = hillClimbing(255, findGoalForF(),       hillArrayF); // Runs the function with 200 as the max iterations and 1000 being the goal
    cout << endl << "(ALG. 1) The top of the f(x) hill is at: " << topOfFHillUsingFirstAlg << " ft." << endl; // Prints the results to the console
    double topOfGHillUsingFirstAlg = hillClimbing(255, findGoalForG(), hillArrayG); // Runs the function with 200 as the max iterations and 1000 being the goal
    cout << endl << "(ALG. 1) The top of the g(x) hill is at: " << topOfGHillUsingFirstAlg << " ft." << endl; // Prints the results to the console
    // Finds and displays the goals for f and g
    double Fgoal = findGoalForF();
    cout << endl << "F's Goal: " << Fgoal;
    double Ggoal = findGoalForG();
    cout << endl << "G's Goal: " << Ggoal << endl;

    return 0;
} // End of main function
// STOP  - Main