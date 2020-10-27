#include "optionslot.h"
#include <qdebug.h>

OptionSlot::OptionSlot()
{
    option[1]=option[0]=noneOpt;
    head=nullptr;
}

void OptionSlot::addKeyQueue(KEYPRS tKeyPrs)
{
    if(tKeyPrs==kS||tKeyPrs==kDown)
    {
        Queue* p;
        p=new Queue(tKeyPrs);
        p->next=head;
        head=p;
        return;
    }
    if(head==nullptr)
    {
        head=new Queue(tKeyPrs);
    }
    else
    {
        Queue* p=head;
        while (p->next!=nullptr)
        {

            p=p->next;
        }
        p->next=new Queue(tKeyPrs);
    }
}

void OptionSlot::removeKeyQueue(KEYPRS tKeyPrs)
{
    Queue* p=head,*pp;
    if(head==nullptr)
        return;
    if(head->keyPrs==tKeyPrs)
    {
        head=head->next;
        delete p;
        return;
    }
    while(p->next!=nullptr)
    {

        if(p->next->keyPrs==tKeyPrs)
        {
            pp=p->next;
            p->next=pp->next;

            delete pp;
            return;
        }
        p=p->next;
    }
}

void OptionSlot::setOption(int i)
{
    Queue *p=head;
    if (i==0)
    {
        while(p!=nullptr)
        {
            if(p->keyPrs==kS)
            {
                option[0]=squat;
                break;
            }
            if(p->keyPrs==kA){
                option[0]=moveL;
                break;
            }
            if(p->keyPrs==kD){
                option[0]=moveR;
                break;
            }
            p=p->next;
        }
        if(p==nullptr)
            option[0]=noneOpt;
    }
    else
    {
        while (p!=nullptr)
        {
            if(p->keyPrs==kDown)
            {
                option[1]=squat;
                break;
            }
            if(p->keyPrs==kLeft){
                option[1]=moveL;
                break;
            }
            if(p->keyPrs==kRight){
                option[1]=moveR;
                break;
            }
            p=p->next;
        }
        if(p==nullptr)
            option[1]=noneOpt;
    }
}
OPTION OptionSlot::getOption(int i)
{
    return option[i];
}

void OptionSlot::coutOpt()
{
    Queue *p=head;
    //qDebug()<<"output";
    while (p!=nullptr)
    {
        //qDebug()<<p->keyPrs;
        p=p->next;
    }
}

void OptionSlot::clear()
{
    Queue *p;
    while (head!=nullptr)
    {
        p=head;
        head=head->next;
        delete p;
    }
}
