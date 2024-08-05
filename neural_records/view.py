# 2024/08/05

import cv2

cap = cv2.VideoCapture('/dev/video0', cv2.CAP_V4L)
# cap = cv2.VideoCapture(0)

# cap.set(cv2.CAP_PROP_FRAME_WIDTH, 2560)
# cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1440)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1440)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1440)
# cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
# cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1280)


while True:
    ret, frame = cap.read()
    img = cv2.resize(frame, (360, 360), interpolation=cv2.INTER_AREA)
    cv2.imshow("stream", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()