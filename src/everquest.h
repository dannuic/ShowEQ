/*
 *  everquest.h
 *
 *  ShowEQ Distributed under GPL
 *  http://seq.sourceforge.net/
 */


/*
** Please be kind and remember to correctly re-order
** the values in here whenever you add a new item,
** thanks.  - Andon
*/


/*
** Structures used in the network layer of Everquest
*/

#ifndef EQSTRUCT_H
#define EQSTRUCT_H

#include <stdint.h>

/*
** ShowEQ specific definitions
*/
// Statistical list defines
#define LIST_HP                         0
#define LIST_MANA                       1
#define LIST_STAM                       2
#define LIST_EXP                        3
#define LIST_FOOD                       4
#define LIST_WATR                       5
#define LIST_STR                        6
#define LIST_STA                        7
#define LIST_CHA                        8
#define LIST_DEX                        9
#define LIST_INT                        10
#define LIST_AGI                        11
#define LIST_WIS                        12
#define LIST_MR                         13
#define LIST_FR                         14
#define LIST_CR                         15
#define LIST_DR                         16
#define LIST_PR                         17
#define LIST_AC                         18
#define LIST_ALTEXP                     19
#define LIST_MAXLIST                    20 

// direction the data is coming from
#define DIR_CLIENT 1
#define DIR_SERVER 2

/*
** MOB Spawn Type
*/
#define SPAWN_PLAYER                    0
#define SPAWN_NPC                       1
#define SPAWN_PC_CORPSE                 2
#define SPAWN_NPC_CORPSE                3
#define SPAWN_NPC_UNKNOWN               4
#define SPAWN_COINS                     5
#define SPAWN_DROP                      6
#define SPAWN_DOOR                      7
#define SPAWN_SELF                      10

/* 
** Diety List
*/
#define DEITY_UNKNOWN                   0
#define DEITY_AGNOSTIC			396
#define DEITY_BRELL			202
#define DEITY_CAZIC			203
#define DEITY_EROL			204
#define DEITY_BRISTLE			205
#define DEITY_INNY			206
#define DEITY_KARANA			207
#define DEITY_MITH			208
#define DEITY_PREXUS			209
#define DEITY_QUELLIOUS			210
#define DEITY_RALLOS			211
#define DEITY_SOLUSEK			213
#define DEITY_TRIBUNAL			214
#define DEITY_TUNARE			215

//Guessed:
#define DEITY_BERT			201	
#define DEITY_RODCET			212
#define DEITY_VEESHAN			216

//Team numbers for Deity teams
#define DTEAM_GOOD			1
#define DTEAM_NEUTRAL			2
#define DTEAM_EVIL			3
#define DTEAM_OTHER			5

//Team numbers for Race teams
#define RTEAM_HUMAN			1
#define RTEAM_ELF			2
#define RTEAM_DARK			3
#define RTEAM_SHORT			4
#define RTEAM_OTHER			5

//Maximum limits of certain types of data
#define MAX_KNOWN_SKILLS                74
#define MAX_KNOWN_LANGS                 25

//Item Flags
#define ITEM_NORMAL                     0x0000
#define ITEM_NORMAL1                    0x0031
#define ITEM_NORMAL2                    0x0036
#define ITEM_NORMAL3                    0x315f
#define ITEM_NORMAL4                    0x3336
#define ITEM_NORMAL5                    0x0032
#define ITEM_NORMAL6                    0x0033
#define ITEM_NORMAL7                    0x0034
#define ITEM_NORMAL8                    0x0039
#define ITEM_CONTAINER                  0x7900
#define ITEM_CONTAINER_PLAIN            0x7953
#define ITEM_BOOK                       0x7379

// Item spellId no spell value
#define ITEM_SPELLID_NOSPELL            0xffff

//Combat Flags
#define COMBAT_MISS						0
#define COMBAT_BLOCK					-1
#define COMBAT_PARRY					-2
#define COMBAT_RIPOSTE					-3
#define COMBAT_DODGE					-4

#define PLAYER_CLASSES     15
#define PLAYER_RACES       14
/*
** Compiler override to ensure
** byte aligned structures
*/
#pragma pack(1)

/*
**            Generic Structures used in specific
**                      structures below
*/

// OpCode stuff (For SINS Migrations)
struct opCode
{
  uint8_t code;
  uint8_t version;

  // kinda silly -- this is required for us to be able to stuff them in a QValueList
  bool operator== ( const struct opCode t ) const
  {
    return ( code == t.code && version == t.version );
  }
  bool operator== ( uint16_t opCode ) const
  {
    return ( *((uint16_t*)&code) == opCode );
  }
};
typedef struct opCode OpCode;

/*
** Buffs
** Length: 16 Octets
** Used in:
**    charProfileStruct(2d20)
*/
struct spellBuff
{
/*0000*/ int32_t  unknown0000;            // ***Placeholder
/*0004*/ int8_t   unknown0001;
/*0005*/ int8_t   level;                  // Level of person who casted buff
/*0006*/ int8_t   unknown0002[2];         // ***Placeholder
/*0008*/ int32_t  spell;                  // Spell
/*0012*/ int32_t  duration;               // Duration in ticks
}; // 16

/*
** Generic Item structure
** Length: 244 Octets
** Used in:
**    itemShopStruct(0c20), tradeItemInStruct(5220),
**    playerItemStruct(6421), playerBookStruct(6521),
**    playerContainerStruct(6621), summonedItemStruct(7821),
**    tradeItemInStruct(df20),
*/

// this is the base structure from which all items are based
struct itemStruct
{
/*0000*/ char      name[64];        // Name of item
/*0064*/ char      lore[80];        // Lore text
/*0144*/ char      idfile[30];      // 3D model
/*0174*/ uint8_t   weight;          // Weight of item
/*0175*/ int8_t    nosave;          // Nosave flag 1=normal, 0=nosave, -1=spell?
/*0176*/ int8_t    nodrop;          // Nodrop flag 1=normal, 0=nodrop, -1=??
/*0177*/ uint8_t   size;            // Size of item
/*0178*/ uint8_t   itemClass;       // 0 - generic item, 1 - container, 2 - book
/*0179*/ uint8_t   unknown0178;     // ***Placeholder
/*0180*/ uint32_t  itemNr;          // Unique Item number
/*0184*/ uint32_t  iconNr;          // Icon Number
/*0188*/ int16_t   equipSlot;       // Current Equip slot
/*0190*/ uint8_t   unknwn0186[2];      // Equip slot cont.?
/*0192*/ uint32_t  equipableSlots;  // Slots where this item goes
/*0196*/ int32_t   cost;            // Item cost in copper
/*0196*/ uint8_t   unknown0196[40]; // ***Placeholder
};

// Common Item Structure (non-book non-containers)
struct itemItemStruct : public itemStruct
{
// 0240- have different meanings depending on flags
/*0240*/ int8_t   STR;              // Strength
/*0241*/ int8_t   STA;              // Stamina
/*0242*/ int8_t   CHA;              // Charisma
/*0243*/ int8_t   DEX;              // Dexterity
/*0244*/ int8_t   INT;              // Intelligence
/*0245*/ int8_t   AGI;              // Agility
/*0246*/ int8_t   WIS;              // Wisdom
/*0247*/ int8_t   MR;               // Magic Resistance
/*0248*/ int8_t   FR;               // Fire Resistance
/*0249*/ int8_t   CR;               // Cold Resistance
/*0250*/ int8_t   DR;               // Disease Resistance
/*0251*/ int8_t   PR;               // Poison Resistance
/*0252*/ int32_t  HP;               // Hitpoints
/*0256*/ int32_t  MANA;             // Mana
/*0260*/ int32_t  AC;               // Armor Class
/*0264*/ int8_t   maxcharges;       // Max charges on charged item
/*0265*/ uint8_t  unknown0246;      // ***Placeholder
/*0266*/ uint8_t  light;            // Light effect of this item
/*0267*/ uint8_t  delay;            // Weapon Delay
/*0268*/ uint8_t  damage;           // Weapon Damage
/*0269*/ uint8_t  unknown0251;      // ***Placeholder
/*0270*/ uint8_t  range;            // Range of weapon
/*0271*/ uint8_t  skill;            // Skill of this weapon
/*0272*/ int8_t   magic;            // Magic flag
                        //   00  (0000)  =   ???
                        //   01  (0001)  =  magic
                        //   12  (1100)  =   ???
                        //   14  (1110)  =   ???
                        //   15  (1111)  =   ???
/*0273*/ int8_t   level0;           // Casting level
/*0274*/ uint8_t  material;         // Material?
/*0275*/ uint8_t  unknown0258[1];   // ***Placeholder
/*0276*/ uint32_t color;            // Amounts of RGB in original color
/*0280*/ uint8_t  unknown0264[4];   // ***Placeholder
/*0284*/ uint32_t spellId0;         // SpellID of special effect
/*0288*/ uint32_t classes;          // Classes that can use this item
/*0292*/ uint32_t races;            // Races that can use this item
/*0296*/ int8_t   stackable;        //  1= stackable, 3 = normal, 0 = ? (not stackable)
/*0297*/ uint8_t  level;            // Casting level

