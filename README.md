#Lab projects for Napier's Games Engineering - 2018/2019

A few projects built during lab sessions demonstrating the basics of building games in C++.
Games rendering and physics are handled using external libraries. (SFML and Box2d)


1.
Built a functional Pong game where the computer is in charge of both the paddels. 
No user input is required, the paddles moves in the correct position by calculating the future position of the ball

![pong](https://github.com/Willyees/SET09121_labs/blob/assets/assets/pong.png)

2.
Built a Space Invaders demo. Very simple, similar to the original, in fact no buffs are spawned after destroing invaders. They gradually reach the bottom of the screen, increasing the speed of movement.
User can move the spaceship, dodge projects and shoot

![space_invaders](https://github.com/Willyees/SET09121_labs/blob/assets/assets/space_invaders.png)

3.
Introduced the concept of maps, designing different leveles as txt files.
A simple level is built where the user can move a physical object which cannot go out from the imposed track. The aim is to reach the end of the track

![maze](https://github.com/Willyees/SET09121_labs/blob/assets/assets/maze.png)

4.
Pacman demo has been created. AI were also introduced. User can move around the track.
Initial project requires future improvements, because AI are getting quickly stuck on corners

![pacman](https://github.com/Willyees/SET09121_labs/blob/assets/assets/pacman.png)

###Conlusion
All the projects proposed have to be seen as practice to understand the inner workings of game creation and not final working games. They have been useful to grasp concepts applied on the coursework
In fact, bugs are present and is quite easy to crash the games.

To be able to compile the solution, after cloning the repo run the command `git submodule init` followed by `git submodule update`. Finally, use CMAKE and compile the CMakeLists in the root folder. 
