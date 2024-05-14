# Clash of Clans | Tower Defense
*Clash of Clans | Tower Defense* is a game inspired by the popular game [Clash of Clans by Supercell](https://supercell.com/en/games/clashofclans/).

### 🗺️ Game Wiki 🗺️
Check the [Official Website](https://mikhaelmounay.github.io/ClashofClansTowerDefenseGame/) for the [Game Wiki](https://mikhaelmounay.github.io/ClashofClansTowerDefenseGame/#/gamewiki) now!

<br />

### Patch Notes (V2.0)

**Game Launcher :**
- Removed "Settings" Button
- Added "Ranked (Online)" Button that connects the user to our Online Database (*hosted on [Render](https://render.com/)*) to join the [Leaderboard on our Website](https://mikhaelmounay.github.io/ClashofClansTowerDefenseGame/).

**Game :**
- New levels added. We know the limit is the sky when competing with friends. The game now contains endless levels so you always have the room to climb to rank 1 again.
	Technically, the game contains a fixed set of 25 levels, which can be increased in the future. The levels' graphics are repeated in a cyclic loop every 25 levels but with different stats for the enemy.
- New Item Shop added. Make sure to prepare for the battle well before locking in.
- Added health bars for the enemy, fence, and the castle.
- Added some exciting sound effects for each part of the game.

**Game Mechanics :**
- Unit movement is based on the shortest path they can find to the castle.
- Workers sprint to fix the damaged fence units in chronological order.

<br />

### Further Improvements to Work on Next Patch

*Further developments are numerous and the game is publicly [open on GitHub](https://github.com/MikhaelMounay/ClashofClansTowerDefenseGame/) for everyone who wants to contribute.*

Further developments we have in mind for now:
- Improvements in the A* Algorithm implementation, especially to deal correctly with invisible Pixmap edges.
- Change the order in which workers fix the damaged fence units to be based on the closest to the worker instead of the chronological order of being damaged.
- Designing a Map Editor Mode that can be shared online with the Clan or Globally. (Inspired by *Fortnite's Creative Mode*)
- Implementing in-game bonuses to vary the game experience. Bonuses that can appear on the map to get higher attack speed, damage, ... etc.

<br />

---

<br />


## For Developers

### Building from Source Code

***Qt C++*** 
> Used build system : `QMake 3.1` - `Desktop Qt 6.6.2 MinGW 64-bit`

***Web Server (RESTful API)***
> `Node.js (>=14)`
> 
> with `PostgreSQL (16)`
> 
> *dependencies:* `express.js (4)` *&* `pg (8)`
> 
> *hosted on* [Render](https://render.com/) 

***Web Client (SPA)***
> `React (18)` on `Vite (5)`
> 
> *with* `SASS`
> 
> *dependencies:* `React Router DOM (6)` & `DataTables (2)` & `Bootstrap (5)`
> 
> *hosted on* [GitHub Pages](https://pages.github.com/) 

<br />

### Modules

*Pages*
- *`MainWindow` Class* (inherits *`QMainWindow` Class*)
- *`ItemShopWindow` Class* (inherits *`QDialog` Class*)
- *`LoginWindow` Class* (inherits *`QDialog` Class*)
- *`Game` Class* (inherits *`QGraphicsView` Class*)

*Primary Elements*
- *`Cannon` Class* (inherits *`QGraphicsPixmapItem` & `QObject` Classes*)
- *`Bullet` Class* (inherits *`QGraphicsPixmapItem` & `QObject` Classes*)
- *`Fence` Class* (inherits *`QGraphicsPixmapItem` & `QObject` Classes*)
- *`Castle` Class* (inherits *`QGraphicsPixmapItem` & `QObject` Classes*)
- *`Enemy` Class* (inherits *`QGraphicsPixmapItem` & `QObject` Classes*)
- *`Worker` Class* (inherits *`QGraphicsPixmapItem` & `QObject` Classes*)

*Secondary Elements*
- *`HealthBar` Class* (inherits *`QGraphicsRectItem` Class*)
- *`ShopItem` Class* (inherits *`QWidget` Class*)

*Helper Classes*
- *`Player` Class* (inherits *`QObject` Class*)
- `APIClient` Class (inherits *`QObject` Class*)
- *`Astar` Class*
- *`ButtonClickAudio` Class*

<br />

![ClashOfClansQtGame _ Milestone 2](https://github.com/MikhaelMounay/ClashofClansTowerDefenseGame/assets/81804418/6a7d31dc-665a-4b48-9d53-3b3871994661)

<br />

