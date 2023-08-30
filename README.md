# EvilPortal-ESP32


# why
I made this cause i didnt want to buy a wifi dev board for my F0


# how to install
you'll need:  
ESP32 dev board
microsd card with a creds.txt
microsd card reader  module

# how to use
Currently only instagram is suported, and its hard coded, but its coming.  
you'll want to change the SSID, something convincing that people wont get thrown off being asked for their instagram credentials

# social engeering tips

if you're worried about targets, questioning why this portal is asking for random credentials,heres my tips for you  
create a sense that the user isnt supposed to be there, for instance, with no password, people will connect, but set the name to a group of people, such as "Staff"  
if the user doesnt think theyre supposed to be there, they wont quesiton why theyre getting asked for creds, its baseless


# making it practical
Unless you want to carry around a portable charger, or laptop, with a cord streaming to a loose ESP32 and SD card reader, I see two options  

1) use a portable charger, with some sort of case, and fix the components inside.

2) use 18650 batteries, and make your own portable charger, in a case.

for both, if you dont use the cable, make sure you connect to the 5v pin, if you dont, the LED will come on but no wifi networks will be made.    

Option 1 -   
find or print some sort of hard plastic carrying case, 



# TODO
sdcard pinouts  
add text file if it isnt deteced  
add other portals
