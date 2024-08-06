import asyncio
# from getkey import getkey

async def tcp_echo_client(message, loop):
    reader, writer = await asyncio.open_connection('192.168.1.18', 9090)
    writer.write(message.encode())
    writer.close()

message = '13,21'
loop = asyncio.new_event_loop()
asyncio.set_event_loop(loop)
loop = asyncio.get_event_loop()

while True:
    loop.run_until_complete(tcp_echo_client(message, loop))

loop.close()


