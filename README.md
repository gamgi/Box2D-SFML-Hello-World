The Box2D lib is not included in this repository:

  For building get Box2d from:
  wget https://github.com/erincatto/Box2D/archive/master.zip
  unzip master.zip
  cd Box2D-master/Box2D
  
  Then Build it:
  instructions in building.txt file
  (instructions also in) https://noz3001.wordpress.com/2011/06/19/2d-game-development-with-opengl-setting-up-box2d/

  Or on arch, using AUR:s
  pacman -S box2d

The SFML lib is not included either:
  on ubuntu: apt-get install libsfml-dev
  on arch: pacman -S sfml



Then learn about box2d:
http://www.box2d.org/manual.html

Noteworthy is the coordinate systems used and units.

The example can be built with
  make main

Then run by 
  make run




