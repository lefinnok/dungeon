Dungeon
-------------------

Name and UID:

Lee Sin Wing 3035928196

Kwok Chak Lai 3035994808

-----------------------------------------------------------------------------------------------------


Make a trpg game (use words and commands to fight,all scenes will be output to the terminal.

-------------------------------------------------------------------------------------------------------

Gamerule:
Create character, dungeon will randomly generate mobs, killmob, drop stuff, repeat until character death

--------------------------------------------------------------------------------------------------------

Description:

-Type ./comp.sh to compile the game

-Type ./test.sh to start the game

-On the title screen, click n to start a new character or c to continue with old character, press q to leave quit the game

-For new character, type in yoor name and choose the class, there are classes like knight, ranger, wizard

-Different character has different attributes and default gear, attributes are agility, presence, toughness and strength

-Attributes affect the chance of success doing some actions like attack and some stats like health

-The character can fight the mobs and use items like health potions

-The damage and actions depends on the dice (ie. 1d3 1d4) 1d3 means there is a dice with 3 faces, each faces rolls for damage from 1-3

-During the fight, the game will get the total damage(calculated with base health, weapon's damage, skills) with the mob's total health (calculated with base health
attributes ...)

Background of the project:

Problem met: groupmates leaving, not familiar with ncurses, first time to try object orientation programming, first time to write all header files and files


------------------------------------------------------------------------------------------------------------

Implemented features:

Generation of random game sets or events

-this is done by random generation of mobs, damage and rewards.

Data structures for storing game status

-saveload.cpp and saveload.h are used to store user's items, status and the game status

-used xml files to store all basic information of mobs and classes

Dynamic memory management

-the saveload files can store infinite amount of user data, when the user adds his characters into the game, the variables for the user's character is added to the file

File input/output (e.g., for loading/saving game status)

-the game reads the saveload.cpp and saveload.h for loading the game and write the saveload.cpp for saving the game.

-the game reads the xml files to get the information of mobs,equipments and consumables 

Program codes in multiple files

-it has event.h and event.cpp for game event, mob.h and mob.cpp for mob generations, xml files for the basic information of mobs , io.cpp and io.h for receiving input and output from the user, etc

-------------------------------------------------------------------------------------------------------------------

Other implemented features:

-used ncurses, ncurses is a programming library providing an application programming interface (API) that allows the programmer to write text-based user interfaces (TUI) in a terminal-independent manner. It is used to make all TUI in our game.

-used xml files, xml files are extensible Markup Language (XML) is a markup language and file format for storing, transmitting, and reconstructing arbitrary data.
They are used for generating tons of mobs, equipments, spell... with similar format in our project.

-------------------------------------------------------------------------------------------------------------------------

Compilation and execution instructions:

all letters in [] (ie. [Q]uit  [N]ew character) means click q to quit and n to make new character

type ./comp.sh to compile then type ./test.sh to run the program

Type n to start a new character, type in your name, click c to choose class(better if you choose knight as it is the most balanced and easiest class)

Click i to open your inventory and use upward and downward arrow to choose equipment, click enter to use the equipment

Click u to use item, choose sword and click enter to use, choose the mob to attack mob

Journal will show the game event

Click i again and choose health potion if you want to heal yourself

Click esc to pause, then click q to quit
