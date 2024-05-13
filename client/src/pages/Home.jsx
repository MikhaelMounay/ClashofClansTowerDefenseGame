import React from "react";
import Hero from "../components/Hero";
import Leaderboard from "../components/Leaderboard";

const Home = () => {
    const scrollToTop = () => {
        window.scrollTo(0, 0);
    };

    return (
        <div>
            <Hero />
            <div className="my-5 d-flex align-items-center justify-content-center">
                <hr className="w-75" />
            </div>
            <Leaderboard />
            <div className="mt-5 text-center">
                <button className="btn text-decoration-underline" onClick={scrollToTop}>
                    Scroll to top ⬆️
                </button>
            </div>
        </div>
    );
};

export default Home;
