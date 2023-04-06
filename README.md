# LTNC2023_INT2215_22
# Chu Huy Quang_22028104
* MyFirstGame WarCraft (War between AirCrafts :D)
#### Table of contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [How to play](#play)
4. [Installation](#installation)

# Introduction <a name="introduction"></a>
* The game is inspired by [Star Wars](https://en.wikipedia.org/wiki/Star_Wars) - one of the most well-known series about space and [Chicken Invaders](https://en.wikipedia.org/wiki/Chicken_Invaders) - the famous shooting game developed in 1999.
* The game was created using [SDL2](https://www.libsdl.org/) and C++.
* The resources used in this game are mostly collected from [itch.io](https://itch.io/game-assets) and have been edited to suit the property of the game.
* Some functions used in the game were learned from Lazyfoo and [Phattrienphanmem123az](http://phattrienphanmem123az.com/)
  * Timer.h / Timer.cpp [AdvancedTimer](https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php)
  * Text.h / Text.cpp  [TrueTypeFonts](https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php)
  * object.h / object.cpp, rendergame.h / rendergame.cpp: learn from phattrienphanmem123az and have many additions.

# Features <a name="features"></a>

**1. GameWindow**
* Two game mode: PlayervsBot and PlayervsPlayer.
* Animations for player, enemies, shield and explosion.
* 3 skills for player, 3 types of enemy.
* Seamless background based on type of enemy.
* Random pickups: shield, heal and asteroid.
* Limit FPS to be compatible with all devices (if not, when running the game on a high-configuration machine, the image will be rendered too fast, causing the "fast forward" effect).

**2. TabPause/GameOver**
* Enable/Mute the game.
* View current score.
* Continue, exit and replay.

![Screenshot (141)](https://user-images.githubusercontent.com/111046219/230269203-aead33d6-f2ab-445c-8e81-2a3ed34e32af.png)

**3. TabGameMenu**
* Start/Exit.
* HighScore/Information.
* Setting Volume.
* Shop to buy skin for player.

![Screenshot (135)](https://user-images.githubusercontent.com/111046219/230268944-490a3639-cb54-4221-be6c-e68b3537239e.png)

# How to play <a name="play"></a>
* Use AWSD to move.
* Use QER to use skills.
* Use SPACE to shoot.
* Press ESC to Pause.

# Installation <a name="installation"></a>
Download zip, open 'x64/Release/WarCraft.exe' to PLAY.
