#include <iostream>
#include <fstream>
#include <string>

const int MAX_OPTIONS = 5; // Максимальное количество вариантов ответов

// Структура для хранения вопроса и ответов
struct Question
{
  std::string question;
  std::string options[MAX_OPTIONS];
  int numOptions;
  std::string correctAnswer;
  int points;
};

// Функция для чтения вопросов из файла
bool readQuestionsFromFile(const std::string &filename, Question questions[], int &numQuestions)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Unable to open file: " << filename << std::endl;
    return false;
  }

  numQuestions = 0;
  while (std::getline(file, questions[numQuestions].question))
  {
    file >> questions[numQuestions].numOptions;
    file.ignore(); // Пропускаем символ новой строки

    for (int i = 0; i < questions[numQuestions].numOptions; ++i)
    {
      std::getline(file, questions[numQuestions].options[i]);
    }

    std::getline(file, questions[numQuestions].correctAnswer); // Считываем правильный ответ
    file >> questions[numQuestions].points;                    // Считываем количество баллов за вопрос
    file.ignore();                                             // Пропускаем символ новой строки
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

// Функция для ответа на вопрос
bool answerQuestion(const Question &q)
{
  std::cout << "Enter your answer: ";
  std::string userAnswer;
  std::getline(std::cin, userAnswer);
  std::cin.ignore(); // Очищаем входной буфер
  return userAnswer == q.correctAnswer;
}

// Функция для проведения тестирования
int conductTest(const Question questions[], int numQuestions)
{
  int totalScore = 0;

  for (int i = 0; i < numQuestions; ++i)
  {
    displayQuestion(questions[i]);
    bool correctAnswer = answerQuestion(questions[i]);

    if (correctAnswer)
    {
      std::cout << "Correct! You earned " << questions[i].points << " points." << std::endl;
      totalScore += questions[i].points;
    }
    else
    {
      std::cout << "Incorrect! The correct answer is: " << questions[i].correctAnswer << std::endl;
    }

    std::cout << std::endl;
  }

  std::cout << "Test completed. Your total score: " << totalScore << std::endl;
  return totalScore;
}

int main()
{
  const std::string filename = "questions2.txt"; // Имя файла с вопросами
  const int MAX_QUESTIONS = 10;                  // Максимальное количество вопросов
  Question questions[MAX_QUESTIONS];
  int numQuestions = 0;

  if (!readQuestionsFromFile(filename, questions, numQuestions))
  {
    return 1;
  }

  int score = conductTest(questions, numQuestions);

  return 0;
}
