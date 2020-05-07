
# Space Invaders 2.0

A  modified  version of the popular arcade game, Space Invaders, with added
twists and features.

Space Invaders (Japanese: スペースインベーダー, Hepburn: Supēsu Inbēdā)
is a 1978 arcade game created by Tomohiro Nishikado (Wikipedia, 2020).
<br/>
<br/>

## Contributers

<pre>
1)	Name	: Chong Zhen Yuen
&nbsp 	UID	: 3035662728
&nbsp 	Study	: Year 1 Engineering
<br/>
2)	Name	: Loh Jian Wei
&nbsp 	UID	: 3035718278
&nbsp 	Study	: Year 1 Engineering
</pre>

<br/>
<br/>

## Game Description

Space  Invaders  2.0  is a single player game, whereby the player will take
control  of  a spaceship and shoot down invading enemy ships using a myriad
of  weapons.  The spaceship moves horizontally at the bottom of the screen,
and  must stop the invading enemy ships from reaching the bottom row. Enemy
ships are able to fire projectiles at random, and the player must avoid all
projectiles.
<br/>
<br/>
As  the  player  progresses through the game, each stage gets progressively
harder  by  the  increasing  number  of enemy ships and types. 
The player's performance  will be  evaluated  based on the  time  spent in 
clearing the 10  stages  in  "Story Mode". The  in-game  leaderboard  will
display the top 5 high scores.
<br/>
<br/>

## Installation Process

Clone the repository into an empty directory. In order to run the game,
execute the bash script *si_2.sh* using the command:

<pre>
chmod u=rwx si_2.sh
./si_2.sh
</pre>

Once the installation process is complete, the game will automatically open in a new terminal.

*NOTE : Since the game opens in a new terminal, running the game on the academy server remotely through applications such as PuTTy is not allowed as the connection would refuse to open a new terminal window. Hence, connecting to the academy server using the x2Go client is necessary.*
<br/>
<br/>

## In-game Key Features

### Bonus round

When the user completes the first 10 stages, he/she will unlock the bonus game mode whereby the user can clear unlimited stages. All the gun and enemy types will be available in "Bonus Mode". 
<br/>

### Different Weapons

As the player progress through the game, more weapons can be unlocked (up to 3 types).
Below are the list of weapons in-game.
<br/>

<pre>
1)	Gattling Gun
&nbsp	- shoots a bullet at a time.
<br/>
2)	Shot gun
&nbsp	- shoots a wide bullet with multiple hitboxes.
<br/>
3)	Laser Gun
&nbsp	- Fires a laser which destroys all enemies in a single line.
<br/>
4)	Shield
&nbsp	- Generates a temporary shield to block all incoming fire.
</pre>

<br/>

### Different Enemies

As the player progress through the game, new enemies types will be introduced (up to 3 types).
Below are the list of enemies in-game.
<br/>

<pre>
1)	Craft X
&nbsp	- Low HP, High fire rate.
<br/>
2) 	The Wall
&nbsp	- High HP, low fire rate.
<br/>
3)	Mirage
&nbsp	- Fires a mirror that can reflect the laser.
</pre>

### Code Elements

This section covers only a few examples of the codes elements in the game. Feel free to check out the all the codes under the *code* directory if you are interested! From asynschronous functions to switching the terminal from cooked mode to raw mode, we have it all :D!

<pre>
1) 	Randomly generated events
	- There  are different types of enemy ships, and their positions on
	  the  screen will be randomly generated for every stage to provide
	  a   unique   gameplay  experience.  Each  enemy  ship  will  fire
	  projectiles at random intervals.
</pre>

<pre>	 
2)	Data structures
	- Structs will be used to store user details such as their name and
	  number of stages cleared. The bullets are stored in linked lists.
	  Classes  would  be  used  to  store  the  details of the player's
	  spaceship and the enemy ships, such as their weapons.
</pre>

<pre>
3) 	Dynamic memory management
	- Instead  of  using  statically  defined arrays with a fixed size,
	  dynamic  arrays  are used to store all enemy ships in every stage
	  to reduce memory usage. As the player proceeds to the next stage,
	  the  number  of  enemy  ships  changes, so  does  the size of the
	  array.  Linked  list  are  used  to  store the information of the
	  bullets fired, such as their locations.
</pre>

<pre>
4)	File input/output
	- A checkpoint  is  placed after completing every stage to save the
	  current  progress  of  the  user  into a text file in the *saves*
	  directory.   Whenever  the  user  reopens  the game,  he/she  can  
	  continue  from  the  current  stage.  All  information  including   
	  the  in-game illustrations are stored as text files  and imported
	  when the game program starts. 
</pre>

<pre>
5)	Separate files
	- All  functions will be defined separately from the main function.
	  Multiple  directories for every individual class has been created
	  under the *codes* directory. This is to promote encapsulation and
	  prevent  any  unintended  modification  or errors which may occur
	  when developing the game.
</pre>

<br/>

#### Refer to instruction.md for more details

<br/>

### References
<pre>
1) Mrigendra Singh, "C++ Program to print current Day, Date and Time"
   Link: https://www.geeksforgeeks.org/c-program-print-current-day-date-time/
2) Patorjk.com, "Text to ASCII Art Generator (TAAG)"
   Link: http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
3) Tomohiro Nishikado, "Space Invader" 
   Link: https://en.wikipedia.org/wiki/Space_Invaders
</pre>

<br/>

*Last modified: Zhen Yuen*
<br/>

*Date: May 7, 2020*
<br/>

*Time: 2100 HKT*
<br/>
