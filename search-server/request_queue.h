#pragma once

#include "search_server.h"
#include <deque>
#include <string>
#include <vector>

using namespace std;

class RequestQueue {
public:
	RequestQueue(const SearchServer& search_server);

	template <typename DocumentPredicate>
	vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate);

	vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status);

	vector<Document> AddFindRequest(const string& raw_query);

	int GetNoResultRequests() const;
private:

	struct QueryResult {
		int day_time = 0;
		vector<Document> found_documents;
	};

	void UpdateTime();

	void UpdateRequests(const vector<Document>& found_documents);

	const SearchServer& search_server_;
	deque<QueryResult> requests_;
	const static int min_in_day_ = 1440;
	int current_time_ = 0;
	int no_result_count_ = 0;
};

template <typename DocumentPredicate>
vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
	UpdateTime();
	auto documents = search_server_.FindTopDocuments(raw_query, document_predicate);
	UpdateRequests(documents);
	return documents;
}
