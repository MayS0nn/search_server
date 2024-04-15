#pragma once


#include <algorithm>
#include <vector>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : first_(begin)
        , last_(end)
        , size_(distance(first_, last_)) {
    }

    Iterator begin() const {
        return first_;
    }

    Iterator end() const {
        return last_;
    }

    size_t size() const {
        return size_;
    }

private:
    Iterator first_, last_;
    size_t size_;
};



template <typename Iterator>
class Paginator {
public:
    using PaginatorIterator = typename vector<IteratorRange<Iterator>>::const_iterator;
    Paginator(Iterator begin, Iterator end, size_t page_size)
        : page_size_(page_size) {

        while (begin != end) {
            const size_t current_page_size = min(page_size_, static_cast<size_t>(distance(begin, end)));
            const Iterator page_end = next(begin, current_page_size);
            pages_.emplace_back(begin, page_end);
            begin = page_end;
        }
    }
    PaginatorIterator begin() const {
        return pages_.begin();
    }

    PaginatorIterator end() const {
        return pages_.end();
    }

    size_t size() const {
        return pages_.size();
    }

private:
    size_t page_size_;
    vector<IteratorRange<Iterator>> pages_;

};

template <typename Container>
auto Paginate(Container& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}