#include <iostream>
#include <memory>
#include <list>
#include <forward_list>
#include <set>


template<typename T>
class SinglyLinkedList
{
private:
  struct Node
  {
    std::shared_ptr<Node> m_next;
    T m_data;

    Node(const T& data)
      : m_data{ data }
    {}

    Node(T&& data) noexcept
      : m_data{ std::move(data) }
    {}
  };

  std::shared_ptr<Node> m_head;

  void PushFront(std::shared_ptr<Node> newNode) noexcept
  {
    if (m_head)
      newNode->m_next = m_head;

    m_head = newNode;
  }

public:
  bool Empty() const
  {
    return static_cast<bool>(m_head);
  }

  void PushFront(const T& data)
  {
    auto newNode = std::make_shared<Node>(data);
    PushFront(newNode);
  }

  void PushFront(T&& data) noexcept
  {
    auto newNode = std::make_shared<Node>(std::move(data));
    PushFront(newNode);
  }

  T& Front()
  {
    return m_head->m_data;
  }
};



template<typename T>
void Print(const T& list)
{
  for (const auto& item : list)
  {
    std::cout << " " << item;
  }
}



//******************************************************************************
// 2.1. Напишите код для удаления дубликатов из несортированного связного списка.
// Дополнительно
// Как вы будете решать задачу, если использовать временный буфер запрещено?
//******************************************************************************

template<typename T>
void Unique_buf(std::list<T>& list)
{
  std::set<T> uniqBuf;

  for (auto cit = list.cbegin(); cit != list.cend();)
  {
    auto ret = uniqBuf.emplace(*cit);

    if (ret.second)
    {
      ++cit;
    }
    else
    {
      cit = list.erase(cit);
    }
  }
}


template<typename T>
void Unique(std::list<T>& list)
{
  for (auto cit = list.cbegin(); cit != list.cend(); ++cit)
  {
    for (auto findCIT = std::next(cit); findCIT != list.cend();)
    {
      if (*cit == *findCIT)
      {
        findCIT = list.erase(findCIT);
      }
      else
      {
        findCIT++;
      }
    }
  }
}



//******************************************************************************
// 2.2. Реализуйте алгоритм для нахождения в односвязном списке k-го элемента
// с конца.
//******************************************************************************

template<typename T>
T* FindK(std::forward_list<T>& fl, std::size_t k)
{
  if (k <= 0)
    return nullptr;

  auto itSlow = fl.before_begin();
  auto itFast = fl.before_begin();

  for (int i{}; i < k; ++i)
  {
    if (fl.end() == itFast)
      return nullptr;

    itFast = std::next(itFast);
  }

  while (itFast != fl.end())
  {
    itSlow = std::next(itSlow);
    itFast = std::next(itFast);
  }

  return &(*itSlow);
}



//******************************************************************************
// 2.3. Реализуйте алгоритм, удаляющий узел из середины односвязного списка(то
// есть узла, не являющегося ни начальным, ни конечным - не обязательно находящегося
// точно в середине). Доступ предоставляется только к этому узлу.
// Пример:
// Ввод: узел с из списка a -> b -> c -> d -> e -> f
// Вывод: ничего не возвращается, но новый список имеет вид : a -> b -> d -> e -> f
//******************************************************************************

template<typename T>
bool DeleteMiddle(std::forward_list<T>& fl)
{
  if (fl.empty())
    return false;

  auto del = fl.cbefore_begin();
  auto runner = fl.cbegin();

  runner = std::next(runner);
  if (fl.cend() == runner)
    return false;

  runner = std::next(runner);
  if (fl.cend() == runner)
    return false;

  std::size_t counter{ 2 };

  while (runner != fl.cend())
  {
    if (0 == (counter % 2))
      del = std::next(del);

    runner = std::next(runner);
    ++counter;
  }

  fl.erase_after(del);
  return true;
}



//******************************************************************************
// 2.4. Напишите код для разбиения связного списка вокруг значения х, так чтобы
// все узлы, меньшие х, предшествовали узлам, большим или равным х. Если х
// содержится в списке, то значения х должны следовать строго после элементов,
// меньших х (см.далее). Элемент разбивки х может находиться где угодно
// в "правой части"; он не обязан располагаться между левой и правой частью.
// Пример:
// Ввод: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [значение разбивки = 5]
// Вывод: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
//******************************************************************************

template<typename T>
void DevideList(std::list<T>& list, T& pivotVal)
{
  std::list<T> lessVal;

  for (auto cit = list.cbegin(); cit != list.cend();)
  {
    if (*cit >= pivotVal)
    {
      cit = std::next(cit);
      continue;
    }

    auto copy = cit;
    cit = std::next(cit);
    lessVal.splice(lessVal.cend(), list, copy);
  }

  list.splice(list.begin(), lessVal);
}



//******************************************************************************
// 2.5. Два числа хранятся в виде связных списков, в которых каждый узел представ-
// ляет один разряд. Все цифры хранятся в обратном порядке, при этом младший
// разряд (единицы) хранится в начале списка. Напишите функцию, которая суммирует
// два числа и возвращает результат в виде связного списка.
// Пример:
// Ввод: (7 -> 1 -> 6) + (5 -> 9 -> 2), то есть 617 + 295.
// Вывод : 2 -> 1 -> 9, то есть 912.
// Дополнительно
// Решите задачу, предполагая, что цифры записаны в прямом порядке.
// Ввод: (6 -> 1 -> 7) + (2 -> 9 -> 5), то есть 617 + 295.
// Вывод : 9 -> 1 -> 2, то есть 912.
//******************************************************************************

template<typename T>
bool Add(T& dest, const T& val, bool c)
{
  auto s = dest + val;

  if (c)
    ++s;

  if (s >= 10)
  {
    dest = s % 10;
    return true;
  }

  dest = s;
  return false;
}


template<typename T>
std::list<T> Addition(const std::list<T>& add_1, const std::list<T>& add_2, bool direct)
{
  std::list<T> result;
  const std::list<T>* pAdd{ nullptr };

  if (add_1.size() >= add_2.size())
  {
    result = add_1;
    pAdd = &add_2;
  }
  else
  {
    result = add_2;
    pAdd = &add_1;
  }

  auto it_r = result.begin();
  auto cit = pAdd->cbegin();
  bool c{ false };

  while (c || (cit != pAdd->cend()))
  {
    T val{};

    if (cit != pAdd->cend())
    {
      val = *cit;
      cit = std::next(cit);
    }

    c = Add(*it_r, val, c);
    it_r = std::next(it_r);

    if (c && (it_r == result.end()))
    {
      result.emplace_back();
      it_r = std::prev(result.end());
    }
  }

  return result;
}



//******************************************************************************
// 2.6. Реализуйте функцию, проверяющую, является ли связный список палиндромом.
//******************************************************************************

template<typename T>
bool IsPalindrom(const std::list<T>& list)
{
  auto forwardCit = list.cbegin();
  auto backwardCit = list.crbegin();

  for (auto counter = list.size() / 2; counter > 0; --counter)
  {
    if (*forwardCit != *backwardCit)
      return false;
  }

  return true;
}



int main()
{
  std::list<int> list_1 = { 1, 2, 3 };
  std::cout << "Source list 1: ";
  Print(list_1);
  std::cout << std::endl;

  std::list<int> list_2 = { 4, 5, 6, 2 };
  std::cout << "Source list 2: ";
  Print(list_2);
  std::cout << std::endl;

  return 0;
}
