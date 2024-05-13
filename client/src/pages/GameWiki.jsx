import React, { useEffect, useState } from "react";
import { Link } from "react-router-dom";
// import ReactMarkdown from "react-markdown";
// import remarkGfm from "remark-gfm";

// import mdFile from "../data/gamewiki.md";

import ItemShopRec from "../assets/vids/itemshop_rec.mp4";
import InGameRec from "../assets/vids/ingame_rec.mp4";

const GameWiki = () => {
    // const mdFilePath = "../data/gamewiki.md";
    // const [mdContent, setMdContent] = useState("");

    // useEffect(() => {
    //     import(mdFilePath).then((response) => {
    //         fetch(response.default)
    //             .then((response) => {
    //                 return response.text();
    //             })
    //             .then((response) => {
    //                 setMdContent(response);
    //             })
    //             .catch((err) => {
    //                 console.log(err);
    //             });
    //     });
    // }, []);

    const scrollToTop = () => {
        window.scrollTo(0, 0);
    };

    return (
        <div className="mt-0 text-center px-5 py-2">
            <div>
                <h1 className="fs-1 mb-4">Clash of Clans | Tower Defense</h1>
                <h2 className="fs-2 mb-0">🗺️ &nbsp; Game Wiki &nbsp; 🗺️</h2>
                <div className="mt-2 mb-4 d-flex align-items-center justify-content-center">
                    <hr className="w-25" />
                </div>
            </div>

            {/* <div className="md-container text-start fs-5">
                <ReactMarkdown skipHtml={false} remarkPlugins={[remarkGfm]}>
                    {mdContent}
                </ReactMarkdown>
            </div> */}

            <div className="md-container text-start fs-5">
                <div>
                    <p>
                        <em>Clash of Clans | Tower Defense</em> &nbsp; is a game inspired by the popular game <a href="https://supercell.com/en/games/clashofclans/">Clash of Clans by Supercell</a>.
                    </p>
                    <p>The purpose of the game is to defend your castle from the incoming enemies.</p>
                    <video src={InGameRec} autoPlay loop className="w-100 mx-auto mt-4 rounded-3"></video>
                    <hr />
                    <p>
                        The main role isn't just to kill the <strong>🎯 Enemies</strong>, by controlling the <strong>💣 Cannon</strong> obviously ;)
                    </p>
                    <p>
                        <em>but also</em>
                    </p>
                    <p>
                        Strategically plan for the battle by choosing the right equipment &amp; army (<strong>💣 Cannon</strong>, <strong>🧱 Fence</strong>, <strong>🏰 Castle</strong>, <strong>🤺 Citizen Workers</strong>) from the <strong>🏪 Item Shop</strong> and determining when to save and when to spend your <strong>🪙 Gold</strong>.
                    </p>
                    <video src={ItemShopRec} autoPlay loop className="w-100 mx-auto mt-4 rounded-3"></video>
                    <hr />
                    <h2 id="-who-said-boring-">👀 Who said "boring" ?!</h2>
                    <p>The game offers two modes: offline basic mode and online competitive mode.</p>
                    <h5 id="in-the-offline-mode-">In the offline mode ....</h5>
                    <ul>
                        <li>Each time you open the game, you start exploring the game levels from 🎚️ Level 1 and on.</li>
                        <li>If you got defeated in some level, you restart from 🎚️ Level 1 again.</li>
                        <li>Pretty good for an offline game, right :)</li>
                    </ul>
                    <h5 id="in-the-online-mode-">In the online mode ....</h5>
                    <ul>
                        <li>After signing in to your account, you progress is saved after winning each level.</li>
                        <li>If you got defeated in some level, you'll stuck trying hard to pass it.</li>
                        <li>
                            <strong>
                                <em>The exciting part</em>
                            </strong>{" "}
                            : joining the online game mode means you joined <em>Clash of Clans | Tower Defense Leaderboard</em>, competing 🏅 <strong>globally</strong> and 🎖️ <strong>locally</strong>, if you joined a clan ;) , to get your name to the top of the Leaderboard.
                        </li>
                    </ul>
                    <p>
                        <em>Note: The Leaderboard is ranked based on</em> 🎚️ <em>Level primarily and</em> 🪙 <em>Gold secondarily.</em>
                    </p>
                    <hr />
                    <h2 id="-main-elements-in-the-battlefield">⚔️ Main elements in the battlefield</h2>
                    <p>Each element in the battlefield has its own properties that you, the General, should know to prepare for the battle.</p>
                    <p>
                        <strong>
                            <em>Keep in mind</em>
                        </strong>{" "}
                        &nbsp; that you should remember the symbol for each property, because in an actual battle there is no time to read :( . <em>i.e., the properties names are not written in the</em> 🏪 <em>Item Shop.</em>
                    </p>
                    <h4 id="1-cannon-">1. Cannon 💣</h4>
                    <ul>
                        <li>💥 Bullet Damage</li>
                        <li>💨 Bullet Speed (Travel Time)</li>
                        <li>🚀 Attack Speed</li>
                    </ul>
                    <h4 id="2-fence-">2. Fence 🧱</h4>
                    <ul>
                        <li>🛡️ Health</li>
                    </ul>
                    <h4 id="3-castle-">3. Castle 🏰</h4>
                    <ul>
                        <li>🛡️ Health</li>
                    </ul>
                    <h4 id="4-citizen-worker-">4. Citizen Worker 🤺</h4>
                    <ul>
                        <li>🛠️ Repairing (Healing) Ability</li>
                        <li>🏃 Movement Speed</li>
                    </ul>
                    <h4 id="5-enemy-">5. Enemy 🎯</h4>
                    <ul>
                        <li>💥 Attack Damage</li>
                        <li>🛡️ Health</li>
                        <li>🏃 Movement Speed</li>
                        <li>⏱️ Spawn Interval</li>
                    </ul>
                    <hr />
                    <h2 id="-item-shop">🏪 Item Shop</h2>
                    <ul>
                        <li>
                            <p>
                                By killing enemies, you start to earn 🪙 <em>Gold</em>, which you can spend (or save depending on the mighty General's strategic plan) in the Item Shop.
                            </p>
                        </li>
                        <li>
                            <p>
                                Before <em>Locking in</em> each battle, you pass by the 🏪 Item Shop to upgrade your equipment.
                            </p>
                        </li>
                        <li>
                            <p>The stats of the next 🎯 Enemy is always showed in the Item Shop.</p>
                        </li>
                    </ul>
                    <p>
                        <strong>The only advice we would give is to know your enemies well 🫵</strong>
                    </p>
                    <hr />
                    <p>
                        <em>The items themselves will not be showed in this Wiki, but you can download and explore the game now</em> ;)
                    </p>
                </div>
            </div>

            <button className="btn btn-success fs-4 mt-5 mb-3">Download & Play Now</button>

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

export default GameWiki;
