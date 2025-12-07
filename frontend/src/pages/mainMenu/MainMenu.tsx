import type { PageProps } from "../../App.tsx";
import styles from "./styles/MainMenu.module.css";
import { Pages } from "../../util/Constants.ts";
import {changePage} from "../../networking/WebRequests.tsx";


function MainMenu({ setPage }: PageProps) {
    return (
        <div className={styles.pageContainer}>
            <div className={styles.topSection}>

                <div className={styles.topBg}></div>
                <div className={styles.topBg2}></div>
                <div className={styles.topBg3}></div>

                <div className={styles.titleBox}>
                    <p className={styles.titleText}>Code-Sort</p>
                    <img className={styles.titleImage} alt="" src="/codeSort.png" />
                </div>
                <p className={styles.creators}>
                    Aidan Haack, Arron Ye, Rebecca Forman, Adrianna Bui, Gopi Melam, Liam Bast
                </p>
            </div>

            <div className={styles.bottomSection}>
                <button className={styles.playButton}
                    onClick={() => changePage(Pages.GameLoop, setPage)}>
                    Play Game
                </button>
                <button className={styles.playButton}
                    onClick={() => changePage(Pages.Tutorial, setPage)}>
                    Tutorial
                </button>
            </div>
        </div>
    );
}

export default MainMenu;