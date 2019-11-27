import time
import datetime
import SDL_DS1307

ds1307 = SDL_DS1307.SDL_DS1307(1, 0x68)
ds1307.write_now()

while True:
	print()
	print("Raspberry Pi = \t" + time.strftime("%Y-%m-%d %H:%M:%S"))

	print("DS1307=\t\t",ds1307.read_datetime())

	time.sleep(10.0)