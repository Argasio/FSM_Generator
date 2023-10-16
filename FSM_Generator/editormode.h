#ifndef EDITORMODE_H
#define EDITORMODE_H
#include<QDebug>
#include<QObject>
enum ModeId_t
{
    ModeId_Select,
    ModeId_Draw_Rect,
    ModeId_Draw_Arrow,
    ModeId_Max

};
/*
QMap<ModeId_t, QString> ModeMap
    {
    {ModeId_Select, "ModeId_Select"},
    {ModeId_Draw_Rect ,"ModeId_Draw_Rect"},
    {ModeId_Draw_Arrow,"ModeId_Draw_Arrow"},

};*/

class EditorMode: public QObject
{
    Q_OBJECT
    ModeId_t modeId;
public:
    EditorMode(ModeId_t _modeId)
    {
        modeId = _modeId;
    }
    virtual void Exit(EditorMode* newMode) {;};
    virtual void Enter(){;}
    virtual void Event_MouseRightClick(float x, float y, int mouseFlags, int keyboardFlags){;};
    virtual void Event_MouseMove(float x, float y, int mouseFlags, int keyboardFlags){;}
    virtual void Event_MouseDoubleClick(float x, float y, int mouseFlags, int keyboardFlags){;}
    virtual void Event_MouseLeftClick(float x, float y, int mouseFlags, int keyboardFlags){;}
    virtual ~EditorMode(){
        qDebug()<<"ModeDeleted";
    }

};



#endif // EDITORMODE_H
