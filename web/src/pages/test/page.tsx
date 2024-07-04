import useMedia from "@/Hooks/useMedia";
import styled from "styled-components";

const Desktop = styled.div`
    width: 1000px;
    height: 500px;
    background-color: #000000;
`
const Tablet = styled.div`
    width: 800px;
    height: 500px;
    background-color: #000000;
`
const Mobile = styled.div`
    width: 600px;
    height: 500px;
    background-color: #000000;
`

export default function page(){
    const { isMobile, isTablet, isDesktop } = useMedia();
    return (
        <>{
            isDesktop?(
                <>
                    <Desktop />
                    <p>desktop</p>
                </>
            ):(
                isTablet?(
                    <>
                        <Tablet />
                        <p>tablet</p>
                    </>
                ):(
                    <>
                        <Mobile />
                        <p>mobile</p>
                    </>
                )
            )
        }</>
    );
}