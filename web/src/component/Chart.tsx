import styled from "styled-components";
import { record } from "@/types/enumTypes";

const ChartContainer = styled.div<{
    $width?:number,
    $height?:number,
}>`
    width: ${(props)=>props.$width}px;
    height: ${(props)=>props.$height}px;
    background-color: #ffffff;
    margin: 10px;
    padding 0px;
    border-radius: ${(props)=>Math.min(props.$height||300, props.$width||300)/20}px;
    display: flex;
    flex-direction: row;
    flex-warp: nowrap;
    justify-content: flex-start;
    align-items: flex-end;
`

const OneRecord = styled.div<{
    $height?:number,
}>`
    width: 30px;
    height: ${(props)=>props.$height}px;
    background-color: #00ff00;
    border-radius: 5px 5px 0px 0px;
    margin: 0px 0px 0px 10px;
`

export default function Chart({
    records
}:{
    records: record[]
}){
    return (
        <ChartContainer $width={450} $height={200}>{
            records.map((obj)=>(
                <OneRecord key={obj.time} $height={obj.offset_x+100} />
            ))
        }</ChartContainer>
    );
}