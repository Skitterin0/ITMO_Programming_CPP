#ifndef LAB5_ALLOCATOR_H
#define LAB5_ALLOCATOR_H

#include <cstddef>
#include <cassert>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include "linkedlist.h"
#include "util.h"

class allocator {
private:
    struct freeHeader {
        size_t blockSize;
    };
    struct allocHeader {
        size_t blockSize;
        char padding;
    };

    typedef linkedlist<freeHeader>::node node;

    void* mStartPtr_ = nullptr;
    linkedlist<freeHeader> mFreeList_;
    size_t mSize_;
    size_t mUsed_;
    size_t mPeak_;

public:
    allocator(const size_t size) : mSize_(size), mUsed_(0), mPeak_(0) {}

    ~allocator() {
        mSize_ = 0;
        if (mStartPtr_ != nullptr) {
            free(mStartPtr_);
            mStartPtr_ = nullptr;
        }
    }

    void* allocate(const size_t size, const size_t alignment = 8) {
        const size_t allocHeaderSize = sizeof(allocHeader);
        const size_t freeHeaderSize = sizeof(freeHeader);
        assert("Allocation size must be bigger" && size >= sizeof(node));
        assert("Alignment must be 8 at least" && alignment >= 8);

        size_t padding;
        node *currNode, *prevNode;
        find(size, alignment, padding, prevNode, currNode);
        assert(currNode != nullptr && "Out of allocated memory");

        const size_t alignPadding = padding - allocHeaderSize;
        const size_t reqSize = size + padding;

        const size_t rest = currNode->data.blockSize - reqSize;

        if (rest > 0) {
            node* newFreeNode = (node*)(currNode + reqSize);
            newFreeNode->data.blockSize = rest;
            mFreeList_.insert(currNode, newFreeNode);
        }
        mFreeList_.remove(prevNode, currNode);

        const size_t headerAddress = (size_t)currNode + alignPadding;
        const size_t dataAddress = headerAddress + allocHeaderSize;
        ((allocHeader*) headerAddress)->blockSize = reqSize;
        ((allocHeader*) headerAddress)->padding = alignPadding;

        mUsed_ += reqSize;
        mPeak_ = std::max(mPeak_, mUsed_);

        return (void*) dataAddress;
    }

    void free(size_t size) {
        const auto headerAddress = (size_t) mStartPtr_;
        node* curr = (node*) headerAddress;

        while (curr->data.blockSize != size) {
            curr = curr->next;
        }

        free(curr);
    }

    void free(void* ptr) {
        const auto currAddress = (size_t) ptr;
        const size_t headerAddress = currAddress - sizeof(allocHeader);
        const allocHeader* headerAlloc = (allocHeader*) headerAddress;

        node* freeNode = (node*) headerAddress;
        freeNode->data.blockSize = headerAlloc->blockSize + headerAlloc->padding;
        freeNode->next = nullptr;

        node* it = mFreeList_.head_;
        node* itPrev = nullptr;
        while (it != nullptr) {
            if (ptr < it) {
                mFreeList_.insert(itPrev, freeNode);
                break;
            }
            itPrev = it;
            it = it->next;
        }

        mUsed_ -= freeNode->data.blockSize;
        coalescence(itPrev, freeNode);
    }

    void init() {
        if (mStartPtr_ != nullptr) {
            free(mStartPtr_);
            mStartPtr_ = nullptr;
        }

        mStartPtr_ = malloc(mSize_);

        reset();
    }

    void reset() {
        mUsed_ = 0;
        mPeak_ = 0;
        node* firstNode = (node*) mStartPtr_;
        firstNode->data.blockSize = mSize_;
        firstNode->next = nullptr;
        mFreeList_.head_ = nullptr;
        mFreeList_.insert(nullptr, firstNode);
    }

private:
    allocator(allocator& other) = default;

    void coalescence(node* prevNode, node* freeNode) {
        if (freeNode->next != nullptr && (size_t)freeNode + freeNode->data.blockSize == (size_t)freeNode->next) {
            freeNode->data.blockSize += freeNode->next->data.blockSize;
            mFreeList_.remove(freeNode, freeNode->next);
        }

        if (prevNode != nullptr && (size_t)prevNode + prevNode->data.blockSize == (size_t) freeNode) {
            prevNode->data.blockSize += freeNode->data.blockSize;
            mFreeList_.remove(prevNode, freeNode);
        }
    }

    void find(const size_t size, const size_t alignment, size_t& padding, node*& prevNode, node*& foundNode) {
        node* it = mFreeList_.head_, *itPrev = nullptr;

        while (it != nullptr) {
            padding = util::paddingWHeader((size_t) it, alignment, sizeof(allocHeader));
            const size_t reqSpace = size + padding;
            if (it->data.blockSize >= reqSpace) {
                break;
            }

            itPrev = it;
            it = it->next;
        }

        prevNode = itPrev;
        foundNode = it;
    }
};

#endif