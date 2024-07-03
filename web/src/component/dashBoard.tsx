import styled from "styled-components";

export const DashBoardContainer = styled.div<{
    $width?:number,
    $height?:number,
}>`
    width: ${(props)=>props.$width}px;
    height: ${(props)=>props.$height}px;
    margin: 10px;
    padding 0px;
    display: flex;
    border-radius: ${(props)=>Math.min(props.$height||300, props.$width||300)/20}px;
    background-color: #F0F0F3;
    box-shadow:
        -10px -10px 30px #ffffff,
        10px 10px 30px #AEAEC066,
        inset -10px -10px 10px #AEAEC040,
        inset 10px 10px 10px #ffffff;
`
    // box-shadow: inset 
    // filter: drop-shadow(-10px, -10px, 30px, 0, #FFFFFF);
    // filter: drop-shadow(10px, 10px, 30px, 0, #AEAEC066);
    // filter: drop-shadow(-10px, -10px, 10px, 0, #AEAEC040);
    // filter: drop-shadow(10px, 10px, 10px, 0, #FFFFFF);

