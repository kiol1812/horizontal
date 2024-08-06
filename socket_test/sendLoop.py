import asyncio
import msvcrt

#THIS CODE WORKS SENDING STRING MESSAGE TO HOLOLENS
# pc

async def tcp_echo_client(message, loop):
    # print("try connect")
    reader, writer = await asyncio.open_connection('192.168.1.18', 9090)
    # print("connected")
    writer.write(message.encode())
    # while True:
        # if msvcrt.kbhit():
        #     if msvcrt.getwche() == '\r':
        #         break
    # data = await reader.read(100)
    # print('Received: %r' % data.decode())
    # print('Send: %r' % message)
    # print('Close the socket')
    # writer.write_eof()
    writer.close()

message = '25,10'
loop = asyncio.new_event_loop()
asyncio.set_event_loop(loop)
loop = asyncio.get_event_loop()
while True:
    loop.run_until_complete(tcp_echo_client(message, loop))
    # if msvcrt.kbhit():
    #     if msvcrt.getwche() == '\r':
    #         break
loop.close()