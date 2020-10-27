#ifndef OPTIONSLOT_H
#define OPTIONSLOT_H

enum KEYPRS
{
    kA,kD,kS,kW,
    kLeft,kRight,kDown,kUp,
    noneKey
};
enum OPTION{moveR,moveL,squat,jump,noneOpt};

struct Queue
{
    KEYPRS keyPrs;
    Queue* next;
    Queue()
    {
        keyPrs=noneKey;
        next=nullptr;
    }
    Queue(KEYPRS key)
    {
        keyPrs=key;
        next=nullptr;
    }
};

class OptionSlot
{
    OPTION option[2];
    Queue* head;
public:
    OptionSlot();
    void addKeyQueue(KEYPRS tKeyPrs);
    void removeKeyQueue(KEYPRS tKeyPrs);
    void setOption(int i);
    OPTION getOption(int i);
    void coutOpt();
    void clear();
};

#endif // OPTIONSLOT_H
