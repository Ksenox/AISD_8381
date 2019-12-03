#include "allheaders.h"
#include "customvector.h"
#include "HashTable.h"
#include "test.h"

lrstruct::Vector<std::string> convertStrToWords(std::string str) {

    // Used to split string around spaces.
    std::istringstream ss(str);

    lrstruct::Vector<std::string> res;

    // Traverse through all words
    do {
        // Read a word
        std::string word;
        ss >> word;
        res.push_back(word);
    } while (ss);   // While there is more to read

    return res;
}

void Test::makeHashTable(lrstruct::Vector<std::string> inpStrs, lrstruct::HashTable<std::string> &workTable) {
    /*
     * FIXME: out of range error
    for(auto const& value: inpStrs) {
        workTable.insert(value);
    }
    */

    for(size_t i = 0; i < inpStrs.size(); i++) {
        workTable.insert(inpStrs.at(static_cast<int>(i)));
    }

    std::fstream fs;
    fs.open (LOG_FILE_WAY, std::fstream::in | std::fstream::out | std::fstream::app);

    workTable.dump(fs);
    fs.close();
}

void Test::findElement(lrstruct::HashTable<std::string> &workTable, std::string elFind) {
    std::fstream fs;
    fs.open (LOG_FILE_WAY, std::fstream::in | std::fstream::out | std::fstream::app);
    bool isElExists = workTable.findOrInsert(elFind);
    if(isElExists) {
        fs << "\nFinding element exists in Hash Table!\n";
    } else {
        fs << "\nFinding element doesn't exist in Hash Table!\n";
        workTable.insert(elFind);
        fs << "It was added\n";
    }
    fs.close();
}
