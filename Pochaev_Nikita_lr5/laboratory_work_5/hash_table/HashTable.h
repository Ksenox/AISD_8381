#ifndef HASHTEBLE_H
#define HASHTEBLE_H

#include "allheaders.h"
#include "customvector.h"

#define DEBUG 0
#define FILE_LOG 1

namespace lrstruct {
    template <typename Key, size_t N = 7/* implementation-defined */>
    class HashTable {

    public:
        /* ----- CONTAINER FIELDS ----- */
        class Iterator;

        // using is to call variable from class namespace without ::
        using value_type = Key;

        // 	key_type - the first template parameter (Key)
        //  In other words, it's just alias name
        using key_type = Key;

        // declares a named variable as a reference,
        // that is, an alias to an already-existing key
        using reference = key_type&;

        // is the same as const Ty&
        using const_reference = const key_type&;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;
        using iterator = Iterator;
        using const_iterator = Iterator;
        // works for anything that supports a less-than comparison
        using key_compare = std::less<key_type>;   // B+-Tree
        // HASHING
        using key_equal = std::equal_to<key_type>;
        /**
         * Returns a value of type std::size_t that represents
         * the hash value of the parameter.
         */
        using hasher = std::hash<key_type>;

    private:
        /**
         * @brief The Node struct
         * for B+-Tree.
         */
        struct Node {
            Key data;
            Node *next = nullptr;
            Node *head = nullptr;
            ~Node() {
                delete head;
                delete next;
            }
        };
        Node *table = nullptr;
        size_type maxSize{N};
        size_type cSize{0};            // current Hash Table size

        /**
         * @brief insert_unchecked
         * Insert an ellement without checking for collision
         * (for copy constructor mostly)
         * @param k
         */
        void insert_unchecked(const_reference k) {
            Node *help = new Node;
            auto position = hash_idx(k);

            help->next = table[position].head;
            help->data = k;

            table[position].head = help;
            ++cSize;

            if (maxSize * 10 < cSize) rehash();
        }

        /**
         * @brief hash_idx
         * @param k
         * @return
         * load factor of current hash table
         */
        size_type hash_idx(const key_type& k) const {
            return hasher{}(k) % maxSize;
        }

        /**
         * @brief rehash
         * The size of the array is increased (doubled) and all the values
         * are hashed again and stored in the new double sized array
         * to maintain a low load factor and low complexity
         */
        void rehash() {
            lrstruct::Vector<Key> dataBuff;
            dataBuff.reserve(cSize);

            for (const auto &k : *this)
                dataBuff.push_back(k);

            delete[] table;
            maxSize *= 2;
            cSize = 0;

            table = new Node[maxSize];
            /*
             * FIXME: for test with more then 71 element
             * it falls. Why??
            for (const auto &fromBuff : dataBuff)
                insert_unchecked(fromBuff);
            */
            for (int i = 0; i < static_cast<int>(dataBuff.size()); i++) {
                insert_unchecked(dataBuff[i]);
            }
            if(DEBUG) qDebug() << "table rehashed!" << endl;
            if(FILE_LOG) {
                std::fstream fs;
                fs.open (LOG_FILE_WAY, std::fstream::in | std::fstream::out | std::fstream::app);
                fs << "\nTable rehashed!\n";
                fs << "New max size of hash is: " << maxSize << ", current size is: " << cSize << "\n\n";
                fs.close();
            }
        }

    public:

        /* ----- CONSTRUCTORS ----- */

        HashTable() : table(new Node[N]) {
            if(DEBUG) qDebug() << "DEFAULT_CONSTRUCTOR" << endl;
            if(FILE_LOG) {
                std::fstream fs;
                fs.open (LOG_FILE_WAY, std::fstream::in | std::fstream::out | std::fstream::app);
                fs << "DEFAULT_CONSTRUCTOR\n";
                fs.close();
            }
        }

        HashTable(std::initializer_list<key_type> ilist) : HashTable() {
            insert(ilist);
        }

        /**
         * Recursion call as foreach work
         */
        template<typename InputIt> HashTable(InputIt first, InputIt last) : table(new Node[N]){
            insert(first, last);
            if(DEBUG) qDebug() << "RANGE_CONSTRUCTOR" << endl;
            if(FILE_LOG) {
                std::fstream fs;
                fs.open (LOG_FILE_WAY, std::fstream::in | std::fstream::out | std::fstream::app);
                fs << "RANGE_CONSTRUCTOR\n";
                fs.close();
            }
        }

        HashTable(const HashTable &other) : table(new Node[N]) {
            for (const auto &key : other)
                insert_unchecked(key);
            if(DEBUG) qDebug() << "COPY_CONSTRUCTOR" << endl;
            if(FILE_LOG) {
                std::fstream fs;
                fs.open (LOG_FILE_WAY, std::fstream::in | std::fstream::out | std::fstream::app);
                fs << "COPY_CONSTRUCTOR\n";
                fs.close();
            }
        }

        ~HashTable() {
            delete[] table;
        }

        /* ----- METHODS ----- */

        size_type size() const {
            return cSize;
        }

        bool empty() const {
            if (cSize == 0)
                return true;
            return false;
        }

        size_type count(const key_type &key) const {
            const auto row = hash_idx(key);                                             // hash the key to find apropriate row
            for (Node *node = table[row].head; node != nullptr; node = node->next)
                if (key_equal{}(node->data, key)) {
                    return 1;
                }
            return 0;                                                                   // return 0 if key not found
        }

