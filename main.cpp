/* Using Smart Pointer */
// Check this file: smartptr_fix-neha3rdFeb_4Err.cpp
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>  // for smart pointers
#include <string>

using namespace std;

bool isAlphabet(char c) {
  return std::isalpha(static_cast<unsigned char>(c)) != 0;
}

double calculateScore(const std::unique_ptr<string[]>& correctAnswers,
                      const std::unique_ptr<string[]>& contestantAnswers,
                      std::size_t numOfQuestions) {
  unsigned long correct = 0;
  for (std::size_t i = 0; i < numOfQuestions; i++) {
    if (correctAnswers[i].compare(contestantAnswers[i]) == 0) {
      correct++;
    }
  }
  return (static_cast<double>(correct) / static_cast<double>(numOfQuestions)) *
         100;
}

int main() {
  string ansKeyFileName = "answers.txt";
  string contestAnsFileName = "contestant.txt";
  ifstream ansKeyFile, contestAnsFile;

  ansKeyFile.open(ansKeyFileName);
  contestAnsFile.open(contestAnsFileName);

  if (!ansKeyFile.is_open()) {
    cout << "Error opening ansKeyFile";
    return 1;
  }

  if (!contestAnsFile.is_open()) {
    cout << "Error opening contestAnsFile";
    return 1;
  }

  size_t numQuestions{0};
  char answer;
  while (ansKeyFile.get(answer)) {
    if (isAlphabet(answer)) {
      numQuestions++;
    }
  }

  ansKeyFile.clear();
  ansKeyFile.seekg(0);

  // Using smart pointers to manage dynamic memory
  std::unique_ptr<string[]> correctAnswers(new string[numQuestions]);
  std::size_t index = 0;
  while (ansKeyFile.get(answer)) {
    if (isAlphabet(answer)) {
      correctAnswers[index++] = answer;
    }
  }

  string line;
  while (getline(contestAnsFile, line)) {
    size_t spacePos = line.find(' ');

    if (spacePos == string::npos) {
      cout << "Invalid contestant file format" << endl;
      continue;
    }

    string contestantID = line.substr(0, spacePos);

    std::unique_ptr<string[]> contestantAnswers(new string[numQuestions]);

    std::size_t x = 11;
    for (std::size_t i = 0; i < numQuestions; i++) {
      contestantAnswers[i] = line.at(x);
      x = x + 2;
    }

    double score =
        calculateScore(correctAnswers, contestantAnswers, numQuestions);

    cout << contestantID << " - " << fixed << setprecision(2) << score << endl;

    for (size_t i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << i + 1 << " ";
      }
    }
    cout << endl;

    for (std::size_t i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << contestantAnswers[i] << " ";
      }
    }
    cout << endl;

    for (std::size_t i = 0; i < numQuestions; ++i) {
      if (correctAnswers[i] != contestantAnswers[i]) {
        cout << correctAnswers[i] << " ";
      }
    }
    cout << endl;
  }

  return 0;
}
