/*
This file is generated, but you can safely change it
until you run "gen_actor_source.py" with "--project" flag.

Generated file is just a skeleton for module contents. 
You should change it corresponding to functionality.
*/

#include <QtCore>
#include <QtGui>
//#include <QtDeclarative>
#include <qmessagebox.h>
#include <algorithm>
#include "umkimodule.h"
#include "extensionsystem/pluginmanager.h"
 //#include <iostream> 

namespace ActorUmki {

    
    class AAA : public QWidget {
    public:
        inline explicit AAA(QWidget * pult): QWidget(), pult_(pult) {
            setLayout(new QVBoxLayout);
            layout()->setContentsMargins(0, 0, 0, 0);
            layout()->addWidget(pult);
        }
        inline QSize minimumSizeHint() const { return pult_->minimumSizeHint(); }
    private:
        QWidget * pult_;
    };

    
    
    ExtensionSystem::SettingsPtr UmkiModule::umkiSettings()
    {
        return UmkiModule::self->mySettings();
//        ExtensionSystem::PluginManager * pluginManager = ExtensionSystem::PluginManager::instance();
//        ExtensionSystem::KPlugin * plugin = pluginManager->loadedPlugins("ActorUmki")[0];
//        return pluginManager->settingsByObject(plugin);
    }

    FieldItm::FieldItm( QGraphicsItem* par ,QGraphicsScene *scene)
    {
        sett=UmkiModule::umkiSettings();
    
        upWallLine = NULL;
        downWallLine = NULL;
        leftWallLine = NULL;
        rightWallLine = NULL;
        sepItmUp=NULL;
        sepItmDown=NULL;
        sepItmLeft=NULL;
        sepItmRight=NULL;
        Scene=scene;
        upWall=false;
        downWall=false;
        leftWall=false;
        rightWall=false;
        IsColored=false;
        mark=false;
        ColorRect=NULL;
        upChar=' ';
        downChar=' ';
        upCharItm=NULL;
        downCharItm=NULL;
        markItm=NULL;
        radItm=NULL;
        tempItm=NULL;
        
        font.setPixelSize(9);
        font.setPointSize(9);
        font.setStyle(QFont::StyleNormal);
        font.setBold(true);
        font.setStyleHint(QFont::SansSerif);
        radiation=0;
        temperature=0;
        font.setWeight(2);
        TextColor=QColor(sett->value("Umki/TextColor","#FFFFFF").toString());
        upCharFld=NULL;
        downCharFld=NULL;
        
    }
    
    FieldItm::~FieldItm()
    {
        cleanSelf();
    }
    
    void FieldItm::cleanSelf()
    {
        if(upWallLine)
        {
            if(Scene)
                Scene->removeItem(upWallLine);
            if(upWallLine && upWallLine->scene()==Scene)delete upWallLine;
            upWallLine=NULL;
        }
        if(downWallLine)
        {
            if(Scene)
                if(downWallLine && downWallLine->scene()==Scene)        Scene->removeItem(downWallLine);
            delete downWallLine;
            downWallLine=NULL;
        }
        if(leftWallLine)
        {
            if(Scene)
                Scene->removeItem(leftWallLine);
            if(leftWallLine && leftWallLine->scene()==Scene)delete leftWallLine;
            leftWallLine=NULL;
        }
        if(rightWallLine)
        {
            if(Scene)
                Scene->removeItem(rightWallLine);
            if(rightWallLine && rightWallLine->scene()==Scene) delete rightWallLine;
            rightWallLine=NULL;
        }
        if(ColorRect)
        {
            if(Scene)
                Scene->removeItem(ColorRect);
            delete ColorRect;
            ColorRect=NULL;
        }
        if(upCharItm)
        {
            if(Scene)
                Scene->removeItem(upCharItm);
            delete upCharItm;
            upCharItm=NULL;
        }
        if(downCharItm)
        {
            if(Scene)
                Scene->removeItem(downCharItm);
            delete downCharItm;
            downCharItm=NULL;
        }
        if(markItm)
        {
            if(Scene)
                Scene->removeItem(markItm);
            delete markItm;
            markItm=NULL;
        }
        if(upCharFld)
        {
            if(Scene)Scene->removeItem(upCharFld);
            upCharFld=NULL;
        }
        if(downCharFld)
        {
            if(Scene)Scene->removeItem(downCharFld);
            downCharFld=NULL;
        }
        if(radItm)
        {
            if(Scene)Scene->removeItem(radItm);
            radItm=NULL;
        }
        if(tempItm)
        {
            if(Scene)Scene->removeItem(tempItm);
            tempItm=NULL;
        }
    }
    
    
    void FieldItm::setTextColor()
    {
        sett=UmkiModule::umkiSettings();
        TextColor=QColor(sett->value("Umki/TextColor","#FFFFFF").toString());
        
        
        upCharItm->setDefaultTextColor(TextColor);
        downCharItm->setDefaultTextColor(TextColor);

        
    };
    
    void FieldItm::setLeftsepItem(FieldItm *ItmLeft)
    {
        sepItmLeft=ItmLeft;
        ItmLeft->setRightsepItem(this);	//Obratnaya ssilka u soseda
    }
    
    void FieldItm::setRightsepItem(FieldItm *ItmRight)
    {
        sepItmRight=ItmRight;
    }
    
    void FieldItm::setUpsepItem(FieldItm *ItmUp)
    {
        sepItmUp=ItmUp;
        ItmUp->setDownsepItem(this);
    }
    
    void FieldItm::setDownsepItem(FieldItm *ItmDown)
    {
        sepItmDown=ItmDown;
    }
    void FieldItm::removeDownsepItem()
    {
        sepItmDown=NULL;
    };
    void FieldItm::removeLeftsepItem()
    {
        
        if(sepItmLeft)sepItmLeft->removeRightsepItem();
        sepItmLeft=NULL;
    };
    void FieldItm::removeRightsepItem()
    {
        sepItmRight=NULL;
    };
    void FieldItm::setWalls(int wallByte)
    {
        if((wallByte & UP_WALL) == UP_WALL)upWall=true;else upWall=false;
        if((wallByte & DOWN_WALL) == DOWN_WALL)downWall=true; else
            downWall=false;
        if((wallByte & LEFT_WALL) == LEFT_WALL)leftWall=true; else leftWall=false;
        if((wallByte & RIGHT_WALL) == RIGHT_WALL)rightWall=true; else rightWall=false;
    }
    
    int FieldItm::wallByte()
    {
        int toret=0;
        if(upWall)toret+=UP_WALL;
        if(downWall)toret+=DOWN_WALL;
        if(leftWall)toret+=LEFT_WALL;
        if(rightWall)toret+=RIGHT_WALL;
        return toret;
    }
    
    void FieldItm::setUpLine(QGraphicsLineItem *Line, QPen pen)
    {
        upWallLine=Line;
        upWallLine->setPen(pen);
        Scene->addItem(upWallLine);
        upWallLine->setZValue(1);
    }
    
    void FieldItm::showCharMark(qreal upLeftCornerX, qreal upLeftCornerY, int size)
    {
        showUpChar(upLeftCornerX,upLeftCornerY,size);
        showDownChar(upLeftCornerX,upLeftCornerY,size);
        showMark(upLeftCornerX,upLeftCornerY,size);
    }
    void FieldItm::showRTItm(qreal upLeftCornerX, qreal upLeftCornerY, int size,int mode)
    {
       
        if (radItm) {
            if (Scene)
                Scene->removeItem(radItm);
            delete radItm;
            radItm = NULL;
        }
        
        
        if (tempItm) {
            if (Scene)
                Scene->removeItem(tempItm);
            delete tempItm;
            tempItm = NULL;
        }
        
     
      // radItm=Scene->addRect(upLeftCornerX+1, upLeftCornerY+1, size*(radiation/99),size/5 );
        radItm=new EditLine();
        radItm->setRad();
        radItm->moveBy(upLeftCornerX+1, upLeftCornerY+1);
        radItm->setScale(0.25);
        radItm->setValue(radiation);
        // radItm=Scene->addItem(upLeftCornerX+1, upLeftCornerY+1, size*(radiation/99),size/5 );
       Scene->addItem(radItm);
      // radItm->setBrush(QBrush(Qt::yellow));
     //  radItm->setPos(upLeftCornerX+1,upLeftCornerY+1);
        radItm->setZValue(100);
        if(mode==RAD_MODE)radItm->show();
        else radItm->hide();
        
        
        
        tempItm=new EditLine();
        tempItm->moveBy(upLeftCornerX+1, upLeftCornerY+1);
        tempItm->setTemp();
        tempItm->setValue(temperature);
        Scene->addItem(tempItm);
         tempItm->setScale(0.25);
        tempItm->setZValue(100);
        if(mode==TEMP_MODE)tempItm->show();
        else tempItm->hide();
        //tempItm=Scene->addText("T: "+QString::number(temperature),font);
        //tempItm->setDefaultTextColor(TextColor);
        //tempItm->setPos(upLeftCornerX+1,upLeftCornerY+size-16);
        //tempItm->setZValue(1);
        
        
    }
    void FieldItm::hideRTItm()
    {
        if (radItm) {radItm->hide();};
        if(tempItm){tempItm->hide();};
    }
    void FieldItm::showCharFld(qreal upLeftCornerX,qreal upLeftCornerY,int field_size)
    {
        
         if(upCharFld) Scene->removeItem(upCharFld);
        upCharFld=new QGraphicsRectItem(upLeftCornerX+4,upLeftCornerY+4,7,11);
        upCharFld->setPen(QPen(Qt::NoPen));
        upCharFld->setBrush(QBrush(QColor(60,115,175)));
        Scene->addItem(upCharFld);
        upCharFld->setZValue(0.2);
        
         if(downCharFld) Scene->removeItem(downCharFld);
        downCharFld=new QGraphicsRectItem(upLeftCornerX+4,field_size+upLeftCornerY-14,7,11);
        downCharFld->setPen(QPen(Qt::NoPen));
        downCharFld->setBrush(QBrush(QColor(60,115,175)));
        Scene->addItem(downCharFld);
        downCharFld->setZValue(0.2);
    };
    void FieldItm::hideCharFld()
    {
       
       if(upCharFld!=NULL) Scene->removeItem(upCharFld);
        if(!Scene)
        {
        qDebug()<<"Scene is NULL!";
            return;
        }
       if(downCharFld)Scene->removeItem(downCharFld);
    };
    void FieldItm::showUpChar(qreal upLeftCornerX, qreal upLeftCornerY, int size)
    {
        Q_UNUSED(size);
        if (upCharItm) {
            if (Scene)
                Scene->removeItem(upCharItm);
            delete upCharItm;
            upCharItm = NULL;
        }
        if (upChar.isPrint() && upChar!=' ') {
            upCharItm=Scene->addText(upChar,font);
            upCharItm->setDefaultTextColor(TextColor);
            upCharItm->setPos(upLeftCornerX+1,upLeftCornerY+1);
            upCharItm->setZValue(1);
        }
    }
    
    void FieldItm::showDownChar(qreal upLeftCornerX, qreal upLeftCornerY, int size)
    {
        Q_UNUSED(size);
        if (downCharItm) {
            if (Scene) {
                Scene->removeItem(downCharItm);
            }
            delete downCharItm;
            downCharItm = NULL;
        }
        if (downChar.isPrint() && downChar!=' ') {
            downCharItm=Scene->addText(downChar,font);
            downCharItm->setDefaultTextColor(TextColor);
            downCharItm->setPos(upLeftCornerX+1,upLeftCornerY+size-16);
            downCharItm->setZValue(1);
        }
    }
    
    void FieldItm::showMark(qreal upLeftCornerX, qreal upLeftCornerY, int size)
    {
        if(mark)
        {
            if (markItm) {
                if (Scene) {
                    Scene->removeItem(markItm);
                }
                delete markItm;
                markItm = NULL;
            }
            markItm=Scene->addText(QChar(9787),font);
            markItm->setDefaultTextColor(TextColor);
            markItm->setPos(upLeftCornerX+size-(size/3)-3,upLeftCornerY-15+size);
            markItm->setZValue(1);
        }
    }
    
    void FieldItm::setColorRect(QGraphicsRectItem *Rect)
    {
        ColorRect = Rect;
        ColorRect->setPen(QPen("gray"));
        ColorRect->setBrush(QBrush(QColor("gray")));
        
        Scene->addItem(Rect);
        
        Rect->setZValue(0.2);
        IsColored=true;
    }
    
    void FieldItm::setDownLine(QGraphicsLineItem *Line, QPen pen)
    {
        downWallLine=Line;
        downWallLine->setPen(pen);
        Scene->addItem(downWallLine);
        downWallLine->setZValue(1);
    }
    
    void FieldItm::setLeftLine(QGraphicsLineItem *Line, QPen pen)
    {
        leftWallLine=Line;
        leftWallLine->setPen(pen);
        Scene->addItem(leftWallLine);
        leftWallLine->setZValue(1);
    }
    
    void FieldItm::setRightLine(QGraphicsLineItem *Line, QPen pen)
    {
        rightWallLine=Line;
        rightWallLine->setPen(pen);
        Scene->addItem(rightWallLine);
        
        rightWallLine->setZValue(1);
    }
    
    bool FieldItm::hasUpWall()
    {
        return upWall;
    }
    
    bool FieldItm::hasDownWall()
    {
        return downWall;
    }
    bool FieldItm::hasLeftWall()
    {
        return leftWall;
    }
    
    bool FieldItm::hasRightWall()
    {
        return rightWall;
    }
    
    bool FieldItm::canUp()
    {
        if(!hasUpSep())return false;
        return !(upWall || sepItmUp->hasDownWall());
    }
    
    bool FieldItm::canDown()
    {
        if(!hasDownSep())return false;
        return !(downWall || sepItmDown->hasUpWall());
    }
    
    bool FieldItm::canLeft()
    {
        if(!hasLeftSep())return false;
        return !(leftWall || sepItmLeft->hasRightWall());
    }
    
    bool FieldItm::canRight()
    {
        if(!hasRightSep())return false;
        return !(rightWall || sepItmRight->hasLeftWall());
    }
    
    bool FieldItm::hasUpSep()
    {
        if(sepItmUp)return true;return false;
    }
    
    bool FieldItm::hasDownSep()
    {
        if(sepItmDown)return true;return false;
    }
    
    bool FieldItm::hasLeftSep()
    {
        if(sepItmLeft)return true;return false;
    }
    
    bool FieldItm::hasRightSep()
    {
        if(sepItmRight)return true;return false;
    }
    
    QGraphicsLineItem* FieldItm::UpWallLine()
    {
        return upWallLine;
    }
    
    QGraphicsLineItem* FieldItm::DownWallLine()
    {
        return downWallLine;
    }
    
    QGraphicsLineItem* FieldItm::LeftWallLine()
    {
        return leftWallLine;
    }
    
    QGraphicsLineItem* FieldItm::RightWallLine()
    {
        return rightWallLine;
    }
    
    bool FieldItm::isColored()
    {
        return IsColored;
    }
    
    void FieldItm::removeUpWall()
    {
        if(upWallLine)
        {
            Scene->removeItem(upWallLine);
            delete upWallLine;
            upWallLine=NULL;
            qDebug("UwallRemoved");
        };
        upWall=false;
        if(hasUpSep())if(sepItmUp->hasDownWall())sepItmUp->removeDownWall();
    }
    
    void FieldItm::setUpWall(QGraphicsLineItem *Line, QPen pen)
    {
        upWall=true;
        setUpLine(Line,pen);
    }
    
    void FieldItm::setDownWall(QGraphicsLineItem *Line, QPen pen)
    {
        downWall=true;
        setDownLine(Line,pen);
    }
    
    void FieldItm::removeDownWall()
    {
        if(downWallLine)
        {
            Scene->removeItem(downWallLine);
            delete downWallLine;
            downWallLine=NULL;
            qDebug("DwallRemoved");
        };
        downWall=false;
        
        if(hasDownSep())if(sepItmDown->hasUpWall())sepItmDown->removeUpWall();
    }
    
    void FieldItm::removeLeftWall()
    {
        if(leftWallLine)
        {
            Scene->removeItem(leftWallLine);
            delete leftWallLine;
            leftWallLine=NULL;
            qDebug("LwallRemoved");
        };
        leftWall=false;
        
        if(hasLeftSep())if(sepItmLeft->hasRightWall())sepItmLeft->removeRightWall();
    }
    
    void FieldItm::removeRightWall()
    {
        if(rightWallLine)
        {
            QGraphicsScene* debug=rightWallLine->scene();
            Q_UNUSED(debug);
            rightWallLine->setVisible(false);
            Scene->removeItem(rightWallLine);
            delete rightWallLine;
            rightWallLine=NULL;
            qDebug("RwallRemoved");
        };
        rightWall=false;
        
        if(hasRightSep())if(sepItmRight->hasLeftWall())sepItmRight->removeLeftWall();
    }
    
    void FieldItm::setLeftWall(QGraphicsLineItem *Line, QPen pen)
    {
        leftWall=true;
        setLeftLine(Line,pen);
    }
    
    void FieldItm::setRightWall(QGraphicsLineItem *Line, QPen pen)
    {
        rightWall=true;
        setRightLine(Line,pen);
    }
    
    void FieldItm::removeColor()
    {
        
        if(ColorRect)
        {
            Scene->removeItem(ColorRect);
            delete ColorRect;
            ColorRect=NULL;
        };
        IsColored=false;
    }
    
    void FieldItm::removeMark()
    {
        if(markItm)
        {
            Scene->removeItem(markItm);
            delete markItm;
            markItm=NULL;
        };
        mark=false;
    }
    
    void FieldItm::removeUpChar()
    {
        if(upCharItm)
        {
            Scene->removeItem(upCharItm);
            delete upCharItm;
            upCharItm=NULL;
        };
        
        upChar=' ';
    }
    
    void FieldItm::removeDownChar()
    {
        if(downCharItm)
        {
            Scene->removeItem(downCharItm);
            delete downCharItm;
            downCharItm=NULL;
        };
        downChar=' ';
    }
    
    bool FieldItm::emptyCell()
    {
        return (!upWall && !downWall && !leftWall && !rightWall && !IsColored && !mark)
        &&(radiation==0)&&(temperature==0)&&(upChar==' ')&&(downChar==' ');
    }
    
    void FieldItm::setScene(QGraphicsScene *scene)
    {
        Scene=scene;
    }
    
