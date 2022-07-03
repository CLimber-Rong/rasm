'''我用python编写MAKEFILE，他更方便'''

import sys
import os
from posixpath import split

class rmake:
    elemfile = []
    cmd = ''
    def analysis(self,cmd = ''):
        if cmd[0] == '-':
                self.elemfile.append(str(cmd[1:]))
                return True
        elif cmd[0]=='=':
                self.elemfile.append(os.path.join(os.getcwd(),cmd[2:]))
                return True
        elif cmd[0]=='#':
            flag = True
            self.cmd = cmd[1:]
            for i in self.elemfile:
                if not os.path.exists(str(i)):
                    raise FileNotFoundError('Element file lost named %s'%str(i))
                    flag = False
            if flag:
                os.system(cmd[1:])
                self.cmd = ''
                self.elemfile = []
                return True
            else:
                print('RMAKE ERROR!')
                return False
        else:
            raise TypeError('Unknow command type named %s'%cmd[0])
            flag = False

            
    def makefile(self,path = ''):
        file = open(path,"r")
        cmd = file.read()
        cmdl = cmd.split('\n')
        for i in cmdl:
            if not self.analysis(str(i)):
                return False
        return True
        


if __name__=='__main__':
    # main funtion
    mymake = rmake()
    if mymake.makefile(sys.argv[1]):
        print('\n'+'FILE MAKED')