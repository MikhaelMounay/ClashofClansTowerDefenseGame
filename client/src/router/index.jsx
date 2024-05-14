import React, { Suspense, lazy } from "react";
// import { Route, createBrowserRouter, createRoutesFromElements } from "react-router-dom";
import { Route, createHashRouter, createRoutesFromElements, redirect } from "react-router-dom";

import App from "../App.jsx";

// Lazy (Dynamic) Import
const Home = lazy(() => import("../pages/Home.jsx"));
const UserPanel = lazy(() => import("../pages/UserPanel.jsx"));
const GameWiki = lazy(() => import("../pages/GameWiki.jsx"));

// Preparing for Suspense
const LoadingElement = () => {
    return <div className="text-center fs-3">Loading ...</div>;
};

const wrappedWithSuspense = (Component) => {
    return (
        <Suspense fallback={<LoadingElement />}>
            <Component />
        </Suspense>
    );
};

// Routes
const router = createHashRouter(
    createRoutesFromElements(
        <Route path="/" element={<App />}>
            <Route index element={wrappedWithSuspense(Home)} />
            <Route path="userpanel" element={wrappedWithSuspense(UserPanel)} />
            <Route path="gamewiki" element={wrappedWithSuspense(GameWiki)} />
            <Route path="ClashofClansTowerDefenseGame" loader={() => redirect("/")} />
            <Route path="ClashofClansTowerDefenseGame/userpanel" loader={() => redirect("/userpanel")} />
            <Route path="ClashofClansTowerDefenseGame/gamewiki" loader={() => redirect("/gamewiki")} />
        </Route>
    )
);

export default router;
