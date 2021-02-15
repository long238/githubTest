#ifndef GAMESECENE_H
#define GAMESECENE_H

#include <QGraphicsScene>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject* parent,const QRectF &sceneRect);
    ~GameScene();
};


#endif // GAMESECENE_H
