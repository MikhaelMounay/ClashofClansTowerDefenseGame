import React, { useRef, useState, useEffect } from "react";
import DataTable from "datatables.net-bs5";

import "datatables.net-bs5/css/dataTables.bootstrap5.min.css";

import Cannons from "../data/cannons.json";
import Fences from "../data/fences.json";
import Castles from "../data/castles.json";
import Workers from "../data/workers.json";

const Leaderboard = () => {
    const lbTableRef = useRef(null);
    const [lbData, setLbData] = useState(null);

    const fetchLbData = async () => {
        try {
            const response = await fetch(`${import.meta.env.VITE_API_BASE_URL}/players`);
            const jsonData = await response.json();

            console.log(jsonData.players);
            for (let i = 0; i < jsonData.players.length; i++) {
                jsonData.players[i].global_rank = parseInt(jsonData.players[i].global_rank);
            }

            setLbData(jsonData.players);
        } catch (err) {
            console.log(err.message);
        }
    };

    const getRankOne = () => {
        for (let i = 0; i < lbData.length; i++) {
            if (lbData[i].global_rank == 1) {
                return lbData[i];
            }
        }
    }

    useEffect(() => {
        fetchLbData();
        const refreshLb = setInterval(fetchLbData, 10000);
        
        return () => {
            clearInterval(refreshLb);
        }
    }, []);

    useEffect(() => {
        const dt = new DataTable(lbTableRef.current, {
            paging: false,
            responsive: true,
            ordering: true,
            fixedHeader: true,
            scrollX: true,
            layout: {
                topStart: "info",
                topEnd: "search",
                bottomStart: null,
                bottomEnd: null,
            },
            language: {
                info: "_TOTAL_ players",
                infoEmpty: "0 players",
                infoFiltered: "(filtered from _MAX_ total players)",
            },
            data: lbData,
            columns: [
                // { data: "global_rank", title: "Global Rank", render: (data) => ("🏅 " + data) },
                // { data: "clan_rank", title: "Clan Rank", render: (data) => ("🎖️ " + data) },
                { data: "global_rank", title: "Global Rank" },
                { data: "clan_rank", title: "Clan Rank" },
                { data: "username", title: "Username", render: (data) => ("📛 " + data) },
                { data: "level", title: "Level", render: (data) => ("🎚️ " + data) },
                { data: "gold", title: "Gold", render: (data) => ("🪙 " + data) },
                { data: "cannon_id", title: "Cannon", render: (data) => ("💣 " + Cannons.cannons[data - 1].name) },
                { data: "fence_id", title: "Fence", render: (data) => ("🧱 " + Fences.fences[data - 1].name) },
                { data: "castle_id", title: "Castle", render: (data) => ("🏰 " + Castles.castles[data - 1].name) },
                { data: "worker_id", title: "Worker", render: (data) => ("🤺 " + Workers.workers[data - 1].name) },
                { data: "clan", title: "Clan", render: (data) => (data == "" ? "" : ("🤼 " + data)) },
            ],
        });

        const handleResize = () => {
            dt.columns.adjust().draw();
        };

        window.addEventListener("resize", handleResize);

        return () => {
            dt.destroy();
            window.removeEventListener("resize", handleResize);
        };
    }, [lbData]);

    return (
        <>
            <div className="leaderboard mt-0 text-center">
                <h1 className="mb-4">Leaderboard</h1>
                <h4 className="mb-3">{lbData && `🥇 ${getRankOne().username} 🥇`}</h4>
                {/* TABLE */}
                <div className="table-container table-responsive w-100">
                    <table ref={lbTableRef} className="table fs-5 table-success table-striped table-hover w-100"></table>
                </div>
            </div>
        </>
    );
};

export default Leaderboard;
