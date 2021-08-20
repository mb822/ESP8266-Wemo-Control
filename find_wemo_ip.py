import pywemo
import time

yes = "yes"
no = "no"

print("discovering devices...")
devices = pywemo.discover_devices()

input("------------------------------\nplease press ENTER to begin");
print("------------------------------")

for device in devices:
    device.toggle()

    
    if input("did your target device change state?\n ") == ("yes" or "YES" or "Yes" or "Y" or "y" or "1" or 1):
        print("\n--------------------IP ADDRESS of device: " + str(device.host))
        exit()
    
print("no other WeMo devices found on current network")
    
