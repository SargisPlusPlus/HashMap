#include "HashMap.hpp"
#include "PrintHash.hpp"

unsigned int default_hash_function(const std::string& s)
{
    int hash = 0;

    for (int i = 0; i < s.length(); i++)
    {
        hash = hash + s[i];
    }

    return hash;
}

HashMap::HashMap()
:cap(INITIAL_BUCKET_COUNT), sz(0)
{
    SomeHashFunction = default_hash_function;
    HashTable = new Node * [INITIAL_BUCKET_COUNT];
    for(unsigned int i = 0; i < INITIAL_BUCKET_COUNT; i++)
    {
        HashTable[i] = nullptr;
    }

}

HashMap::HashMap(HashFunction hashFunction)
: SomeHashFunction(hashFunction)
{
    HashTable = new Node*[INITIAL_BUCKET_COUNT];
    sz = 0;
    cap = INITIAL_BUCKET_COUNT;

    for (int i = 0; i < INITIAL_BUCKET_COUNT; i++)
    {
        HashTable[i]= nullptr;
    }
}

HashMap::~HashMap()
{
    for (unsigned int i = 0; i < cap; ++i)
    {
        Node* curr = HashTable[i];
        Node* next;
        while (curr != nullptr)
        {
            next = curr->next;
            delete curr;
            curr = next;
        }
     }
     delete[] HashTable;
}

void HashMap::add(const std::string& key, const std::string& value)
{
    //GET INDEX
    unsigned int capacity = HashMap::bucketCount();
    int index = default_hash_function(key);
    index = index % capacity;
    

    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;
    newNode->next = nullptr;

    Node*& n = HashTable[index];
    newNode->next = n;
    n = newNode;

        sz++; //INCREMENT SIZE
        double loadF = HashMap::loadFactor();
        //IF LOAD FACTOR > 0.8, CREATE A BIGGER TABLE
    if( loadF > 0.8 )
    HashMap::reHash();
    
}

HashMap::HashMap(const HashMap& hm)
: sz(hm.sz), cap(hm.cap)
{
    HashTable = new Node*[cap];
    for (unsigned int i = 0; i < hm.cap; ++i)
        HashTable[i] = nullptr;
    for (unsigned int i = 0; i < hm.sz; ++i)
        add(hm.HashTable[i]->key, hm.HashTable[i]->value);
}

void HashMap::remove(const std::string& key)
{
    unsigned int capacity = HashMap::bucketCount();
    int index = SomeHashFunction(key);
    index = index % capacity;

    if (sz <= 0)
        return;
    if (contains(key))
    {
        Node*& head = HashTable[index];
        if (head->key.compare(key) == 0)
        {
            Node* next = head->next;
            delete head;
            head = next;
        }
        else
        {
            Node* n = head;
            while(n->next != nullptr)
            {
                if (n->next->key.compare(key) == 0)
                {
                    Node* next = nullptr;
                    if (n->next->next != nullptr)
                        next = n->next->next;
                    delete n->next;
                    n->next = next;
                    break;
                }
                n=n->next;
            }
        }
        sz--;
    }
}

std::string HashMap::value(const std::string& key) const
{
    unsigned int capacity = HashMap::bucketCount();
    unsigned int index = default_hash_function(key);
    index = index % capacity;

    bool foundKey = false;
    std::string val = "";
    //GET BUCKET
    Node* Ptr = HashTable[index];
    while (Ptr != nullptr)
    {
        //KEEP LOOKING FOR THE KEY'S VALUE
        if(Ptr->key == key)
        {
            foundKey = true;
            val = Ptr->value;
        }
        Ptr = Ptr->next;
    }

    if (foundKey == true)
    {
        return val;
    }
    else
        return val;
}

HashMap& HashMap::operator=(const HashMap& hm)
{
    if (this != &hm) 
    {
        for (size_t i = 0; i < cap; ++i)
        {
             Node* curr = HashTable[i];
             Node* next;
             while ( curr != nullptr)
             {
                next = curr->next;
                delete curr;
                curr = next;
             }
        }
        delete[] HashTable;
        
        sz = hm.sz;
        cap = hm.cap;
        HashTable = new Node*[cap];
        
        for (unsigned int i = 0; i < cap; i++)
        {
            HashTable[i] = nullptr;
        }
        for (unsigned int i = 0; i < hm.sz; ++i)
            add(hm.HashTable[i]->key, hm.HashTable[i]->value);
    }

    return *this;
}

bool HashMap::contains(const std::string& key) const
{
    unsigned int capacity = HashMap::bucketCount();
    unsigned int index = default_hash_function(key);
    index = index % capacity;


    const Node* Ptr = HashTable[index];

    while (Ptr != nullptr)
    {
        if(Ptr->key == key)
            return true;
        Ptr = Ptr->next;
    }

    return false;
}

double HashMap::loadFactor() const
{
    double factor = 0.0;

    unsigned int size = HashMap::size();
    unsigned int capacity = HashMap::bucketCount();

    factor = (double)size / (double)capacity;

    return factor;
}

unsigned int HashMap::maxBucketSize() const
{
    unsigned int largestSoFar = 0;
    unsigned int capacity = HashMap::bucketCount();

    for (int i = 0; i < capacity; i++)
    {
    int counter = 0;
    Node* Ptr = HashTable[i];

    while(Ptr != nullptr)
    {
    counter++;
    Ptr = Ptr->next;
    }
    if(counter > largestSoFar)
    largestSoFar = counter;
    }

    return largestSoFar;
}

void HashMap::clear()
{

    unsigned int capacity = HashMap::bucketCount();

    for (unsigned int i = 0; i < capacity; i++)
    {
        while (HashTable[i] != nullptr)
        {
            Node* temp = HashTable[i];
            HashTable[i] = temp->next;
            delete temp;
        }
     }   
   
    sz=0; // reset size
}

void HashMap::reHash()
{
    int OldCapacity = cap;
    cap = cap * 2 + 1; //set new capacity
    
    Node** newHashTable = new Node*[cap]();

    for (unsigned int i = 0; i <OldCapacity; i++)
    {
        Node* n = HashTable[i];
        while (n != nullptr)
        {
            Node *tmp = n;
            n=n->next;

            Node*& bucket = newHashTable[default_hash_function(tmp->key) % cap];
            tmp->next = bucket;
            bucket = tmp;
         }
     }
    

    delete [] HashTable;
    HashTable = newHashTable;
}

unsigned int HashMap::size() const
{
    return sz;
}

unsigned int HashMap::bucketCount() const
{
    return cap;
}
