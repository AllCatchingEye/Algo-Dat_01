#ifndef LINKEDLIST_LIST_H
#define LINKEDLIST_LIST_H

#include <functional>
#include <iostream>
#include <string>
#include <tuple>

template <typename K, typename V>
class list {
 private:
  struct element {
    const K key;
    V value;
    element *next;

    element(const std::tuple<K, V>, element *);
  };

  element *head = nullptr;

  element* quicksort(element*, std::function<bool(K, K)> lessThan);

 public:
  ~list();

  const V *search(const K) const;

  bool isEmpty() const;

  bool isSorted(std::function<bool(K, K)> lessThan) const;

  std::tuple<K, V> popHead();

  void sort(std::function<bool(K, K)> lessThan);

  list<K, V> &operator+=(const std::tuple<K, V>);

  list<K, V> &operator-=(const K);

  void printTo(std::ostream &ostr) const;
};

template <typename K, typename V>
list<K, V>::~list() {
  auto elem = head;

  while (elem != nullptr) {
    auto next = elem->next;
    delete elem;
    elem = next;
  }
}

template <typename K, typename V>
const V* list<K, V>::search(const K key) const {
  auto elem = head;

  while (elem != nullptr) {
    if (elem->key == key) {
      return &elem->value;
    }

    elem = elem->next;
  }

  return nullptr;
}

template <typename K, typename V>
bool list<K, V>::isEmpty() const {
  return this->head == nullptr;
}

template <typename K, typename V>
bool list<K, V>::isSorted(std::function<bool(K, K)> lessThan) const {
  auto first = head;

  while (first != nullptr) {
    auto second = first->next;

    if (second != nullptr && lessThan(second->key, first->key)) {
      return false;
    }

    first = second;
  }

  return true;
}

template <typename K, typename V>
std::tuple<K, V> list<K, V>::popHead() {
  if (isEmpty()) {
    throw "List was empty!";
  }

  auto key = head->key;
  auto value = head->value;
  auto next = head->next;

  delete head;
  head = next;

  return std::make_tuple(key, value);
}

template <typename K, typename V>
void list<K, V>::sort(std::function<bool(K, K)> lessThan) {
  if (head == nullptr) {
    return;
  }

  head = quicksort(head, lessThan);
}

template <typename K, typename V>
typename list<K, V>::element* list<K, V>::quicksort(list::element *first, std::function<bool(K, K)> lessThan) {
  if (first == nullptr || first->next == nullptr) {
    return first;
  }

  element *pivot = first;

  element* previous = first;
  element* current = first->next;

  // becomes new head
  element *lower = pivot;

  do {
    if (lessThan(current->key, pivot->key)) {
      element *next = current->next;

      current->next = lower;
      lower = current;

      previous->next = next;
      current = next;
    } else {
      previous = current;
      current = current->next;
    }
  } while(current != nullptr);

  element *upper = pivot->next;
  pivot->next = nullptr;

  lower = quicksort(lower, lessThan);
  upper = quicksort(upper, lessThan);

  pivot->next = upper;
  return lower;
}

template <typename K, typename V>
list<K, V>& list<K, V>::operator+=(const std::tuple<K, V> tuple) {
  if (isEmpty()) {
    head = new element(tuple, nullptr);
    return *this;
  }

  auto elem = head;

  while (true) {
    if (elem->key == std::get<0>(tuple)) {
      elem->value = std::get<1>(tuple);
      return *this;
    } else if (elem->next == nullptr) {
      elem->next = new element(tuple, nullptr);
      return *this;
    }

    elem = elem->next;
  }
}


template <typename K, typename V>
list<K, V>& list<K, V>::operator-=(const K key) {
  if (isEmpty()) {
    return *this;
  }

  if (head->key == key) {
    auto next = head->next;
    delete head;
    head = next;

    return *this;
  }

  auto elem = head;

  do {
    if (elem->next != nullptr && elem->next->key == key) {
      auto next = elem->next->next;
      delete elem->next;
      elem->next = next;

      return *this;
    }

    elem = elem->next;
  } while (elem != nullptr);

  return *this;
}

template <typename K, typename V>
void list<K, V>::printTo(std::ostream& ostr) const {
  auto elem = head;

  while (elem != nullptr) {
    ostr << elem->key << '.' << elem->value << std::endl;

    elem = elem->next;
  }
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &ostr, const list<K, V> &list) {
  list.printTo(ostr);
  return ostr;
}

template <typename K, typename V>
list<K, V>::element::element(const std::tuple<K, V> tuple, list::element *elem) : key(std::get<0>(tuple)) {
  value = std::get<1>(tuple);
  next = elem;
}

#endif  // LINKEDLIST_LIST_H
