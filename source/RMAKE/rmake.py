'''我用python编写MAKEFILE，他更方便'''

from enum import Flag
import sys
import os
from posixpath import split

class rmake:
    elemfile = []
    cmd = ''
    Flag = True
    def analysis(self,cmd = ''):
        if cmd=='- %::POSIX::%':
            if os.name!='posix':
                self.Flag = False
                print('Little Warning: Your system is not POSIX,so we continue this command!')
                return True
            else:
                return True
        if cmd=='- %::NT::%':
            if os.name!='nt':
                self.Flag = False
                print('Little Warning: Your system is not NT,so we continue this command!')
                return True
            else:
                return True
        if cmd[0] == '-':
            self.elemfile.append(str(cmd[1:]))
            return True
        elif cmd[0]=='=':
            if self.Flag==False:
                return True
            self.elemfile.append(os.path.join(os.getcwd(),cmd[2:]))
            return True
        elif cmd[0]=='>':
            if self.Flag==False:
                self.Flag = True
                return True
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
                self.Flag = True
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