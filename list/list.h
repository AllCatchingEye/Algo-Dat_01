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
const V *list<K, V>::search(const K) const {
  // TODO
  return nullptr;
}

template <typename K, typename V>
bool list<K, V>::isEmpty() const {
  return this->head == nullptr;
}

template <typename K, typename V>
bool list<K, V>::isSorted(std::function<bool(K, K)> lessThan) const {
  // TODO
  lessThan(head->key, head->key);
  return false;
}

template <typename K, typename V>
std::tuple<K, V> list<K, V>::popHead() {
  // TODO
  return std::tuple<K, V>();
}

template <typename K, typename V>
void list<K, V>::sort(std::function<bool(K, K)> lessThan) {
  // TODO
  lessThan(head->key, head->key);
}

template <typename K, typename V>
list<K, V> &list<K, V>::operator+=(const std::tuple<K, V>) {
  // TODO
  return *this;
}

template <typename K, typename V>
list<K, V> &list<K, V>::operator-=(const K) {
  // TODO
  return *this;
}

template <typename K, typename V>
void list<K, V>::printTo(std::ostream &ostr) const {
  // TODO
}

template <typename K, typename V>
list<K, V>::element::element(const std::tuple<K, V>, list::element *) {
  // TODO
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &ostr, const list<K, V> &list) {
  list.printTo(ostr);
  return ostr;
}

#endif  // LINKEDLIST_LIST_H
