from mathutils import Quaternion
from struct import unpack
class Bone():
    RAD_90 = 1.5707963267948966
    def __init__(self, id : int, bone, c_vec : tuple) -> None:
        self.id = str(id).encode('ASCII')
        self.idNum = id
        self.bone = bone
        self.corection = Quaternion((-1.05, 1.05, 1.05), Bone.RAD_90)
    def update(self, data):
        index, w,x,y,z = unpack('iffff', data)
        if index == self.idNum:
            self.bone.rotation_quaternion = Quaternion((w,x,y,z)) #* self.corection
        