  union // 0298 has different meanings depending on an stackable
  {
    /*0298*/ int8_t   number;          // Number of items in stack
    /*0298*/ int8_t   charges;         // Number of charges (-1 = unlimited)
  };

/*0299*/ int8_t   effectType;       // 0 = no effect, 1=click anywhere w/o class check, 2=latent/worn, 3=click anywhere EXPENDABLE, 4=click worn, 5=click anywhere w/ class check
/*0300*/ uint32_t spellId;          // spellId of special effect
/*0304*/ uint8_t  unknown0282[12];  // ***Placeholder
/*0316*/ uint32_t castTime;         // Cast time of clicky item in miliseconds
/*0320*/ uint8_t  unknown0296[16];  // ***Placeholder
/*0336*/ uint32_t skillModId;       // ID of skill that item modifies
/*0340*/ int32_t  skillModPercent;  // Percent that item modifies skill
/*0344*/ uint8_t  unknown0315[120];
}; // 432
 
// Book Structure (flag == 0x7379) 
struct itemBookStruct : public itemStruct
{
  /*0240*/ uint8_t  unknown0228[3];      // ***Placeholder
  /*0243*/ char     file[15];            // Filename of book text on server
  /*0258*/ uint8_t  unknown0246[18];     // ***Placeholder 
  // pad out to 276
};

// Container Structure (flag == 0x7900 || flag == 0x7953
struct itemContainerStruct : public itemStruct
{
  /*0240*/ int8_t   unknown0228[41];     // ***Placeholder
  /*0281*/ uint8_t  numSlots;            // number of slots in container
  /*0282*/ int8_t   unknown0271;         // ***Placeholder
  /*0283*/ int8_t   sizeCapacity;        // Maximum size item container can hold
  /*0284*/ uint8_t  weightReduction;     // % weight reduction of container
  /*0285*/ uint8_t  unknown0273[3];     // ***Placeholder
  // pad out to 0288
};


/*
** Generic Item Properties
** Length: 16 Octets
** Used in: charProfile
**
*/

struct itemPropertiesStruct
{
/*000*/ uint8_t    unknown01[2];
/*002*/ int8_t     charges;         // not sure if this is in the right place
/*003*/ uint8_t    unknown02[13];
};


/*
** Simple Spawn Update
** Length: 11 Octets
*/

struct spawnPositionUpdate 
{
/*0000*/ uint16_t opcode;		// 0x0002
/*0002*/ int16_t  spawnId;             // Id of spawn to update
/*0004*/ int16_t  y;                   // New Y position of spawn
/*0006*/ int16_t  x;                   // New X position of spawn
/*0009*/ int16_t  z;                   // New Z position of spawn
/*0010*/ int8_t   heading;
};


/* 
** Generic Spawn Struct 
** Length: 260 Octets 
** Used in: 
**   spawnZoneStruct
**   dbSpawnStruct
**   petStruct
**   newSpawnStruct
*/ 

struct spawnStruct
{
/*0000*/ int32_t  petOwnerId;
/*0009*/ signed   deltaY:10;              // Velocity Y
         unsigned spacer1:1;              // Placeholder
         signed   deltaZ:10;              // Velocity Z
         unsigned spacer2:1;              // ***Placeholder
         signed   deltaX:10;              // Velocity X
/*0008*/ int16_t y;			 // y loc
/*0010*/ int16_t x;			 // x loc
/*0012*/ int16_t z;			 // z loc
/*0014*/ int8_t animation;		 // animation
/*0015*/ int8_t deltaHeading;		 // delta heading
/*0016*/ int8_t heading;		 // heading
/*0017*/ uint8_t unknown0017[35];        // ***Placeholder
/*0052*/ uint8_t light;			 // location on this is wrong
/*0053*/ uint8_t unknown0053[15];	 // ***Placeholder
/*0068*/ uint16_t spawnId;		 // Id of spawn
/*0070*/ uint8_t unknown0070[2];	 // ***Placeholder
/*0072*/ int32_t guildID;		 // GuildID
/*0076*/ uint32_t typeflag;		 // Bodytype
/*0080*/ int32_t curHp;			 // Current hp
/*0084*/ uint8_t unknown0084[3];	 // ***Placeholder
/*0087*/ uint8_t npc_armor_graphic;	 // 0xFF=Player, 0=none, 1=leather, 2=chain, 3=plate
/*0088*/ uint8_t npc_helm_graphic;	 // 0xFF=Player, 0=none, 1=leather, 2=chain, 3=plate
/*0089*/ uint8_t unknown0089[3];	 // ***Placeholder
/*0092*/ int32_t maxHp;			 // max hp
/*0096*/ int32_t race;			 // race
/*0100*/ uint8_t NPC;			 // 0=player,1=npc,2=pc corpse,3=npc corpse,4=???,5=unknown spawn,10=self
/*0101*/ uint8_t class_;		 // class
/*0102*/ uint8_t gender;		 // 0=male, 1=female, 2=other
/*0103*/ uint8_t level;			 // level
/*0104*/ uint8_t unknown104[9];		 // ***Placeholder
/*0113*/ char name[64];			 // name
/*0177*/ uint8_t unknown177[3];		 // ***Placeholder
/*0180*/ int32_t equipment[9];		 // 0=helm, 1=chest, 2=arm, 3=bracer
			// 4=hand, 5=leg 6=boot, 7=melee1, 8=melee2
/*0216*/ char lastName[20];		 // lastname
/*0236*/ uint8_t unknown0263[12];	 // ***Placeholder
/*0248*/ int16_t deity;			 // deity
/*0250*/ uint8_t unknown0250[10];	 // ***Placeholder
}; // 260

/* 
** Zone Spawn Struct 
** Length: 176 Octets 
** Used in: 
**    zoneSpawnStruct
**
*/ 

struct spawnZoneStruct
{
/*0000*/ uint8_t     unknown0000[4];
/*0004*/ spawnStruct spawn;
};

/*
** Generic Door Struct
** Length: 52 Octets
** Used in: 
**    cDoorSpawnsStruct(f721)
**
*/

struct doorStruct
{
/*0000*/ char    name[8];            // Filename of Door?
/*0008*/ uint8_t unknown0008[8];     // ****Placeholder
/*0016*/ float   y;               // y loc
/*0020*/ float   x;               // x loc
/*0024*/ float   z;               // z loc
/*0028*/ uint8_t unknown0028[16];    // ***Placeholder
/*0044*/ uint8_t doorId;             // door's id #
/*0045*/ uint8_t size;               // guess..
/*0046*/ uint8_t unknown0040[6];     // ***Placeholder
}; // 52

/*
**                 ShowEQ Specific Structures
*/

/*
** DB spawn struct (adds zone spawn was in)
*/

struct dbSpawnStruct
{
/*0000*/ struct spawnStruct spawn;      // Spawn Information
/*0156*/ char   zoneName[40];           // Zone Information
};

/*
** Pet spawn struct (pets pet and owner in one struct)
*/

struct petStruct
{
/*0000*/ struct spawnStruct owner;      // Pet Owner Information
/*0156*/ struct spawnStruct pet;        // Pet Infromation
};

/*
**                 Specific Structures defining OpCodes
*/

/*
** Drop Coins
** Length: 114 Octets
** OpCode: dropCoinsCode
*/

