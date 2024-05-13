import React, { useState } from "react";
import { Link } from "react-router-dom";

import Login from "../components/Login";
import ControlPanel from "../components/ControlPanel";

const UserPanel = () => {
    const [loggedIn, setLoggedIn] = useState(false);
    const [playerInfo, setPlayerInfo] = useState({});

    const handleLoggedInState = (PlayerInfo) => {
        setLoggedIn(true);
        setPlayerInfo(PlayerInfo);
    };

    const scrollToTop = () => {
        window.scrollTo(0, 0);
    };

    return (
        <div className="mt-0 text-center px-3">
            <div>
                <p className="fs-1 mb-0">{loggedIn ? `Hello ${playerInfo.username} 👋` : "Welcome Back"}</p>
                <div className="mt-2 mb-4 d-flex align-items-center justify-content-center">
                    <hr className="w-25" />
                </div>
            </div>
            
            {!loggedIn && <Login handleLoggedInState={handleLoggedInState} />}
            {loggedIn && <ControlPanel PlayerInfo={playerInfo} />}

            <div className="mt-5 text-center">
                <Link to="/">
                    <button className="btn text-decoration-underline" onClick={scrollToTop}>
                        Back to Home ⬅️
                    </button>
                </Link>
                <button className="btn text-decoration-underline" onClick={scrollToTop}>
                    Scroll to top ⬆️
                </button>
            </div>
        </div>
    );
};

export default UserPanel;
