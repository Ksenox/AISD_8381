#include "allheaders.h"
#include "HashTable.h"
#include "TableHandler.h"

std::vector<std::string> convertStrToWords(std::string str) {

    // Used to split string around spaces.
    std::istringstream ss(str);

    std::vector<std::string> res;

    // Traverse through all words
    do {
        // Read a word
        std::string word;
        ss >> word;
        res.push_back(word);
    } while (ss);   // While there is more to read

    return res;
}

void TableHandler::makeHashTable(std::vector<std::string> inpStrs, lrstruct::HashTable<std::string>*& workTable) {
    workTable = new lrstruct::HashTable<std::string>();

    /*
     * FIXME: out of range error
    for(auto const& value: inpStrs) {
        workTable.insert(value);
    }
    */

    for(size_t i = 0; i < inpStrs.size(); i++) {
        workTable->insert(inpStrs.at(i));
    }
}

void TableHandler::makeHashTableDump(const lrstruct::HashTable<std::string> *workTable) {
    std::fstream fs;
    fs.open (LOG_FILE_WAY, std::ios::out | std::ios::trunc);
    workTable->dump(fs);
    fs.close();
}

void TableHandler::separateNames(std::string &data) {
    // separate name and surname for tests
    size_t spaceFindPose;
    for(size_t i = 0; i < data.size(); i++) {
    spaceFindPose = data.find(" ");
    if (spaceFindPose != std::string::npos)
        data.replace(spaceFindPose, 1, "\n");
    }
}

std::string TableHandler::connectNames(std::string data) {
    size_t spaceFindPose;
    std::string res = data;
    for(size_t i = 0; i < res.size(); i++) {
    spaceFindPose = res.find("\n");
    if (spaceFindPose != std::string::npos)
        res.replace(spaceFindPose, 1, " ");
    }

    return res;
}

void TableHandler::loopLatency() {
    qDebug() << "Loop latency for step-by-step started" << endl;
    for( ; ; ) {
        QApplication::processEvents();
        if(stepLoopSwitcher == false) break;
    }
    stepLoopSwitcher = true;
}

void TableHandler::disableLoop() {
    stepLoopSwitcher = false;
}
