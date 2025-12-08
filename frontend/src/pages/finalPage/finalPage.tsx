import type { PageProps } from "../../App.tsx";
import styles from "./Styles/Endscreen.module.css";
import { Pages } from "../../util/Constants.ts";
import {changePage} from "../../networking/WebRequests.tsx";

function EndScreen({ setPage, points }: PageProps & { points:number }) {
    return (
        <div className = {styles.wrapper}>
            <div className={styles.endPopup}>
                <div className = {styles.GameoverText}>
                    Game Over
                    <br />
                    Finished with {points} points!
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