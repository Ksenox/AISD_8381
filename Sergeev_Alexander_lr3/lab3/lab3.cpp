//
// Created by alex on 10/21/19.
//

#include "lab3.h"


unsigned long lab3::currentPos; // -1 for gui
string lab3::source;
string lab3::nextCommand;
string lab3::answer;
string lab3::message;
visible_stack<char>* lab3::stack;
bool lab3::init = false;

bool lab3::stackOperationalMode;

unsigned long lab3::getCurrentPos() {
    return currentPos;
}

const string& lab3::getSource() {
    return source;
}

const string& lab3::getNextCommand() {
    return nextCommand;
}

const string& lab3::getAnswer() {
    return answer;
}

const string& lab3::getMessage() {
    return message;
}

const visible_stack<char>* lab3::getStackState() {
    return stack;
}

bool lab3::isInit() {
    return init;
}


double lab3::process(string& input, bool friendly) {
    source = input;
    currentPos = 0;
    stack = new visible_stack<char>();
    stackOperationalMode = true;

    init = true;
    answer = ANSWER_PROCESS;

    if (!friendly) {
        bool result = true;

        clock_t sTime = clock();
        for (; currentPos < source.size(); currentPos++) {
            result = unfriendlyStep();
            if (!result) break;
        }
        clock_t eTime = clock();

        if (result) {
            answer = ANSWER_TRUE;
            message = MESSAGE_OK;
        } else {
            answer = ANSWER_FALSE;
            considerMessage();
        }

        init = false;

        return ((double) (eTime - sTime) / CLOCKS_PER_SEC ) * 1000.0;
    }

    return 1L;
}

bool lab3::unfriendlyStep() {
    switch (source[currentPos]) {
        case After:
        case Before:
            if (stackOperationalMode) {
                stack->push(source[currentPos]);
            } else if (stack->isEmpty() || stack->pop() != source[currentPos]) {
                return false;
            }
            break;
        case Cetera:
            stackOperationalMode = !stackOperationalMode;
            break;
        case Dawn:
            if (!stack->isEmpty()) return false;
            stackOperationalMode = !stackOperationalMode;
            break;
        default:
            if (!isblank(source[currentPos])) {
                return false;
            }
            break;
    }
    return true;
}

void lab3::friendlyStep() {
    if (unfriendlyStep()) {
        currentPos++;
        if (considerNextAction()) {
            message = MESSAGE_OK;
            answer = ANSWER_TRUE;
            init = false;
        }
    } else {
        considerMessage();
        answer = ANSWER_FALSE;
        init = false;
    }
}

bool lab3::considerNextAction() {
    if (currentPos < source.size()) {
        switch (source[currentPos]) {
            case After:
            case Before:
                if (stackOperationalMode) {
                    nextCommand = COMMAND_PUSH;
                } else {
                    nextCommand = COMMAND_POP;
                }
                break;
            case Cetera:
                nextCommand = COMMAND_CHANGING;
                break;
            case Dawn:
                nextCommand = COMMAND_REBUILDING;
                break;
            default:
                if (isblank(source[currentPos])) {
                    nextCommand = COMMAND_SKIPPING;
                } else {
                    nextCommand = COMMAND_ERROR;
                }
                break;
        }
        return false;
    } else {
        nextCommand = COMMAND_FINISHING;
        return true;
    }
}

void lab3::considerMessage() {
    switch (source[currentPos]) {
        case After:
        case Before:
        case Dawn:
            message = (new universal_exception(10, currentPos, &source))->toString();
            break;
        default:
            message = (new universal_exception(11, currentPos, &source))->toString();
            break;
    }
}
