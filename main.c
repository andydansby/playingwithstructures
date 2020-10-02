
// compile with 
// zcc +zx -m -create-app -startup=1 -clib=new  main.c -o output

#include <stdio.h>//standard input output
//#include <stdlib.h> // for bpeek
#include <input.h>
#include <arch/spectrum.h>
//#include <cpu.h>


#define z80_bpeek(a)    (*(unsigned char *)(a))

#define MAX_ENEMIES 10




struct Entity
{
	unsigned char x;
	unsigned char y;
	unsigned char sprnum;	// Number of the entity sprite: if 0, this entity is not active
	unsigned char movement;	// movement type, from one of the predefined ones
	unsigned char energy;
	unsigned char param1;
	unsigned char param2;	// Two parameters, to store some information that is entity-specific
}Entity_structure;

//-----------------------------------------------------------------------

// Array of enemy locations in the game
// We use the same Entity structure, with just one difference: X now means the tile

struct Enemy
{
	unsigned char x;        // Tile in X
	unsigned char x_desp;   // Displacement in tile (0-23)
	unsigned char y;        // Y position
	unsigned char sprnum;	// Number of the enemy sprite: if 0, this enemy is not active
	unsigned char movement;	// movement type, from one of the predefined ones
	unsigned char energy;
	unsigned char param1;
	unsigned char param2;	// Two parameters, to store some information that is entity-specific
} Enemy_structure;
//-----------------------------------------------------------------------

struct {
    unsigned char x;//position
    unsigned char x_desp;//velocity
    unsigned char y;//acceleration
    unsigned char sprnum;
    unsigned char movement;
}bodies[3];


unsigned char temp1;
unsigned char temp2;
unsigned char BOB;
unsigned char TIM;
unsigned char BILL;

// Array of existing enemies and shoots (max 8 enemies for now)
//struct Entity active_enemies[MAX_ENEMIES];
//struct Entity my_active_shoots[MAX_ENEMIES];
//struct Entity enemy_active_shoots[MAX_ENEMIES];
//struct Entity power_up;			// Only one powerup active at a time...


//-----------------------------------------------------------------------





unsigned char TAM;//temp variable

struct Enemy enemy_locations[128]; // up to 128 enemies per level, 8 bytes per enemy: 1K
//	struct Enemy *enemy_locations = 0xF800; // up to 256 enemies per level, 8 bytes per enemy: 2K, WARNING: this is placed in RAM 4
//struct Enemy enemy_locations[128]; // up to 128 enemies per level, 8 bytes per enemy: 1K



unsigned int SUE;
unsigned int keypress;

unsigned char *MIA;
unsigned int *enemyPointer;
//-----------------------------------------------------------------------




void setBodies_structure (void)
{
	//sets the struct array item by item
	bodies[0].x = 100;
	bodies[0].x_desp = 101;
	bodies[0].y = 102;
	bodies[0].sprnum = 103;
	bodies[0].movement = 104;
	
	bodies[1].x = 110;
	bodies[1].x_desp = 111;
	bodies[1].y = 112;
	bodies[1].sprnum = 113;
	bodies[1].movement = 114;
	
	bodies[2].x = 120;
	bodies[2].x_desp = 121;
	bodies[2].y = 122;
	bodies[2].sprnum = 123;
	bodies[2].movement = 124;
}

void printBodies_structure()
{
	printf("bodies Struct Members\n");
	
	for (temp1 = 0; temp1 < 3; temp1 ++)
	{
		printf("%d\n", bodies[temp1].x);
		printf("%d\n", bodies[temp1].x_desp);
		printf("%d\n", bodies[temp1].y);
		printf("%d\n", bodies[temp1].sprnum);
		printf("%d\n", bodies[temp1].movement);
	}
	
	printf("\nPress a key\n");
}

void setVariables()
{
	BOB = 0;
}

void pointerPrintL1 ()
{
	extern unsigned int LEVEL_1_ENEMIES_LOCATIONS;
		
	SUE = &LEVEL_1_ENEMIES_LOCATIONS;
	
	printf(" LEVEL_1_ENEMIES_LOCATIONS\n pointer address\n\n");
	
	printf("%u\n", SUE);
	printf("%x\n", SUE);
	
	
	printf("\nPress the ANY key\nWherever that is");
}

