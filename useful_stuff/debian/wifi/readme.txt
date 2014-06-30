1. Update and install Ralink firmware using

	sudo apt-get update && apt-get install firmware-ralink

2. Connect the device to the Beagle

3. Run

	lusb | grep Ralink

   You should see the device. Then run

	lsmod | grep rt2

   You should see somthing a list with drivers

4. Add the network to /etc/network/interfaces like

	auto wlan0
	iface wlan0 inet dhcp
	wpa-ssid <Your Access Point Name aka SSID>
	wpa-psk <Your WPA Password>

   NOTE: the password should be the encrypted password, see bottom of the doc.

5. Verify by

	sudo ifup wlan0

	ifconfig wlan0

	iwconfig wlan0


Encrypted password:

run
	wpa_passphrase "Acces Point" passphrase

and substitute "Access Point and passphrase with your network name and password.
The encrypted password is the sequence after "psk=".

