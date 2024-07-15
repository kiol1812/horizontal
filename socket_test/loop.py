import msvcrt, time

i = 0
while True:
    i+=1
    if msvcrt.kbhit():
        if msvcrt.getwche() == '\r':
            break
    time.sleep(0.1)
print(i)