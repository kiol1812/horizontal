import styled from "styled-components";
import { point } from "@/types/enumTypes";

const Circle = styled.div<{
    $size?:number,
}>`
    width: ${(props)=>props.$size}px;
    height: ${(props)=>props.$size}px;
    background-color: #ffffff;
    margin: 10px;
    padding: 10px;
    display: flex;
    border-radius: 50%;
    justify-content: center;
    align-items: center;
`
const Point = styled.div<{
    $size?:number,
    $x?:number,
    $y?:number,
}>`
    width: ${(props)=>props.$size}px;
    height: ${(props)=>props.$size}px;
    border-radius: 50%;
    background-color: #ff0000;
    position: relative;
    top: ${(props)=>props.$y}px;
    left: ${(props)=>props.$x}px;
`

export default function CircleContainer({
    point
}:{
    point:point
}){
    return (
        <Circle $size={300}>
            <Point $size={50} $x={point.x} $y={point.y} />
        </Circle>
    );
}