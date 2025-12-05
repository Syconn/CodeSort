import { motion } from "framer-motion";
import arrayAreaStyles from "../pages/gameLoopPage/styles/arrayArea.module.css"
import headerStyles from "../pages/gameLoopPage/styles/header.module.css";

export function ArrayElement({ value, spot } : { value: number, spot: boolean }) {
    return (
        <motion.div
            layout
            initial={{ opacity: 0, scale: 0.8 }}
            animate={{ opacity: 1, scale: 1 }}
            exit={{ opacity: 0, scale: 0.8 }}
            transition={{ type: "spring", stiffness: 300, damping: 20 }}
            className={`${arrayAreaStyles.arrayDigit} ${spot ? arrayAreaStyles.redSpot : arrayAreaStyles.greenSpot}`}>
            {value}
        </motion.div>
    )
}

export function HeaderElement({ turns, points, reset } : { turns: number, points: number, reset: () => void }) {
    return (
        <div className={headerStyles.header}>
            <button className={headerStyles.resetButton} onClick={() => reset()}> Restart </button>
            <div className={headerStyles.title}>
                <p className={headerStyles.titleText}>CodeSort</p>
                <img className={headerStyles.titleImage} src="/codeSort.png" alt="" />
            </div>
            <div className= {headerStyles.rightSection}>
                <p className = {headerStyles.turns}> Turns Passed {turns} </p>
                <p className = {headerStyles.points}> Total Points {points} </p>
            </div>
        </div>
    )
}

// export function