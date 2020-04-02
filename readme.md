Last modified : Chong Zhen Yuen, 2/4/2020



# Space Invaders 2.0

A  modified  version of the popular arcade game, Space Invaders, with added
twists and features.

 

## Contributers

1)	Name	: Chong Zhen Yuen 
	UID	: 3035662728
	Study	: Year 1 Engineering 


2) 	Name	: Loh Jian Wei
	UID	:
	Study	: Year 1 Engineering



## Game Description

Space  Invaders  2.0  is a single player game, whereby the player will take
control  of  a spaceship and shoot down invading enemy ships using a myriad
of  weapons.  The spaceship moves horizontally at the bottom of the screen,
and  must stop the invading enemy ships from reaching the bottom row. Enemy
ships are able to fire projectiles at random, and the player must avoid all
projectiles.  The  player  is only given 3 lives to clear as many stages as
he/she can.  

As  the  player  progresses through the game, each stage gets progressively  
harder  by  the increasing number of enemy ships. More advance weaponry and  
loot  boxes  can  be  obtainable  by  the  player  in the later stages. The 
player's  performance  will be evaluated based on the time spent and number 
of  stages  cleared.  The  in-game  leaderboard will display the top 5 high 
scores.



## Features and Code Structure

1) 	Randomly generated events
	- There  are different types of enemy ships, and their positions on
	  the  screen will be randomly generated for every stage to provide
	  a   unique   gameplay  experience.  Each  enemy  ship  will  fire
	  projectiles at random intervals.


2)	Data structures
	- As  the player progresses through the game, his/her progress such
	  as  time  spent  and number of stages cleared will be stored in a
	  custom data structure. Classes would be used to store the details
	  of  the  player's  spaceship  and  the enemy ships, such as their
	  weapons.


3) 	Dynamic memory management
	- Instead  of  using  statically  defined arrays with a fixed size,
	  dynamic  arrays  are used to store all enemy ships in every stage
	  to  reduce  memory  usage. As the player shoots down enemy ships,
	  the  number  of  enemy  ships  decreases, so does the size of the
	  array.


4)	File input/output
	- The  player  is  allowed  to save his/her current progress before
	  every stage, so he/she can resume the game from the current stage
	  in  the  future.  All  information  including  the  top  5 scores
	  displayed in the leaderboard will be stored in a text file.


5)	Seperate files
	- All  functions will be defined separately from the main function.
	  Classes  and  custom  data  structures  will also be separated in
	  another  file.  This  is to promote encapsulation and prevent any
	  unintended  modification  or errors which may occur when updating
	  the game.




