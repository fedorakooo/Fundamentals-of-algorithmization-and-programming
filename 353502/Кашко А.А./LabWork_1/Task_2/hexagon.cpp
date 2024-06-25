#include "hexagon.h"

QRectF Hexagon::boundingRect() const {
    return {-side, -side, 2 * side, 2 * side};
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen rect;
    rect.setColor(Qt::black);
    painter->setPen(rect);

    QPolygonF hexagonPolygon;

    // Задаем координаты центра шестиугольника
    QPointF center(0, 0); // Центр шестиугольника

    // Вычисляем координаты вершин на основе центра и радиуса
    for (int i = 0; i < 6; ++i) {
        qreal angle = i * M_PI / 3; // Угол между вершинами
        QPointF point(center.x() + side * cos(angle), center.y() + side * sin(angle));
        hexagonPolygon << point;
    }

    painter->drawPolygon(hexagonPolygon);
}

qreal Hexagon::Perimeter() {

    return 6 * side;
}

qreal Hexagon::Area() {

    return (6 * sqrt(3) * side * side) / 4;
}

qreal Hexagon::newArea(qreal number) {

    return side += number;
}

void Hexagon::newparametrs(double side_1, double side_2, double side_3) {

    side = side_1;
}

