#include "drawingwindow.h"
#include "allheaders.h"
#include "TableHandler.h"

void DrawingWindow::drawNodesStartGrid(int levelsCount) {
    for (int i = 0; i < levelsCount; i++) {
        mainGraphicsScene->addRect(startDrawPos.x(), startDrawPos.y() + i * (nodeHight + spaceBetNodes), \
                                   nodeWidth, nodeHight, pen);
    }

    // nodes numbers
    std::vector<QGraphicsTextItem*> numbers;
    numbers.reserve(static_cast<unsigned long>(levelsCount));
    for (unsigned long i{0}; i < static_cast<unsigned long>(levelsCount); i++) {
        numbers[i] = new QGraphicsTextItem;
        numbers[i]->setPlainText(QString::number(i));
        numbers[i]->setPos(startDrawPos.x() + nodeWidth / 4, \
                           static_cast<unsigned long>(startDrawPos.y() + nodeHight) / 4 + \
                           i * static_cast<unsigned long>(nodeHight + spaceBetNodes));
        numbers[i]->setFont(font);
        numbers[i]->setDefaultTextColor(QColor::fromRgb(0, 0, 0));
        mainGraphicsScene->addItem(numbers[i]);
    }

    mainTextOutput->setPlainText("Starting grid was generated!\nHash table key size is: " + \
                            QString::number(levelsCount) + "\n");
}

/**
 * @brief DrawingWindow::makeNodesRects
 *
 * Recalc all nodes coords and positions
 */
void DrawingWindow::makeNodesRects(lrstruct::HashTable<std::string> *wTable, std::vector<nodeRect>& wTableNodeRect) {
    nodeRect newRect;
    int i = 0;
    for(auto iter = workTable->begin(); iter != workTable->end(); ++iter) {
        newRect.data = *iter;
        wTable->getPosOfEl(newRect.data, newRect.level, newRect.posInLevel);
        newRect.geomPar.setX(startDrawPos.x() + nodeWidth + arrowLength + newRect.posInLevel * (arrowLength + rectWidth));
        newRect.geomPar.setY(startDrawPos.y() + newRect.level * (nodeHight + spaceBetNodes) - (nodeHight - rectHieght) / 2);
        newRect.geomPar.setHeight(rectHieght);
        newRect.geomPar.setWidth(rectWidth);
        i++;
        wTableNodeRect.push_back(newRect);
    }
}

void DrawingWindow::drawBaseRects() {
    for(const auto& rect : tableNodesRect) {
        mainGraphicsScene->addRect(rect.geomPar, pen);
    }

    QPen arrowPen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    int arrowX{0}, arrowY{0};
    QPolygon polygon;           // Using Polygon class, to draw the triangle

    // data out
    std::vector<QGraphicsTextItem*> strings;
    strings.reserve(tableNodesRect.size());
    for (unsigned long i = 0; i < tableNodesRect.size(); i++) {
        polygon.clear();
        TableHandler::separateNames(tableNodesRect[i].data);
        strings[i] = new QGraphicsTextItem;
        strings[i]->setPlainText(QString::fromUtf8(tableNodesRect[i].data.c_str()));
        strings[i]->setFont(font);
        strings[i]->setDefaultTextColor(QColor::fromRgb(0, 0, 0));
        strings[i]->setPos(startDrawPos.x() + nodeWidth + arrowLength + \
                           tableNodesRect[i].posInLevel * (rectWidth + arrowLength), \
                           startDrawPos.y() + \
                           tableNodesRect[i].level * (rectHieght + spaceBetNodes));
        arrowX = startDrawPos.x() + nodeWidth + tableNodesRect[i].posInLevel * (rectWidth + arrowLength);
        arrowY = startDrawPos.y() + nodeHight / 2 + tableNodesRect[i].level * (rectHieght + spaceBetNodes);
        mainGraphicsScene->addLine(arrowX, arrowY, arrowX + arrowLength, arrowY, arrowPen);
        // arrow cup drawing
        polygon << QPoint(arrowX + arrowLength - 1, arrowY) << QPoint(arrowX + arrowLength - 1 - arrowTriangleLength, arrowY + arrowTriangleHight) << \
                   QPoint(arrowX + arrowLength - 1 - arrowTriangleLength, arrowY - arrowTriangleHight);
        mainGraphicsScene->addPolygon(polygon, pen, brush);
        mainGraphicsScene->addItem(strings[i]);
    }

    mainTextOutput->setPlainText("All steps was shown.\nIt's full hash table.\nSize is " + \
                                 QString::number(inpStrs.size()) + " elements.");
    reconectForAddDel();
}

void DrawingWindow::drawRect(nodeRect& rectNode, QPen pen = QPen(), QBrush brush = QBrush()) {
    mainGraphicsScene->addRect(rectNode.geomPar, pen);

    QPen arrowPen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    int arrowX{0}, arrowY{0};
    QPolygon polygon;           // Using Polygon class, to draw the triangle
    TableHandler::separateNames(rectNode.data);
    QGraphicsTextItem* text = new QGraphicsTextItem;
    text = new QGraphicsTextItem;
    text->setPlainText(QString::fromUtf8(rectNode.data.c_str()));
    text->setFont(font);
    text->setDefaultTextColor(pen.color());
    text->setPos(startDrawPos.x() + nodeWidth + arrowLength + \
                       rectNode.posInLevel * (rectWidth + arrowLength), \
                       startDrawPos.y() + \
                       rectNode.level * (rectHieght + spaceBetNodes));
    arrowX = startDrawPos.x() + nodeWidth + rectNode.posInLevel * (rectWidth + arrowLength);
    arrowY = startDrawPos.y() + nodeHight / 2 + rectNode.level * (rectHieght + spaceBetNodes);
    mainGraphicsScene->addLine(arrowX, arrowY, arrowX + arrowLength, arrowY, arrowPen);
    // arrow cup drawing
    polygon << QPoint(arrowX + arrowLength - 1, arrowY) << QPoint(arrowX + arrowLength - 1 - arrowTriangleLength, arrowY + arrowTriangleHight) << \
               QPoint(arrowX + arrowLength - 1 - arrowTriangleLength, arrowY - arrowTriangleHight);
    mainGraphicsScene->addPolygon(polygon, pen, brush);
    mainGraphicsScene->addItem(text);
}

