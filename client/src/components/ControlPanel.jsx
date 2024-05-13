import React, { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";

import Cannons from "../data/cannons.json";
import Fences from "../data/fences.json";
import Castles from "../data/castles.json";
import Workers from "../data/workers.json";

const ControlPanel = ({ PlayerInfo }) => {
    const navigate = useNavigate();

    const [playerInfo, setPlayerInfo] = useState(PlayerInfo);
    const [clans, setClans] = useState([]);
    const [changedClan, setChangedClan] = useState(playerInfo.clan);
    const [isNewClan, setIsNewClan] = useState(false);
    const [isDeleteConfirmed, setIsDeleteConfirmed] = useState(false);

    const fetchClans = async () => {
        try {
            console.log(import.meta.env.VITE_API_BASE_URL);
            const response = await fetch(import.meta.env.VITE_API_BASE_URL + "/clans");
            const jsonData = await response.json();
            setClans(jsonData.clans);
        } catch (err) {
            console.log(err.message);
        }
    };

    const handleChangeClan = (e) => {
        e.preventDefault();

        if (isNewClan && changedClan == "") {
            return;
        }

        fetch(`${import.meta.env.VITE_API_BASE_URL}/player/${playerInfo.username}/${playerInfo.hashedpassword}`, {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify({
                level: playerInfo.level,
                gold: playerInfo.gold,
                clan: changedClan,
                cannon_id: playerInfo.cannon_id,
                fence_id: playerInfo.fence_id,
                castle_id: playerInfo.castle_id,
                worker_id: playerInfo.worker_id,
            }),
        }).then((response) => {
            if (!response.ok) {
                alert("Something went wrong! Please try again.");
            } else {
                response.json().then((data) => {
                    setPlayerInfo({ ...data.playerInfo });
                    if (isNewClan) {
                        console.log(changedClan);
                        setClans([...clans, { clan: changedClan }]);
                        setIsNewClan(false);
                    }
                });
            }
        });
    };

    const handleAccountDelete = () => {
        fetch(`${import.meta.env.VITE_API_BASE_URL}/player/${playerInfo.username}/${playerInfo.hashedpassword}`, {
            method: "DELETE",
        }).then((response) => {
            if (!response.ok) {
                alert("Something went wrong! Please try again.");
            } else {
                response.json().then((data) => {
                    if (!data.deleted) {
                        alert("Something went wrong!");
                    } else {
                        navigate("/", { replace: true });
                    }
                });
            }
        });
    };

    useEffect(() => {
        fetchClans();
    }, []);

    return (
        <div className="control-panel">
            <div className="row fs-5">
                {/* Player Controls */}
                <div className="col-md-6">
                    {/* Change Clan */}
                    <div className="mb-4">
                        <h3 className="mb-3">{playerInfo.clan == "" ? "Join a " : "Change"} Clan</h3>
                        {playerInfo.clan != "" && <p className="mb-4"> Current Clan: {playerInfo.clan}</p>}

                        {!isNewClan && clans.length > 0 && (
                            <div>
                                <form onSubmit={handleChangeClan} className="d-flex align-items-center justify-content-around mx-5">
                                    <select
                                        className="form-select me-5"
                                        value={changedClan}
                                        onChange={(e) => {
                                            setChangedClan(e.target.value);
                                        }}
                                    >
                                        <option value="" className="text-muted">
                                            (Just leave!)
                                        </option>
                                        {clans.map((clan, index) => {
                                            if (clan.clan != "") {
                                                return (
                                                    <option key={index} value={clan.clan}>
                                                        {clan.clan}
                                                    </option>
                                                );
                                            }
                                        })}
                                    </select>
                                    <button type="submit" className="btn btn-success">
                                        Change
                                    </button>
                                </form>

                                <button
                                    className="btn mt-4 text-muted text-decoration-underline"
                                    onClick={() => {
                                        setIsNewClan(true);
                                        setChangedClan("");
                                    }}
                                >
                                    Create New Clan
                                </button>
                            </div>
                        )}

                        {isNewClan && clans.length > 0 && (
                            <div>
                                <form onSubmit={handleChangeClan} className="d-flex align-items-center justify-content-around mx-5">
                                    <input
                                        type="text"
                                        className="form-control"
                                        placeholder="Clan name"
                                        value={changedClan}
                                        onChange={(e) => {
                                            setChangedClan(e.target.value);
                                        }}
                                    ></input>
                                    <button type="submit" className="btn btn-success">
                                        Create
                                    </button>
                                </form>

                                <button
                                    className="btn mt-4 text-muted text-decoration-underline"
                                    onClick={() => {
                                        setIsNewClan(false);
                                        setChangedClan(playerInfo.clan);
                                    }}
                                >
                                    Join Existing Clan
                                </button>
                            </div>
                        )}
                    </div>

                    {/* Delete Account */}
                    <div className="mt-5 mb-4">
                        <h3 className="text-danger">Delete Account</h3>
                        <p
                            className="text-danger fst-italic confirm-delete"
                            onClick={() => {
                                setIsDeleteConfirmed(!isDeleteConfirmed);
                            }}
                        >
                            Once you delete your account, you cannot recover it!
                        </p>
                        {isDeleteConfirmed && (
                            <button className="btn btn-danger" onClick={handleAccountDelete}>
                                Delete Account!
                            </button>
                        )}
                    </div>
                </div>

                {/* Player Info */}
                <div className="col-md-6 text-center">
                    <h3>Player Info</h3>
                    <p className="mb-1">📛 {playerInfo.username} 📛</p>
                    <p className="mb-1">🎚️ {playerInfo.level}</p>
                    <p className="mb-1">🪙 {playerInfo.gold}</p>
                    <p className="mb-1">🤼 {playerInfo.clan === "" ? "(No Clan)" : playerInfo.clan}</p>
                    <p className="mb-1">🎖️ C# {parseInt(playerInfo.clan_rank) === 0 ? "∞" : playerInfo.clan_rank}</p>
                    <p className="mb-1">🏅 G# {parseInt(playerInfo.global_rank) === 0 ? "∞" : playerInfo.global_rank}</p>
                    <p className="mb-1">💣 {Cannons.cannons[playerInfo.cannon_id - 1].name}</p>
                    <p className="mb-1">🧱 {Fences.fences[playerInfo.fence_id - 1].name}</p>
                    <p className="mb-1">🏰 {Castles.castles[playerInfo.castle_id - 1].name}</p>
                    <p className="mb-1">🤺 {Workers.workers[playerInfo.worker_id - 1].name}</p>
                </div>
            </div>
        </div>
    );
};

export default ControlPanel;
