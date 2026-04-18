#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class CircVector {
 private:
  T* data;
  size_t vec_size;
  size_t capacity;
  size_t front_idx;

  void resize(size_t newCapacity) {
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < vec_size; i++) {
      newData[i] = data[wrapping(i)];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
    front_idx = 0;
  }
  size_t wrapping(size_t index) {
    return (front_idx + index) % capacity;
  }

  // TODO_STUDENT: add private helper functions, such as resize
  // You may also find a "wrapping" function helpful.

 public:
  /**
   * Default constructor. Creates an empty `CircVector` with capacity 10.
   */
  CircVector() : CircVector(10) {
  }

  /**
   * Creates an empty `CircVector` with given capacity. Capacity must exceed 0.
   */
  CircVector(size_t capacity) {
    this->capacity = capacity;
    this->vec_size = 0;
    this->front_idx = 0;
    data = new T[capacity];
  }

  /**
   * Returns whether the `CircVector` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    if (vec_size == 0) {
      return true;
    }
    return false;
  }

  /**
   * Returns the number of elements in the `CircVector`.
   */
  size_t size() const {
    return vec_size;
  }

  /**
   * Adds the given `T` to the front of the `CircVector`.
   */
  void push_front(T elem) {
    if (vec_size == capacity) {
      resize(capacity * 2);
    }
    front_idx = (front_idx + capacity - 1) % capacity;
    data[front_idx] = elem;
    vec_size++;
  }

  /**
   * Adds the given `T` to the back of the `CircVector`.
   */
  void push_back(T elem) {
    if (vec_size == capacity) {
      resize(capacity * 2);
    }
    size_t theBack = (front_idx + vec_size) % capacity;
    data[theBack] = elem;
    vec_size++;
  }

  /**
   * Removes the element at the front of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (vec_size == 0) {
      throw runtime_error(
          "Can't remove any element if there is no element at the front\n");
    }
    T value = data[front_idx];
    front_idx = (front_idx + 1) % capacity;
    vec_size--;
    return value;
  }

  /**
   * Removes the element at the back of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (vec_size == 0) {
      throw runtime_error(
          "Can't remove any element if there is no element at the front\n");
    }
    size_t theBack = (front_idx + vec_size - 1) % capacity;
    T value = data[theBack];
    vec_size--;
    return value;
  }

  /**
   * Removes all elements from the `CircVector`.
   */
  void clear() {
    front_idx = 0;
    vec_size = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~CircVector() {
    delete[] data;
  }

  /**
   * Returns the element at the given index in the `CircVector`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T& at(size_t index) const {
    if (index >= vec_size) {
      throw out_of_range("element at that index is out of range of the list");
    }
    return data[(front_idx + index) % capacity];
  }

  /**
   * Copy constructor. Creates a deep copy of the given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector(const CircVector& other)
      : data(new T[other.capacity]),
        vec_size(other.vec_size),
        capacity(other.capacity),
        front_idx(0) {
    for (size_t i = 0; i < vec_size; i++) {
      data[i] = other.data[(other.front_idx + i) % other.capacity];
    }
  }

  /**
   * Assignment operator. Sets the current `CircVector` to a deep copy of the
   * given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector& operator=(const CircVector& other) {
    if (this == &other) {
      return *this;
    }
    T* newData = new T[other.capacity];
    for (size_t i = 0; i < other.vec_size; i++) {
      newData[i] = other.data[(other.front_idx + i) % other.capacity];
    }

    delete[] data;
    data = newData;
    capacity = other.capacity;
    vec_size = other.vec_size;
    front_idx = 0;
    return *this;
  }

  /**
   * Converts the `CircVector` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    ostringstream output;
    output << "[";
    for (size_t i = 0; i < vec_size; i++) {
      output << at(i);
      if (i + 1 < vec_size) output << ", ";
    }
    output << "]";
    return output.str();
  }

  /**
   * Searches the `CircVector` for the first matching element, and returns its
   * index in the `CircVector`. If no match is found, returns "-1".
   */
  size_t find(const T& target) {
    for (size_t i = 0; i < vec_size; i++) {
      if (at(i) == target) {
        return i;
      }
    }
    return -1;
  }

  /**
   * Removes the last occurrence of the given `value` from the `CircVector`.
   *
   * For example, if a list was `[0, 1, 2, 1, 0, 1, 8]`, then a call to
   * `remove_last(1)` should change the list to be [0, 1, 2, 1, 0, 8]`.
   *
   * If the given value is not found on the `CircVector`, throws an
   * `invalid_argument` exception.
   */
  void remove_last(const T& value) {
    size_t lastValue = -1;
    if (vec_size == 0) {
      throw invalid_argument("value is not found on the circvector");
    }
    for (size_t i = 0; i < vec_size; i++) {
      if (at(i) == value) {
        lastValue = i;
      }
    }
    if (lastValue == -1) {
      throw invalid_argument("value is not found on the circvector");
    }
    for (size_t i = lastValue; i + 1 < vec_size; i++) {
      at(i) = at(i + 1);
    }
    vec_size--;
  }

  /**
   * Inserts the given `T` as a new element in the `CircVector` before
   * the element currently stored in the given index. If the index is not
   * a current valid index in the list, throws `out_of_range`.
   */
  void insert_before(size_t index, T elem) {
    if (index >= vec_size) {
      throw out_of_range("index is out of range");
    }
    if (vec_size == capacity) {
      resize(capacity * 2);
    }
    for (size_t i = vec_size; i > index; --i) {
      data[wrapping(i)] = data[wrapping(i - 1)];
    }
    data[wrapping(index)] = elem;
    vec_size++;
  }

  /**
   * Remove every other element (alternating) from the
   * `CircVector`, starting at index 1. Must run in O(N). May not reallocate.
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    if (vec_size <= 1) {
      return;
    }
    size_t nextElementt = 1;
    for (size_t currentElement = 2; currentElement < vec_size;
         currentElement += 2) {
      data[wrapping(nextElementt)] = data[wrapping(currentElement)];
      nextElementt++;
    }
    vec_size = nextElementt;
  }

  /**
   * Returns a pointer to the underlying memory managed by the `CircVec`.
   * For autograder testing purposes only.
   */
  T* get_data() const {
    return this->data;
  }

  /**
   * Returns the capacity of the underlying memory managed by the `CircVec`. For
   * autograder testing purposes only.
   */
  size_t get_capacity() const {
    return this->capacity;
  }
};
