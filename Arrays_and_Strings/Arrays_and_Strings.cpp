#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <memory>
#include <bitset>
#include <string>


//******************************************************************************
// 1.1 Реализуйте алгоритм, определяющий, все ли символы в строке встречаются
// только один раз.А если при этом запрещено использование дополнительных
// структур данных?
//******************************************************************************

bool IsUnique_set(const std::string& str)
{
  if (str.length() < 2)
    return true;

  std::set<std::string::value_type> filter;

  for (const auto& ch : str)
  {
    auto res = filter.insert(ch);

    if (!res.second)
      return false;
  }

  return true;
}


bool IsUnique_loops(const std::string& str)
{
  if (str.length() < 2)
    return true;

  for (int i{}; i < str.length() - 1; ++i)
  {
    for (int j = i + 1; j < str.length(); ++j)
    {
      if (str[i] == str[j])
        return false;
    }
  }

  return true;
}



//******************************************************************************
// 1.2. Для двух строк напишите метод, определяющий, является ли одна строка
// перестановкой другой.
//******************************************************************************

bool IsReshuffle_sort(const std::string& first, const std::string& second)
{
  if (first.length() != second.length())
    return false;

  std::string sortedFirst(first);
  std::sort(sortedFirst.begin(), sortedFirst.end());

  std::string sortedSecond(second);
  std::sort(sortedSecond.begin(), sortedSecond.end());

  return sortedFirst == sortedSecond;
}


bool IsReshuffle_CharSet(const std::string& first, const std::string& second)
{
  if (first.length() != second.length())
    return false;

  std::map<char, std::size_t> charSet;

  for (auto& ch : first)
  {
    auto res = charSet.try_emplace(ch, 1);
    if (false == res.second)
      res.first->second++;
  }

  for (auto& ch : second)
  {
    auto found = charSet.find(ch);
    if (charSet.end() == found)
      return false;

    if (1 == found->second)
    {
      charSet.erase(found);
    }
    else
    {
      found->second--;
    }
  }

  return charSet.empty();
}



//******************************************************************************
// 1.3. Напишите метод, заменяющий все пробелы в строке символами '%20'. Можете
// считать, что длина строки позволяет сохранить дополнительные символы,
// а фактическая длина строки известна заранее. (Примечание: при реализации
// метода на java для выполнения операции "на месте" используйте символьный
// массив.)
// Пример:
// Ввод: "Mr John Smith    ", 13
// Вывод : "Mr%20John%20Smith"
//******************************************************************************

void ChangeWhiteSpaces(char* str, int strLen)
{
  int bufLen{};
  for (int i{}; i < strLen; ++i)
  {
    if (str[i] == ' ')
      ++bufLen;
  }

  bufLen = strLen + bufLen * 2;
  str[bufLen] = '\0';

  int strLast = strLen - 1;

  for (int bufLast = bufLen - 1; (bufLast >= 0) && (strLast >= 0); --bufLast, --strLast)
  {
    if (str[strLast] == ' ')
    {
      str[bufLast--] = '0';
      str[bufLast--] = '2';
      str[bufLast] = '%';
    }
    else
    {
      str[bufLast] = str[strLast];
    }
  }
}



//******************************************************************************
// 1.4.Напишите функцию, которая проверяет, является ли заданная строка переста-
// новкой палиндрома. (Палиндром - слово или фраза, одинаково читающиеся в пря-
// мом и обратном направлении; перестановка - строка, содержащая те же символы в
// другом порядке.) Палиндром не ограничивается словами из словаря.
// Пример:
// Ввод: Tact Соа
// Вывод : True(перестановки : "taco cat ", " atco cta ", и т.д .)
//******************************************************************************

bool isMixPalindrom(const std::string& str)
{
  std::bitset<UCHAR_MAX> indicator;

  for (const auto& ch : str)
  {
    if (' ' == ch)
      continue;

    auto lowCh = std::tolower(ch);
    indicator.flip(lowCh);
  }

  return indicator.count() <= 1;
}



//******************************************************************************
// 1.5. Существуют три вида модифицирующих операций со строками : вставка сим-
// вола, удаление символа и замена символа. Напишите функцию, которая проверяет,
// находятся ли две строки на расстоянии одной модификации(или нуля модификаций).
// Пример :
// pale, ple -> true
// pales, pale -> true
// pale, bale-> true
// pale, bake -> false
//******************************************************************************

bool OnlyModification(const std::string& first, const std::string& second)
{
  auto fl = first.length();
  auto sl = second.length();

  auto minMax = std::minmax(fl, sl);
  auto dl = minMax.second - minMax.first;

  if (dl > 1)
    return false;

  bool once{ false };

  for (std::size_t fc{}, sc{}; (fc < fl) && (sc < sl); ++fc, ++sc)
  {
    if (first[fc] == second[sc])
      continue;

    if (once)
      return false;

    once = true;

    if (fl > sl)
    {
      ++fc;
    }
    else if (sl > fl)
    {
      ++sc;
    }
  }

  return true;
}



//******************************************************************************
// 1.6. Реализуйте метод для выполнения простейшего сжатия строк с использованием
// счетчика повторяющихся символов. Например, строка aabcccccaaa превращается
// в а2b1с5а3. Если сжатая строка не становится короче исходной, то метод
// возвращает исходную строку.Предполагается, что строка состоит только из букв
// верхнего и нижнего регистра(a - z).
//******************************************************************************

