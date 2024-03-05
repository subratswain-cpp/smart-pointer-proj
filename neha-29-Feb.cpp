#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
// Sunday...
using namespace std;

bool isAlphabet(char c) { return isalpha(static_cast<unsigned char>(c)) != 0; }

// Function to calculate the mode
double *calculateMode(double *contestantScores, int numOfScores,
                      int &numModes) {
  sort(contestantScores, contestantScores + numOfScores);

  vector<double> modes;
  vector<int> repCount;

  double currentMode = contestantScores[0];
  int currentCount = 1;
  int maxCount = 1;

  for (int i = 1; i < numOfScores; ++i) {
    if (contestantScores[i] == contestantScores[i - 1]) {
      currentCount++;
    } else {
      if (currentCount > maxCount) {
        maxCount = currentCount;
        modes.clear();
        modes.push_back(currentMode);
      } else if (currentCount == maxCount) {
        modes.push_back(currentMode);
      }

      currentMode = contestantScores[i];
      currentCount = 1;
    }
  }

  // Check for mode at the end of the array
  if (currentCount > maxCount) {
    modes.clear();
    modes.push_back(currentMode);
  } else if (currentCount == maxCount) {
    modes.push_back(currentMode);
  }

  // Allocate memory for array of modes
  double *modeArray = new double[modes.size()];
  for (size_t i = 0; i < modes.size(); ++i) {
    modeArray[i] = modes[i];
  }

  // Update number of modes
  numModes = modes.size();

  // Return pointer to array of modes
  return modeArray;
}
/*
// Function to calculate the mode - version 2 - returns one mode correctly, not
multiple modes double* calculateMode(double *contestantScores, int numOfScores)
{ sort(contestantScores, contestantScores + numOfScores);

    vector<double> modes;
    vector<int> repCount;

    double currentMode = contestantScores[0];
    int currentCount = 1;
    int maxCount = 1;

    for (int i = 1; i < numOfScores; ++i) {
        if (contestantScores[i] == contestantScores[i - 1]) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
                modes.clear();
                modes.push_back(currentMode);
            } else if (currentCount == maxCount) {
                modes.push_back(currentMode);
            }

            currentMode = contestantScores[i];
            currentCount = 1;
        }
    }

    // Check for mode at the end of the array
    if (currentCount > maxCount) {
        modes.clear();
        modes.push_back(currentMode);
    } else if (currentCount == maxCount) {
        modes.push_back(currentMode);
    }

    // Allocate memory for array of modes
    double *modeArray = new double[modes.size()];
    for (size_t i = 0; i < modes.size(); ++i) {
        modeArray[i] = modes[i];
    }

    // Return pointer to array of modes
    return modeArray;
}
*/
/*function to calculate the mode (version 1)
double* calculateMode(double *contestantScores, int numOfScores){
    sort(contestantScores, contestantScores+numOfScores);
    vector<double> modes;
    vector<double> repCount;
    double compareVariable = 0;

    //create vector(because we don't know length of num of modes for array) for
repetitionCount and store all the time that variable incremetns for a vairable.
store its highest value for each variable

    for(int i=0; i<numOfScores; i++){ //start for loop to update the the compare
variable variable = *(contestantScores + i );// update compare variable int
repetitionCount=0; for(int j=0; j<numOfScores; j++){ //for loop to update the
pointer if(variable == *(contestantScores + j )){ repetitionCount++;
            }
        }
        if (repetitionCount > 0){ //store the repetitionCount variable in its
vector here reCount.push_back(repetitionCount)
        }

        if (repetitionCount > 0){ // you might not even need this vector, you
can just find the corresponding value in the array itself
            modes.push_back(variable);
        }

    }
    for (int i = 0; i < repCount.size()-1; ++i) {
        double compareVal = repCount[i];  //TOASK: can you use bracket notation
while using vectors for (int j = 0; j < repCount.size()-1; ++j){
            if(compareVal>repCount)

        }
    }


    // go through the repetition vector and see what is it's highest
value/values (first see how many highvalues you have)
        //create a dynamic array and store all modes
        //change function return type to pointer
        //if single value, find the corresponding array value and save it in the
mode array
        // if multiple high values, find the corresponding array values and save
it in the mode array
        // return the mode arraypointer

}
*/

// function calculate the median
double calculateMedian(double *contestantScores, int numOfScores) {
  int medianIndex;
  double median;
  sort(contestantScores, contestantScores + numOfScores);
  if (numOfScores % 2 == 1) {
    medianIndex = static_cast<int>(numOfScores / 2);
    median = *(contestantScores + medianIndex);

  } else {
    medianIndex = static_cast<int>(numOfScores / 2);
    median = *(contestantScores + medianIndex);

    medianIndex++;
    median = median + *(contestantScores + medianIndex);

    median = median / 2;
  }
  return median;
}

// function to calculate the mean
double calculateMean(double *contestantScores, int numOfScores) {
  double sumOfScores{};
  for (int i = 0; i < numOfScores; i++) {
    sumOfScores += *(contestantScores + i);
  }
  return sumOfScores / numOfScores;
}