struct dropCoinsStruct
{
/*0000*/ uint8_t  opCode;                 // 0x07
/*0001*/ uint8_t  version;		  // 0x20
/*0002*/ uint8_t  unknown0002[24];        // ***Placeholder
/*0026*/ uint16_t dropId;                 // Drop ID
/*0028*/ uint8_t  unknown0028[22];        // ***Placeholder
/*0050*/ uint32_t amount;                 // Total Dropped
/*0054*/ uint8_t  unknown0054[4];         // ***Placeholder
/*0058*/ float    y;                   // Y Position
/*0062*/ float    x;                   // X Position
/*0066*/ float    z;                   // Z Position
/*0070*/ uint8_t  unknown0070[12];        // blank space
/*0082*/ int8_t   type[15];               // silver gold whatever
/*0097*/ uint8_t  unknown0097[17];        // ***Placeholder
};

/*
** Channel Message received or sent
** Length: 71 Octets + Variable Length + 4 Octets
** OpCode: ChannelMessageCode
*/

struct channelMessageStruct
{
/*0000*/ uint8_t  opCode;                 // 0x07
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ char     target[64];             // the target characters name
/*0066*/ char     sender[64];             // The senders name 
/*0130*/ uint8_t  language;               // Language
/*0131*/ uint8_t  unknown0131[3];         // ***Placeholder
/*0134*/ uint8_t  chanNum;                // Channel
/*0135*/ int8_t   unknown0133[11];            // ***Placeholder
/*0146*/ char     message[0];             // Variable length message
};

/*
** Remove Coins
** Length: 10 Octets
** OpCode: removeCoinsCode
*/

struct removeCoinsStruct
{
/*0000*/ uint8_t  opCode;                 // 0x08
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint16_t dropId;                 // Drop ID - Guess
/*0004*/ uint8_t  unknown0004[2];         // ***Placeholder
/*0006*/ uint16_t spawnId;                // Spawn Pickup
/*0008*/ uint8_t  unknown0008[2];         // ***Placeholder
};


/*
** Compressed Item In Shop
** Length: variable
** OpCode cItemInShop
*/

struct cItemInShopStruct
{
/*0000*/ uint8_t  opCode;                 // 
/*0001*/ uint8_t  version;                // 
/*0002*/ uint16_t count;                  // number of items in shop
/*0004*/ uint8_t  compressedData[0];      // All the packets compressed together
};


/*
** Item In Shop
** Length: 255 Octets
** OpCode: ItemInShopCode
*/

struct itemInShopStruct
{
/*0004*/ int16_t   itemType;               // 0 - item, 1 - container, 2 - book
union
{
  /*0005*/ struct itemItemStruct item;        // Refer to itemStruct for members
  /*0005*/ struct itemContainerStruct container;
  /*0005*/ struct itemBookStruct book;
};
/*0297*/ //uint8_t  unknown0297[6];         // ***Placeholder
};

/*
** Server System Message
** Length: Variable Length
** OpCode: SysMsgCode
*/

struct sysMsgStruct
{
/*0000*/ uint8_t  opCode;                 // 0x14
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ char     message[0];             // Variable length message
};

/*
** Emote text
** Length: Variable Text
** OpCode: emoteTextCode
*/

struct emoteTextStruct
{
/*0000*/ uint8_t  opCode;                 // 0x15
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint8_t  unknown0002[2];         // ***Placeholder
/*0004*/ char     text[0];                // Emote `Text
};

/*
** Formatted text messages
** Length: Variable Text
** OpCode: emoteTextCode
*/

struct formattedMessageStruct
{
/*0000*/ uint8_t  opCode;                 // 0x15
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint8_t  unknown0002[2];         // ***Placeholder
/*0003*/ uint16_t messageFormat;          // Indicates the message format
/*0005*/ uint8_t  unknown0004[2];         // ***Placeholder (arguments?)
/*0007*/ char     messages[0];            // messages(NULL delimited)
/*0???*/ uint8_t  unknownXXXX[8];         // ***Placeholder
};

/*
** Corpse location
** Length: 18 Octets
** OpCode: corpseLocCode
*/

struct corpseLocStruct
{
/*0000*/ uint8_t  opCode;                 // 0x21
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint32_t spawnId;
/*0006*/ float    x;
/*0010*/ float    y;
/*0014*/ float    z;
};

/*
** Grouping Infromation
** Length: 138 Octets
** OpCode: groupinfoCode
*/

struct groupInfoStruct
{
/*0000*/ uint8_t  opCode;                 // 0x26
/*0001*/ uint8_t  version;                // 0x40
/*0002*/ uint8_t  unknown0002[4];
/*0006*/ char     yourname[64];           // Player Name
/*0070*/ char     membername[64];         // Goup Member Name
/*0134*/ uint8_t  unknown0130[4];        // ***Placeholder
};
typedef struct groupInfoStruct groupMemberStruct; // new form

/*
** Grouping Invite
** Length 195 Octets
** Opcode GroupInviteCode
*/

struct groupInviteStruct
{
/*0000*/ uint8_t  opCode;                 // 0x40
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ char     yourname[64];           // Player Name
/*0066*/ char     membername[64];         // Invited Member Name
/*0130*/ uint8_t  unknown0130[65];        // ***Placeholder
};

/*
** Grouping Invite Answer - Decline
** Length 131 Octets
** Opcode GroupDeclineCode
*/

struct groupDeclineStruct
{
/*0000*/ uint8_t  opCode;                 // 0x41
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ char     yourname[64];           // Player Name
/*0066*/ char     membername[64];         // Invited Member Name
/*0130*/ uint8_t  reason;                 // Already in Group = 1, Declined Invite = 3
};

/*
** Grouping Invite Answer - Accept 
** Length 130 Octets
** Opcode GroupAcceptCode
*/

struct groupAcceptStruct
{
/*0000*/ uint8_t  opCode;                 // 0x42
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ char     yourname[64];           // Player Name
/*0066*/ char     membername[64];         // Invited Member Name
};

/*
** Grouping Removal
** Length 130 Octets
** Opcode GroupDeleteCode
*/

struct groupDeleteStruct
{
/*0000*/ uint8_t  opCode;                 // 0x44
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ char     yourname[64];           // Player Name
/*0066*/ char     membername[64];         // Invited Member Name
};

/*
** Client Zone Entry struct
** Length: 70 Octets
** OpCode: ZoneEntryCode (when direction == client)
*/

struct ClientZoneEntryStruct
{
/*0000*/ uint8_t  opCode;                 // 0x29
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint32_t unknown0002;            // ***Placeholder
/*0006*/ char     name[32];               // Player firstname
/*0038*/ uint8_t  unknown0036[28];        // ***Placeholder
/*0066*/ uint32_t unknown0066;            // unknown
};

/*
** Server Zone Entry struct
** Length: 390 Octets
** OpCode: ZoneEntryCode (when direction == server)
*/

struct ServerZoneEntryStruct
{
/*0000*/ uint8_t  opCode;                 // 0x29
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint32_t checksum;               // some kind of checksum
/*0006*/ uint8_t  unknown0006;            // unknown
/*0007*/ char     name[64];               // Player first name
/*0071*/ uint8_t  unknown0071[3];
/*0074*/ uint32_t zoneId;                 // zone number
/*0078*/ float    y;
/*0082*/ float    x;
/*0086*/ float    z;
/*0090*/ float    heading;
/*0094*/ uint8_t  unknown0094[76];
/*0170*/ uint32_t guildId;
/*0174*/ uint8_t  unknown0168[5];
/*0179*/ uint8_t  class_;                 // Player's Class
/*0180*/ uint8_t  unknown0180[2];
/*0182*/ uint32_t race;                   // Player's Race
/*0186*/ uint8_t  gender;
/*0187*/ uint32_t level;                  // Player's Level
/*0191*/ uint8_t  unknown0191[83];        // ***Placeholder 
/*0274*/ float    walkspeed;
/*0278*/ float    runspeed;
/*0282*/ uint8_t  unknown0282[20]; 
/*0302*/ uint8_t  anon;
/*0303*/ uint8_t  unknown0303[31];
/*0334*/ char     lastName[20];
/*0354*/ uint8_t  unknown0354[16];
/*0370*/ uint32_t deity;                  // Player's Deity
/*0374*/ uint8_t  unknown0374[16];         // ***Placeholder
/*0390*/
};

/*
** Delete Spawn
** Length: 4 Octets
** OpCode: DeleteSpawnCode
*/

struct deleteSpawnStruct
{
/*0000*/ uint8_t  opCode;                 // 0x2a
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint32_t spawnId;                // Spawn ID to delete
};

/*
** Player Profile
** Length: 8454 Octets
** OpCode: CharProfileCode
*/

