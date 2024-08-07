import styled from "styled-components";

const AlertContainer = styled.div`
    width: 300px;
    height: 200px;
    border: 3px #394D5F solid;
    border-radius: 20px;
    position: absolute;
    top:30px;
    display: flex;
    justify-content: space-around;
    flex-direction: column;
`
const AlertTitle = styled.h1`
    display: flex;
    justify-content: center;
`
const AlertMsg = styled.p`
    display: flex;
    justify-content: center;
    margin-bottom: 40px;
`
const HideBtn = styled.button`
    position: absolute;
    bottom: 5px;
    right: 5px;
    width: 45px;
    height: 30px;
    border-radius: 10px;
`

export default function Alert({
    show,
    onHide,
    msg,
}:{
    show:boolean,
    onHide:()=>void,
    msg:string
}){
    return(
        show?(<AlertContainer>
            {/* <h1>Alert</h1> */}
            <AlertTitle>Alert</AlertTitle>
            <AlertMsg>{msg}</AlertMsg>
            {/* <button onClick={onHide}>hide</button> */}
            <HideBtn onClick={onHide}>ok</HideBtn>
        </AlertContainer>):(<></>)
    );
}