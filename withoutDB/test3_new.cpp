#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <windows.h>

using namespace std;

const int MAX_OPTIONS = 5; // Максимальное количество вариантов ответов

// Структура для хранения вопроса и ответов
struct Question
{
  string question;
  string options[MAX_OPTIONS];
  int numOptions;
  string correctAnswer;
  int points;
};
// Функция для чтения вопросов из файла
bool readQuestionsFromFile(const string &filename, Question questions[], int &numQuestions);

// Функция для вывода вопроса и вариантов ответов
void displayQuestion(const Question &q);

// Функция для ответа на вопрос
bool answerQuestion(const Question &q);

// Функция для проведения тестирования
int conductTest(const Question questions[], int numQuestions);

int main()
{
  setlocale(LC_ALL, "ru_RU.UTF-8");
  SetConsoleCP(CP_UTF8);                   // Установка кодовой страницы UTF-8 для ввода
  SetConsoleOutputCP(CP_UTF8);             // Установка кодовой страницы UTF-8 для вывода
  const string filename = "questions.txt"; // Имя файла с вопросами
  const short MAX_QUESTIONS = 20;          // Максимальное количество вопросов
  Question questions[MAX_QUESTIONS];
  int numQuestions = 0;

  // Проверка на чтения вопросов из файла
  if (!readQuestionsFromFile(filename, questions, numQuestions))
  {
    return 1;
  }

  int score = conductTest(questions, numQuestions);

  return 0;
}

// Функция для чтения вопросов из файла
bool readQuestionsFromFile(const string &filename, Question questions[], int &numQuestions)
{
  ifstream file(filename);

  // Проверка на открытие файла
  if (!file.is_open())
  {
    cerr << "Невозможно открыть файл: " << filename << endl;
    return false;
  }

  numQuestions = 0;

  // Чтение файла
  while (getline(file, questions[numQuestions].question))
  {
    file >> questions[numQuestions].numOptions;
    file.ignore(); // Пропускаем символ новой строки

    for (int i = 0; i < questions[numQuestions].numOptions; ++i)
    {
      getline(file, questions[numQuestions].options[i]);
    }

    getline(file, questions[numQuestions].correctAnswer); // Считываем правильный ответ
    file >> questions[numQuestions].points;               // Считываем количество баллов за вопрос
    file.ignore();                                        // Пропускаем символ новой строки
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
    cout << q.options[i] << endl;
  }
}

string normalizeString(const std::string &str)
{
  std::string normalizedStr;
  normalizedStr.reserve(str.length()); // Зарезервируем память для новой строки

  for (char c : str)
  {
    // Приводим символ к нижнему регистру
    char lowercaseChar = std::tolower(c);

    // Добавляем символ в новую строку, если это не пробел
    if (lowercaseChar != ' ')
    {
      normalizedStr.push_back(lowercaseChar);
    }
  }

  return normalizedStr;
}

// Функция для ответа на вопрос
bool answerQuestion(const Question &q)
{
  // cout << "Введите свой ответ: ";
  // string userAnswer;
  // getline(cin, userAnswer);
  // cin.ignore(); // Очищаем входной буфер
  // return userAnswer == q.correctAnswer;

  locale::global(std::locale("ru_RU.UTF-8")); // Устанавливаем локаль "ru_RU.UTF-8" для правильной кодировки символов

  cout << "Введите свой ответ: ";
  string userAnswer;
  getline(cin, userAnswer);
  cin.ignore(); // Очищаем входной буфер

  // Нормализуем строки перед сравнением
  userAnswer = normalizeString(userAnswer);
  string correctAnswer = normalizeString(q.correctAnswer);

  return userAnswer == correctAnswer;
}

// Функция для проведения тестирования
int conductTest(const Question questions[], int numQuestions)
{
  int totalScore = 0;

  for (int i = 0; i < numQuestions; ++i)
  {
    displayQuestion(questions[i]);
    bool correctAnswer = answerQuestion(questions[i]);

    // Проверка правильного ответа
    if (correctAnswer)
    {
      cout << "Правильно! Вы заработали " << questions[i].points << " баллов." << endl;
      totalScore += questions[i].points;
    }
    else
    {
      cout << "Неверно! Правильный ответ: " << questions[i].correctAnswer << endl;
    }

    cout << endl;
  }

  cout << "Тест завершен. Ваш общий балл: " << totalScore << endl;
  return totalScore;
}