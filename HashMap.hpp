

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <functional>
#include <string>



class HashMap
{
public:

    typedef std::function<unsigned int(const std::string&)> HashFunction;

    // This constant specifies the number of buckets that a HashMap will
    // have when it is initially constructed.
    static const unsigned int INITIAL_BUCKET_COUNT = 10;


public:

    HashMap();

    HashMap(HashFunction hashFunction);

    HashMap(const HashMap& hm);
    ~HashMap();
    HashMap& operator=(const HashMap& hm);

    void add(const std::string& key, const std::string& value);

    void remove(const std::string& key);

    bool contains(const std::string& key) const;


    std::string value(const std::string& key) const;

    // size() returns the number of key/value pairs stored in this HashMap.
    unsigned int size() const;

    // bucketCount() returns the number of buckets currently allocated in
    // this HashMap.
    unsigned int bucketCount() const;

    // loadFactor() returns the proportion of the number of key/value pairs
    // to the number of buckets, a measurement of how "full" the HashMap is.
    // For example, if there are 20 key/value pairs and 50 buckets, we would
    // say that the load factor is 20/50 = 0.4.
    double loadFactor() const;

    // maxBucketSize() returns the number of key/value pairs stored in this
    // HashMap's largest bucket.
    unsigned int maxBucketSize() const;
    
    void clear();
    
private:
    // This structure describes the nodes that make up the linked lists in
    // each of this HashMap's buckets.
    struct Node
    {
        std::string key;
        std::string value;
        Node* next;
    };


    // You will no doubt need to add at least a few more private members
    
    void reHash();
//    void arrayCopy(Node *Target[], Node *Source[], unsigned int sz);
    HashFunction SomeHashFunction;
    Node **HashTable;
    unsigned int cap;
    unsigned int sz;
};

unsigned int default_hash_function(const std::string& s);

#endif // HASHMAP_HPP