        iterator find(const key_type& key) const {
            const auto row = hash_idx(key);
            for (Node* n = table[row].head; n != nullptr; n = n->next)
                if (key_equal{}(n->data, key)) {
                    return const_iterator{ this, n, row, maxSize };
                }
            return end();
        }

        bool findOrInsert(const key_type& key) const {
            const auto row = hash_idx(key);
            for (Node* n = table[row].head; n != nullptr; n = n->next)
                if (key_equal{}(n->data, key)) {
                    return true;
                }
            return false;
        }

        void swap(HashTable& other){
            std::swap(maxSize, other.maxSize);
            std::swap(table, other.table);
            std::swap(cSize, other.cSize);
        }

        void insert(std::initializer_list<key_type> ilist) {
            for (auto const &element : ilist)                                         // iterate through the list
                if (!count(element))
                    insert_unchecked(element);                                        // if element(key) already exists in table then skip
        }

        std::pair<iterator,bool> insert(const_reference key) {
            if (!count(key)) {
                insert_unchecked(key);
                return std::make_pair(find(key), true);
            }
            return std::make_pair(find(key), false);
        }

        template<typename InputIt> void insert(InputIt first, InputIt last) {
            for (auto it = first; it != last; ++it)
                insert(*it);
        }

        void clear() {
            delete[] table;
            cSize = 0;
            maxSize = N;
            table = new Node[maxSize];
        }

        size_type erase (const key_type& key) {
            if (count(key)) {
                auto idx = hash_idx(key);

                Node *current = table[idx].head;
                Node *previous = nullptr;

                for ( ; current != nullptr; current = current->next) {
                    if (key_equal{}(current->data, key)) {
                    if (current == table[idx].head) {
                            table[idx].head = current->next;
                            current->next = nullptr;
                            delete current;

                            --cSize;
                            return 1;
                        }
                        if (previous) {
                            previous->next = current->next;
                            current->next = nullptr;
                            delete current;

                            previous = nullptr;
                            delete previous;

                            --cSize;
                            return 1;
                        }
                    }
                    previous = current;
                }
            }
            return 0;
        }

        /* -------- ITERATORS --------*/

        const_iterator begin() const {
            for (size_t i = 0; i < maxSize; i++)
                if (table[i].head) {
                    return const_iterator(this, table[i].head, i, maxSize);
                }
            return end();
        }

        const_iterator end() const {
            return const_iterator(nullptr);
        }

        void dump(std::ostream& o = std::cerr) const {
            for (size_type i{0}; i < maxSize; ++i) {
                if (table[i].head == nullptr) {
                    o << "[" << i << "]" << ": nullptr" << '\n';
                    continue;
                }
                o << "[" << i << "]" << ": ";
                for (Node* a = table[i].head; a != nullptr; a = a->next) {
                    o << a->data;
                    if (a->next != nullptr)
                    o << " -> ";
                }
                o << '\n';
            }
        }

        HashTable& operator = (const HashTable& other) {
            clear();

            for (const auto &key : other)
            insert(key);

            return *this;
        }

        HashTable& operator = (std::initializer_list<key_type> ilist) {
            clear();
            insert(ilist);

            return *this;
        }

        friend bool operator == (const HashTable& lhs, const HashTable& rhs) {
            if (lhs.cSize != rhs.cSize)
                return false;

            for (const auto &key : lhs) {
                if (!rhs.count(key)) {
                    return false;
                }
            }

            return true;
        }


        friend bool operator != (const HashTable& lhs, const HashTable& rhs) {
            return !(lhs == rhs);
        }
    };

    /* -------- HASH TABLE ITERATORS --------*/

    template <typename Key, size_t N>
    class HashTable<Key,N>::Iterator {
        private:
        const HashTable<Key, N> *ptr;
            Node *to;
            size_type itPos;
            size_type tblSz;

        public:
            using value_type = Key;
            using difference_type = std::ptrdiff_t;
            using reference = const value_type&;
            using pointer = const value_type*;
            using iterator_category = std::forward_iterator_tag;

        explicit Iterator(const HashTable *ads = nullptr, Node *tbl = nullptr,
                                        size_type idx = 0, size_type sz = 0)
                                            : ptr(ads), to(tbl), itPos(idx), tblSz(sz){
            if(DEBUG) qDebug() << "ITERATOR_CONSTRUCTOR" << endl;
        }

        reference operator*() const {
            return to->data;
        }

        Iterator& operator++() {
            while (itPos < tblSz) {
                if (to->next) {
                    to = to->next; return *this;
                }
                else ++itPos;

                if (itPos == tblSz) {
                    to = nullptr; return *this;
                }

                auto transit = ptr->table[itPos].head;
                if (transit) {
                    to = transit;
                    return *this;
                }
            }
            return *this;
        }

        Iterator operator ++ (int) {
            Iterator tmp(*this);
            operator++();

            return tmp;
        }

        friend bool operator == (const Iterator& lhs, const Iterator& rhs) {
            return lhs.to == rhs.to;
        }

        friend bool operator != (const Iterator& lhs, const Iterator& rhs) {
            return !(lhs.to == rhs.to);
        }
    };

    template <typename Key, size_t N> void swap(HashTable<Key,N>& lhs, HashTable<Key,N>& rhs) {
        lhs.swap(rhs);
    }
}

#endif // HASHTEBLE_H
