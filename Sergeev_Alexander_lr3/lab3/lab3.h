//
// Created by alex on 10/21/19.
//

#ifndef ALG_LAB1_LAB3_H
#define ALG_LAB1_LAB3_H

#include <bits/stdc++.h>
#include "visible_stack.h"

#define ANSWER_PROCESS "Given string is being checked..."
#define ANSWER_TRUE "The string matches the criteria!"
#define ANSWER_FALSE "The string does not match the criteria :/"

#define After 'A'
#define Before 'B'
#define Cetera 'C'
#define Dawn 'D'

#define COMMAND_PUSH "Push"
#define COMMAND_POP "Pop"
#define COMMAND_CHANGING "Checking stack"
#define COMMAND_REBUILDING "Clearing stack"
#define COMMAND_SKIPPING "Skipping"
#define COMMAND_ERROR "Unknown"
#define COMMAND_FINISHING "Finishing"

#define MESSAGE_OK "Program finished successfully."

using namespace std;


class lab3 {
private:
    static unsigned long currentPos; // -1 for gui
    static string source;
    static string nextCommand;
    static string answer;
    static string message;
    static visible_stack<char>* stack;
    static bool init;

    static bool stackOperationalMode;

    static bool considerNextAction();

    static void considerMessage();

    static bool unfriendlyStep();

public:
    static unsigned long getCurrentPos();

    static const string& getSource();

    static const string& getNextCommand();

    static const string& getAnswer();

    static const string& getMessage();

    static const visible_stack<char>* getStackState();

    static bool isInit();

    static double process(string& input, bool friendly); // no time for gui

    static void friendlyStep();
};

#endif //ALG_LAB1_LAB3_H
