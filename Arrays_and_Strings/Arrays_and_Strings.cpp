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
// 1.1 ���������� ��������, ������������, ��� �� ������� � ������ �����������
// ������ ���� ���.� ���� ��� ���� ��������� ������������� ��������������
// �������� ������?
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
// 1.2. ��� ���� ����� �������� �����, ������������, �������� �� ���� ������
// ������������� ������.
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
// 1.3. �������� �����, ���������� ��� ������� � ������ ��������� '%20'. ������
// �������, ��� ����� ������ ��������� ��������� �������������� �������,
// � ����������� ����� ������ �������� �������. (����������: ��� ����������
// ������ �� java ��� ���������� �������� "�� �����" ����������� ����������
// ������.)
// ������:
// ����: "Mr John Smith    ", 13
// ����� : "Mr%20John%20Smith"
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
// 1.4.�������� �������, ������� ���������, �������� �� �������� ������ �������-
// ������ ����������. (��������� - ����� ��� �����, ��������� ���������� � ���-
// ��� � �������� �����������; ������������ - ������, ���������� �� �� ������� �
// ������ �������.) ��������� �� �������������� ������� �� �������.
// ������:
// ����: Tact ���
// ����� : True(������������ : "taco cat ", " atco cta ", � �.� .)
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
// 1.5. ���������� ��� ���� �������������� �������� �� �������� : ������� ���-
// ����, �������� ������� � ������ �������. �������� �������, ������� ���������,
// ��������� �� ��� ������ �� ���������� ����� �����������(��� ���� �����������).
// ������ :
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
// 1.6. ���������� ����� ��� ���������� ����������� ������ ����� � ��������������
// �������� ������������� ��������. ��������, ������ aabcccccaaa ������������
// � �2b1�5�3. ���� ������ ������ �� ���������� ������ ��������, �� �����
// ���������� �������� ������.��������������, ��� ������ ������� ������ �� ����
// �������� � ������� ��������(a - z).
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
// 1.7. ������� �����������, �������������� �������� NxN; ������ ������ ��������-
// ��� 4 �������. �������� ����� ��� �������� ����������� �� 90 ��������.
// � ������ �� ��� ��������� ��� �������� ��� ����� ?
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

      // ����� <- ����� �������
      uint32_t tl = matrix[first][i];

      // ����� ������� <- ����� ������
      matrix[first][i] = matrix[last - offset][first];

      // ����� ������ <- ����� ������
      matrix[last - offset][first] = matrix[last][last - offset];

      // ������ ������ <- ������ �������
      matrix[last][last - offset] = matrix[i][last];

      // ������ ������� <- �����
      matrix[i][last] = tl;
    }
  }
}



//******************************************************************************
// 1.8. �������� ��������, ����������� ��������� �������: ���� ������� �������
// MxN ����� 0, �� ���� ������� � ��� ������ ����������.
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
// 1.9. ��������, ��� ���������� ����� isSubstring, �����������, �������� ��
// ���� ����� ���������� �������. ��� ���� ����� s1 � s2 �������� ���, �������
// ���������, �������� �� ������ s2 ����������� ������� s1, ��������� ������
// ���� ����� ������ isSubstring (������: ����� waterbottle �������� �����������
// ������� erbottlewat).
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
