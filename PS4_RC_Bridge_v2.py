
# PS4 RC Bridge v2
# pip install pygame-ce websocket-client

import json,time,signal,sys
import pygame
from websocket import create_connection

ESP_IP="192.168.4.1"
WS_URL=f"ws://{ESP_IP}:81"

UPDATE_HZ=100
DEADZONE=0.06
STEER_EXPO=1.7

pygame.init()
pygame.joystick.init()

ws=None
js=None

def expo(v,e):
    if abs(v)<DEADZONE:
        return 0.0
    s=1 if v>=0 else -1
    return s*(abs(v)**e)

def connect_controller():
    global js
    while True:
        pygame.joystick.quit()
        pygame.joystick.init()
        if pygame.joystick.get_count():
            js=pygame.joystick.Joystick(0)
            js.init()
            print(f"✓ Controller: {js.get_name()}")
            return
        print("Waiting for controller...")
        time.sleep(1)

def connect_ws():
    global ws
    while True:
        try:
            print("Connecting to ESP...")
            ws=create_connection(WS_URL,timeout=2)
            print("✓ Connected")
            return
        except Exception:
            print("Retrying...")
            time.sleep(1)

def estop():
    global ws
    try:
        if ws:
            ws.send(json.dumps({"steer":0,"r2":0,"l2":1}))
            ws.close()
    except:
        pass

def shutdown(sig=None,frm=None):
    print("\nStopping...")
    estop()
    pygame.quit()
    sys.exit(0)

signal.signal(signal.SIGINT,shutdown)

connect_controller()
connect_ws()

print("Running at",UPDATE_HZ,"Hz")

period=1.0/UPDATE_HZ

while True:
    start=time.time()

    try:
        pygame.event.pump()

        if not js.get_init():
            print("Controller disconnected.")
            connect_controller()

        steer=expo(js.get_axis(0),STEER_EXPO)

        a4=js.get_axis(4)
        a5=js.get_axis(5)

        # Auto-detect trigger range
        if a4 < -0.1 or a5 < -0.1:
            l2=(a4+1)/2
            r2=(a5+1)/2
        else:
            l2=max(0,min(1,a4))
            r2=max(0,min(1,a5))

        msg={
            "steer":round(steer,3),
            "r2":round(r2,3),
            "l2":round(l2,3)
        }

        ws.send(json.dumps(msg))

    except Exception:
        print("Connection lost.")
        estop()
        connect_ws()

    dt=time.time()-start
    if dt<period:
        time.sleep(period-dt)
