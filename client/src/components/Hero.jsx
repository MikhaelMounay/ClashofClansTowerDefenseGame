import React from "react";
import { Link } from "react-router-dom";

import ClashOfClansIcon from "../assets/imgs/icon.png";
import GitHubIcon from "../assets/imgs/github.svg";

const Hero = () => {
    return (
        <>
            <div className="hero mt-0 text-center px-3">
                <img src={ClashOfClansIcon} alt="Clash of Clans Icon" className="landing-icon rounded mb-5" />
                <h1 className="mb-3">Clash of Clans | Tower Defense</h1>
                <p className="text-muted fs-5 fst-italic">
                    A Qt-based desktop clone for the popular mobile game{" "}
                    <a className="text-muted" target="_blank" href="https://supercell.com/en/games/clashofclans/">
                        Clash of Clans by Supercell
                    </a>
                </p>
                <p className="text-muted fs-5">Play now and make your and defend your rank or compete among your friends within a clan!</p>
                <p className="text-muted mt-4">Made with ❤️ by Mikhael Khalil | Kirollos Mounir | Amonios Beshara @ AUC</p>

                {/* TODO: Link for game download */}
                <button className="btn btn-success fs-4 mt-5 mb-4">Download & Play Now</button>

                <div className="row w-75 mx-auto g-4 mt-1 text-muted fs-6">
                    <div className="col-md-4 d-flex align-items-center justify-content-center">
                        {/* TODO: GitHub Repo link */}
                        Contribute on &nbsp;
                        <a href="https://github.com/MikhaelMounay/ClashofClansTowerDefenseGame/" target="_blank">
                            GitHub Repo &nbsp;{" "}
                            <span>
                                <img src={GitHubIcon} width="20"></img>
                            </span>
                        </a>
                    </div>
                    <div className="col-md-4 d-flex align-items-center justify-content-center">
                        <Link to="userpanel">Sign in to manage account</Link>
                    </div>
                    <div className="col-md-4 d-flex align-items-center justify-content-center">
                        <Link to="gamewiki">🗺️ Game Wiki</Link>
                    </div>
                </div>
            </div>
        </>
    );
};

export default Hero;
