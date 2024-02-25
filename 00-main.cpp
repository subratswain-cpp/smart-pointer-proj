//
//  main.cpp
//  MemLeakExpriments
//
//  Created by Subrat Kumar Swain on 25/02/24.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

bool isAlphabet(char c) {
  return std::isalpha(static_cast<unsigned char>(c)) != 0;
}

double calculateScore(string* correctAnswers, string* contestantAnswers,
                      std::size_t numOfQuestions) {
  unsigned long correct = 0;
  for (std::size_t i = 0; i < numOfQuestions; i++) {
    if (correctAnswers[i].compare(contestantAnswers[i]) == 0) {
      correct++;
    }
  }
  return (static_cast<double>(correct) / static_cast<double>(numOfQuestions)) * 100; // Either operand can be made double. But clang complains. So we make both the operands to double by using static_cast.
}

int main() {
  string ansKeyFileName = "/Users/subrat/Downloads/neha-proj2/answers.txt";
  string contestAnsFileName = "/Users/subrat/Downloads/neha-proj2/contestant.txt";
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
  size_t numQuestions{0};  // Uniform Initialization.
  char answer;
  while (ansKeyFile.get(answer)) {
    // cout << "Answer inside while loop:" << answer << 'X' << endl;
    if (isAlphabet(answer)) {  // use isSpace function (better)?
      numQuestions++;
    }
  }
  // cout << "Number of questions = " << numQuestions << endl; //TODO: delete

  // reset stuff
  ansKeyFile.clear();   // Reset file stream state
  ansKeyFile.seekg(0);  // Move file pointer to the beginning

  // create dynamic allocated array for answerkey & add values in
  string* correctAnswers = new string[numQuestions];
  int index = 0;
  while (ansKeyFile.get(answer)) {
    if (isAlphabet(answer)) {  // TODO: check for space here aswell like before
      correctAnswers[index++] = answer;
    }
  }

  // ****** read contestant's info ******* //

  // 1 read the first line of the file: this is contestant 1
  // 2 create a dynamic array to hold the first contestant's answers
  // 3 create

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
    string* contestantAnswers = new string[numQuestions];

    /// add values in the dynamic array from each line
    std::size_t x = 11;
    // cout << "This is line:" << line << endl;
    for (std::size_t i = 0; i < numQuestions; i++) {
      // contestantAnswers[i] = line[x]; // going through a array of character
      // which is the string
      contestantAnswers[i] = line.at(x);
      x = x + 2;
    }

    // Calculate contestant score
    double score =
        calculateScore(correctAnswers, contestantAnswers, numQuestions);

    // Display contestant data
    cout << contestantID << " - " << fixed << setprecision(2) << score << endl;

    // Display wrong answers and correct answers

    // question number of wrong answer
    for (size_t i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << i + 1 << " ";
      }
    }
    cout << endl;

    // wrong answers
    for (std::size_t i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << contestantAnswers[i] << " ";
      }
    }
    cout << endl;

    // right answers
    for (std::size_t i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << correctAnswers[i] << " ";
      }
    }
    cout << endl;

    // Clean up contestant answers array
    delete[] contestantAnswers;
  }

  // Clean up dynamic memory
  delete[] correctAnswers;

  return 0;
}
