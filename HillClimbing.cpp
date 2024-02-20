//
// Created by Noah Klaus on 2/13/24.
//

// START - Imports
#include <iostream>
#include <cmath> // For the math involved in the function given for the assignment
#include <random> // For pseudo random number generator
// STOP  - Imports

// START - Namespaces
using namespace std;
// STOP  - Namespaces

// START - Global Variables
const double PI = 3.14159265358979323846; // Constant variable representing pi relatively accurately
const int ARRAYLENGTH = 256;
const int PARAMETERARRAYLENGTH = 30;
    // Hill Arrays
double hillArrayF[ARRAYLENGTH];
double hillArrayG[ARRAYLENGTH];
    // Parameter Value Arrays
double maxIterationParameterArray[PARAMETERARRAYLENGTH];
double nStartParameterArray[PARAMETERARRAYLENGTH];
double tParameterArray[PARAMETERARRAYLENGTH];
    // Arrays Holding The Values Returned From Each Algorithm Given The Respective Parameters From The Arrays Above
double firstAlgorithmOutputFromParameterArray[PARAMETERARRAYLENGTH];
double secondAlgorithmOutputFromParameterArray[PARAMETERARRAYLENGTH];
double thirdAlgorithmOutputFromParameterArray[PARAMETERARRAYLENGTH];
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

void makeValuesF() { // Function that generates the list of f(x) outputs from the function below
    for (int x = 0 ; x < 255 ; ++x) { // Iterates from 0-255 as per the requirements of the assignment
        hillArrayF[x] = f(x); // Appends the values to the result array hillArrayF
    }
} // End of makeValueF function

void makeValuesG() { // Function that generates the list of f(x) outputs from the function below
    for (int x = 0 ; x <= 255 ; ++x) { // Iterates from 0-255 as per the requirements of the assignment
        double gVal = x * 0.00390625; // Finds the applicable value between 0-256 for g(x)
        hillArrayG[x] = g(gVal); // Appends the values to the result array hillArrayG
        }
} // End of makeValues function

double findGoalForF() { // Function to find the goal for the HillArrayG array using basic brute force algorithm
    double goal = 0;
    for (int x = 0; x <= 255; ++x) {
        if ( f(x) > goal ) {
            goal = f(x);
        }
    }
    return goal;
} // End of findGoalForG function

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

double randomBetweenZeroAndOne() {
    // Create a random number engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Generate a random double between 0 and 1
    return dis(gen);
}

bool findPhi(double currentVal, double nextVal, double T) {
    double randNum = randomBetweenZeroAndOne(); // Random number
    return randNum < (1 / (1 + exp( (currentVal - nextVal) / (T) ) ) );
} // This function calculates Phi to simplify the stochastic hill clim

double findTValues(double x) {
    return 0.0000001 * pow(x, 2); // f(x) = 0.0000001x^(2)
}

void printHillArrays() {
    // This code that is commented out is an example that visualizes how the hillArray array is populated
    // through the use of the console.
    cout << "Array f(x):" << endl;
    for (int x = 0; x < 255; ++x) { // Print values of the BLANK array to the console
        cout << hillArrayF[x] << " "; // No 'endl' so that it prints in one line
    }

    cout << endl << "Array g(x):" << endl;
    for (int x = 0; x < 255; ++x) { // Print values of the BLANK array to the console
        cout << hillArrayG[x] << " "; // No 'endl' so that it prints in one line
    }
    cout << endl; // Blank space
}

void printGivenParameterArray(double* array) {
    int array_length = sizeof(array) / sizeof(array[0]);
    cout << "Parameter Array: " << endl;
    for (int x = 0; x < PARAMETERARRAYLENGTH; ++x) { // Print values of the BLANK array to the console
        cout << array[x] << " "; // No 'endl' so that it prints in one line
    }
    cout << endl;
}

void printGivenHillArray(double* array) {
    int array_length = sizeof(array) / sizeof(array[0]);
    cout << "Hill Array: " << endl;
    for (int x = 0; x < ARRAYLENGTH; ++x) { // Print values of the BLANK array to the console
        cout << array[x] << " "; // No 'endl' so that it prints in one line
    }
    cout << endl;
}

void populateMaxIterationParameterArray() {
    for (int x = 0; x < 256; ++x) { // Iterates from 1-255 as per the requirements of the assignment
        maxIterationParameterArray[x] = ceil(x * 8.6); // Appends the values to the result array hillArrayF
    }
}

