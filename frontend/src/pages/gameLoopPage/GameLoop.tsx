import gameAreaStyles from "./styles/gameArea.module.css"
import arrayAreaStyles from "./styles/arrayArea.module.css"
import handAreaStyles from "./styles/handArea.module.css"
import {ArrayElement, HeaderElement} from "../../util/Utility.tsx";
import {useEffect, useRef, useState} from "react";
import {arrayState, deckState, restart} from "../../networking/WebRequests.tsx";
import CardElement, {type CardData} from "./Card.tsx";
import {AnimatePresence} from "framer-motion";
import type {PageProps} from "../../App.tsx";

function GameLoop({ setPage }: PageProps) {
    const [array, setArray] = useState<number[]>([])
    const [cards, setCards] = useState<CardData[]>([])
    const [turns] = useState<number>(0)
    const [points] = useState<number>(0)

    const prevArray = useRef<number[]>(array);
    const sortedArray = useRef<number[]>([]);

    async function loadData() {
        const arr = await arrayState();
        prevArray.current = arr;
        sortedArray.current = [...arr].sort((a, b) => a - b);
        setArray(arr);

        const cardData = await deckState();
        setCards(cardData);
    }

    async function reset() {
        restart()
        setArray([]);
        setTimeout(loadData, 500);
    }

    useEffect(() => { loadData() }, []);

    return (
        <div className={gameAreaStyles.pageContainer}>
            <HeaderElement turns={turns} points={points} reset={reset} setPage={setPage}/>
            <div className={gameAreaStyles.gameArea}>
                <div className={arrayAreaStyles.arrayArea}>
                    <AnimatePresence>
                        {array.map((val, ind) => (<ArrayElement value={val} key={val} spot={sortedArray.current[ind] !== val}/>))}
                    </AnimatePresence>
                </div>
                <div className={handAreaStyles.handArea}>
                    {cards.map(((card, index) => (<CardElement card={card} index={index} sync={loadData} />)))}
                </div>
            </div>
        </div>
    )
}

export default GameLoop;