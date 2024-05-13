const { Pool } = require("pg");
const path = require("path");

require("dotenv").config({ path: path.join(__dirname, ".env") });

let poolConfig = {};

if (process.env.POSTGRES_URL != "") {
    poolConfig = {
        connectionString: process.env.POSTGRES_URL + "?sslmode=require",
    };
} else {
    poolConfig = {
        user: process.env.USER,
        host: process.env.HOST,
        database: process.env.DATABASE,
        password: process.env.PASSWORD,
        port: process.env.PORT,
    };
}

const pool = new Pool(poolConfig);

module.exports = pool;