struct charProfileStruct 
{
/*0000*/ uint8_t  opCode;                 // 0x36
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint32_t checksum;               // some pre-encryption checksum
/*0006*/ uint8_t  unknown0006[2];         // ***Placeholder
/*0008*/ char     name[64];               // Name of player sizes not right
/*0072*/ char     lastName[20];           // Last name of player sizes not right
/*0092*/ uint8_t  unknown0072[50];
/*0142*/ uint32_t gender;
/*0146*/ uint32_t race;                   // Player race
/*0150*/ uint32_t class_;                 // Player class
/*0154*/ uint32_t unknown0154;
/*0158*/ uint32_t level;                  // Level of player (might be one byte)
/*0162*/ uint32_t exp;                    // Current Experience
/*0166*/ uint32_t points;                 // Unspent Practice points
/*0170*/ uint32_t MANA;                   // MANA
/*0174*/ uint32_t curHp;                  // current hp
/*0178*/ uint32_t unknown0178;            // ***Placeholder
/*0182*/ uint32_t STR;                    // Strength
/*0186*/ uint32_t STA;                    // Stamina
/*0190*/ uint32_t CHA;                    // Charisma
/*0194*/ uint32_t DEX;                    // Dexterity
/*0198*/ uint32_t INT;                    // Intelligence
/*0202*/ uint32_t AGI;                    // Agility
/*0206*/ uint32_t WIS;                    // Wisdom
/*0210*/ uint8_t  unknown0182[48];
/*0258*/ uint32_t inventory[30];          // inventory images?
/*0378*/ uint32_t unknown0378;
/*0382*/ uint8_t  languages[32];          // List of languages (MAX_KNOWN_LANGS)
/*0414*/ uint8_t  unknown0414[8];         // unknown ?more languages?
/*0422*/ struct itemPropertiesStruct invitemprops[30];
                                          // these correlate with inventory[30]
/*0902*/ struct spellBuff buffs[15];      // Buffs currently on the player
/*1142*/ uint32_t unknown1142[2];
/*1150*/ uint32_t containerinv[80];       // player items in containers
/*1470*/ uint32_t cursorinv[10];          // player items on cursor
/*1510*/ struct itemPropertiesStruct containeritemprops[80];
                                          //just like invitemprops[]
/*2790*/ struct itemPropertiesStruct cursoritemprops[10];
                                          //just like invitemprops[]
/*2950*/ int32_t  sSpellBook[512];        // List of the Spells in spellbook
/*4998*/ int32_t  sMemSpells[8];          // List of spells memorized
/*5030*/ uint8_t  unknown5030[36];
/*5066*/ float    y;
/*5070*/ float    x;
/*5074*/ float    z;
/*5078*/ float    heading;
/*5082*/ uint32_t unknown5082;
/*5086*/ uint32_t platinum;               // Platinum Pieces on player
/*5090*/ uint32_t gold;                   // Gold Pieces on player
/*5094*/ uint32_t silver;                 // Silver Pieces on player
/*5098*/ uint32_t copper;                 // Copper Pieces on player
/*5102*/ uint32_t platinumBank;           // Platinum Pieces in Bank
/*5106*/ uint32_t goldBank;               // Gold Pieces in Bank
/*5110*/ uint32_t silverBank;             // Silver Pieces in Bank
/*5114*/ uint32_t copperBank;             // Copper Pieces in Bank
/*5118*/ uint8_t  unknown5118[32];
/*5150*/ uint32_t skills[74];             // List of skills (MAX_KNOWN_SKILLS)
/*5446*/ uint8_t  unknown5446[412];       // ***Placeholder
/*5858*/ uint32_t zoneId;                 // see zones.h
/*5862*/ uint8_t  unknown5862[548];
/*6410*/ uint32_t bindzoneId[5];          // bound to bindzoneId[0]
/*6430*/ float    sYpos[5];               // starting locs per bindzoneId
/*6450*/ float    sXpos[5];               // starting locs per bindzoneId
/*6470*/ float    sZpos[5];               // starting locs per bindzoneId
/*6490*/ uint8_t  unknown9490[20];
/*6510*/ struct itemPropertiesStruct bankinvprops[8];
/*6638*/ struct itemPropertiesStruct bankinvprops2[8];
/*6766*/ struct itemPropertiesStruct bankinvcontprops[80];
/*8046*/ struct itemPropertiesStruct bankinvcontprops2[80];
/*9326*/ uint8_t  unknown9326[4];
/*9330*/ uint32_t bank_inv[8];            // itemIds of the 8 bank slots
/*9362*/ uint32_t bank_inv2[8];           // itemIds of the 8 bank slots
/*9394*/ uint32_t bank_cont_inv[80];      // itemIds of items inside containers in bank
/*9714*/ uint32_t bank_cont_inv2[80];     // itemIds of items inside containers in bank
/*10034*/ uint32_t deity;                  // deity
/*10038*/ uint32_t guildID;                // guild ID
/*10042*/ uint8_t  unknown10042[14];
/*10056*/ uint8_t  pvp;
/*10057*/ uint8_t  _level;                 // seems to be player level
/*10058*/ uint8_t  anon;                   // 0 plain, 1 anon, 2 roleplay,
/*10059*/ uint8_t  gm;                     // gm flag?
/*10060*/ uint8_t  guildstatus;            // 0 member, 1 officer, 2 leader
/*10061*/ uint8_t  unknown10061[44];
/*10105*/ char     GroupMembers[6][64];    // all the members in group, including self
/*10489*/ uint8_t  unknown10489[24];
/*10513*/ uint32_t altexp;                 // alternate exp pool 0 - ~15,000,000
/*10517*/ uint8_t  unknown10517[428];
/*10945*/ uint32_t aapoints;               // number of unspent ability points
/*10949*/ uint8_t  unknown10949[2625];
}; // 13562

