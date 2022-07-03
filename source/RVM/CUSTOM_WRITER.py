
'''这个批处理程序将setting.ini文件分析并写入custom.c文件，格式是json'''
'''The batch program parses the setting.ini file and writes it to a custom.c file in json format '''
'''你需要在setting.ini里输入以下键-值：
    USER_MEM_PARTITION:INT
    CODE_MEM_PARTITION:INT
'''
'''You need to enter the following key-values in setting.ini:
    USER_MEM_PARTITION:INT
    CODE_MEM_PARTITION:INT
'''
import json
fout = open("custom.c","w")
fin = open("setting.ini","r").read().encode()
ans = json.loads(fin.decode())
for i in list(ans):
    fout.write("#define RASM_"+i+" "+str(ans[i])+'\n')
fout.close()
exit()