#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isAlphabet(char c) { return isalpha(static_cast<unsigned char>(c)) != 0; }

void WrongQuestionFrequency(vector<size_t>& wrongAnsQuestions,
                            const size_t numOfScores) {
    // Calculate the threshold for the 60% miss rate
    size_t wrongQThreshold = static_cast<size_t>(0.6 * numOfScores) + 1;

    // Sort the array of wrong questions
    sort(wrongAnsQuestions.begin(), wrongAnsQuestions.end());

    cout << "MOST MISSED QUESTIONS:" << endl;

    // Initialize variables for tracking repetitions
    size_t currentQuestion = wrongAnsQuestions[0];
    size_t repCount = 1;

    for (size_t i = 1; i < wrongAnsQuestions.size(); ++i) {
        if (wrongAnsQuestions[i] == currentQuestion) {
            // Same question, increment repetition count
            ++repCount;
        } else {
            // Different question, calculate miss percentage
            double missPercentage = (static_cast<double>(repCount) / numOfScores) * 100;
            if (repCount >= wrongQThreshold) {
                cout << currentQuestion << "\t" << missPercentage << "%" << endl;
            }

            // Update current question and reset repetition count
            currentQuestion = wrongAnsQuestions[i];
            repCount = 1;
        }
    }

    // Print info for the last question
    double missPercentage = (static_cast<double>(repCount) / numOfScores) * 100;
    if (repCount >= wrongQThreshold) {
        cout << currentQuestion << "\t" << missPercentage << "%" << endl;
    }
}

// Function to calculate the mode
double *calculateMode(double *contestantScores, const size_t numOfScores,
                      long unsigned int &numModes) {
  sort(contestantScores, contestantScores + numOfScores);

  vector<double> modes;
  vector<int> repCount;

  double currentMode = contestantScores[0];
  int currentCount = 1;
  int maxCount = 1;

  for (size_t i = 1; i < numOfScores; ++i) {
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

// function calculate the median
double calculateMedian(double *contestantScores, const size_t numOfScores) {
  int medianIndex;
  double median;
  sort(contestantScores, contestantScores + numOfScores);
  if (numOfScores % 2 == 1) {  // if the numOfScores is odd
    medianIndex = static_cast<int>(numOfScores / 2);
    median = *(contestantScores + medianIndex);

  }

  else {  // if the numOfScores is even
    medianIndex = (static_cast<int>(numOfScores / 2)) - 1;
    median = *(contestantScores + medianIndex);

    medianIndex++;
    median = median + *(contestantScores + medianIndex);

    median = median / 2;
  }
  return median;
}

// function to calculate the mean
double calculateMean(double *contestantScores, const size_t numOfScores) {
  double sumOfScores{};
  for (size_t i = 0; i < numOfScores; i++) {
    sumOfScores += *(contestantScores + i);
  }
  return sumOfScores / numOfScores;
}

// function to calculate score
double calculateScore(string *correctAnswers, string *contestantAnswers,
                      const size_t numOfQuestions) {
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

  for (size_t i = 0; i < numOfQuestions; i++) {
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
  unsigned long numQuestions = 0;
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
  unsigned long numOfScores = 0;
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

  // creating a vector to store all wrong answer questions for 60% questions
  // missed
  vector<size_t> wrongAnsQuestions;

  string line;
  while (getline(contestAnsFile, line)) {
    size_t spacePos = line.find(' ');  // returns the index of the first time of
                                       // space which separates ID and answers

    if (spacePos == string::npos) {
      cout << "Invalid contestant file format" << endl;
      continue;
    }

    string contestantID = line.substr(0, spacePos);

    // create dynamic allocated array for contestant answers
    string *contestantAnswers = new string[numQuestions];

    /// add values in the dynamic array from each line
    unsigned long x = 11;

    // cout << "This is line:" << line << endl;
    for (size_t i = 0; i < numQuestions; i++) {
      // contestantAnswers[i] = line[x]; // going through a array of character
      // which is the string
      *(contestantAnswers + i) = line.at(x);
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
    // TODO: Change all these displays to pointer arithmetic

    // Question number of wrong answer
    for (size_t i = 0; i < numQuestions; ++i) {
      if (*(correctAnswers + i) != *(contestantAnswers + i)) {
        cout << i + 1 << " ";
        wrongAnsQuestions.push_back(i + 1);
      }
    }
    cout << endl;

    // Wrong answers - from contestant
    for (size_t i = 0; i < numQuestions; ++i) {
      if (*(correctAnswers + i) != *(contestantAnswers + i)) {
        cout << *(contestantAnswers + i) << " ";
      }
    }
    cout << endl;

    // Right answers - from answer key
    for (size_t i = 0; i < numQuestions; ++i) {
      if (*(correctAnswers + i) != *(contestantAnswers + i)) {
        cout << *(correctAnswers + i) << " ";
      }
    }
    cout << endl;

    // Clean up contestant answers array
    delete[] contestantAnswers;
  }

  // make the printing modular - create a print function, cout the results there
  // calling the mean function and outputting the result
  double mean = calculateMean(contestantScores, numOfScores);
  cout << endl << "Mean: " << mean << endl;

  // calling the median function and outputting the result
  double median = calculateMedian(contestantScores, numOfScores);
  cout << "Median: " << median << endl;

  // calling the mode function
  // create a pointer variable to receive the pointer and create a forloop to
  // run through the mode dynamic array using a pointer,
  long unsigned int numModes = 0;
  double *modes = calculateMode(contestantScores, numOfScores, numModes);
  cout << "Mode: ";
  for (long unsigned i = 0; i < numModes; ++i) {
    // 1. print the Mode
    // cout << modes[i];
    cout << *(modes + i);

    /* check if there are more elements
     */

    if (i < (numModes - 1)) {
      cout << ", ";
    } else {
      cout << endl;
    }
  }
  cout << endl;

  // 60% plus missed question function calling
  WrongQuestionFrequency(wrongAnsQuestions, numOfScores);

  // Clean up dynamic memory
  delete[] correctAnswers;
  delete[] contestantScores;
  delete[] modes;
  // make sure to delete the dynamic arrays created in mode

  return 0;
}