#if 0
struct playerAAStruct {
/*    0 */  uint8 unknown0;
  union {
    uint8 unnamed[17];
    struct _named {  
/*    1 */  uint8 innate_strength;
/*    2 */  uint8 innate_stamina;
/*    3 */  uint8 innate_agility;
/*    4 */  uint8 innate_dexterity;
/*    5 */  uint8 innate_intelligence;
/*    6 */  uint8 innate_wisdom;
/*    7 */  uint8 innate_charisma;
/*    8 */  uint8 innate_fire_protection;
/*    9 */  uint8 innate_cold_protection;
/*   10 */  uint8 innate_magic_protection;
/*   11 */  uint8 innate_poison_protection;
/*   12 */  uint8 innate_disease_protection;
/*   13 */  uint8 innate_run_speed;
/*   14 */  uint8 innate_regeneration;
/*   15 */  uint8 innate_metabolism;
/*   16 */  uint8 innate_lung_capacity;
/*   17 */  uint8 first_aid;
    } named;
  } general_skills;
  union {
    uint8 unnamed[17];
    struct _named {
/*   18 */  uint8 healing_adept;
/*   19 */  uint8 healing_gift;
/*   20 */  uint8 unknown20;
/*   21 */  uint8 spell_casting_reinforcement;
/*   22 */  uint8 mental_clarity;
/*   23 */  uint8 spell_casting_fury;
/*   24 */  uint8 chanelling_focus;
/*   25 */  uint8 unknown25;
/*   26 */  uint8 unknown26;
/*   27 */  uint8 unknown27;
/*   28 */  uint8 natural_durability;
/*   29 */  uint8 natural_healing;
/*   30 */  uint8 combat_fury;
/*   31 */  uint8 fear_resistance;
/*   32 */  uint8 finishing_blow;
/*   33 */  uint8 combat_stability;
/*   34 */  uint8 combat_agility;
    } named;
  } archetype_skills;
  union {
    uint8 unnamed[93];
    struct _name {
/*   35 */  uint8 mass_group_buff; // All group-buff-casting classes(?)
// ===== Cleric =====
/*   36 */  uint8 divine_resurrection;
/*   37 */  uint8 innate_invis_to_undead; // cleric, necromancer
/*   38 */  uint8 celestial_regeneration;
/*   39 */  uint8 bestow_divine_aura;
/*   40 */  uint8 turn_undead;
/*   41 */  uint8 purify_soul;
// ===== Druid =====
/*   42 */  uint8 quick_evacuation; // wizard, druid
/*   43 */  uint8 exodus; // wizard, druid
/*   44 */  uint8 quick_damage; // wizard, druid
/*   45 */  uint8 enhanced_root; // druid
/*   46 */  uint8 dire_charm; // enchanter, druid, necromancer
// ===== Shaman =====
/*   47 */  uint8 cannibalization;
/*   48 */  uint8 quick_buff; // shaman, enchanter
/*   49 */  uint8 alchemy_mastery;
/*   50 */  uint8 rabid_bear;
// ===== Wizard =====
/*   51 */  uint8 mana_burn;
/*   52 */  uint8 improved_familiar;
/*   53 */  uint8 nexus_gate;
// ===== Enchanter  =====
/*   54 */  uint8 unknown54;
/*   55 */  uint8 permanent_illusion;
/*   56 */  uint8 jewel_craft_mastery;
/*   57 */  uint8 gather_mana;
// ===== Mage =====
/*   58 */  uint8 mend_companion; // mage, necromancer
/*   59 */  uint8 quick_summoning;
/*   60 */  uint8 frenzied_burnout;
/*   61 */  uint8 elemental_form_fire;
/*   62 */  uint8 elemental_form_water;
/*   63 */  uint8 elemental_form_earth;
/*   64 */  uint8 elemental_form_air;
/*   65 */  uint8 improved_reclaim_energy;
/*   66 */  uint8 turn_summoned;
/*   67 */  uint8 elemental_pact;
// ===== Necromancer =====
/*   68 */  uint8 life_burn;
/*   69 */  uint8 dead_mesmerization;
/*   70 */  uint8 fearstorm;
/*   71 */  uint8 flesh_to_bone;
/*   72 */  uint8 call_to_corpse;
// ===== Paladin =====
/*   73 */  uint8 divine_stun;
/*   74 */  uint8 improved_lay_of_hands;
/*   75 */  uint8 slay_undead;
/*   76 */  uint8 act_of_valor;
/*   77 */  uint8 holy_steed;
/*   78 */  uint8 fearless; // paladin, shadowknight

/*   79 */  uint8 two_hand_bash; // paladin, shadowknight
// ===== Ranger =====
/*   80 */  uint8 innate_camouflage; // ranger, druid
/*   81 */  uint8 ambidexterity; // all "dual-wield" users
/*   82 */  uint8 archery_mastery; // ranger
/*   83 */  uint8 unknown83;
/*   84 */  uint8 endless_quiver; // ranger
// ===== Shadow Knight =====
/*   85 */  uint8 unholy_steed;
/*   86 */  uint8 improved_harm_touch;
/*   87 */  uint8 leech_touch;
/*   88 */  uint8 unknown88;
/*   89 */  uint8 soul_abrasion;
// ===== Bard =====
/*   90 */  uint8 instrument_mastery;
/*   91 */  uint8 unknown91;
/*   92 */  uint8 unknown92;
/*   93 */  uint8 unknown93;
/*   94 */  uint8 jam_fest;
/*   95 */  uint8 unknown95;
/*   96 */  uint8 unknown96;
// ===== Monk =====
/*   97 */  uint8 critical_mend;
/*   98 */  uint8 purify_body;
/*   99 */  uint8 unknown99;
/*  100 */  uint8 rapid_feign;
/*  101 */  uint8 return_kick;
// ===== Rogue =====
/*  102 */  uint8 escape;
/*  103 */  uint8 poison_mastery;
/*  104 */  uint8 double_riposte; // all "riposte" users
/*  105 */  uint8 unknown105;
/*  106 */  uint8 unknown106;
/*  107 */  uint8 purge_poison; // rogue
// ===== Warrior =====
/*  108 */  uint8 flurry;
/*  109 */  uint8 rampage;
/*  110 */  uint8 area_taunt;
/*  111 */  uint8 warcry;
/*  112 */  uint8 bandage_wound;
// ===== (Other) =====
/*  113 */  uint8 spell_casting_reinforcement_mastery; // all "pure" casters
/*  114 */  uint8 unknown114;
/*  115 */  uint8 extended_notes; // bard
/*  116 */  uint8 dragon_punch; // monk
/*  117 */  uint8 strong_root; // wizard
/*  118 */  uint8 singing_mastery; // bard
/*  119 */  uint8 body_and_mind_rejuvenation; // paladin, ranger, bard
/*  120 */  uint8 physical_enhancement; // paladin, ranger, bard
/*  121 */  uint8 adv_trap_negotiation; // rogue, bard
/*  122 */  uint8 acrobatics; // all "safe-fall" users
/*  123 */  uint8 scribble_notes; // bard
/*  124 */  uint8 chaotic_stab; // rogue
/*  125 */  uint8 pet_discipline; // all pet classes except enchanter
/*  126 */  uint8 unknown126;
/*  127 */  uint8 unknown127;
    } named;
  } class_skills;
};
#endif


/*
** Drop Item On Ground
** Length: 226 Octets
** OpCode: MakeDropCode
*/

struct makeDropStruct
{
/*0000*/ uint8_t  opCode;                 // 0x2d
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint8_t  unknown0002[8];         // ***Placeholder
/*0010*/ uint32_t itemNr;                 // Item ID
/*0014*/ uint32_t dropId;                 // DropID
/*0018*/ uint8_t  unknown0146[192];       // ***Placeholder
/*0202*/ float    z;                      // Z Position
/*0206*/ float    x;                      // X Position
/*0210*/ float    y;                      // Y Position
/*0222*/ char     idFile[16];             // ACTOR ID
/*0238*/ uint8_t  unknown0174[4];         // ***Placeholder
/*0242*/ uint8_t  unknown0178[68];        // ***Placeholder
};

/*
** Remove Drop Item On Ground
** Length: 10 Octets
** OpCode: RemDropCode
*/

struct remDropStruct
{
/*0000*/ uint8_t  opCode;                 // 0x2c
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint16_t dropId;                 // DropID - Guess
/*0004*/ uint8_t  unknown0004[2];         // ***Placeholder
/*0006*/ uint16_t spawnId;                // Pickup ID - Guess
/*0008*/ uint8_t  unknown0008[2];         // ***Placeholder
};

/*
** Consider Struct
** Length: 30 Octets
** OpCode: considerCode
*/

struct considerStruct{
/*0000*/ uint8_t  opCode;                 // 0x0136
/*0001*/ uint8_t  version;                // 
/*0002*/ uint32_t playerid;               // PlayerID
/*0006*/ uint32_t targetid;               // TargetID
/*0010*/ int32_t  faction;                // Faction
/*0014*/ int32_t  level;                  // Level
/*0018*/ int32_t  curHp;                  // Current Hitpoints
/*0022*/ int32_t  maxHp;                  // Maximum Hitpoints
/*0026*/ int32_t  unknown0026;            // unknown
};

/*
** Spell Casted On
** Length: 38 Octets
** OpCode: castOnCode
*/

struct castOnStruct
{
/*0000*/ uint8_t  opCode;                 // 0x46
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint16_t targetId;               // Target ID
/*0004*/ uint8_t  unknown0004[2];         // ***Placeholder
/*0006*/ int16_t  sourceId;                // ***Source ID
/*0008*/ uint8_t  unknown0008[2];         // ***Placeholder
/*0010*/ uint8_t  unknown0010[24];        // might be some spell info?
/*0034*/ uint16_t spellId;                // Spell Id
/*0036*/ uint8_t  unknown0036[2];         // ***Placeholder
};

/*
** New Spawn
** Length: xxx Octets
** OpCode: NewSpawnCode
*/

struct newSpawnStruct
{
/*0000*/ uint8_t opCode;                 // 0x49
/*0001*/ uint8_t version;                // 0x21
/*0002*/ int32_t unknown0002;            // ***Placeholder
/*0006*/ struct spawnStruct spawn;       // Spawn Information
};

/*
** Spawn Death Blow
** Length: 18 Octets
** OpCode: NewCorpseCode
*/

struct newCorpseStruct
{
/*0000*/ uint8_t  opCode;                 // 0x42
/*0001*/ uint8_t  version;                // 0x00
/*0002*/ uint32_t spawnId;                // Id of spawn that died
/*0006*/ uint32_t killerId;               // Killer
/*0010*/ uint8_t  unknown0006[8];         // ***Placeholder
/*0018*/ uint32_t spellId;                // ID of Spell
/*0022*/ int8_t   type;                   // Spell, Bash, Hit, etc...
/*0023*/ uint32_t damage;                 // Damage
/*0027*/ uint8_t  unknown0016[7];         // ***Placeholder
}; //34

