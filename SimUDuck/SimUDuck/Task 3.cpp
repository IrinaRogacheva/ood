#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

typedef std::function<void()> Strategy;

void FlyWithWings() 
{ 
    cout << "I'm flying with wings!!" << endl; 
}

void FlyNoWay()
{
    cout << "I don't fly!!" << endl;
}

void MakeQuack() 
{
    cout << "Quack Quack!!!" << endl;
}

void Squeak()
{
    cout << "Squeek!!!" << endl;
}

void MuteQuack()
{
    cout << "I don't make any sounds" << endl;
}

void DanceWaltz()
{
    cout << "I'm dancing waltz" << endl;
}

void DanceMinuet()
{
    cout << "I'm dancing minuet" << endl;
}

void DanceNoWay()
{
    cout << "I don't dance" << endl;
}

class Duck 
{
public:
    Duck(Strategy flyBehavior,
        Strategy quackBehavior,
        Strategy danceBehavior)
        : m_quackBehavior(quackBehavior)
        , m_flyBehavior(flyBehavior) 
        , m_danceBehavior(danceBehavior)
    {
        assert(m_quackBehavior);
        assert(m_flyBehavior);
        assert(m_danceBehavior);
    }
    void Quack()
    {
        m_quackBehavior();
    }
    void Swim() 
    { 
        cout << "I'm swimming" << endl; 
    }
    void Fly() const
    { 
        m_flyBehavior();
    }
    void Dance() const
    { 
        m_danceBehavior(); 
    }
    void SetFlyBehavior(Strategy flyBehavior)
    {
        m_flyBehavior = flyBehavior;
    }
    virtual void Display() const = 0;
    virtual ~Duck() = default;

private:
  Strategy m_flyBehavior;
  Strategy m_quackBehavior;
  Strategy m_danceBehavior;
};

class MallardDuck : public Duck {
public:
    MallardDuck()
        : Duck(FlyWithWings, MakeQuack, DanceWaltz)
    {
    }

    void Display() const override 
    { 
        cout << "I'm mallard duck" << endl; 
    }
};

class RedheadDuck : public Duck {
public:
    RedheadDuck()
        : Duck(FlyWithWings, MakeQuack, DanceMinuet)
    {
    }
    void Display() const override 
    { 
        cout << "I'm redhead duck" << endl; 
    }
};
class DecoyDuck : public Duck {
public:
    DecoyDuck()
        : Duck(FlyNoWay, MuteQuack, DanceNoWay) 
    {
    }
    void Display() const override 
    { 
        cout << "I'm decoy duck" << endl; 
    }
};
class RubberDuck : public Duck {
public:
    RubberDuck() : Duck(FlyNoWay, Squeak, DanceNoWay)
    {
    }
    void Display() const override 
    { 
        cout << "I'm rubber duck" << endl; 
    }
};

class ModelDuck : public Duck {
public:
    ModelDuck() : Duck(FlyNoWay, MakeQuack, DanceNoWay)
    {
    }
    void Display() const override 
    { 
        cout << "I'm model duck" << endl; 
    }
};

void DrawDuck(Duck const& duck)
{
    duck.Display();
}

void PlayWithDuck(Duck& duck)
{
    DrawDuck(duck);
    duck.Quack();
    duck.Fly();
    duck.Dance();
    cout << endl;
}

int main()
{
    MallardDuck mallardDuck;
    PlayWithDuck(mallardDuck);

    RedheadDuck redheadDuck;
    PlayWithDuck(redheadDuck);

    RubberDuck rubberDuck;
    PlayWithDuck(rubberDuck);

    DecoyDuck decoyDuck;
    PlayWithDuck(decoyDuck);

    ModelDuck modelDuck;
    PlayWithDuck(modelDuck);
    modelDuck.SetFlyBehavior(FlyWithWings);
    PlayWithDuck(modelDuck);
}