    void FieldItm::wbWalls()
    {
        if(UpWallLine())
        {
            wallPen=UpWallLine()->pen();
            int w=3;
            if(!hasUpSep())w=4;
            UpWallLine()->setPen(QPen(QBrush(QColor("blue")),w));
        };
        if(DownWallLine())
        {
            wallPen=DownWallLine()->pen();
            int w=3;
            if(!hasDownSep())w=4;
            DownWallLine()->setPen(QPen(QBrush(QColor("blue")),w));
        };
        if(LeftWallLine())
        {
            wallPen=LeftWallLine()->pen();
            int w=3;
            if(!hasLeftSep())w=4;
            LeftWallLine()->setPen(QPen(QBrush(QColor("blue")),w));
        };
        if(RightWallLine())
        {
            wallPen=RightWallLine()->pen();
            int w=3;
            if(!hasRightSep())w=4;
            RightWallLine()->setPen(QPen(QBrush(QColor("blue")),w));
        };
        
        if(downCharItm)downCharItm->setDefaultTextColor("black");
        if(upCharItm)upCharItm->setDefaultTextColor("black");
        if(markItm)markItm->setDefaultTextColor("black");
    }
    
    void FieldItm::colorWalls()
    {
        if(UpWallLine())
        {
            if(!hasUpSep())wallPen.setWidth(4);else wallPen.setWidth(3);
            UpWallLine()->setPen(wallPen);
        };
        if(DownWallLine())
        {
            if(!hasDownSep())wallPen.setWidth(4);else wallPen.setWidth(3);
            DownWallLine()->setPen(wallPen);
        };
        if(LeftWallLine())
        {
            if(!hasLeftSep())wallPen.setWidth(4);else wallPen.setWidth(3);
            LeftWallLine()->setPen(wallPen);
        };
        if(RightWallLine())
        {
            if(!hasRightSep())wallPen.setWidth(4);else wallPen.setWidth(3);
            RightWallLine()->setPen(wallPen);
        };
        if(downCharItm)downCharItm->setDefaultTextColor("white");
        if(upCharItm) upCharItm->setDefaultTextColor("white");
        if(markItm)markItm->setDefaultTextColor("white");
    }
    
    
    
    
    FieldItm* FieldItm::Copy()
    {
        FieldItm* copy=new FieldItm(0,Scene);
        copy->leftWall=leftWall;
        copy->rightWall=rightWall;
        copy->upWall=upWall;
        copy->downWall=downWall;
        
        copy->upChar=upChar;
        copy->downChar=downChar;
        copy->mark=mark;
        copy->radiation=radiation;
        copy->temperature=temperature;
        copy->IsColored=IsColored;
        copy->upCharFld=upCharFld;
        return copy;
    };
    
    UmkiField::~UmkiField()
    {
        destroyField();
        destroyUmki();
        destroyNet();
        destroyScene();
        for (int i=0; i<Items.size(); i++) {
            for (int j=0; j<Items[i].size(); j++) {
                if (Items[i][j])
                    delete Items[i][j];
            }
        }
        Items.clear();
    }
    
    UmkiField::UmkiField(QWidget *parent)
    : QGraphicsScene(parent)
	
    
    {
        old_cell=QPair<int,int>(-1,-1);
        pressed=false;
        sett=UmkiModule::umkiSettings();
//        QString className = sett->metaObject()->className();
        Parent=parent;
        mode=0;
        LineColor = QColor(sett->value("LineColor","#C8C800").toString());
        EditLineColor = QColor(sett->value("LineColorEdit","#C8C800").toString());
        WallColor=QColor(sett->value("WallColor","#C8C800").toString());
        EditColor=QColor(sett->value("EditColor","#00008C").toString());
        NormalColor=QColor(sett->value("NormalColor","#289628").toString());
        showLine=QPen(QColor(0,255,0,125));
        showLine.setWidth(3);
        timer=new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(timerTic()));
        fieldSize=30;
        this->setItemIndexMethod(NoIndex);
        umki=NULL;
        markMode=true;