/*
** Money Loot
** Length: 22 Octets
** OpCode: MoneyOnCorpseCode
*/

struct moneyOnCorpseStruct
{
/*0000*/ uint8_t  opCode;                 // 0x50
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint8_t  unknown0002[4];         // ***Placeholder
/*0006*/ uint32_t platinum;               // Platinum Pieces
/*0010*/ uint32_t gold;                   // Gold Pieces
/*0014*/ uint32_t silver;                 // Silver Pieces
/*0018*/ uint32_t copper;                 // Copper Pieces
};

/*
** Item received by the player
** Length: x Octets
** OpCode: ItemOnCorpseCode and TradeItemInCode
*/

struct tradeItemInStruct
{
/*0000*/ uint8_t  opCode;                 // 0x52
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ struct itemItemStruct item;          // Refer to itemStruct for members
};

/*
** Container Item received by the player
** Length: x Octets
** OpCode: TradeContainerInCode
*/

struct tradeContainerInStruct
{
/*0000*/ uint8_t  opCode;                 // 0x52
/*0001*/ uint8_t  version;                // 0x20
union
{
  /*0002*/ struct itemStruct item;
  /*0002*/ struct itemContainerStruct container;          // Refer to itemStruct for members
};
};

/*
** Book Item received by the player
** Length: x Octets
** OpCode: TradeBookInCode
*/

struct tradeBookInStruct
{
/*0000*/ uint8_t  opCode;                 // 0x52
/*0001*/ uint8_t  version;                // 0x20
union
{
  /*0002*/ struct itemStruct item;
  /*0002*/ struct itemBookStruct book;          // Refer to itemStruct for members
};
};

struct itemOnCorpseStruct
{
/*0000*/ uint8_t  opCode;                 // 0x52
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ struct itemItemStruct item;          // Refer to itemStruct for members
};

/*
** Stamina
** Length: 14 Octets
** OpCode: staminaCode
*/

struct staminaStruct {
/*0000*/ uint8_t opCode;                   // 0x57
/*0001*/ uint8_t version;                  // 0x21
/*0002*/ int32_t food;                     // (low more hungry 127-0)
/*0006*/ int32_t water;                    // (low more thirsty 127-0)
/*0010*/ int32_t fatigue;                  // (high more fatigued 0-100)
};

/*
** Battle Code
** Length: 34 Octets
** OpCode: ActionCode
*/

struct action2Struct
{
/*0000*/ uint8_t  opCode;               // 0x4d
/*0001*/ uint8_t  version;              // 0x00
/*0002*/ uint16_t target;               // Target ID
/*0004*/ uint16_t source;               // Source ID
/*0006*/ uint8_t  type;                 // Bash, kick, cast, etc.
/*0007*/ int16_t  spell;                // SpellID
/*0009*/ int32_t  damage;
/*0013*/ uint8_t  unknown0010[11];
/*0024*/ uint8_t  unknown0014;      // ***Placeholder
}; // 25


struct actionStruct
{
/*0000*/ uint8_t  opCode;                 // 0x58
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint16_t target;                 // Target ID
/*0004*/ uint8_t  unknown0004[2];         // ***Placeholder
/*0006*/ uint16_t source;                 // SourceID
/*0008*/ uint8_t  unknown0008[2];         // ***Placeholder
/*0010*/ int8_t   type;                   // Casts, Falls, Bashes, etc...
/*0011*/ uint8_t  unknown0011;            // ***Placeholder
/*0012*/ int16_t  spell;                  // SpellID
/*0014*/ int32_t  damage;                 // Amount of Damage
/*0018*/ uint8_t  unknown0018[12];        // ***Placeholder
};

/*
** New Zone Code
** Length: 578 Octets
** OpCode: NewZoneCode
*/

struct newZoneStruct
{
/*0000*/ uint8_t opCode;                   // 0x5b
/*0001*/ uint8_t version;                  // 0x20
/*0002*/ char    name[64];                 // Character name
/*0066*/ char    shortName[32];            // Zone Short Name
/*0098*/ char    longName[180];            // Zone Long Name
/*0278*/ uint8_t unknown0278[300];         // *** Placeholder
};

/*
** Zone Spawns
** Length: 6Octets + Variable Length Spawn Data
** OpCode: ZoneSpawnsCode
*/

struct zoneSpawnsStruct
{
/*0000*/ uint8_t opCode;                     // 0x61
/*0001*/ uint8_t version;                    // 0x21
/*0002*/ struct spawnZoneStruct spawn[0];    // Variable number of spawns
};

/*
** client changes target struct
** Length: 4 Octets
** OpCode: clientTargetCode
*/

struct clientTargetStruct
{
/*0000*/ uint8_t  opCode;                 // 0x62
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint32_t newTarget;              // Target ID
/*0004*/ //uint16_t unknown0004;          // ***Placeholder - Removed Feb 13, 2002
};

/*
** Item belonging to a player
** Length: 246 Octets
** OpCode: PlayerItemCode
*/

struct playerItemStruct
{
/*0000*/ uint8_t  opCode;                 // 0x64
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint16_t unknown0002;
/*0004*/ struct itemItemStruct item;          // Refer to itemStruct for members
};

/*
** Book belonging to player
** Length: 205 Octets
** OpCode: PlayerBookCode
*/

struct playerBookStruct
{
/*0000*/ uint8_t  opCode;                 // 0x65
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint16_t unknown;
union
{
  /*0004*/ struct itemStruct item;
  /*0004*/ struct itemBookStruct book;          // Refer to itemStruct for members
};
};

/*
** Container Struct
** Length: 216 Octets
** OpCode: PlayerContainerCode
**
*/

struct playerContainerStruct
{
/*0000*/ uint8_t  opCode;                 // 0x66
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint16_t unknown0002;
union
{
  /*0004*/ struct itemStruct item;
  /*0004*/ struct itemContainerStruct container;          // Refer to itemStruct for members
};
};

/*
** Summoned Item - Player Made Item?
** Length: 244 Octets
** OpCode: summonedItemCode
*/

struct summonedItemStruct
{
/*0000*/ uint8_t  opCode;                 // 0x78
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ struct itemItemStruct item;          // Refer to itemStruct for members
};

/*
** Summoned Item - Player Made Item?
** Length: 244 Octets
** OpCode: summonedItemCode
*/

struct summonedContainerStruct
{
/*0000*/ uint8_t  opCode;                 // 0x78
/*0001*/ uint8_t  version;                // 0x21
union
{
  /*0002*/ struct itemStruct item;
  /*0002*/ struct itemContainerStruct container;          // Refer to itemStruct for members
};
};


/*
** Info sent when you start to cast a spell
** Length: 18 Octets
** OpCode: StartCastCode
*/

struct startCastStruct 
{
/*0000*/ uint8_t  opCode;                 // 0x7e
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ int32_t  unknown0002;            // ***Placeholder
/*0006*/ uint32_t spellId;                // Spell ID
/*0010*/ int32_t  unknown0010;            // ***Placeholder
/*0014*/ uint32_t targetId;               // The current selected target
/*0018*/ uint32_t unknown0018;            // ***Placeholder 
};

/*
** New Mana Amount
** Length: 10 Octets
** OpCode: manaDecrementCode
*/

struct manaDecrementStruct
{
/*0000*/ uint8_t opCode;                   // 0x7f
/*0001*/ uint8_t version;		   // 0x21
/*0002*/ int32_t newMana;                  // New Mana AMount
/*0004*/ int32_t spellID;                  // Last Spell Cast
};

/*
** Special Message
** Length: 6 Octets + Variable Text Length
** OpCode: SPMesgCode
*/
struct spMesgStruct
{
/*0000*/ uint8_t opCode;                  // 0x80
/*0001*/ uint8_t version;                 // 0x21
/*0002*/ int32_t msgType;                 // Type of message
/*0006*/ char    message[0];              // Message, followed by four Octets?
};

/*
** Spell Action Struct
** Length: 10 Octets
** OpCode: BeginCastCode
*/
struct beginCastStruct
{
/*0000*/ uint8_t  opCode;                 // 0x82
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint32_t spawnId;                // Id of who is casting
/*0004*/ uint32_t spellId;                // Id of spell
/*0006*/ int16_t  param1;                 // Paramater 1
/*0008*/ int16_t  param2;                 // Paramater 2
};

/*
** Spell Action Struct
** Length: 14 Octets
** OpCode: MemSpellCode
*/

