#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node* next;

    Node(T data) {
      this->data = data;
      this->next = nullptr;
    }

    Node(T data, Node* next) {
      this->data = data;
      this->next = next;
    }
  };

  size_t list_size;
  Node* list_front;

 public:
  /**
   * Default constructor. Creates an empty `LinkedList`.
   */
  LinkedList() : list_size(0), list_front(nullptr) {
    // Completed
  }
  /**
   * Returns whether the `LinkedList` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return list_size == 0;
    // Completed
  }

  /**
   * Returns the number of elements in the `LinkedList`.
   */
  size_t size() const {
    return list_size;
    // compeleted
  }

  /**
   * Adds the given `T` to the front of the `LinkedList`.
   */
  void push_front(T data) {
    if (list_size == 0) {
      list_front = new Node(data);
    } else {
      Node* newNode = new Node(data);
      Node* tempNode = list_front;
      newNode->next = tempNode;
      list_front = newNode;
    }
    list_size++;
    // completed
  }

  /**
   * Adds the given `T` to the back of the `LinkedList`.
   */
  void push_back(T data) {
    if (list_front == nullptr) {
      list_front = new Node(data);
      list_size = 1;
      return;
    }
    Node* currentNode = list_front;
    while (currentNode->next != nullptr) {
      currentNode = currentNode->next;
    }
    currentNode->next = new Node(data);
    list_size++;
    // Completed
  }

  /**
   * Removes the element at the front of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (list_size == 0) {
      throw runtime_error(
          "Can't remove any element if there is no element at the front\n");
    }
    Node* currentNode = list_front;
    T Value = currentNode->data;
    list_front = currentNode->next;
    delete (currentNode);
    list_size--;
    return Value;
  }

  /**
   * Removes the element at the back of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (list_size == 0) {
      throw runtime_error(
          "Can't remove any element if there is no element at the back\n");
    }
    if (list_size == 1) {
      T Value = list_front->data;
      delete (list_front);
      list_front = nullptr;
      list_size = 0;
      return Value;
    }
    Node* pervousNode = list_front;
    while (pervousNode->next->next != nullptr) {
      pervousNode = pervousNode->next;
    }
    Node* nextNode = pervousNode->next;
    T Value = nextNode->data;
    pervousNode->next = nullptr;
    delete (nextNode);
    list_size--;
    return Value;
  }

  /**
   * Empties the `LinkedList`, releasing all allocated memory, and resetting
   * member variables appropriately.
   */
  void clear() {
    while (list_front != nullptr) {
      Node* currentNode = list_front;
      list_front = list_front->next;
      delete currentNode;
    }
    list_size = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~LinkedList() {
    clear();
  }

  /**
   * Returns the element at the given index in the `LinkedList`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T& at(size_t index) const {
    if (index >= list_size) {
      throw out_of_range("element at that index is out of range of the list");
    }
    Node* currentNode = list_front;
    for (size_t i = 0; i < index; i++) {
      currentNode = currentNode->next;
    }
    return currentNode->data;
  }
  /**
   * Copy constructor. Creates a deep copy of the given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList(const LinkedList& other) {
    list_front = nullptr;
    list_size = 0;
    if (other.list_front == nullptr) {
      return;
    }
    Node* curr = other.list_front;
    list_front = new Node(curr->data);
    Node* tail = list_front;
    curr = curr->next;
    while (curr != nullptr) {
      tail->next = new Node(curr->data);
      curr = curr->next;
      tail = tail->next;
    }
    list_size = other.list_size;
  }

  /**
   * Assignment operator. Sets the current `LinkedList` to a deep copy of the
   * given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList& operator=(const LinkedList& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    if (other.list_front == nullptr) {
      return *this;
    }
    Node* curr = other.list_front;
    list_front = new Node(curr->data);
    Node* tail = list_front;
    curr = curr->next;
    while (curr != nullptr) {
      tail->next = new Node(curr->data);
      curr = curr->next;
      tail = tail->next;
    }
    list_size = other.list_size;
    return *this;
  }

  /**
   * Converts the `LinkedList` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    ostringstream output;
    output << "[";
    Node* curr = list_front;
    while (curr != nullptr) {
      output << curr->data;
      if (curr->next != nullptr) {
        output << ", ";
      }
      curr = curr->next;
    }
    output << "]";
    return output.str();
  }

  /**
   * Searches the `LinkedList` for the first matching element, and returns its
   * index. If no match is found, returns "-1".
   */
  size_t find(const T& data) {
    Node* curr = list_front;
    size_t index = 0;
    while (curr != nullptr) {
      if (curr->data == data) {
        return index;
      }
      curr = curr->next;
      index++;
    }
    return -1;
  }

  /**
   * Removes the last occurrence of the given value from the `LinkedList`.
   *
   * For example, if a list was `[0, 1, 2, 1, 0, 1, 8]`, then a call to
   * `remove_last(1)` should change the list to be [0, 1, 2, 1, 0, 8]`.
   *
   * If the given value is not found on the `LinkedList`, throws an
   * `invalid_argument` exception.
   */
  void remove_last(const T& value) {
    Node* lastMatched = nullptr;
    Node* prevousNode = nullptr;
    Node* currNode = list_front;
    Node* lastPrevousNode = nullptr;
    while (currNode != nullptr) {
      if (currNode->data == value) {
        lastMatched = currNode;
        lastPrevousNode = prevousNode;
      }
      prevousNode = currNode;
      currNode = currNode->next;
    }
    if (lastMatched == nullptr) {
      throw invalid_argument("value is not found on the linkedlist");
    }

    if (lastPrevousNode == nullptr) {
      list_front = lastMatched->next;
    } else {
      lastPrevousNode->next = lastMatched->next;
    }

    delete lastMatched;
    list_size--;
  }
  /**
   * Inserts the given `T` as a new element in the `LinkedList` before
   * the element currently stored in the given index. If the index is not
   * a current valid index in the list, throws `out_of_range`.
   */
  void insert_before(size_t index, T elem) {
    if (index >= list_size) {
      throw out_of_range("index is out of range");
    }
    if (index == 0) {
      Node* newNode = new Node(elem, list_front);
      list_front = newNode;
      list_size++;
      return;
    }
    Node* prevousNode = list_front;
    for (size_t i = 0; i < index - 1; i++) {
      prevousNode = prevousNode->next;
    }
    Node* newNode = new Node(elem, prevousNode->next);
    prevousNode->next = newNode;
    list_size++;
  }

  /**
   * Remove every other element (alternating) from the
   * `LinkedList`, starting at index 1. Must run in O(N).
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    if (list_size <= 1) {
      return;
    }
    Node* currentNode = list_front;
    while (currentNode != nullptr && currentNode->next != nullptr) {
      Node* oldNode = currentNode->next;
      currentNode->next = oldNode->next;
      delete oldNode;
      list_size--;
      currentNode = currentNode->next;
    }
  }

  /**
   * Returns a pointer to the node at the front of the `LinkedList`. For
   * autograder testing purposes only.
   */
  void* front() const {
    return this->list_front;
  }
};
