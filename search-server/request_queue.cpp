#include "request_queue.h"
#include "document.h"

 RequestQueue::RequestQueue(const SearchServer & search_server)
    : search_server_(search_server) {}

 vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentStatus status) {
     UpdateTime();
     auto documents = search_server_.FindTopDocuments(raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
         return document_status == status;
         });
     UpdateRequests(documents);
     return documents;
 }

 vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
     UpdateTime();
     auto documents = search_server_.FindTopDocuments(raw_query, DocumentStatus::ACTUAL);
     UpdateRequests(documents);
     return documents;
 }
 
 int RequestQueue::GetNoResultRequests() const {
     return no_result_count_;
 }


 void RequestQueue::UpdateTime() {
     ++current_time_;
 }

 void RequestQueue::UpdateRequests(const vector<Document>& found_documents) {
     QueryResult result;
     result.day_time = current_time_;
     result.found_documents = found_documents;
     requests_.push_back(result);
     if (found_documents.empty()) {
         no_result_count_++;
     }

     while (!requests_.empty() && current_time_ - requests_.front().day_time > min_in_day_) {
         if (requests_.front().found_documents.empty()) {
             --no_result_count_;
         }
         --no_result_count_;
         requests_.pop_front();
     }


 }