void populateNStartParameterArray() {
    for (int x = 0; x < 256; ++x) { // Iterates from 1-255 as per the requirements of the assignment
        nStartParameterArray[x] = ceil(x * 8.6); // Appends the values to the result array hillArrayF
    }
}

void populateTParameterArray() {
    for (int x = 0; x < 256; ++x) { // Iterates from 1-255 as per the requirements of the assignment
        tParameterArray[x] = findTValues(x); // Appends the values to the result array hillArrayF
    }
}
// STOP - Supporting Functions



// START - Hill Climbing Algorithms
double hillClimbing(int max_it, double g, double* hillArray) { // FIRST ALGORITHM
    // START - Init. Vars
    int t = 0; // Init. loop var to 1
    int hillArrayLength = ARRAYLENGTH; // Length of the hill array using 'sizeof'
    double currentValue;
    // STOP  - Init. Vars

    if ( hillArray[0] == g ) { // If the first spot is the top of the hill (this should never be true if only running this function by itself)
        cout << "The First Value Was The Top of The Hill." << endl;
        return hillArray[0];
    } else { // If the first spot was not the top of the hill
        while ( (t < max_it) && (t < hillArrayLength - 1 ) ) { // Iterates over the space, stopping if you reach the max amount of steps or the highest point
            double currentValue = hillArray[t];     // x
            double nextValue    = hillArray[t + 1]; // x' (next x)
            if ( currentValue > nextValue ) { return currentValue; } // If the current value is the goal, return it
            else if ( currentValue < nextValue ){ currentValue = nextValue; } // If current value is smaller than the next value, set the current value to the next value
            t++; // Increment t by 1
        }
    }
    return currentValue;
} // End of hillClimbing Function

double iterativeHillClimbing(int n_start, int max_it, double g, double* hillArray) { // Second algorithm ; Iterative Hill Climbing
    // START - Init. Variables
    double best = 0; // Return Variable
    int    loopVar = 1; // Loop Variable
    // STOP  - Init. Variables
    do {
        double hillHeight = hillClimbing(max_it, g, hillArray); // Runs the first algorithm
        loopVar++; // Increments loop variable
        if (hillHeight > best) {
            best = hillHeight;
        }
    } while ( (loopVar < n_start) and (best != g) ); // End of do loop
    return best;
} // End of Iterative Hill Climbing Function

double stochasticHillClimbing(int max_it, double T, double g, double* hillArray) { // Sometimes returns weird values, not sure why
    double currentValue;
    double nextValue;
    int    loopVar = 1;
    while ( (loopVar < (max_it-1)) and (currentValue != g) ) {
        currentValue = hillArray[loopVar];
        nextValue    = hillArray[loopVar + 1];
        if ( findPhi(currentValue, nextValue, T) ) { currentValue = nextValue; } // Swap currentValue and nextValue based on Phi
        loopVar++;
    } // End of while loop
    return currentValue;
} // End of Stochastic Hill Climbing Function
// STOP  - Hill Climbing Algorithms



// START - Varying Parameter Algorithm Running Function
    // For First Algorithm
void populatefirstAlgorithmOutputFromParameterArrayUsingF() {
    for (int x = 0; x < 256; ++x) { // Iterates from 1-255 as per the requirements of the assignment
        firstAlgorithmOutputFromParameterArray[x] = hillClimbing(firstAlgorithmOutputFromParameterArray[x], findGoalForF(), hillArrayF); // Appends the values to the result array hillArrayF
    }
}

void populatefirstAlgorithmOutputFromParameterArrayUsingG() {
    for (int x = 0; x < 256; ++x) { // Iterates from 1-255 as per the requirements of the assignment
        firstAlgorithmOutputFromParameterArray[x] = hillClimbing(firstAlgorithmOutputFromParameterArray[x], findGoalForG(), hillArrayG); // Appends the values to the result array hillArrayF
    }
}

void runHillClimbingVaryParamsOnF() {
    populateMaxIterationParameterArray(); // Populates the max iter. parameter array for use
    populatefirstAlgorithmOutputFromParameterArrayUsingF(); // Populates the output array
    cout << endl << "First Algorithm Output From Varying Parameters On F Hill: " << endl;
    printGivenParameterArray(firstAlgorithmOutputFromParameterArray); // Prints it
}

void runHillClimbingVaryParamsOnG() {
    populateMaxIterationParameterArray(); // Populates the max iter. parameter array for use
    populatefirstAlgorithmOutputFromParameterArrayUsingG(); // Populates the output array
    cout << endl << "First Algorithm Output From Varying Parameters On G Hill: " << endl;
    printGivenParameterArray(firstAlgorithmOutputFromParameterArray); // Prints it
}

    // For Second Algorithm