        wasEdit=false;
        showWall=new QGraphicsLineItem(0,0,0,0);
        this->addItem(showWall);
      //  textEditMode=false;
        mode=NORMAL_MODE;
        keyCursor=new QGraphicsLineItem(0,0,0,0);
        this->addItem(keyCursor); 
        keyCursor->hide();
        radSpinBox=new QDoubleSpinBox();
        radSpinBox->setRange(0, 99);
        tempSpinBox=new QSpinBox();
        tempSpinBox->setRange(-273, 233);
        tempSpinBox->setValue(77);
        radSpinBox->setValue(55);
        btnAddRow=new QToolButton();btnAddCol=new QToolButton();btnRemCol=new QToolButton();btnRemRow=new QToolButton();
    };
  void UmkiField::showButtons(bool yes)
    {
        if(!wAddCol)return;
        wAddCol->setVisible(yes);
        wAddRow->setVisible(yes);
        wRemCol->setVisible(yes);
        wRemRow->setVisible(yes);
        if(yes)
        {
            wAddRow->setPos((fieldSize*(columns())/2) - (wAddRow->size().height()+3),fieldSize*(rows())+5);
            wRemRow->setPos(fieldSize*(columns())/2+2,fieldSize*((float)rows())+5);
            
            wAddCol->setPos(fieldSize*((float)columns())+7,(fieldSize*(rows())/2) - (wAddRow->size().width()+1));
            wRemCol->setPos(fieldSize*((float)columns())+7,fieldSize*(rows())/2+1);
        }
    };
  void UmkiField::setMode( int Mode) 
    { 
        mode=Mode;
        sett=UmkiModule::umkiSettings();
        QGraphicsView * view=views().first();
       if(mode==NORMAL_MODE)
       {
              if(this->items().indexOf(keyCursor)>-1)this->removeItem(keyCursor);
       
           radSpinBox->hide();
           tempSpinBox->hide();
           redrawEditFields();
           redrawRTFields();  
           view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
           view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
           showButtons(false);
           update();
       }
        if(mode==NEDIT_MODE)
        {
             if(this->items().indexOf(keyCursor)>-1)this->removeItem(keyCursor);
          radSpinBox->hide();
          tempSpinBox->hide();
          redrawEditFields();
          redrawRTFields();  
          view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
          view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            showButtons(true);
            update();
        }
        
        if(mode==RAD_MODE)
        {
               if(this->items().indexOf(keyCursor)>-1)this->removeItem(keyCursor);
          
            tempSpinBox->hide();
            radSpinBox->setParent(view);
            radSpinBox->move(100,2);
            
            radSpinBox->show();
            clickCell=QPair<int,int>(-1,-1);
          
            
            
            redrawEditFields();
            redrawRTFields();
            showButtons(false);
            update();
            
        }
        if(mode==TEMP_MODE)
        {
            if(this->items().indexOf(keyCursor)>-1)this->removeItem(keyCursor);
         
            radSpinBox->hide();
            tempSpinBox->setParent(view);
            tempSpinBox->move(100,2);
            
            tempSpinBox->show();
            clickCell=QPair<int,int>(-1,-1);
            
            
            
            redrawEditFields();
            redrawRTFields();
            showButtons(false);
            update();
            
        }
        if(mode==TEXT_MODE)
        {
            tempSpinBox->hide();
            radSpinBox->hide();
            redrawRTFields();
            setTextEditMode(true);
            showButtons(false);
            update();
        }
        LineColor = QColor(sett->value("LineColor","#C8C800").toString());
        WallColor=QColor(sett->value("WallColor","#C8C800").toString());
        EditColor=QColor(sett->value("EditColor","#00008C").toString());
        NormalColor=QColor(sett->value("NormalColor","#289628").toString());
        update();
        view->repaint();
        update();
       
        
    }
    void UmkiField::editField()
    {
       mode=NEDIT_MODE;
        showButtons(true);
     //   connect(cellDialog->buttonBox,SIGNAL(accepted()),this,SLOT(cellDialogOk()));
    };
    /**
     * Создание пустого поля умкиа
     * @param x количество строк
     * @param y количество столбцов
     */
    void UmkiField::createField(int x,int y)
    {
        destroyNet();
        destroyField();
        destroyUmki();
        //qDebug("Before items destroy");
        while (Items.count()>0)Items.removeFirst();
        //qDebug("After items destroy");
        for(int i=0;i<x;i++)
        {
            QList<FieldItm*> row;
            for(int j=0;j<y;j++)
            {
                
                row.append(new FieldItm(0,this));
                FieldItm* thisItm=row.last();
                if(j>0)thisItm->setLeftsepItem(row[j-1]);//Устанавливаем соседей
                if(i>0)thisItm->setUpsepItem(Items[i-1].at(j));//Устанавливаем соседей
            };
            Items.append(row);
        };
        createResizeButtons();
        
       timer->stop();
    };
    void UmkiField::addRow()
    {
        qDebug()<<"addRow";
        QList<FieldItm*> row;
        int old_rows=rows();
        for(int i=0;i<columns();i++)
        {
            row.append(new FieldItm(0,this));
            FieldItm* thisItm=row.last();
            if(i>0)thisItm->setLeftsepItem(row[i-1]);
            thisItm->setUpsepItem(Items[Items.count()-1].at(i));
        }
        Items.append(row);
        drawField(fieldSize);
        showButtons(true);
        qDebug()<<"addRow";
    };
    void UmkiField::remRow()
    {
        
        if(Items.count()>1){
            for(int i=0;i<columns();i++)
            {
                Items[Items.count()-2].at(i)->removeDownsepItem();
            }
        
            Items.removeLast();
            if(umkiY()>rows()-1)
            {
                setUmkiPos(umkiX(), umkiY()-1);
            }
        drawField(fieldSize);
            showButtons(true);
        }
    };

    void UmkiField::remCol()
    {
        
        if(Items.count()>0 && (Items[0].count()>1)){
            for(int i=0;i<Items.count();i++)
            {
                Items[i].at(Items[i].count()-1)->removeLeftsepItem();
                Items[i].removeLast();
            }
            if(umkiX()>columns()-1)
            {
                setUmkiPos(umkiX()-1, umkiY());
            }
         
            drawField(fieldSize);
            showButtons(true);
        }
    };
    
    void UmkiField::addCol()
    {
        btnAddCol->setDown ( true );
        
        for(int i=0;i<Items.count();i++)
        {
            FieldItm* lastItm=Items[i].last();
            Items[i].append(new FieldItm(0,this));
            
            Items[i].last()->setLeftsepItem(lastItm);
            if(i>0)
            {
                Items[i].last()->setUpsepItem(Items[i-1].last());
            }
          
        }
   
        drawField(fieldSize);
        showButtons(true);
    }
    
    QPoint UmkiField::upLeftCorner(int str,int stlb)
    {
        int ddx = BORT-2;
        return QPoint(stlb*fieldSize+ddx,str*fieldSize);
    };
    
    FieldItm* UmkiField::getFieldItem(int str,int stlb)
    {
        if(rows()<str) {
            qDebug("UmkiField:rows()<str");
            return NULL;
        };
        if(columns()<stlb) {
            qDebug("UmkiField:columns()<str");
            return NULL;
        };
        
        if (str>=0 && stlb>=0 && str<Items.size() && stlb<Items[str].size())
            return Items[str].at(stlb);
        else
            return NULL;
        
    };
    void UmkiField::drawField(uint FieldSize)
    {
        sett=UmkiModule::umkiSettings();
        keyCursor=new QGraphicsLineItem(0,0,0,0);
        this->addItem(keyCursor);
        keyCursor->hide();
        if(rows()<1||columns()<1)return;
        destroyNet();
        destroyField();
        // clear();
        //debug();
        QColor gridColor;
        showWall = new QGraphicsLineItem(0,0,0,0);
        if(!(mode>0))
        {
        Color = NormalColor;//Normal Color
        gridColor=LineColor;
        }
        else 
        {
        Color=EditColor;//Edit Color
         gridColor=EditLineColor;
        }
        
        this->setBackgroundBrush (QBrush(Color));
        fieldSize=FieldSize;
        drawNet();
        
        BortLine = QPen(WallColor,4);
        StLine=QPen(gridColor,3);
        WallLine=QPen(WallColor,3);
        qDebug()<<"Rows"<<rows()<< "Cols:"<<columns();
        //if(rows()==2)return;
        for(int i=0;i<rows();i++) //Cikl po kletkam
        {
            QList<FieldItm*>* row=&Items[i];
            for(int j=0;j<columns();j++)
            {
               
                //Отрисовываем бордюры
                row->at(j)->setScene(this);
//                if(textEditMode)row->at(j)->showCharFld(upLeftCorner(i,j).x(),
//                                        upLeftCorner(i,j).y(),fieldSize);
//                else row->at(j)->hideCharFld();
                
                
                if(!row->at(j)->hasUpSep())
                    row->at(j)->setUpLine(
                                          new QGraphicsLineItem(upLeftCorner(i,j).x(),
                                                                upLeftCorner(i,j).y(),
                                                                upLeftCorner(i,j).x()+fieldSize,
                                                                upLeftCorner(i,j).y()),BortLine);
                
                if(!row->at(j)->hasDownSep())
                    row->at(j)->setDownLine(
                                            new QGraphicsLineItem(upLeftCorner(i,j).x(),
                                                                  upLeftCorner(i,j).y()+fieldSize,
                                                                  upLeftCorner(i,j).x()+fieldSize,
                                                                  upLeftCorner(i,j).y()+fieldSize),BortLine);
                
                
                if(!row->at(j)->hasLeftSep())
                {
                    row->at(j)->setLeftLine(
                                            new QGraphicsLineItem(upLeftCorner(i,j).x(),
                                                                  upLeftCorner(i,j).y(),
                                                                  upLeftCorner(i,j).x(),
                                                                  upLeftCorner(i,j).y()+fieldSize),BortLine);
                    //qDebug()<<"Line "<<row->at(j)->leftWallLine <<"Scene"<<row->at(j)->leftWallLine->scene();
                };
                if(!row->at(j)->hasRightSep())
                    row->at(j)->setRightLine(
                                             new QGraphicsLineItem(upLeftCorner(i,j).x()+fieldSize,
                                                                   upLeftCorner(i,j).y(),
                                                                   upLeftCorner(i,j).x()+fieldSize,
                                                                   upLeftCorner(i,j).y()+fieldSize),BortLine);
                if(row->at(j)->hasDownWall())
                {
                    row->at(j)->setDownLine(
                                            new QGraphicsLineItem(upLeftCorner(i,j).x(),
                                                                  upLeftCorner(i,j).y()+fieldSize,
                                                                  upLeftCorner(i,j).x()+fieldSize,
                                                                  upLeftCorner(i,j).y()+fieldSize),WallLine);
                    
                };
                if(row->at(j)->hasUpWall())
                {
                    row->at(j)->setUpLine(
                                          new QGraphicsLineItem(upLeftCorner(i,j).x(),
                                                                upLeftCorner(i,j).y(),
                                                                upLeftCorner(i,j).x()+fieldSize,
                                                                upLeftCorner(i,j).y()),WallLine);
                    
                };
                if(row->at(j)->hasLeftWall())
                {
                    row->at(j)->setLeftLine(
                                            new QGraphicsLineItem(upLeftCorner(i,j).x(),
                                                                  upLeftCorner(i,j).y(),
                                                                  upLeftCorner(i,j).x(),
                                                                  upLeftCorner(i,j).y()+fieldSize),WallLine);
                    
                };
                if(row->at(j)->hasRightWall())
                {
                    row->at(j)->setRightLine(
                                             new QGraphicsLineItem(upLeftCorner(i,j).x()+fieldSize,
                                                                   upLeftCorner(i,j).y(),
                                                                   upLeftCorner(i,j).x()+fieldSize,
                                                                   upLeftCorner(i,j).y()+fieldSize),WallLine);
                    
                };
                if(row->at(j)->isColored())
                {
                    row->at(j)->setColorRect(
                                             new QGraphicsRectItem(upLeftCorner(i,j).x(),
                                                                   upLeftCorner(i,j).y(),
                                                                   fieldSize,
                                                                   fieldSize));
                    
                };
                
                row->at(j)->showCharMark(upLeftCorner(i,j).x(),upLeftCorner(i,j).y(),fieldSize);
                
                
            };
        };
        
 
        createResizeButtons();
        destroyUmki();
        createUmki();
      
       // wAddRow->setVisible(yes);
        //wRemCol->setVisible(yes);
        //wRemRow->setVisible(yes);
        
    }
    void UmkiField::createResizeButtons()
    {
       
        btnAddRow=new QToolButton();btnAddCol=new QToolButton();btnRemCol=new QToolButton();btnRemRow=new QToolButton();
        
        
        
        btnAddRow->setCheckable(false);
        btnAddRow->setIcon(QIcon(UmkiModule::self->myResourcesDir().absoluteFilePath("plus.png")));
        qDebug()<<UmkiModule::self->myResourcesDir().absoluteFilePath("plus.png");
        btnAddCol->setCheckable(false);
        
        btnAddCol->setIcon(QIcon(UmkiModule::self->myResourcesDir().absoluteFilePath("plus.png")));
        
        btnRemCol->setCheckable(false);
        btnRemRow->setCheckable(false);
        btnRemCol->setIcon(QIcon(UmkiModule::self->myResourcesDir().absoluteFilePath("minus.png")));
        btnRemRow->setIcon(QIcon(UmkiModule::self->myResourcesDir().absoluteFilePath("minus.png")));
        
        
        
        btnAddRow->setAutoRaise ( true);
        btnAddCol->setAutoRaise ( true);
        btnRemCol->setAutoRaise ( true);
        btnRemRow->setAutoRaise ( true);
       // connect(btnAddRow,SIGNAL(pressed ()),this,SLOT(addRow()));
        
        wAddRow=addWidget(btnAddRow);
        wAddCol=addWidget(btnAddCol);wRemCol=addWidget(btnRemCol);wRemRow=addWidget(btnRemRow);
        wAddRow->setZValue(200);
     
        wAddRow->resize(fieldSize, (float)fieldSize/2);
        wRemRow->resize(fieldSize, (float)fieldSize/2);
        
        wAddCol->resize((float)fieldSize/2, fieldSize);
        wRemCol->resize((float)fieldSize/2, fieldSize);
        
        

    //     return;
        
        wAddCol->setZValue(200);
         wRemRow->setZValue(200);
         wRemCol->setZValue(200);
        
        showButtons(false);
    };
    void UmkiField::destroyField()
    {
        qDebug()<<"cols"<<columns();
        for(int i=0;i<columns();i++)
        {
            for(int j=0;j<rows();j++)  {
                FieldItm * itm=getFieldItem(j,i);
                if(itm)itm->cleanSelf();
            }
        };
       
        clear();
        setka.clear();
        umki=NULL;
        keyCursor=NULL;
        this->update();
    }
   void UmkiField::setTextEditMode(bool flag)
    {
        clickCell=QPair<int,int>(-1,-1);
        if(flag)
        {
            keyCursor= new QGraphicsLineItem(0,0,0,0);
            this->addItem(keyCursor);
        }
       
       
       // destroyField();
       // drawField(FIELD_SIZE_SMALL);

        if(mode!=TEXT_MODE && !flag)
        {timer->stop();
        if(keyCursor)keyCursor->hide();
        };
        radSpinBox->hide(); 
        redrawEditFields();
        redrawRTFields();
    };

    
    void UmkiField::destroyUmki()
    {
        if(umki)
        {
            removeItem(umki);
            delete umki;
            umki=NULL;
        }
    }
    
    void UmkiField::destroyNet()
    {
        
        for(int i=0;i<setka.count();i++)
            this->removeItem(setka[i]);
        setka.clear();
    }
    void UmkiField::redrawEditFields()
    {
        for(int i=0;i<rows();i++) //Cikl po kletkam
        {
            QList<FieldItm*>* row=&Items[i];
            for(int j=0;j<columns();j++)
            {
      
                if(mode==TEXT_MODE)row->at(j)->showCharFld(upLeftCorner(i,j).x(),
                                                        upLeftCorner(i,j).y(),FIELD_SIZE_SMALL);
                else row->at(j)->hideCharFld();
                
            };
        };
    };
    void UmkiField::redrawRTFields()
    {
        for(int i=0;i<rows();i++) //Cikl po kletkam
        {
            QList<FieldItm*>* row=&Items[i];
            for(int j=0;j<columns();j++)
            {
                
                if(mode==RAD_MODE || mode==TEMP_MODE)row->at(j)->showRTItm(upLeftCorner(i,j).x(),
                                                        upLeftCorner(i,j).y(),FIELD_SIZE_SMALL,mode);
                else row->at(j)->hideRTItm();
                
            };
        };
        update();

    };
    void UmkiField::destroyScene()
    {
        QList<QGraphicsItem*> items=this->items();
        while(items.count()>0)
        {
            this->removeItem(items.first());
            items=this->items();
        }
        clickCell=QPair<int,int>(-1,-1);
    }
    
    void UmkiField::debug()
    {
        QList<QGraphicsItem*> items=this->items();
        for(int i=0;i<items.count();i++)
            qDebug()<<"Scene debug"<<items[i];
    }
    
    void UmkiField::createUmki()
    {
        umki=new SimpleUmki();
        this->addItem(umki);
        umki->setPos(upLeftCorner(robo_y,robo_x).x(),upLeftCorner(robo_y,robo_x).y());
        connect(umki,SIGNAL(moved(QPointF)),this,SLOT(roboMoved(QPointF)));
    }
    
    void UmkiField::reverseUpWall(int row, int col)
    {
        if(!getFieldItem(row,col)->hasUpSep()){
            return;qDebug("!UpSep");
        }
        if(!getFieldItem(row,col)->canUp())
        {
            getFieldItem(row,col)->removeUpWall();
            qDebug("removeUp");
        } else {
            getFieldItem(row,col)->setUpWall(new QGraphicsLineItem(upLeftCorner(row,col).x(),
                                                                   upLeftCorner(row,col).y(),
                                                                   upLeftCorner(row,col).x()+fieldSize,
                                                                   upLeftCorner(row,col).y()),StLine);
        }
        wasEdit=true;
    }
    
    void UmkiField::reverseDownWall(int row, int col)
    {
        if(!getFieldItem(row,col)->hasDownSep()) {
            return;
        }
        if(!getFieldItem(row,col)->canDown())
        {
            getFieldItem(row,col)->removeDownWall();
        }
        else {
            getFieldItem(row,col)->setDownWall(new QGraphicsLineItem(upLeftCorner(row,col).x(),
                                                                     upLeftCorner(row,col).y()+fieldSize,
                                                                     upLeftCorner(row,col).x()+fieldSize,
                                                                     upLeftCorner(row,col).y()+fieldSize),StLine);
        }
        wasEdit=true;
    }
    
    void UmkiField::reverseLeftWall(int row, int col)
    {
        if(!getFieldItem(row,col)->hasLeftSep())
            return;
        if(!getFieldItem(row,col)->canLeft())
        {
            getFieldItem(row,col)->removeLeftWall();
        }
        else {
            getFieldItem(row,col)->setLeftWall(new QGraphicsLineItem(upLeftCorner(row,col).x(),
                                                                     upLeftCorner(row,col).y(),
                                                                     upLeftCorner(row,col).x(),
                                                                     upLeftCorner(row,col).y()+fieldSize),StLine);
        }
        wasEdit=true;
    }
    
    void UmkiField::reverseRightWall(int row, int col)
    {
        if(!getFieldItem(row,col)->hasRightSep())
            return;
        if(!getFieldItem(row,col)->canRight())
        {
            getFieldItem(row,col)->removeRightWall();
        }
        else {
            getFieldItem(row,col)->setRightWall(new QGraphicsLineItem(upLeftCorner(row,col).x()+fieldSize,
                                                                      upLeftCorner(row,col).y(),
                                                                      upLeftCorner(row,col).x()+fieldSize,
                                                                      upLeftCorner(row,col).y()+fieldSize),StLine);
        }
        wasEdit=true;
    }
    
    
    
    void UmkiField::showUpWall(int row, int col)
    {
       
        this->removeItem(showWall);
        delete showWall;
        if(mode>NEDIT_MODE)
          {
              showWall=new QGraphicsLineItem(0,0,0,0);
              this->addItem(showWall);
              return;
              
          }
        showWall=new QGraphicsLineItem(upLeftCorner(row,col).x(),
                                                                   upLeftCorner(row,col).y(),
                                                                   upLeftCorner(row,col).x()+fieldSize,
                                                                   upLeftCorner(row,col).y());
        
        showWall->setPen(showLine);
        showWall->setZValue(200);

        this->addItem(showWall);
    qDebug()<<"Show up wall";
    }
    
    void UmkiField::showDownWall(int row, int col)
    {
        this->removeItem(showWall);
        delete showWall;
        if(mode>NEDIT_MODE)
        {
            showWall=new QGraphicsLineItem(0,0,0,0);
            this->addItem(showWall);
            return;
        }
        showWall=new QGraphicsLineItem(upLeftCorner(row,col).x(),
                                                                     upLeftCorner(row,col).y()+fieldSize,
                                                                     upLeftCorner(row,col).x()+fieldSize,
                                                                     upLeftCorner(row,col).y()+fieldSize);
        
        showWall->setPen(showLine);
        showWall->setZValue(200);
        
        this->addItem(showWall);
       
    }
    
    void UmkiField::showLeftWall(int row, int col)
    {
        this->removeItem(showWall);
       if(showWall) delete showWall;
        if(mode>NEDIT_MODE)
        {
            showWall=new QGraphicsLineItem(0,0,0,0);
            this->addItem(showWall);
            return;
        };
        showWall=new QGraphicsLineItem(upLeftCorner(row,col).x(),
                                                                     upLeftCorner(row,col).y(),
                                                                     upLeftCorner(row,col).x(),
                                                                     upLeftCorner(row,col).y()+fieldSize);
      
       
        showWall->setPen(showLine);
        showWall->setZValue(200);
        
        this->addItem(showWall);
    }
    
    void UmkiField::showRightWall(int row, int col)
    {
        this->removeItem(showWall);
        delete showWall;
        
        if(mode>NEDIT_MODE)
        {
            showWall=new QGraphicsLineItem(0,0,0,0);
            this->addItem(showWall);
            return;
            
        };
        showWall=new QGraphicsLineItem(upLeftCorner(row,col).x()+fieldSize,
                                                                      upLeftCorner(row,col).y(),
                                                                      upLeftCorner(row,col).x()+fieldSize,
                                                                      upLeftCorner(row,col).y()+fieldSize);
        
        showWall->setPen(showLine);
        showWall->setZValue(200);
        
        this->addItem(showWall);
    }
    

    
    
    void UmkiField::reverseColor(int row, int col)
    {
        if(getFieldItem(row,col)->isColored())
        {
            getFieldItem(row,col)->removeColor();
        }else
        {
            getFieldItem(row,col)->setColorRect(
                                                new QGraphicsRectItem(upLeftCorner(row,col).x(),
                                                                      upLeftCorner(row,col).y(),
                                                                      fieldSize,
                                                                      fieldSize));
        };
        if(mode!=NORMAL_MODE)wasEdit=true;
    }
    
    void UmkiField::reverseColorCurrent()
    {
        reverseColor(robo_y,robo_x);
        if(mode!=NORMAL_MODE)wasEdit=true;
    }
    
    void UmkiField::reverseMark(int row, int col)
    {
        if(getFieldItem(row,col)->mark)
        {
            getFieldItem(row,col)->removeMark();
        }
        else {
            getFieldItem(row,col)->mark=true;
            getFieldItem(row,col)->showCharMark(upLeftCorner(row,col).x(),upLeftCorner(row,col).y(),fieldSize);
        }
        wasEdit=true;
    }
    
    void UmkiField::setUmkiPos(int roboX, int roboY)
    {
        robo_x=roboX;
        robo_y=roboY;
    }
    

    
    void UmkiField::roboMoved(QPointF pos)
    {
        int roboRow=pos.y() / FIELD_SIZE_SMALL;
        int roboCol=pos.x() / FIELD_SIZE_SMALL;
        if(roboRow>=rows())roboRow=rows()-1;
        if(roboRow<0)roboRow=0;
        if(roboCol>=columns())roboCol=columns()-1;
        if(roboCol<0)roboCol=0;
        umki->setPos(upLeftCorner(roboRow,roboCol).x(),upLeftCorner(roboRow,roboCol).y());
        robo_x=roboCol;robo_y=roboRow;
        wasEdit=true;
    };
    
    void UmkiField::UpdateColors()
    {
        LineColor = QColor(sett->value("LineColor","#C8C800").toString());
        WallColor=QColor(sett->value("WallColor","#C8C800").toString());
        EditColor=QColor(sett->value("EditColor","#00008C").toString());
        NormalColor=QColor(sett->value("NormalColor","#289628").toString());
        
        destroyNet();
        destroyField();
        drawNet();
        drawField(FIELD_SIZE_SMALL);
    };
    
    void UmkiField::drawNet()
    {
        QPen Pen,PenError;
        int ddx = 2+FIELD_SIZE_SMALL/2;
        qDebug()<<"Bort "<<BORT;
        int infin;
        
        
        
        Pen = QPen(LineColor,1);
        PenError = QPen(LineColor,1);
        infin = 5*BORT+10;
 
       // printf("Columns:%d",col_debug);
        for (int i = -1; i < columns(); i++) //Vertikalnie linii
        {
            setka.append(this->addLine(i * FIELD_SIZE_SMALL+ddx+FIELD_SIZE_SMALL/2+2 , -FIELD_SIZE_SMALL , i * FIELD_SIZE_SMALL+ddx+2+FIELD_SIZE_SMALL/2,(rows()+1) * FIELD_SIZE_SMALL,Pen ));
            setka.last()->setZValue(0.5);
        }
        
        for (int i = -1; i < rows(); i++)//Horizontalnie linii
        {
            setka.append(this->addLine(-FIELD_SIZE_SMALL, i * FIELD_SIZE_SMALL+ddx-1+FIELD_SIZE_SMALL/2 ,(columns()+1 )* FIELD_SIZE_SMALL, i * FIELD_SIZE_SMALL+ddx-1+FIELD_SIZE_SMALL/2,Pen));
            setka.last()->setZValue(0.5);
        }
       
    };
    qreal UmkiField::m_height()
    {
        return FIELD_SIZE_SMALL*  rows(); 
    }
    qreal UmkiField::m_width()
    {
        return FIELD_SIZE_SMALL*  rows(); 
    }
    /**
     * Загрузка обстановки из файла, отображение не производится.
     * @param fileName Имя файла
     * @return Код ошибки
     * 1 - Ошибка чтения файла
     * 2 - Пустой файл
     * 3 - Ошибка чтения размеров обстановки
     * 4 - Неверные размеры поля
     * 5 - Пустя строка
     * 6 - Неверное положение умкиа
     * 0< - Ошибка в строке
     * 10 - Ошибки основного прогона
     */
    int UmkiField::loadFromDataStream(QIODevice * l_File)
    {
        
        //destroyField();
     
        
        
        QString tmp = "";
 
        
        

        wasEdit=false;
        
        
        
        int NStrok;
        NStrok = 0;
        QString l_String;
        //	long l_Err;
        int CurX,CurY;
        int SizeX, SizeY;
        destroyField();
        // Тестовый прогон
      
        
        
        
        // 1 stroka - razmery polya
        tmp = l_File->readLine();
        //QMessageBox::information( 0, "", tmp, 0,0,0);
        
        
        if (tmp.isNull()||tmp.isEmpty())
        {
            l_File->close();
            
            return 2;
        }
        
        //QMessageBox::information( 0, "", tmp, 0,0,0);
        
        while (tmp.left(1) == ";" || tmp == "")
        {
            tmp = l_File->readLine();
            NStrok++;
            if (tmp.isNull())
            {
                return 1;
            }
        }
        tmp = tmp.simplified();
        QStringList l_List = tmp.split(' ');
        
        if (l_List.count() != 2)
        {
            l_File->close();
            
            
            return 3;
        }
        
        SizeX = (l_List[0]).toInt();
        SizeY = (l_List[1]).toInt();
        
        if ( (SizeX<= 0) || (SizeY <= 0) )
        {
            return 4;
        }
        //            field.destroyField();
        // field.createField(l_List[0].toInt(),l_List[1].toInt());
        
        // Вторая строка - положение умкиа
        
        tmp = l_File->readLine();
        
        
        
        if (tmp.isNull())
        {
            l_File->close();
            
            return 5;
        }
        
        
        
        while (tmp.left(1) == ";" || tmp == "")
        {
            tmp = l_File->readLine();
            NStrok++;
            if (tmp.isNull())
            {
               l_File->close();
                
                return 5;
            }
        }
        tmp = tmp.simplified();
        l_List = tmp.split(' ');
        
        // koordinaty umkia
        // proverka
        if ((l_List[0]).toInt() < 0 || (l_List[1]).toInt() < 0)
        {
            
            
            l_File->close();return 6;
        }
        
        if ((l_List[0]).toInt() > SizeX || (l_List[1]).toInt() > SizeY )
        {
            
            l_File->close(); return 6;
        }
        
        
        //	m_DefaultSett = l_Sett;
        
        while (!l_File->atEnd())
        {
            //l_Err = l_File.readLine(l_String, 255);
            tmp = QString::fromUtf8(l_File->readLine());
            NStrok++;
            if (tmp.isNull())
            {
                
                return 5;
            }
            if (tmp.left(1) == ";" || tmp == "")
            {
                continue;
            }
            tmp = tmp.simplified();
            l_List = tmp.split(' ');
            if (l_List.count() == 0)continue;
            
            if (l_List.count() > 9 )
            {
                
                l_File->close();
                return -NStrok;
            }
            if(l_List.count()<6)
            {
                l_File->close();
                qDebug("N Lexem<6");
                return -NStrok;
            };
            bool ok;
            CurX = l_List[0].toInt(&ok);
            if(!ok)
            {
                l_File->close();
                qDebug("Bad cur X<6");
                return -NStrok;
            };
            
            CurY = l_List[1].toInt(&ok);
            
            if(!ok){
                l_File->close();
                qDebug("Bad curY <6");
                return -NStrok;
            };
            
            if (CurX < 0 || CurX > SizeX || CurY < 0 || CurY > SizeY)
            {
                
                l_File->close(); return -NStrok;
            }
            
            if (l_List[4].toFloat() < 0)
            {
                
                l_File->close(); return -NStrok;
            }
            
            
            if (l_List[5].toFloat() < MIN_TEMP)
            {
                
               l_File->close(); return -NStrok;
            }
            
            
            if (l_List.count() >= 7)
            {
                
                QString tmp1 = l_List[6];
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    
                    l_File->close(); return -NStrok;
                }
                
                
            }
            
            
            if (l_List.count() >= 8)
            {
                
                QString tmp1 = l_List[7];
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    l_File->close(); return -NStrok;
                }
                
                
            }
            
        }
        l_File->close();
        
        //реальный прогон
        //destroyField();
        
        if  (!l_File->open(QIODevice::ReadOnly))
        {
            
            return 10;
        }
        
        
        
        // 1 stroka - razmery polya
        tmp = l_File->readLine();
        
        if (tmp.isNull())
        {
            l_File->close();
            
            return 10;
        }
        
        
        while (tmp.left(1) == ";" || tmp == "")
        {
            tmp = QString::fromUtf8(l_File->readLine());
            NStrok++;
            if (tmp.isNull())
            {
                l_File->close();
                
                return 10;
            }
        }
        tmp = tmp.simplified();
        l_List = tmp.split(' ');
        
        if (l_List.count() != 2)
        {
            l_File->close();
            
            return -NStrok;
        }
        
        SizeX = (l_List[0]).toInt();
        SizeY = (l_List[1]).toInt();
        // 	 //NEW ROBO CODE
        createField(SizeY,SizeX);
        
        //END
        if ((l_List[0]).toInt() <= 0 || (l_List[1]).toInt() <= 0)
        {
            
            l_File->close();
            return - NStrok;
        }
        
        
        // Вторая строка - положение умкиа
        
        tmp = l_File->readLine();
        
        
        
        if (tmp.isNull())
        {
            l_File->close();
            
            return 10;
        }
        
        
        
        while (tmp.left(1) == ";" || tmp == "")
        {
            tmp = l_File->readLine();
            NStrok++;
            if (tmp.isNull())
            {
                l_File->close();
                
                return 10;
            }
        }
        tmp = tmp.simplified();
        l_List = tmp.split(' ');
        
        // koordinaty umkia
        
        if ((l_List[0]).toInt() < 0 || (l_List[1]).toInt() < 0)
        {
            
           l_File->close();return - NStrok;
        }
        
        if ((l_List[0]).toInt() > SizeX || (l_List[1]).toInt() > SizeY )
        {
            
            l_File->close(); return - NStrok;
        }
        
        robo_x = (l_List[0]).toInt();
        robo_y = (l_List[1]).toInt();
        
        //InitialX = m_x;
        //InitialY = m_y;
        
        
        
        
        //	delete []m_FieldDubl;
        
        
        
        while (!l_File->atEnd())
        {
            tmp = QString::fromUtf8(l_File->readLine());
            NStrok++;
            if (tmp.isNull())
            {
                
                l_File->close();
                return 10;
            }
            if (tmp.left(1) == ";" || tmp == "")
            {
                continue;
            }
            tmp = tmp.simplified();
            l_List = tmp.split(' ');
            if (l_List.count() == 0)continue;
            
            if (l_List.count() > 9)
            {
                
                l_File->close();
                return -NStrok;
            }
            CurX = l_List[0].toInt();
            CurY = l_List[1].toInt();
            if (CurX < 0 || CurX > SizeX || CurY < 0 || CurY > SizeY)
            {
                
                l_File->close(); return -NStrok;
            }
            // TODO STENI
            if (getFieldItem(CurY, CurX))
                getFieldItem(CurY,CurX)->setWalls((l_List[2]).toInt());
            
            //		int ix = (l_List[0]).toInt();
            //		int iy = (l_List[1]).toInt();
            
            if (!((l_List[3]).toInt() == 0))
            {
                getFieldItem(CurY,CurX)->IsColored = true;
                // //QMessageBox::information( 0, "","test1" , 0,0,0);
            }
            else {
                if (getFieldItem(CurY,CurX))
                    getFieldItem(CurY,CurX)->IsColored = false;
            }
            qreal radiation = (l_List[4].replace(",",".")).toDouble();
            if (getFieldItem(CurY,CurX))
                getFieldItem(CurY,CurX)->radiation=radiation;
            
            if (l_List[4].toFloat() < 0)
            {
                
                l_File->close(); return -NStrok;
            }
            qreal temperature = (l_List[5].replace(",",".")).toDouble();
            if (getFieldItem(CurY,CurX))
                getFieldItem(CurY,CurX)->temperature=temperature;
            
            if (l_List[5].toFloat() < MIN_TEMP)
            {
                
                l_File->close(); return -NStrok;
            }
            
            
            
            if (l_List.count() >= 7)
            {
                
                QString tmp1 = l_List[6];
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    
                    l_File->close(); return -NStrok;
                }
                //qDebug()<<QString::fromUtf8("Тест Up:")<<tmp1[0];
                if(tmp1[0]!='$') {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->upChar = tmp1[0];
                }
                else {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->upChar = ' ' ;
                }
            }
            else
            {
                if (getFieldItem(CurY,CurX))
                    getFieldItem(CurY,CurX)->upChar = ' ' ;
            }
            
            
            
            if (l_List.count() >= 8)
            {
                
                QString tmp1 = l_List[7];
                
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    
                    l_File->close(); return -NStrok;
                }
                //qDebug()<<QString::fromUtf8("Тест Down:")<<tmp1[0];
                if(tmp1[0]!='$') {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->downChar = tmp1[0];
                }
                else {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->downChar = ' ' ;
                }
            }
            else
            {
                if (getFieldItem(CurY,CurX))
                    getFieldItem(CurY,CurX)->downChar = ' ' ;
            }
            
            
            
            if (l_List.count() >= 9)
            {
                
                QString tmp1 = l_List[8];
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    
                    l_File->close(); return -NStrok;
                }
                if(tmp1[0]=='1') {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->mark = true;
                }
                else {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->mark = false ;
                }
            }
            else
            {
                if (getFieldItem(CurY,CurX))
                    getFieldItem(CurY,CurX)->mark = false ;
            }
            
            
            
            
            
            
        }
        
       l_File->close();
        
        
        
        
        
        wasEdit=false;
        
        
        //umki->setZValue(100);
        return(0);
        
        

    }
    
    /**
     * Загрузка обстановки из файла, отображение не производится.
     * @param fileName Имя файла
     * @return Код ошибки
     * 1 - Ошибка чтения файла
     * 2 - Пустой файл
     * 3 - Ошибка чтения размеров обстановки
     * 4 - Неверные размеры поля
     * 5 - Пустя строка
     * 6 - Неверное положение умкиа
     * 0< - Ошибка в строке
     * 10 - Ошибки основного прогона
     */
    int UmkiField::loadFromFile(QString fileName)
    {
        
        //destroyField();
        
        QFileInfo fi(fileName);
        QString name = fi.fileName();
        
        QString Title = QString::fromUtf8("Умки - ") + name;
        
        
        QString tmp = "";
        QString ctmp;
        
        
        QFile l_File(fileName);
        
        
        
        
        int NStrok;
        NStrok = 0;
        QString l_String;
        //	long l_Err;
        int CurX,CurY;
        int SizeX, SizeY;
       
        // Тестовый прогон
        
        if  (!l_File.open(QIODevice::ReadOnly))
        {
            
            return 1;
        }
        
        
        
        // 1 stroka - razmery polya
        tmp = l_File.readLine();
        //QMessageBox::information( 0, "", tmp, 0,0,0);
        
        
        if (tmp.isNull()||tmp.isEmpty())
        {
            l_File.close();
            
            return 2;
        }
        
        //QMessageBox::information( 0, "", tmp, 0,0,0);
        
        while (tmp.left(1) == ";" || tmp == "")
        {
            tmp = l_File.readLine();
            NStrok++;
            if (tmp.isNull())
            {
                return 1;
            }
        }
        tmp = tmp.simplified();
        QStringList l_List = tmp.split(' ');
        
        if (l_List.count() != 2)
        {
            l_File.close();
            
            
            return 3;
        }
        
        SizeX = (l_List[0]).toInt();
        SizeY = (l_List[1]).toInt();
        
        if ( (SizeX<= 0) || (SizeY <= 0) )
        {
            return 4;
        }
        //            field.destroyField();
        // field.createField(l_List[0].toInt(),l_List[1].toInt());
        
        // Вторая строка - положение умкиа
        
        tmp = l_File.readLine();
        
        
        
        if (tmp.isNull())
        {
            l_File.close();
            
            return 5;
        }
        
        
        
        while (tmp.left(1) == ";" || tmp == "")
        {
            tmp = l_File.readLine();
            NStrok++;
            if (tmp.isNull())
            {
                l_File.close();
                
                return 5;
            }
        }
        tmp = tmp.simplified();
        l_List = tmp.split(' ');
        
        // koordinaty umkia
        // proverka
        if ((l_List[0]).toInt() < 0 || (l_List[1]).toInt() < 0)
        {
            
            
            l_File.close();return 6;
        }
        
        if ((l_List[0]).toInt() > SizeX || (l_List[1]).toInt() > SizeY )
        {
            
            l_File.close(); return 6;
        }
        
        
        //	m_DefaultSett = l_Sett;
        
        while (!l_File.atEnd())
        {
            //l_Err = l_File.readLine(l_String, 255);
            tmp = QString::fromUtf8(l_File.readLine());
            NStrok++;
            if (tmp.isNull())
            {
                
                return 5;
            }
            if (tmp.left(1) == ";" || tmp == "")
            {
                continue;
            }
            tmp = tmp.simplified();
            l_List = tmp.split(' ');
            if (l_List.count() == 0)continue;
            
            if (l_List.count() > 9 )
            {
                
                l_File.close();
                return -NStrok;
            }
            if(l_List.count()<6)
            {
                l_File.close();
                qDebug("N Lexem<6");
                return -NStrok;
            };
            bool ok;
            CurX = l_List[0].toInt(&ok);
            if(!ok)
            {
                l_File.close();
                qDebug("Bad cur X<6");
                return -NStrok;
            };
            
            CurY = l_List[1].toInt(&ok);
            
            if(!ok){
                l_File.close();
                qDebug("Bad curY <6");
                return -NStrok;
            };
            
            if (CurX < 0 || CurX > SizeX || CurY < 0 || CurY > SizeY)
            {
                
                l_File.close(); return -NStrok;
            }
            
            if (l_List[4].toFloat() < 0)
            {
                
                l_File.close(); return -NStrok;
            }
            
            
            if (l_List[5].toFloat() < MIN_TEMP)
            {
                
                l_File.close(); return -NStrok;
            }
            
            
            if (l_List.count() >= 7)
            {
                
                QString tmp1 = l_List[6];
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    
                    l_File.close(); return -NStrok;
                }
                
                
            }
            
            
            if (l_List.count() >= 8)
            {
                
                QString tmp1 = l_List[7];
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    l_File.close(); return -NStrok;
                }
                
                
            }
            
        }
        l_File.close();
         destroyField();
        //реальный прогон
        //destroyField();
        
        if  (!l_File.open(QIODevice::ReadOnly))
        {
            
            return 10;
        }
        
        
        
        // 1 stroka - razmery polya
        tmp = l_File.readLine();
        
        if (tmp.isNull())
        {
            l_File.close();
            
            return 10;
        }
        
        
        while (tmp.left(1) == ";" || tmp == "")
        {
            tmp = QString::fromUtf8(l_File.readLine());
            NStrok++;
            if (tmp.isNull())
            {
                l_File.close();
                
                return 10;
            }
        }
        tmp = tmp.simplified();
        l_List = tmp.split(' ');
        
        if (l_List.count() != 2)
        {
            l_File.close();
            
            return -NStrok;
        }
        
        SizeX = (l_List[0]).toInt();
        SizeY = (l_List[1]).toInt();
        // 	 //NEW ROBO CODE
        createField(SizeY,SizeX);
        
        //END
        if ((l_List[0]).toInt() <= 0 || (l_List[1]).toInt() <= 0)
        {
            
            l_File.close();
            return - NStrok;
        }
        
        
        // Вторая строка - положение умки
        
        tmp = l_File.readLine();
        
        
        
        if (tmp.isNull())
        {
            l_File.close();
            
            return 10;
        }
        
        
        
        while (tmp.left(1) == ";" || tmp == "")
        {
            tmp = l_File.readLine();
            NStrok++;
            if (tmp.isNull())
            {
                l_File.close();
                
                return 10;
            }
        }
        tmp = tmp.simplified();
        l_List = tmp.split(' ');
        
        // koordinaty umkia
        
        if ((l_List[0]).toInt() < 0 || (l_List[1]).toInt() < 0)
        {
            
            l_File.close();return - NStrok;
        }
        
        if ((l_List[0]).toInt() > SizeX || (l_List[1]).toInt() > SizeY )
        {
            
            l_File.close(); return - NStrok;
        }
        
        robo_x = (l_List[0]).toInt();
        robo_y = (l_List[1]).toInt();
        
        //InitialX = m_x;
        //InitialY = m_y;
        
        
        
        
        //	delete []m_FieldDubl;
        
        
        
        while (!l_File.atEnd())
        {
            tmp = QString::fromUtf8(l_File.readLine());
            NStrok++;
            if (tmp.isNull())
            {
                
                l_File.close();
                return 10;
            }
            if (tmp.left(1) == ";" || tmp == "")
            {
                continue;
            }
            tmp = tmp.simplified();
            l_List = tmp.split(' ');
            if (l_List.count() == 0)continue;
            
            if (l_List.count() > 9)
            {
                
                l_File.close();
                return -NStrok;
            }
            CurX = l_List[0].toInt();
            CurY = l_List[1].toInt();
            if (CurX < 0 || CurX > SizeX || CurY < 0 || CurY > SizeY)
            {
                
                l_File.close(); return -NStrok;
            }
            // TODO STENI
            if (getFieldItem(CurY, CurX))
                getFieldItem(CurY,CurX)->setWalls((l_List[2]).toInt());
            
            //		int ix = (l_List[0]).toInt();
            //		int iy = (l_List[1]).toInt();
            
            if (!((l_List[3]).toInt() == 0))
            {
                getFieldItem(CurY,CurX)->IsColored = true;
                // //QMessageBox::information( 0, "","test1" , 0,0,0);
            }
            else {
                if (getFieldItem(CurY,CurX))
                    getFieldItem(CurY,CurX)->IsColored = false;
            }
            qreal radiation = (l_List[4].replace(",",".")).toDouble();
            if (getFieldItem(CurY,CurX))
                getFieldItem(CurY,CurX)->radiation=radiation;
            
            if (l_List[4].toFloat() < 0)
            {
                
                l_File.close(); return -NStrok;
            }
            qreal temperature = (l_List[5].replace(",",".")).toDouble();
            if (getFieldItem(CurY,CurX))
                getFieldItem(CurY,CurX)->temperature=temperature;
            
            if (l_List[5].toFloat() < MIN_TEMP)
            {
                
                l_File.close(); return -NStrok;
            }
            
            
            
            if (l_List.count() >= 7)
            {
                
                QString tmp1 = l_List[6];
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    
                    l_File.close(); return -NStrok;
                }
                //qDebug()<<QString::fromUtf8("Тест Up:")<<tmp1[0];
                if(tmp1[0]!='$') {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->upChar = tmp1[0];
                }
                else {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->upChar = ' ' ;
                }
            }
            else
            {
                if (getFieldItem(CurY,CurX))
                    getFieldItem(CurY,CurX)->upChar = ' ' ;
            }
            
            
            
            if (l_List.count() >= 8)
            {
                
                QString tmp1 = l_List[7];
                
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    
                    l_File.close(); return -NStrok;
                }
                //qDebug()<<QString::fromUtf8("Тест Down:")<<tmp1[0];
                if(tmp1[0]!='$') {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->downChar = tmp1[0];
                }
                else {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->downChar = ' ' ;
                }
            }
            else
            {
                if (getFieldItem(CurY,CurX))
                    getFieldItem(CurY,CurX)->downChar = ' ' ;
            }
            
            
            
            if (l_List.count() >= 9)
            {
                
                QString tmp1 = l_List[8];
                //dlina lexemy dolzna ravnyatsa 1
                if (!(tmp1.length() == 1))
                {
                    
                    l_File.close(); return -NStrok;
                }
                if(tmp1[0]=='1') {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->mark = true;
                }
                else {
                    if (getFieldItem(CurY,CurX))
                        getFieldItem(CurY,CurX)->mark = false ;
                }
            }
            else
            {
                if (getFieldItem(CurY,CurX))
                    getFieldItem(CurY,CurX)->mark = false ;
            }
            
            
            
            
            
            
        }
        
        l_File.close();
        
        
        
        qDebug() << "File " << fileName ;
        wasEdit=false;
        
        
        //umki->setZValue(100);
        return(0);
        
        
        
    };
    
    int UmkiField::saveToFile(QString fileName)
    {
        QFileInfo fi(fileName);
        QString name = fi.fileName();
        
        qDebug()<<"NewUmki Save file: "<<fileName;
        //QString Title = QString::fromUtf8("Умки - ") + name;
        
        
        QChar Bukva;
        char ctmp[200];
        QFile l_File(fileName);
        if  (!l_File.open(QIODevice::WriteOnly))
        {
            return 1;
        }
        
        l_File.write("; Field Size: x, y\n");
        
        //QString l_String;
        
        sprintf(ctmp,"%i %i\n", columns(), rows());
        l_File.write(ctmp);
        l_File.write("; Umki position: x, y\n");
        sprintf(ctmp,"%i %i\n", robo_x, robo_y);
        l_File.write(ctmp );
        l_File.write("; A set of special Fields: x, y, Wall, Color, Radiation, Temperature, Symbol, Symbol1, Point\n");
        
        for (int i = 0; i < rows(); i++)
        {
            for (int j = 0; j < columns(); j++)
            {
                
                Bukva = getFieldItem(i,j)->upChar;
                if(Bukva==' ')Bukva='$';
                qDebug()<<QString::fromUtf8("Буква")<<Bukva;
                QChar cc;
                cc = Bukva;
                
                
                Bukva = getFieldItem(i,j)->downChar;
                if(Bukva==' '){Bukva='$';qDebug()<<QString::fromUtf8("Буквы нет");}
                else qDebug()<<QString::fromUtf8("Буква ")<<Bukva;
                
                QChar cc1 = Bukva;
                
                
                char cc2[2];
                cc2[0] = 0;
                cc2[1] = 0;
                
                if(getFieldItem(i,j)->mark)cc2[0] = '1';
                //char cc = 'g';
                if (!getFieldItem(i, j)->emptyCell())
                {
                    qDebug()<<" i:"<<i << " j:"<< j << " walls:"<<getFieldItem(i, j)->wallByte();
                    sprintf(ctmp,"%i %i %i %i %f %f ", j, i, getFieldItem(i, j)->wallByte(), getFieldItem(i, j)->IsColored, getFieldItem(i, j)->radiation, getFieldItem(i,j)->temperature);
                    QString toWrite=QString(ctmp)+cc+" "+cc1+" "+cc2+"\n";
                    l_File.write(toWrite.toUtf8());
                    qDebug()<<"ROBOT:WRITE 2 FILE";
                }
            }
        }
        l_File.write( "; End Of File\n");
        
        l_File.close();
        if (fi.exists())
        {
            //QMessageBox::information( 0, "", QString::fromUtf8("файл записан"), 0,0,0);
            
        }
        else
        {
            QMessageBox::information( 0, "", QString::fromUtf8("Файл не записан - попробуйте снова!"), 0,0,0);
            return -1;
        }
        
        //ToDubl();
        wasEdit=false;
        return 0;
        
    };
    
    bool UmkiField::stepUp()
    {
//        if (m_umki && !property("fromPult").toBool())
//            m_umki->showHideWindow(true);
        
        // setProperty("fromPult", false);
        
        if(getFieldItem(robo_y,robo_x)->canUp())
        {
            umki->setPos( QPointF(umki->pos().x(),
                                   umki->pos().y() - fieldSize));
            
            robo_y--;
            return true;
        }else return false;
    };
    
    bool UmkiField::stepDown()
    {
//        if (m_umki && !property("fromPult").toBool())
//            m_umki->showHideWindow(true);
        
        // setProperty("fromPult", false);
        
        if(getFieldItem(robo_y,robo_x)->canDown())
        {
            umki->moveBy(0,fieldSize);
            robo_y++;
            return true;
        }else return false;
    };
    
    bool UmkiField::stepLeft()
    {
//        if (m_umki && !property("fromPult").toBool())
//            m_umki->showHideWindow(true);
        // setProperty("fromPult", false);
        
        if(getFieldItem(robo_y,robo_x)->canLeft())
        {
            umki->setPos( QPointF(umki->pos().x()-fieldSize,
                                   umki->pos().y()));
            robo_x--;
            return true;
        }else return false;
    };
    
    bool UmkiField::stepRight()
    {
//        if (m_umki && !property("fromPult").toBool())
//            m_umki->showHideWindow(true);
        // setProperty("fromPult", false);
        
        if(getFieldItem(robo_y,robo_x)->canRight())
        {
            umki->moveBy(fieldSize,0);
            robo_x++;
            return true;
        }else return false;
    };
    
    
    /**
     * Обработка событий нажатий кнопок мыши, показ диалога редактирования *клетки
     * @param mouseEvent
     */
    void UmkiField::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
    {
        qDebug()<<" Field Mouse event mode:"<<mode;
        
        if(mode==0)
        {
            pressed=true;
            oldRect=sceneRect();
            perssX=mouseEvent->pos().x();
            pressY=mouseEvent->pos().y();
              mouseEvent->accept();
            return;
        };
        
        
        //qDebug()<<" Edit mouse press event";
        QPointF scenePos=mouseEvent->scenePos();
        float rc=float(scenePos.y())/float(fieldSize);
        if(rc<0)rc=-1;
        float cc=float(scenePos.x()-3)/float(fieldSize);
        if(cc<0)cc=-1;
        int rowClicked=rc;
        int colClicked=cc;
       // qDebug()<<"RC:"<<rowClicked<<"CC:"<<colClicked<<" sc pos y:"<<scenePos.y()<<" scenePos.x()"<<scenePos.x()<<"";
        if(mode==TEXT_MODE)
        { 
            if(rowClicked>rows() || colClicked>columns() ||rowClicked<0 || colClicked<0)//clik mimio polya
            {
            return;
            }
            pressD=false;
            if(keyCursor)this->removeItem(keyCursor);
            clickCell=QPair<int,int>(rowClicked,colClicked);
            if((scenePos.y()-rowClicked*fieldSize)>fieldSize/2)
            {
                pressD=true;
                showCursorDown(rowClicked,colClicked);
            }
             else showCursorUp(rowClicked,colClicked);
            update();
            return;
        }
        if(mode==RAD_MODE)//if radiation || temp edit mode
        {   if(rowClicked>rows() || colClicked>columns() ||rowClicked<0 || colClicked<0)//clik mimio polya
            {
            //radSpinBox->hide();
            return;
            }
            qDebug()<<"RAD MODE CLick";
            if(clickCell!=QPair<int,int>(rowClicked,colClicked))
             {
               if(radSpinBox->isVisible())
                   
               {    clickCell=QPair<int,int>(rowClicked,colClicked);
                   qDebug()<<"SET F:"<<clickCell.first<<"SET SEC:"<<clickCell.second;
                   
                   if(!(rowClicked>=rows() || colClicked>=columns() ||rowClicked<0 || colClicked<0))
                   getFieldItem(rowClicked,colClicked)->radiation=radSpinBox->value();
                
               }
                 redrawRTFields();  
                // radSpinBox->hide();
             }
            if(rowClicked>=rows() || colClicked>=columns() ||rowClicked<0 || colClicked<0)//clik mimio polya
            {update();
              //radSpinBox->hide();
             return;
            }
           
   
           QGraphicsView * view=views().first();  //current view
            //QPoint clickViewPos=view->mapFromScene(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
           // qDebug()<<"ROW:"<<rowClicked<<"COL:"<<colClicked;
            //radSpinBox->setValue(getFieldItem(rowClicked,colClicked)->radiation);//set radiation
            view->repaint();
            update();
            return;
        }
        if(mode==TEMP_MODE)
        {
            qDebug()<<"Temp MODE CLick";
            if(rowClicked>=rows() || colClicked>=columns() ||rowClicked<0 || colClicked<0)//clik mimio polya
            {
                //radSpinBox->hide();
                return;
            }
            if(tempSpinBox->isVisible())
                
            {    clickCell=QPair<int,int>(rowClicked,colClicked);
                qDebug()<<"SET F:"<<clickCell.first<<"SET SEC:"<<clickCell.second;
                getFieldItem(rowClicked,colClicked)->temperature=tempSpinBox->value();
                update();
            }
            redrawRTFields();
             QGraphicsView * view=views().first();
            view->repaint();
            update();
            return;
        }
 
        
        bool left,right,up,down;
        left=false;right=false;up=false;down=false;
        int upD=fieldSize,downD=fieldSize,leftD=fieldSize,rightD=fieldSize;
        qreal delta_row=scenePos.y() - rowClicked * fieldSize;
        qreal delta_col=scenePos.x()- colClicked * fieldSize-3;
        qDebug()<<"MousePress event";
       if((rowClicked==rows())&&(scenePos.x()>((fieldSize*(columns())/2) - (wAddRow->size().height()+3)))&&(scenePos.x()<fieldSize*((float)columns()/2)) )
       {
           addRow();
           return;
       }
        if((rowClicked==rows())   && (scenePos.x()>fieldSize*((float)columns()/2))  && (scenePos.x()<fieldSize*((float)columns()/2)+ wAddRow->size().height()+3 ))
        {
            remRow();
            return;
        }
        if(  scenePos.x()>(fieldSize*((float)columns())+7)  && scenePos.y()>((fieldSize*(rows())/2) - (wAddRow->size().width()+1))
           && scenePos.x()<(fieldSize*((float)columns())+7)+(fieldSize/2)+5 && scenePos.y()<((fieldSize*(rows())/2) - (wAddRow->size().width()+1))+fieldSize)
        {
            addCol();
            return;
        }
        if( scenePos.x()>fieldSize*((float)columns())+7 && scenePos.y()>fieldSize*(rows())/2+1 &&
           scenePos.x()<fieldSize*((float)columns())+7+(fieldSize/2)+5 && scenePos.y()<fieldSize*(rows())/2+1+fieldSize)
        {
            remCol();
            return;
            
        }
        QGraphicsScene::mousePressEvent(mouseEvent);
        if(mouseEvent->isAccepted ())return;
        
        
        
        if((rowClicked>rows()-1)||(rowClicked<0))
        {mouseEvent->ignore();QGraphicsScene::mousePressEvent(mouseEvent);return;};
        
        if((colClicked>columns()-1)||(colClicked<0))
        {mouseEvent->ignore();QGraphicsScene::mousePressEvent(mouseEvent);return;};
        
       // qDebug()<<"ScenePos y "<<scenePos.y() <<" sceneposx"<<scenePos.x() << "rowClick:"<<rowClicked << " "<<" colClick:"<<colClicked <<
      //  " delta_row" <<delta_row << " delta_col" << delta_col;
        if(!NEDIT_MODE)return; //don't setup walls,and marks;
        
        if(delta_row<=MAX_CLICK_DELTA){up=true;upD=delta_row;qDebug("UP");};
        
        if(fieldSize-delta_row<=MAX_CLICK_DELTA){down=true;downD=fieldSize-delta_row;};
        
        
        if(delta_col<=MAX_CLICK_DELTA){left=true;leftD=delta_col;};
        
        if(fieldSize-delta_col<=MAX_CLICK_DELTA){right=true;rightD=fieldSize-delta_col;};
        if(mouseEvent->modifiers ()==Qt::ControlModifier) { markMode=false; } else { markMode=true; }
        
        //Углы клетки
        if ((left)&&(up)) {
            if(upD<leftD) {
                left=false;
            }
            else  {
                up=false;
            }
        }
        if((left)&&(down)) {
            if(downD<leftD) {
                left=false;
            }
            else  {
                down=false;
            }
        }
        if((right)&&(up)) {
            if(upD<rightD) {
                right=false;
            }
            else  {
                up=false;
            }
        }
        if((right)&&(down)) {
            if(downD<rightD) {
                right=false;
            }
            else  {
                down=false;
            }
        }
        
        //Ставим стены
        if(up){reverseUpWall(rowClicked,colClicked);qDebug("ReversUP");};
        if(down)reverseDownWall(rowClicked,colClicked);
        if(left)reverseLeftWall(rowClicked,colClicked);
        if(right)reverseRightWall(rowClicked,colClicked);
        if(!up && !down && !right && !left)
        {
            if(markMode)
            {
                reverseColor(rowClicked,colClicked); //Zakraska
                old_cell=QPair<int,int>(rowClicked, colClicked); 
            }
            else //Otmetit tochkoy
            {
                reverseMark(rowClicked,colClicked);
                old_cell=QPair<int,int>(rowClicked, colClicked); 
            };
        };
        wasEdit=true;
//        if(wasEdit)emit was_edit();
    };
    void UmkiField::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
    {
        qDebug()<<"FIELD RELEASE";
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        if(mouseEvent->isAccepted ())
        {
        qDebug()<<"Field is ACC";
           return; 
        }
        if(mode==0)pressed=true;
    };
    void UmkiField::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
    {
       // qDebug()<<"FIELD MOVE";
        if(mode==0)return;
        if(mode!=NEDIT_MODE)return;
        
        QGraphicsScene::mouseMoveEvent(mouseEvent);
     if(!pressed)
     {
         QPointF scenePos=mouseEvent->scenePos();
         int rowClicked=scenePos.y()/fieldSize;  //clicked = mouse cur pos!!
         int colClicked=(scenePos.x()-3)/fieldSize;
         
         bool left,right,up,down;
         left=false;right=false;up=false;down=false;
         int upD=fieldSize,downD=fieldSize,leftD=fieldSize,rightD=fieldSize;
         qreal delta_row=scenePos.y() - rowClicked * fieldSize;
         qreal delta_col=scenePos.x()- colClicked * fieldSize-3;

         
         if((rowClicked>rows()-1)||(rowClicked<0))
         {mouseEvent->ignore();QGraphicsScene::mousePressEvent(mouseEvent);return;};
         
         if((colClicked>columns()-1)||(colClicked<0))
         {mouseEvent->ignore();QGraphicsScene::mousePressEvent(mouseEvent);return;};

      
         if(delta_row<=MAX_CLICK_DELTA){up=true;upD=delta_row;qDebug("UP");};
         
         if(fieldSize-delta_row<=MAX_CLICK_DELTA){down=true;downD=fieldSize-delta_row;};
         
         
         if(delta_col<=MAX_CLICK_DELTA){left=true;leftD=delta_col;};
         
         if(fieldSize-delta_col<=MAX_CLICK_DELTA){right=true;rightD=fieldSize-delta_col;};
         if(mouseEvent->modifiers ()==Qt::ControlModifier) { markMode=false; } else { markMode=true; }
         
         //Углы клетки
         if ((left)&&(up)) {
             if(upD<leftD) {
                 left=false;
             }
             else  {
                 up=false;
             }
         }
         if((left)&&(down)) {
             if(downD<leftD) {
                 left=false;
             }
             else  {
                 down=false;
             }
         }
         if((right)&&(up)) {
             if(upD<rightD) {
                 right=false;
             }
             else  {
                 up=false;
             }
         }
         if((right)&&(down)) {
             if(downD<rightD) {
                 right=false;
             }
             else  {
                 down=false;
             }
         }
         
         //Ставим стены
         if(up && markMode){showUpWall(rowClicked,colClicked);qDebug("ShowUP");};
         if(down && markMode)showDownWall(rowClicked,colClicked);
         if(left && markMode)showLeftWall(rowClicked,colClicked);
         if(right && markMode)showRightWall(rowClicked,colClicked);
         if(!up && !down && !left && !right)
         {
             if((mouseEvent->buttons()==Qt::LeftButton) && (old_cell!=QPair<int,int>(rowClicked, colClicked)&&(!umki->isMoving())))
             {
             if(markMode)
             {
                 
              reverseColor(rowClicked,colClicked); //Zakraska 
                 old_cell=QPair<int,int>(rowClicked, colClicked); 
             }
             else //Otmetit tochkoy
             {
                 reverseMark(rowClicked,colClicked);
             old_cell=QPair<int,int>(rowClicked, colClicked); 
             }
                 
                 
             }
            // qDebug()<<"OldCell!newCell"<<  (old_cell!=QPair<int,int>(rowClicked, colClicked));
         showWall->setVisible(false);
         }
          
         
     }
    };   
    void UmkiField::keyPressEvent ( QKeyEvent * keyEvent )
    {
        if(clickCell==QPair<int,int>(-1,1))return;
   
        redrawRTFields();
        
        if(!(mode==NEDIT_MODE || mode==TEXT_MODE))return;
      
        qDebug()<<"KEY PRESSD"<<keyEvent->text ();
        int rowP=clickCell.first;
        int colP=clickCell.second;
        if(keyEvent->text ().isNull() || keyEvent->text ().isEmpty() || keyEvent->text()=="/n" )return;
        if(!pressD)//Pressed up symbol
        {
        getFieldItem(rowP,colP)->upChar=keyEvent->text ().at(0);
        getFieldItem(rowP,colP)->showUpChar
        (upLeftCorner(rowP,colP).x(),upLeftCorner(rowP,colP).y(),fieldSize);
        }else
        {
            getFieldItem(rowP,colP)->downChar=keyEvent->text ().at(0);
            getFieldItem(rowP,colP)->showDownChar
            (upLeftCorner(rowP,colP).x(),upLeftCorner(rowP,colP).y(),fieldSize);
        }
            wasEdit=true;
    };  

    void UmkiField::setColorFromSett()
    {
         sett=UmkiModule::umkiSettings();
        LineColor = QColor(sett->value("LineColor","#C8C800").toString());
        EditLineColor = QColor(sett->value("LineColorEdit","#C8C800").toString());
        WallColor=QColor(sett->value("WallColor","#C8C800").toString());
        EditColor=QColor(sett->value("EditColor","#00008C").toString());
        NormalColor=QColor(sett->value("NormalColor","#289628").toString());
        QColor gridColor;
        qDebug()<<"Normal color blue"<<NormalColor.blue ();
        if(mode==NORMAL_MODE) {
            gridColor=LineColor;
            this->setBackgroundBrush (QBrush(NormalColor));
            
        }
            else 
            {
                gridColor=EditLineColor;
               this->setBackgroundBrush (QBrush(EditColor)); 
            }
        
        for(int i=0;i<setka.count();i++)
        {
            setka.at(i)->setPen(QPen(gridColor));
        }
    
    }
    
    
    
    void UmkiField::showCellDialog(FieldItm * cellClicked)
    {
        
//        qDebug() << "showCellDialog";
//        QPoint pos = views().first()->pos();
//        pos = views().first()->mapToGlobal(pos);
//        qDebug() << "Pos: " << pos;
//        cellDialog->move(pos);
//        
//        cellDialog->setRowCols(rows(),columns());
//        
//        
//        //       cellDialog->mark->setChecked(cellClicked->mark);
//        
//        
//        //       cellDialog->colored->setChecked(cellClicked->IsColored);
//        
//        QChar upChar,downChar;
//        if(cellClicked->upChar == ' ')upChar='_';else upChar=cellClicked->upChar;
//        if(cellClicked->downChar == ' ')downChar='_';else downChar=cellClicked->downChar;
//        
//        cellDialog->upChar->setText(upChar);
//        cellDialog->downChar->setText(downChar);
//        
//        cellDialog->RadSpinBox->setValue(cellClicked->radiation);
//        cellDialog->TempSpinBox->setValue(cellClicked->temperature);
//        
//        cellDialog->show();
    };
    
    void UmkiField::cellDialogOk()
    {
//        int rowP = cellDialog->row_pos;
//        int colP = cellDialog->col_pos;
//        // qDebug()<<"CellDalog:color:"<<cellDialog->colored->isChecked();
//        //  if(cellDialog->colored->isChecked()!=getFieldItem(rowP,colP)->IsColored)
//        //{reverseColor(rowP,colP);wasEdit=true;};
//        
//        //  if(cellDialog->mark->isChecked()!=getFieldItem(rowP,colP)->mark){reverseMark(rowP,colP);wasEdit=true;};
//        if(cellDialog->upChar->text()!=getFieldItem(rowP,colP)->upChar)
//        {
//            
//            QString tmp=cellDialog->upChar->text();	    if((tmp.length()==0)||(tmp[0]!='_'))getFieldItem(rowP,colP)->removeUpChar();
//            if((tmp.length()==1)&&(tmp[0]!='_')){
//                getFieldItem(rowP,colP)->removeUpChar();
//                
//                
//                
//                getFieldItem(rowP,colP)->upChar=tmp[0];
//                getFieldItem(rowP,colP)->showUpChar
//                (upLeftCorner(rowP,colP).x(),upLeftCorner(rowP,colP).y(),fieldSize);wasEdit=true;};
//        };
//        if(cellDialog->downChar->text()!=getFieldItem(rowP,colP)->downChar)
//        {
//            QString tmp=cellDialog->downChar->text();
//            if((tmp.length()==0)||(tmp[0]!='_'))getFieldItem(rowP,colP)->removeDownChar();
//            if((tmp.length()==1)&&(tmp[0]!='_')){
//                
//                getFieldItem(rowP,colP)->removeDownChar();
//                
//                getFieldItem(rowP,colP)->downChar=tmp[0];
//                getFieldItem(rowP,colP)->showDownChar
//                (upLeftCorner(rowP,colP).x(),upLeftCorner(rowP,colP).y(),fieldSize);wasEdit=true;};
//        };
//        if((getFieldItem(rowP,colP)->radiation!=cellDialog->RadSpinBox->value())||
//           (getFieldItem(rowP,colP)->temperature!=cellDialog->TempSpinBox->value())) wasEdit=true;
//        getFieldItem(rowP,colP)->radiation=cellDialog->RadSpinBox->value();
//        getFieldItem(rowP,colP)->temperature=cellDialog->TempSpinBox->value();
//        /*
//         if(cellDialog->setUmki->isChecked())
//         {
//         robo_y=rowP;
//         robo_x=colP;
//         umki->setPos(upLeftCorner(robo_y,robo_x).x(),upLeftCorner(robo_y,robo_x).y());
//         wasEdit=true;
//         };*/
//        
//        if(wasEdit)emit was_edit();
    };
    void UmkiField::showCursorUp(int row,int col)
    {
        timer->start(500);
        


        
   keyCursor=new QGraphicsLineItem(upLeftCorner(row,col).x()+4,upLeftCorner(row,col).y()+4,upLeftCorner(row,col).x()+4,upLeftCorner(row,col).y()+14);
        keyCursor->setPen(QPen(QColor(Qt::white)));
        keyCursor->setZValue(210);
        this->addItem(keyCursor); 
    };
    void UmkiField::showCursorDown(int row,int col)
    {
        timer->start(500);
        
        if(this->items().indexOf(keyCursor)>-1)this->removeItem(keyCursor);
        
        
        keyCursor=new QGraphicsLineItem(upLeftCorner(row,col).x()+4,upLeftCorner(row,col).y()+18,upLeftCorner(row,col).x()+4,upLeftCorner(row,col).y()+29);
        keyCursor->setPen(QPen(QColor(Qt::white)));
        keyCursor->setZValue(210);
        this->addItem(keyCursor);   
    };
    void UmkiField::timerTic()
    {
        if(mode!=TEXT_MODE){
         if(keyCursor)keyCursor->hide();
            timer->stop();  
        }
      qDebug()<<"TIK!"; 
        if(!keyCursor)
        {
         timer->stop();
            return;
        }
      timer->start(500);
        if(keyCursor->isVisible())keyCursor->hide();
        else keyCursor->show();
    };
    void UmkiField::setFieldItems(QList<QList<FieldItm *> > FieldItems)
    {
        
        Items = QList< QList<FieldItm*> >();
        for (int i=0; i<FieldItems.size(); i++) {
            QList<FieldItm*> row;
            for (int j=0; j<FieldItems[i].size(); j++) {
                row << NULL;
            }
            Items << row;
        }
    }
    
    void UmkiField::setItem(FieldItm *item, uint str, uint stlb)
    {
        if (Items[str][stlb]) {
            delete Items[str][stlb];
        }
        Items[str][stlb]=item;
    }
    
    UmkiField* UmkiField::Clone()
    {
        UmkiField* clone=new UmkiField(0);
        clone->setFieldItems(Items);
        clone->robo_x=robo_x;
        clone->robo_y=robo_y;
        clone->setModeFlag(mode);
        for(int i=0;i<rows();i++)
        {
            for(int j=0;j<columns();j++)
            {
                clone->setItem(getFieldItem(i,j)->Copy(),i,j);
                if(j>0)clone->getFieldItem(i,j)->setLeftsepItem(clone->getFieldItem(i,j-1));
                if(i>0)clone->getFieldItem(i,j)->setUpsepItem(clone->getFieldItem(i-1,j));
            };
        };
        
        return clone;
    };
    
    
    
    void UmkiField::wbMode()
    {
        
        this->setBackgroundBrush (QBrush("white"));
        for(int i=0;i<rows();i++)
        {
            for(int j=0;j<columns();j++)
            {
                getFieldItem(i,j)->wbWalls();
            };
        };
    };
    void UmkiField::colorMode()
    {
         sett=UmkiModule::umkiSettings();
        for(int i=0;i<rows();i++)
        {
            for(int j=0;j<columns();j++)
            {
                getFieldItem(i,j)->colorWalls();
                getFieldItem(i,j)->setTextColor();
            };
        };
        if(mode==0)Color = QColor(40,150,40);//Normal Color
        else Color=QColor(0,0,140);//Edit Color
        this->setBackgroundBrush (QBrush(Color));
    };
    
    
    //++++++++EditLine
    
    EditLine::EditLine(QGraphicsItem *parent)
    {
        Value=0;
        istemp=false;
        iconPath=QUrl::fromLocalFile(UmkiModule::self->myResourcesDir()
                                     .absoluteFilePath("btn_radiation.png")
                                     );
        rad=QImage(iconPath.toLocalFile ());
        
        rad.load(iconPath.toLocalFile ());
        QPainter pntr;
        pntr.begin(&radiation);
       // pntr.drawImage(2,2,rad.scaledToHeight(FIELD_SIZE_SMALL) );
     //   setRenderHints(QPainter::Antialiasing);
    }
    
    void EditLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
    {
        Q_UNUSED(option); Q_UNUSED(widget);
      //  painter->setRenderHints(QPainter::SmoothPixmapTransform);
        if(isRad())
        {
                        
          //  painter->drawPicture(0,0,radiation);
            painter->setPen(QPen(Qt::yellow));
           // painter->drawRect(2, FIELD_SIZE_SMALL+4, (FIELD_SIZE_SMALL-FIELD_SIZE_SMALL/4)*(Value*4/99),FIELD_SIZE_SMALL*4/6 );
            QFont sansFont("Helvetica [Cronyx]", 12);
            sansFont.setPixelSize(FIELD_SIZE_SMALL*1.2);
            painter->setFont(sansFont);
            painter->drawText(4, FIELD_SIZE_SMALL+4,FIELD_SIZE_SMALL*3,FIELD_SIZE_SMALL*1.5,0 ,QString::number(Value));
            
        }
        if(isTemp())
        {
            
            //  painter->drawPicture(0,0,radiation);
            painter->setPen(QPen(Qt::white));
            // painter->drawRect(2, FIELD_SIZE_SMALL+4, (FIELD_SIZE_SMALL-FIELD_SIZE_SMALL/4)*(Value*4/99),FIELD_SIZE_SMALL*4/6 );
            QFont sansFont("Helvetica [Cronyx]", 12);
            sansFont.setPixelSize(FIELD_SIZE_SMALL*1.2);
            painter->setFont(sansFont);
            painter->drawText(4, FIELD_SIZE_SMALL+4,FIELD_SIZE_SMALL*3,FIELD_SIZE_SMALL*1.5,0 ,QString::number(Value));
            
        }
    }
    QRectF EditLine::boundingRect() const
    {
        //     qreal adjust = 0.5;
        return QRectF(0,0,FIELD_SIZE_SMALL/4,FIELD_SIZE_SMALL/4);
    };
    //+++++++Simple Umki
    SimpleUmki::SimpleUmki(QGraphicsItem *parent )
    {
        Q_UNUSED(parent);
        setAcceptDrops(true);
        
        
        
        static const int points[] = {  14+2,6+3, 22+3,14+2, 14+3,22+3, 6+3,14+3 };
        QPolygon polygon;
        polygon.setPoints(4, points);
        QPolygonF polygonf = QPolygonF(polygon);
        Umki = new QGraphicsPolygonItem ( );
        Umki->setPolygon(polygonf);
        Umki->setZValue(100);
        setZValue(100);
        crash=NO_CRASH;
        moving=false;
        // ainter->drawPolygon(polygonf);
        //Umki->setPolygon(polygonf);
    };
    
    void SimpleUmki::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
    {
        event->setAccepted(event->mimeData()->hasFormat("text/plain"));
        qDebug("Umki Drag enter");
    }
    void SimpleUmki::dragMoveEvent ( QGraphicsSceneDragDropEvent * event )
    {
        event->accept();
        qDebug("Umki Drag");
    };
    
    void SimpleUmki::mousePressEvent ( QGraphicsSceneMouseEvent * event )
    {
       // event->accept();
        moving=true;
        qDebug()<<"Mouse press SROBOT2" << event->pos();
    };
    
    void SimpleUmki::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
    {
        qDebug("Mouse move sumki");
        setPos(event->scenePos());
        
    };
    void SimpleUmki::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
    {
        //setZValue(100);
         qDebug()<<"Mouse release SROBOT" << event->pos();
       // emit moved(event->scenePos());
        
    };
    QRectF SimpleUmki::boundingRect() const
    {
        //     qreal adjust = 0.5;
        return Umki->boundingRect();
    };
    
    void SimpleUmki::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
    {
        Q_UNUSED(option); Q_UNUSED(widget);
        // Body
        painter->setBrush(QColor("lightgray"));
        painter->setPen(QPen("black"));
        
        static const int points[] = {  14+3,6+3, 22+3,14+3, 14+3,22+3, 6+3,14+3 };
        QVector<QPointF> up_crash,down_crash,left_crash,right_crash ;
        up_crash << QPointF(14+3 , 6+3) << QPointF(13, 14) <<  QPointF(19+3 ,11+3);
        down_crash << QPointF(14+3 , 22+3) << QPointF(11+3, 18+3) <<  QPointF(18+3 ,18+3);
        left_crash << QPointF(7+3 , 14+3) << QPointF(11+3, 10+3) <<  QPointF(11+3 ,18+3);
        right_crash << QPointF(22+3 , 14+3) << QPointF(18+3, 10+3) <<  QPointF(18+3 ,18+3);
        QPolygon polygon;
        polygon.setPoints(4, points);
        QPolygonF polygonf = QPolygonF(polygon);
        
        painter->drawPolygon(polygonf);
        if(crash!=NO_CRASH)
        {
            qDebug("crash!");
            QPen noPen(Qt::NoPen);
            painter->setPen(noPen);
            painter->setBrush(QColor("red"));
            if(crash==UP_CRASH)painter->drawPolygon(QPolygonF(up_crash));
            if(crash==DOWN_CRASH)painter->drawPolygon(QPolygonF(down_crash));
            if(crash==LEFT_CRASH)painter->drawPolygon(QPolygonF(left_crash));
            if(crash==RIGHT_CRASH)painter->drawPolygon(QPolygonF(right_crash));
            
        };
    };
    
    QGraphicsPolygonItem* SimpleUmki::UmkiItem()
    {
        return Umki;
    }
    
    void SimpleUmki::setCrash(uint dirct)
    {
        crash=dirct;
        update();
    }
    
    
    UmkiModule* UmkiModule::self = 0;
   
    