bool ZipString(std::string& str)
{
  if (str.length() <= 2)
    return false;

  std::string zipped;
  zipped.reserve(str.length() - 1);

  zipped = str.front();
  std::size_t counter{ 1 };

  for (std::size_t i{ 1 }; i < str.length(); ++i)
  {
    if (str[i] == zipped.back())
    {
      ++counter;
      continue;
    }

    zipped += std::to_string(counter);

    if (zipped.length() >= (str.length() - 2))
      return false;

    zipped += str[i];
    counter = 1;
  }

  zipped += std::to_string(counter);

  if (zipped.length() >= str.length())
    return false;

  str = std::move(zipped);
  return true;
}



//******************************************************************************
// 1.7. Имеется изображение, представленное матрицей NxN; каждый пиксел представ-
// лен 4 байтами. Напишите метод для поворота изображения на 90 градусов.
// У дастся ли вам выполнить эту операцию «на месте» ?
//******************************************************************************

constexpr std::size_t MATRIX_SIZE = 9;
constexpr std::size_t NUM_ROWS{ 8 };
constexpr std::size_t NUM_COLS{ 10 };


void PrintMatrix(uint32_t matrix[][NUM_COLS], std::size_t nRows, std::size_t nCols)
{
  for (std::size_t i{}; i < nRows; ++i)
  {
    for (std::size_t j{}; j < nCols; ++j)
    {
      std::cout << "\t" << matrix[i][j];
    }

    std::cout << std::endl;
  }
}


void RotateMatrix(uint32_t matrix[][MATRIX_SIZE], std::size_t size)
{
  for (std::size_t layer{}; layer < (size / 2); ++layer)
  {
    std::size_t first = layer;
    std::size_t last = size - 1 - layer;

    for (std::size_t i{ first }; i < last; ++i)
    {
      std::size_t offset = i - first;

      // Буфер <- Левый верхний
      uint32_t tl = matrix[first][i];

      // Левый верхний <- левый нижний
      matrix[first][i] = matrix[last - offset][first];

      // Левый нижний <- правй нижний
      matrix[last - offset][first] = matrix[last][last - offset];

      // Правый нижний <- правый верхний
      matrix[last][last - offset] = matrix[i][last];

      // Правый верхний <- буфер
      matrix[i][last] = tl;
    }
  }
}



//******************************************************************************
// 1.8. Напишите алгоритм, реализующий следующее условие: если элемент матрицы
// MxN равен 0, то весь столбец и вся строка обнуляются.
//******************************************************************************

void ClearRowCol(uint32_t matrix[][NUM_COLS], std::size_t nRows, std::size_t nCols)
{
  auto ClearRow = [&](std::size_t row)
    {
      for (std::size_t i{}; i < nCols; ++i)
        matrix[row][i] = 0;
    };

  auto ClearCol = [&](std::size_t col)
    {
      for (std::size_t i{}; i < nRows; ++i)
        matrix[i][col] = 0;
    };

  bool rowHasZero{ false };
  bool colHasZero{ false };

  for (std::size_t i{}; i < nRows; ++i)
  {
    if (0 == matrix[i][0])
    {
      rowHasZero = true;
      break;
    }
  }

  for (std::size_t i{}; i < nCols; ++i)
  {
    if (0 == matrix[0][i])
    {
      colHasZero = true;
      break;
    }
  }

  for (std::size_t i{ 1 }; i < nRows; ++i)
  {
    for (std::size_t j{ 1 }; j < nCols; ++j)
    {
      if (0 == matrix[i][j])
      {
        matrix[0][j] = 0;
        matrix[i][0] = 0;
      }
    }
  }

  for (std::size_t i{ 1 }; i < nRows; ++i)
  {
    if (0 == matrix[i][0])
      ClearRow(i);
  }

  for (std::size_t i{ 1 }; i < nCols; ++i)
  {
    if (0 == matrix[0][i])
      ClearCol(i);
  }

  if (rowHasZero)
    ClearRow(0);

  if (colHasZero)
    ClearCol(0);
};



//******************************************************************************
// 1.9. Допустим, что существует метод isSubstring, проверяющий, является ли
// одно слово подстрокой другого. Для двух строк s1 и s2 напишите код, который
// проверяет, получена ли строка s2 циклическим сдвигом s1, используя только
// один вызов метода isSubstring (пример: слово waterbottle получено циклическим
// сдвигом erbottlewat).
//******************************************************************************

bool isSubstring(const std::string& source, const std::string& str)
{
  auto pos = source.find(str);
  return (pos != std::string::npos);
}

bool IsShiftedString(const std::string& s1, const std::string& s2)
{
  if ((s1.length() != s2.length()) || s1.empty())
    return false;

  return isSubstring(s1 + s1, s2);
}


int main()
{
  std::string s1 = "waterbottle";
  std::string s2 = "erbottlewat";

  std::cout << "S1: \"" << s1 << "\"" << std::endl;
  std::cout << "S2: \"" << s2 << "\"" << std::endl;

  std::cout << std::endl;

  std::cout << "S2 ";
  std::cout << (IsShiftedString(s1, s2) ? "is" : "is not") << " shifted string of S1" << std::endl;

  std::cout << std::endl;
}