void populatesecondAlgorithmOutputFromParameterArrayUsingF() {
    for (int x = 0; x < 256; ++x) { // Iterates from 1-255 as per the requirements of the assignment
        secondAlgorithmOutputFromParameterArray[x] = iterativeHillClimbing(secondAlgorithmOutputFromParameterArray[x], firstAlgorithmOutputFromParameterArray[x], findGoalForF(), hillArrayF); // Appends the values to the result array hillArrayF
    }
}

void populatesecondAlgorithmOutputFromParameterArrayUsingG() {
    for (int x = 0; x < 256; ++x) { // Iterates from 1-255 as per the requirements of the assignment
        secondAlgorithmOutputFromParameterArray[x] = iterativeHillClimbing(firstAlgorithmOutputFromParameterArray[x], firstAlgorithmOutputFromParameterArray[x], findGoalForG(), hillArrayG); // Appends the values to the result array hillArrayF
    }
}

void runIterativeHillClimbingVaryParamsOnF() {
    populateMaxIterationParameterArray(); // Populates the max iter. parameter array for use
    populateNStartParameterArray();       // Populates the n_start parameter array for use
    populatesecondAlgorithmOutputFromParameterArrayUsingF(); // Populates the output array
    cout << endl << "Second Algorithm Output From Varying Parameters On F Hill: " << endl;
    printGivenParameterArray(secondAlgorithmOutputFromParameterArray); // Prints it
}

void runIterativeHillClimbingVaryParamsOnG() {
    populateMaxIterationParameterArray(); // Populates the max iter. parameter array for use
    populateNStartParameterArray();       // Populates the n_start parameter array for use
    populatesecondAlgorithmOutputFromParameterArrayUsingG(); // Populates the output array
    cout << endl << "Second Algorithm Output From Varying Parameters On G Hill: " << endl;
    printGivenParameterArray(secondAlgorithmOutputFromParameterArray); // Prints it
}
    // For Third Algorithm ( NOT DONE )
// STOP  - Varying Parameter Algorithm Running Function



// START - Accuracy Determining Functions
double findAccuracyOfHillClimbing(int timesToRun) {
    double wrongCounter = 0; // # of times the function returned the wrong value

    for ( int i = 0 ; i <= timesToRun ; i++ ) {
        double topOfFHillUsingFirstAlg = hillClimbing(255, findGoalForF(), hillArrayF);
        double topOfGHillUsingFirstAlg = hillClimbing(255, findGoalForG(), hillArrayG);
        if ( topOfFHillUsingFirstAlg != findGoalForF() ) { wrongCounter++; }
        if ( topOfGHillUsingFirstAlg != findGoalForG() ) { wrongCounter++; }
    }

    return wrongCounter / (timesToRun * 2); // Percent of misses (Multiply timesToRun * 2 due to running the function twice per loop cycle)
} // STATIC PARAMETER TESTING

double findAccuracyOfIterativeHillClimbing(int timesToRun) {
    double wrongCounter = 0; // # of times the function returned the wrong value

    for ( int i = 0 ; i <= timesToRun ; i++ ) {
        double topOfFHillUsingSecondAlg = iterativeHillClimbing(1, 255, findGoalForF(), hillArrayF);
        double topOfGHillUsingSecondAlg = iterativeHillClimbing(1, 255, findGoalForG(), hillArrayG);
        if ( topOfFHillUsingSecondAlg != findGoalForF() ) { wrongCounter++; }
        if ( topOfGHillUsingSecondAlg != findGoalForG() ) { wrongCounter++; }
    }

    return wrongCounter / (timesToRun * 2); // Percent of misses (Multiply timesToRun * 2 due to running the function twice per loop cycle)
} // STATIC PARAMETER TESTING

double findAccuracyOfStochasticHillClimbing(int timesToRun, double tVal) {
    double wrongCounter = 0; // # of times the function returned the wrong value

    for ( int i = 0 ; i <= timesToRun ; i++ ) {
        double topOfFHillUsingThirdAlg = stochasticHillClimbing(255, tVal, findGoalForF(), hillArrayF);
        double topOfGHillUsingThirdAlg = stochasticHillClimbing(255, tVal, findGoalForG(), hillArrayG);
        if ( topOfFHillUsingThirdAlg != findGoalForF() ) { wrongCounter++; }
        if ( topOfGHillUsingThirdAlg != findGoalForG() ) { wrongCounter++; }
    }

    return (wrongCounter / (timesToRun * 2) ) * 100; // Percent of misses (Multiply timesToRun * 2 due to running the function twice per loop cycle)
} // STATIC PARAMETER TESTING

