import os.path

f = open(os.path.dirname(os.path.abspath(__file__)) + '/index.h', 'w')
f.write('struct A_Class {')
f.write('int a = 0;')
f.write('};')
f.close()
