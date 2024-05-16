//
// Created by Владислав Отвагин on 07.05.2024.
//

#include "Item.h"

#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QMessageBox>
#include <QGraphicsView>
#include <QMouseEvent>

#include "tree_space.h"

Item::Item(int x, int y, int key, bool is_kurevo = false, int prior = 0, bool is_rb = false, bool is_red = false, QObject* parent )     : QObject(parent), QGraphicsItem()
 {
 this->key=key;
 this-> x = x;
 this->y = y;
 this->is_kurevo = is_kurevo;
 this->is_rb = is_rb;
 this->is_red = is_red;
 this->prior = prior;
}

Item::~Item() {

}

QRectF Item::boundingRect() const {
 return QRectF(this->x,this->y,30,30);

}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
 // Устанавливаем кисть в QPainter и отрисовываем круг, то есть ТОЧКУ
 if(this->is_kurevo) {
  QBrush b;
  b.setColor(QRgb(808000));
  painter->setBrush(Qt::darkMagenta);
  painter->drawEllipse(QRectF(this->x, this->y, 30, 30));
  QColor color = Qt::green;
  painter->setBrush(Qt::blue);
  QFont font = painter->font();
  font.setPointSize(5);
  painter->setFont(font);
  if(QString::number(this->key).size() <4) {
   painter->drawText(this->x + 3 , this->y + 10, QString::number(this->prior));
   painter->drawText(this->x + 10 , this->y + 17, QString::number(this->key));
  }else {
   painter->drawText(this->x + 3 , this->y + 10, QString::number(this->prior));
   painter->drawText(this->x + 4 , this->y + 17, QString::number(this->key));

  }
 } else if(this->is_rb) {
  QBrush b;
  b.setColor(QRgb(808000));
  if(this->is_red) {
   painter->setBrush(Qt::darkRed);
  }
  else {
   painter->setBrush(Qt::black);

  }
  painter->drawEllipse(QRectF(this->x, this->y, 30, 30));
  QColor color = Qt::green;
  painter->setBrush(Qt::blue);
  QFont font = painter->font();
  font.setPointSize(7);
  painter->setFont(font);
  if(QString::number(this->key).size() <4) {
   painter->drawText(this->x + 10 , this->y + 15, QString::number(this->key));

  }else {
   painter->drawText(this->x + 4 , this->y + 15, QString::number(this->key));
  }
 }
 else{
   QBrush b;
   b.setColor(QRgb(808000));
   painter->setBrush(Qt::darkMagenta);
   painter->drawEllipse(QRectF(this->x, this->y, 30, 30));
   QColor color = Qt::green;
   painter->setBrush(Qt::blue);
   QFont font = painter->font();
   font.setPointSize(7);
   painter->setFont(font);
   if(QString::number(this->key).size() <4) {
    painter->drawText(this->x + 10 , this->y + 15, QString::number(this->key));

   }else {
    painter->drawText(this->x + 4 , this->y + 15, QString::number(this->key));
   }
 }
 Q_UNUSED(option);
 Q_UNUSED(widget);
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event) {
 QPointF mousePos = event->pos();
 emit signal1(mousePos.x(), mousePos.y());
}

