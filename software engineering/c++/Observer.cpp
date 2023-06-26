#include<iostream>
#include<vector>
using std::cin;
using std::cout;
using std::vector;
/**
 * 1.Observer
 *  1.1只有一个方法update()
 * 
 * 2.Subject 被观察者，通知者
 *  2.1 attach()和detach()用来增删观察者的数量
 *  2.2 setState()和getState()用来获取和设置通知者本身的状态，这个状态通常是传给观察者们的信息
 *  2.3 notify()被观察者通知所有观察者，让观察者根据自己的当前状态(getState())执行自己的update()
 * 
 * 3.ConcreteSubject
 *  
 * 4.ConcreteObserver
*/


/***
我们假定1个事件有3个角色.

1. 指挥者.(Commander)

            指挥炮手打炮, 他可以让让若干个炮手和炮灰纳入自己的命令范围.

2. 炮手, (CannonShooter)

          一旦指挥者通知目标, 若干个炮手就往哪个目标轰击.

3. 炮灰 (CannonFodder)

         一旦指挥者通知, 炮灰就趴下..

也就是说, 炮手必须知道指挥者的状态(目标信号), 到底打谁.

而炮灰是无序关心到底打哪里的, 一旦接到通知, 趴下就是了.

*/
#if 1
class Observer{
public:
    void update();
};

class Subject{
public:
    void attach(Observer obs);
    void detach(Observer obs);
    void notify();
    int  getState();
    void setState(int state);
};

class ConcreateObserver : public Observer{
    public:
    int id;
};

class Commander : public Subject{
    private:
    int targetPlaceID;
    vector<ConcreateObserver> gunnders;

    public:
    void attach(ConcreateObserver obs)
    {
        this->gunnders.push_back(obs);
    }

    void detach(ConcreateObserver obs)
    {
        int i ;
        for( i =0;i<this->gunnders.size();i++)
        {
            if (gunnders[i].id==obs.id)
            break;
        }
        this->gunnders.erase(gunnders.begin()+i);
    }

    void notify()
    {
        if(this->gunnders.empty())
        return;

        for(auto g : gunnders)
        {
            g.update();
        }
    }
};
#endif
