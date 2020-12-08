#pragma once

#include <algorithm>
#include <cassert>
#include <cstring>

template <typename T>
class Range {
public:
  constexpr Range() : begin_{nullptr}, end_{nullptr} {}
  constexpr Range(const T* begin, const T* end) : begin_{begin}, end_{end} {}

  [[nodiscard]] const T* begin() const {
    return begin_;
  }

  [[nodiscard]] const T* end() const {
    return end_;
  }

  [[nodiscard]] constexpr MemSize length() const {
    return end_ - begin_;
  }

  [[nodiscard]] constexpr bool empty() const {
    return end_ - begin_ == 0;
  }

  Range middle(MemSize offset) {
    assert(begin_ + offset <= end_);
    return {begin_ + offset, end_};
  }

  Range middle(MemSize offset, MemSize length) {
    assert(begin_ + offset <= end_);
    assert(begin_ + offset + length <= end_);
    return {begin_ + offset, begin_ + offset + length};
  }

private:
  const T* begin_;
  const T* end_;
};

inline Range<char> range_from(const char* text) {
  return {text, text + std::strlen(text)};
}

template <typename T>
Range<T> front(const Range<T>& range, MemSize count) {
  assert(range.begin() + count <= range.end());
  return {range.begin(), range.begin() + count};
}

template <typename T, typename Predicate>
Range<T> front_until(const Range<T>& range, Predicate&& predicate) {
  auto begin = range.begin();
  return {begin, std::find_if(begin, range.end(), std::forward<Predicate>(predicate))};
}

template <typename T, typename Predicate>
Range<T> front_until_not(const Range<T>& range, Predicate&& predicate) {
  auto begin = range.begin();
  return {begin, std::find_if_not(begin, range.end(), std::forward<Predicate>(predicate))};
}

template <typename T>
Range<T> advance(const Range<T>& range, MemSize count) {
  assert(range.begin() + count <= range.end());
  return {range.begin() + count, range.end()};
}

template <typename T, typename Predicate>
Range<T> advance_until(const Range<T>& range, Predicate&& predicate) {
  auto end = range.end();
  return {std::find_if(range.begin(), end, predicate), end};
}

template <typename T, typename Predicate>
Range<T> advance_until_not(const Range<T>& range, Predicate&& predicate) {
  auto end = range.end();
  return {std::find_if_not(range.begin(), end, predicate), end};
}
