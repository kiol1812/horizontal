import { io, Socket } from "socket.io-client";

interface ServerToClientEvents{
    // noArg: () => void;
    // basicEmit: (a:number, b:string, c:Buffer) => void;
    // withAck: (d:string, callback:(e:number)=>void) => void;
    serverMsg: (data: {msg:string;}) => void;
}
interface ClientToServerEvents{
    // hello: () => void;
    clientMsg: (data: {msg:string;}) => void;
}

// const socket: Socket<ServerToClientEvents, ClientToServerEvents> = io();

// socket.emit("hello");
// socket.on("noArg", ()=>{
//     console.log("noArg");
// })
// socket.on("basicEmit", ()=>{
//     console.log("basicEmit");
// })
// socket.on("withAck", ()=>{
//     console.log("withAck");
// })

export default function page(){
    const socket: Socket<ServerToClientEvents, ClientToServerEvents> = io("http://192.168.1.43:9090");
    socket.on('connect', ()=>{
        console.log(`client: ${socket.id}`);
    });
    function handleSubmit(){
        socket.emit("clientMsg", {msg:"hello from ts"});
    }
    return (
        <>test</>
    );
}




