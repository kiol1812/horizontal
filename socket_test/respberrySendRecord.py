# windows didn't hava getkey, I gusses
# 這邊等raspberry pi 測試完後再補齊

import asyncio
# from getkey import getkey

async def tcp_echo_client(message, loop):
    reader, writer = await asyncio.open_connection('192.168.1.43', 9090)
    # print('Send: %r' % message)
    writer.write(message.encode())
    data = await reader.read(100)
    # print('Received: %r' % data.decode())
    # print('Close the socket')
    # writer.close()

message = '0,30'
loop = asyncio.new_event_loop()
asyncio.set_event_loop(loop)
loop = asyncio.get_event_loop()
while True:
    loop.run_until_complete(tcp_echo_client(message, loop))
    # k = getkey(blocking=False)
    # if len(k)>0:
        # break
loop.close()


