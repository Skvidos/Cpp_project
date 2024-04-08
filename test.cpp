#include <iostream>
#include <fstream>

const int MAX_QUESTION_LENGTH = 256; // Максимальная длина вопроса
const int MAX_OPTIONS = 5;           // Максимальное количество вариантов ответов

// Структура для хранения вопроса и ответов
struct Question
{
  char question[MAX_QUESTION_LENGTH];
  char options[MAX_OPTIONS][MAX_QUESTION_LENGTH];
  int numOptions;
  int correctAnswerIndex;
};

// Функция для чтения вопросов из файла
bool readQuestionsFromFile(const char *filename, Question questions[], int &numQuestions)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Unable to open file: " << filename << std::endl;
    return false;
  }

  numQuestions = 0;
  while (file.peek() != EOF)
  {
    file.getline(questions[numQuestions].question, MAX_QUESTION_LENGTH);
    file >> questions[numQuestions].numOptions;
    file.ignore(); // Пропускаем символ новой строки

    for (int i = 0; i < questions[numQuestions].numOptions; ++i)
    {
      file.getline(questions[numQuestions].options[i], MAX_QUESTION_LENGTH);
    }

    file >> questions[numQuestions].correctAnswerIndex;
    file.ignore(); // Пропускаем символ новой строки

    ++numQuestions;
  }

  file.close();
  return true;
}

// Функция для вывода вопроса и вариантов ответов
void displayQuestion(const Question &q)
{
  std::cout << q.question << std::endl;
  for (int i = 0; i < q.numOptions; ++i)
  {
    std::cout << i + 1 << ". " << q.options[i] << std::endl;
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
    std::cout << "Your answer: ";
    std::cin >> userAnswer;

    if (userAnswer == questions[i].correctAnswerIndex + 1)
    {
      std::cout << "Correct!" << std::endl;
      ++score;
    }
    else
    {
      std::cout << "Incorrect!" << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << "Test completed. Your score: " << score << " out of " << numQuestions << std::endl;
}

int main()
{
  const char *filename = "questions.txt"; // Имя файла с вопросами
  const int MAX_QUESTIONS = 10;           // Максимальное количество вопросов
  Question questions[MAX_QUESTIONS];
  int numQuestions = 0;

  if (!readQuestionsFromFile(filename, questions, numQuestions))
  {
    return 1;
  }

  conductTest(questions, numQuestions);

  return 0;
}
