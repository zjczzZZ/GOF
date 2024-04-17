#pragma once

#include <atomic>
#include <vector>
/*
    read1 read2
    read_index_
    write1 write2
    write_index_
    read write
*/
template <typename T, size_t N = 1024>
class LockFreeQueue {
public:
    struct Element {
        std::atomic<bool> full_;
        T data_;
    };

    LockFreeQueue() : _data(N) {
        _readIndex = 0;
        _writeIndex = 0;
    }

    // write_index_ == read_index_ + data_.size()
    bool Enqueue(T value) {
        size_t write_index = 0;
        Element* e = NULL;
        do {
            write_index = _writeIndex.load(std::memory_order_relaxed);
            if (write_index >= _readIndex.load(std::memory_order_relaxed) + _data.size()) {
                return false;
            }
            size_t index = write_index % _data.size();
            e = &_data[index];
            if (e->full_.load(std::memory_order_relaxed)) {
                return false;
            }
        } while (!_writeIndex.compare_exchange_weak(write_index, write_index + 1, std::memory_order_release, std::memory_order_relaxed));

        e->data_ = std::move(value);
        e->full_.store(true, std::memory_order_release);
        return true;
    }

    bool Dequeue(T& value) {
        size_t read_index = 0;
        Element* e = NULL;
        do {
            read_index = _readIndex.load(std::memory_order_relaxed);
            if (read_index >= _writeIndex.load(std::memory_order_relaxed)) {
                return false;
            }
            size_t index = read_index % _data.size();
            e = &_data[index];
            if (!e->full_.load(std::memory_order_relaxed)) {
                return false;
            }
        } while (!_readIndex.compare_exchange_weak(read_index, read_index + 1, std::memory_order_release, std::memory_order_relaxed));
        value = std::move(e->data_);
        e->full_.store(false, std::memory_order_release);
        return true;
    }

private:
    std::vector<Element> _data;
    std::atomic<size_t> _readIndex;
    std::atomic<size_t> _writeIndex;
};