void printEntity_structure()
{
	printf("Entity_structure Struct Members\n");
	
	printf("%d\n", Entity_structure.x);
	printf("%d\n", Entity_structure.y);
	printf("%d\n", Entity_structure.movement);
	printf("%d\n", Entity_structure.energy);
	printf("%d\n", Entity_structure.param1);
	printf("%d\n", Entity_structure.param2);
	
	printf("\nPress a key\n");
}

void printEnemy_structure()
{
	printf("Enemy_structure Struct Members\n");
	
	printf("%d\n", Enemy_structure.x);
	printf("%d\n", Enemy_structure.x_desp);
	printf("%d\n", Enemy_structure.y);
	printf("%d\n", Enemy_structure.sprnum);
	printf("%d\n", Enemy_structure.movement);
	printf("%d\n", Enemy_structure.energy);
	printf("%d\n", Enemy_structure.param1);
	printf("%d\n", Enemy_structure.param2);
	
	printf("\nPress a key\n");
}


void set_Entity_structure ()
{
	// Access array members
	//Entity_structure = $97AD
	Entity_structure.x = 1; 
	Entity_structure.y= 2; 
	Entity_structure.movement = 4;
	Entity_structure.energy = 8;	
	Entity_structure.param1 = 16; 
	Entity_structure.param2= 32; 
}

void set_Enemy_structure()
{
	//-------------------------------------------------------------------
	// Access array members
	//Enemy_structure = $97AD
	Enemy_structure.x = 1; 
	Enemy_structure.x_desp = 2; 
	Enemy_structure.y= 4; 
	Enemy_structure.sprnum= 8;
	Enemy_structure.movement = 16;
	Enemy_structure.energy = 32;	
	Enemy_structure.param1 = 64; 
	Enemy_structure.param2= 128; 
}

void pauseWipe (void)
{
	in_wait_key();
	//keypress = n_wait_key();
	//keypress = in_WaitForKey();
	//in_Inkey();
	in_pause(100);
	zx_cls(INK_BLACK | PAPER_WHITE);
	puts("\x16\x01\x02");
}

void fillEnemyLocationsArray (void)
{
	extern unsigned int LEVEL_1_ENEMIES_LOCATIONS;
	
	SUE = &LEVEL_1_ENEMIES_LOCATIONS;//address of pointer

	for (temp1 = 0; temp1 < 3; temp1 ++)// 3 = number of baddes
	{
		bodies[temp1].x = z80_bpeek(SUE);//value of pointer
		SUE ++;
		bodies[temp1].x_desp = z80_bpeek(SUE);//value of pointer
		SUE ++;
		bodies[temp1].y = z80_bpeek(SUE);//value of pointer
		SUE ++;
		bodies[temp1].sprnum = z80_bpeek(SUE);//value of pointer
		SUE ++;
		bodies[temp1].movement = z80_bpeek(SUE);//value of pointer
		SUE ++;		
	}	
}


void printEnemyArray()
{
	printf("Entity_structure Struct Members\n");
	
	
	for (temp1 = 0; temp1 < 3; temp1 ++)// 3 = number of baddes
	{
		printf("%d\n", bodies[temp1].x);
		printf("%d\n", bodies[temp1].x_desp);
		printf("%d\n", bodies[temp1].y);
		printf("%d\n", bodies[temp1].sprnum);
		printf("%d\n", bodies[temp1].movement);
		printf("-----------\n");
	}
	
	printf("\nPress any key\n");
}


void main (void)
{
	
	while (1)
	{
	
		zx_cls(INK_BLACK | PAPER_WHITE);
		puts("\x16\x01\x02");
		//		\x16 == set cursor position
		//		\x01 = x position (01) in hex
		//		\x02 = y position (0C) in hex
		
		setVariables();

	//	printf("Entity_structure Struct Members\n");
		set_Entity_structure();	
		printEntity_structure();		
		pauseWipe();

	//	printf("Enemy_structure Struct Members\n");
		set_Enemy_structure();
		printEnemy_structure();		
		pauseWipe();
		
		setBodies_structure();//
		printBodies_structure();
		pauseWipe();
		
		
		pointerPrintL1 ();		
		pauseWipe();
		
		fillEnemyLocationsArray ();
		printEnemyArray();
		pauseWipe();
		
		//look at enemy_locations[]
		
		
	}
	
}







