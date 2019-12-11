#include "strstrtester.h"


int pairNumTester(StrStrWorker &ssw, testInfo info, QCustomPlot *&plot, string &output, testResult &res)
{
    if (info.max <= info.min)
        return BAD_MAXMIN;
    output.clear();
    int length = (info.max-info.min)/info.step;
    plot->graph(0)->data()->clear();
    plot->graph(1)->data()->clear();
    plot->graph(2)->data()->clear();
    if (info.checkMaxIter)
        plot->yAxis->setLabel("MI");
    else
        plot->yAxis->setLabel("I");
    if (info.worstCase)
    {
        plot->graph(0)->setPen(QPen(QBrush(QColor((Qt::red))), 8));
        plot->graph(1)->setPen(QPen(QBrush(QColor((Qt::green))), 5));
        plot->graph(2)->setPen(QPen(QBrush(QColor((Qt::blue))), 2));
    }
    else
    {
        plot->graph(0)->setPen(QPen(QBrush(QColor((Qt::red))), 3));
        plot->graph(1)->setPen(QPen(QBrush(QColor((Qt::green))), 3));
        plot->graph(2)->setPen(QPen(QBrush(QColor((Qt::blue))), 3));
    }
    res.maxIterArr = new unsigned int*[3];
    res.sumIterArr = new unsigned int*[3];
    res.clockArr = new long*[3];
    res.num = new int*[length+1];
    for (int i=0; i<3; i++)
    {
        res.maxIterArr[i] = new unsigned int[length+1];
        res.sumIterArr[i] = new unsigned int[length+1];
        res.clockArr[i] = new long[length+1];
        res.num[i] = new int[length+1];
    }
    hCreateInfo outInfo;
    int genErr = 0;
    int counter = -1;
    string param;
    long clStart, clEnd;
    switch (info.mode)
    {
    case 1:
        plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignTop);
        plot->xAxis->setLabel("L");
        for (int mL=info.min; mL<=info.max; mL+=info.step)
        {
            counter++;
            if (!info.worstCase)
                genErr = ssw.generateFile(info.size, mL, info.fileName, info.worstCase, 0);
            for (int hF=1; hF<=3; hF++)
            {
                if (info.worstCase)
                    genErr = ssw.generateFile(info.size, mL, info.fileName, info.worstCase, hF);
                if (genErr)
                    return genErr;
                clStart = clock();
                outInfo = ssw.createHashTable(ssw.getFromFile(info.fileName), hF, info.factor, "");
                clEnd = clock() - clStart;
                res.maxIterArr[hF-1][counter] = outInfo.maxIterNum;
                res.sumIterArr[hF-1][counter] = outInfo.sumIterNum;
                res.num[hF-1][counter] = mL;
                res.clockArr[hF-1][counter] = clEnd;
                if (info.checkMaxIter)
                    plot->graph(hF-1)->addData(mL, outInfo.maxIterNum);
                else
                    plot->graph(hF-1)->addData(mL, outInfo.sumIterNum);
            }
            plot->rescaleAxes();
            plot->yAxis->setRangeLower(0);
            plot->replot();
        }
        param = "Key max length";
        break;
    case 2:
        plot->xAxis->setLabel("N");
        for (int sz=info.min; sz<=info.max; sz+=info.step)
        {
            counter++;
            if (!info.worstCase)
                genErr = ssw.generateFile(sz, info.maxLength, info.fileName, info.worstCase, 0);
            for (int hF=1; hF<=3; hF++)
            {
                if (info.worstCase)
                    genErr = ssw.generateFile(sz, info.maxLength, info.fileName, info.worstCase, hF);
                if (genErr)
                    return genErr;
                clStart = clock();
                outInfo = ssw.createHashTable(ssw.getFromFile(info.fileName), hF, info.factor, "");
                clEnd = clock() - clStart;
                res.maxIterArr[hF-1][counter] = outInfo.maxIterNum;
                res.sumIterArr[hF-1][counter] = outInfo.sumIterNum;
                res.num[hF-1][counter] = sz;
                res.clockArr[hF-1][counter] = clEnd;
                if (info.checkMaxIter)
                    plot->graph(hF-1)->addData(sz, outInfo.maxIterNum);
                else
                    plot->graph(hF-1)->addData(sz, outInfo.sumIterNum);
            }
            plot->rescaleAxes();
            plot->yAxis->setRangeLower(0);
            plot->replot();
        }
        param = "Pair number";
        break;
    case 3:
        plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
        plot->xAxis->setLabel("X");
        for (int fc=info.min; fc<=info.max; fc+=info.step)
        {
            counter++;
            if (!info.worstCase)
                genErr = ssw.generateFile(info.size, info.maxLength, info.fileName, info.worstCase, 0);
            for (int hF=1; hF<=3; hF++)
            {
                if (info.worstCase)
                    genErr = ssw.generateFile(info.size, info.maxLength, info.fileName, info.worstCase, hF);
                if (genErr)
                    return genErr;
                clStart = clock();
                outInfo = ssw.createHashTable(ssw.getFromFile(info.fileName), hF, fc, "");
                clEnd = clock() - clStart;
                res.maxIterArr[hF-1][counter] = outInfo.maxIterNum;
                res.sumIterArr[hF-1][counter] = outInfo.sumIterNum;
                res.num[hF-1][counter] = fc;
                res.clockArr[hF-1][counter] = clEnd;
                if (info.checkMaxIter)
                    plot->graph(hF-1)->addData(fc, outInfo.maxIterNum);
                else
                    plot->graph(hF-1)->addData(fc, outInfo.sumIterNum);
            }
            plot->rescaleAxes();
            plot->yAxis->setRangeLower(0);
            plot->replot();
        }
        param = "Size factor  ";
    }
    output += "Result for hFunc1:\n";
    output += param + "\tWorst hF1\tAll hF1\tTimehF1\tWorst hF2\tAll hF2\tTime hF2\tWorst hF3\tAll hF3\tTime hF3\n";
    for (int i=0; i<=counter; i++)
    {
        output += to_string(res.num[0][i]) + "\t\t" + to_string(res.maxIterArr[0][i]) + "\t" + to_string(res.sumIterArr[0][i]) + "\t" + to_string(res.clockArr[0][i]);
        output += "\t" + to_string(res.maxIterArr[1][i]) + "\t" + to_string(res.sumIterArr[1][i]) + "\t" + to_string(res.clockArr[1][i]);
        output += "\t" + to_string(res.maxIterArr[2][i]) + "\t" + to_string(res.sumIterArr[2][i]) + "\t" + to_string(res.clockArr[2][i]) + "\n";
    }
    return 0;
}