void DrawingWindow::drawRectsStepByStep() {
    std::vector<nodeRect> currentNodeRects;
    std::vector<nodeRect> firstEmptyEl;
    tableBackUp.push_back(firstEmptyEl);

    // making backup
    for(stepsCount = static_cast<int>(inpStrs.size() - 1); stepsCount >= 0; stepsCount--) {
        for(auto& rect : tableNodesRect) {
            if(TableHandler::connectNames(rect.data) == inpStrs[static_cast<unsigned long>(stepsCount)]) {
                currentNodeRects.push_back(rect);
                tableBackUp.push_back(currentNodeRects);
                break;
            }
        }
    }
    if(DEBUG) {
        qDebug() << "Backup: " << endl;
        for(auto& rectH : tableBackUp) {
            for(auto& rect : rectH) {
                qDebug() << QString::fromUtf8(rect.data.c_str());
            }
            qDebug() << endl;
        }
    }

    for(stepsCount = static_cast<int>(inpStrs.size() - 1); stepsCount >= 0; stepsCount--) {
        for(auto& rect : tableNodesRect) {
            if(TableHandler::connectNames(rect.data) == inpStrs[static_cast<unsigned long>(stepsCount)]) {
                if(DEBUG)qDebug() << "Next step: " << stepsCount << ", " << QString::fromUtf8(TableHandler::connectNames(rect.data).c_str()) << endl;
                mainTextOutput->setPlainText("Next step for: " +  QString::fromUtf8(TableHandler::connectNames(rect.data).c_str()));
                drawRect(rect, pen, brush);
                TableHandler::loopLatency();
                break;
            }
        }
    }
    mainTextOutput->setPlainText("Full hash table was drawn!\nStep button reconnected!");
    reconectForAddDel();
}

void DrawingWindow::baseDrawStepBack() {
    if(stepsCount <= static_cast<int>(tableBackUp.size())) {
        for(auto& rect : tableNodesRect) {
            if(TableHandler::connectNames(rect.data) == inpStrs[static_cast<unsigned long>(stepsCount)]) {
                if(DEBUG)qDebug() << "Back step: " << stepsCount << ", " << QString::fromUtf8(TableHandler::connectNames(rect.data).c_str()) << endl;
                if(!tableBackUp.empty()) {
                    stepsCount++;
                    mainGraphicsScene->clear();
                    drawNodesStartGrid(levelsCount);
                    std::vector<nodeRect> prevRectDraw;
                    prevRectDraw = tableBackUp[tableBackUp.size() - static_cast<unsigned long>(stepsCount) - 1];
                    for(auto& rect : prevRectDraw) {
                        drawRect(rect, pen, brush);
                    }
                }
                mainTextOutput->setPlainText("Back step for: " +  QString::fromUtf8(TableHandler::connectNames(rect.data).c_str()));
                break;
            }
        }
    }
}

void DrawingWindow::showAllSteps() {
    TableHandler::disableLoop();
    mainGraphicsScene->clear();
    drawNodesStartGrid(levelsCount);
    drawBaseRects();
    nextStepButton->disconnect();
    prevStepButton->disconnect();
    reconectForAddDel();
}

void DrawingWindow::addEl() {
    std::string inputStr = inputEl->text().toStdString();
    int level, posInLevel;
    if(inputStr.empty()) {
        mainTextOutput->setPlainText("Please, enter the string for adding.");
        return;
    }
    if(workTable->findEl(inputStr) == true) {
        workTable->getPosOfEl(inputStr, level, posInLevel);
        mainTextOutput->setPlainText("Element already exists!\nPosition: level = " \
                                     + QString::number(level) + ", pos = " + QString::number(posInLevel));
        return;
    }

    workTable->insert(inputStr);
    workTable->getPosOfEl(inputStr, level, posInLevel);

    tableNodesRect.clear();
    makeNodesRects(workTable, tableNodesRect);
    mainGraphicsScene->clear();

    drawNodesStartGrid(levelsCount);
    drawBaseRects();

    mainTextOutput->setPlainText("Element: " + QString::fromUtf8(inputStr.c_str()) + " was added.\n" + \
                                 "Position: level = " + QString::number(level) + ", pos = " + QString::number(posInLevel));
}

void DrawingWindow::delEl() {
    std::string inputStr = inputEl->text().toStdString();
    int level, posInLevel;
    if(inputStr.empty()) {
        mainTextOutput->setPlainText("Please, enter the string for adding.");
        return;
    }
    workTable->getPosOfEl(inputStr, level, posInLevel);

    workTable->erase(inputStr);

    tableNodesRect.clear();
    makeNodesRects(workTable, tableNodesRect);
    mainGraphicsScene->clear();

    drawNodesStartGrid(levelsCount);
    drawBaseRects();

    mainTextOutput->setPlainText("Element: " + QString::fromUtf8(inputStr.c_str()) + " was deleted.\nIt had position: " + \
                                 QString::number(level) + ", pos = " + QString::number(posInLevel));
}
