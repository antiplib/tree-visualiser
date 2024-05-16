//
// Created by Владислав Отвагин on 07.05.2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <QObject>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPainter>
#include <QRectF>
class Item :  public QObject, public QGraphicsItem{
Q_OBJECT
public:
       explicit Item(int x, int y, int key, bool is_kur, int prior, bool is_rb, bool is_red, QObject *parent = nullptr);
       ~Item();
 signals:
    void signal1(int, int);
private:
    int x, y, key;
    bool is_red = false, is_kurevo = false, is_rb = false;
    int prior;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};



#endif //ITEM_H
