import React, { useRef, useState } from "react";

const Login = ({ handleLoggedInState }) => {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");

    const usernameValidRef = useRef(null);
    const passwordValidRef = useRef(null);
    const errorRef = useRef(null);

    const hashString = async (input) => {
        const msgUint8 = new TextEncoder().encode(input);
        const hashBuffer = await crypto.subtle.digest("SHA-256", msgUint8);
        const hashArray = Array.from(new Uint8Array(hashBuffer));
        const hashHex = hashArray.map((b) => b.toString(16).padStart(2, "0")).join("");
        return hashHex;
    };

    const handleSubmit = (e) => {
        e.preventDefault();

        // Validation
        let valid = true;
        if (username == "") {
            usernameValidRef.current.classList.remove("d-none");
            valid = false;
        } else {
            usernameValidRef.current.classList.add("d-none");
        }

        if (password == "") {
            passwordValidRef.current.classList.remove("d-none");
            valid = false;
        } else {
            passwordValidRef.current.classList.add("d-none");
        }

        if (!valid) {
            return;
        }

        // Handle login
        hashString(password).then((hashedPassword) => {
            fetch(`${import.meta.env.VITE_API_BASE_URL}/login`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({
                    username: username,
                    hashedPassword: hashedPassword,
                }),
            }).then((response) => {
                if (!response.ok) {
                    alert("Something went wrong! Please try again.");
                } else {
                    response.json().then((data) => {
                        if (data.playerInfo == null) {
                            errorRef.current.classList.remove("d-none");
                        } else {
                            errorRef.current.classList.add("d-none");
                            handleLoggedInState(data.playerInfo);
                        }
                    });
                }
            });
        });
    };

    return (
        <div>
            <form onSubmit={handleSubmit} className="login-form mx-auto text-start fs-5">
                <div className="mb-5">
                    <label htmlFor="usernameInput" className="form-label">
                        Username
                    </label>
                    <input
                        type="text"
                        className="form-control"
                        id="usernameInput"
                        value={username}
                        onChange={(e) => {
                            setUsername(e.target.value);
                        }}
                    />
                    <div ref={usernameValidRef} className="form-text text-danger mt-2 d-none">
                        Please enter a username!
                    </div>
                </div>

                <div className="mb-5">
                    <label htmlFor="passwordInput" className="form-label">
                        Password
                    </label>
                    <input
                        type="password"
                        className="form-control"
                        id="passwordInput"
                        value={password}
                        onChange={(e) => {
                            setPassword(e.target.value);
                        }}
                    />
                    <div ref={passwordValidRef} className="form-text text-danger mt-2 d-none">
                        Please enter a password!
                    </div>
                </div>

                <div ref={errorRef} className="form-text text-center text-danger mt-0 mb-4 d-none">
                        Incorrect username or password!
                </div>

                <button type="submit" className="btn btn-success d-block mx-auto fs-5">
                    Login
                </button>
            </form>
        </div>
    );
};

export default Login;
