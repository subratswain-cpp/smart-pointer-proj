#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

bool isAlphabet(char c) {
    return isalpha(static_cast<unsigned char>(c)) != 0;
}
//function to calculate the mode
double calculateMode(double *contestantScores, int numOfScores){
    sort(contestantScores, contestantScores+numOfScores);
    
    
}


//function calculate the median
double calculateMedian(double *contestantScores, int numOfScores){
    int medianIndex;
    double median;
    sort(contestantScores, contestantScores+numOfScores);
    if(numOfScores % 2 == 1){
        medianIndex = static_cast <int> (numOfScores/2);
        median = *(contestantScores + medianIndex);
        
    }
    else{
        medianIndex = static_cast <int> (numOfScores/2);
        median = *(contestantScores + medianIndex);
        
        medianIndex++;
        median = median + *(contestantScores + medianIndex);
        
        median = median/2;
    }
    return median; 
}



//function to calculate the mean
double calculateMean(double *contestantScores, int numOfScores){
    double sumOfScores;
    for(int i=0; i<numOfScores; i++){
         sumOfScores += *(contestantScores + i);
    }
    return sumOfScores/numOfScores;
}


//function to calculate score 
double calculateScore(string *correctAnswers, string *contestantAnswers, int numOfQuestions ){
    /*int correct = 0;
    for (int i = 0; i < numOfQuestions; i++) {
        if (correctAnswers[i].compare(contestantAnswers[i]) == 0) {
            correct++;
        }
    }
    */
    
    int correct = 0;
    correctAnswers += numOfQuestions - 1; //why are we doing += instead of just =
    contestantAnswers += numOfQuestions - 1;
    
    for (int i = 0; i < numOfQuestions; i++) {
        if (*correctAnswers == *contestantAnswers){
            correct++;
        }
        correctAnswers--;
        contestantAnswers--;
    }
    return (static_cast<double>(correct)/numOfQuestions)*100;
    
}


int main()
{
    string ansKeyFileName = "answers.txt"; 
    string contestAnsFileName = "contestant.txt";
    ifstream ansKeyFile, contestAnsFile;
    
    /* Prompting user for filenames
    cout << "Enter correct answers filename: ";
    cin >> ansKeyFileName;
    cout << "Enter contestant responses filename: ";
    cin >> contestAnsFileName;
    */
    
    //opening the filenames
    ansKeyFile.open(ansKeyFileName);
    contestAnsFile.open(contestAnsFileName);
    
    //checking if the files opened correctly
    if (!ansKeyFile.is_open()){
        cout << "Error opening ansKeyFile";
        return 1;
    }
    
    if (!contestAnsFile.is_open()){
        cout << "Error opening contestAnsFile";
        return 1;
    }
    
    
    //Figure out the number of answers/questions
    // write a function to calculate the number of spaces in a line to then get the number of answers in that line
    int numQuestions = 0;
    char answer;
    while (ansKeyFile.get(answer)) {
        if (isAlphabet(answer)) { // use isSpace function (better)?
            numQuestions++;
        }
    } 
    // reset stuff
    ansKeyFile.clear(); // Reset file stream state
    ansKeyFile.seekg(0); // Move file pointer to the beginning

    //create dynamic allocated array for answerkey & add values in
    string* correctAnswers = new string[numQuestions]; // make numQuestions long unsigned int
    int index = 0;
    while (ansKeyFile.get(answer)) {
        if (isAlphabet(answer)) { // TODO: check for space here aswell like before
            correctAnswers[index++] = answer;
        }
    }

// ****** saving the values of all the scores ******* //
string fakeLine;
int numOfScores = 0;
while(getline(contestAnsFile, fakeLine)){
    numOfScores++;
}
double *contestantScores = new double[numOfScores];
int cScoreIndex = 0;

// Reset the file pointer to the beginning of the file
contestAnsFile.clear();  // Clear any error flags
contestAnsFile.seekg(0, ios::beg); // Set pointer to the beginning of the file
   
    
// ****** read contestant's info ******* //

string line;
while (getline(contestAnsFile,line)){
    size_t spacePos = line.find(' '); //returns the index of the first time of space which separates ID and answers
    
    if (spacePos == string::npos){
        cout << "Invalid contestant file format" << endl;
        continue;
    }
    
    string contestantID = line.substr(0,spacePos);
    //cout << "Contestant Id:" << contestantID << endl;
    
    //create dynamic allocated array for contestant answers 
    string* contestantAnswers = new string[numQuestions];
    
    ///add values in the dynamic array from each line
    int x = 11;
    
    //cout << "This is line:" << line << endl;
    for(int i=0; i<numQuestions; i++){ 
        //contestantAnswers[i] = line[x]; // going through a array of character which is the string
        contestantAnswers[i] = line.at(x);
        x = x+2;
    }
    
    // Calculate contestant score
    double score = calculateScore(correctAnswers, contestantAnswers, numQuestions);
    
    //Add score to the array
    *(contestantScores + cScoreIndex) = score;
    cScoreIndex++;
    
    
    // Display contestant data
       cout << contestantID << " - " << fixed << setprecision(2) << score << endl;

    //Display wrong answers and correct answers
        
        //question number of wrong answer
        for (int i = 0; i < numQuestions; ++i) {
            if (correctAnswers[i] != contestantAnswers[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
        
        //wrong answers
        for (int i = 0; i < numQuestions; ++i) {
            if (correctAnswers[i] != contestantAnswers[i]) {
                cout << contestantAnswers[i] << " ";
            }
        }
        cout << endl;
        
        //right answers
        for (int i = 0; i < numQuestions; ++i) {
            if (correctAnswers[i] != contestantAnswers[i]) {
                cout << correctAnswers[i] << " ";
            }
        }
        cout << endl;
        

        // Clean up contestant answers array
        delete[] contestantAnswers;
    }
    
     //for loop to check the contestantScores array
     /*
    for (int i=0; i<numOfScores; i++){
       cout <<  *(contestantScores + i) << endl;
    }
    */
    
    //calling the mean function and outputting the result
    double mean = calculateMean(contestantScores, numOfScores);
    cout << "Mean: " << mean << endl;
    
    //calling the median function and outputting the result
    double median = calculateMedian(contestantScores, numOfScores);
    cout << "Median: " << median <<endl; 
    
    //calling the mode function
    
    //cout << "Mode(s): " << mode << endl; 
    
    
    


    // Clean up dynamic memory
    delete[] correctAnswers;
    delete[] contestantScores;

    return 0;
}
