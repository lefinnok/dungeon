Name and UID:
Lee Sin Wing 3035928196
Kwok Chak Lai 3035994808

(Written by Lee Sin Wing):

Make a trpg game (use words and commands to fight,all scenes will be output to the terminal.

Gamerule:
Defeat endless amount of random generated dungeons, if the character die, the user have to start another new dungeon and try again.

Description:
-user run the game by typing ./io
-the game prints out the title screen and click n to start a new character or c to continue with old character.
-the game asks the user to type in the username e.g "Sorry I forget what is your name, can you say it again?" and user inputs the username and presses enter
-the game opens the saveload file and check if the username is there, 
 If yes then print out "Hi xxxx, here is your stuff" and print out his stat as well as last time's progress
 If no, print out "sorry I can't find your name on my list, would you like to introduce yourself?" and print out "can I have your name?".
 The user inputs the preferred username and the input will be added to the saveload file. It will also add the basic stat to the user's save 
-The game prints out the user's stat and some possible commands(e.g startdungeon, showstat)

-If the user typed startdungeon, it will start a new dungeon for user to challenge
-All mobs information will be stored in the mob file

The main program will call other functions for skills, mob atks, mob generation and prints out the scenes like:

-When the user use atk, the mob will decrease its hp the damage of the weapon's atk, if the number of remaining hp<=0, print out "you have defeated xxx"
 if the number of remaining hp >0, print out the scene like the scene above with updated mob health
-When the user use def, in next round mob's atk will decrease by the def
-When the user use use item, print out the scene of user's avaliable items "you have xx,xx,xx"
 If user input the item name, the item will be used
 If user input "back", it will back to the scene above
-When the user has done 1 action, the mob will attack the user and decrease the hp of mobs by

-If the user defeat one mob, it will get random drops from that mob, the drops will be added to the user's stat
-If the user is defeated by the mob, print out "you have been defeated by xxx, please try harder next time" and jump back to the scene before startdungeon command

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

