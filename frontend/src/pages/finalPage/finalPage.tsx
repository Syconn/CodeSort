import type { PageProps } from "../../App.tsx";
import styles from "./Styles/Endscreen.module.css";
import { Pages } from "../../util/Constants.ts";
import {changePage} from "../../networking/WebRequests.tsx";

function EndScreen({ setPage, points }: PageProps & { points:number }) {
    return (
        <div className = {styles.wrapper}>
            <div className={styles.endPopup}>
                <div className = {styles.GameoverText}>
                    <p className= {styles.gameOver}>Game Over</p>
                    <p className = {styles.poinDisplay}>
                    {points} Points
                    </p>
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