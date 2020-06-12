//demonstrate override
#include <iostream>

using std::cout;

class Enemy
{
public:
    Enemy(int damage = 10);
    void virtual Taunt() const; // made virtual to be overriden
    void virtual Attack() const;
private:
    int m_Damage;
};

Enemy::Enemy(int damage):
    m_Damage(damage)
{}

void Enemy::Taunt() const
{
    cout << "The enemy says he will fight you.\n";
}

void Enemy::Attack() const
{
    cout << "Attack inflicts " << m_Damage << " damage points.\n";
}

class Boss : public Enemy
{
public:
    Boss(int damage = 30);
    void virtual Taunt() const;
    void virtual Attack() const;
};

Boss::Boss(int damage):
    Enemy(damage)
{}

void Boss::Taunt() const
{
    cout << "The boss says he will end your pitiful existence.\n";
}

void Boss::Attack() const
{
    Enemy::Attack();
    cout << "And laugh heartily at you\n";
}

int main()
{
    cout << "Enemy object: \n";
    Enemy anEnemy;
    anEnemy.Taunt();
    anEnemy.Attack();

    cout << "\n\nBoss object: ";
    Boss aBoss;
    aBoss.Taunt();
    aBoss.Attack();

    return 0;
}