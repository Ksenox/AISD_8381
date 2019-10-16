#ifndef BINARY_ROCK_H
#define BINARY_ROCK_H
#include <string>

struct BinRock;
struct Plum{
    bool isPlum;
    union{
      int weight;
      BinRock *child;
    } uni;
};

struct Side{
    int lenght;
    Plum *plum;

};
struct BinRock {
    Side *right;
    Side *left;
};


class binary_rock
{
private:

public:
    binary_rock();
    int Weight(BinRock *);
    bool Balanced(BinRock *);
    void parseString (std::string, Side&);
    void push(Side &);
};

#endif // BINARY_ROCK_H
