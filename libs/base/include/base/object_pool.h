#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <utility>

namespace base {

template <typename T>
class ObjectPool {
public:
#if 0
  class Object {
  public:
    ~Object() {
      release();
    }

    void release() {
      object_pool_->release(ptr_);
      object_pool_ = nullptr;
      ptr_ = nullptr;
    }

    T* operator->() {
      assert(ptr_);
      return ptr_;
    }

    T* ptr() {
      return ptr_;
    }

  private:
    friend class ObjectPool<T>;

    Object(ObjectPool* object_pool, T* ptr) : object_pool_{object_pool}, ptr_{ptr} {}

    ObjectPool* object_pool_;
    T* ptr_;
  };
#endif

  ObjectPool() = default;

  template <typename... Args>
  T* emplace(Args&&... args) {
    T* storage = find_block_with_open_space();
    assert(storage);

    new (storage) T{std::forward<Args>(args)...};

    return storage;
  }

  void release(T* object) {
    auto success = find_block_containing(object);
    assert(success);
  }

private:
  struct Block {
    T object[64];
    uint64_t used;
    U8 open_count;
    Block* next;

    uint8_t find(T* p) {
      for (uint8_t i = 0; i < 64; ++i) {
        if (&object[i] == p) {
          return i;
        }
      }

      return 0xFF;
    }
  };

  T* find_block_with_open_space() {
    if (!first_block_) {
      first_block_ = allocate_block();
    }

    Block* last = nullptr;
    for (Block* current = first_block_; current; current = current->next) {
      auto* p = find_open_space(current);
      if (p != nullptr) {
        return p;
      }
      last = current;
    }

    Block* new_block = allocate_block();
    last->next = new_block;

    return find_open_space(new_block);
  }

  bool find_block_containing(T* ptr) {
    for (Block* current = first_block_; current; current = current->next) {
      auto pos = current->find(ptr);
      printf("pos: %d\n", pos);
      if (pos != 0xFF) {
        set_unused(&current->used, pos);
        return true;
      }
    }

    return false;
  }

  Block* allocate_block() {
    auto* block = static_cast<Block*>(std::malloc(sizeof(Block)));

    block->used = 0;
    block->open_count = 64;
    block->next = nullptr;

    return block;
  }

  bool is_used(uint64_t used, uint8_t position) {
    assert(position < 64);
    return (used & (1llu << position)) != 0;
  }

  void set_used(uint64_t* used, uint8_t position) {
    *used |= (1llu << position);
  }

  void set_unused(uint64_t* used, uint8_t position) {
    *used &= ~(1llu << position);
  }

  T* find_open_space(Block* block) {
    for (uint8_t i = 0; i < 64; ++i) {
      if (!is_used(block->used, i)) {
        set_used(&block->used, i);
        return &block->object[i];
      }
    }

    return nullptr;
  }

  Block* first_block_ = nullptr;
};

}  // namespace base
