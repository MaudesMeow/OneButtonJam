#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "globals.hpp"
#include "ammo.hpp"

class Player
{
    public:
        int direction;
        Vector2 pos;
        Texture2D playerSprite;
        float speed;
        bool canShoot;
        vector<Ammo*> ammoInventory;
        Rectangle hitBox;
        bool hasTeleported;
        float shooterTimer;
        int score;
        bool isReady;
        int health;
        

        Player() : playerSprite(), pos({0, 0}) {}
        Player(Texture2D playerSprite, Vector2 pos)
        {
            this->playerSprite = playerSprite;
            this->pos = pos;
            direction = 1;
            speed = 160;
            ammoCount = 0;
            canShoot = true;
            hitBox = Rectangle{pos.x,pos.y,32,32};
            hasTeleported = false;
            shooterTimer = 0;
            isReady = false;
            health = 3;
        }
        void AnimatePlayer();
        void HandleInput();
        int GetAmmoCount(){return ammoCount;};
        void SetAmmoCount(int amount){ammoCount = amount;};
        void SetPlayerScore(int newScore){score = newScore;};
        int GetPlayerScore(){return score;};
        void SetPlayerHealth(int newHealth){health = newHealth;};
        int GetPlayerHealth(){return health;};
        void UpdatePlayerBehavior();

    private:
        int ammoCount;
        void BulletBehavior();
};

void DisplayPlayerHealth(int health,Texture2D sprite);

#endif 