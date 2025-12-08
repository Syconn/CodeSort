import {Pages} from "./util/Constants.ts";
import MainMenu from "./pages/mainMenu/MainMenu.tsx";
import "./App.css"
import GameLoop from "./pages/gameLoopPage/GameLoop.tsx";
import {useEffect, useState} from "react";
import {requestPage, serverStatus} from "./networking/WebRequests.tsx";
import {ErrorPopup} from "./pages/errorPopup/Popups.tsx";
import EndScreen from "./pages/finalPage/finalPage.tsx";

export type PageProps = {
    setPage: (page: string) => void;
}

function App() {
    const [page, setPage] = useState<string>(Pages.MainMenu);
    const [oldPoints, setOldPoints] = useState<number>(0);
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
          {!serverActive && <ErrorPopup />}
          {page == Pages.MainMenu && <MainMenu setPage={p => setPage(p)} />}
          {page == Pages.GameLoop && <GameLoop setPage={p => setPage(p)} setOldPoints={setOldPoints} />}
          {page == Pages.EndScreen && <EndScreen setPage={p => setPage(p)} points={oldPoints} />}
      </div>

    )
}

export default App
