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

  struct PartitionData {
    element *firstLeft;
    element *lastLeft;
    element *firstRight;
    element *lastRight;
  };

  PartitionData quicksort(element*, element*, std::function<bool(K, K)> lessThan);
  PartitionData partition(element*, element*, std::function<bool(K, K)> lessThan);

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

  auto end = head;

  while (end->next != nullptr) {
    end = end->next;
  }

  auto partitionData = quicksort(head, end, lessThan);

  head = partitionData.firstLeft;
}

template <typename K, typename V>
typename list<K, V>::PartitionData list<K, V>::quicksort(list::element *first, list::element *last, std::function<bool(K, K)> lessThan) {
  if (first == nullptr || first == last) {
    PartitionData partitionData;
    partitionData.firstLeft = first;
    partitionData.lastLeft = first;
    partitionData.firstRight = last;
    partitionData.lastRight = last;

    return partitionData;
  }

  auto partitionData = partition(first, last, lessThan);

  auto left = quicksort(partitionData.firstLeft, partitionData.lastLeft, lessThan);
  auto right = quicksort(partitionData.firstRight, partitionData.lastRight, lessThan);

  left.lastRight->next = right.firstLeft;

  partitionData.firstLeft = left.firstLeft;
  partitionData.lastLeft = nullptr;
  partitionData.firstRight = nullptr;
  partitionData.lastRight = right.lastRight;

  return partitionData;
}


template <typename K, typename V>
typename list<K, V>::PartitionData list<K, V>::partition(list::element *first, list::element *last, std::function<bool(K, K)> lessThan) {
  auto pivot = last;
  auto newLast = pivot;

  element *prev = nullptr;
  auto current = first;
  auto newFirst = first;

  while (current != pivot) {
    if (lessThan(current->key, pivot->key)) {
      prev = current;
      current = current->next;
    } else {
      auto next = current->next;

      if (prev != nullptr) {
        prev->next = next;
      } else {
        newFirst = next;
      }

      current->next = nullptr;

      newLast->next = current;
      newLast = current;

      current = next;
    }
  }

  PartitionData partitionData;

  partitionData.firstLeft = newFirst;
  partitionData.lastLeft = prev == nullptr ? newFirst : prev;
  partitionData.firstRight = pivot == newLast ? newLast : pivot->next;
  partitionData.lastRight = newLast;

  return partitionData;
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
