import React from "react";
import { Outlet } from "react-router-dom";

function App() {
    return (
        <>
            <div className="body-background container py-5 px-0">
                <Outlet />
            </div>
        </>
    );
}

export default App;
