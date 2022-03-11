#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include  "birditem.h"
#include  "scene.h"
PillarItem::PillarItem() :
 topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
  bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
  pastBird(false)

{
    topPillar->setPos(QPointF(0,0) -QPointF(topPillar->boundingRect().width()/2,topPillar->boundingRect().height()+ 60));
    bottomPillar->setPos(QPointF(0,0)  + QPointF(-bottomPillar->boundingRect().width()/2,60));
    addToGroup(topPillar);
    addToGroup(bottomPillar);
     yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);
    setPos(QPoint(0,0) + QPoint(xRandomizer + 260, yPos));
    xanimation = new QPropertyAnimation(this,"x",this);
    xanimation->setStartValue(260 + xRandomizer);
    xanimation->setEndValue(-260);
    xanimation->setEasingCurve(QEasingCurve::Linear);
    xanimation->setDuration(1500);
    connect(xanimation,&QPropertyAnimation::finished,[=](){
        qDebug()<<"Animation Finished";
     scene()->removeItem(this);
     delete this;
    });
    xanimation->start();


}

PillarItem::~PillarItem()
{
    qDebug()<<" Deleting Pillar";
    delete topPillar;
    delete bottomPillar;
}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::freezeInPlace()
{
    xanimation->stop();
}

void PillarItem::setX(qreal x)
{
    m_x = x;

    if(x<0 && !pastBird){
        pastBird = true;
        QGraphicsScene * mScene = scene();
        Scene * myScene = dynamic_cast<Scene*>(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }

    if(colllidesWithBird()){
        emit collideFail();
    }

    setPos(QPointF(0,0) + QPointF(x,yPos));
}

bool PillarItem::colllidesWithBird()
{
    QList<QGraphicsItem*>collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());
    foreach(QGraphicsItem * item,collidingItems){
        BirdItem * birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;
}


