import gameAreaStyles from "./styles/gameArea.module.css"
import arrayAreaStyles from "./styles/arrayArea.module.css"
import handAreaStyles from "./styles/handArea.module.css"
import {ArrayElement, HeaderElement} from "../../util/Utility.tsx";
import {useEffect, useRef, useState} from "react";
import {arrayState, deckState, loadPoints, loadRounds, resetGame} from "../../networking/WebRequests.tsx";
import CardElement, {type CardData} from "./Card.tsx";
import {AnimatePresence, number} from "framer-motion";
import type {PageProps} from "../../App.tsx";
import {AlertPopup} from "../errorPopup/Popups.tsx";
import {Pages} from "../../util/Constants.ts";
import question from "../../../public/question.png";
import gameLoopStyles from "./styles/GameLoop.module.css";

function GameLoop({ setPage, setOldPoints }: PageProps & { setOldPoints: (v:number) => void }) {
    const [array, setArray] = useState<number[]>([])
    const [cards, setCards] = useState<CardData[]>([])
    const [rounds, setRounds] = useState<number>(0)
    const [points, setPoints] = useState<number>(0)
    const [showPopup, setShowPopup] = useState(false)
    const [sorted, setSorted] = useState(false)
    const [lastRound, setLastRound] = useState(0)

    const prevArray = useRef<number[]>(array);
    const sortedArray = useRef<number[]>([]);

    useEffect(() => {
        if (sorted && lastRound < 4) {
            const timer = setTimeout(() => {
                setShowPopup(true);

                const timer = setTimeout(() => {
                    setShowPopup(false);
                }, 2000);

                return () => clearTimeout(timer);
            }, 250);
            return () => clearTimeout(timer);
        }
    }, [sorted]);

    async function loadData(sorted : boolean) {
        setOldPoints(points)
        setLastRound(rounds)

        if (lastRound >= 4) setPage(Pages.GameLoop)

        loadRounds().then(v => setRounds(v));
        loadPoints().then(v => setPoints(v));

        setSorted(sorted);

        if (sorted) setArray(sortedArray.current)

        const arr = await arrayState();
        prevArray.current = arr;
        sortedArray.current = [...arr].sort((a, b) => a - b);
        setArray(arr);

        const cardData = await deckState();
        setCards(cardData);
    }

    async function reset() {
        resetGame();
        setArray([]);
        setTimeout(loadData, 500);
    }

    useEffect(() => { loadData(false) }, []);

    return (
        <div className={gameAreaStyles.pageContainer}>
            {showPopup && (<AlertPopup rounds={rounds} points={points} />)}
            <HeaderElement rounds={rounds} points={points} reset={reset} setPage={setPage}/>
            <div className={gameAreaStyles.gameArea}>
                {!showPopup && (
                    <div className={arrayAreaStyles.arrayArea}>
                        <AnimatePresence>
                            {array.map((val, ind) => (<ArrayElement value={val} key={val} spot={sortedArray.current[ind] !== val}/>))}
                        </AnimatePresence>
                        <div>
                            <img src={question} alt="question" className={gameLoopStyles.helpSymbol} />
                            <div className={ gameLoopStyles.arrayDesc}>
                                This is the array you are trying to sort, sorting is done from least to greatest, when a square is highlighted in green it is in the correct position
                            </div>
                        </div>

                    </div>

                )}
                <div className={handAreaStyles.handArea}>
                    {cards.map(((card, index) => (<CardElement key={index} card={card} index={index} sync={loadData} />)))}
                </div>
            </div>

            <div></div>
            <div></div>
            <div></div>
            <div></div>
            <div></div>
            <div></div>
        </div>
    )
}

export default GameLoop;