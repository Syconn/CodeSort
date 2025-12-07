import { X } from "lucide-react"
import styles from "./styles/ServerErrorPopup.module.css"

export function ErrorPopup() {
    return (
        <div className={styles.overlay}>
            <div className={styles.popup}>
                <X size={48} className={styles.icon} />
                <h2 className={styles.rh2}>Server is Not Running</h2>
                <p className={styles.rp}>Please restart.</p>
            </div>
        </div>
    )
}

export function AlertPopup({ rounds, points } : { rounds: number, points: number }) {
    return (
        <div className={styles.overlay}>
            <div className={styles.success}>
                <h2 className={styles.gh2}>Successfully Sorted round {rounds} Array!</h2>
                <p className={styles.gp}>You have {points} points now</p>
            </div>
        </div>
    )
}