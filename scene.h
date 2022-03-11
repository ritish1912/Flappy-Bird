#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include<QTimer>
#include "pillaritem.h"
#include "birditem.h"
#include <QFile>
#include <QString>
#include <QTextStream>


class Scene : public QGraphicsScene
{
    Q_OBJECT
 public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();
    void startGame();
    bool getGameOn() const;
    void setGameOn(bool value);
    void incrementScore();

    void setScore(int value);
    //void Write();
    //void Read();


signals:
public slots :

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();
    void SetUpPillarTimer();
    void freezeBirdAndPillarInPlace();
    QTimer * pillarTimer;
    BirdItem * bird;
    bool gameOn;

    int score;
    int bestScore;
    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;





};

#endif // SCENE_H
