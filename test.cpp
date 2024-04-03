#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_OPTIONS = 5; // Максимальное количество вариантов ответов

// Структура для хранения вопроса и ответов
struct Question
{
  string question;
  string options[MAX_OPTIONS];
  int numOptions;
  int correctAnswerIndex;
};

// Функция для чтения вопросов из файла
bool readQuestionsFromFile(const string &filename, Question questions[], int &numQuestions)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cerr << "Unable to open file: " << filename << endl;
    return false;
  }

  numQuestions = 0;
  string line;
  while (getline(file, line))
  {
    if (line.empty())
      continue;

    questions[numQuestions].question = line;

    getline(file, line); // Считываем количество вариантов ответов
    questions[numQuestions].numOptions = stoi(line);

    for (int i = 0; i < questions[numQuestions].numOptions; ++i)
    {
      getline(file, line);
      questions[numQuestions].options[i] = line;
    }

    getline(file, line); // Считываем правильный ответ
    questions[numQuestions].correctAnswerIndex = stoi(line);

    ++numQuestions;
  }

  file.close();
  return true;
}

// Функция для вывода вопроса и вариантов ответов
void displayQuestion(const Question &q)
{
  cout << q.question << endl;
  for (int i = 0; i < q.numOptions; ++i)
  {
    cout << i + 1 << ". " << q.options[i] << endl;
  }
}

// Функция для проведения тестирования
void conductTest(const Question questions[], int numQuestions)
{
  int score = 0;

  for (int i = 0; i < numQuestions; ++i)
  {
    displayQuestion(questions[i]);

    int userAnswer;
    cout << "Your answer: ";
    cin >> userAnswer;

    if (userAnswer == questions[i].correctAnswerIndex + 1)
    {
      cout << "Correct!" << endl;
      ++score;
    }
    else
    {
      cout << "Incorrect!" << endl;
    }

    cout << endl;
  }

  cout << "Test completed. Your score: " << score << " out of " << numQuestions << endl;
}

int main()
{
  const string filename = "questions.txt"; // Имя файла с вопросами
  const int MAX_QUESTIONS = 10;            // Максимальное количество вопросов
  Question questions[MAX_QUESTIONS];
  int numQuestions = 0;

  if (!readQuestionsFromFile(filename, questions, numQuestions))
  {
    return 1;
  }

  conductTest(questions, numQuestions);

  return 0;
}
