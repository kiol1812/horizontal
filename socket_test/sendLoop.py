import asyncio
import websockets

#THIS CODE WORKS SENDING STRING MESSAGE TO HOLOLENS

async def tcp_echo_client(message, loop):
    print("try connect")
    reader, writer = await asyncio.open_connection('192.168.1.43', 9090)
    print("connected")

    print('Send: %r' % message)
    writer.write(message.encode())

    data = await reader.read(100)
    print('Received: %r' % data.decode())

    print('Close the socket')
    writer.close()

message = 'hello from PC'
loop = asyncio.new_event_loop()
asyncio.set_event_loop(loop)
loop = asyncio.get_event_loop()
loop.run_until_complete(tcp_echo_client(message, loop))
loop.close()