UmkiModule::UmkiModule(ExtensionSystem::KPlugin * parent)
    : UmkiModuleBase(parent)
{
//UMKI
    myUmki = new Vehicle();


    self = this;
	/* TODO 
	implement class Constructor
	*/
    inDock=false;
    animation=true;
    pressed=false;
    m_mainWidget = 0;
    m_pultWidget = 0;
}


void UmkiModule::createGui()
{
    field=new UmkiField(0);
    //field->editField();
    field->createField(7,7);

    field->setUmkiPos(0,0);
      field->createUmki();
    view=new UmkiView(field);
    m_mainWidget = view;
    const QUrl rcUrl = QUrl::fromLocalFile(
                myResourcesDir().absoluteFilePath("rc.qml")
                );
   // m_pultWidget = new QDeclarativeView(rcUrl);
   // m_pultWidget->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    //QDeclarativeItem * pult = qobject_cast<QDeclarativeItem*>(m_pultWidget->rootObject());
    m_pultWidget = new UmkiPult();
  //  connect(m_pultWidget, SIGNAL(hasLeftWall()), this, SLOT(runGoLeft()));
   // connect(m_pultWidget, SIGNAL(hasRightWall()), this, SLOT(runGoRight()));
    connect(m_pultWidget, SIGNAL(goUp()), this, SLOT(runGoUp()));
    connect(m_pultWidget, SIGNAL(goDown()), this, SLOT(runGoDown()));
    connect(m_pultWidget, SIGNAL(goLeft()), this, SLOT(runGoLeft()));
    connect(m_pultWidget, SIGNAL(goRight()), this, SLOT(runGoRight()));
    connect(m_pultWidget, SIGNAL(doPaint()), this, SLOT(runDoPaint()));
    connect(m_pultWidget, SIGNAL(hasLeftWall()), this, SLOT(runIsWallAtLeft()));
    connect(m_pultWidget, SIGNAL(hasRightWall()), this, SLOT(runIsWallAtRight()));
    connect(m_pultWidget, SIGNAL(hasUpWall()), this, SLOT(runIsWallAtTop()));
    connect(m_pultWidget, SIGNAL(hasDownWall()), this, SLOT(runIsWallAtBottom()));
    connect(m_pultWidget, SIGNAL(noLeftWall()), this, SLOT(runIsFreeAtLeft()));
    connect(m_pultWidget, SIGNAL(noRightWall()), this, SLOT(runIsFreeAtRight()));
    connect(m_pultWidget, SIGNAL(noUpWall()), this, SLOT(runIsFreeAtTop()));
    connect(m_pultWidget, SIGNAL(noDownWall()), this, SLOT(runIsFreeAtBottom()));
    connect(m_pultWidget, SIGNAL(Rad()), this, SLOT(runRadiation()));
    connect(m_pultWidget, SIGNAL(Temp()), this, SLOT(runTemperature()));
    connect(m_pultWidget, SIGNAL(Colored()), this, SLOT(runIsColor()));
    connect(m_pultWidget, SIGNAL(Clean()), this, SLOT(runIsClear()));
    connect(m_pultWidget, SIGNAL(Color()), this, SLOT(runDoPaint()));

    connect(m_pultWidget, SIGNAL(copyTextToKumir(QString)), this, SLOT(copyFromPult(QString)));
    connect(this, SIGNAL(sendToPultLog(QVariant)), m_pultWidget, SLOT(addToResultLog(QVariant)));
    startField=field->Clone();
    field->drawField(FIELD_SIZE_SMALL);
    field->dropWasEdit();
    m_actionUmkiEditEnvironment->setCheckable(true);
    connect(m_actionUmkiLoadEnvironment,SIGNAL(triggered()) , this, SLOT(loadEnv()));
    connect(m_actionUmkiRevertEnvironment,SIGNAL(triggered()) , this, SLOT(resetEnv()));
    connect(m_actionUmkiSaveEnvironment,SIGNAL(triggered()) , this, SLOT(saveEnv()));
    connect(m_actionUmkiEditEnvironment,SIGNAL(triggered()) , this, SLOT(editEnv()));
    connect(m_actionUmkiNewEnvironment,SIGNAL(triggered()) , this, SLOT(newEnv()));
    connect(m_actionUmkiAutoWindowSize,SIGNAL(triggered()) , this, SLOT(setWindowSize()));

    prepareNewWindow();
    rescentMenu=new QMenu();
    m_actionUmkiLoadRescent->setMenu(rescentMenu);
    view->setWindowTitle(trUtf8("Умки - нет файла"));
   // setWindowSize();
}

