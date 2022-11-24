Name and UID:
Lee Sin Wing 3035928196
Kwok Chak Lai 3035994808

(Written by Lee Sin Wing):

Make a trpg game (use words and commands to fight,all scenes will be output to the terminal.

Gamerule:
Defeat endless amount of random generated dungeons, if the character die, the user have to start another new dungeon and try again.

Description:
-user run the game by typing ./main
-the game prints out some welcome words(e.g Hello adventurers....)
-the game asks the user to type in the username e.g "Sorry I forget what is your name, can you say it again?" and user inputs the username and presses enter
-the game opens the saveload file and check if the username is there, 
 If yes then print out "Hi xxxx, here is your stuff" and print out his stat as well as last time's progress
 If no, print out "sorry I can't find your name on my list, would you like to introduce yourself?" and print out "can I have your name?".
 The user inputs the preferred username and the input will be added to the saveload file. It will also add the basic stat to the user's save 
-The game prints out the user's stat and some possible commands(e.g startdungeon, showstat)

-If the user typed startdungeon, it will start a new dungeon for user to challenge
-All mobs information will be stored in the mob file

The main program will call other functions for skills, mob atks, mob generation and prints out the scenes like:

-------------------------------

        ------------
        |   24/24  |
        |   slime  |
        ------------
        
--------------------------------
atk   def    use item
hp:100

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