// function to calculate score
double calculateScore(string *correctAnswers, string *contestantAnswers,
                      int numOfQuestions) {
  /*int correct = 0;
  for (int i = 0; i < numOfQuestions; i++) {
      if (correctAnswers[i].compare(contestantAnswers[i]) == 0) {
          correct++;
      }
  }
  */

  int correct = 0;
  correctAnswers += numOfQuestions - 1;  // why are we doing += instead of just
                                         // =
  contestantAnswers += numOfQuestions - 1;

  for (int i = 0; i < numOfQuestions; i++) {
    if (*correctAnswers == *contestantAnswers) {
      correct++;
    }
    correctAnswers--;
    contestantAnswers--;
  }
  return (static_cast<double>(correct) / numOfQuestions) * 100;
}

int main() {
  string ansKeyFileName = "answers.txt";
  string contestAnsFileName = "contestant.txt";
  ifstream ansKeyFile, contestAnsFile;

  /* Prompting user for filenames
  cout << "Enter correct answers filename: ";
  cin >> ansKeyFileName;
  cout << "Enter contestant responses filename: ";
  cin >> contestAnsFileName;
  */

  // opening the filenames
  ansKeyFile.open(ansKeyFileName);
  contestAnsFile.open(contestAnsFileName);

  // checking if the files opened correctly
  if (!ansKeyFile.is_open()) {
    cout << "Error opening ansKeyFile";
    return 1;
  }

  if (!contestAnsFile.is_open()) {
    cout << "Error opening contestAnsFile";
    return 1;
  }

  // Figure out the number of answers/questions
  //  write a function to calculate the number of spaces in a line to then get
  //  the number of answers in that line
  int numQuestions = 0;
  char answer;
  while (ansKeyFile.get(answer)) {
    if (isAlphabet(answer)) {  // use isSpace function (better)?
      numQuestions++;
    }
  }
  // reset stuff
  ansKeyFile.clear();   // Reset file stream state
  ansKeyFile.seekg(0);  // Move file pointer to the beginning

  // create dynamic allocated array for answerkey & add values in
  string *correctAnswers =
      new string[numQuestions];  // make numQuestions long unsigned int
  int index = 0;
  while (ansKeyFile.get(answer)) {
    if (isAlphabet(answer)) {  // TODO: check for space here aswell like before
      correctAnswers[index++] = answer;
    }
  }

  // ****** saving the values of all the scores ******* //
  string fakeLine;
  int numOfScores = 0;
  while (getline(contestAnsFile, fakeLine)) {
    numOfScores++;
  }
  double *contestantScores = new double[numOfScores];
  int cScoreIndex = 0;

  // Reset the file pointer to the beginning of the file
  contestAnsFile.clear();  // Clear any error flags
  contestAnsFile.seekg(0,
                       ios::beg);  // Set pointer to the beginning of the file

  // ****** read contestant's info ******* //

  string line;
  while (getline(contestAnsFile, line)) {
    size_t spacePos = line.find(' ');  // returns the index of the first time of
                                       // space which separates ID and answers

    if (spacePos == string::npos) {
      cout << "Invalid contestant file format" << endl;
      continue;
    }

    string contestantID = line.substr(0, spacePos);
    // cout << "Contestant Id:" << contestantID << endl;

    // create dynamic allocated array for contestant answers
    string *contestantAnswers = new string[numQuestions];

    /// add values in the dynamic array from each line
    int x = 11;

    // cout << "This is line:" << line << endl;
    for (int i = 0; i < numQuestions; i++) {
      // contestantAnswers[i] = line[x]; // going through a array of character
      // which is the string
      contestantAnswers[i] = line.at(x);
      x = x + 2;
    }

    // Calculate contestant score
    double score =
        calculateScore(correctAnswers, contestantAnswers, numQuestions);

    // Add score to the array
    *(contestantScores + cScoreIndex) = score;
    cScoreIndex++;

    // Display contestant data
    cout << contestantID << " - " << fixed << setprecision(2) << score << endl;

    // Display wrong answers and correct answers

    // question number of wrong answer
    for (int i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << i + 1 << " ";
      }
    }
    cout << endl;

    // wrong answers
    for (int i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << contestantAnswers[i] << " ";
      }
    }
    cout << endl;

    // right answers
    for (int i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << correctAnswers[i] << " ";
      }
    }
    cout << endl;

    // Clean up contestant answers array
    delete[] contestantAnswers;
  } // End of while

  // for loop to check the contestantScores array
  /*
 for (int i=0; i<numOfScores; i++){
    cout <<  *(contestantScores + i) << endl;
 }
 */

  // calling the mean function and outputting the result
  double mean = calculateMean(contestantScores, numOfScores);
  cout << "Mean: " << mean << endl;

  // Output modes // Subrat: Commented below 6 Lines
//   cout << "Number of modes: " << numModes << endl;
//   cout << "Modes: ";
//   for (int i = 0; i < numModes; ++i) {
//     cout << modes[i] << " ";
//   }
//   cout << endl;

  // calling the median function and outputting the result
  double median = calculateMedian(contestantScores, numOfScores);
  cout << "Median: " << median << endl;

  // calling the mode function
  // create a pointer variable to receive the pointer and create a forloop to
  // run through the mode dynamic array using a pointer,
  int l_numModes{};
  double* mode = calculateMode(contestantScores, numOfScores, l_numModes);
  cout << "Mode(s): " << *mode << endl;


  // Clean up dynamic memory
  delete[] correctAnswers;
  delete[] contestantScores;
  // make sure to delete the dynamic arrays created in mode

  return 0;
}
