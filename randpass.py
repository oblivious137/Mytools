import pyperclip, random

tmp = ""
n = int(input("Input the length\n"))
for i in range(0,n):
	tmp+=chr(random.randint(33,126))
pyperclip.copy(tmp)
	