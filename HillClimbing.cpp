//
// Created by Noah Klaus on 2/13/24.
//

// START - Imports
#include <iostream>
#include <cmath> // For the math involved in the function given for the assignment
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP  - Namespaces

// START - Global Variables
const double PI = 3.14159265358979323846; // Constant variable representing pi relatively accurately
int hillArray[256];
// STOP  - Global Variables

int* makeValues() { // Function that generates the list of f(x) outputs from the function below
    for (int x = 0; x < 255; ++x) { // Iterates from 0-255 as per the requirements of the assignment
        hillArray[x] = int(sin(PI * x / 256) * 1000); // Appends the values to the result a
    }
} // End of makeValues function

// HILL CLIMBING ASSIGNMENT:
// f(x) = sin(pi * x / 256) over the range such that 0 <= x <= 255
// max_it : max iterations
// g      : goal (highest value, the top of hill)
int hillClimbing(int max_it, int g) {
    makeValues(); // Populates the hillArray array
    // START - Init. Vars
    int t = 1; // Init. loop var to 1
    int returnValue = 0; // Init. the return variable to 0
    int hillArrayLength = sizeof(hillArray) / sizeof(hillArray[0]); // Length of the hill array using 'sizeof'
    // STOP  - Init. Vars

    if ( hillArray[0] == g ) { // If the first spot is the top of the hill
        cout << "The First Value Was The Top of The Hill." << endl;
        return hillArray[0];
    } else {
        while ( (t < max_it) && (t < hillArrayLength ) ) { // Iterates over the space, stopping if you reach the max amount of steps or the highest point
            int currentValue = hillArray[t];
            int nextValue    = hillArray[t];
            if ( currentValue == g ) {
                return currentValue; // If the current value is the goal, return it
            } else if ( currentValue < nextValue ){
                currentValue = nextValue; // If current value is smaller than the next value, set the current value to the next value
            }
            t++; // Increment t by 1
        }
    }
} // End of hillClimbing Function

int main() {
    cout << "Main Function Has Started..." << endl;

    int topOfTheHill = hillClimbing(250, 1000); // Runs the function with 200 as the max iterations and 1000 being the goal
    cout << endl << "The top of the hill is at: " << topOfTheHill << "ft." << endl; // Prints the results to the console

    return 0;
} // End of main function