void UmkiModule::copyFromPult(QString log)
    {
        QClipboard *clipboard = QApplication::clipboard();
        QString originalText = clipboard->text();
       
        clipboard->setText(log); 
    };

/* public slot */ void UmkiModule::loadActorData(QIODevice * source)
{
    // Set actor specific data (like environment)
    // The source should be ready-to-read QIODevice like QBuffer or QFile
       qDebug()<<"Load env";
    if(field->loadFromDataStream(source)!=0)return ;
     m_mainWidget->setWindowTitle(trUtf8("Умки - ")+source->objectName());
    startField=field->Clone();
    field->dropWasEdit();
    //   ajustWindowSize();//NEW ROBOT
    
        
    
    
    //  ToDubl();
    
    
    //  SizeX = m_Size_x * m_FieldSize;
    // SizeY = m_Size_y * m_FieldSize + MenuHigth;
    
    
    
    // WasEditFlag=false;
    //delete btnFind;
    //CreatebtnFind();
    

    reset();
    return;
}

    
void UmkiModule::reset()
{
	/* TODO
	This method is called when actor resets its state before program starts.
	*/
    //delete field;
    qDebug()<<"Reset!!";

        
    field->destroyUmki();
    field->deleteLater();
    if(field->isEditMode())
    {
        field->setMode(NORMAL_MODE);
        view->showButtons(false);
        view->repaint();
        m_actionUmkiEditEnvironment->setChecked(false);
      startField=field->Clone();  
    }
    field=startField->Clone();
    field->setUmkiPos(startField->umkiX(),startField->umkiY());
    field->createUmki();
    field->drawField(FIELD_SIZE_SMALL);
    //delete m_mainWidget;
    view->setScene(field);
    field->drawField(FIELD_SIZE_SMALL);
    view->setField(field);
    
}

    void UmkiModule::changeGlobalState(ExtensionSystem::GlobalState old, ExtensionSystem::GlobalState current){
        using Shared::PluginInterface;
    qDebug()<<"UmkiModuleBase::changeGlobalState";
        if(current==PluginInterface::GS_Running)
          {
              m_actionUmkiRevertEnvironment->setEnabled(false);
              m_actionUmkiLoadEnvironment->setEnabled(false);
              m_actionUmkiLoadRescent->setEnabled(false);
              m_actionUmkiRevertEnvironment->setEnabled(false);
              m_actionUmkiSaveEnvironment->setEnabled(false);
              m_actionUmkiEditEnvironment->setEnabled(false);
              m_actionUmkiNewEnvironment->setEnabled(false);
          }
        if(current==PluginInterface::GS_Unlocked || current==PluginInterface::GS_Observe)
        {
            m_actionUmkiRevertEnvironment->setEnabled(true);
            m_actionUmkiLoadEnvironment->setEnabled(true);
            m_actionUmkiLoadRescent->setEnabled(true);
            m_actionUmkiRevertEnvironment->setEnabled(true);
            m_actionUmkiSaveEnvironment->setEnabled(true);
            m_actionUmkiEditEnvironment->setEnabled(true);
            m_actionUmkiNewEnvironment->setEnabled(true);
            view->FindUmki();
        }

    };    
    
