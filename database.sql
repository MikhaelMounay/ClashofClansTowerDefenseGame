CREATE DATABASE clashofclans;

CREATE TABLE players (
    username VARCHAR(50) PRIMARY KEY,
    hashedpassword CHAR(64),
    level INT NOT NULL,
    gold INT NOT NULL,
    clan VARCHAR(100),
    cannon_id INT,
    fence_id INT,
    castle_id INT,
    worker_id INT
);
