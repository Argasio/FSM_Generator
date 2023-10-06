#ifndef EDITORMODE_H
#define EDITORMODE_H

enum ModeId_t
{
    ModeId_Select,
    ModeId_Draw_Rect,
    ModeId_Draw_Arrow,

};

class EditorMode
{
    ModeId_t modeId;
public:
    EditorMode(ModeId_t _modeId)
    {
        modeId = _modeId;
    }
    virtual void Exit(EditorMode* newMode) {;};
    virtual void Enter(){;}
    virtual void Action_Click(float x, float y){;};


};



#endif // EDITORMODE_H
