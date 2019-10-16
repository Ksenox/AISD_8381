#include "basics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "components.h"
#include "vec.h"

#include <thread>
#include <QApplication>

int* rec(int indent, int length, int *arr, string& result){

    for(int i = 0; i < indent; i++)
        result.append("\t");

    result.append("--> rec with vector: ");

    for(int i = 0; i < length; i++)
        result.append(to_string(arr[i]) + " ");

    result.append("\n");

    int halfl = length/2;
    if(length > 2){
        rec(indent + 1, length - halfl, arr, result);
        rec(indent + 1, halfl, arr + length - halfl, result);
    }
    if(length == 2){
        int a = arr[0];
        int b = arr[1];
        (arr[0] = (a <= b) ? a : b);
        (arr[1] = (a <= b) ? b : a);
    }

    for(int i = 0; i < indent; i++)
        result.append("\t");

    result.append("<-- rec\n");
    return arr;
}