void UmkiModule::reloadSettings(ExtensionSystem::SettingsPtr settings, const QStringList & keys)
{
    qDebug()<<"reload settings";
    field->setColorFromSett();
    CurCellSize=settings->value("Umki/CellSize", FIELD_SIZE_SMALL).toInt();
    view->reloadSett(settings);
    if(UmkiModule::umkiSettings()->value("Umki/SFF").isValid())
    {
        if(LoadFromFile(UmkiModule::umkiSettings()->value("Umki/SFF").toString())!=0){
            createEmptyField(7,7);
            
        }
        setWindowSize();
    }
    createRescentMenu();
}

void UmkiModule::setAnimationEnabled(bool enabled)
{
    animation=enabled;
	/* TODO
	Set internal flag for animation
	*/
}


QWidget* UmkiModule::mainWidget() const
{
	/* TODO
	This method should return a pointer to main widget.
	NOTE: This metod should NOT create main widget -- just return!
	*/
 
    return m_mainWidget;
}

QWidget* UmkiModule::pultWidget() const
    {
        static QWidget * dummy = new AAA(m_pultWidget);
        return dummy;
    return m_pultWidget;
}
QList<ExtensionSystem::CommandLineParameter>  UmkiModule::acceptableCommandLineParameters()
{
    QList<ExtensionSystem::CommandLineParameter> params;
    params.append(ExtensionSystem::CommandLineParameter(true,'f',"field",tr("Umki field file name"),QVariant::String,false));
    return params;
    
}
QString UmkiModule::initialize(const QStringList &configurationParameters, const ExtensionSystem::CommandLine & runtimeParameters)
{
    if (!configurationParameters.contains("tablesOnly")) {
        createGui();
        ExtensionSystem::SettingsPtr sett;
        sett=umkiSettings();

        if(runtimeParameters.value("field").isValid())
        {
            qDebug()<<"FIELD:|"<<runtimeParameters.value("field").toString()<<"|";
            // std::cout <<"FIELD:" <<runtimeParameters.value("field").toString().toStdString();
            if(LoadFromFile(runtimeParameters.value("field").toString())!=0)return "Error loading:"+runtimeParameters.value("field").toString();
            return "";
        }
        if(UmkiModule::umkiSettings()->value("Umki/SFF").isValid())
        {
            if(LoadFromFile(UmkiModule::umkiSettings()->value("Umki/SFF").toString())!=0){
                createEmptyField(7,7);

            }
            //setWindowSize();
        }
        if(sett->value("Umki/Dir").isValid())
        {
            curDir=sett->value("Umki/Dir").toString();
        }
        // setWindowSize();
    }
    return "";
}


