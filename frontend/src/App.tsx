import {Pages} from "./util/Constants.ts";
import MainMenu from "./pages/mainMenu/MainMenu.tsx";
import "./App.css"
import GameLoop from "./pages/gameLoopPage/GameLoop.tsx";
import {useEffect, useState} from "react";
import {requestPage, serverStatus} from "./networking/WebRequests.tsx";
import ServerErrorPopup from "./pages/errorPopup/ErrorPopup.tsx";

export type PageProps = {
    setPage: (page: string) => void;
}

function App() {
    const [page, setPage] = useState<string>(Pages.MainMenu);
    const [serverActive, setServerActive] = useState<boolean>(true)

    useEffect(() => {
        const update = () => {
            serverStatus().then(result => setServerActive(result != undefined))
            requestPage().then(pageData => { if (pageData) setPage(pageData); })
        }

        update()

        const interval = setInterval(update, 5000)
        return () => clearInterval(interval);
    }, [])

    return (
      <div className="App">
          {!serverActive && <ServerErrorPopup />}
          {page == Pages.MainMenu && <MainMenu setPage={p => setPage(p)} />}
          {page == Pages.GameLoop && <GameLoop setPage={p => setPage(p)} />}
      </div>
    )
}

export default App
