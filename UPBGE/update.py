import bge
import socket
from bone import Bone
from struct import unpack
from mathutils import Quaternion
from time import sleep
def pulse(controller):
    armature = controller.owner 
    if armature.get('isInit'):
        
        armature['socket'].sendto('a'.encode('ASCII'), ("192.168.1.20", 6666))
        pack = armature['socket'].recv(256)
        
        
        for i in range(4):
            armature['BONES'][i].update(pack[i*20:(i+1)*20])
            
        armature.update()
        
        
    else:
        
        armature['socket'] = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        armature['socket'].setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        armature['socket'].settimeout(0.1)
        try:
            armature['socket'].bind(('', 5535))
        except Exception as E:
            print(E)
        
        armature['BONES'] = [
         Bone(0, armature.channels["Left arm"] , (1,-1,1)),
         Bone(1, armature.channels["Right arm"], (-1,1,1)),
         Bone(2, armature.channels["Left leg"] , (-1,1,1)),
         Bone(3, armature.channels["Right leg"], (-1,1,1))
         ]
        
        armature['isInit'] = True
        
        