//my function umki


void UmkiModule::runGoUp()
{
	/* TODO implement me */
    qDebug() << "Umki up";
    QString status = "OK";
     if(!field->stepUp())
     {
     field->umki->setCrash(UP_CRASH);    
     setError(trUtf8("Умки разбился: сверху стена!"));
     status = trUtf8("Отказ");
     }
     myUmki->SendCommForw1();
     status = trUtf8("Поехали вперед");
//     if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//         emit sendToPultLog(status);
//     }
if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(trUtf8("вверх"),QString::fromUtf8("вверх     "),status);
    if(animation)msleep(250);
	return;
}


void UmkiModule::runGoDown()
{
	/* TODO implement me */
    qDebug() << "Umki down";
    QString status = "OK";
     if(!field->stepDown())
     {setError(trUtf8("Умки разбился: снизу стена!"));
     field->umki->setCrash(DOWN_CRASH);
     status = trUtf8("Отказ");
     }

         myUmki->SendCommRevers1();

//     if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//         emit sendToPultLog(status);
//     }
  if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(trUtf8("вниз"),QString::fromUtf8("вниз     "),status);
    if(animation){
        view->update();
     msleep(250);   
    }
	return;
}


void UmkiModule::runGoLeft()
{
	/* TODO implement me */
    qDebug() << "Umki left";
    QString status = "OK";
    if(!field->stepLeft()){
      field->umki->setCrash(LEFT_CRASH);  
    setError(trUtf8("Умки разбился: слева стена!"));
    status = trUtf8("Отказ");
    };
     myUmki->SendCommExtrLeft1();
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
      if (sender()==m_pultWidget)   m_pultWidget->Logger->appendText(trUtf8("влево"),QString::fromUtf8("влево     "),status);
    if(animation)
    {
        view->update();
        msleep(250);
    }
	return;
}


void UmkiModule::runGoRight()
{
	/* TODO implement me */
    qDebug() << "Umki right";
    QString status = "OK";
    if(!field->stepRight()){
        field->umki->setCrash(RIGHT_CRASH);  
        status = trUtf8("Отказ");
        
    setError(trUtf8("Умки разбился: справа стена!"));}

     myUmki->SendCommExtrRight1();
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
   if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(trUtf8("вправо"),QString::fromUtf8("вправо     "),status);
     if(animation)
     {
         view->update();
     msleep(250);
     }
	return;
}



//end my function umki



void UmkiModule::runDoPaint()
{
	if(!field->currentCell()->IsColored)field->reverseColorCurrent();
    QString status = "OK";
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
   if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(trUtf8("закрасить"),trUtf8("закрасить"), "OK");
    if(animation)
    {
        view->update();
        msleep(250);
    }
	return;
}


bool UmkiModule::runIsWallAtTop()
{
    bool result = !field->currentCell()->canUp();
    QString status = result? trUtf8("Да") : trUtf8("Нет");
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
   if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Сверху стена: \',сверху стена,нс"),
                                     trUtf8("сверху стена"),status);
    return result;
}


bool UmkiModule::runIsWallAtBottom()
{
    bool result = !field->currentCell()->canDown();
    QString status = result? trUtf8("Да") : trUtf8("Нет");
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
   if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Снизу стена: \',снизу стена,нс"),
                       QString::fromUtf8("снизу стена"),status);
    
    return result;
}


bool UmkiModule::runIsWallAtLeft()
{
    bool result = !field->currentCell()->canLeft();
    QString status = result? trUtf8("Да") : trUtf8("Нет");
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
   if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Слева стена: \',слева стена,нс"),
                       trUtf8("слева стена"),status);
    
    return result;
}


bool UmkiModule::runIsWallAtRight()
{
    bool result = !field->currentCell()->canRight();
    QString status = result? trUtf8("Да") : trUtf8("Нет");
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
    if (sender()==m_pultWidget) {
    if(result)m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Справа стена: \',справа стена,нс"),
                                               trUtf8("справа стена"),trUtf8("Да"));
    else m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Справа стена: \',справа стена,нс"),
                                          trUtf8("справа стена"),trUtf8("Нет"));}
    return result;
}

bool UmkiModule::runIsFreeAtTop()
{
    bool result = field->currentCell()->canUp();
    QString status = result? trUtf8("Да") : trUtf8("Нет");
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
  if (sender()==m_pultWidget)   m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Сверху свободно: \',сверху свободно,нс"),
                       trUtf8("сверху свободно"),status);
    return result;
}
    
    
bool UmkiModule::runIsFreeAtBottom()
{
    bool result = field->currentCell()->canDown();
    QString status = result? trUtf8("Да") : trUtf8("Нет");
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
  if (sender()==m_pultWidget)   m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Снизу свободно: \',снизу свободно,нс"),
                                     trUtf8("снизу свободно"),status);
    return result;
}
    
    
bool UmkiModule::runIsFreeAtLeft()
{
    bool result = field->currentCell()->canLeft();
    QString status = result? trUtf8("Да") : trUtf8("Нет");
//    if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//        emit sendToPultLog(status);
//    }
   if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Слева свободно: \',слева свободно,нс"),
                                     trUtf8("слева свободно"),status);
    return result;
}
    
    
bool UmkiModule::runIsFreeAtRight()
{
    bool result = field->currentCell()->canRight();
    QString status = result? trUtf8("Да") : trUtf8("Нет");
   // QObject *sendr=sender();
    if (sender()==m_pultWidget) {
       
   
   
   if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Справа свободно: \',справа свободно,нс"),
                                     trUtf8("справа свободно"),status);
    }
    return result;
}

bool UmkiModule::runIsColor()
    {
     bool result = field->currentCell()->isColored();
        QString status = result? trUtf8("Да") : trUtf8("Нет");
//        if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//            emit sendToPultLog(status);
//        }
      if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Клетка закрашена: \',клетка закрашена,нс"),
                           QString::fromUtf8("клетка закрашена"),status);
        return result;
        
    };
    bool UmkiModule::runIsClear()
    {
        bool result = !field->currentCell()->isColored();
        QString status = result? trUtf8("да") : trUtf8("нет");
//        if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//            emit sendToPultLog(status);
//        }
        if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Клетка чистая: \',клетка чистая,нс"),
                           QString::fromUtf8("клетка чистая"),status);
        return result;
    };
    qreal UmkiModule::runRadiation(){    
        double result = field->currentCell()->radiation;
        QString status = QString::number(result);
//        if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//            emit sendToPultLog(status);
//        }
       if (sender()==m_pultWidget)  m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Радиация: \',радиация,нс"),
                                         QString::fromUtf8("радиация"),status);
        return result;
    };
    int UmkiModule::runTemperature(){       
        int result = field->currentCell()->temperature;
        QString status = QString::number(result);
//        if (sender() && qobject_cast<QDeclarativeItem*>(sender())) {
//            emit sendToPultLog(status);
//        }
      if (sender()==m_pultWidget)   m_pultWidget->Logger->appendText(QString::fromUtf8("вывод \'Температура: \',температура,нс"),
                                         QString::fromUtf8("температура"),status);
        return result;};
    void UmkiModule::runFieldSize(int& rows, int& cols)
    {
        rows=field->rows();
        cols=field->columns();
    };
    bool UmkiModule::runMark(const int row, const int col)
    {
        int rws=field->rows();
        int clmns=field->columns();
        if(row-1>=field->rows() ||col-1>=field->columns()|| row-1<0 || col-1<0)
        {
            
            setError(trUtf8("Нет какой клетки!"));
            
            return false;
        }
        return field->cellAt(row-1,col-1)->mark;
    };
    bool UmkiModule::runColored(const int row, const int col)
    {
        int rows=field->rows();
        
        if(row-1>=field->rows() ||col-1>=field->columns())
        {
            
            setError(trUtf8("Нет какой клетки!"));
            
            return false;
        }
        return  field->cellAt(row-1,col-1)->isColored();
    };
    void UmkiModule::runUmkiPos(int& row, int& col)
    {
        if(row-1>=field->rows() ||col-1>=field->columns())
        {
            
            setError(trUtf8("Нет какой клетки!"));
            
            return;
        }
        col=field->umkiX()+1;
        row=field->umkiY()+1;
    };
    
    QChar UmkiModule::runUpChar(const int row, const int col)
    {
        if(row-1>=field->rows() ||col-1>=field->columns())
        {
           
            setError(trUtf8("Нет какой клетки!"));
            
            return ' ';
        }
        qDebug()<<field->cellAt(row-1,col-1)->upChar;
        return field->cellAt(row-1,col-1)->upChar;  
    };
    int UmkiModule::runCellTemp(const int row, const int col)
    {
        if(row-1>=field->rows() ||col-1>=field->columns())
        {
            
            setError(trUtf8("Нет какой клетки!"));
            
            return ' ';
        }
        qDebug()<<field->cellAt(row-1,col-1)->upChar;
        return field->cellAt(row-1,col-1)->temperature;  
    };
    qreal UmkiModule::runCellRad(const int row, const int col)
    {
        if(row-1>=field->rows() ||col-1>=field->columns())
        {
            
            setError(trUtf8("Нет какой клетки!"));
            
            return ' ';
        }
        qDebug()<<field->cellAt(row-1,col-1)->upChar;
        return field->cellAt(row-1,col-1)->radiation; 
    };
    
QChar UmkiModule::runDownChar(const int row, const int col)
    {
        if(row-1>=field->rows() ||col-1>=field->columns())
            {
        
        setError(trUtf8("Нет какой клетки!"));
        
        return ' ';
                }
        qDebug()<<field->cellAt(row-1,col-1)->downChar;
        return field->cellAt(row-1,col-1)->downChar;
    };   
    
 int UmkiModule::LoadFromFile(QString p_FileName)
    {
        qDebug() <<"LoadField "<<p_FileName;
        if(field->loadFromFile(p_FileName)!=0)return 1;
        startField=field->Clone();
        field->dropWasEdit();
     //   ajustWindowSize();//NEW ROBOT
        
        QFileInfo fi(p_FileName);
        QString name = fi.fileName();
        
        QString Title = trUtf8("Umki") + " - " + name;
      //  std::cout <<"Title"<<Title.toStdString();
        m_mainWidget->setWindowTitle(Title);

        
        
      //  ToDubl();
        
        
      //  SizeX = m_Size_x * m_FieldSize;
       // SizeY = m_Size_y * m_FieldSize + MenuHigth;
        
        
        
       // WasEditFlag=false;
        //delete btnFind;
        //CreatebtnFind();
        
        UmkiModule::umkiSettings()->setValue("Umki/SFF",p_FileName);
        field->drawField(FIELD_SIZE_SMALL);
       // if(CurrentUmkiMode==ANALYZE_MODE)SetUmkiMode(SEE_MODE);
        qDebug() << "File " << p_FileName ;
   
        return(0);
    }
void UmkiModule::editEnv()
    {
        if(field->isEditMode())
        {
           // field->setMode(NORMAL_MODE);
            reset(); //reset 2 normal mode
            setWindowSize();
            return;
        }
        startField->setModeFlag(NEDIT_MODE);
        view->repaint();
        
        view->showButtons(true);
         
        reset();
        field->setMode(NEDIT_MODE);
        startField->setModeFlag(NORMAL_MODE);
        
        setWindowSize(); 
    };  
void UmkiModule::createEmptyField(int rows,int cols)
    {
        field->createField(7,7);
        field->setUmkiPos(0,0);
        field->createUmki();
        startField=field->Clone();
        field->drawField(umkiSettings()->value("Umki/CellSize",FIELD_SIZE_SMALL).toInt());
        
        mainWidget()->setWindowTitle(QString::fromUtf8("Умки - нет файла") );
        field->dropWasEdit();
    };
bool UmkiModule::isSafeToQuit() 
    {
        if(field->WasEdit())
        {
            QMessageBox::StandardButton r;
        
        QMessageBox messageBox(
                               QMessageBox::Question,
                               trUtf8("Умки"),
                               trUtf8("Сохранить изменения?"),
                               QMessageBox::NoButton,mainWidget()
                               );
        
        QPushButton * btnSave =
        messageBox.addButton(trUtf8("Да"), QMessageBox::AcceptRole);
        QPushButton * btnDiscard =
        messageBox.addButton(trUtf8("Нет"), QMessageBox::DestructiveRole);
        QPushButton * btnCancel =
        messageBox.addButton(trUtf8("Отмена"), QMessageBox::RejectRole);
        
        messageBox.setDefaultButton(btnSave);
        messageBox.exec();
        if (messageBox.clickedButton()==btnSave) {
            r = QMessageBox::Save;
        }
        if (messageBox.clickedButton()==btnDiscard) {
            r = QMessageBox::Discard;
        }
        if (messageBox.clickedButton()==btnCancel) {
            r = QMessageBox::Cancel;
        }
        if (r==QMessageBox::Save) {saveEnv();};
        if (r==QMessageBox::Cancel) {return false;};
        }
        return true; 
    }
void UmkiModule::loadEnv()
    {
        if(field->WasEdit())
        {
            if(QMessageBox::question(mainWidget(), "", QString::fromUtf8("Сохранить изменения?"), QMessageBox::Yes,QMessageBox::No,0) == QMessageBox::Yes)
            {
               saveEnv();
                
            }
            
        }
        
        
        
        //
        
        QString	UmkiFile=QFileDialog::getOpenFileName(mainWidget(), QString::fromUtf8 ("Открыть файл"), curDir, "(*.fil)");
        
        qDebug()<<"CurDir"<<curDir;
        
        QFileInfo info(UmkiFile);
        QDir dir=info.absoluteDir();
        
        curDir=dir.path();
        umkiSettings()->setValue("Umki/Dir",QVariant(curDir));
        if ( UmkiFile.isEmpty())return;
       // CurrentFileName = UmkiFile;
       
        if( LoadFromFile(UmkiFile)!=0)//Get troubles when loading env.
        {
            QMessageBox::information( mainWidget(), "", QString::fromUtf8("Ошибка открытия файла! ")+UmkiFile, 0,0,0); 
            return;
        }
        
        updateLastFiles(UmkiFile);
        
        setWindowSize();
        view->setWindowTitle(trUtf8("Умки  - ")+info.baseName ());
        umkiSettings()->setValue("Umki/SFF",QVariant(UmkiFile));
        
    }
    void UmkiModule::resetEnv()
    {
        reset();
    }
    void UmkiModule::prepareNewWindow()
    {
    NewWindow = new QDialog(mainWidget());
	QGridLayout *nwl = new QGridLayout;
	NewWindow->setLayout(nwl);
	NewWindow->setWindowModality(Qt::WindowModal);
	//NewWindow->setPalette (BackPall);
	NewWindow->setWindowTitle ( QString::fromUtf8("Новая обстановка"));
	QLabel *lKol = new QLabel(QString::fromUtf8("Количество:"),NewWindow,0);
	nwl->addWidget(lKol, 0, 0, 1, 2, Qt::AlignCenter);
    
	QLabel *lXSize = new QLabel(QString::fromUtf8("Столбцов"),NewWindow,0);
	nwl->addWidget(lXSize, 1, 1, 1, 1, Qt::AlignCenter);
    
    
	QLabel *lYSize = new QLabel(QString::fromUtf8("Строк"),NewWindow,0);
	nwl->addWidget(lYSize, 1, 0, 1, 1, Qt::AlignCenter);
    
	NewWindow->setFixedSize(250,150);
	eXSizeEdit = new QSpinBox(NewWindow);
	eXSizeEdit->setRange ( 2, MAX_COLUMNS );
	//eTemp->show();
	eYSizeEdit = new QSpinBox(NewWindow);
    
    
	eYSizeEdit->setRange ( 2, MAX_ROWS );
	nwl->addWidget(eYSizeEdit, 2, 0, 1, 1, Qt::AlignCenter);
	nwl->addWidget(eXSizeEdit, 2, 1, 1, 1, Qt::AlignCenter);
    
    
	QDialogButtonBox *buttonBox = new QDialogButtonBox(NewWindow);
    
	btnOK1 = buttonBox->addButton(QDialogButtonBox::Ok);
	btnCancel1 = new QPushButton(trUtf8("Отмена"));
    buttonBox->addButton(btnCancel1,QDialogButtonBox::RejectRole);
   
    nwl->addWidget(buttonBox, 3, 0, 1, 2, Qt::AlignRight);  
    connect ( btnCancel1, SIGNAL(clicked()), NewWindow, SLOT(close()));
    connect ( btnOK1, SIGNAL(clicked()), this, SLOT(createNewField()) );
    }
    void UmkiModule::createNewField()
    {
        field->destroyField();
        field->destroyUmki();
        field->createField(eYSizeEdit->value(),eXSizeEdit->value());
        field->setUmkiPos(0,0);
        field->createUmki();
        startField=field->Clone();
        field->drawField(FIELD_SIZE_SMALL);
        
        mainWidget()->setWindowTitle(QString::fromUtf8("Умки - нет файла") );

        view->centerOn(field->m_height()/2,field->m_width()/2);
        NewWindow->close();
        
        if(!field->isEditMode())editEnv();
    };
    void UmkiModule::newEnv()
    {
        if(field->WasEdit())
        {
            QMessageBox::StandardButton r;
            
            QMessageBox messageBox(
                                   QMessageBox::Question,
                                   trUtf8("Новая обстановка"),
                                   trUtf8("Сохранить текущую?"),
                                   QMessageBox::NoButton,mainWidget()
                                   );
            
            QPushButton * btnSave =
            messageBox.addButton(trUtf8("Сохранить"), QMessageBox::AcceptRole);
            QPushButton * btnDiscard =
            messageBox.addButton(trUtf8("Не сохранять"), QMessageBox::DestructiveRole);
            QPushButton * btnCancel =
            messageBox.addButton(trUtf8("Отмена"), QMessageBox::RejectRole);
            
            messageBox.setDefaultButton(btnSave);
            messageBox.exec();
            if (messageBox.clickedButton()==btnSave) {
                r = QMessageBox::Save;
            }
            if (messageBox.clickedButton()==btnDiscard) {
                r = QMessageBox::Discard;
            }
            if (messageBox.clickedButton()==btnCancel) {
                r = QMessageBox::Cancel;
            }
            if (r==QMessageBox::Save) {saveEnv();};
            if (r==QMessageBox::Cancel) {return;};
            
        }
        
        NewWindow->show();
    }
