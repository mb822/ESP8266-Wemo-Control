import pywemo
import time

print("discovering devices...")
devices = pywemo.discover_devices()

input("------------------------------\nplease press ENTER to begin");
print("------------------------------")

for device in devices:
    device.toggle()

    answer = input("did your target device change state?\n ")
    
    if answer.lower() == "yes" or answer == 1 or answer.lower() == "maybe":
        print("--------------------\nIP ADDRESS OF DEVICE: " + str(device.host))
        exit()
    
print("no other WeMo devices found on current network")
    
