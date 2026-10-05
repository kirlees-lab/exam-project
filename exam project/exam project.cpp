#include <iostream>
using namespace std;

class Participant
{
protected:
    char* name;
    double stamina;
    double maxRunDistance;
    double maxJumpHeight;

public:
    Participant(const char* name, double stamina, double maxRunDistance, double maxJumpHeight)
    {
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);

        this->stamina = stamina;
        this->maxRunDistance = maxRunDistance;
        this->maxJumpHeight = maxJumpHeight;
    }

    virtual void Run(double distance) = 0;
    virtual void Jump(double height) = 0;
    void Fall()
    {
        stamina -= 20;
    }

    const char* GetName()
    {
        return name;
    }

    double GetStamina()
    {
        return stamina;
    }

    double GetMaxRunDistance()
    {
        return maxRunDistance;
    }

    double GetMaxJumpHeight()
    {
        return maxJumpHeight;
    }

    virtual ~Participant()
    {
        delete[] name;
    }
};

class Person : public Participant
{
public:
    Person(const char* name, double stamina, double maxRunDistance, double maxJumpHeight) : Participant(name, stamina, maxRunDistance, maxJumpHeight)
    {
    }


    void Run(double distance) override
    {
        stamina -= distance * 0.1;
        cout << "Person " << name << " is running " << distance << " meters" << endl;
        cout << "Stamina: " << stamina << endl;
    }

    void Jump(double height) override
    {
        stamina -= height * 10;
        cout << "Person " << name << " jumped up " << height << " meters" << endl;
        cout << "Stamina: " << stamina << endl;
    }
};

class Cat : public Participant
{
public:
    Cat(const char* name, double stamina, double maxRunDistance, double maxJumpHeight) : Participant(name, stamina, maxRunDistance, maxJumpHeight) {}

    void Run(double distance) override
    {
        stamina -= distance * 0.1;
        cout << "Cat " << name << " is running " << distance << " meters" << endl;
        cout << "Stamina: " << stamina << endl;
    }

    void Jump(double height) override
    {
        stamina -= height * 10;
        cout << "Cat " << name << " jumped up " << height << " meters" << endl;
        cout << "Stamina: " << stamina << endl;
    }
};

class Robot : public Participant
{
public:
    Robot(const char* name, double stamina, double maxRunDistance, double maxJumpHeight) : Participant(name, stamina, maxRunDistance, maxJumpHeight) {}

    void Run(double distance) override
    {
        stamina -= distance * 0.1;
        cout << "Robot " << name << " is running " << distance << " meters" << endl;
        cout << "Stamina: " << stamina << endl;
    }

    void Jump(double height) override
    {
        stamina -= height * 10;
        cout << "Robot " << name << " jumped up " << height << " meters" << endl;
        cout << "Stamina: " << stamina << endl;
    }
};


class Obstacle
{
public:
    virtual bool Overcome(Participant* participant) = 0;

    virtual ~Obstacle() {}
};


class RunningTrack : public Obstacle
{
    double distance;

public:
    RunningTrack(double distance)
    {
        this->distance = distance;
    }

    bool Overcome(Participant* participant) override
    {
        cout << participant->GetName() << " sees the running track (" << distance << " meters)" << "\n1.Run \n2.Jump\n->" << endl;
        int c;
        cin >> c;
        if (c ==1)
        {
            if (participant->GetMaxRunDistance() >= distance)
            {
                participant->Run(distance);
                cout << participant->GetName() << " overcomes the running track: ";
                return participant->GetStamina() > 0;
            }
            else
            {
                return false;
            }
        }
        else if (c == 2)
        {
            participant->Jump(1);
            cout << participant->GetName() << " fell" << endl;
            participant->Fall();
            if (participant->GetMaxRunDistance() >= distance)
            {
                participant->Run(distance);
                cout << participant->GetName() << " overcomes the running track: ";
                return participant->GetStamina() > 0;
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << participant->GetName() << " fell" << endl;
            participant->Fall();
            if (participant->GetMaxRunDistance() >= distance)
            {
                participant->Run(distance);
                cout << participant->GetName() << " overcomes the running track: ";
                return participant->GetStamina() > 0;
            }
            else
            {
                return false;
            }
        }
    }
};


class Wall : public Obstacle
{
    double height;

public:
    Wall(double height)
    {
        this->height = height;
    }

    bool Overcome(Participant* participant) override
    {
        cout << participant->GetName() << " sees the wall (" << height << " meters)" << "\n1.Run \n2.Jump\n->" << endl;
        int c;
        cin >> c;
        if (c == 2)
        {
            if (participant->GetMaxJumpHeight() >= height)
            {
                participant->Jump(height);
                cout << participant->GetName() << " overcomes the wall: ";
                return participant->GetStamina() > 0;
            }
            else
            {
                return false;
            }
        }
        else if (c == 1)
        {
            participant->Run(1);
            cout << participant->GetName() << " fell" << endl;
            participant->Fall();
            if (participant->GetMaxJumpHeight() >= height)
            {
                participant->Jump(height);
                cout << participant->GetName() << " overcomes the wall: ";
                return participant->GetStamina() > 0;
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << participant->GetName() << " fell" << endl;
            participant->Fall();
            if (participant->GetMaxJumpHeight() >= height)
            {
                participant->Jump(height);
                cout << participant->GetName() << " overcomes the wall: ";
                return participant->GetStamina() > 0;
            }
            else
            {
                return false;
            }
        }
    }
};


int main()
{
    Person person("Bogdan", 70, 100, 1.56);
    Cat cat("Barsik", 80, 160, 2);
    Robot robot("Atom", 120, 400, 2.2);

    Participant* participants[] =
    {
        &person,
        &cat,
        &robot
    };

    RunningTrack track1(25);
    RunningTrack track2(75);
    RunningTrack track3(150);
    Wall wall2(2);
    Wall wall1(1.5);

    Obstacle* obstacles[] =
    {
        &track1,
        &wall1,
        &track2,
        &wall2,
        &track3
    };

    cout << "Choose participant:" << endl;
    cout << "1. " << person.GetName() << endl;
    cout << "2. " << cat.GetName() << endl;
    cout << "3. " << robot.GetName() << endl;
    cout << "-> ";

    int choice;
    cin >> choice;

    if (choice < 1 || choice > 3)
    {
        cout << "Wrong choice!" << endl;
        return 0;
    }

    Participant* participant = participants[choice - 1];

    cout << "\n================================" << endl;
    cout << "Race started!" << endl;
    cout << "Participant: " << participant->GetName() << endl;
    cout << "\n" << endl;


    for (int i = 0; i < 5; i++)
    {
        cout << "\n--- Obstacle " << i + 1 << " ---" << endl;

        if (!obstacles[i]->Overcome(participant))
        {
            cout << "\n" << participant->GetName()
                << " was eliminated!" << endl;
            break;
        }
    }

    cout << "\n" << endl;
    cout << "Race finished!" << endl;
    cout << "Final stamina: " << participant->GetStamina() << endl;

}