void UmkiModule::saveEnv()
    {
        QString	UmkiFile=QFileDialog::getSaveFileName(mainWidget(), QString::fromUtf8 ("Сохранить файл"), curDir, "(*.fil)");
        
        
        //QString	UmkiFile=dialog.selectedFiles().first();
        QFileInfo info(UmkiFile);
        QDir dir=info.absoluteDir();
        curDir=dir.path();
        umkiSettings()->setValue("Umki/Dir",QVariant(curDir));
        if (UmkiFile.contains("*") || UmkiFile.contains("?"))
        {
            QMessageBox::information( 0, "", trUtf8("Недопустимый символ в имени файла!"), 0,0,0);
            return;
        }
        //QString	UmkiFile =  QFileDialog::getSaveFileName(MV,QString::fromUtf8 ("Сохранить в файл"),"/home", "(*.fil)");
        //if ( UmkiFile.isEmpty())return;
        
        if(UmkiFile.right(4)!=".fil")UmkiFile+=".fil";
        //CurrentFileName = UmkiFile;
        
        SaveToFile(UmkiFile);
        
         UmkiModule::umkiSettings()->setValue("Umki/StartField/File",UmkiFile);
        updateLastFiles(UmkiFile);
        
        mainWidget()->setWindowTitle(trUtf8("Умки - ")+info.baseName());
    }
    
    

  
int UmkiModule::SaveToFile(QString p_FileName)
    {
        

        if(field->saveToFile(p_FileName)!=0){QMessageBox::warning(0, tr("Umki"), QString::fromUtf8("Не удалось сохранить файл"));return 1;};
        
     
        return 0;
        
    }    
    

    
 void UmkiModule::createRescentMenu()
    {
        rescentMenu->clear();
        QStringList lastFiles= mySettings()->value("Umki/LastFiles").toString().split(";");
        qDebug()<<lastFiles;
        if(lastFiles.count()==0)rescentMenu->setEnabled(false);else  rescentMenu->setEnabled(true);


        for(int i=0;i<lastFiles.count();i++) {
            if(lastFiles[i]=="")continue;
            QAction *action = rescentMenu->addAction("&"+QString::number(i+1)+" "+lastFiles[i],this,SLOT(openRecent()));
            Q_UNUSED(action);
            }
    };
QSize UmkiModule::minimumSize() const
    {
        return QSize(mySettings()->value("Umki/CellSize").toInt()*3, mySettings()->value("Umki/CellSize",FIELD_SIZE_SMALL).toInt()*3);
        
    };
void UmkiModule::setWindowSize()
    {
        QRect baseFieldSize; //fieldSize in pixel. Zoom 1:1
        QSize newSize;
        newSize=view->size();
        baseFieldSize.setHeight(field->rows()*mySettings()->value("Umki/CellSize", FIELD_SIZE_SMALL).toInt());
        baseFieldSize.setWidth(field->columns()*mySettings()->value("Umki/CellSize", FIELD_SIZE_SMALL).toInt());
        int editEnlarge=0;
        QWidgetList scBars=view->scrollBarWidgets(Qt::AlignRight);
        if(field->isEditMode())editEnlarge=1.8*mySettings()->value("Umki/CellSize", FIELD_SIZE_SMALL).toInt();
        view->setMinimumSize(minimumSize());
        
        if(baseFieldSize.height()<view->height())
        {
            newSize.setHeight( baseFieldSize.height()+mySettings()->value("Umki/CellSize",FIELD_SIZE_SMALL).toInt()+editEnlarge);
            
            // mainWidget()->setGeometry(view->x(), view->y(), view->width(), baseFieldSize.height());
        }
        
        if(baseFieldSize.width()<view->width())
        {
            newSize.setWidth( baseFieldSize.width()+mySettings()->value("Umki/CellSize",FIELD_SIZE_SMALL).toInt()+editEnlarge);
           // view->setGeometry(view->x(), view->y(), baseFieldSize.width(), view->height()); 
            
        }   
        
        if(baseFieldSize.height()>view->height() && field->rows()<11)
        {
            newSize.setHeight( baseFieldSize.height()+mySettings()->value("Umki/CellSize",FIELD_SIZE_SMALL).toInt()+editEnlarge);
            
            // mainWidget()->setGeometry(view->x(), view->y(), view->width(), baseFieldSize.height());
        }
        if(baseFieldSize.width()>view->width() && field->columns()<17)
        {
            newSize.setWidth( baseFieldSize.width()+mySettings()->value("Umki/CellSize",FIELD_SIZE_SMALL).toInt()+editEnlarge);
            // view->setGeometry(view->x(), view->y(), baseFieldSize.width(), view->height()); 
            
        } 
                view->setWindowSize(newSize);
    }
  
 void UmkiModule::openRecent()
    {
        QAction *s = qobject_cast<QAction*>(sender());
        QString txt = s->text();
        if(field->WasEdit())
        {
            QMessageBox::StandardButton r;
            
            QMessageBox messageBox(
                                   QMessageBox::Question,
                                   tr("New field"),
                                   tr("Save current field?"),
                                   QMessageBox::NoButton,mainWidget()
                                   );
            
            QPushButton * btnSave =
            messageBox.addButton(tr("Save"), QMessageBox::AcceptRole);
            QPushButton * btnDiscard =
            messageBox.addButton(tr("Don't save"), QMessageBox::DestructiveRole);
            QPushButton * btnCancel =
            messageBox.addButton(tr("Cancel"), QMessageBox::RejectRole);
            
            messageBox.setDefaultButton(btnSave);
            messageBox.exec();
            if (messageBox.clickedButton()==btnSave) {
                r = QMessageBox::Save;
            }
            if (messageBox.clickedButton()==btnDiscard) {
                r = QMessageBox::Discard;
            }
            if (messageBox.clickedButton()==btnCancel) {
                r = QMessageBox::Cancel;
            }
            if (r==QMessageBox::Save) {saveEnv();};
            if (r==QMessageBox::Cancel) {return;};
            
        }

        
       
        txt.remove(0,1);
        QStringList words = txt.split(" ");
        if(words.count()<2)return;
        QString UmkiFile=words[1];
        if( LoadFromFile(UmkiFile)!=0)QMessageBox::information( mainWidget(), "", QString::fromUtf8("Ошибка открытия файла! ")+UmkiFile, 0,0,0);
        reset();
        view->setWindowSize(view->size());
        
    };
 void UmkiModule::updateLastFiles(const QString newFile )
    {
     QStringList lastFiles= UmkiModule::umkiSettings()->value("Umki/LastFiles").toString().split(";");
        if(lastFiles.indexOf(newFile)<0)lastFiles.prepend(newFile);
        int max_fid=std::min(lastFiles.count(),11);
        QString sett="";
        for(int i=0;i<max_fid;i++)
        {
            sett+= lastFiles.at(i)+";";
        }
        UmkiModule::umkiSettings()->setValue("Umki/LastFiles",sett);  
        createRescentMenu();
    }

    UmkiView::UmkiView(UmkiField * roboField)
    {
        setScene(roboField);
        pressed=false;
        inDock=false;
        firstShow=true;
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setMouseTracking(true);
        setCursor(Qt::OpenHandCursor);
        umkiField=roboField;
        textEditBtn=new QToolButton(this);
        textEditBtn->hide();
        textEditBtn->setCheckable ( true );
        textEditBtn->setIcon(QIcon(UmkiModule::self->myResourcesDir()
                                   .absoluteFilePath("text.png")));

        radEditBtn=new QToolButton(this);
        radEditBtn->setIcon(QIcon(UmkiModule::self->myResourcesDir()
                                  .absoluteFilePath("btn_radiation.png")));

        radEditBtn->hide();
        radEditBtn->setCheckable ( true );
        radEditBtn->move(textEditBtn->height(),0);
        tmpEditBtn=new QToolButton(this);
        tmpEditBtn->hide();
        tmpEditBtn->setCheckable ( true );
        tmpEditBtn->setIcon(QIcon(UmkiModule::self->myResourcesDir()
                                   .absoluteFilePath("btn_temperature.png")));
        tmpEditBtn->move(textEditBtn->height()*2+2,0);
        
        connect(textEditBtn,SIGNAL(toggled(bool)),this,SLOT(changeEditMode(bool)));
        connect(radEditBtn,SIGNAL(toggled(bool)),this,SLOT(changeEditMode(bool)));
        connect(tmpEditBtn,SIGNAL(toggled(bool)),this,SLOT(changeEditMode(bool)));
        setMinimumWidth ( 30 );
        c_scale=1;
        CurCellSize=FIELD_SIZE_SMALL;
      //  setRenderHint(QPainter::Antialiasing);
    };
    
    void UmkiView::showButtons(bool flag)
    {
        textEditBtn->setVisible(flag);
        radEditBtn->setVisible(flag);
        tmpEditBtn->setVisible(flag);
    };
    void UmkiView::mousePressEvent ( QMouseEvent * event )
    {
        if(umkiField->isEditMode())
        {
         qDebug()<<"Edit mode;";
           QGraphicsView::mousePressEvent(event);
            update();
            repaint();
            return;
        }
        if(umkiField->sceneRect().height()*c_scale> this->height()  || umkiField->sceneRect().width()*c_scale> this->width())//field > view
        {
        pressed=true;
        setCursor(Qt::ClosedHandCursor);   
        };
        pressX=event->pos().x();
        pressY=event->pos().y();
         
    };
    
   void UmkiView::mouseReleaseEvent ( QMouseEvent * event )
    {
        repaint();
        update();
        if(umkiField->isEditMode())
            
        { //event->ignore ();
           // umkiField->mouseReleaseEvent(event);
            if(umkiField->umki->isMoving())
            {
               umkiField->roboMoved(this->mapToScene(event->pos()));
                umkiField->umki->setMoving(false);
            };
            qDebug()<<"Mouse Release EV (UmkiView)";
            return;   
        }
        pressed=false;
        setCursor(Qt::OpenHandCursor);
    };
    
void UmkiView::mouseMoveEvent ( QMouseEvent * event )
    { 
        if(umkiField->isEditMode())
        {
        setCursor(Qt::ArrowCursor);    
        QGraphicsView::mouseMoveEvent(event);
        return;
            
        }
        setCursor(Qt::ArrowCursor);
       if(umkiField->sceneRect().height()> this->height()  || umkiField->sceneRect().width()> this->width())//field size more then view size
          {
        setCursor(Qt::OpenHandCursor);
           }
        if(!pressed)return;
        setCursor(Qt::ClosedHandCursor);
        QPointF center = mapToScene(viewport()->rect().center());
        qDebug()<<"==========Move==========";
        qDebug()<<"Old center:"<<center;
        qreal diffX=pressX-event->pos().x();
        qreal diffY=pressY-event->pos().y();
        if(diffX==0 && diffY==0)return;
        center.setX(center.x()+diffX);
        center.setY(center.y()+diffY);
        qDebug()<<"New center:"<<center<<" DiffX"<<diffX;
 
        if(diffX< width() && diffY<height())centerOn(center);
       // qDebug()<<mapFromScene (umkiField->sceneRect())<<umkiField->sceneRect().height();
        
    };
void	UmkiView::wheelEvent ( QWheelEvent * event )
    {
        float numDegrees = event->delta() / 8;
        qDebug()<<"whell:"<<numDegrees;
//        c_scale=c_scale*0.8;
        qDebug()<<"Scale"<<c_scale;
    
      //setRenderHint(QPainter::Antialiasing);
        if(numDegrees>0)
        { //if(c_scale<3 && c_scale>0.003)this->scale(1.2,1.2);
          c_scale=c_scale*1.2;
            if(c_scale>10)c_scale=10;
                else this->scale(1.2,1.2);
        }
        else{ 
         // if(c_scale<3 && c_scale>0.01)this->scale(0.8,0.8);
          c_scale=c_scale*0.8;
            if(c_scale<0.1)c_scale=0.1;
                else this->scale(0.8,0.8);
        }
        
    }
 void UmkiView::showEvent ( QShowEvent * event )
    {
        if(firstShow)setWindowSize(size());
        firstShow=false;
    };
 void UmkiView:: FindUmki()
    {
        centerOn(umkiField->roboPosF());
    };
    
 void UmkiView::setWindowSize(const QSize newGeometry)
    {
        QSize oldSize=this->size();
        
       if(inDock)
       {
           scale(1/c_scale,1/c_scale);
           
           
           qreal w=sceneRect().width();
           qreal h=sceneRect().height();
           qreal maxDisp=qMax(w/oldSize.width(),h/oldSize.height());
          
           scale(1/maxDisp,1/maxDisp);
           c_scale=1/maxDisp;
           maxDisp=qMax(w*(1/maxDisp)/oldSize.width(),h*(1/maxDisp)/oldSize.height());
           while(maxDisp>1.01 || maxDisp<0.99)
           {
            scale(1/maxDisp,1/maxDisp);
             c_scale=c_scale/maxDisp;
            maxDisp=qMax(w*(1/maxDisp)/oldSize.width(),h*(1/maxDisp)/oldSize.height());
           }
           centerOn(sceneRect().width()/2, sceneRect().height());
           return;
     }
        emit  resizeRequest(newGeometry);
        if(newGeometry != oldSize)
       {centerOn(newGeometry.width()/2-(CurCellSize/2),newGeometry.height()/2-(CurCellSize/2));
        qDebug()<<"CenterON:"<<newGeometry.width()/2-CurCellSize/2<<newGeometry.width()/2-CurCellSize/2;
           this->scale(1/c_scale,1/c_scale);
           c_scale=1;
    }
    };
    
QSize	UmkiView::sizeHint () const
    {
    return QSize(umkiField->columns()*CurCellSize+CurCellSize, umkiField->rows()*CurCellSize+CurCellSize);
}

void UmkiView::handleDocked()
{
    qDebug() << "Umki is visible in dock. Size = " << size();
    setWindowSize(size());
}
void UmkiView::reloadSett(ExtensionSystem::SettingsPtr settings)
    {
       CurCellSize=settings->value("Umki/CellSize", FIELD_SIZE_SMALL).toInt(); 
        
    };
void UmkiView::setDock(bool docked)
    {
    qDebug() << "UmkiView::setDock(" << docked << ")";
        inDock=docked;
        if(inDock)setWindowSize(size());
    };
void UmkiView::changeEditMode(bool state)
    {
        QToolButton *clicked = qobject_cast<QToolButton*>(sender());
        if(radEditBtn!=clicked && radEditBtn->isChecked())radEditBtn->setChecked(false); 
        if(textEditBtn!=clicked && textEditBtn->isChecked())textEditBtn->setChecked(false);
        if(tmpEditBtn!=clicked && tmpEditBtn->isChecked())tmpEditBtn->setChecked(false); 
        if(clicked->isChecked()!=state)clicked->setChecked(state);
       if(!textEditBtn->isChecked () && !radEditBtn->isChecked ())umkiField->setMode(NEDIT_MODE);
        if(textEditBtn->isChecked ())
        {
          
            umkiField->setMode(TEXT_MODE);
            update();
        }
        if(radEditBtn->isChecked ())
        {
                    umkiField->setMode(RAD_MODE);
            repaint();
            update();
            
        }; 
        if(tmpEditBtn->isChecked ())
        {
            umkiField->setMode(TEMP_MODE);
            repaint();
            update();
        };
        ViewportUpdateMode mod=viewportUpdateMode ();
        setViewportUpdateMode ( QGraphicsView::FullViewportUpdate);
            setViewportUpdateMode (mod);
            qDebug()<<"UPDATE VIEW";
            scale(0.99,0.99);
            scale(1.01,1.01);
        
    };
    
    

    int UmkiModule::runTemp(){       
        printf ("Zapros temper \n");
//        QString status = trUtf8("Запрос температуры");
//	 m_pultWidget->Logger->appendText(trUtf8("вниз"),QString::fromUtf8("вниз     "),status);

	int ust = myUmki->GetVibrUst();
        int result = (int)  myUmki->GetTemper(ust);
 
        return result;};

    int UmkiModule::runDim(){       
//        printf ("Zapros temper \n");
	int ust = myUmki->GetVibrUst();
        int result = (int)  myUmki->GetDim(ust);
 
        return result;};

    int UmkiModule::runOsv(){       
//        printf ("Zapros temper \n");
	int ust = myUmki->GetVibrUst();
        int result = (int)  myUmki->GetOsv(ust);
 
        return result;};

    int UmkiModule::runBar(){       
//        printf ("Zapros bar \n");
	int ust = myUmki->GetVibrUst();
        int result = (int)  myUmki->GetBar(ust);
 
        return result;};

    int UmkiModule::runKas(){       
//        printf ("Zapros kasan \n");
	int ust = myUmki->GetVibrUst();
        int result = (int)  myUmki->GetDatKas(ust);
 
        return result;};

    int UmkiModule::runSbrosKas(){       
	int ust = myUmki->GetVibrUst();
        int result = (int)  myUmki->SbrosDatKas(ust);
 
        return result;};

    int UmkiModule::runNumb_car(){       
//        printf ("Zapros kol-va mashinok \n");
        int result= (int)  myUmki->kol_ust;
 
        return result;};



        	
    void UmkiModule::runNumbUstr(const int numb)
    {
	if (numb>=0) myUmki->SetVibrUst(numb-1);
    };
    
        	
    void UmkiModule::runImpLeftAll(const int imp)
    {
	myUmki->def_diskr_impl = imp;
    };

    void UmkiModule::runImpRightAll(const int imp)
    {
	myUmki->def_diskr_impr = imp;
    };

    void UmkiModule::runImpLeft(const int imp)
    {
        qDebug( "Umki имп лев");

	myUmki->act_ust[myUmki->num_vibr_ust].impl = imp;
    };

    void UmkiModule::runImpRight(const int imp)
    {
	myUmki->act_ust[myUmki->num_vibr_ust].impr = imp;
    };

    void UmkiModule::runSignal(const int sec)
    {
	myUmki->SendCommBip1();

	// zedergka v sec
	double ms=myUmki->GetTime();
	while((myUmki->GetTime()-ms)<sec) ;
	// end zedergka v sec

	myUmki->SendCommStopBip1();
    };
    void UmkiModule::runSvet(const int sec)
    {
	myUmki->SendCommLight1();

	// zedergka v sec
	double ms=myUmki->GetTime();
	while((myUmki->GetTime()-ms)<sec) ;
	// end zedergka v sec
	
	myUmki->SendCommStopLight1();
    };
    
    
} // $namespace