struct memSpellStruct
{
/*0000*/ uint8_t  opCode;                 // 0x82
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint32_t spawnId;                // Id of who is casting
/*0006*/ uint32_t spellId;                // Id of spell
/*0010*/ int16_t  param1;                 // Paramater 1
/*0012*/ int16_t  param2;                 // Paramater 2
};

/*
** Skill Increment
** Length: 10 Octets
** OpCode: SkillIncCode
*/

struct skillIncStruct
{
/*0000*/ uint8_t  opCode;                 // 0x89
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint16_t skillId;                // Id of skill
/*0004*/ uint8_t  unknown0004[2];         // ***Placeholder
/*0006*/ int16_t  value;                  // New value of skill
/*0008*/ uint8_t  unknown0008[2];         // ***Placeholder
};

/*
** When somebody changes what they're wearing
**      or give a pet a weapon (model changes)
** Length: 18 Octets
** Opcode: WearChangeCode
*/

struct wearChangeStruct
{
/*0000*/ uint8_t  opCode;                 // 0x92
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint32_t spawnId;                // SpawnID
/*0004*/ uint8_t  wearSlotId;             // Slot ID
/*0005*/ uint8_t  unknown0005[3];            // unknown
/*0006*/ uint16_t newItemId;              // Item ID see weaponsX.h or util.cpp
/*0008*/ uint8_t  unknown0008[2];         // unknown
/*0010*/ uint32_t color;                  // color
};

/*
** Level Update
** Length: 14 Octets
** OpCode: LevelUpUpdateCode
*/

struct levelUpUpdateStruct
{
/*0000*/ uint8_t  opCode;                 // 0x98
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint32_t level;                  // New level
/*0006*/ uint32_t levelOld;               // Old level
/*0010*/ uint32_t exp;                    // Current Experience
};

/*
** Experience Update
** Length: 6 Octets
** OpCode: ExpUpdateCode
*/

struct expUpdateStruct
{
/*0000*/ uint8_t  opCode;                 // 0x99
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint16_t exp;                    // experience value  x/330
/*0004*/ uint16_t unknown0004;            // ***Place Holder
};

/*
** Alternate Experience Update
** Length: 14 Octets
** OpCode: AltExpUpdateCode
*/
struct altExpUpdateStruct
{
/*0000*/ uint8_t  opCode;                 // 0x23
/*0001*/ uint8_t  version;                // 0x22
/*0002*/ uint32_t altexp;                 // alt exp x/330
/*0006*/ uint32_t aapoints;               // current number of AA points
/*0010*/ uint8_t  percent;                // percentage in integer form
/*0011*/ uint8_t  unknown0009[3];            // ***Place Holder
};

/*
** Type:   Zone Change Request (before hand)
** Length: 70 Octets
** OpCode: ZoneChangeCode
*/

struct zoneChangeStruct
{
/*0000*/ uint8_t  opCode;               // 0xa3
/*0001*/ uint8_t  version;              // 0x20
/*0002*/ char     name[64];		// Character Name
/*0066*/ uint32_t zoneId;               // zone Id
/*0070*/ uint8_t unknown[8];              // unknown
};

/*
** Player HP Update
** Length: 8 Octets
** OpCode: HPUpdateCode
*/

struct hpUpdateStruct
{
/*0000*/ uint8_t  opCode;                 // 0xb6
/*0001*/ uint8_t  version;                // 0x00
/*0002*/ int16_t  maxHp;                  // Maximum hp of spawn
/*0004*/ int16_t  curHp;                  // Current hp of spawn
/*0006*/ uint16_t spawnId;                // Id of spawn to update
};

/*
** NPC Hp Update
** Length: 5 Octets
** Opcode NpcHpUpdateCode
*/

struct hpNpcUpdateStruct
{
/*0000*/ uint16_t opcode;
/*0002*/ uint16_t spawnId;
/*0004*/ int8_t   curHp;
};

/*
** Inspecting Information
** Length: 1746 Octets
** OpCode: InspectDataCode
*/

struct inspectDataStruct
{
/*0000*/ uint8_t  opCode;                 // 0xb6
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint8_t  unknown0002[68];        // ***Placeholder
/*0070*/ char     itemNames[21][64];      // 21 items with names 
                                          //    64 characters long.
/*1414*/ uint8_t  unknown1344[2];         // ***placeholder
/*1416*/ int16_t  icons[21];              // Icon Information
/*1458*/ char     mytext[200];            // Player Defined Text Info
/*1658*/ uint8_t  unknown0958[88];        // ***Placeholder
};

/*
** Reading Book Information
** Length: Variable Length Octets
** OpCode: BookTextCode
*/

struct bookTextStruct
{
/*0000*/ uint8_t opCode;                   // 0xce
/*0001*/ uint8_t version;                  // 0x20
/*0002*/ char    text[0];                  // Text of item reading
};

/*
** Interrupt Casting
** Length: 6 Octets + Variable Length Octets
** Opcode: BadCastCode
*/

struct badCastStruct
{
/*0000*/ uint8_t  opCode;                   // 0xd3
/*0001*/ uint8_t  version;                  // 0x21
/*0002*/ uint32_t spawnId;                  // Id of who is casting
/*0006*/ char     message[0];               // Text Message
};

/*
** Info sent when trading an item
** Length: 258 Octets
** OpCode: tradeItemOutCode
*/

struct tradeItemOutStruct
{
/*0000*/ uint8_t  opCode;                 // 0xdf
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint8_t  unknown0002[4];         // ***Placeholder
/*0008*/ int8_t   itemType;               // Type of item
union
{
  /*0008*/ struct itemItemStruct item;        // Refer to itemStruct for members
  /*0009*/ struct itemContainerStruct container;
  /*0009*/ struct itemBookStruct book;
};
/*0253*/ uint8_t  unknown0253[5];         // ***Placeholder
};

/*
** Random Number Request
** Length: 10 Octets
** OpCode: RandomCode
*/
struct randomStruct 
{
/*0000*/ uint8_t  opCode;                 // 0xe7
/*0001*/ uint8_t  version;                // 0x21
/*0002*/ uint32_t bottom;                 // Low number
/*0006*/ uint32_t top;                    // High number
};

/*
** Time of Day
** Length: 8 Octets
** OpCode: TimeOfDayCode
*/

struct timeOfDayStruct
{
/*0000*/ uint8_t  opCode;                 // 0xf2
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint8_t  hour;                   // Hour (1-24)
/*0003*/ uint8_t  minute;                 // Minute (0-59)
/*0004*/ uint8_t  day;                    // Day (1-28)
/*0005*/ uint8_t  month;                  // Month (1-12)
/*0006*/ uint16_t year;                   // Year
/*0008*/ uint16_t unknown0016;            // Placeholder
};

/*
** Player Position Update
** Length: 19 Octets
** OpCode: PlayerPosCode
*/

struct playerPosStruct
{
/*0000*/ uint8_t  opCode;                 // 0xf3
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint16_t spawnId;                // Id of player
/*0004*/ signed   deltaY:10;              // Y Velocity
         unsigned spacer1:1;              // ***Placeholder
         signed   deltaZ:10;              // Z Velocity
         unsigned spacer2:1;              // ***Placeholder
         signed   deltaX:10;              // X Velocity
/*0008*/ int16_t  y;                   // Players Y Position
/*0010*/ int16_t  x;                   // Players X Position
/*0012*/ int16_t  z;                   // Players Z Position
int8_t animation;
/*0014*/ int8_t   deltaHeading;                // Current heading of player
/*0015*/ int8_t   heading;           // Heading Change
};

/*
** Spawn Appearance
** Length: 10 Octets
** OpCode: spawnAppearanceCode
*/

struct spawnAppearanceStruct
{
/*0000*/ uint8_t  opCode;                 // 0xf5
/*0001*/ uint8_t  version;                // 0x20
/*0002*/ uint16_t spawnId;                // ID of the spawn
/*0004*/ int16_t  type;                   // Type of data sent
/*0006*/ uint32_t paramter;               // Values associated with the type
};

/*
** Compressed Player Items Struct
** Length: Variable Octets
** Opcodes: CPlayerItemCode
*/

struct cPlayerItemsStruct
{
/*0000*/ uint8_t  opCode;                 // 0xf6
/*0001*/ uint8_t  version;                // 0x41
/*0002*/ uint32_t count;                  // Number of packets contained
/*0006*/ uint8_t  compressedData[0];      // All the packets compressed together
};

