import styled from "styled-components";
import { record } from "@/types/enumTypes";
import styles from "@/component/fix.module.css";

const ChartContainer = styled.div<{
    $width?:number,
    $height?:number,
}>`
    width: ${(props)=>props.$width}px;
    height: ${(props)=>props.$height}px;
    margin: 10px;
    padding 0px;
    border-radius: ${(props)=>Math.min(props.$height||300, props.$width||300)/20}px;
    display: flex;
    flex-direction: row;
    flex-warp: nowrap;
    justify-content: flex-start;
    align-items: flex-end;
    padding: 0px 0px 0px 20px;
    background-color: #F0F0F3;
    box-shadow:
        inset -10px -10px 10px #FFFFFFB6,
        inset 10px 10px 10px #AEAEC040;
`

const OneRecord = styled.div<{
    $height?:number,
}>`
    width: 30px;
    height: ${(props)=>props.$height}px;
    background-color: #00000000;
    border-radius: 5px 5px 0px 0px;
    margin: 0px 0px 0px 10px;
`
const RecordPoint = styled.div<{
}>`
    width: 30px;
    height: 30px;
    background-color: #394D5F;
    border-radius: 15px;
    position: relative;
    top: -15px;
    display: flex;
    justify-content: center;
    align-items: center;
`

export default function Chart({
    records
}:{
    records: record[]
}){
    return ( //have warning here, but I could seen where have no-key problem. maybe <></>? 等優化再來解決
        <ChartContainer $width={450} $height={250}>{
            records.length<=10?(
                records.map((obj)=>(
                    <OneRecord key={obj.time} $height={obj.offset_x+125}>
                        <RecordPoint key={obj.time}>
                            <p key={obj.time} className={styles.pointFont}>{`${obj.offset_x}`}</p>
                        </RecordPoint>
                    </OneRecord>
                ))
            ):(
                records.map((obj)=>(
                    obj.time+10>records.length?(
                        <OneRecord key={obj.time} $height={obj.offset_x+125}>
                            <RecordPoint key={obj.time}>
                                <p key={obj.time} className={styles.pointFont}>{`${obj.offset_x}`}</p>
                            </RecordPoint>
                        </OneRecord>
                    ):<></>
                ))
            )
        }</ChartContainer>
        // <>
        //     {/* <div className={styles.shadow}></div> */}
        // </>
    );
}