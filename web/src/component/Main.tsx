import styled from "styled-components";
import useMedia from "@/Hooks/useMedia";
import React from "react";

const MainContainer = styled.div`
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    flex-wrap: nowrap;
    justify-content: center;
    align-items: flex-start;
`
const TtileBar = styled.div`
    width: 100%;
    height: 100px;
    border: 2px #394D5F solid;
    border-radius: 10px;
    display: flex;
    justify-content: center;
    align-items: center;
`
const Title = styled.p`
    font-size: 24px;
`
const Center_when_Desktop = styled.div`
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    jusitify-content: center;
    align-items: center;
`;

export default function Main({
    children
}:{
    children:React.ReactNode
}){
    return (
        <MainContainer>
            <TtileBar>
                <Title>Title</Title>
            </TtileBar>
            <Center_when_Desktop>
                {children}
            </Center_when_Desktop>
        </MainContainer>
    );
}