// TO DO:
// The following functions should determine the accuracy of the given algorithm over the given parameter arrays,
// In other words: we should populate the (firstAlgorithmOutputFromParameterArray through the thirdAlgorithmOutputFromParameterArray)
//                 and then iterate over the aforementioned output arrays and output the percentage of wrong answers
//                 contained within the output arrays, which will effectively return the accuracy of the given
//                 algorithms over the given varying parameter values.
// - first  algorithm accuracy finding using the parameter array to dynamically test parameters
// - second algorithm accuracy finding using the parameter array to dynamically test parameters
// - third  algorithm accuracy finding using the parameter array to dynamically test parameters

// STOP  - Accuracy Determining Functions



// START - Main
int main() {
    cout << "Main Function Has Started..." << endl;

    printHillArrays(); // Prints both hill arrays BLANK (before population)
    makeValuesF(); // Populates the f(x) hill array
    makeValuesG(); // Populates the g(x) hill array
    printHillArrays(); // Prints both hill arrays FULL (after population)

    // Finds and displays the goals for f and g
    double Fgoal = findGoalForF();
    cout << endl << "F's Goal: " << Fgoal;
    double Ggoal = findGoalForG();
    cout << endl << "G's Goal: " << Ggoal << endl;

    // Running Each Algorithm Individually on Each Hill Once
    // First Algorithm On f(x) and g(x) hills:
    double topOfFHillUsingFirstAlg = hillClimbing(255, findGoalForF(), hillArrayF);
    cout << endl << "(ALG. 1) The top of the f(x) hill is at: " << topOfFHillUsingFirstAlg << " ft." << endl; // Prints the results to the console
    double topOfGHillUsingFirstAlg = hillClimbing(255, findGoalForG(), hillArrayG);
    cout << "(ALG. 1) The top of the g(x) hill is at: " << topOfGHillUsingFirstAlg << " ft." << endl; // Prints the results to the console
    // Second Algorithm on f(x) and g(x) hills:
    double topOfFHillUsingSecondAlg = iterativeHillClimbing(1, 255, findGoalForF(), hillArrayF);
    cout << endl << "(ALG. 2) The top of the f(x) hill is at: " << topOfFHillUsingSecondAlg << " ft." << endl; // Prints the results to the console
    double topOfGHillUsingSecondAlg = iterativeHillClimbing(1, 255, findGoalForG(), hillArrayG);
    cout << "(ALG. 2) The top of the g(x) hill is at: " << topOfGHillUsingSecondAlg << " ft." << endl; // Prints the results to the console
    // Third Algorithm on f(x) and g(x) hills:
    double topOfFHillUsingThirdAlg = stochasticHillClimbing(255, 0.00001, findGoalForF(), hillArrayF);
    cout << endl << "(ALG. 3) The top of the f(x) hill is at: " << topOfFHillUsingThirdAlg << " ft." << endl; // Prints the results to the console
    double topOfGHillUsingThirdAlg = stochasticHillClimbing(255, 0.00001, findGoalForG(), hillArrayG);
    cout << "(ALG. 3) The top of the g(x) hill is at: " << topOfGHillUsingThirdAlg << " ft." << endl; // Prints the results to the console

    // Finding Miss Percentage of Each Algorithm
    double missPercentageOfFirstAlgorithm = findAccuracyOfHillClimbing(100);
    double missPercentageOfSecondAlgorithm = findAccuracyOfIterativeHillClimbing(100);
    double missPercentageOfThirdAlgorithm = findAccuracyOfStochasticHillClimbing(100, 0.0001);
    cout << endl << "Miss Percentage Of HillClimb:  " << missPercentageOfFirstAlgorithm << "%" << endl;
    cout << "Miss Percentage Of Iterative:  " << missPercentageOfSecondAlgorithm << "%" << endl;
    cout << "Miss Percentage Of Stochastic: " << missPercentageOfThirdAlgorithm << "%" << endl << endl;

    // Populating and Printing Each Parameter Array
    populateMaxIterationParameterArray();
    populateNStartParameterArray();
    populateTParameterArray();
    printGivenParameterArray(maxIterationParameterArray);
    printGivenParameterArray(nStartParameterArray);
    printGivenParameterArray(tParameterArray);

    cout << endl;
    runHillClimbingVaryParamsOnF();
    runHillClimbingVaryParamsOnG();
    runIterativeHillClimbingVaryParamsOnF();
    runIterativeHillClimbingVaryParamsOnG();
} // End of main function
// STOP  - Main