import asyncio
import msvcrt

#THIS CODE WORKS SENDING STRING MESSAGE TO HOLOLENS

async def tcp_echo_client(message, loop):
    # print("try connect")
    reader, writer = await asyncio.open_connection('192.168.1.43', 9090)
    writer.write(message.encode())
    data = await reader.read(100)
    print('Received: %r' % data.decode())
    # print("connected")
    # print('Send: %r' % message)
    # while True:
        # print(data.decode())
        # if msvcrt.kbhit():
        #     if msvcrt.getwche() == '\r':
        #         break
    # print('Close the socket')
    # writer.write_eof()
    writer.close()

message = '00,45'
loop = asyncio.new_event_loop()
asyncio.set_event_loop(loop)
loop = asyncio.get_event_loop()
while True:
    loop.run_until_complete(tcp_echo_client(message, loop))
    if msvcrt.kbhit():
        if msvcrt.getwche() == '\r':
            break
loop.close()