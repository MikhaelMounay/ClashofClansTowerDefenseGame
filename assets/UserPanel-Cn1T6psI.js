import{r as a,j as e,u as N,L as v}from"./index-CacztNA1.js";import{C as w,F as y,a as C,W as S}from"./workers-BzU4q7tQ.js";const k=({handleLoggedInState:d})=>{const[m,s]=a.useState(""),[h,c]=a.useState(""),r=a.useRef(null),t=a.useRef(null),o=a.useRef(null),x=async l=>{const u=new TextEncoder().encode(l),j=await crypto.subtle.digest("SHA-256",u);return Array.from(new Uint8Array(j)).map(n=>n.toString(16).padStart(2,"0")).join("")},p=l=>{l.preventDefault();let u=!0;m==""?(r.current.classList.remove("d-none"),u=!1):r.current.classList.add("d-none"),h==""?(t.current.classList.remove("d-none"),u=!1):t.current.classList.add("d-none"),u&&x(h).then(j=>{fetch("https://clashofclanstowerdefensegame.onrender.com/login",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({username:m,hashedPassword:j})}).then(f=>{f.ok?f.json().then(g=>{g.playerInfo==null?o.current.classList.remove("d-none"):(o.current.classList.add("d-none"),d(g.playerInfo))}):alert("Something went wrong! Please try again.")})})};return e.jsx("div",{children:e.jsxs("form",{onSubmit:p,className:"login-form mx-auto text-start fs-5",children:[e.jsxs("div",{className:"mb-5",children:[e.jsx("label",{htmlFor:"usernameInput",className:"form-label",children:"Username"}),e.jsx("input",{type:"text",className:"form-control",id:"usernameInput",value:m,onChange:l=>{s(l.target.value)}}),e.jsx("div",{ref:r,className:"form-text text-danger mt-2 d-none",children:"Please enter a username!"})]}),e.jsxs("div",{className:"mb-5",children:[e.jsx("label",{htmlFor:"passwordInput",className:"form-label",children:"Password"}),e.jsx("input",{type:"password",className:"form-control",id:"passwordInput",value:h,onChange:l=>{c(l.target.value)}}),e.jsx("div",{ref:t,className:"form-text text-danger mt-2 d-none",children:"Please enter a password!"})]}),e.jsx("div",{ref:o,className:"form-text text-center text-danger mt-0 mb-4 d-none",children:"Incorrect username or password!"}),e.jsx("button",{type:"submit",className:"btn btn-success d-block mx-auto fs-5",children:"Login"})]})})},I=({PlayerInfo:d})=>{const m=N(),[s,h]=a.useState(d),[c,r]=a.useState([]),[t,o]=a.useState(s.clan),[x,p]=a.useState(!1),[l,u]=a.useState(!1),j=async()=>{try{console.log("https://clashofclanstowerdefensegame.onrender.com");const i=await(await fetch("https://clashofclanstowerdefensegame.onrender.com/clans")).json();r(i.clans)}catch(n){console.log(n.message)}},f=n=>{n.preventDefault(),!(x&&t=="")&&fetch(`https://clashofclanstowerdefensegame.onrender.com/player/${s.username}/${s.hashedpassword}`,{method:"PUT",headers:{"Content-Type":"application/json"},body:JSON.stringify({level:s.level,gold:s.gold,clan:t,cannon_id:s.cannon_id,fence_id:s.fence_id,castle_id:s.castle_id,worker_id:s.worker_id})}).then(i=>{i.ok?i.json().then(b=>{h({...b.playerInfo}),x&&(console.log(t),r([...c,{clan:t}]),p(!1))}):alert("Something went wrong! Please try again.")})},g=()=>{fetch(`https://clashofclanstowerdefensegame.onrender.com/player/${s.username}/${s.hashedpassword}`,{method:"DELETE"}).then(n=>{n.ok?n.json().then(i=>{i.deleted?m("/",{replace:!0}):alert("Something went wrong!")}):alert("Something went wrong! Please try again.")})};return a.useEffect(()=>{j()},[]),e.jsx("div",{className:"control-panel",children:e.jsxs("div",{className:"row fs-5",children:[e.jsxs("div",{className:"col-md-6",children:[e.jsxs("div",{className:"mb-4",children:[e.jsxs("h3",{className:"mb-3",children:[s.clan==""?"Join a ":"Change"," Clan"]}),s.clan!=""&&e.jsxs("p",{className:"mb-4",children:[" Current Clan: ",s.clan]}),!x&&c.length>0&&e.jsxs("div",{children:[e.jsxs("form",{onSubmit:f,className:"d-flex align-items-center justify-content-around mx-5",children:[e.jsxs("select",{className:"form-select me-5",value:t,onChange:n=>{o(n.target.value)},children:[e.jsx("option",{value:"",className:"text-muted",children:"(Just leave!)"}),c.map((n,i)=>{if(n.clan!="")return e.jsx("option",{value:n.clan,children:n.clan},i)})]}),e.jsx("button",{type:"submit",className:"btn btn-success",children:"Change"})]}),e.jsx("button",{className:"btn mt-4 text-muted text-decoration-underline",onClick:()=>{p(!0),o("")},children:"Create New Clan"})]}),x&&c.length>0&&e.jsxs("div",{children:[e.jsxs("form",{onSubmit:f,className:"d-flex align-items-center justify-content-around mx-5",children:[e.jsx("input",{type:"text",className:"form-control",placeholder:"Clan name",value:t,onChange:n=>{o(n.target.value)}}),e.jsx("button",{type:"submit",className:"btn btn-success",children:"Create"})]}),e.jsx("button",{className:"btn mt-4 text-muted text-decoration-underline",onClick:()=>{p(!1),o(s.clan)},children:"Join Existing Clan"})]})]}),e.jsxs("div",{className:"mt-5 mb-4",children:[e.jsx("h3",{className:"text-danger",children:"Delete Account"}),e.jsx("p",{className:"text-danger fst-italic confirm-delete",onClick:()=>{u(!l)},children:"Once you delete your account, you cannot recover it!"}),l&&e.jsx("button",{className:"btn btn-danger",onClick:g,children:"Delete Account!"})]})]}),e.jsxs("div",{className:"col-md-6 text-center",children:[e.jsx("h3",{children:"Player Info"}),e.jsxs("p",{className:"mb-1",children:["📛 ",s.username," 📛"]}),e.jsxs("p",{className:"mb-1",children:["🎚️ ",s.level]}),e.jsxs("p",{className:"mb-1",children:["🪙 ",s.gold]}),e.jsxs("p",{className:"mb-1",children:["🤼 ",s.clan===""?"(No Clan)":s.clan]}),e.jsxs("p",{className:"mb-1",children:["🎖️ C# ",parseInt(s.clan_rank)===0?"∞":s.clan_rank]}),e.jsxs("p",{className:"mb-1",children:["🏅 G# ",parseInt(s.global_rank)===0?"∞":s.global_rank]}),e.jsxs("p",{className:"mb-1",children:["💣 ",w.cannons[s.cannon_id-1].name]}),e.jsxs("p",{className:"mb-1",children:["🧱 ",y.fences[s.fence_id-1].name]}),e.jsxs("p",{className:"mb-1",children:["🏰 ",C.castles[s.castle_id-1].name]}),e.jsxs("p",{className:"mb-1",children:["🤺 ",S.workers[s.worker_id-1].name]})]})]})})},L=()=>{const[d,m]=a.useState(!1),[s,h]=a.useState({}),c=t=>{m(!0),h(t)},r=()=>{window.scrollTo(0,0)};return e.jsxs("div",{className:"mt-0 text-center px-3",children:[e.jsxs("div",{children:[e.jsx("p",{className:"fs-1 mb-0",children:d?`Hello ${s.username} 👋`:"Welcome Back"}),e.jsx("div",{className:"mt-2 mb-4 d-flex align-items-center justify-content-center",children:e.jsx("hr",{className:"w-25"})})]}),!d&&e.jsx(k,{handleLoggedInState:c}),d&&e.jsx(I,{PlayerInfo:s}),e.jsxs("div",{className:"mt-5 text-center",children:[e.jsx(v,{to:"/",children:e.jsx("button",{className:"btn text-decoration-underline",onClick:r,children:"Back to Home ⬅️"})}),e.jsx("button",{className:"btn text-decoration-underline",onClick:r,children:"Scroll to top ⬆️"})]})]})};export{L as default};
