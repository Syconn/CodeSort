import type { PageProps } from "../../App.tsx";
// import styles from "./styles/MainMenu.module.css";
import styles from "./Styles/Endscreen.module.css";
import { Pages } from "../../util/Constants.ts";
import {changePage} from "../../networking/WebRequests.tsx";

function EndScreen({ setPage }: PageProps) {
    return (
        <div className = {styles.wrapper}>
            <div className={styles.endPopup}>
                <div className = {styles.GameoverText}>
                    Game Over
                </div>
                <div>

                </div>
                <div className={styles.buttonWrapper}>
                    <button className = {styles.buttonGeneral}
                        onClick={() => changePage(Pages.GameLoop, setPage)}
                    >
                        Restart
                    </button>
                    <button className = {styles.buttonGeneral}
                        onClick={() => changePage(Pages.MainMenu, setPage)}
                    >
                        Main Menu
                    </button>
                </div>
            </div>
        </div>
    );
}

export default EndScreen;