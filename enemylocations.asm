SECTION UNCONTENDED_enemy_locations


PUBLIC _LEVEL_1_ENEMIES_LOCATIONS
_LEVEL_1_ENEMIES_LOCATIONS:
;defs 0x1000


;defb 	x		x_desp	y		sprnum	movement
defb		130,		131,		132,		133,		134
defb		140,		141,		142,		143,		144
defb		150,		151,		152,   	153,		154

;struct Enemy
;{
;	unsigned char x;        // Tile in X
;	unsigned char x_desp;   // Displacement in tile (0-23)
;	unsigned char y;        // Y position
;	unsigned char sprnum;	// Number of the enemy sprite: if 0, this enemy is not active
;	unsigned char movement;	// movement type, from one of the predefined ones
;	unsigned char energy;
;	unsigned char param1;
;	unsigned char param2;	// Two parameters, to store some information that is entity-specific
;} Enemy_structure;




PUBLIC _someting_else
_someting_else:
;defs 0x1000


;defb 	x		x_desp	y		sprnum	movement	energy		param1	param2
defb		01,		02,		03,		04,		05,				06,			07,			08
defb		$0b,		$0c,		$0d,		$0e,		$0f,				$10,			$11,			$12
defb		21,		22,		23,   	24,		25,				26,			27,			28
defb		31,		32,		33,   	34,		25,				36,			37,			38
defb		41,		42,		43,   	44,		25,				46,			47,			48
defb		51,		52,		53,   	54,		25,				56,			57,			58
defb		61,		62,		63,   	64,		25,				66,			67,			68
defb		71,		72,		73,   	74,		25,				76,			77,			78
defb		81,		82,		83,   	84,		25,				86,			87,			88