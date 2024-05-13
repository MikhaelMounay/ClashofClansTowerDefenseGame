import React from "react";
import ReactDOM from "react-dom/client";
import { RouterProvider } from "react-router-dom";

import router from "./router";
import * as bootstrap from "bootstrap";

import "bootstrap/dist/css/bootstrap.min.css";
import "./assets/scss/main.scss";

ReactDOM.createRoot(document.getElementById("root")).render(
    <React.StrictMode>
        <RouterProvider router={router} />
    </React.StrictMode>
);
