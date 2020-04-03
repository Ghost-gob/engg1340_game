
# Space Invaders 2.0

A  modified  version of the popular arcade game, Space Invaders, with added
twists and features.


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

## Game Description

Space  Invaders  2.0  is a single player game, whereby the player will take
control  of  a spaceship and shoot down invading enemy ships using a myriad
of  weapons.  The spaceship moves horizontally at the bottom of the screen,
and  must stop the invading enemy ships from reaching the bottom row. Enemy
ships are able to fire projectiles at random, and the player must avoid all
projectiles.  The  player  is only given 3 lives to clear as many stages as
he/she can. 
<br/> 
<br/>
As  the  player  progresses through the game, each stage gets progressively
harder  by  the increasing number of enemy ships. More advance weaponry and
loot  boxes  can  be  obtainable  by  the  player  in the later stages. The 
player's  performance  will be evaluated based on the time spent and number 
of  stages  cleared.  The  in-game  leaderboard will display the top 5 high 
scores.
<br/>
<br/>
When the player progresses from one stage to the next stage, the player has
to nagivate the  spaceship  through a group of asteriods by dodging them to
prevent crashing.


<br/>

## In-game Features

### Spaceships
There will be three types of spaceship to choose from, each with a different
special ability.  There will be a  charging bar to track the charging status
for the special ability.  When the bar is fully charged, the special ability
can be executed. 

<br/>
<pre>
1)	Galaxy Reaper
&nbsp	Special Ability: Double Damage until end of stage.
<br/>
2)	Galaxy Tanker
&nbsp	Special Ability: Summons a sheild barrier that absorbs a projectile.
<br/>
3)	Galaxy Pirates
&nbsp	Special Ability: Doubles the coins earned from each enemy killed.
<pre>
<br/>

### Weaponry

Players can upgrade to more powerful weapons by buying them with coins or from
loot boxes. Below are the list of weapons in-game.
<br/>
```
1)	Single Barrel Machine Gun
	- shoots a bullet at a time. 
<br/>
2)	Rapid Machine Gun
	- upgraded version of Single Barrel Machine Gun. Higher fire rate.
<br/>
3)	Double Barrel Machine Gun
	- shoots two bullets at a time.
<br/>
4)	Plasma Gun
	- shoots an energy pulse that can cause splash damage.
<br/>
5)	Laser Gun
	-continuous emission of laser beam that can damages the enemies.
```

## Features and Code Structure

<pre>
1) 	Randomly generated events
	- There  are different types of enemy ships, and their positions on
	  the  screen will be randomly generated for every stage to provide
	  a   unique   gameplay  experience.  Each  enemy  ship  will  fire
	  projectiles at random intervals.
</pre>

<pre>
2)	Data structures
	- As  the player progresses through the game, his/her progress such
	  as  time  spent  and number of stages cleared will be stored in a
	  custom data structure. Classes would be used to store the details
	  of  the  player's  spaceship  and  the enemy ships, such as their
	  weapons.
</pre>

<pre>
3) 	Dynamic memory management
	- Instead  of  using  statically  defined arrays with a fixed size,
	  dynamic  arrays  are used to store all enemy ships in every stage
	  to  reduce  memory  usage. As the player shoots down enemy ships,
	  the  number  of  enemy  ships  decreases, so does the size of the
	  array.
</pre>

<pre>
4)	File input/output
	- The  player  is  allowed  to save his/her current progress before
	  every stage, so he/she can resume the game from the current stage
	  in  the  future.  All  information  including  the  top  5 scores
	  displayed in the leaderboard will be stored in a text file.
</pre>

<pre>
5)	Separate files
	- All  functions will be defined separately from the main function.
	  Classes  and  custom  data  structures  will also be separated in
	  another  file.  This  is to promote encapsulation and prevent any
	  unintended  modification  or errors which may occur when updating
	  the game.
</pre>

<br/>

*Last modified : *
*Date: April 3, 2020*
*Time: 1600 HKT
