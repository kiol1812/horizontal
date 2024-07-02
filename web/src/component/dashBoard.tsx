import styled from "styled-components";

export const DashBoardContainer = styled.div<{
    $width?:number,
    $height?:number,
}>`
    width: ${(props)=>props.$width}px;
    height: ${(props)=>props.$height}px;
    background-color: #aaaaaa;
    margin: 10px;
    padding 0px;
    display: flex;
    border-radius: ${(props)=>Math.min(props.$height||300, props.$width||300)/20}px;
`


