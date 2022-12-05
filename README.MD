Dungeon
-------------------
Name and UID:
Lee Sin Wing 3035928196
Kwok Chak Lai 3035994808

-----------------------------------------------------------------------------------------------------


Make a trpg game (use words and commands to fight,all scenes will be output to the terminal.

-------------------------------------------------------------------------------------------------------

Gamerule:
Defeat endless amount of random generated dungeons, if the character die, the user have to start another new dungeon and try again.

--------------------------------------------------------------------------------------------------------

Description:

-On the title screen, click n to start a new character or c to continue with old character, press q to leave quit the game

-For new character, type in yoor name and choose the class, there are classes like knight, ranger, wizard

-Different character has different attributes and default gear, attributes are agility, presence, toughness and strength

-Attributes affect the chance of success doing some actions like attack and some stats like health

-The character can fight the mobs and use items like health potions

-The damage and actions depends on the dice (ie. 1d3 1d4) 1d3 means there is a dice with 3 faces, each faces rolls for damage from 1-3

-During the fight, the game will get the total damage(calculated with base health, weapon's damage, skills) with the mob's total health (calculated with base health
attributes ...)


------------------------------------------------------------------------------------------------------------

Implemented features:

Generation of random game sets or events

-this is done by generating mobs with random gears and attributes.

Data structures for storing game status

-saveload.cpp and saveload.h are used to store user's items, status and the game status

Dynamic memory management

-the saveload files can store infinite amount of user data, when the user adds his characters into the game, the variables for the user's character is added to the file

File input/output (e.g., for loading/saving game status)

-the program read the saveload.cpp and saveload.h for loading the game and write the saveload.cpp for saving the game.

Program codes in multiple files

-it has event.h and event.cpp for game event, mob.h and mob.cpp for mob generations, io.cpp and io.h for receiving input and output from the user, etc

Other implemented features:

-used ncurses, ncurses is a programming library providing an application programming interface (API) that allows the programmer to write text-based user interfaces (TUI) in a terminal-independent manner. It is used to make all TUI in our game.

-used xml files, xml files are extensible Markup Language (XML) is a markup language and file format for storing, transmitting, and reconstructing arbitrary data.
They are used for generating tons of mobs, equipments, spell... with similar format in our project.
