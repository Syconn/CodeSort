import handAreaStyles from "./styles/handArea.module.css";
import { HelpCircle } from "lucide-react";
import {sortCard} from "../../networking/WebRequests.tsx";

export type CardData = {
    name: string,
    image: string,
    description: string,
}

function CardElement({ card, index, sync }: { card: CardData, index: number, sync: () => void }) {
    return (
        <div className={handAreaStyles.card} onClick={() => sortCard(index, sync)}>
            <div className={handAreaStyles.hoverCorner}>
                <HelpCircle size={16} />
            </div>
            <div className={handAreaStyles.cardDesc}>{card.description}</div>
            <p className={handAreaStyles.cardText}>{card.name}</p>
            <img className={handAreaStyles.photo}  alt={""} src={card.image} />
        </div>
    )
}

export default CardElement