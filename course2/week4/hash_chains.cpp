#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::list;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<list<string> > elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

    list<string>::iterator search_list(list<string> &chain, const string query) {
        for (list<string>::iterator itr = chain.begin(); itr != chain.end(); itr++)
            if ((*itr).compare(query) == 0)
               return itr; 
        return chain.end();
    }
public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {elems.resize(bucket_count);}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            list<string> &chain = elems[query.ind];
            // use reverse order, because we append strings to the end
            for (list<string>::iterator itr = chain.begin(); itr != chain.end(); itr++)
                std::cout << *itr << " ";
            std::cout << "\n";
        } else {
            if (query.type == "find") {
                list<string> &chain = elems[hash_func(query.s)];
                writeSearchResult(search_list(chain, query.s) != chain.end());
            } else if (query.type == "add") {
                list<string> &chain = elems[hash_func(query.s)];
                if (search_list(chain, query.s) == chain.end())
                    chain.push_front(query.s); 
            } else if (query.type == "del") {
                list<string> &chain = elems[hash_func(query.s)];
                list<string>::iterator itr = search_list(chain, query.s);
                if (itr != chain.end())
                    chain.erase(itr); 
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
