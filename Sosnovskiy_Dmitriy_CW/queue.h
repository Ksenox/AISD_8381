template<class T>
class Queue
{
public:
    class Node
    {
    public:
        Node(T data = T(), Node* next = nullptr) :data(data), next(next) {}
        T data;
        Node* next;
    };
    void enqueue(T current) { // adding to the queue
        if (head != nullptr) {
            this->tail->next = new Node(current);
            this->tail = this->tail->next;
        }
        else {
            this->head = new Node(current);
            this->tail = head;
        }
        this->Counter++;
    }
    T dequeue() {// Remove from queue. Returns the deleted item
        if (head != nullptr) {
            Node* current = head;
            T cur = head->data;
            head = head->next;
            delete current;
            this->Counter--;
            return cur;
        }
    }

    bool checkNotNull()
    {
        Node* tmp = head;
        while(tmp != nullptr)
        {
            if(tmp->data != nullptr) return true;
            tmp = tmp->next;
        }
        return false;
    }


    T peek() { //returns an item from the beginning of the queue
        if (head != nullptr) {
            return head->data;
        }
    }
    int get_size() { // returns the number of items in the queue
        return Counter;
    }
    Queue(Node* head = nullptr, Node* tail = nullptr, int Counter = 0) :head(head), tail(tail), Counter(Counter) {}

    ~Queue() {
        while (head != nullptr) {
            Node* cur = head->next;
            delete head;
            head = cur;
        }
    }
private:
    Node* head;
    Node* tail;
    int Counter;
};
