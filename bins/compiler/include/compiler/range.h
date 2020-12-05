#pragma once

#include <algorithm>
#include <cassert>
#include <cstring>

template <typename T>
class Range {
public:
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

  [[nodiscard]] Range front(MemSize count) const {
    assert(count <= length());
    return {begin_, begin_ + count};
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

template <typename T, typename Predicate>
Range<T> find_if(const Range<T>& range, Predicate&& predicate) {
  auto begin = range.begin();
  return {begin, std::find_if(begin, range.end(), std::forward<Predicate>(predicate))};
}

template <typename T, typename Predicate>
Range<T> find_if_not(const Range<T>& range, Predicate&& predicate) {
  auto begin = range.begin();
  return {begin, std::find_if_not(begin, range.end(), std::forward<Predicate>(predicate))};
}

inline Range<char> range_from(const char* text) {
  return {text, text + std::strlen(text)};
}
