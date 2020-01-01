#include "CPCore.h"
#include "CPCore/App/Window.h"

struct Point {
    int x;
    int y;
};

class Enemy {
public:

    Enemy() = default;
    Enemy( int x, int y, int hp, int damage, int resistance, int level ) 
        :
        pos{ x, y },
        hp{ hp },
        damage{ damage },
        resistance{ resistance },
        level{ level }
    {
    }

    int getDamage() const { return damage; }
    void TakeDamage( int damage ) { 
        int damageTaken = damage-resistance;
        if( damageTaken < 0 ) return;
        hp -= damageTaken;
        if( hp < 0 ) hp = 0;
    }

    int getHP() const { return hp; }
    Point getPos() const { return pos; }
    int getLevel() const { return level; }

private:
    Point pos;
    int hp;
    int damage;
    int resistance;
    int level;
};

class Player {
public:
    Player() {
        x = 0;
        y = 0;
        hp = 20;
        xp = 0;
        damage = 1;
        resistance = 0;
    }

    void attack( Enemy& enemy ) {
        enemy.TakeDamage( damage );
        if( enemy.getHP() == 0 ) xp += enemy.getLevel();
    }

    void attacked( const Enemy& enemy ) {
        int damageTaken = enemy.getDamage() - resistance;             
        if( damageTaken < 0 ) return;
        hp -= damageTaken;
        if( hp < 0 ) hp = 0;
    }

    void move( int offx, int offy ) {
        x += offx;
        y += offy;
    }

    bool improveRes() {
        if( xp < resistance ) return false;
        xp -= resistance;
        resistance++;
        return true;
    }

    bool improveDam() {
        if( xp < damage ) return false;
        xp -= damage;
        damage++;
        return true;
    }

    bool heal() {
        if( xp == 0 || hp == 20 ) return false;
        if( xp > 20-hp ) {
            hp = 20;
            xp -= 20-hp;
            return true;
        }
        hp += xp;
        xp = 0;
        return true;
    }
    
private:
    int x, y;
    int hp;
    int damage;
    int xp;
    int resistance;
};

class Game {
public:
    Game() {
        cpInitConsoleApps();
        cpInitWindowApps();
        console = cpCreateConsole( "Game", "%l" );
        window = cpCreateWindow( "Bad Game", 400, 500 );
        cpSetKeyDownCallback( window, keyDownCallback );
        cpAttachParentClass( window, this );
        enemies[0] ={ 2, 0, 1, 1, 0, 1 };
        enemies[1] ={ 5, 5, 3, 2, 1, 4 };
        enemies[2] ={ -3, 2, 5, 4, 3, 7 };
        enemies[3] ={ 7, 0, 2, 10, 5, 10 };
        enemies[4] ={ 20, 0, 10, 10, 10, 100 };
    }

    ~Game() {
        cpDeleteConsole( console );
        cpUninitConsoleApps();
    }

    bool gameIsRunning() {
        return !cpGetWindowShouldClose( window ); 
    }

    void run() {
        cpPollEvents();
    }

    static void keyDownCallback( CPpwindow window, CPqword key ) {
        Game* game = (Game*)cpGetParentClass( window );
        if( key == XK_Escape ) {
            cpSetWindowShouldClose( window, true );
        }
        if( key == 'a' ) {
            cpConsoleLogTrace( game->console, "MOVE LEFT" );
        } 
        if( key == 'd' ) {
            cpConsoleLogTrace( game->console, "MOVE RIGHT" );
        }
        if( key == 's' ) {
            cpConsoleLogTrace( game->console, "MOVE BACKWARD" );
        }
        if( key == 'w' ) {
            cpConsoleLogTrace( game->console, "MOVE FORWARD" );
        }
    }

private:
    CPpwindow window;
    CPpconsole console;
    Player player;
    Enemy enemies[5];
};

int main()
{
    Game game;
    while( game.gameIsRunning() ) {
        game.run();
    }
	return 0;
}