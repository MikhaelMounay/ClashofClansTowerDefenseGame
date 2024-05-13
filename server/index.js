const express = require("express");
const cors = require("cors");
const pool = require("./db");

const app = express();

// Middleware
app.use(cors());
app.use(express.json());

// == Repeated Functions ==

// Getting Ranks (priority: level, gold)
const getRanks = async (username, clan) => {
    try {
        const global_rank = await pool.query("WITH global_ranking AS (SELECT username, ROW_NUMBER() OVER (ORDER BY level DESC, gold DESC) AS rank FROM players) SELECT rank FROM global_ranking WHERE username = $1", [username]);
        if (clan) {
            const clan_rank = await pool.query("WITH clan_ranking AS (SELECT username, clan, ROW_NUMBER() OVER (ORDER BY level DESC, gold DESC) AS rank FROM players WHERE clan = $1) SELECT rank FROM clan_ranking WHERE username = $2", [clan, username]);
            return { global_rank: global_rank.rows[0].rank, clan_rank: clan_rank.rows[0].rank };
        } else {
            return { global_rank: global_rank.rows[0].rank, clan_rank: 0 };
        }
    } catch (err) {
        console.log(err.message);
    }
};

// == Routes ==

// Register a New Player
app.post("/newplayer", async (req, res) => {
    try {
        const { username, hashedPassword, clan } = req.body;
        const player = await pool.query("INSERT INTO players (username, hashedpassword, level, gold, clan, cannon_id, fence_id, castle_id, worker_id) VALUES($1, $2, 1, 0, $3, 1, 1, 1, 1) RETURNING *", [username, hashedPassword, clan]);

        res.json({ playerInfo: { ...player.rows[0], ...(await getRanks(username, player.rows[0].clan)) } });
    } catch (err) {
        console.log(err.message);
        if (err.code === "23505") {
            res.json({ playerInfo: null });
        }
    }
});

// Login
app.post("/login", async (req, res) => {
    try {
        const { username, hashedPassword } = req.body;
        const player = await pool.query("SELECT * FROM players WHERE username = $1 AND hashedpassword = $2", [username, hashedPassword]);

        if (player.rows.length === 0) {
            res.json({ playerInfo: null });
        } else {
            res.json({ playerInfo: { ...player.rows[0], ...(await getRanks(username, player.rows[0].clan)) } });
        }
    } catch (err) {
        console.log(err.message);
    }
});

// Update Player Info
app.put("/player/:username/:hashedPassword", async (req, res) => {
    try {
        const { username, hashedPassword } = req.params;
        const { level, gold, clan, cannon_id, fence_id, castle_id, worker_id } = req.body;
        const player = await pool.query("UPDATE players SET level = $1, gold = $2, clan = $3, cannon_id = $4, fence_id = $5, castle_id = $6, worker_id = $7 WHERE username = $8 AND hashedpassword = $9 RETURNING *", [level, gold, clan, cannon_id, fence_id, castle_id, worker_id, username, hashedPassword]);

        if (player.rows.length === 0) {
            res.json({ playerInfo: null });
        } else {
            res.json({ playerInfo: { ...player.rows[0], ...(await getRanks(username, player.rows[0].clan)) } });
        }
    } catch (err) {
        console.error(err.message);
    }
});

// Get Player Info
app.get("/player/:username", async (req, res) => {
    try {
        const { username } = req.params;
        const player = await pool.query("SELECT * FROM players WHERE username = $1", [username]);

        if (player.rows.length === 0) {
            res.json({ playerInfo: null });
        } else {
            res.json({
                playerInfo: {
                    level: player.rows[0].level,
                    gold: player.rows[0].gold,
                    clan: player.rows[0].clan,
                    cannon_id: player.rows[0].cannon_id,
                    fence_id: player.rows[0].fence_id,
                    castle_id: player.rows[0].castle_id,
                    worker_id: player.rows[0].worker_id,
                    ...(await getRanks(username, player.rows[0].clan)),
                },
            });
        }
    } catch (err) {
        console.log(err.message);
    }
});

// Delete Player
app.delete("/player/:username/:hashedPassword", async (req, res) => {
    try {
        const { username, hashedPassword } = req.params;
        const player = await pool.query("DELETE FROM players WHERE username = $1 AND hashedpassword = $2 RETURNING *", [username, hashedPassword]);

        if (player.rows.length === 0) {
            res.json({ deleted: false });
        } else {
            res.json({ deleted: true });
        }
    } catch (err) {
        console.log(err.message);
    }
});

// Get All Clans
app.get("/clans", async (req, res) => {
    try {
        const clans = await pool.query("SELECT DISTINCT clan FROM players");

        res.json({ clans: clans.rows });
    } catch (err) {
        console.log(err.message);
        res.json({ clans: null });
    }
});

// Get All Players
app.get("/players", async (req, res) => {
    try {
        // const players = await pool.query("SELECT username, level, gold, clan, cannon_id, fence_id, castle_id, worker_id FROM players");
        const players = await pool.query(`
        WITH global_ranking AS (
            SELECT 
                username,
                ROW_NUMBER() OVER (ORDER BY level DESC, gold DESC) AS global_rank
            FROM players
        ),
        clan_ranking AS (
            SELECT 
                username,
                ROW_NUMBER() OVER (PARTITION BY clan ORDER BY level DESC, gold DESC) AS clan_rank
            FROM players
        )
        SELECT 
            players.username,
            players.level,
            players.gold,
            players.clan,
            players.cannon_id,
            players.fence_id,
            players.castle_id,
            players.worker_id,
            global_ranking.global_rank,
            clan_ranking.clan_rank
        FROM 
            players
        LEFT JOIN 
            global_ranking ON players.username = global_ranking.username
        LEFT JOIN 
            clan_ranking ON players.username = clan_ranking.username
        `);

        res.json({ players: players.rows });
    } catch (err) {
        console.log(err.message);
        res.json({ players: null });
    }
});

app.listen(process.env.PORT || 5000, () => {
    console.log("ClashOfClansAPI has started on port 5000");
});
