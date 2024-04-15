#pragma once
#include "document.h"
#include "paginator.h"


#include <set>
#include <string>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& text);

template <typename StringContainer>
set<string> MakeUniqueNonEmptyStrings(const StringContainer& strings);

template <typename Iterator>
ostream& operator<<(ostream& out, const IteratorRange<Iterator>& range);

ostream& operator<<(ostream& out, const Document& document);

template <typename StringContainer>
set<string> MakeUniqueNonEmptyStrings(const StringContainer& strings) {
    set<string> non_empty_strings;
    for (const string& str : strings) {
        if (!str.empty()) {
            non_empty_strings.insert(str);
        }
    }
    return non_empty_strings;
}

template <typename Iterator>
ostream& operator<<(ostream& out, const IteratorRange<Iterator>& range) {
    for (Iterator it = range.begin(); it != range.end(); ++it) {
        out << *it;
    }
    return out;
}



