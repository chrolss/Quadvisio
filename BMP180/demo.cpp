#include "BMP085.hpp"
#include <iostream>
#include <sstream>
#include <stdlib.h>

/* Demo for the BMP085 class.  Documentation for the class
 * is in BMP085.hpp. */

using namespace std;

void usage () {
	cout << "- USAGE -\n"
		"All arguments are optional.\n"
		"1st arg, oversampling setting: 0-3 (default 1)\n"
		"2nd arg, high res pressure mode: 0 or 1 (default 1)\n";
	exit(0);
}

int main (int argc, const char* argv[]) {
// Set defaults and check for arguments.
	BMP085::OversamplingSetting oss = BMP085::OSS_STANDARD;
	bool hires = true;
	if (argc > 1) {
		int n;
		istringstream(argv[1]) >> n;
		switch (n) {
			case 0:
				oss = BMP085::OSS_LOW;
				break;
			case 1: break;
			case 2:
				oss = BMP085::OSS_HIGH;
				break;
			case 3:
				oss = BMP085::OSS_ULTRAHIGH;
				break;
			default: usage();
		}
		if (argc > 2) {
			istringstream(argv[2]) >> n;
			switch (n) {
				case 0:
					hires = false;
					break;
				case 1: break;
			default: usage();
			}
		}
	}

// Create object.
	BMP085 *bcm = new BMP085(oss);
	// For rev. 1 Model B pis:
	// BMP085 *bcm = new BMP085(oss, "/dev/i2c-0");
	if (!bcm->ok) {
		cerr << bcm->err << endl;
		return 1;
	}
	bcm->hiRes = hires;

// Take reading, report, and repeat ad infititum.
	try {
		BMP085::reading data = bcm->getBoth();
		cout << "Relative altitude at " << data.kPa << " kPa: "
			<< BMP085::getRelativeAltitude(data.kPa) << "m.\n";
		while (1) {
			cout << "\rTemperature: " << data.celcius << " °C    "
				<< "Pressure: " << data.kPa << " kPa         " << flush;
			data = bcm->getBoth();
			sleep(2);
		}
	} catch (BMP085::smbusIOException &ex) {
		cerr << "SMBus I/O Error:\n" << ex.what();
	}
	return 0;
}
