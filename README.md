# Clash of Clans | Tower Defense
*Clash of Clans | Tower Defense* is a game inspired by the popular game [Clash of Clans by Supercell](https://supercell.com/en/games/clashofclans/).

<br />

### Check the [Official Website](https://mikhaelmounay.github.io/ClashofClansTowerDefenseGame/) for the [🗺️ Game Wiki 🗺️](https://mikhaelmounay.github.io/ClashofClansTowerDefenseGame/#/gamewiki) now!

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

### Building from Source Code (Used Techs / Services)

#### **Qt C++**
- [![Qt C++ 6](https://img.shields.io/badge/-Qt%20C%2B%2B%206-41CD52?logo=Qt&logoColor=white&style=flat-square)](https://pages.github.com/)

	Used build system : `QMake 3.1` - `Desktop Qt 6.6.2 MinGW 64-bit`

#### **Web Server (RESTful API)**
 - [![Node.js](https://img.shields.io/badge/-Node%2Ejs%2020-5FA04E?logo=Node%2Ejs&logoColor=white&style=flat-square)](https://nodejs.org/) [![PostgreSQL 16](https://img.shields.io/badge/-PostgreSQL%2016-4169E1?logo=PostgreSQL&logoColor=white&style=flat-square)](https://www.postgresql.org/)
 - [![Express 4](https://img.shields.io/badge/-Express%204-000000?logo=Express&logoColor=white&style=flat-square)](https://www.express.com/)
 - [![Render.com](https://img.shields.io/badge/-Render%2Ecom-black?logoColor=white&style=flat-square)](https://render.com/)

#### **Web Client (SPA)**
 - [![React](https://img.shields.io/badge/-React%2018-61DAFB?logo=React&logoColor=black&style=flat-square)](https://react.dev/) [![Vite](https://img.shields.io/badge/-Vite%205-646CFF?logo=Vite&logoColor=white&style=flat-square)](https://vitejs.dev/)
 - [![Sass](https://img.shields.io/badge/-Sass-CC6699?logo=Sass&logoColor=white&style=flat-square)](https://sass-lang.com/)
 - [![React Router 6](https://img.shields.io/badge/-React%20Router%206-CA4245?logo=React%20Router&logoColor=white&style=flat-square)](https://reactrouter.com/)
 - [![Bootstrap 5](https://img.shields.io/badge/-Bootstrap%205-7952B3?logo=Bootstrap&logoColor=white&style=flat-square)](https://getbootstrap.com/)
 - [![DataTables 2](https://img.shields.io/badge/-DataTables%202-3a7fd5?logoColor=white&style=flat-square)](https://datatables.net/)
 - [![GitHub Pages](https://img.shields.io/badge/-GitHub%20Pages-222222?logo=GitHub%20Pages&logoColor=white&style=flat-square)](https://pages.github.com/)

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

