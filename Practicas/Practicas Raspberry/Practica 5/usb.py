import os
import subprocess
import sys
import csv
filename = sys.argv[1]
numberOfItems = sys.argv[2]
rpistr = "ls /media/pi/MonCab"
proc = subprocess.Popen(rpistr, shell=True, preexec_fn=os.setsid,stdout=subprocess.PIPE)
line = proc.stdout.readline()
directory =  line.rstrip()
data = []
for i in range(int(numberOfItems)):
    data.append([i, " Hola USB ", "data" + str(i)])

with open("/media/pi/MonCab"+directory+"/fse.csv", 'w') as csvFile:
        writer = csv.writer(csvFile)
        writer.writerows(data)
csvFile.close()
