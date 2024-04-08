#include <iostream>
#include <fstream>
#include "sqlite3.h"

using namespace std;

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
  ifstream file(filename);
  if (!file.is_open())
  {
    cerr << "Unable to open file: " << filename << endl;
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

// int main()
// {
//   const char *filename = "questions.txt"; // Имя файла с вопросами
//   const int MAX_QUESTIONS = 10;           // Максимальное количество вопросов
//   Question questions[MAX_QUESTIONS];
//   int numQuestions = 0;

//   if (!readQuestionsFromFile(filename, questions, numQuestions))
//   {
//     return 1;
//   }

//   conductTest(questions, numQuestions);

//   return 0;
// }

int main()
{
  sqlite3 *db;
  int rc = sqlite3_open("Questions.db", &db); // Открываем базу данных "quiz.db"
  if (rc)
  {
    cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
    return 1;
  }
  else
  {
    cout << "Opened database successfully" << endl;
  }

  sqlite3_stmt *stmt;
  const char *sql = "SELECT * FROM Questions"; // SQL-запрос для выборки всех строк из таблицы Questions

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr); // Подготавливаем SQL-запрос
  if (rc != SQLITE_OK)
  {
    cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
    return 1;
  }

  // Выполняем запрос и обрабатываем результат
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
  {
    // Получаем значения из результирующей строки
    int id = sqlite3_column_int(stmt, 0);
    const char *question = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    int numOptions = sqlite3_column_int(stmt, 2);
    // Здесь можно получить остальные значения и обработать их

    // Пример вывода данных на экран
    cout << "ID: " << id << ", Question: " << question << ", NumOptions: " << numOptions << endl;
  }

  if (rc != SQLITE_DONE)
  {
    cerr << "Error fetching data: " << sqlite3_errmsg(db) << endl;
  }

  sqlite3_finalize(stmt); // Завершаем операцию с базой данных
  sqlite3_close(db);      // Закрываем базу данных

  return 0;
}