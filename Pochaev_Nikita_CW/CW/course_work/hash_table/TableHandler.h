#ifndef TEST_H
#define TEST_H

#include "allheaders.h"
#include "HashTable.h"

class TableHandler : public QObject {
    Q_OBJECT

public:
    static void makeHashTable(std::vector<std::string>, lrstruct::HashTable<std::string>*&);
    static void makeHashTableDump(const lrstruct::HashTable<std::string>*);
    static void separateNames(std::string&);
    static std::string connectNames(std::string);

    inline static bool stepLoopSwitcher;
    static void loopLatency();
public slots:
    static void disableLoop();
private:
    static std::vector<std::string> convertStrToWords(std::string str);
};

#endif // TEST_H
