import cv2
import os, sys
import time
import paho.mqtt.client as mqtt


def startdetector():
    while True:
        if os.path.exists("/dev/shm/0.jpg"):
            os.system("cp /dev/shm/0.jpg /dev/shm/raw.jpg")
            raw="/dev/shm/raw.jpg"
            print("OK")
            break
    framedetector(raw)



def framedetector(raw):
    host = sys.argv[1]
    port = int(sys.argv[2])
    subscribe_name = sys.argv[3]
    print("args :::", host, port, subscribe_name)
    client = mqtt.Client()
    client.connect(host, port, 60)
    while True:
        timea=time.time()
        new ="/dev/shm/0.jpg"
        img1 = cv2.imread(raw)
        img2 = cv2.imread(new)
        
        if img1 is None or img2 is None:
            print("???")
            continue
        H1 = cv2.calcHist([img1], [1], None, [256], [0, 256])
        H1 = cv2.normalize(H1, H1, 0, 1, cv2.NORM_MINMAX, -1)

        H2 = cv2.calcHist([img2], [1], None, [256], [0, 256])
        H2 = cv2.normalize(H2, H2, 0, 1, cv2.NORM_MINMAX, -1)

  
        similarity = abs(cv2.compareHist(H1, H2, 0))



        if similarity < 0.99 :
            os.system("cp /dev/shm/0.jpg /dev/shm/raw.jpg")
            client.publish(subscribe_name, raw, 1)
        timeb=time.time()
        print("framedetectortime:",timeb-timea)
#        else:
#            continue




if __name__=='__main__':
    startdetector()