/*
** Compressed Door Struct
** Length: 4 + (count * sizeof(doorStruct)) Octets
** OpCode: CompressedDoorSpawnCode
*/

struct cDoorSpawnsStruct
{
/*0000*/ uint8_t  opCode;                // 0xf7
/*0001*/ uint8_t  version;               // 0x41
/*0002*/ uint32_t count;                 // number of doors
/*0006*/ struct doorStruct doors[0];     // door structures
};
typedef struct cDoorSpawnsStruct doorSpawnsStruct; // alias

/*
**               Structures that are not being currently used
 *               (except for logging)
*/

struct bindWoundStruct
{
/*0000*/ uint8_t  opCode;               // ????
/*0001*/ uint8_t  version;		// ????
/*0002*/ uint16_t playerid;             // TargetID
/*0004*/ uint8_t  unknown0004[2];       // ***Placeholder
/*0006*/ uint32_t hpmaybe;              // Hitpoints -- Guess
};

struct inspectedStruct
{
/*0000*/ uint8_t  opCode;              // ????
/*0001*/ uint8_t  version;             // ????
/*0002*/ uint16_t inspectorid;         // Source ID
/*0004*/ uint8_t  unknown0004[2];      // ***Placeholder
/*0006*/ uint16_t inspectedid;         // Target ID - Should be you
/*0008*/ uint8_t  unknown0008[2];      // ***Placeholder
};

struct attack1Struct
{
/*0000*/ uint8_t  opCode;                 // ????
/*0001*/ uint8_t  version;                // ????
/*0002*/ uint16_t spawnId;                // Spawn ID
/*0004*/ int16_t  param1;                 // ***Placeholder
/*0004*/ int16_t  param2;                 // ***Placeholder
/*0004*/ int16_t  param3;                 // ***Placeholder
/*0004*/ int16_t  param4;                 // ***Placeholder
/*0004*/ int16_t  param5;                 // ***Placeholder
};

struct attack2Struct{
/*0000*/ uint8_t  opCode;                 // ????
/*0001*/ uint8_t  version;                // ????
/*0002*/ uint16_t spawnId;                // Spawn ID
/*0004*/ int16_t  param1;                 // ***Placeholder
/*0004*/ int16_t  param2;                 // ***Placeholder
/*0004*/ int16_t  param3;                 // ***Placeholder
/*0004*/ int16_t  param4;                 // ***Placeholder
/*0004*/ int16_t  param5;                 // ***Placeholder
};

struct newGuildInZoneStruct
{
/*0000*/ uint8_t  opCode;                 // ????
/*0001*/ uint8_t  version;                // ????
/*0002*/ uint8_t  unknown0002[8];         // ***Placeholder
/*0010*/ char     guildname[56];          // Guildname
};

struct moneyUpdateStruct{
/*0000*/ uint8_t  opCode;                 // ????
/*0001*/ uint8_t  version;                // ????
/*0002*/ uint16_t unknown0002;            // ***Placeholder
/*0006*/ uint8_t  cointype;               // Coin Type
/*0007*/ uint8_t  unknown0007[3];         // ***Placeholder
/*0010*/ uint32_t amount;                 // Amount
};
typedef struct moneyUpdateStruct moneyThingStruct; 

/* Memorize slot operations, mem, forget, etc */

struct memorizeSlotStruct
{
/*0000*/ uint8_t  opCode;                   // ????
/*0001*/ uint8_t  version;                  // ????
/*0002*/ int8_t   slot;                     // Memorization slot (0-7)
/*0003*/ uint8_t  unknown0003[3];           // ***Placeholder
/*0006*/ uint16_t spellId;                  // Id of spell 
                                            // (offset of spell in spdat.eff)
/*0008*/ uint8_t  unknown0008[6];           // ***Placeholder 00,00,01,00,00,00
};

struct cRunToggleStruct
{
/*0000*/ uint8_t  opCode;
/*0001*/ uint8_t  version;
/*0002*/ uint32_t status;                   //01=run  00=walk
};

struct cChatFiltersStruct
{
/*0000*/ uint8_t  opCode;
/*0001*/ uint8_t  version;
/*0002*/ uint32_t DamageShields;   //00=on  01=off
/*0006*/ uint32_t NPCSpells;       //00=on  01=off
/*0010*/ uint32_t PCSpells;        //00=all 01=off 02=grp
/*0014*/ uint32_t BardSongs;       //00=all 01=me  02=grp 03=off
/*0018*/ uint32_t Unused;
/*0022*/ uint32_t GuildChat;       //00=off 01=on
/*0026*/ uint32_t Socials;         //00=off 01=on
/*0030*/ uint32_t GroupChat;       //00=off 01=on
/*0034*/ uint32_t Shouts;          //00=off 01=on
/*0038*/ uint32_t Auctions;        //00=off 01=on
/*0042*/ uint32_t OOC;             //00=off 01=on
/*0046*/ uint32_t MyMisses;        //00=off 01=on
/*0050*/ uint32_t OthersMisses;    //00=off 01=on
/*0054*/ uint32_t OthersHits;      //00=off 01=on
/*0058*/ uint32_t AttackerMisses;  //00=off 01=on
/*0062*/ uint32_t CriticalSpells;  //00=all 01=me  02=off
/*0066*/ uint32_t CriticalMelee;   //00=all 01=me  02=off
};

struct cOpenSpellBookStruct
{
/*0000*/ uint8_t  opCode;
/*0001*/ uint8_t  version;
/*0002*/ int32_t status; //01=open 00=close
};

struct xTradeSpellBookSlotsStruct
{
/*0000*/ uint8_t  opCode;
/*0001*/ uint8_t  version;
/*0002*/ uint32_t slot1;
/*0006*/ uint32_t slot2;
};


/*
** serverLFGStruct
** Length: 10 Octets
** signifies LFG, maybe afk, role, ld, etc
*/

struct serverLFGStruct
{
/*0000*/ uint8_t  opCode;
/*0001*/ uint8_t  version;
/*0002*/ uint16_t spawnID;
/*0004*/ uint16_t unknown0004;
/*0006*/ uint16_t LFG;             //1=LFG
/*0008*/ uint16_t unknown0008;
};

/*
** clientLFGStruct
** Length: 70 Octets
** signifies LFG, maybe afk, role, ld, etc
*/

struct clientLFGStruct
{
/*0000*/ uint8_t  opCode;
/*0001*/ uint8_t  version;
/*0002*/ uint8_t  name[64];
/*0006*/ uint16_t LFG;             //1=LFG
/*0008*/ uint16_t unknown0008;
};

/*
** xBuffDropStruct
** Length: 10 Octets
** signifies LFG, maybe afk, role, ld, etc
*/

struct xBuffDropStruct
{
/*0000*/ uint8_t  opCode;
/*0001*/ uint8_t  version;
/*0002*/ uint16_t spawnid;
/*0004*/ uint8_t  unknown0004[4]; 
/*0008*/ uint16_t spellid;
/*0010*/ uint8_t  unknown0010[8];
/*0018*/ uint16_t spellslot;
/*0020*/ uint8_t  unknown0020[2];
};



/*******************************/
/* World Server Structs        */

/*
** Guild List (from world server)
** Length: 96 Octets
** used in: worldGuildList
*/

struct guildListStruct
{
/*0000*/ uint16_t guildID;
/*0002*/ uint16_t unknown0006;
/*0004*/ char     guildName[60];
/*0064*/ uint8_t  unknown0064[8]; 
/*0072*/ uint32_t valid;
/*0076*/ uint8_t  unknown0076[20];
};

/*
** Guild List (from world server)
** Length: 49158 Octets
** OpCode: GuildListCode 0x9221
*/
#define MAXGUILDS 512
struct worldGuildListStruct
{
/*0000*/ uint32_t header;  // probably a checksum
/*0004*/ guildListStruct guilds[MAXGUILDS];
};

struct rawWorldGuildListStruct
{
/*0000*/ uint8_t opCode;
/*0001*/ uint8_t version;
/*0002*/ worldGuildListStruct guildlist;
};

struct keyStruct
{
/*0002*/ uint64_t key;
};

// Restore structure packing to default
#pragma pack()

#endif // EQSTRUCT_H

//. .7...6....,X....D4.M.\.....P.v..>..W....
//123456789012345678901234567890123456789012
//000000000111111111122222222223333333333444
