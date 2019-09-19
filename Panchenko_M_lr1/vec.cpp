#include "basics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void rec(int indent, int length, int *arr, int *newarr, string& result){
    for(int i = 0; i < indent; i++)
        result.append("\t");

    result.append("--> rec with vector: ");

    for(int i = 0; i < length; i++)
        result.append(to_string(arr[i]) + " ");

    result.append("\n");

    int halfl = length/2;
    if(length > 2){
        rec(indent + 1, length - halfl, arr, newarr, result);
        rec(indent + 1, halfl, arr + length - halfl, newarr + length - halfl, result);
    }
    if(length == 2){
        (newarr[0] = (arr[0] <= arr[1]) ? arr[0] : arr[1]);
        (newarr[1] = (arr[0] <= arr[1]) ? arr[1] : arr[0]);
    }
    if(length == 1)
        newarr[0] = arr[0];

    for(int i = 0; i < indent; i++)
        result.append("\t");

    result.append("<-- rec\n");
}
