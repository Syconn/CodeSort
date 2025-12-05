import { X } from "lucide-react"
import styles from "./styles/ServerErrorPopup.module.css"

function ServerErrorPopup() {
    return (
        <div className={styles.overlay}>
            <div className={styles.popup}>
                <X size={48} className={styles.icon} />
                <h2>Server is Not Running</h2>
                <p>Please restart.</p>
            </div>
        </div>
    )
}

export default ServerErrorPopup