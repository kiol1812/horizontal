import styled from "styled-components";
import { point } from "@/types/enumTypes";

const Circle = styled.div<{
    $size?:number,
}>`
    width: ${(props)=>props.$size}px;
    height: ${(props)=>props.$size}px;
    margin: 10px;
    padding: 10px;
    display: flex;
    border-radius: 50%;
    justify-content: center;
    align-items: center;
    box-shadow:
        inset -10px -10px 10px #FFFFFFB6,
        inset 10px 10px 10px #AEAEC040;
`
const Point = styled.div<{
    $size?:number,
    $x?:number,
    $y?:number,
}>`
    width: ${(props)=>props.$size}px;
    height: ${(props)=>props.$size}px;
    border-radius: 50%;
    background-color: #394D5F;
    position: relative;
    top: ${(props)=>props.$y}px;
    left: ${(props)=>props.$x}px;
    display: flex;
    justify-content: center;
    algin-items: center;
`
const OriginPoint = styled.div<{
}>`
    width: 10px;
    height: 10px;
    border-radius: 5px;
    background-color: #FEF9E6;
    position: absolute;
    z-index: 10;
`

const PointDescription = styled.p`
    position: relative;
    top: 50px;
    background-color: #00000000;
    color: #394D5F;
`

export default function CircleContainer({
    point
}:{
    point:point
}){
    return (
        <Circle $size={300}>
            <OriginPoint />
            <Point $size={50} $x={point.x} $y={point.y}>
                <PointDescription>{`(${point.x},${point.y})`}</PointDescription>
            </Point>
            {/* <Point $size={50} $x={0} $y={0} /> */}
        </Circle>
    );
}